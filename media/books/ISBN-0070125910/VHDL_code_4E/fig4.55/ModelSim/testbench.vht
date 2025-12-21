LIBRARY ieee ;
USE ieee.std_logic_1164.all ;
USE ieee.numeric_std.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT shifter
      PORT ( w     : IN  UNSIGNED(3 DOWNTO 0) ;
             Shift : IN  STD_LOGIC ;
             y     : OUT UNSIGNED(3 DOWNTO 0) ;
			    k     : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL w, y : UNSIGNED(3 DOWNTO 0);
   SIGNAL Shift, k : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      w <= "0101"; Shift <= '0';
      WAIT FOR 20 ns;
      Shift <= '1';
      WAIT FOR 20 ns;
      w <= "1010"; Shift <= '0';
      WAIT FOR 20 ns;
      Shift <= '1';
		WAIT;
   END PROCESS;                                          

   U1: shifter PORT MAP (w, Shift, y, k);
END;
