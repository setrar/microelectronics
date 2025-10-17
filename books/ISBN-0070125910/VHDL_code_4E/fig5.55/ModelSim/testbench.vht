LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT shiftrne
    GENERIC ( N : INTEGER := 4 ) ;
    PORT ( R        : IN  STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
           L, E, w  : IN  STD_LOGIC ;
           Clock    : IN  STD_LOGIC ;
           Q        : OUT STD_LOGIC_VECTOR(N-1 DOWNTO 0) ) ;
   END COMPONENT ;
   SIGNAL L, E, w, Clock : STD_LOGIC ;
   SIGNAL R, Q : STD_LOGIC_VECTOR(3 DOWNTO 0);
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
        L <= '1'; E <= '0'; w <= '1'; R <= X"5";
        WAIT FOR 20 ns;
        L <= '0'; E <= '1';
        WAIT;
   END PROCESS;                                          

   U1: shiftrne PORT MAP (R, L, E, w, Clock, Q);
END;
