LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT upcount
   PORT ( Clock, Resetn, E : IN STD_LOGIC ;
          Q                : OUT STD_LOGIC_VECTOR (3 DOWNTO 0)) ;
   END COMPONENT ;
   SIGNAL Clock, Resetn, E : STD_LOGIC;
   SIGNAL Q : STD_LOGIC_VECTOR(3 DOWNTO 0);
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
      Resetn <= '0'; E <= '1';
      WAIT FOR 20 ns;
      Resetn <= '1';
      WAIT FOR 80 ns;
      E <= '0';
      WAIT FOR 20 ns;
      E <= '1';
		WAIT;
   END PROCESS;                                          

   U1: upcount PORT MAP (Clock, Resetn, E, Q);
END;
