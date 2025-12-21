LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT adder4
      PORT ( Cin				 : IN  STD_LOGIC ;
			    x3, x2, x1, x0 : IN  STD_LOGIC ;
			    y3, y2, y1, y0 : IN  STD_LOGIC ;
			    s3, s2, s1, s0 : OUT STD_LOGIC ;
			    Cout 			 : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL Cin, x3, x2, x1, x0, y3, y2, y1, y0 : STD_LOGIC;
   SIGNAL s3, s2, s1, s0, Cout : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      Cin <= '0';
      x3 <= '0'; x2 <= '0'; x1 <= '0'; x0 <= '0';
      y3 <= '0'; y2 <= '0'; y1 <= '0'; y0 <= '0';
      WAIT FOR 20 ns;
      x3 <= '0'; x2 <= '1'; x1 <= '0'; x0 <= '1';
      y3 <= '0'; y2 <= '0'; y1 <= '0'; y0 <= '0';
      WAIT FOR 20 ns;
      x3 <= '0'; x2 <= '1'; x1 <= '0'; x0 <= '1';
      y3 <= '1'; y2 <= '0'; y1 <= '1'; y0 <= '0';
      WAIT FOR 20 ns;
      Cin <= '1';
      WAIT FOR 20 ns;
      x3 <= '0'; x2 <= '1'; x1 <= '0'; x0 <= '1';
      y3 <= '0'; y2 <= '0'; y1 <= '0'; y0 <= '0';
      WAIT FOR 20 ns;
      x3 <= '0'; x2 <= '0'; x1 <= '0'; x0 <= '0';
      y3 <= '0'; y2 <= '0'; y1 <= '0'; y0 <= '0';
		WAIT;
   END PROCESS;                                          

   U1: adder4 PORT MAP (Cin, x3, x2, x1, x0, y3, y2, y1, y0, s3, s2, s1, s0, Cout);
END;
