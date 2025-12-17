library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- ============================================================
-- CLB: Configurable Logic Block
-- FPGA-style CLB inspired by 74HC-based schematic
-- ============================================================

entity clb is
  port (
    -- External inputs
    in0     : in  std_logic;
    in1     : in  std_logic;
    in2     : in  std_logic;
    in3     : in  std_logic;

    -- Clocking
    clk     : in  std_logic;
    ce      : in  std_logic;

    -- Input select (74HC153 equivalent)
    sel0    : in  std_logic;
    sel1    : in  std_logic;

    -- Output select (74HC157 equivalent)
    regsel  : in  std_logic;  -- 0 = combinational, 1 = registered

    -- CLB output
    clb_out : out std_logic
  );
end entity clb;

-- ============================================================
-- RTL Architecture
-- ============================================================

architecture rtl of clb is

  -- Internal signals
  signal sel      : std_logic_vector(1 downto 0);
  signal lut_in   : std_logic;
  signal lut_out  : std_logic;
  signal reg_out  : std_logic;
  signal mux_out  : std_logic;

begin

  ----------------------------------------------------------------
  -- Input select vector (fixes GHDL overload issue)
  ----------------------------------------------------------------
  sel <= sel1 & sel0;

  ----------------------------------------------------------------
  -- Input MUX (74HC153 equivalent)
  ----------------------------------------------------------------
  with sel select
    lut_in <= in0 when "00",
              in1 when "01",
              in2 when "10",
              in3 when "11",
              '0' when others;

  ----------------------------------------------------------------
  -- LUT Logic (example combinational function)
  -- Replace this with any logic you want
  -- Example: (A XOR B) OR C
  ----------------------------------------------------------------
  lut_out <= (lut_in xor in1) or in2;

  ----------------------------------------------------------------
  -- D Flip-Flop (behavioral equivalent of NOR-based FF)
  -- Enabled clocked storage
  ----------------------------------------------------------------
  process(clk)
  begin
    if rising_edge(clk) then
      if ce = '1' then
        reg_out <= lut_out;
      end if;
    end if;
  end process;

  ----------------------------------------------------------------
  -- Output MUX (74HC157 equivalent)
  ----------------------------------------------------------------
  mux_out <= lut_out when regsel = '0' else reg_out;

  ----------------------------------------------------------------
  -- Output buffer (74HC125 / 74HC243 equivalent)
  ----------------------------------------------------------------
  clb_out <= mux_out;

end architecture rtl;

