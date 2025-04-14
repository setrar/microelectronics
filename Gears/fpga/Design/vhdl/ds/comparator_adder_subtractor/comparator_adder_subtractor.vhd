library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity comparator_adder_subtractor is
    Port (
        a : in  STD_LOGIC_VECTOR (7 downto 0);
        b : in  STD_LOGIC_VECTOR (7 downto 0);
        s : out STD_LOGIC_VECTOR (8 downto 0)
    );
end comparator_adder_subtractor;

architecture Behavioral of comparator_adder_subtractor is
    signal a_signed, b_signed : signed(7 downto 0);
    signal s_signed : signed(8 downto 0);
begin
    process(a, b)
    begin
        -- Initialize the signals to avoid meta-values
        a_signed <= signed(a);
        b_signed <= signed(b);

        if (unsigned(a) > unsigned(b)) then
            s_signed <= resize(a_signed, 9) - resize(b_signed, 9);
        else
            s_signed <= resize(a_signed, 9) + resize(b_signed, 9);
        end if;
        
        s <= std_logic_vector(s_signed);
    end process;
end Behavioral;

