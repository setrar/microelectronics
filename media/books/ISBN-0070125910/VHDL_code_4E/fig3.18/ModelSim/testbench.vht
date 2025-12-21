LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT fulladd
      PORT ( Cin, x, y : IN 	STD_LOGIC ;
				 s, Cout	  : OUT	STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL Cin, x, y, s, Cout : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      Cin <= '0'; x <= '0'; y <= '0';
      WAIT FOR 20 ns;
      Cin <= '0'; x <= '1'; y <= '0';
      WAIT FOR 20 ns;
      Cin <= '0'; x <= '0'; y <= '1';
      WAIT FOR 20 ns;
      Cin <= '0'; x <= '1'; y <= '1';
      WAIT FOR 20 ns;
      Cin <= '1'; x <= '0'; y <= '0';
      WAIT FOR 20 ns;
      Cin <= '1'; x <= '1'; y <= '0';
      WAIT FOR 20 ns;
      Cin <= '1'; x <= '0'; y <= '1';
      WAIT FOR 20 ns;
      Cin <= '1'; x <= '1'; y <= '1';
      WAIT FOR 20 ns;
		WAIT;
   END PROCESS;                                          

   U1: fulladd PORT MAP (Cin, x, y, s, Cout);
END;
