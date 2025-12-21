LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

PACKAGE components IS

	COMPONENT regn -- register
		GENERIC ( N : INTEGER := 8 ) ;
		PORT ( 	R 			: IN 	STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
				L, Clock 	: IN 	STD_LOGIC ;
				Q 			: OUT 	STD_LOGIC_VECTOR(N-1 DOWNTO 0) ) ;
	END COMPONENT ;

END components ;
