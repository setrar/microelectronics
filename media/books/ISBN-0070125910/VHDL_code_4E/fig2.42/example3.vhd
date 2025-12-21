LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY example3 IS
    PORT ( x1, x2, s	: IN  STD_LOGIC ;
           f	      : OUT STD_LOGIC ) ;
END example3 ;

ARCHITECTURE LogicFunc OF example3 IS 
BEGIN   
    f <= (NOT s AND x1) OR (s AND x2) ; 
END LogicFunc ; 
