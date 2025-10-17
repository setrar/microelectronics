LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY seg7 IS
    PORT ( hex  : IN  STD_LOGIC_VECTOR(3 DOWNTO 0) ;
           leds : OUT STD_LOGIC_VECTOR(1 TO 7) ) ;
END seg7 ;

ARCHITECTURE Behavior OF seg7 IS    
BEGIN
    PROCESS ( hex )
    BEGIN
        CASE hex IS             --  abcdefg
            WHEN "0000" => leds <= "1111110" ;
            WHEN "0001" => leds <= "0110000" ;
            WHEN "0010" => leds <= "1101101" ;
            WHEN "0011" => leds <= "1111001" ;
            WHEN "0100" => leds <= "0110011" ;
            WHEN "0101" => leds <= "1011011" ;
            WHEN "0110" => leds <= "1011111" ;
            WHEN "0111" => leds <= "1110000" ;
            WHEN "1000" => leds <= "1111111" ;
            WHEN "1001" => leds <= "1111011" ;
            WHEN "1010" => leds <= "1110111" ;
            WHEN "1011" => leds <= "0011111" ;
            WHEN "1100" => leds <= "1001110" ;
            WHEN "1101" => leds <= "0111101" ;
            WHEN "1110" => leds <= "1001111" ;
            WHEN OTHERS => leds <= "1000111" ;
        END CASE ;
    END PROCESS ;
END Behavior ;
