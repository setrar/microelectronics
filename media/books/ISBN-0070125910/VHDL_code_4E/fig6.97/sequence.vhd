LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY sequence IS
	PORT ( Clock, Resetn, w : IN 	STD_LOGIC ;
		 z			: OUT STD_LOGIC ) ;
END sequence ;

ARCHITECTURE Behavior OF sequence IS
	TYPE State_type IS (A, B, C, D, E) ;
	SIGNAL y : State_type ;
BEGIN
	PROCESS ( Resetn, Clock )
	BEGIN
		IF Resetn = '0' THEN
			y <= A ;
		ELSIF (Clock'EVENT AND Clock = '1') THEN
			CASE y IS
				WHEN A =>
					IF w = '0' THEN
						y <= B ;
					ELSE
						y <= D ;
					END IF ;
				WHEN B =>
					IF w = '0' THEN
						y <= C ;
					ELSE
						y <= D ;
					END IF ;
				WHEN C =>
					IF w = '0' THEN
						y <= C ;
					ELSE
						y <= D ;
					END IF ;
				WHEN D =>
					IF w = '0' THEN
						y <= B ;
					ELSE
						y <= E ;
					END IF ;
				WHEN E =>
					IF w = '0' THEN
						y <= B ;
					ELSE
						y <= E ;
					END IF ;
			END CASE ;
		END IF ;
	END PROCESS ;
	z <= '1' WHEN (y = C OR y = E) ELSE '0' ;
END Behavior ;
