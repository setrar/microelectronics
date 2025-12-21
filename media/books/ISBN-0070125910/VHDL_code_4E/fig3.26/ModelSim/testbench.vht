ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT adder16
      PORT ( X, Y : IN 	INTEGER RANGE -32768 TO 32767 ;
			    S 	: OUT	INTEGER RANGE -65536 TO 65535 ) ;
   END COMPONENT;

   SIGNAL X, Y : INTEGER RANGE -32768 TO 32767;
   SIGNAL S : INTEGER RANGE -65536 TO 65535;
BEGIN
   vectors: PROCESS           
	BEGIN
      X <= 0; Y <= 0; 
      WAIT FOR 20 ns;
      X <= 100;
      WAIT FOR 20 ns;
      Y <= 900;
      WAIT FOR 20 ns;
      X <= 1000;
      WAIT FOR 20 ns;
      Y <= 10000;
		WAIT;
   END PROCESS;                                          

   U1: adder16 PORT MAP (X, Y, S);
END;
