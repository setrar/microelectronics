LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT seg7
        PORT ( bcd  : IN  STD_LOGIC_VECTOR(3 DOWNTO 0) ;
               leds : OUT STD_LOGIC_VECTOR(1 TO 7) ) ;
    END COMPONENT ;
    SIGNAL bcd  : STD_LOGIC_VECTOR(3 DOWNTO 0);
    SIGNAL leds : STD_LOGIC_VECTOR(1 TO 7);
BEGIN
    vectors: PROCESS           
    BEGIN
        bcd <= "0000";
        WAIT FOR 10 ns;
        bcd <= "0001";
        WAIT FOR 10 ns;
        bcd <= "0010";
        WAIT FOR 10 ns;
        bcd <= "1001";
        WAIT;
    END PROCESS;                                          

    U1: seg7 PORT MAP (bcd, leds);
END;
