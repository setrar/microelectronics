LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS

   COMPONENT mux4to1
      PORT ( w0, w1, w2, w3 : IN  STD_LOGIC ;
             s              : IN  STD_LOGIC_VECTOR(1 DOWNTO 0) ;
			    f			       : OUT STD_LOGIC ) ;
   END COMPONENT;

   SIGNAL w0, w1, w2, w3, f : STD_LOGIC;
   SIGNAL s : STD_LOGIC_VECTOR(1 DOWNTO 0);
BEGIN
   vectors: PROCESS           
	BEGIN
      w0 <= '0'; w1 <= '1'; w2 <= '0'; w3 <= '1'; s <= "00";
      WAIT FOR 20 ns;
      s <= "01";
      WAIT FOR 20 ns;
      s <= "10";
      WAIT FOR 20 ns;
      s <= "11";
      WAIT FOR 20 ns;
      w0 <= '1'; w1 <= '0'; w2 <= '1'; w3 <= '0';
      WAIT FOR 20 ns;
      s <= "10";
      WAIT FOR 20 ns;
      s <= "01";
      WAIT FOR 20 ns;
      s <= "00";
		WAIT;
   END PROCESS;                                          

   U1: mux4to1 PORT MAP (w0, w1, w2, w3, s, f);
END;
