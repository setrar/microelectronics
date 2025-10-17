LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT BCD
      PORT ( X, Y	: IN 	STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    S 	: OUT	STD_LOGIC_VECTOR(4 DOWNTO 0) ) ;
   END COMPONENT;

   SIGNAL X, Y : STD_LOGIC_VECTOR(3 DOWNTO 0);
   SIGNAL S : STD_LOGIC_VECTOR(4 DOWNTO 0);
BEGIN
   vectors: PROCESS           
	BEGIN
      X <= X"0"; Y <= X"0"; 
      WAIT FOR 20 ns;
      X <= X"1"; Y <= X"8"; 
      WAIT FOR 20 ns;
      Y <= X"9"; 
      WAIT FOR 20 ns;
      X <= X"2";
      WAIT FOR 20 ns;
      X <= X"8";
		WAIT;
   END PROCESS;                                          

   U1: BCD PORT MAP (X, Y, S);
END;
