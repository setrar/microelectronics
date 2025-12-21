LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT f_g
      PORT ( x, y, z : IN  STD_LOGIC ;
             f, g    : OUT STD_LOGIC ) ;
   END COMPONENT;
   SIGNAL x, y, z, f, g : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      x <= '0'; y <= '0'; z <= '0';
      WAIT FOR 20 ns;
      x <= '1'; y <= '0'; z <= '0';
      WAIT FOR 20 ns;
      x <= '0'; y <= '1'; z <= '0';
      WAIT FOR 20 ns;
      x <= '1'; y <= '1'; z <= '0';
      WAIT FOR 20 ns;
      x <= '0'; y <= '0'; z <= '1';
      WAIT FOR 20 ns;
      x <= '1'; y <= '0'; z <= '1';
      WAIT FOR 20 ns;
      x <= '0'; y <= '1'; z <= '1';
      WAIT FOR 20 ns;
      x <= '1'; y <= '1'; z <= '1';
		WAIT;
   END PROCESS;                                          

   U1: f_g PORT MAP (x, y, z, f, g);
END;
