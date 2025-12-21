LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT implied
       PORT ( A, B : IN  STD_LOGIC ;
              AeqB : OUT STD_LOGIC ) ;
    END COMPONENT ;
   SIGNAL A, B, AeqB : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      A <= '0'; B <= '0';
      WAIT FOR 10 ns;
      A <= '1'; B <= '0';
      WAIT FOR 10 ns;
      A <= '0'; B <= '1';
      WAIT FOR 10 ns;
      A <= '1'; B <= '1';
		WAIT;
   END PROCESS;                                          

   U1: implied PORT MAP (A, B, AeqB);
END;
