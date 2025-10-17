LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT downcnt
       GENERIC ( modulus : INTEGER := 8 ) ;
       PORT ( Clock, L, E : IN     STD_LOGIC ;
              Q           : OUT INTEGER RANGE 0 TO modulus-1 ) ;
   END COMPONENT ;
   SIGNAL Clock, L, E : STD_LOGIC ;
   SIGNAL Q : INTEGER RANGE 0 TO 7 ;
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
      L <= '1'; E <= '0';
      WAIT FOR 20 ns;
      L <= '0';
      WAIT FOR 40 ns;
      E <= '1';
		WAIT;
   END PROCESS;                                          

   U1: downcnt PORT MAP (Clock, L, E, Q);
END;
