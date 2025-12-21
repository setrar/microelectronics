LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY adder_display IS 
    PORT ( x, y                : IN  STD_LOGIC ; 
           a, b, c, d, e, f, g : OUT STD_LOGIC ) ; 
END adder_display ;

ARCHITECTURE Structure OF adder_display IS
    COMPONENT adder IS
        PORT ( a, b    : IN  STD_LOGIC ; 
               s1, s0  : OUT STD_LOGIC ) ;
    END COMPONENT ; 
    COMPONENT display IS 
    PORT ( s1, s0              : IN  STD_LOGIC ; 
           a, b, c, d, e, f, g : OUT STD_LOGIC ) ; 
    END COMPONENT ; 
    SIGNAL w1, w0 : STD_LOGIC ;
BEGIN 
    U1: adder PORT MAP ( x, y, w1, w0 ) ;
    U2: display PORT MAP ( w1, w0, a, b, c, d, e, f, g ) ;
END Structure ;
