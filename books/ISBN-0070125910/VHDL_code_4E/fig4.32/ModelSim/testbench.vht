LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT mux16to1
      PORT ( w : IN  STD_LOGIC_VECTOR(0 TO 15) ;
             s : IN  STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    f : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL w : STD_LOGIC_VECTOR(0 TO 15);
   SIGNAL s : STD_LOGIC_VECTOR(3 DOWNTO 0);
   SIGNAL f : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      w <= X"5555"; s <= X"0";
      WAIT FOR 10 ns;
      s <= X"1";
      WAIT FOR 10 ns;
      s <= X"E";
      WAIT FOR 10 ns;
      s <= X"F";
      WAIT FOR 10 ns;
      w <= X"AAAA";
      WAIT FOR 10 ns;
      s <= X"E";
      WAIT FOR 10 ns;
      s <= X"1";
      WAIT FOR 10 ns;
      s <= X"0";
		WAIT;
   END PROCESS;                                          

   U1: mux16to1 PORT MAP (w, s, f);
END;
