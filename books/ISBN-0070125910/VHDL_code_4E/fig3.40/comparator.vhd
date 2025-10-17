LIBRARY ieee ;
USE ieee.std_logic_1164.all ;
USE ieee.std_logic_signed.all ;

ENTITY comparator IS
	PORT ( X, Y 	: IN 	STD_LOGIC_VECTOR(3 DOWNTO 0) ;
		 V, N, Z 	: OUT 	STD_LOGIC ) ;
END comparator ;

ARCHITECTURE Behavior OF comparator IS    
	SIGNAL S : STD_LOGIC_VECTOR(4 DOWNTO 0) ;
BEGIN
	S <= ('0' & X) - ('0' & Y) ;
	V <= S(4) XOR X(3) XOR Y(3) XOR S(3) ;
	N <= S(3) ;
	Z <= '1' WHEN S(3 DOWNTO 0) = 0 ELSE '0';
END Behavior ;
