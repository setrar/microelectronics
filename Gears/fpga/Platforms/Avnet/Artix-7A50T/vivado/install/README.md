# Install

Here is a **step-by-step installation guide** to install **Vivado Design Suite 2025.1** together with **Vitis Unified Software Platform 2025.1** on **Ubuntu 22.04.03 LTS**, tuned for your “Artix-7” project environment.

---

## Pre-installation preparation 

To avoid installer hang-ups or missing dependencies, do the following first:

1. Update your system: 

   ```bash
   sudo apt update && sudo apt upgrade
   ```

2. Install required libraries and add i386 architecture (because some legacy libs may be 32-bit): (:x: not sure about this section)

   ```bash
   sudo dpkg --add-architecture i386
   sudo apt install -y \
     build-essential gcc g++ make \
     python3-dev python3-pip \
     libtinfo5 libncurses5 libncursesw5 \
     libglib2.0-dev libgtk2.0-dev zlib1g zlib1g-dev \
     unzip xvfb git net-tools
   ```

   The packages `libtinfo5` and `libncurses5` are explicitly required. ([Adaptive Support][1])
   Also, for Ubuntu 22.04 some guides mention adding `libncursesw5`, etc. ([element14 Community][2])

3. Ensure you have enough disk space. For the full installation you’ll likely need **60 GB or more**. ([People ECE][3])
   Consider where you’ll install (e.g., `/tools/Xilinx` or `/tools/Xilinx`) and ensure your user has permissions:

   ```bash
   sudo mkdir -p /tools/Xilinx
   sudo chown -R $USER:$USER /tools/Xilinx
   ```

4. (Optional but recommended) Make sure the default shell `/bin/sh` is `bash` rather than `dash`, if you later install PetaLinux or other scripts expect it:

   ```bash
   sudo dpkg-reconfigure dash  
   # choose “No” when asked if you want /bin/sh to be dash.
   ```

   (While this is more relevant for PetaLinux, many FPGA tool flows assume bash.) ([FPGA Developer][4])

---

## 🛠 Download Installer

1. Go to the AMD (formerly Xilinx) downloads page. For 2025.1 you’ll find:

   * Linux Self Extracting Web Installer (BIN)
   * Full Product Installation (SFD TAR/GZIP) (~100 GB) ([AMD][5])
2. Choose where you will download it (e.g., `~/Downloads`).
3. Make it executable:

   ```bash
   cd ~/Downloads
   chmod +x FPGAs_AdaptiveSoCs_Unified_SDI_2025.1_0530_0145_Lin64.bin
   ```

---

## 🚀 Installation of Vivado + Vitis

Since Vitis includes Vivado in the 2025.1 unified installer, you can install both in one go. ([AMD][5])

1. Run the installer:

   ```bash
   bash ./FPGAs_AdaptiveSoCs_Unified_SDI_2025.1_0530_0145_Lin64.bin
   ```
<details>

```lua
Verifying archive integrity... All good.
Uncompressing AMD Installer for FPGAs and Adaptive SoCs..............................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................................
This is a fresh install.
INFO  - Internet connection validated, can connect to internet. 
INFO  - Installing Edition: Vitis Unified Software Platform 
INFO  - Installation directory is /tools/Xilinx 
```

</details>

   (Use `sudo` if installing to a system location like `/tools/Xilinx`.)

2. The installer GUI will launch.


   * Accept license agreement.
   * Select installation directory (e.g., `/tools/Xilinx/Vivado/2025.1` or whatever path you prefer).
   * When prompted for products to install: **select both Vivado Design Suite** and **Vitis Unified Software Platform** (or “Vitis Core Development Kit”) depending on your license/edition.
   * Select the device families you need (e.g., for Artix-7, ensure the 7 Series devices are selected).
   * Follow through the installer until it finishes.

<img src=images/vivado-install1.png width='30%' height='30%' > </img>

3. After installation completes, run the post-install library script if available. Some users have needed to run `installlibs.sh` from the installer folder to satisfy missing dependencies. ([element14 Community][2])
   e.g.,

   ```bash
   cd /tools/Xilinx/…/InstallFiles
   ./installLibs.sh
   ```

---

## 🔧 Environment setup

1. Add the tool settings to your shell initialization (~/.bashrc or ~/.zshrc):

   ```bash
   # Vivado/Vitis setup
   source /tools/Xilinx/Vivado/2025.1/settings64.sh
   # or if Vitis installs its own path:
   source /tools/Xilinx/Vitis/2025.1/settings64.sh
   ```
2. Verify the installation:

   ```bash
   vivado &    # should launch the GUI (or show version info)
   vitis &     # should launch Vitis IDE
   ```
3. If you later use cable drivers (USB JTAG etc), you’ll need to install drivers (in Vivado folder, `…/data/xicom/cable_drivers/lin64/install_script/install_drivers`). ([LogicTronix][6])

---

## ✅ Post-install checks and tips

* Ensure your GPU/display drivers are okay (if using GUI).
* Check that you have the correct board files for your Artix-7 board and that they are visible in Vivado (Tools → Board Part).
* If you face GUI freezes or installer hangs (common on Ubuntu 22.04) then the missing libs above are often the culprit. Several users report multiple install tries were needed. ([element14 Community][2])
* For any issue with `/bin/sh` being dash rather than bash (especially when using PetaLinux later), ensure you changed it.
* If you plan to use embedded software/accelerators (with Vitis), ensure you install the correct Linux tools and device support.

---

If you like, I can **pull together a detailed script** that automates most of these steps (including dependencies installation, download placeholder, environment setup) for Ubuntu 22.04 and your Artix-7 workflow. Would you like that?

[1]: https://adaptivesupport.amd.com/s/article/63794 "Install - What Ubuntu files are required for Vivado to run successfully?"
[2]: https://community.element14.com/technologies/fpga-group/b/blog/posts/installing-xilinx-vivado-on-ubuntu?utm_source=chatgpt.com "Installing Xilinx Vivado on Ubuntu 20 & 22 - element14 Community"
[3]: https://people-ece.vse.gmu.edu/coursewebpages/ECE/ECE545/F24/resources/Vivado_Installation_Linux.pdf "[PDF] Vivado Installation on Linux - People"
[4]: https://www.fpgadeveloper.com/how-to-install-vitis-and-petalinux-2024.1 "How to Install Vitis and PetaLinux 2024.1 - FPGA Developer"
[5]: https://www.xilinx.com/support/download/index.html/content/xilinx/en/downloadNav/vitis.html "Downloads - AMD"
[6]: https://tutorials.logictronix.com/our-resources/linux-for-fpga-design/how-to-install-vivado-on-ubuntu "Install VIVADO on Ubuntu - Linux for FPGA Design - LogicTronix"



# :books: References

[Vivado™ Edition - 2025.1  Full Product Installation]: https://account.amd.com/en/forms/downloads/xef.html?filename=FPGAs_AdaptiveSoCs_Unified_SDI_2025.1_0530_0145_Lin64.bin
