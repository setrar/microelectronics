-- testbench_killer.vhd
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_killer is
end tb_killer;

architecture test of tb_killer is
    signal life_in1, life_in2, ctrl_a, ctrl_b : std_logic := '0';
    signal kill_a, kill_b, kill_c : std_logic;

    component killer_ckt
        Port (
            life_in1, life_in2, ctrl_a, ctrl_b : in  std_logic;
            kill_a, kill_b, kill_c : out std_logic
        );
    end component;

begin
    UUT: killer_ckt
        port map (
            life_in1 => life_in1,
            life_in2 => life_in2,
            ctrl_a   => ctrl_a,
            ctrl_b   => ctrl_b,
            kill_a   => kill_a,
            kill_b   => kill_b,
            kill_c   => kill_c
        );

    stimulus: process
    begin
        life_in1 <= '1'; ctrl_a <= '1'; ctrl_b <= '0';
        wait for 10 ns;
        life_in2 <= '1';
        wait for 10 ns;
        ctrl_a <= '0'; ctrl_b <= '1';
        wait for 10 ns;
        -- add more test patterns here

        wait;
    end process;
end test;

