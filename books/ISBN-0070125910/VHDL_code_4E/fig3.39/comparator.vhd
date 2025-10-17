LIBRARY ieee ;
USE ieee.std_logic_1164.all ;
USE work.fulladd_package.all ;

ENTITY comparator IS
	PORT ( X, Y : IN STD_LOGIC_VECTOR(3 DOWNTO 0) ;
		V, N, Z : OUT STD_LOGIC ) ;
END comparator ;

ARCHITECTURE Structure OF comparator IS
	SIGNAL Yn, S : STD_LOGIC_VECTOR(3 DOWNTO 0) ;
	SIGNAL C : STD_LOGIC_VECTOR(1 TO 4) ;

BEGIN
   Yn <= NOT Y;
	stage0: fulladd PORT MAP ( '1', X(0), Yn(0), S(0), C(1) ) ;
	stage1: fulladd PORT MAP ( C(1), X(1), Yn(1), S(1), C(2) ) ;
	stage2: fulladd PORT MAP ( C(2), X(2), Yn(2), S(2), C(3) ) ;
	stage3: fulladd PORT MAP ( C(3), X(3), Yn(3), S(3), C(4) ) ;
	V <= C(4) XOR C(3) ;
	N <= S(3) ;
	Z <= '1' WHEN S(3 DOWNTO 0) = "0000" ELSE '0';
END Structure ;	
