LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT regn
        GENERIC ( N : INTEGER := 8 ) ;
        PORT ( R        : IN  STD_LOGIC_VECTOR(N-1 DOWNTO 0);
               L, Clock : IN  STD_LOGIC ;
               Q        : OUT STD_LOGIC_VECTOR(N-1 DOWNTO 0) );
    END COMPONENT ;
    SIGNAL L, Clock : STD_LOGIC;
    SIGNAL R, Q : STD_LOGIC_VECTOR(7 DOWNTO 0);
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
        L <= '0'; R <= X"55";
        WAIT FOR 20 ns;
        L <= '1';
        WAIT FOR 20 ns;
        R <= X"AA";
        WAIT FOR 20 ns;
        R <= X"00";
        WAIT;
   END PROCESS;                                          

   U1: regn PORT MAP (R, L, Clock, Q);
END;
