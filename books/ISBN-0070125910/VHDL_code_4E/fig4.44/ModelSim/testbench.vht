LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT alu
      PORT ( s    : IN  STD_LOGIC_VECTOR(2 DOWNTO 0) ;
             A, B : IN  STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    F    : OUT STD_LOGIC_VECTOR(3 DOWNTO 0) ) ;
   END COMPONENT;

   SIGNAL s : STD_LOGIC_VECTOR(2 DOWNTO 0);
   SIGNAL A, B, F : STD_LOGIC_VECTOR(3 DOWNTO 0);
BEGIN
   vectors: PROCESS           
	BEGIN
      s <= "000"; A <= X"5"; B <= X"A";
      WAIT FOR 10 ns;
      s <= "001";
      WAIT FOR 10 ns;
      s <= "010";
      WAIT FOR 10 ns;
      s <= "011";
      WAIT FOR 10 ns;
      s <= "100";
      WAIT FOR 10 ns;
      s <= "101";
      WAIT FOR 10 ns;
      s <= "110";
      WAIT FOR 10 ns;
      s <= "111";
		WAIT;
   END PROCESS;                                          

   U1: alu PORT MAP (s, A, B, F);
END;
