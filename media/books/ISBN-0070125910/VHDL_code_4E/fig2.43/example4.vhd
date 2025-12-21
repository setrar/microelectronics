LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY example4 IS
    PORT ( x1, x2, s	: IN  STD_LOGIC ;
           f	      : OUT STD_LOGIC ) ;
END example4 ;

ARCHITECTURE Behavior OF example4 IS
BEGIN
    PROCESS ( x1, x2, s )
    BEGIN
        IF s = '0' THEN
            f <= x1 ;
        ELSE
            f <= x2 ;
        END IF ;
    END PROCESS ;
END Behavior ;
