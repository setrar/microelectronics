LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT example4
      PORT ( x1, x2, s : IN  STD_LOGIC ;
             f         : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL x1, x2, s, f : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      x1 <= '0'; x2 <= '0'; s <= '0';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '0'; s <= '0';
      WAIT FOR 20 ns;
      x1 <= '0'; x2 <= '1'; s <= '0';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '1'; s <= '0';
      WAIT FOR 20 ns;
      x1 <= '0'; x2 <= '0'; s <= '1';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '0'; s <= '1';
      WAIT FOR 20 ns;
      x1 <= '0'; x2 <= '1'; s <= '1';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '1'; s <= '1';
		WAIT;
   END PROCESS;                                          

   U1: example4 PORT MAP (x1, x2, s, f);
END;
