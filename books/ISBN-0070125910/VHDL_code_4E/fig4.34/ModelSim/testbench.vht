LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT mux2to1
      PORT ( w0, w1, s : IN  STD_LOGIC ;
			    f			  : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL w0, w1, s, f : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      w0 <= '0'; w1 <= '0'; s <= '0';
      WAIT FOR 20 ns;
      w0 <= '1'; w1 <= '0'; s <= '0';
      WAIT FOR 20 ns;
      w0 <= '0'; w1 <= '1'; s <= '0';
      WAIT FOR 20 ns;
      w0 <= '1'; w1 <= '1'; s <= '0';
      WAIT FOR 20 ns;
      w0 <= '0'; w1 <= '0'; s <= '1';
      WAIT FOR 20 ns;
      w0 <= '1'; w1 <= '0'; s <= '1';
      WAIT FOR 20 ns;
      w0 <= '0'; w1 <= '1'; s <= '1';
      WAIT FOR 20 ns;
      w0 <= '1'; w1 <= '1'; s <= '1';
		WAIT;
   END PROCESS;                                          

   U1: mux2to1 PORT MAP (w0, w1, s, f);
END;
