LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT addersubtractor
        GENERIC ( n : INTEGER := 16 ) ;
        PORT (	A, B 	: IN STD_LOGIC_VECTOR(n-1 DOWNTO 0) ;
				   Clock, Reset, Sel, AddSub : IN STD_LOGIC ;
				   Z 	: BUFFER	STD_LOGIC_VECTOR(n-1 DOWNTO 0) ;
				Overflow	: OUT STD_LOGIC ) ;
   END COMPONENT ;
   SIGNAL Clock, Reset, Sel, AddSub : STD_LOGIC;
   SIGNAL A, B, Z : STD_LOGIC_VECTOR(15 DOWNTO 0);
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
        Reset <= '1'; A <= X"0000"; B <= X"0000"; Sel <= '0'; AddSub <= '0';
        WAIT FOR 11 ns;
        Reset <= '0';
        WAIT FOR 20 ns;
        A <= X"0008"; B <= X"0004";
        WAIT FOR 20 ns;
        Sel <= '1';
        WAIT FOR 160 ns;
        AddSub <= '1';
        WAIT;
   END PROCESS;                                          

   U1: addersubtractor PORT MAP (A, B, Clock, Reset, Sel, AddSub, Z);
END;
