LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT upcount
       PORT ( R                : IN     INTEGER RANGE 0 TO 15 ;
              Clock, Resetn, L : IN     STD_LOGIC ;
              Q                : BUFFER INTEGER RANGE 0 TO 15 ) ;
   END COMPONENT ;
   SIGNAL Clock, Resetn, L : STD_LOGIC ;
   SIGNAL R, Q : INTEGER RANGE 0 TO 15 ;
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
      Resetn <= '0'; L <= '0'; R <= 7;
      WAIT FOR 20 ns;
      Resetn <= '1'; L <= '1';
      WAIT FOR 20 ns;
      L <= '0';
		WAIT;
   END PROCESS;                                          

   U1: upcount PORT MAP (R, Clock, Resetn, L, Q);
END;
