LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
    COMPONENT reaction IS
        PORT ( Clock, c9, Reset : IN STD_LOGIC ;
               w, Pushn         : IN STD_LOGIC ;
               LEDn             : OUT STD_LOGIC ;
               Digit1, Digit0   : BUFFER STD_LOGIC_VECTOR(1 TO 7) ) ;
    END COMPONENT ;
    SIGNAL Clock, c9, Reset, w, Pushn, LEDn : STD_LOGIC ;
    SIGNAL Digit1, Digit0 : STD_LOGIC_VECTOR(1 TO 7) ;
BEGIN
   -- High-speed Clock (arbitrarily) set to 100 KHz
   clock_process: PROCESS
	BEGIN
	   Clock <= '0';
	   WAIT FOR 5 us ;
	   Clock <= '1';
	   WAIT FOR 5 us ;
	END PROCESS;

   -- c9 set to 1000 times lower rate than Clock
   c9_process: PROCESS
	BEGIN
	   c9 <= '0';
	   WAIT FOR 5 ms;
	   c9 <= '1';
	   WAIT FOR 5 ms;
	END PROCESS;

   vectors: PROCESS           
	BEGIN
      Reset <= '1'; Pushn <= '0'; w <= '0';
      WAIT FOR 10 ms;
      Reset <= '0'; Pushn <= '1';
      WAIT FOR 20 ms;
      w <= '1';
      WAIT FOR 10 ms;
      w <= '0';
      WAIT FOR 150 ms;
      Pushn <= '0';
		WAIT;
   END PROCESS;                                          

   U1: reaction PORT MAP (Clock, c9, Reset, w, Pushn, LEDn, Digit1, Digit0);
END;
