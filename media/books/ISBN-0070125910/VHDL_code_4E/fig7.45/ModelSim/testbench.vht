LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT sort
    GENERIC ( N : INTEGER := 4 ) ;
    PORT ( Clock, Resetn : IN     STD_LOGIC ;
           s, WrInit, Rd : IN     STD_LOGIC ;
           DataIn        : IN     STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
           RAdd          : IN     INTEGER RANGE 0 TO 3 ;
           DataOut       : BUFFER STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
           Done          : OUT    STD_LOGIC ) ;
   END COMPONENT ;
   SIGNAL Clock, Resetn, s, WrInit, Rd, Done : STD_LOGIC;
   SIGNAL RAdd : INTEGER RANGE 0 TO 3 ;
   SIGNAL DataIn, DataOut : STD_LOGIC_VECTOR(3 DOWNTO 0);
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
        Resetn <= '0'; DataIn <= X"0"; RAdd <= 0; WrInit <= '0'; s <= '0'; Rd <= '0';
        WAIT FOR 11 ns;
        Resetn <= '1';
        WAIT FOR 20 ns;
        DataIn <= X"3"; RAdd <= 0; WrInit <= '1';
        WAIT FOR 20 ns;
        DataIn <= X"2"; RAdd <= 1;
        WAIT FOR 20 ns;
        DataIn <= X"4"; RAdd <= 2;
        WAIT FOR 20 ns;
        DataIn <= X"1"; RAdd <= 3;
        WAIT FOR 20 ns;
        DataIn <= X"0"; RAdd <= 0; WrInit <= '0';
        WAIT FOR 20 ns;
        s <= '1';
        WAIT FOR 700 ns;
        s <= '0';
        WAIT FOR 80 ns;
        Rd <= '1';
        WAIT FOR 20 ns;
        RAdd <= 1;
        WAIT FOR 20 ns;
        RAdd <= 2;
        WAIT FOR 20 ns;
        RAdd <= 3;
        WAIT FOR 20 ns;
        RAdd <= 0; Rd <= '0';
        WAIT;
   END PROCESS;                                          

   U1: sort PORT MAP (Clock, Resetn, s, WrInit, Rd, DataIn, RAdd, DataOut, Done);
END;
