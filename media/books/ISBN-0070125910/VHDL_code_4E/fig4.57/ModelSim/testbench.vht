LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT parity
      PORT ( X : IN  STD_LOGIC_VECTOR(7 DOWNTO 0) ;
             Y : OUT STD_LOGIC_VECTOR(7 DOWNTO 0) ) ;
   END COMPONENT;

   SIGNAL X, Y : STD_LOGIC_VECTOR(7 DOWNTO 0);
BEGIN
   vectors: PROCESS           
	BEGIN
      X <= "00000000";
      WAIT FOR 20 ns;
      X <= "00000001";
      WAIT FOR 20 ns;
      X <= "01010101";
      WAIT FOR 20 ns;
      X <= "01110101";
		WAIT;
   END PROCESS;                                          

   U1: parity PORT MAP (X, Y);
END;
