LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY parity IS
    PORT ( X : IN  STD_LOGIC_VECTOR(7 DOWNTO 0) ;
           Y : OUT STD_LOGIC_VECTOR(7 DOWNTO 0) ) ;
END parity ;

ARCHITECTURE Behavior OF parity IS    
    SIGNAL p : STD_LOGIC;
BEGIN
    p <= X(0) XOR X(1) XOR X(2) XOR X(3) XOR X(4) XOR X(5) XOR X(6) ;
    Y <= p & X(6 DOWNTO 0) ;
END Behavior ;
