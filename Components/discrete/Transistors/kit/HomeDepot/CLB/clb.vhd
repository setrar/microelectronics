library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- ============================================================
-- CLB: FPGA-Style Configurable Logic Block
-- Fully aligned with architecture diagram
-- ============================================================

entity clb is
  port (
    -- External inputs
    in0     : in  std_logic;
    in1     : in  std_logic;
    in2     : in  std_logic;
    in3     : in  std_logic;

    -- Feedback input (from routing fabric)
    fb      : in  std_logic;

    -- Clocking
    clk     : in  std_logic;
    ce      : in  std_logic;

    -- Input select
    sel0    : in  std_logic;
    sel1    : in  std_logic;

    -- Output select
    regsel  : in  std_logic;  -- 0 = combinational, 1 = registered

    -- LUT configuration bits (SRAM model)
    lut_mem : in  std_logic_vector(3 downto 0);

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
  -- Input select vector
  ----------------------------------------------------------------
  sel <= sel1 & sel0;

  ----------------------------------------------------------------
  -- Input MUX (5 inputs modeled as 4 + feedback via fabric)
  -- 74HC153 equivalent abstraction
  ----------------------------------------------------------------
  with sel select
    lut_in <= in0 when "00",
              in1 when "01",
              in2 when "10",
              fb  when "11",
              '0' when others;

  ----------------------------------------------------------------
  -- True MUX-Based LUT (2-input LUT, SRAM-configured)
  -- This is FPGA-realistic
  ----------------------------------------------------------------
  with sel select
    lut_out <= lut_mem(0) when "00",
               lut_mem(1) when "01",
               lut_mem(2) when "10",
               lut_mem(3) when "11",
               '0'        when others;

  ----------------------------------------------------------------
  -- D Flip-Flop with Clock Enable
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
  -- Output buffer (tri-state abstracted)
  ----------------------------------------------------------------
  clb_out <= mux_out;

end architecture rtl;

