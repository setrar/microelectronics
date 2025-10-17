LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT adder4
      PORT ( Cin 	: IN 	STD_LOGIC ;
			    X, Y	: IN 	STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    S 	: OUT STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    Cout	: OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL Cin, Cout : STD_LOGIC;
   SIGNAL X, Y, S : STD_LOGIC_VECTOR(3 DOWNTO 0);
BEGIN
   vectors: PROCESS           
	BEGIN
      Cin <= '0';
      X <= "0000"; Y <= "0000"; 
      WAIT FOR 20 ns;
      X <= "0101"; Y <= "0000"; 
      WAIT FOR 20 ns;
      X <= "0101"; Y <= "1010"; 
      WAIT FOR 20 ns;
      Cin <= '1';
      WAIT FOR 20 ns;
      X <= "0101"; Y <= "0000"; 
      WAIT FOR 20 ns;
      X <= "0000"; Y <= "0000"; 
		WAIT;
   END PROCESS;                                          

   U1: adder4 PORT MAP (Cin, X, Y, S, Cout);
END;
