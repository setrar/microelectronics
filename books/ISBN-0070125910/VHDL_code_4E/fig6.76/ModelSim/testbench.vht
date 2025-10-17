LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT arbiter
        PORT ( Clock, Resetn : IN  STD_LOGIC ;
               r             : IN  STD_LOGIC_VECTOR(1 TO 3) ;
               g             : OUT STD_LOGIC_VECTOR(1 TO 3) ) ;
    END COMPONENT ;
    SIGNAL Clock, Resetn : STD_LOGIC ;
    SIGNAL r, g : STD_LOGIC_VECTOR(1 TO 3) ;
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
        Resetn <= '0'; r <= "000";
        WAIT FOR 11 ns;
        Resetn <= '1';
        WAIT FOR 20 ns;
        r <= "110";
        WAIT FOR 80 ns;
        r <= "011";
        WAIT FOR 80 ns;
        r <= "001";
        WAIT FOR 80 ns;
        r <= "000";
        WAIT;
    END PROCESS;                                          

    U1: arbiter PORT MAP (Clock, Resetn, r, g);
END;
