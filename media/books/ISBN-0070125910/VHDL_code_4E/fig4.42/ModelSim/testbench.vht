LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT dec2to4
      PORT ( w	 : IN  STD_LOGIC_VECTOR(1 DOWNTO 0) ;
			    En : IN  STD_LOGIC ;
			    y  : OUT STD_LOGIC_VECTOR(0 TO 3) ) ;
   END COMPONENT;

   SIGNAL w : STD_LOGIC_VECTOR(1 DOWNTO 0);
   SIGNAL En : STD_LOGIC;
   SIGNAL y : STD_LOGIC_VECTOR(0 TO 3);
BEGIN
   vectors: PROCESS           
	BEGIN
      w <= "00"; En <= '0';
      WAIT FOR 20 ns;
      En <= '1';
      WAIT FOR 20 ns;
      w <= "01";
      WAIT FOR 20 ns;
      w <= "10";
      WAIT FOR 20 ns;
      w <= "11";
      WAIT FOR 20 ns;
      En <= '0';
		WAIT;
   END PROCESS;                                          

   U1: dec2to4 PORT MAP (w, En, y);
END;
