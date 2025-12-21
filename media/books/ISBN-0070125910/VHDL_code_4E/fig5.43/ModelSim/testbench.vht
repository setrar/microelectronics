LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT muxdff
       PORT ( D0, D1, Sel, Clock : IN  STD_LOGIC ;
              Q                  : OUT STD_LOGIC ) ;
   END COMPONENT ;
   SIGNAL D0, D1, Sel, Clock, Q : STD_LOGIC;
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
      Sel <= '0';
      D0 <= '0'; D1 <= '1';
      WAIT FOR 20 ns;
      Sel <= '1';
      WAIT FOR 20 ns;
      Sel <= '0';
      WAIT FOR 20 ns;
      Sel <= '1';
		WAIT;
   END PROCESS;                                          

   U1: muxdff PORT MAP (D0, D1, Sel, Clock, Q);
END;
