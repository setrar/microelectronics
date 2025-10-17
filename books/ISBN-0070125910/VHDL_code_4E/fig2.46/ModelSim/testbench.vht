LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT display
       PORT ( s1, s0              : IN STD_LOGIC ;
              a, b, c, d, e, f, g : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL s1, s0, a, b, c, d, e, f, g : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      s1 <= '0'; s0 <= '0';
      WAIT FOR 20 ns;
      s1 <= '0'; s0 <= '1';
      WAIT FOR 20 ns;
      s1 <= '1'; s0 <= '0';
		WAIT;
   END PROCESS;                                          

   U1: display PORT MAP (s1, s0, a, b, c, d, e, f, g);
END;
