LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT multiply
    GENERIC ( N : INTEGER := 8; NN : INTEGER := 16 ) ;
    PORT ( Clock, Resetn : IN     STD_LOGIC ;
           LA, LB, s     : IN     STD_LOGIC ;
           DataA         : IN     STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
           DataB         : IN     STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
           P             : BUFFER STD_LOGIC_VECTOR(NN-1 DOWNTO 0) ;
           Done          : OUT    STD_LOGIC ) ;
   END COMPONENT ;
   SIGNAL Clock, Resetn, LA, LB, s, Done : STD_LOGIC;
   SIGNAL DataA, DataB : STD_LOGIC_VECTOR(7 DOWNTO 0);
   SIGNAL P : STD_LOGIC_VECTOR(15 DOWNTO 0);
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
        Resetn <= '0'; DataA <= X"00"; DataB <= X"00"; LA <= '0'; LB <= '0'; s <= '0'; 
        WAIT FOR 11 ns;
        Resetn <= '1';
        WAIT FOR 20 ns;
        DataA <= X"64"; DataB <= X"19"; LA <= '1'; LB <= '1';
        WAIT FOR 20 ns;
        DataA <= X"00"; DataB <= X"00"; LA <= '0'; LB <= '0';
        WAIT FOR 20 ns;
        s <= '1';
        WAIT FOR 160 ns;
        s <= '0';
        WAIT;
   END PROCESS;                                          

   U1: multiply PORT MAP (Clock, Resetn, LA, LB, s, DataA, DataB, P, Done);
END;
