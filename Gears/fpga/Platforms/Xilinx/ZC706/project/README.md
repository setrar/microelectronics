# petalinux project

## 🔍 What Can You Do With an `.xsa` *Without* a Bitstream?

An `.xsa` without a bitstream still includes:

* The **Zynq PS7 configuration** (DDR, UART, Ethernet, SD, clocks, etc.)
* The **block diagram and IPI metadata**
* The **part and board information**
* The **address map and hardware interfaces**

This is **enough for software tools** like PetaLinux, Yocto, or Vitis to:

---

### ✅ You **CAN**:

| Task                                              | Why it works                                           |
| ------------------------------------------------- | ------------------------------------------------------ |
| 🟢 **Build U-Boot, FSBL, and ATF (if needed)**    | FSBL configures PS (DDR, clocks, UART) from `.xsa`     |
| 🟢 **Generate Linux device trees (`system.dts`)** | Extracts hardware mapping (UART, Ethernet, etc.)       |
| 🟢 **Build and boot Linux on PS (CPU)**           | No need for PL/FPGA unless your logic is in the fabric |
| 🟢 **Run applications on Linux (ARM A9)**         | Full PS operation with bootloaders and OS              |
| 🟢 **Use UART/USB/SD/Ethernet from PS**           | These peripherals are connected to Zynq PS, not PL     |

---

### ❌ You **CANNOT**:

| Task                                                       | Why it fails                                     |
| ---------------------------------------------------------- | ------------------------------------------------ |
| 🔴 **Configure PL (Programmable Logic) with custom logic** | No bitstream in the `.xsa` = PL is unused        |
| 🔴 **Use GPIO/AXI IPs mapped into PL**                     | PL peripherals need bitstream to be active       |
| 🔴 **Accelerate applications using custom IP blocks**      | These must be implemented and included in `.bit` |
| 🔴 **Verify IP cores, DMA, BRAM, DSP, etc.**               | PL side is empty unless synthesized/implemented  |

---

## 🧠 Think of it this way:

* `.xsa` **without bitstream** = pure **PS configuration only**
* `.xsa` **with bitstream** = PS + your **custom PL logic**

This makes a minimal `.xsa` ideal for:

* Bootstrapping embedded Linux fast
* Validating basic boot infrastructure
* Early-stage driver or system bring-up
* Hosting software development before full FPGA flow

---

## ✅ Typical Minimal `.xsa` Use Case

You want to:

1. Boot Linux on ZC706
2. Use UART, SD card, Ethernet
3. Build with Yocto or Petalinux
4. Skip long Vivado synth/impl steps

A minimal `.xsa` lets you:

* Skip Vivado licenses (no synthesis)
* Bring up the board faster
* Add bitstream later when needed

---

## ✅ Minimal TCL Script to Create a PS-Only `.xsa` for ZC706

```tcl
set proj_name "zc706_proj"
set proj_dir "./${proj_name}"
set part "xc7z045ffg900-2"

create_project $proj_name $proj_dir -part $part -force
set_property BOARD_PART xilinx.com:zc706:part0:1.4 [current_project]

create_bd_design base_design
create_bd_cell -type ip -vlnv xilinx.com:ip:processing_system7:5.5 ps7
set_property -dict [list CONFIG.PCW_USE_M_AXI_GP0 {0}] [get_bd_cells ps7]

validate_bd_design
save_bd_design

# Generate HDL, handoff, etc.
generate_target all [get_files ./zc706_proj/zc706_proj.srcs/sources_1/bd/base_design/base_design.bd]
export_ip_user_files -of_objects [get_files ./zc706_proj/zc706_proj.srcs/sources_1/bd/base_design/base_design.bd] -no_script -sync -force -quiet

# Create wrapper and add to project
make_wrapper -files [get_files ./zc706_proj/zc706_proj.srcs/sources_1/bd/base_design/base_design.bd] -top
add_files -norecurse ./zc706_proj/zc706_proj.gen/sources_1/bd/base_design/hdl/base_design_wrapper.v

set_property platform.name "zc706_minimal" [current_project]
set_property platform.board_id "zc706" [current_project]

# Build wrapper and generate XSA
update_compile_order -fileset sources_1

# launch_runs synth_1 -jobs 4
# wait_on_run synth_1
# write_hw_platform -fixed -force -include_bit -file ./zc706_minimal.xsa

write_hw_platform -fixed -force -file ./zc706_minimal.xsa
```

---

## ✅ Run it:

```bash
vivado -mode batch -source create_project.tcl
```

---

## ✅ What You Get

This produces:

* A clean project at `./zc706_proj`
* A block design with just the Zynq PS
* A valid `zc706_minimal.xsa` that:

  * Can be used in **Yocto** or **PetaLinux**
  * Does **not** contain a bitstream or PL (programmable logic)
  * Is good enough for booting U-Boot + Linux on PS cores

---

## 🧪 Optional: Verify `.xsa` Contents

```bash
unzip -l zc706_minimal.xsa
```

You should see:

* `hardware/hw.hdf`
* `xsa.xml`
* No `.bit` file → expected.

---

