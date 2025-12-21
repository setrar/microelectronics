LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY f_g IS 
    PORT ( x, y, z : IN  STD_LOGIC ; 
           f, g    : OUT STD_LOGIC ) ; 
END f_g ;

ARCHITECTURE LogicFunc OF f_g IS 
    SIGNAL k : STD_LOGIC ; 
BEGIN
    k <= y XOR z ; 
    g <= k XOR x ;
    f  <= (NOT k AND z) OR (k AND x) ; 
END LogicFunc ;

