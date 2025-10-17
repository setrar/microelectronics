LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT flipflop
       PORT ( D, Resetn, Clock : IN  STD_LOGIC ;
              Q                : OUT STD_LOGIC ) ;
   END COMPONENT ;
   SIGNAL D, Resetn, Clock, Q : STD_LOGIC;
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
      Resetn <= '0'; D <= '0';
      WAIT FOR 20 ns;
      Resetn <= '1';
      D <= '1';
      WAIT FOR 20 ns;
      D <= '0';
		WAIT;
   END PROCESS;                                          

   U1: flipflop PORT MAP (D, Resetn, Clock, Q);
END;
