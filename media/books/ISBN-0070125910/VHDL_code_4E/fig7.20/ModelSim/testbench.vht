LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT bitcount
    PORT ( Clock, Resetn : IN     STD_LOGIC ;
           LA, s         : IN     STD_LOGIC ;
           Data          : IN     STD_LOGIC_VECTOR(7 DOWNTO 0) ;
           B             : BUFFER INTEGER RANGE 0 TO 8 ;
           Done          : OUT    STD_LOGIC ) ;
   END COMPONENT ;
   SIGNAL Clock, Resetn, LA, s, Done : STD_LOGIC;
   SIGNAL Data : STD_LOGIC_VECTOR(7 DOWNTO 0);
   SIGNAL B : INTEGER RANGE 0 TO 8;
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
        Resetn <= '0'; Data <= X"00"; LA <= '0'; s <= '0'; 
        WAIT FOR 11 ns;
        Resetn <= '1';
        WAIT FOR 20 ns;
        Data <= X"3B"; LA <= '1';
        WAIT FOR 20 ns;
        Data <= X"00"; LA <= '0';
        WAIT FOR 40 ns;
        s <= '1';
        WAIT FOR 180 ns;
        s <= '0';
        WAIT;
   END PROCESS;                                          

   U1: bitcount PORT MAP (Clock, Resetn, LA, s, Data, B, Done);
END;
