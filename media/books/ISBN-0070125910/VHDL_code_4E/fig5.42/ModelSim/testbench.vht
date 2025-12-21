LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT regn
       GENERIC ( N : INTEGER := 16 ) ;
       PORT ( D             : IN  STD_LOGIC_VECTOR(N-1 DOWNTO 0);
              Resetn, Clock : IN  STD_LOGIC ;
              Q             : OUT STD_LOGIC_VECTOR(N-1 DOWNTO 0) );
   END COMPONENT ;
   SIGNAL Resetn, Clock : STD_LOGIC;
   SIGNAL D, Q : STD_LOGIC_VECTOR(15 DOWNTO 0);
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
      Resetn <= '0'; D <= X"5555";
      WAIT FOR 20 ns;
      Resetn <= '1';
      WAIT FOR 20 ns;
      D <= X"AAAA";
      WAIT FOR 20 ns;
      D <= X"0000";
		WAIT;
   END PROCESS;                                          

   U1: regn PORT MAP (D, Resetn, Clock, Q);
END;
