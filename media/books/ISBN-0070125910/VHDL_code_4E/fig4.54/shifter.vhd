LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY shifter IS
	PORT ( w 	 : IN  STD_LOGIC_VECTOR(3 DOWNTO 0) ;
		 Shift : IN	 STD_LOGIC ;
		 y  	 : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) ;
		 k	 : OUT STD_LOGIC ) ;
END shifter ;

ARCHITECTURE Behavior OF shifter IS	
BEGIN
	PROCESS ( Shift, w )
	BEGIN
		IF Shift = '1' THEN
			y(3) <= '0' ;
			y(2 DOWNTO 0) <= w(3 DOWNTO 1) ;
			k <= w(0) ;
		ELSE
			y <= w ;
			k <= '0' ;
		END IF ;
	END PROCESS ;
END Behavior ;
