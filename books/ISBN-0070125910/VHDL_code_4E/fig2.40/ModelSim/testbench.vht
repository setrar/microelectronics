ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT example2
      PORT ( x1, x2, x3, x4 : IN  BIT ;
             f, g           : OUT BIT ) ;
   END COMPONENT;

   SIGNAL x1, x2, x3, x4, f, g : BIT;
BEGIN
   vectors: PROCESS           
	BEGIN
      x1 <= '0'; x2 <= '0'; x3 <= '0'; x4 <= '0';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '1'; x3 <= '0'; x4 <= '0';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '1'; x3 <= '1'; x4 <= '0';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '1'; x3 <= '0'; x4 <= '1';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '0'; x3 <= '0'; x4 <= '1';
		WAIT;
   END PROCESS;                                          

   U1: example2 PORT MAP ( x1, x2, x3, x4, f, g ) ;
END;
