LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT comparator
      PORT ( X, Y    : IN STD_LOGIC_VECTOR(3 DOWNTO 0) ;
		       V, N, Z : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL X, Y : STD_LOGIC_VECTOR(3 DOWNTO 0);
   SIGNAL V, N, Z : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      X <= X"0"; Y <= X"0";
      WAIT FOR 20 ns;
      X <= X"F"; Y <= X"F";
      WAIT FOR 20 ns;
      X <= X"0"; Y <= X"F";
      WAIT FOR 20 ns;
      X <= X"F"; Y <= X"0";
      WAIT FOR 20 ns;
      X <= X"7"; Y <= X"0";
      WAIT FOR 20 ns;
      X <= X"0"; Y <= X"7";
      WAIT FOR 20 ns;
      X <= X"7"; Y <= X"8";
      WAIT FOR 20 ns;
      X <= X"8"; Y <= X"7";
		WAIT;
   END PROCESS;                                          

   U1: comparator PORT MAP (X, Y, V, N, Z);
END;
