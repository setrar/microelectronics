LIBRARY ieee ;
USE ieee.std_logic_1164.all ;
USE ieee.numeric_std.all ;

ENTITY shifter IS
	PORT ( w 	 : IN  UNSIGNED(3 DOWNTO 0) ;
		 Shift : IN	 STD_LOGIC ;
		 y  	 : OUT UNSIGNED(3 DOWNTO 0) ;
		 k	 : OUT STD_LOGIC ) ;
END shifter ;

ARCHITECTURE Behavior OF shifter IS	
BEGIN
	PROCESS ( Shift, w )
	BEGIN
		IF Shift = '1' THEN
			y <= w SRL 1 ;
			k <= w(0) ;
		ELSE
			y <= w ;
			k <= '0' ;
		END IF ;
	END PROCESS ;
END Behavior ;
