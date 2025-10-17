LIBRARY ieee ;
USE ieee.std_logic_1164.all ;
USE ieee.numeric_std.all ;

ENTITY barrel IS
	PORT ( w : IN  UNSIGNED(3 DOWNTO 0) ;
		 s : IN  UNSIGNED(1 DOWNTO 0) ;
		 y : OUT UNSIGNED(3 DOWNTO 0) ) ;
END barrel ;

ARCHITECTURE Behavior OF barrel IS	
BEGIN
	PROCESS ( s, w )
	BEGIN
		CASE s IS
			WHEN "00" =>
				y <= w ;
		    	WHEN "01" =>
				y <= w ROR 1 ;
			WHEN "10" =>
				y <= w ROR 2 ;
			WHEN OTHERS =>
				y <= w ROR 3 ;
		END CASE ;
	END PROCESS ;
END Behavior ;
