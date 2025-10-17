LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT priority
      PORT ( w	: IN  STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    y : OUT STD_LOGIC_VECTOR(1 DOWNTO 0) ;
			    z : OUT  STD_LOGIC );
   END COMPONENT;

   SIGNAL w : STD_LOGIC_VECTOR(3 DOWNTO 0);
   SIGNAL y : STD_LOGIC_VECTOR(1 DOWNTO 0);
   SIGNAL z : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      w <= X"0";
      WAIT FOR 10 ns;
      w <= X"1";
      WAIT FOR 10 ns;
      w <= X"2";
      WAIT FOR 10 ns;
      w <= X"3";
      WAIT FOR 10 ns;
      w <= X"4";
      WAIT FOR 10 ns;
      w <= X"7";
      WAIT FOR 10 ns;
      w <= X"8";
      WAIT FOR 10 ns;
      w <= X"9";
      WAIT FOR 10 ns;
      w <= X"F";
		WAIT;
   END PROCESS;                                          

   U1: priority PORT MAP (w, y, z);
END;
