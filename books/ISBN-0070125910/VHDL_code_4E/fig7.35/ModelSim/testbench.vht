LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT divider
    GENERIC ( N : INTEGER := 8 ) ;
    PORT ( Clock     : IN     STD_LOGIC ;
           Resetn    : IN     STD_LOGIC ;
           s, LA, EB : IN     STD_LOGIC ;
           DataA         : IN     STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
           DataB         : IN     STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
           R, Q          : BUFFER STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
           Done          : OUT    STD_LOGIC ) ;
   END COMPONENT ;
   SIGNAL Clock, Resetn, s, LA, EB, Done : STD_LOGIC;
   SIGNAL DataA, DataB, R, Q : STD_LOGIC_VECTOR(7 DOWNTO 0);
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
        Resetn <= '0'; DataA <= X"00"; DataB <= X"00"; LA <= '0'; EB <= '0'; s <= '0'; 
        WAIT FOR 11 ns;
        Resetn <= '1';
        WAIT FOR 20 ns;
        DataA <= X"A6"; DataB <= X"08"; LA <= '1'; EB <= '1';
        WAIT FOR 20 ns;
        DataA <= X"00"; DataB <= X"00"; LA <= '0'; EB <= '0';
        s <= '1';
        WAIT FOR 20 ns;
        s <= '0';
        WAIT FOR 160 ns;
        s <= '0';
        WAIT;
   END PROCESS;                                          

   U1: divider PORT MAP (Clock, Resetn, s, LA, EB, DataA, DataB, R, Q, Done);
END;
