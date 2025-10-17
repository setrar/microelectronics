LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

PACKAGE components IS
	-- 2-to-1 multiplexer
	COMPONENT mux2to1 
		PORT (	w0, w1 	: IN 	STD_LOGIC ;
				s 		: IN 	STD_LOGIC ;
				f 		: OUT 	STD_LOGIC );
	END COMPONENT ;

	-- n-bit register with enable
	COMPONENT regne  
		GENERIC ( N : INTEGER := 4 ) ;
		PORT (	R 			: IN 	STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
				Resetn 		: IN 	STD_LOGIC ;
				E, Clock 	: IN 	STD_LOGIC ;
				Q 			: OUT 	STD_LOGIC_VECTOR(N-1 DOWNTO 0) ) ;
	END COMPONENT ;

	-- n-bit right-to-left shift register with parallel load and enable
	COMPONENT shiftlne  
		GENERIC ( N : INTEGER := 4 ) ;
		PORT (	R 			: IN 		STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
				L, E, w		: IN 		STD_LOGIC ;
				Clock		: IN 		STD_LOGIC ;
				Q 			: BUFFER 	STD_LOGIC_VECTOR(N-1 DOWNTO 0) ) ;
	END COMPONENT ;

	-- n-bit left-to-right shift register with parallel load and enable
	COMPONENT shiftrne  
		GENERIC ( N : INTEGER := 4 ) ;
		PORT (	R 		: IN 		STD_LOGIC_VECTOR(N-1 DOWNTO 0) ;
				L, E, w	: IN 		STD_LOGIC ;
				Clock	: IN 		STD_LOGIC ;
				Q 		: BUFFER 	STD_LOGIC_VECTOR(N-1 DOWNTO 0) ) ;
	END COMPONENT ;

END components ;
