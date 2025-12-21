LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT BCDcount
        PORT ( CountClock : IN STD_LOGIC ;
               Clear, E   : IN STD_LOGIC ;
               BCD1, BCD0 : BUFFER STD_LOGIC_VECTOR(3 DOWNTO 0) ) ;
    END COMPONENT ;
    SIGNAL CountClock, Clear, E : STD_LOGIC ;
    SIGNAL BCD1, BCD0 : STD_LOGIC_VECTOR(3 DOWNTO 0) ;
BEGIN
   clock_process: PROCESS
	BEGIN
	   CountClock <= '0';
	   WAIT FOR 10 ns;
	   CountClock <= '1';
	   WAIT FOR 10 ns;
	END PROCESS;

   vectors: PROCESS           
	BEGIN
      Clear <= '1'; E <= '0';
      WAIT FOR 20 ns;
      Clear <= '0'; E <= '1';
      WAIT FOR 80 ns;
      E <= '0';
      WAIT FOR 20 ns;
      E <= '1';
		WAIT;
   END PROCESS;                                          

   U1: BCDcount PORT MAP (CountClock, Clear, E, BCD1, BCD0);
END;
