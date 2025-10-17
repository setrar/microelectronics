LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT dec4to16
      PORT ( w	 : IN  STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    En : IN  STD_LOGIC ;
			    y	 : OUT STD_LOGIC_VECTOR(0 TO 15) ) ;
   END COMPONENT;

   SIGNAL w : STD_LOGIC_VECTOR(3 DOWNTO 0);
   SIGNAL En : STD_LOGIC;
   SIGNAL y : STD_LOGIC_VECTOR(0 TO 15);
BEGIN
   vectors: PROCESS           
	BEGIN
      w <= X"0"; En <= '0';
      WAIT FOR 10 ns;
      En <= '1';
      WAIT FOR 10 ns;
      w <= X"1";
      WAIT FOR 10 ns;
      w <= X"2";
      WAIT FOR 10 ns;
      w <= X"E";
      WAIT FOR 10 ns;
      w <= X"F";
      WAIT FOR 10 ns;
      En <= '0';
		WAIT;
   END PROCESS;                                          

   U1: dec4to16 PORT MAP (w, En, y);
END;
