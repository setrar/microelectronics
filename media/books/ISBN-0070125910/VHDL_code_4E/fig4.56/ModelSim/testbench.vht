LIBRARY ieee ;
USE ieee.std_logic_1164.all ;
USE ieee.numeric_std.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT barrel
      PORT ( w     : IN  UNSIGNED(3 DOWNTO 0) ;
             s     : IN  UNSIGNED(1 DOWNTO 0) ;
             y     : OUT UNSIGNED(3 DOWNTO 0) ) ;
   END COMPONENT;

   SIGNAL w, y : UNSIGNED(3 DOWNTO 0);
   SIGNAL s : UNSIGNED(1 DOWNTO 0);
BEGIN
   vectors: PROCESS           
	BEGIN
      w <= "0101"; s <= "00";
      WAIT FOR 10 ns;
      s <= "01";
      WAIT FOR 10 ns;
      s <= "10";
      WAIT FOR 10 ns;
      s <= "11";
      WAIT FOR 10 ns;
      w <= "0001"; s <= "00";
      WAIT FOR 10 ns;
      s <= "01";
      WAIT FOR 10 ns;
      s <= "10";
      WAIT FOR 10 ns;
      s <= "11";
		WAIT;
   END PROCESS;                                          

   U1: barrel PORT MAP (w, s, y);
END;
