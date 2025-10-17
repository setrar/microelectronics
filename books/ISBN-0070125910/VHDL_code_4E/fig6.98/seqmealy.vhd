LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY seqmealy IS
	PORT ( Clock, Resetn, w : IN 	STD_LOGIC ;
		 z			: OUT STD_LOGIC ) ;
END seqmealy ;

ARCHITECTURE Behavior OF seqmealy IS
	TYPE State_type IS (A, B, C) ;
	SIGNAL y : State_type ;
BEGIN
	PROCESS ( Resetn, Clock )
	BEGIN
		IF Resetn = '0' THEN
			y <= A ;
		ELSIF (Clock'EVENT AND Clock = '1') THEN
			CASE y IS
				WHEN A =>
					IF w = '0' THEN y <= B ;
					ELSE y <= C ;
					END IF ;
				WHEN B =>
					IF w = '0' THEN y <= B ;
					ELSE y <= C ;
					END IF ;
				WHEN C =>
					IF w = '0' THEN y <= B ;
					ELSE y <= C ;
					END IF ;
			END CASE ;
		END IF ;
	END PROCESS ;

	PROCESS ( y, w )
	BEGIN
		CASE y IS
			WHEN A =>
				z <= '0' ;
			WHEN B =>
				z <= NOT w ;
			WHEN C =>
				z <= w ;
		END CASE ;
	END PROCESS ;
END Behavior ;
