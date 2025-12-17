library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity mini_ethernet_phy is
    port (
        clk         : in  std_logic;
        rst         : in  std_logic;
        din         : in  std_logic;
        payload_out : out std_logic_vector(3 downto 0);
        frame_ready : out std_logic
    );
end mini_ethernet_phy;

architecture rtl of mini_ethernet_phy is

    type state_type is (IDLE, PREAMBLE, SFD, PAYLOAD);
    signal state : state_type := IDLE;

    signal shift_reg  : std_logic_vector(7 downto 0) := (others => '0');
    signal byte_reg   : std_logic_vector(7 downto 0) := (others => '0');
    signal bit_cnt    : integer range 0 to 7 := 0;
    signal pre_cnt    : integer range 0 to 6 := 0;
    signal byte_valid : std_logic := '0';

begin

    process(clk)
    begin
        if rising_edge(clk) then
            if rst = '1' then
                shift_reg   <= (others => '0');
                byte_reg    <= (others => '0');
                bit_cnt     <= 0;
                pre_cnt     <= 0;
                state       <= IDLE;
                payload_out <= (others => '0');
                frame_ready <= '0';
                byte_valid  <= '0';

            else
                frame_ready <= '0';
                byte_valid  <= '0';

                -- Shift in serial bit (MSB first)
                shift_reg <= shift_reg(6 downto 0) & din;

                if bit_cnt = 7 then
                    bit_cnt    <= 0;
                    byte_reg   <= shift_reg(6 downto 0) & din;
                    byte_valid <= '1';
                else
                    bit_cnt <= bit_cnt + 1;
                end if;

                -- FSM consumes FULL BYTES only
                if byte_valid = '1' then
                    case state is
                        when IDLE =>
                            if byte_reg = "10101010" then
                                state   <= PREAMBLE;
                                pre_cnt <= 1;
                            end if;

                        when PREAMBLE =>
                            if byte_reg = "10101010" then
                                if pre_cnt = 6 then
                                    state <= SFD;
                                else
                                    pre_cnt <= pre_cnt + 1;
                                end if;
                            else
                                state   <= IDLE;
                                pre_cnt <= 0;
                            end if;

                        when SFD =>
                            if byte_reg = "10101011" then
                                state <= PAYLOAD;
                            else
                                state <= IDLE;
                            end if;

                        when PAYLOAD =>
                            payload_out <= byte_reg(3 downto 0);
                            frame_ready <= '1';
                            state <= IDLE;
                    end case;
                end if;
            end if;
        end if;
    end process;

end rtl;

