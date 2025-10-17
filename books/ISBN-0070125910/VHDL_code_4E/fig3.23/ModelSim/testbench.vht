LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT adder16
      PORT ( X, Y : IN 	STD_LOGIC_VECTOR(15 DOWNTO 0) ;
			    S 	: OUT	STD_LOGIC_VECTOR(15 DOWNTO 0) ) ;
   END COMPONENT;

   SIGNAL X, Y, S : STD_LOGIC_VECTOR(15 DOWNTO 0);
BEGIN
   vectors: PROCESS           
	BEGIN
      X <= X"0000"; Y <= X"0000"; 
      WAIT FOR 20 ns;
      X <= X"0101"; Y <= X"0000"; 
      WAIT FOR 20 ns;
      Y <= X"1010"; 
      WAIT FOR 20 ns;
      X <= X"5555"; Y <= X"0000"; 
      WAIT FOR 20 ns;
      Y <= X"AAAA"; 
		WAIT;
   END PROCESS;                                          

   U1: adder16 PORT MAP (X, Y, S);
END;
