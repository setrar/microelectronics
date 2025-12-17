library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_clb is
end entity;

architecture sim of tb_clb is

  -- DUT signals
  signal in0, in1, in2, in3 : std_logic := '0';
  signal fb                : std_logic := '0';
  signal clk               : std_logic := '0';
  signal ce                : std_logic := '0';
  signal sel0, sel1         : std_logic := '0';
  signal regsel             : std_logic := '0';
  signal lut_mem            : std_logic_vector(3 downto 0) := (others => '0');
  signal clb_out            : std_logic;

  constant CLK_PERIOD : time := 10 ns;

begin

  ----------------------------------------------------------------
  -- DUT Instantiation
  ----------------------------------------------------------------
  uut : entity work.clb
    port map (
      in0     => in0,
      in1     => in1,
      in2     => in2,
      in3     => in3,
      fb      => fb,
      clk     => clk,
      ce      => ce,
      sel0    => sel0,
      sel1    => sel1,
      regsel  => regsel,
      lut_mem => lut_mem,
      clb_out => clb_out
    );

  ----------------------------------------------------------------
  -- Clock Generator
  ----------------------------------------------------------------
  clk_process : process
  begin
    while true loop
      clk <= '0';
      wait for CLK_PERIOD / 2;
      clk <= '1';
      wait for CLK_PERIOD / 2;
    end loop;
  end process;

  ----------------------------------------------------------------
  -- Stimulus
  ----------------------------------------------------------------
  stim : process
  begin
    ----------------------------------------------------------------
    -- Program LUT: XOR truth table
    -- sel = "00" -> 0
    -- sel = "01" -> 1
    -- sel = "10" -> 1
    -- sel = "11" -> 0
    ----------------------------------------------------------------
    lut_mem <= "0110";

    ce <= '1';
    regsel <= '0';  -- combinational path

    -- Drive inputs
    in0 <= '0';
    in1 <= '1';
    in2 <= '0';
    in3 <= '1';
    fb  <= '0';

    -- Sweep LUT select
    sel1 <= '0'; sel0 <= '0'; wait for 20 ns;
    sel1 <= '0'; sel0 <= '1'; wait for 20 ns;
    sel1 <= '1'; sel0 <= '0'; wait for 20 ns;
    sel1 <= '1'; sel0 <= '1'; wait for 20 ns;

    ----------------------------------------------------------------
    -- Enable registered path
    ----------------------------------------------------------------
    regsel <= '1';

    sel1 <= '0'; sel0 <= '0'; wait for 20 ns;
    sel1 <= '0'; sel0 <= '1'; wait for 20 ns;
    sel1 <= '1'; sel0 <= '0'; wait for 20 ns;
    sel1 <= '1'; sel0 <= '1'; wait for 20 ns;

    ----------------------------------------------------------------
    -- Feedback test
    ----------------------------------------------------------------
    fb <= clb_out;
    sel1 <= '1'; sel0 <= '1';
    wait for 40 ns;

    ----------------------------------------------------------------
    -- End simulation
    ----------------------------------------------------------------
    wait;
  end process;

end architecture sim;

