LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT proc
    PORT ( Data      : IN     STD_LOGIC_VECTOR(7 DOWNTO 0) ;
           Reset, w  : IN     STD_LOGIC ;
           Clock     : IN     STD_LOGIC ;
           F, Rx, Ry : IN     STD_LOGIC_VECTOR(1 DOWNTO 0) ;
           Done      : BUFFER STD_LOGIC ;
           BusWires  : INOUT  STD_LOGIC_VECTOR(7 DOWNTO 0) ) ;
   END COMPONENT ;
   SIGNAL Reset, w, Clock, Done : STD_LOGIC;
   SIGNAL Data, BusWires : STD_LOGIC_VECTOR(7 DOWNTO 0);
   SIGNAL F, Rx, Ry : STD_LOGIC_VECTOR(1 DOWNTO 0);
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
        Reset <= '1'; Data <= X"00"; 
        w <= '0'; F <= "00"; Rx <= "00"; Ry <= "00";
        WAIT FOR 11 ns;
        Reset <= '0';
        WAIT FOR 20 ns;
        w <= '1'; Data <= X"2A";
        WAIT FOR 20 ns;
        w <= '0';
        WAIT FOR 20 ns;
        w <= '1'; Data <= X"55"; Rx <= "01";
        WAIT FOR 20 ns;
        w <= '0';
        WAIT FOR 20 ns;
        w <= '1'; Data <= X"22"; Rx <= "10";
        WAIT FOR 20 ns;
        w <= '0';
        WAIT FOR 20 ns;
        w <= '1'; Data <= X"00"; F <= "10"; Rx <= "01";
        WAIT FOR 20 ns;
        w <= '0'; F <= "00";
        WAIT FOR 60 ns;
        w <= '1'; F <= "01"; Rx <= "11"; Ry <= "01";
        WAIT FOR 20 ns;
        w <= '0';
        WAIT FOR 20 ns;
        w <= '1'; F <= "11"; Rx <= "11"; Ry <= "10";
        WAIT FOR 20 ns;
        w <= '0';
        WAIT;
   END PROCESS;                                          

   U1: proc PORT MAP (Data, Reset, w, Clock, F, Rx, Ry, Done, BusWires);
END;
