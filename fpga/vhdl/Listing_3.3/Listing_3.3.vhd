library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity mux_4 is
    Port (
        -- Input data signals
        a_data, b_data, c_data, d_data : in  std_logic_vector(7 downto 0);
        
        -- Select signals
        sel0, sel1 : in  std_logic;
        
        -- Output data signal
        data_out   : out std_logic_vector(7 downto 0)
    );
end mux_4;

architecture Behavioral of mux_4 is
begin
    process (a_data, b_data, c_data, d_data, sel0, sel1)
    begin
        case (sel1 & sel0) is
            when "00" =>
                data_out <= a_data;
            when "01" =>
                data_out <= b_data;
            when "10" =>
                data_out <= c_data;
            when "11" =>
                data_out <= d_data;
            when others =>
                data_out <= (others => '0'); -- default case
        end case;
    end process;
end Behavioral;
