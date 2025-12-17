library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;
use std.env.all;

entity tb_mini_ethernet_phy is
end tb_mini_ethernet_phy;

architecture sim of tb_mini_ethernet_phy is

    signal clk         : std_logic := '0';
    signal rst         : std_logic := '1';
    signal din         : std_logic := '0';
    signal payload_out : std_logic_vector(3 downto 0);
    signal frame_ready : std_logic;

    constant CLK_PERIOD : time := 10 ns;

    -- Send byte MSB-first
    procedure send_byte(
        signal d : out std_logic;
        constant b : std_logic_vector(7 downto 0)
    ) is
    begin
        for i in 7 downto 0 loop
            d <= b(i);
            wait until rising_edge(clk);
        end loop;
    end procedure;

begin

    clk <= not clk after CLK_PERIOD/2;

    dut: entity work.mini_ethernet_phy
        port map (
            clk         => clk,
            rst         => rst,
            din         => din,
            payload_out => payload_out,
            frame_ready => frame_ready
        );

    stim: process
    begin
        -- reset
        wait for 30 ns;
        rst <= '0';

        -- 7x preamble
        for i in 1 to 7 loop
            send_byte(din, "10101010");
        end loop;

        -- SFD
        send_byte(din, "10101011");

        -- payload (1010xxxx)
        send_byte(din, "10100000");

        -- wait for frame_ready
        loop
            wait until rising_edge(clk);
            exit when frame_ready = '1';
        end loop;

        assert payload_out = "1010"
            report "ERROR: Payload mismatch"
            severity error;

        report "OK: Frame received correctly" severity note;
        stop;
    end process;

    watchdog: process
    begin
        wait for 5 us;
        assert false
            report "ERROR: Simulation timeout"
            severity failure;
    end process;

end sim;

