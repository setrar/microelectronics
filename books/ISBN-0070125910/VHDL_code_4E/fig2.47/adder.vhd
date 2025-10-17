-- An adder circuit
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

