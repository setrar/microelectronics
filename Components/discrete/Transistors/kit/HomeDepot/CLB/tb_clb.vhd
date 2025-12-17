library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity tb_clb is
end entity;

architecture sim of tb_clb is

  -- DUT signals
  signal in0     : std_logic := '0';
  signal in1     : std_logic := '0';
  signal in2     : std_logic := '0';
  signal in3     : std_logic := '0';

  signal clk     : std_logic := '0';
  signal ce      : std_logic := '0';

  signal sel0    : std_logic := '0';
  signal sel1    : std_logic := '0';
  signal regsel  : std_logic := '0';

  signal clb_out : std_logic;

  constant CLK_PERIOD : time := 10 ns;

begin

  ----------------------------------------------------------------
  -- Instantiate DUT
  ----------------------------------------------------------------
  uut: entity work.clb
    port map (
      in0     => in0,
      in1     => in1,
      in2     => in2,
      in3     => in3,
      clk     => clk,
      ce      => ce,
      sel0    => sel0,
      sel1    => sel1,
      regsel  => regsel,
      clb_out => clb_out
    );

  ----------------------------------------------------------------
  -- Clock generator
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
  -- Stimulus process
  ----------------------------------------------------------------
  stim_proc : process
  begin
    --------------------------------------------------------------
    -- Initial state
    --------------------------------------------------------------
    ce     <= '0';
    regsel <= '0';
    sel1   <= '0';
    sel0   <= '0';

    in0 <= '0';
    in1 <= '0';
    in2 <= '0';
    in3 <= '0';

    wait for 20 ns;

    --------------------------------------------------------------
    -- Combinational mode
    --------------------------------------------------------------
    regsel <= '0';   -- combinational
    ce     <= '1';

    in0 <= '1';
    in1 <= '0';
    in2 <= '0';
    in3 <= '0';
    wait for 20 ns;

    sel0 <= '1';     -- select in1
    wait for 20 ns;

    sel1 <= '1';     -- select in3
    sel0 <= '1';
    in3  <= '1';
    wait for 20 ns;

    --------------------------------------------------------------
    -- Registered mode
    --------------------------------------------------------------
    regsel <= '1';   -- registered output
    ce     <= '1';

    sel1 <= '0';
    sel0 <= '0';
    in0  <= '0';
    in1  <= '1';
    in2  <= '1';

    wait for 30 ns;

    in1 <= '0';
    in2 <= '0';
    wait for 30 ns;

    --------------------------------------------------------------
    -- Disable clock enable
    --------------------------------------------------------------
    ce <= '0';
    in0 <= '1';
    wait for 30 ns;

    --------------------------------------------------------------
    -- End simulation
    --------------------------------------------------------------
    wait for 50 ns;
    assert false report "Simulation finished" severity failure;
  end process;

end architecture sim;

