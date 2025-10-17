LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT adder
      PORT ( a, b   : IN  STD_LOGIC ;
             s1, s0 : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL a, b, s1, s0 : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      a <= '0'; b <= '0';
      WAIT FOR 20 ns;
      a <= '1'; b <= '0';
      WAIT FOR 20 ns;
      a <= '0'; b <= '1';
      WAIT FOR 20 ns;
      a <= '1'; b <= '1';
		WAIT;
   END PROCESS;                                          

   U1: adder PORT MAP (a, b, s1, s0);
END;
