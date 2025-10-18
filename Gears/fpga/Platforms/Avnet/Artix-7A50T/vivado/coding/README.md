# Coding

---

[TOC]

---

## Coding on the `A750T` board

To perform the entire process using only the command line, we can leverage the Xilinx Vivado toolchain, specifically using `vivado` and `quartus` commands. Below is a step-by-step guide on how to write a simple VHDL example and deploy it to the A750T FPGA via the command line.

### Assumptions:
- You have **Vivado** installed and added to your PATH.
- You have a **A750T board** (or equivalent hardware) ready for programming.
- You have basic knowledge of Vivado tools and file paths.

### Step 1: Set Up Your Environment

First, open a terminal and set up the Vivado environment:
```bash
source ${VIVADO_HOME}/settings64.sh
```
Replace `/path/to/Vivado/202X.X/` with the actual path to your Vivado installation.

```bash
export VIVADO_HOME=/tools/Xilinx/Vivado/2024.2
```

### Step 2: Create a Project Directory
Create a directory where you will store your VHDL project.
```bash
mkdir my_vhdl_project
cd my_vhdl_project
```

### Step 3: Write the VHDL Code (2-bit Counter)
Create a VHDL file called `counter.vhdl` with the simple counter logic.

#### `counter.vhdl`:
```vhdl
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity counter is
    Port ( clk   : in  STD_LOGIC;
           rst   : in  STD_LOGIC;
           count : out STD_LOGIC_VECTOR(1 downto 0));
end counter;

architecture Behavioral of counter is
    signal count_reg : STD_LOGIC_VECTOR(1 downto 0) := "00";
begin
    process(clk, rst)
    begin
        if rst = '1' then
            count_reg <= "00";
        elsif rising_edge(clk) then
            count_reg <= count_reg + 1;
        end if;
    end process;

    count <= count_reg;
end Behavioral;
```

### Step 4: Write the Constraints File (XDC)
Next, create a constraints file `constraints.xdc` that defines the pin mappings for the ZCU670. You need to find the correct pin numbers for your design, but here is an example:

#### `constraints.xdc`:
```xdc
# Clock pin
set_property PACKAGE_PIN E3 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]

# Reset pin example (you must customize this if you use it)
set_property PACKAGE_PIN H15 [get_ports rst]
set_property IOSTANDARD LVCMOS33 [get_ports rst]

# Configuration voltage (required for bitstream generation)
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]
[bricer@kalogria my_vhdl_project]$ cat constraints.xdc 
# Clock pin
set_property PACKAGE_PIN E3 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports clk]

# Reset pin example (you must customize this if you use it)
set_property PACKAGE_PIN H15 [get_ports rst]
set_property IOSTANDARD LVCMOS33 [get_ports rst]

# Configuration voltage (required for bitstream generation)
set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]
```

### Step 5: Create a Vivado Project via Command Line
Create a new Vivado project using the command line. Replace `xc7a50tcsg324-1` with the appropriate part for your A750T.


```bash
vivado -mode batch -source create_project.tcl
```

Create a TCL script (`create_project.tcl`) to set up the project. Here's an example of `create_project.tcl`:

#### `create_project.tcl`:
```tcl
# Create a new Vivado project
create_project my_vhdl_project ./my_vhdl_project -part xc7a50tcsg324-1

# Add VHDL source files
add_files ./counter.vhdl

# Add constraints file
add_files ./constraints.xdc

# Set the top module
set_property top counter [current_fileset]

# Run synthesis
launch_runs synth_1
wait_on_run synth_1

# Run implementation
launch_runs impl_1
wait_on_run impl_1

# Generate bitstream
launch_runs impl_1 -to_step write_bitstream
wait_on_run impl_1
```

Run this TCL script in Vivado:
```bash
vivado -mode batch -source create_project.tcl
```

This will:
1. Create the Vivado project.
2. Add the `counter.vhdl` and `constraints.xdc` files.
3. Set the top module.
4. Run synthesis, implementation, and bitstream generation.

### Step 6: Program the FPGA via Command Line
Once the bitstream (`.bit` file) is generated, you can program the FPGA via the Vivado hardware manager.

Use the following command to program the ZCU670. Replace `/path/to/bitstream.bit` with the actual path to your `.bit` file.

```bash
vivado -mode batch -source program_fpga.tcl
```

Here’s an example of the `program_fpga.tcl` script:

#### `program_fpga.tcl`:
```tcl
# Open hardware manager and connect to the FPGA
open_hw

# Connect to the target device (ensure that your board is connected)
connect_hw_server
open_hw_target

# Program the FPGA with the generated bitstream file
program_hw_devices [get_hw_devices xczu19eg_0] -bitstream_file ./my_vhdl_project.runs/impl_1/top.bit

# Close hardware manager
close_hw
```

Run the script:
```bash
vivado -mode batch -source program_fpga.tcl
```

### Step 7: Verify Operation
Once the FPGA is programmed, you can verify the 2-bit counter's output on the physical board. You might connect the output signals (`count[0]` and `count[1]`) to LEDs or use an oscilloscope to verify the counter functionality.

### Summary of Command Line Steps:
1. **Create Project**: `vivado -mode batch -source create_project.tcl`
2. **Program FPGA**: `vivado -mode batch -source program_fpga.tcl`

This process covers the full flow, from writing the VHDL code to programming the ZCU670 FPGA using only command-line tools in Vivado.

# References

- [ ] [A huge VHDL library for FPGA development ](https://github.com/slaclab/surf)
