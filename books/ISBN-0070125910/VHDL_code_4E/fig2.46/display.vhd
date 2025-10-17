-- A circuit for driving a 7-segment display
LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY display IS
    PORT ( s1, s0              : IN STD_LOGIC ;
           a, b, c, d, e, f, g : OUT STD_LOGIC ) ;
END display ;

ARCHITECTURE Behavior OF display IS
BEGIN
    a <= NOT s0 ;
    b <= '1' ;
    c <= NOT s1 ;
    d <= NOT s0 ;
    e <= NOT s0 ;
    f <= NOT s1 AND NOT s0 ;
    g <= s1 AND NOT s0 ;
END Behavior ;

