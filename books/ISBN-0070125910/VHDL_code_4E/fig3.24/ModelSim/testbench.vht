LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT adder16
      PORT ( Cin            : IN  STD_LOGIC ;
             X, Y           : IN 	STD_LOGIC_VECTOR(15 DOWNTO 0) ;
			    S 	          : OUT	STD_LOGIC_VECTOR(15 DOWNTO 0) ;
             Cout, Overflow : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL Cin, Cout, Overflow : STD_LOGIC ;
   SIGNAL X, Y, S : STD_LOGIC_VECTOR(15 DOWNTO 0);
BEGIN
   vectors: PROCESS           
	BEGIN
      Cin <= '0';
      X <= X"0000"; Y <= X"0000"; 
      WAIT FOR 20 ns;
      X <= X"0101"; Y <= X"0000"; 
      WAIT FOR 20 ns;
      Y <= X"1010"; 
      WAIT FOR 20 ns;
      X <= X"5555"; Y <= X"0000"; 
      WAIT FOR 20 ns;
      Y <= X"AAAA"; 
      WAIT FOR 20 ns;
      Cin <= '1';
      WAIT FOR 20 ns;
      Cin <= '0';
      X <= X"7FFE"; Y <= X"0001"; 
      WAIT FOR 20 ns;
      Cin <= '1';
      WAIT FOR 20 ns;
      Cin <= '1';
      X <= X"8000"; Y <= X"FFFF"; 
      WAIT FOR 20 ns;
      Cin <= '0';
		WAIT;
   END PROCESS;                                          

   U1: adder16 PORT MAP (Cin, X, Y, S, Cout, Overflow);
END;
