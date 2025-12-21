LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT simple
    PORT ( Clock, Resetn, w     : IN     STD_LOGIC ;
           z                    : OUT     STD_LOGIC ) ;
    END COMPONENT ;
    SIGNAL Clock, Resetn, w, z : STD_LOGIC ;
BEGIN
    clock_process: PROCESS
    BEGIN
        Clock <= '0';
        WAIT FOR 10 ns;
        Clock <= '1';
        WAIT FOR 10 ns;
    END PROCESS;

    vectors: PROCESS           
    BEGIN
        Resetn <= '0'; w <= '0';
        WAIT FOR 11 ns;
        Resetn <= '1';
        WAIT FOR 20 ns;
        w <= '1';
        WAIT FOR 20 ns;
        w <= '0';
        WAIT FOR 20 ns;
        w <= '1';
        WAIT FOR 20 ns;
        w <= '1';
        WAIT FOR 20 ns;
        w <= '0';
        WAIT FOR 20 ns;
        w <= '1';
        WAIT FOR 20 ns;
        w <= '1';
        WAIT FOR 20 ns;
        w <= '1';
        WAIT FOR 20 ns;
        w <= '0';
        WAIT;
    END PROCESS;                                          

    U1: simple PORT MAP (Clock, Resetn, w, z);
END;
