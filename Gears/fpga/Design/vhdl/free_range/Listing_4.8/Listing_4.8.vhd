library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity my_ckt_f3 is
    Port (
        L, M, N : in  std_logic;
        F3      : out std_logic
    );
end my_ckt_f3;

architecture f3_2 of my_ckt_f3 is
    signal A1, A2 : std_logic;
begin
    -- Implement the intermediate signals
    A1 <= (NOT L) AND (NOT M) AND N;
    A2 <= L AND M;

    -- Implement the final output
    F3 <= A1 OR A2;
end f3_2;
