LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT vend
        PORT ( N, D, Q, Resetn, Coin  : IN  STD_LOGIC ;
               Z                      : OUT STD_LOGIC ) ;
    END COMPONENT ;
    SIGNAL N, D, Q, Resetn, Coin, Z : STD_LOGIC;
BEGIN
    vectors: PROCESS           
    BEGIN
        Resetn <= '0'; 
        N <= '0'; D <= '0'; Q <= '0'; Coin <= '0';
        WAIT FOR 10 ns;
        Resetn <= '1'; 
        N <= '1'; Coin <= '1';
        WAIT FOR 10 ns;
        N <= '0'; Coin <= '0';
        WAIT FOR 10 ns;
        D <= '1'; Coin <= '1';
        WAIT FOR 10 ns;
        D <= '0'; Coin <= '0';
        WAIT FOR 10 ns;
        Q <= '1'; Coin <= '1';
        WAIT FOR 10 ns;
        Q <= '0'; Coin <= '0';
        WAIT;
    END PROCESS;                                          

    U1: vend PORT MAP (N, D, Q, Resetn, Coin, Z);
END;
