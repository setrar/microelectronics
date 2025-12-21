LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT shift4
       PORT ( R     : IN     STD_LOGIC_VECTOR(3 DOWNTO 0);
              Clock : IN     STD_LOGIC ;
              L, w  : IN     STD_LOGIC ;
              Q     : BUFFER STD_LOGIC_VECTOR(3 DOWNTO 0) );
   END COMPONENT ;
   SIGNAL L, w, Clock : STD_LOGIC;
   SIGNAL R, Q : STD_LOGIC_VECTOR(3 DOWNTO 0);
BEGIN
   clock_process: PROCESS
	BEGIN
	   Clock <= '0';
	   WAIT FOR 10 ns;
	   Clock <= '1';
	   WAIT FOR 10 ns;
	END PROCESS;

   vectors: PROCESS           
	BEGIN
      L <= '1'; w <= '1'; R <= "0000";
      WAIT FOR 20 ns;
      L <= '0';
      WAIT FOR 20 ns;
      WAIT FOR 20 ns;
      WAIT FOR 20 ns;
      WAIT FOR 20 ns;
      L <= '1';
		WAIT;
   END PROCESS;                                          

   U1: shift4 PORT MAP (R, Clock, L, w, Q);
END;
