LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT example2_30
      PORT ( a, b, c, d, m : IN  STD_LOGIC ;
             s1, s0        : OUT STD_LOGIC ) ;
   END COMPONENT;
   SIGNAL a, b, c, d, m, s1, s0 : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      a <= '0'; b <= '0'; c <= '1'; d <= '1'; m <= '0';
      WAIT FOR 20 ns;
      a <= '0'; b <= '0'; c <= '1'; d <= '1'; m <= '1';
      WAIT FOR 20 ns;
      a <= '1'; b <= '1'; c <= '0'; d <= '0'; m <= '0';
      WAIT FOR 20 ns;
      a <= '1'; b <= '1'; c <= '0'; d <= '0'; m <= '1';
		WAIT;
   END PROCESS;                                          

   U1: example2_30 PORT MAP (a, b, c, d, m, s1, s0);
END;
