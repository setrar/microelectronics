# Listing 3.2

<img src=Listing_3.2.png width='' height='' > </img>

### ✅ Step-by-Step GHDL Flow

#### 1. **Analyze the file**
This part you've done correctly:

```bash
ghdl analyse --std=08 Listing_3.2.vhd
```

(or the short version: `ghdl -a --std=08 Listing_3.2.vhd`)

---

#### 2. **Elaborate the top-level entity**

```bash
ghdl elaborate --std=08 killer_ckt
```

(or short: `ghdl -e --std=08 killer_ckt`)

> This builds the executable for your design (kind of like compiling a `main()` in C).

---

#### 3. **Run the simulation**

```bash
ghdl run --std=08 killer_ckt --vcd=killer_ckt.vcd
```

This runs the elaborated design and optionally dumps VCD waveforms for viewing in GTKWave.

---

### 🧪 But Wait... You Need a Testbench!

Your current `killer_ckt` entity **has no stimulus**. You need a **testbench** to actually do something meaningful in simulation.

Here's a **minimal example**:

```vhdl
-- testbench_killer.vhd
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_killer is
end tb_killer;

architecture test of tb_killer is
    signal life_in1, life_in2, ctrl_a, ctrl_b : std_logic := '0';
    signal kill_a, kill_b, kill_c : std_logic;

    component killer_ckt
        Port (
            life_in1, life_in2, ctrl_a, ctrl_b : in  std_logic;
            kill_a, kill_b, kill_c : out std_logic
        );
    end component;

begin
    UUT: killer_ckt
        port map (
            life_in1 => life_in1,
            life_in2 => life_in2,
            ctrl_a   => ctrl_a,
            ctrl_b   => ctrl_b,
            kill_a   => kill_a,
            kill_b   => kill_b,
            kill_c   => kill_c
        );

    stimulus: process
    begin
        life_in1 <= '1'; ctrl_a <= '1'; ctrl_b <= '0';
        wait for 10 ns;
        life_in2 <= '1';
        wait for 10 ns;
        ctrl_a <= '0'; ctrl_b <= '1';
        wait for 10 ns;
        -- add more test patterns here

        wait;
    end process;
end test;
```

Then compile and run:

```bash
ghdl -a --std=08 Listing_3.2.vhd
ghdl -a --std=08 testbench_killer.vhd
ghdl -e --std=08 tb_killer
ghdl -r --std=08 tb_killer --vcd=wave.vcd
gtkwave wave.vcd
```

