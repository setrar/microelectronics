LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT latch
       PORT ( D, Clk : IN  STD_LOGIC ;
              Q      : OUT STD_LOGIC ) ;
    END COMPONENT ;
   SIGNAL D, Clk, Q : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      Clk <= '0'; D <= '0';
      WAIT FOR 10 ns;
      Clk <= '1';
      WAIT FOR 10 ns;
      Clk <= '0'; D <= '1';
      WAIT FOR 10 ns;
      Clk <= '1';
		WAIT;
   END PROCESS;                                          

   U1: latch PORT MAP (D, Clk, Q);
END;
