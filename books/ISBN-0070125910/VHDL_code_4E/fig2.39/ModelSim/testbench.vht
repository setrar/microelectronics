ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT example1
      PORT ( x1, x2, s : IN  BIT ;
             f         : OUT BIT ) ;
   END COMPONENT;

   SIGNAL x1, x2, s, f : BIT;
BEGIN
   vectors: PROCESS           
	BEGIN
      x1 <= '0'; x2 <= '0'; s <= '0';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '0'; s <= '0';
      WAIT FOR 20 ns;
      x1 <= '0'; x2 <= '1'; s <= '0';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '1'; s <= '0';
      WAIT FOR 20 ns;
      x1 <= '0'; x2 <= '0'; s <= '1';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '0'; s <= '1';
      WAIT FOR 20 ns;
      x1 <= '0'; x2 <= '1'; s <= '1';
      WAIT FOR 20 ns;
      x1 <= '1'; x2 <= '1'; s <= '1';
		WAIT;
   END PROCESS;                                          

   U1: example1 PORT MAP (x1, x2, s, f);
END;
