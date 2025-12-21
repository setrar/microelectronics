LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT mux4to1
      PORT ( s : IN  STD_LOGIC_VECTOR(1 DOWNTO 0) ;
             w : IN  STD_LOGIC_VECTOR(3 DOWNTO 0) ;
			    f : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL s : STD_LOGIC_VECTOR(1 DOWNTO 0);
   SIGNAL w : STD_LOGIC_VECTOR(3 DOWNTO 0);
   SIGNAL f : STD_LOGIC;
BEGIN
   vectors: PROCESS           
	BEGIN
      w <= "0101"; s <= "00";
      WAIT FOR 20 ns;
      s <= "01";
      WAIT FOR 20 ns;
      s <= "10";
      WAIT FOR 20 ns;
      s <= "11";
      WAIT FOR 20 ns;
      w <= "1010";
      WAIT FOR 20 ns;
      s <= "10";
      WAIT FOR 20 ns;
      s <= "01";
      WAIT FOR 20 ns;
      w <= "0011"; s <= "00";
      WAIT FOR 20 ns;
      s <= "01";
      WAIT FOR 20 ns;
      s <= "10";
      WAIT FOR 20 ns;
      s <= "11";
		WAIT;
   END PROCESS;                                          

   U1: mux4to1 PORT MAP (s, w, f);
END;
