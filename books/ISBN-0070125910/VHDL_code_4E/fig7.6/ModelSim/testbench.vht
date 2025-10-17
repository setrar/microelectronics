LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT trin
        GENERIC ( N : INTEGER := 8 ) ;
        PORT ( X : IN  STD_LOGIC_VECTOR(N-1 DOWNTO 0);
               E : IN  STD_LOGIC ;
               F  : OUT STD_LOGIC_VECTOR(N-1 DOWNTO 0) );
    END COMPONENT ;
    SIGNAL E : STD_LOGIC;
    SIGNAL X, F : STD_LOGIC_VECTOR(7 DOWNTO 0);
BEGIN
    vectors: PROCESS           
    BEGIN
        E <= '0'; X <= X"55";
        WAIT FOR 20 ns;
        E <= '1';
        WAIT FOR 20 ns;
        X <= X"AA"; E <= '0';
        WAIT FOR 20 ns;
        E <= '1';
        WAIT;
   END PROCESS;                                          

   U1: trin PORT MAP (X, E, F);
END;
