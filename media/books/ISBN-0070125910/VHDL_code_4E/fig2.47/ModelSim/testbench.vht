LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT adder_display
       PORT ( x, y                : IN STD_LOGIC ;
              a, b, c, d, e, f, g : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL x, y, a, b, c, d, e, f, g : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      x <= '0'; y <= '0';
      WAIT FOR 20 ns;
      x <= '0'; y <= '1';
      WAIT FOR 20 ns;
      x <= '1'; y <= '0';
      WAIT FOR 20 ns;
      x <= '1'; y <= '1';
		WAIT;
   END PROCESS;                                          

   U1: adder_display PORT MAP (x, y, a, b, c, d, e, f, g);
END;
