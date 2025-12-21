LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY testbench IS
END testbench;

ARCHITECTURE Behavior OF testbench IS
   COMPONENT rege
       PORT ( R, Resetn, E, Clock : IN     STD_LOGIC ;
              Q                   : BUFFER STD_LOGIC ) ;
   END COMPONENT ;
   SIGNAL R, Resetn, E, Clock, Q : STD_LOGIC ;
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
        Resetn <= '0'; E <= '0'; R <= '1';
        WAIT FOR 20 ns;
        Resetn <= '1'; E <= '1';
        WAIT;
   END PROCESS;                                          

   U1: rege PORT MAP (R, Resetn, E, Clock, Q);
END;
