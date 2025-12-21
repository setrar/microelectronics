LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY example2_30 IS 
    PORT ( a, b, c, d, m : IN  STD_LOGIC ; 
           s1, s0        : OUT STD_LOGIC ) ; 
END example2_30 ;

ARCHITECTURE Structure OF example2_30 IS
    COMPONENT example3 IS 
    PORT ( x1, x2, s : IN  STD_LOGIC ; 
           f         : OUT STD_LOGIC ) ; 
    END COMPONENT ; 
    COMPONENT adder IS
        PORT ( a, b    : IN  STD_LOGIC ; 
               s1, s0  : OUT STD_LOGIC ) ;
    END COMPONENT ; 
    SIGNAL w1, w2 : STD_LOGIC ;
BEGIN 
    U1: example3 PORT MAP ( a, c, m, w1 ) ;
    U2: example3 PORT MAP ( b, d, m, w2 ) ;
    U3: adder PORT MAP ( w1, w2, s1, s0 ) ;
END Structure ;

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

LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY adder IS
    PORT ( a, b	: IN  STD_LOGIC ;
           s1, s0	: OUT STD_LOGIC ) ;
END adder ;

ARCHITECTURE Behavior OF adder IS
BEGIN
    s1 <= a AND b ;
    s0 <= a XOR b ;
END Behavior ;


