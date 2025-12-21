LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT compare
      PORT ( A, B  				: IN 	STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    AeqB, AgtB, AltB	: OUT	STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL A, B : STD_LOGIC_VECTOR(3 DOWNTO 0);
   SIGNAL AeqB, AgtB, AltB	: STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      A <= X"0"; B <= X"0";
      WAIT FOR 10 ns;
      A <= X"1"; B <= X"0";
      WAIT FOR 10 ns;
      A <= X"0"; B <= X"2";
      WAIT FOR 10 ns;
      A <= X"8"; B <= X"0";
      WAIT FOR 10 ns;
      A <= X"0"; B <= X"9";
      WAIT FOR 10 ns;
      A <= X"F"; B <= X"9";
      WAIT FOR 10 ns;
      A <= X"9"; B <= X"F";
      WAIT FOR 10 ns;
      A <= X"F"; B <= X"F";
		WAIT;
   END PROCESS;                                          

   U1: compare PORT MAP (A, B, AeqB, AgtB, AltB);
END;
