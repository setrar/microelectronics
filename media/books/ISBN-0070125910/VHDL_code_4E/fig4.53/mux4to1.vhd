LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY mux4to1 IS
	PORT ( s : IN STD_LOGIC_VECTOR(1 DOWNTO 0) ;
		 w : IN STD_LOGIC_VECTOR(3 DOWNTO 0) ;
		 f : OUT STD_LOGIC ) ;
END mux4to1 ;

ARCHITECTURE Structure OF mux4to1 IS
	COMPONENT dec2to4
		PORT (w  : IN STD_LOGIC_VECTOR(1 DOWNTO 0) ;
			En : IN STD_LOGIC ;
			y  : OUT STD_LOGIC_VECTOR(0 TO 3));
	END COMPONENT;
	SIGNAL y    : STD_LOGIC_VECTOR(0 TO 3) ;
BEGIN
	decoder: dec2to4 PORT MAP (s, '1', y) ;
	f <= (w(0) AND y(0)) OR (w(1) AND y(1)) OR (w(2) AND y(2)) OR (w(3) AND y(3)) ;
END Structure ;


LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY dec2to4 IS
	PORT ( w	: IN 	STD_LOGIC_VECTOR(1 DOWNTO 0) ;
		 En 	: IN 	STD_LOGIC ;
		 y 	: OUT STD_LOGIC_VECTOR(0 TO 3) ) ;
END dec2to4 ;

ARCHITECTURE Behavior OF dec2to4 IS
	SIGNAL Enw : STD_LOGIC_VECTOR(2 DOWNTO 0) ;
BEGIN
	Enw <= En & w ;
	WITH Enw SELECT
		y <= 	"1000" WHEN "100",
			"0100" WHEN "101",
			"0010" WHEN "110",
			"0001" WHEN "111",
			"0000" WHEN OTHERS ;
END Behavior ;


