LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT serial
        GENERIC ( length : INTEGER := 8 ) ;
        PORT ( Clock     : IN         STD_LOGIC ;
               Reset     : IN         STD_LOGIC ;
               A, B      : IN         STD_LOGIC_VECTOR(length-1 DOWNTO 0) ;
               Sum       : BUFFER     STD_LOGIC_VECTOR(length-1 DOWNTO 0) );
   END COMPONENT ;
   SIGNAL Clock, Reset : STD_LOGIC;
   SIGNAL A, B, Sum : STD_LOGIC_VECTOR(7 DOWNTO 0);
BEGIN
    clock_process: PROCESS
    BEGIN
       Clock <= '0';
       WAIT FOR 10 ns;
       Clock <= '1';
       WAIT FOR 10 ns;
    END PROCESS;

    vectors: PROCESS           
    BEGIN
        Reset <= '1'; A <= "01010101"; B <= "00000001";
        WAIT FOR 11 ns;
        Reset <= '0'; 
        WAIT;
    END PROCESS;                                          

    U1: serial PORT MAP (Clock, Reset, A, B, Sum);
END;
