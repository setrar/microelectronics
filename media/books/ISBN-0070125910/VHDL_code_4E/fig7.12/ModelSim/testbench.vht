LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT upcount
   PORT ( Clear, Clock : IN STD_LOGIC ;
          Q            : OUT STD_LOGIC_VECTOR (1 DOWNTO 0)) ;
   END COMPONENT ;
   SIGNAL Clear, Clock : STD_LOGIC;
   SIGNAL Q : STD_LOGIC_VECTOR(1 DOWNTO 0);
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
      Clear <= '1';
      WAIT FOR 20 ns;
      Clear <= '0';
		WAIT;
   END PROCESS;                                          

   U1: upcount PORT MAP (Clear, Clock, Q);
END;
