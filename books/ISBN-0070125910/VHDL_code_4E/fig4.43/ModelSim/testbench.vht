LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT seg7
      PORT ( hex  : IN  STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    leds : OUT STD_LOGIC_VECTOR(1 TO 7) ) ;
   END COMPONENT;

   SIGNAL hex : STD_LOGIC_VECTOR(3 DOWNTO 0);
   SIGNAL leds : STD_LOGIC_VECTOR(1 TO 7);
BEGIN
   vectors: PROCESS           
	BEGIN
      hex <= X"0";
      WAIT FOR 10 ns;
      hex <= X"1";
      WAIT FOR 10 ns;
      hex <= X"2";
      WAIT FOR 10 ns;
      hex <= X"3";
      WAIT FOR 10 ns;
      hex <= X"4";
      WAIT FOR 10 ns;
      hex <= X"7";
      WAIT FOR 10 ns;
      hex <= X"8";
      WAIT FOR 10 ns;
      hex <= X"9";
      WAIT FOR 10 ns;
      hex <= X"E";
      WAIT FOR 10 ns;
      hex <= X"F";
		WAIT;
   END PROCESS;                                          

   U1: seg7 PORT MAP (hex, leds);
END;
