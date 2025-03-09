library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity my_ckt_f3 is
    Port (
        L, M, N : in  std_logic;
        F3      : out std_logic
    );
end my_ckt_f3;

architecture f3_2 of my_ckt_f3 is
begin
    -- Implement the logic equation with explicit parentheses
    F3 <= ((NOT L) AND (NOT M) AND N) OR (L AND M);
end f3_2;
