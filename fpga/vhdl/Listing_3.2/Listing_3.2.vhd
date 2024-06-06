library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity killer_ckt is
    Port (
        -- Input signals
        life_in1, life_in2, ctrl_a, ctrl_b : in  std_logic;
        
        -- Output signals
        kill_a, kill_b, kill_c : out std_logic
    );
end killer_ckt;

architecture Behavioral of killer_ckt is
begin
    -- Architecture implementation goes here
end Behavioral;

