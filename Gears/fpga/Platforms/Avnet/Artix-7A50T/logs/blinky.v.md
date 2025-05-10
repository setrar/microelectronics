```powershell
 /----------------------------------------------------------------------------\
 |  yosys -- Yosys Open SYnthesis Suite                                       |
 |  Copyright (C) 2012 - 2025  Claire Xenia Wolf <claire@yosyshq.com>         |
 |  Distributed under an ISC-like license, type "license" to see terms        |
 \----------------------------------------------------------------------------/
 Yosys 0.52+104 (git sha1 3d1f2161d, clang++ 15.0.7 -fPIC -O3)

-- Parsing `blinky.v' using frontend ` -vlog2k' --

1. Executing Verilog-2005 frontend: blinky.v
Parsing Verilog input from `blinky.v' to AST representation.
Storing AST representation for module `$abstract\blinky'.
Successfully finished Verilog frontend.

-- Running command `synth_xilinx -top blinky -family xc7' --

2. Executing SYNTH_XILINX pass.

2.1. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/cells_sim.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/cells_sim.v' to AST representation.
Generating RTLIL representation for module `\VCC'.
Generating RTLIL representation for module `\GND'.
Generating RTLIL representation for module `\IBUF'.
Generating RTLIL representation for module `\IBUFG'.
Generating RTLIL representation for module `\OBUF'.
Generating RTLIL representation for module `\IOBUF'.
Generating RTLIL representation for module `\OBUFT'.
Generating RTLIL representation for module `\BUFG'.
Generating RTLIL representation for module `\BUFGCTRL'.
Generating RTLIL representation for module `\BUFHCE'.
Generating RTLIL representation for module `\INV'.
Generating RTLIL representation for module `\LUT1'.
Generating RTLIL representation for module `\LUT2'.
Generating RTLIL representation for module `\LUT3'.
Generating RTLIL representation for module `\LUT4'.
Generating RTLIL representation for module `\LUT5'.
Generating RTLIL representation for module `\LUT6'.
Generating RTLIL representation for module `\LUT6_2'.
Generating RTLIL representation for module `\$__ABC9_LUT7'.
Generating RTLIL representation for module `\$__ABC9_LUT8'.
Generating RTLIL representation for module `\MUXCY'.
Generating RTLIL representation for module `\MUXF5'.
Generating RTLIL representation for module `\MUXF6'.
Generating RTLIL representation for module `\MUXF7'.
Generating RTLIL representation for module `\MUXF8'.
Generating RTLIL representation for module `\MUXF9'.
Generating RTLIL representation for module `\XORCY'.
Generating RTLIL representation for module `\CARRY4'.
Generating RTLIL representation for module `\CARRY8'.
Generating RTLIL representation for module `\ORCY'.
Generating RTLIL representation for module `\MULT_AND'.
Generating RTLIL representation for module `\FDRE'.
Generating RTLIL representation for module `\FDRE_1'.
Generating RTLIL representation for module `\FDSE'.
Generating RTLIL representation for module `\FDSE_1'.
Generating RTLIL representation for module `\FDRSE'.
Generating RTLIL representation for module `\FDRSE_1'.
Generating RTLIL representation for module `\FDCE'.
Generating RTLIL representation for module `\FDCE_1'.
Generating RTLIL representation for module `\FDPE'.
Generating RTLIL representation for module `\FDPE_1'.
Generating RTLIL representation for module `\FDCPE'.
Generating RTLIL representation for module `\FDCPE_1'.
Generating RTLIL representation for module `\LDCE'.
Generating RTLIL representation for module `\LDPE'.
Generating RTLIL representation for module `\LDCPE'.
Generating RTLIL representation for module `\AND2B1L'.
Generating RTLIL representation for module `\OR2L'.
Generating RTLIL representation for module `\RAM16X1S'.
Generating RTLIL representation for module `\RAM16X1S_1'.
Generating RTLIL representation for module `\RAM32X1S'.
Generating RTLIL representation for module `\RAM32X1S_1'.
Generating RTLIL representation for module `\RAM64X1S'.
Generating RTLIL representation for module `\RAM64X1S_1'.
Generating RTLIL representation for module `\RAM128X1S'.
Generating RTLIL representation for module `\RAM128X1S_1'.
Generating RTLIL representation for module `\RAM256X1S'.
Generating RTLIL representation for module `\RAM512X1S'.
Generating RTLIL representation for module `\RAM16X2S'.
Generating RTLIL representation for module `\RAM32X2S'.
Generating RTLIL representation for module `\RAM64X2S'.
Generating RTLIL representation for module `\RAM16X4S'.
Generating RTLIL representation for module `\RAM32X4S'.
Generating RTLIL representation for module `\RAM16X8S'.
Generating RTLIL representation for module `\RAM32X8S'.
Generating RTLIL representation for module `\RAM16X1D'.
Generating RTLIL representation for module `\RAM16X1D_1'.
Generating RTLIL representation for module `\RAM32X1D'.
Generating RTLIL representation for module `\RAM32X1D_1'.
Generating RTLIL representation for module `\RAM64X1D'.
Generating RTLIL representation for module `\RAM64X1D_1'.
Generating RTLIL representation for module `\RAM128X1D'.
Generating RTLIL representation for module `\RAM256X1D'.
Generating RTLIL representation for module `\RAM32M'.
Generating RTLIL representation for module `\RAM32M16'.
Generating RTLIL representation for module `\RAM64M'.
Generating RTLIL representation for module `\RAM64M8'.
Generating RTLIL representation for module `\RAM32X16DR8'.
Generating RTLIL representation for module `\RAM64X8SW'.
Generating RTLIL representation for module `\ROM16X1'.
Generating RTLIL representation for module `\ROM32X1'.
Generating RTLIL representation for module `\ROM64X1'.
Generating RTLIL representation for module `\ROM128X1'.
Generating RTLIL representation for module `\ROM256X1'.
Generating RTLIL representation for module `\SRL16'.
Generating RTLIL representation for module `\SRL16E'.
Generating RTLIL representation for module `\SRLC16'.
Generating RTLIL representation for module `\SRLC16E'.
Generating RTLIL representation for module `\SRLC32E'.
Generating RTLIL representation for module `\CFGLUT5'.
Generating RTLIL representation for module `\MULT18X18'.
Generating RTLIL representation for module `\MULT18X18S'.
Generating RTLIL representation for module `\MULT18X18SIO'.
Generating RTLIL representation for module `\DSP48A'.
Generating RTLIL representation for module `\DSP48A1'.
Generating RTLIL representation for module `\DSP48'.
Generating RTLIL representation for module `\DSP48E1'.
Generating RTLIL representation for module `\RAMB18E1'.
Generating RTLIL representation for module `\RAMB36E1'.
Successfully finished Verilog frontend.

2.2. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/cells_xtra.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/cells_xtra.v' to AST representation.
Generating RTLIL representation for module `\RAMB4_S1'.
Generating RTLIL representation for module `\RAMB4_S2'.
Generating RTLIL representation for module `\RAMB4_S4'.
Generating RTLIL representation for module `\RAMB4_S8'.
Generating RTLIL representation for module `\RAMB4_S16'.
Generating RTLIL representation for module `\RAMB4_S1_S1'.
Generating RTLIL representation for module `\RAMB4_S1_S2'.
Generating RTLIL representation for module `\RAMB4_S1_S4'.
Generating RTLIL representation for module `\RAMB4_S1_S8'.
Generating RTLIL representation for module `\RAMB4_S1_S16'.
Generating RTLIL representation for module `\RAMB4_S2_S2'.
Generating RTLIL representation for module `\RAMB4_S2_S4'.
Generating RTLIL representation for module `\RAMB4_S2_S8'.
Generating RTLIL representation for module `\RAMB4_S2_S16'.
Generating RTLIL representation for module `\RAMB4_S4_S4'.
Generating RTLIL representation for module `\RAMB4_S4_S8'.
Generating RTLIL representation for module `\RAMB4_S4_S16'.
Generating RTLIL representation for module `\RAMB4_S8_S8'.
Generating RTLIL representation for module `\RAMB4_S8_S16'.
Generating RTLIL representation for module `\RAMB4_S16_S16'.
Generating RTLIL representation for module `\RAMB16_S1'.
Generating RTLIL representation for module `\RAMB16_S2'.
Generating RTLIL representation for module `\RAMB16_S4'.
Generating RTLIL representation for module `\RAMB16_S9'.
Generating RTLIL representation for module `\RAMB16_S18'.
Generating RTLIL representation for module `\RAMB16_S36'.
Generating RTLIL representation for module `\RAMB16_S1_S1'.
Generating RTLIL representation for module `\RAMB16_S1_S2'.
Generating RTLIL representation for module `\RAMB16_S1_S4'.
Generating RTLIL representation for module `\RAMB16_S1_S9'.
Generating RTLIL representation for module `\RAMB16_S1_S18'.
Generating RTLIL representation for module `\RAMB16_S1_S36'.
Generating RTLIL representation for module `\RAMB16_S2_S2'.
Generating RTLIL representation for module `\RAMB16_S2_S4'.
Generating RTLIL representation for module `\RAMB16_S2_S9'.
Generating RTLIL representation for module `\RAMB16_S2_S18'.
Generating RTLIL representation for module `\RAMB16_S2_S36'.
Generating RTLIL representation for module `\RAMB16_S4_S4'.
Generating RTLIL representation for module `\RAMB16_S4_S9'.
Generating RTLIL representation for module `\RAMB16_S4_S18'.
Generating RTLIL representation for module `\RAMB16_S4_S36'.
Generating RTLIL representation for module `\RAMB16_S9_S9'.
Generating RTLIL representation for module `\RAMB16_S9_S18'.
Generating RTLIL representation for module `\RAMB16_S9_S36'.
Generating RTLIL representation for module `\RAMB16_S18_S18'.
Generating RTLIL representation for module `\RAMB16_S18_S36'.
Generating RTLIL representation for module `\RAMB16_S36_S36'.
Generating RTLIL representation for module `\RAMB16BWE_S18'.
Generating RTLIL representation for module `\RAMB16BWE_S36'.
Generating RTLIL representation for module `\RAMB16BWE_S18_S9'.
Generating RTLIL representation for module `\RAMB16BWE_S18_S18'.
Generating RTLIL representation for module `\RAMB16BWE_S36_S9'.
Generating RTLIL representation for module `\RAMB16BWE_S36_S18'.
Generating RTLIL representation for module `\RAMB16BWE_S36_S36'.
Generating RTLIL representation for module `\RAMB16BWER'.
Generating RTLIL representation for module `\RAMB8BWER'.
Generating RTLIL representation for module `\FIFO16'.
Generating RTLIL representation for module `\RAMB16'.
Generating RTLIL representation for module `\RAMB32_S64_ECC'.
Generating RTLIL representation for module `\FIFO18'.
Generating RTLIL representation for module `\FIFO18_36'.
Generating RTLIL representation for module `\FIFO36'.
Generating RTLIL representation for module `\FIFO36_72'.
Generating RTLIL representation for module `\RAMB18'.
Generating RTLIL representation for module `\RAMB36'.
Generating RTLIL representation for module `\RAMB18SDP'.
Generating RTLIL representation for module `\RAMB36SDP'.
Generating RTLIL representation for module `\FIFO18E1'.
Generating RTLIL representation for module `\FIFO36E1'.
Generating RTLIL representation for module `\FIFO18E2'.
Generating RTLIL representation for module `\FIFO36E2'.
Generating RTLIL representation for module `\RAMB18E2'.
Generating RTLIL representation for module `\RAMB36E2'.
Generating RTLIL representation for module `\URAM288'.
Generating RTLIL representation for module `\URAM288_BASE'.
Generating RTLIL representation for module `\DSP48E'.
Generating RTLIL representation for module `\DSP48E2'.
Generating RTLIL representation for module `\FDDRCPE'.
Generating RTLIL representation for module `\FDDRRSE'.
Generating RTLIL representation for module `\IFDDRCPE'.
Generating RTLIL representation for module `\IFDDRRSE'.
Generating RTLIL representation for module `\OFDDRCPE'.
Generating RTLIL representation for module `\OFDDRRSE'.
Generating RTLIL representation for module `\OFDDRTCPE'.
Generating RTLIL representation for module `\OFDDRTRSE'.
Generating RTLIL representation for module `\IDDR2'.
Generating RTLIL representation for module `\ODDR2'.
Generating RTLIL representation for module `\IDDR'.
Generating RTLIL representation for module `\IDDR_2CLK'.
Generating RTLIL representation for module `\ODDR'.
Generating RTLIL representation for module `\IDELAYCTRL'.
Generating RTLIL representation for module `\IDELAY'.
Generating RTLIL representation for module `\ISERDES'.
Generating RTLIL representation for module `\OSERDES'.
Generating RTLIL representation for module `\IODELAY'.
Generating RTLIL representation for module `\ISERDES_NODELAY'.
Generating RTLIL representation for module `\IODELAYE1'.
Generating RTLIL representation for module `\ISERDESE1'.
Generating RTLIL representation for module `\OSERDESE1'.
Generating RTLIL representation for module `\IDELAYE2'.
Generating RTLIL representation for module `\ODELAYE2'.
Generating RTLIL representation for module `\ISERDESE2'.
Generating RTLIL representation for module `\OSERDESE2'.
Generating RTLIL representation for module `\PHASER_IN'.
Generating RTLIL representation for module `\PHASER_IN_PHY'.
Generating RTLIL representation for module `\PHASER_OUT'.
Generating RTLIL representation for module `\PHASER_OUT_PHY'.
Generating RTLIL representation for module `\PHASER_REF'.
Generating RTLIL representation for module `\PHY_CONTROL'.
Generating RTLIL representation for module `\IDDRE1'.
Generating RTLIL representation for module `\ODDRE1'.
Generating RTLIL representation for module `\IDELAYE3'.
Generating RTLIL representation for module `\ODELAYE3'.
Generating RTLIL representation for module `\ISERDESE3'.
Generating RTLIL representation for module `\OSERDESE3'.
Generating RTLIL representation for module `\BITSLICE_CONTROL'.
Generating RTLIL representation for module `\RIU_OR'.
Generating RTLIL representation for module `\RX_BITSLICE'.
Generating RTLIL representation for module `\RXTX_BITSLICE'.
Generating RTLIL representation for module `\TX_BITSLICE'.
Generating RTLIL representation for module `\TX_BITSLICE_TRI'.
Generating RTLIL representation for module `\IODELAY2'.
Generating RTLIL representation for module `\IODRP2'.
Generating RTLIL representation for module `\IODRP2_MCB'.
Generating RTLIL representation for module `\ISERDES2'.
Generating RTLIL representation for module `\OSERDES2'.
Generating RTLIL representation for module `\IBUF_DLY_ADJ'.
Generating RTLIL representation for module `\IBUF_IBUFDISABLE'.
Generating RTLIL representation for module `\IBUF_INTERMDISABLE'.
Generating RTLIL representation for module `\IBUF_ANALOG'.
Generating RTLIL representation for module `\IBUFE3'.
Generating RTLIL representation for module `\IBUFDS'.
Generating RTLIL representation for module `\IBUFDS_DLY_ADJ'.
Generating RTLIL representation for module `\IBUFDS_IBUFDISABLE'.
Generating RTLIL representation for module `\IBUFDS_INTERMDISABLE'.
Generating RTLIL representation for module `\IBUFDS_DIFF_OUT'.
Generating RTLIL representation for module `\IBUFDS_DIFF_OUT_IBUFDISABLE'.
Generating RTLIL representation for module `\IBUFDS_DIFF_OUT_INTERMDISABLE'.
Generating RTLIL representation for module `\IBUFDSE3'.
Generating RTLIL representation for module `\IBUFDS_DPHY'.
Generating RTLIL representation for module `\IBUFGDS'.
Generating RTLIL representation for module `\IBUFGDS_DIFF_OUT'.
Generating RTLIL representation for module `\IOBUF_DCIEN'.
Generating RTLIL representation for module `\IOBUF_INTERMDISABLE'.
Generating RTLIL representation for module `\IOBUFE3'.
Generating RTLIL representation for module `\IOBUFDS'.
Generating RTLIL representation for module `\IOBUFDS_DCIEN'.
Generating RTLIL representation for module `\IOBUFDS_INTERMDISABLE'.
Generating RTLIL representation for module `\IOBUFDS_DIFF_OUT'.
Generating RTLIL representation for module `\IOBUFDS_DIFF_OUT_DCIEN'.
Generating RTLIL representation for module `\IOBUFDS_DIFF_OUT_INTERMDISABLE'.
Generating RTLIL representation for module `\IOBUFDSE3'.
Generating RTLIL representation for module `\OBUFDS'.
Generating RTLIL representation for module `\OBUFDS_DPHY'.
Generating RTLIL representation for module `\OBUFTDS'.
Generating RTLIL representation for module `\KEEPER'.
Generating RTLIL representation for module `\PULLDOWN'.
Generating RTLIL representation for module `\PULLUP'.
Generating RTLIL representation for module `\DCIRESET'.
Generating RTLIL representation for module `\HPIO_VREF'.
Generating RTLIL representation for module `\BUFGCE'.
Generating RTLIL representation for module `\BUFGCE_1'.
Generating RTLIL representation for module `\BUFGMUX'.
Generating RTLIL representation for module `\BUFGMUX_1'.
Generating RTLIL representation for module `\BUFGMUX_CTRL'.
Generating RTLIL representation for module `\BUFGMUX_VIRTEX4'.
Generating RTLIL representation for module `\BUFG_GT'.
Generating RTLIL representation for module `\BUFG_GT_SYNC'.
Generating RTLIL representation for module `\BUFG_PS'.
Generating RTLIL representation for module `\BUFGCE_DIV'.
Generating RTLIL representation for module `\BUFH'.
Generating RTLIL representation for module `\BUFIO2'.
Generating RTLIL representation for module `\BUFIO2_2CLK'.
Generating RTLIL representation for module `\BUFIO2FB'.
Generating RTLIL representation for module `\BUFPLL'.
Generating RTLIL representation for module `\BUFPLL_MCB'.
Generating RTLIL representation for module `\BUFIO'.
Generating RTLIL representation for module `\BUFIODQS'.
Generating RTLIL representation for module `\BUFR'.
Generating RTLIL representation for module `\BUFMR'.
Generating RTLIL representation for module `\BUFMRCE'.
Generating RTLIL representation for module `\DCM'.
Generating RTLIL representation for module `\DCM_SP'.
Generating RTLIL representation for module `\DCM_CLKGEN'.
Generating RTLIL representation for module `\DCM_ADV'.
Generating RTLIL representation for module `\DCM_BASE'.
Generating RTLIL representation for module `\DCM_PS'.
Generating RTLIL representation for module `\PMCD'.
Generating RTLIL representation for module `\PLL_ADV'.
Generating RTLIL representation for module `\PLL_BASE'.
Generating RTLIL representation for module `\MMCM_ADV'.
Generating RTLIL representation for module `\MMCM_BASE'.
Generating RTLIL representation for module `\MMCME2_ADV'.
Generating RTLIL representation for module `\MMCME2_BASE'.
Generating RTLIL representation for module `\PLLE2_ADV'.
Generating RTLIL representation for module `\PLLE2_BASE'.
Generating RTLIL representation for module `\MMCME3_ADV'.
Generating RTLIL representation for module `\MMCME3_BASE'.
Generating RTLIL representation for module `\PLLE3_ADV'.
Generating RTLIL representation for module `\PLLE3_BASE'.
Generating RTLIL representation for module `\MMCME4_ADV'.
Generating RTLIL representation for module `\MMCME4_BASE'.
Generating RTLIL representation for module `\PLLE4_ADV'.
Generating RTLIL representation for module `\PLLE4_BASE'.
Generating RTLIL representation for module `\BUFT'.
Generating RTLIL representation for module `\IN_FIFO'.
Generating RTLIL representation for module `\OUT_FIFO'.
Generating RTLIL representation for module `\HARD_SYNC'.
Generating RTLIL representation for module `\STARTUP_SPARTAN3'.
Generating RTLIL representation for module `\STARTUP_SPARTAN3E'.
Generating RTLIL representation for module `\STARTUP_SPARTAN3A'.
Generating RTLIL representation for module `\STARTUP_SPARTAN6'.
Generating RTLIL representation for module `\STARTUP_VIRTEX4'.
Generating RTLIL representation for module `\STARTUP_VIRTEX5'.
Generating RTLIL representation for module `\STARTUP_VIRTEX6'.
Generating RTLIL representation for module `\STARTUPE2'.
Generating RTLIL representation for module `\STARTUPE3'.
Generating RTLIL representation for module `\CAPTURE_SPARTAN3'.
Generating RTLIL representation for module `\CAPTURE_SPARTAN3A'.
Generating RTLIL representation for module `\CAPTURE_VIRTEX4'.
Generating RTLIL representation for module `\CAPTURE_VIRTEX5'.
Generating RTLIL representation for module `\CAPTURE_VIRTEX6'.
Generating RTLIL representation for module `\CAPTUREE2'.
Generating RTLIL representation for module `\ICAP_SPARTAN3A'.
Generating RTLIL representation for module `\ICAP_SPARTAN6'.
Generating RTLIL representation for module `\ICAP_VIRTEX4'.
Generating RTLIL representation for module `\ICAP_VIRTEX5'.
Generating RTLIL representation for module `\ICAP_VIRTEX6'.
Generating RTLIL representation for module `\ICAPE2'.
Generating RTLIL representation for module `\ICAPE3'.
Generating RTLIL representation for module `\BSCAN_SPARTAN3'.
Generating RTLIL representation for module `\BSCAN_SPARTAN3A'.
Generating RTLIL representation for module `\BSCAN_SPARTAN6'.
Generating RTLIL representation for module `\BSCAN_VIRTEX4'.
Generating RTLIL representation for module `\BSCAN_VIRTEX5'.
Generating RTLIL representation for module `\BSCAN_VIRTEX6'.
Generating RTLIL representation for module `\BSCANE2'.
Generating RTLIL representation for module `\DNA_PORT'.
Generating RTLIL representation for module `\DNA_PORTE2'.
Generating RTLIL representation for module `\FRAME_ECC_VIRTEX4'.
Generating RTLIL representation for module `\FRAME_ECC_VIRTEX5'.
Generating RTLIL representation for module `\FRAME_ECC_VIRTEX6'.
Generating RTLIL representation for module `\FRAME_ECCE2'.
Generating RTLIL representation for module `\FRAME_ECCE3'.
Generating RTLIL representation for module `\FRAME_ECCE4'.
Generating RTLIL representation for module `\USR_ACCESS_VIRTEX4'.
Generating RTLIL representation for module `\USR_ACCESS_VIRTEX5'.
Generating RTLIL representation for module `\USR_ACCESS_VIRTEX6'.
Generating RTLIL representation for module `\USR_ACCESSE2'.
Generating RTLIL representation for module `\POST_CRC_INTERNAL'.
Generating RTLIL representation for module `\SUSPEND_SYNC'.
Generating RTLIL representation for module `\KEY_CLEAR'.
Generating RTLIL representation for module `\MASTER_JTAG'.
Generating RTLIL representation for module `\SPI_ACCESS'.
Generating RTLIL representation for module `\EFUSE_USR'.
Generating RTLIL representation for module `\SYSMON'.
Generating RTLIL representation for module `\XADC'.
Generating RTLIL representation for module `\SYSMONE1'.
Generating RTLIL representation for module `\SYSMONE4'.
Generating RTLIL representation for module `\GTPA1_DUAL'.
Generating RTLIL representation for module `\GT11_CUSTOM'.
Generating RTLIL representation for module `\GT11_DUAL'.
Generating RTLIL representation for module `\GT11CLK'.
Generating RTLIL representation for module `\GT11CLK_MGT'.
Generating RTLIL representation for module `\GTP_DUAL'.
Generating RTLIL representation for module `\GTX_DUAL'.
Generating RTLIL representation for module `\CRC32'.
Generating RTLIL representation for module `\CRC64'.
Generating RTLIL representation for module `\GTHE1_QUAD'.
Generating RTLIL representation for module `\GTXE1'.
Generating RTLIL representation for module `\IBUFDS_GTXE1'.
Generating RTLIL representation for module `\IBUFDS_GTHE1'.
Generating RTLIL representation for module `\GTHE2_CHANNEL'.
Generating RTLIL representation for module `\GTHE2_COMMON'.
Generating RTLIL representation for module `\GTPE2_CHANNEL'.
Generating RTLIL representation for module `\GTPE2_COMMON'.
Generating RTLIL representation for module `\GTXE2_CHANNEL'.
Generating RTLIL representation for module `\GTXE2_COMMON'.
Generating RTLIL representation for module `\IBUFDS_GTE2'.
Generating RTLIL representation for module `\GTHE3_CHANNEL'.
Generating RTLIL representation for module `\GTHE3_COMMON'.
Generating RTLIL representation for module `\GTYE3_CHANNEL'.
Generating RTLIL representation for module `\GTYE3_COMMON'.
Generating RTLIL representation for module `\IBUFDS_GTE3'.
Generating RTLIL representation for module `\OBUFDS_GTE3'.
Generating RTLIL representation for module `\OBUFDS_GTE3_ADV'.
Generating RTLIL representation for module `\GTHE4_CHANNEL'.
Generating RTLIL representation for module `\GTHE4_COMMON'.
Generating RTLIL representation for module `\GTYE4_CHANNEL'.
Generating RTLIL representation for module `\GTYE4_COMMON'.
Generating RTLIL representation for module `\IBUFDS_GTE4'.
Generating RTLIL representation for module `\OBUFDS_GTE4'.
Generating RTLIL representation for module `\OBUFDS_GTE4_ADV'.
Generating RTLIL representation for module `\GTM_DUAL'.
Generating RTLIL representation for module `\IBUFDS_GTM'.
Generating RTLIL representation for module `\OBUFDS_GTM'.
Generating RTLIL representation for module `\OBUFDS_GTM_ADV'.
Generating RTLIL representation for module `\HSDAC'.
Generating RTLIL representation for module `\HSADC'.
Generating RTLIL representation for module `\RFDAC'.
Generating RTLIL representation for module `\RFADC'.
Generating RTLIL representation for module `\PCIE_A1'.
Generating RTLIL representation for module `\PCIE_EP'.
Generating RTLIL representation for module `\PCIE_2_0'.
Generating RTLIL representation for module `\PCIE_2_1'.
Generating RTLIL representation for module `\PCIE_3_0'.
Generating RTLIL representation for module `\PCIE_3_1'.
Generating RTLIL representation for module `\PCIE40E4'.
Generating RTLIL representation for module `\PCIE4CE4'.
Generating RTLIL representation for module `\EMAC'.
Generating RTLIL representation for module `\TEMAC'.
Generating RTLIL representation for module `\TEMAC_SINGLE'.
Generating RTLIL representation for module `\CMAC'.
Generating RTLIL representation for module `\CMACE4'.
Generating RTLIL representation for module `\MCB'.
Generating RTLIL representation for module `\HBM_REF_CLK'.
Generating RTLIL representation for module `\HBM_SNGLBLI_INTF_APB'.
Generating RTLIL representation for module `\HBM_SNGLBLI_INTF_AXI'.
Generating RTLIL representation for module `\HBM_ONE_STACK_INTF'.
Generating RTLIL representation for module `\HBM_TWO_STACK_INTF'.
Generating RTLIL representation for module `\PPC405_ADV'.
Generating RTLIL representation for module `\PPC440'.
Generating RTLIL representation for module `\PS7'.
Generating RTLIL representation for module `\PS8'.
Generating RTLIL representation for module `\ILKN'.
Generating RTLIL representation for module `\ILKNE4'.
Generating RTLIL representation for module `\VCU'.
Generating RTLIL representation for module `\FE'.
Successfully finished Verilog frontend.

2.3. Executing HIERARCHY pass (managing design hierarchy).

2.4. Executing AST frontend in derive mode using pre-parsed AST for module `\blinky'.
Generating RTLIL representation for module `\blinky'.

2.4.1. Analyzing design hierarchy..
Top module:  \blinky

2.4.2. Analyzing design hierarchy..
Top module:  \blinky
Removing unused module `$abstract\blinky'.
Removed 1 unused modules.

2.5. Executing PROC pass (convert processes to netlists).

2.5.1. Executing PROC_CLEAN pass (remove empty switches from decision trees).
Cleaned up 0 empty switches.

2.5.2. Executing PROC_RMDEAD pass (remove dead branches from decision trees).
Removed a total of 0 dead cases.

2.5.3. Executing PROC_PRUNE pass (remove redundant assignments in processes).
Removed 0 redundant assignments.
Promoted 3 assignments to connections.

2.5.4. Executing PROC_INIT pass (extract init attributes).
Found init rule in `\blinky.$proc$blinky.v:5$1099'.
  Set init value: \counter = 24'000000000000000000000000

2.5.5. Executing PROC_ARST pass (detect async resets in processes).

2.5.6. Executing PROC_ROM pass (convert switches to ROMs).
Converted 0 switches.

2.5.7. Executing PROC_MUX pass (convert decision trees to multiplexers).
Creating decoders for process `\blinky.$proc$blinky.v:5$1099'.
Creating decoders for process `\blinky.$proc$blinky.v:7$1097'.

2.5.8. Executing PROC_DLATCH pass (convert process syncs to latches).

2.5.9. Executing PROC_DFF pass (convert process syncs to FFs).
Creating register for signal `\blinky.\led' using process `\blinky.$proc$blinky.v:7$1097'.
  created $dff cell `$procdff$1100' with positive edge clock.
Creating register for signal `\blinky.\counter' using process `\blinky.$proc$blinky.v:7$1097'.
  created $dff cell `$procdff$1101' with positive edge clock.

2.5.10. Executing PROC_MEMWR pass (convert process memory writes to cells).

2.5.11. Executing PROC_CLEAN pass (remove empty switches from decision trees).
Removing empty process `blinky.$proc$blinky.v:5$1099'.
Removing empty process `blinky.$proc$blinky.v:7$1097'.
Cleaned up 0 empty switches.

2.5.12. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.6. Executing TRIBUF pass.

2.7. Executing DEMINOUT pass (demote inout ports to input or output).

2.8. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.9. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..
Removed 0 unused cells and 2 unused wires.
<suppressed ~1 debug messages>

2.10. Executing CHECK pass (checking for obvious problems).
Checking module blinky...
Found and reported 0 problems.

2.11. Executing OPT pass (performing simple optimizations).

2.11.1. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.11.2. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
Removed a total of 0 cells.

2.11.3. Executing OPT_MUXTREE pass (detect dead branches in mux trees).
Running muxtree optimizer on module \blinky..
  Creating internal representation of mux trees.
  No muxes found in this module.
Removed 0 multiplexer ports.

2.11.4. Executing OPT_REDUCE pass (consolidate $*mux and $reduce_* inputs).
  Optimizing cells in module \blinky.
Performed a total of 0 changes.

2.11.5. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
Removed a total of 0 cells.

2.11.6. Executing OPT_DFF pass (perform DFF optimizations).

2.11.7. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..

2.11.8. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.11.9. Finished OPT passes. (There is nothing left to do.)

2.12. Executing FSM pass (extract and optimize FSM).

2.12.1. Executing FSM_DETECT pass (finding FSMs in design).

2.12.2. Executing FSM_EXTRACT pass (extracting FSM from design).

2.12.3. Executing FSM_OPT pass (simple optimizations of FSMs).

2.12.4. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..

2.12.5. Executing FSM_OPT pass (simple optimizations of FSMs).

2.12.6. Executing FSM_RECODE pass (re-assigning FSM state encoding).

2.12.7. Executing FSM_INFO pass (dumping all available information on FSM cells).

2.12.8. Executing FSM_MAP pass (mapping FSMs to basic logic).

2.13. Executing OPT pass (performing simple optimizations).

2.13.1. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.13.2. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
Removed a total of 0 cells.

2.13.3. Executing OPT_MUXTREE pass (detect dead branches in mux trees).
Running muxtree optimizer on module \blinky..
  Creating internal representation of mux trees.
  No muxes found in this module.
Removed 0 multiplexer ports.

2.13.4. Executing OPT_REDUCE pass (consolidate $*mux and $reduce_* inputs).
  Optimizing cells in module \blinky.
Performed a total of 0 changes.

2.13.5. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
Removed a total of 0 cells.

2.13.6. Executing OPT_DFF pass (perform DFF optimizations).

2.13.7. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..

2.13.8. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.13.9. Finished OPT passes. (There is nothing left to do.)

2.14. Executing WREDUCE pass (reducing word size of cells).
Removed top 31 bits (of 32) from port B of cell blinky.$add$blinky.v:8$1098 ($add).
Removed top 8 bits (of 32) from port Y of cell blinky.$add$blinky.v:8$1098 ($add).

2.15. Executing PEEPOPT pass (run peephole optimizers).

2.16. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..
Removed 0 unused cells and 1 unused wires.
<suppressed ~1 debug messages>

2.17. Executing PMUX2SHIFTX pass.

2.18. Executing MEMORY_DFF pass (merging $dff cells to $memrd).

2.19. Executing TECHMAP pass (map to technology primitives).

2.19.1. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/mul2dsp.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/mul2dsp.v' to AST representation.
Generating RTLIL representation for module `\_80_mul'.
Generating RTLIL representation for module `\_90_soft_mul'.
Successfully finished Verilog frontend.

2.19.2. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/xc7_dsp_map.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/xc7_dsp_map.v' to AST representation.
Generating RTLIL representation for module `\$__MUL25X18'.
Successfully finished Verilog frontend.

2.19.3. Continuing TECHMAP pass.
No more expansions possible.
<suppressed ~5 debug messages>

2.20. Executing OPT_EXPR pass (perform const folding).

2.21. Executing WREDUCE pass (reducing word size of cells).

2.22. Executing XILINX_DSP pass (pack resources into DSPs).

2.23. Executing TECHMAP pass (map to technology primitives).

2.23.1. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/cmp2lut.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/cmp2lut.v' to AST representation.
Generating RTLIL representation for module `\_90_lut_cmp_'.
Successfully finished Verilog frontend.

2.23.2. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/cmp2lcu.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/cmp2lcu.v' to AST representation.
Generating RTLIL representation for module `\_80_lcu_cmp_'.
Generating RTLIL representation for module `\$__CMP2LCU'.
Successfully finished Verilog frontend.

2.23.3. Continuing TECHMAP pass.
No more expansions possible.
<suppressed ~7 debug messages>

2.24. Executing ALUMACC pass (create $alu and $macc cells).
Extracting $alu and $macc cells in module blinky:
  creating $macc model for $add$blinky.v:8$1098 ($add).
  creating $alu model for $macc $add$blinky.v:8$1098.
  creating $alu cell for $add$blinky.v:8$1098: $auto$alumacc.cc:495:replace_alu$1104
  created 1 $alu and 0 $macc cells.

2.25. Executing SHARE pass (SAT-based resource sharing).

2.26. Executing OPT pass (performing simple optimizations).

2.26.1. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.26.2. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
Removed a total of 0 cells.

2.26.3. Executing OPT_MUXTREE pass (detect dead branches in mux trees).
Running muxtree optimizer on module \blinky..
  Creating internal representation of mux trees.
  No muxes found in this module.
Removed 0 multiplexer ports.

2.26.4. Executing OPT_REDUCE pass (consolidate $*mux and $reduce_* inputs).
  Optimizing cells in module \blinky.
Performed a total of 0 changes.

2.26.5. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
Removed a total of 0 cells.

2.26.6. Executing OPT_DFF pass (perform DFF optimizations).

2.26.7. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..

2.26.8. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.26.9. Finished OPT passes. (There is nothing left to do.)

2.27. Executing MEMORY pass.

2.27.1. Executing OPT_MEM pass (optimize memories).
Performed a total of 0 transformations.

2.27.2. Executing OPT_MEM_PRIORITY pass (removing unnecessary memory write priority relations).
Performed a total of 0 transformations.

2.27.3. Executing OPT_MEM_FEEDBACK pass (finding memory read-to-write feedback paths).

2.27.4. Executing MEMORY_BMUX2ROM pass (converting muxes to ROMs).

2.27.5. Executing MEMORY_DFF pass (merging $dff cells to $memrd).

2.27.6. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..

2.27.7. Executing MEMORY_SHARE pass (consolidating $memrd/$memwr cells).

2.27.8. Executing OPT_MEM_WIDEN pass (optimize memories where all ports are wide).
Performed a total of 0 transformations.

2.27.9. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..

2.27.10. Executing MEMORY_COLLECT pass (generating $mem cells).

2.28. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..

2.29. Executing MEMORY_LIBMAP pass (mapping memories to cells).

2.30. Executing TECHMAP pass (map to technology primitives).

2.30.1. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/lutrams_xc5v_map.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/lutrams_xc5v_map.v' to AST representation.
Generating RTLIL representation for module `\$__XILINX_LUTRAM_SP_'.
Generating RTLIL representation for module `\$__XILINX_LUTRAM_DP_'.
Generating RTLIL representation for module `\$__XILINX_LUTRAM_QP_'.
Generating RTLIL representation for module `\$__XILINX_LUTRAM_OP_'.
Generating RTLIL representation for module `\$__XILINX_LUTRAM_SDP_'.
Generating RTLIL representation for module `\$__XILINX_LUTRAM_64X8SW_'.
Generating RTLIL representation for module `\$__XILINX_LUTRAM_32X16DR8_'.
Successfully finished Verilog frontend.

2.30.2. Continuing TECHMAP pass.
No more expansions possible.
<suppressed ~9 debug messages>

2.31. Executing TECHMAP pass (map to technology primitives).

2.31.1. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/brams_xc6v_map.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/brams_xc6v_map.v' to AST representation.
Generating RTLIL representation for module `\$__XILINX_BLOCKRAM_TDP_'.
Generating RTLIL representation for module `\$__XILINX_BLOCKRAM_SDP_'.
Successfully finished Verilog frontend.

2.31.2. Continuing TECHMAP pass.
No more expansions possible.
<suppressed ~4 debug messages>

2.32. Executing OPT pass (performing simple optimizations).

2.32.1. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.32.2. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
Removed a total of 0 cells.

2.32.3. Executing OPT_DFF pass (perform DFF optimizations).

2.32.4. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..

2.32.5. Finished fast OPT passes.

2.33. Executing MEMORY_MAP pass (converting memories to logic and flip-flops).

2.34. Executing OPT pass (performing simple optimizations).

2.34.1. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.34.2. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
Removed a total of 0 cells.

2.34.3. Executing OPT_MUXTREE pass (detect dead branches in mux trees).
Running muxtree optimizer on module \blinky..
  Creating internal representation of mux trees.
  No muxes found in this module.
Removed 0 multiplexer ports.

2.34.4. Executing OPT_REDUCE pass (consolidate $*mux and $reduce_* inputs).
  Optimizing cells in module \blinky.
Performed a total of 0 changes.

2.34.5. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
Removed a total of 0 cells.

2.34.6. Executing OPT_SHARE pass.

2.34.7. Executing OPT_DFF pass (perform DFF optimizations).

2.34.8. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..

2.34.9. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.34.10. Finished OPT passes. (There is nothing left to do.)

2.35. Executing XILINX_SRL pass (Xilinx shift register extraction).

2.36. Executing TECHMAP pass (map to technology primitives).

2.36.1. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/techmap.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/techmap.v' to AST representation.
Generating RTLIL representation for module `\_90_simplemap_bool_ops'.
Generating RTLIL representation for module `\_90_simplemap_reduce_ops'.
Generating RTLIL representation for module `\_90_simplemap_logic_ops'.
Generating RTLIL representation for module `\_90_simplemap_compare_ops'.
Generating RTLIL representation for module `\_90_simplemap_various'.
Generating RTLIL representation for module `\_90_simplemap_registers'.
Generating RTLIL representation for module `\_90_shift_ops_shr_shl_sshl_sshr'.
Generating RTLIL representation for module `\_90_shift_shiftx'.
Generating RTLIL representation for module `\_90_fa'.
Generating RTLIL representation for module `\_90_lcu_brent_kung'.
Generating RTLIL representation for module `\_90_alu'.
Generating RTLIL representation for module `\_90_macc'.
Generating RTLIL representation for module `\_90_alumacc'.
Generating RTLIL representation for module `\$__div_mod_u'.
Generating RTLIL representation for module `\$__div_mod_trunc'.
Generating RTLIL representation for module `\_90_div'.
Generating RTLIL representation for module `\_90_mod'.
Generating RTLIL representation for module `\$__div_mod_floor'.
Generating RTLIL representation for module `\_90_divfloor'.
Generating RTLIL representation for module `\_90_modfloor'.
Generating RTLIL representation for module `\_90_pow'.
Generating RTLIL representation for module `\_90_pmux'.
Generating RTLIL representation for module `\_90_demux'.
Generating RTLIL representation for module `\_90_lut'.
Successfully finished Verilog frontend.

2.36.2. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/arith_map.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/arith_map.v' to AST representation.
Generating RTLIL representation for module `\_80_xilinx_lcu'.
Generating RTLIL representation for module `\_80_xilinx_alu'.
Successfully finished Verilog frontend.

2.36.3. Continuing TECHMAP pass.
Using extmapper simplemap for cells of type $dff.
Using template $paramod$92416ad05ea14f047e025d5dd00bd9d45058060b\_80_xilinx_alu for cells of type $alu.
Using extmapper simplemap for cells of type $xor.
Using extmapper simplemap for cells of type $mux.
Using extmapper simplemap for cells of type $not.
Using extmapper simplemap for cells of type $pos.
No more expansions possible.
<suppressed ~106 debug messages>

2.37. Executing OPT pass (performing simple optimizations).

2.37.1. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.
<suppressed ~48 debug messages>

2.37.2. Executing OPT_MERGE pass (detect identical cells).
Finding identical cells in module `\blinky'.
<suppressed ~3 debug messages>
Removed a total of 1 cells.

2.37.3. Executing OPT_DFF pass (perform DFF optimizations).

2.37.4. Executing OPT_CLEAN pass (remove unused cells and wires).
Finding unused cells or wires in module \blinky..
Removed 23 unused cells and 20 unused wires.
<suppressed ~24 debug messages>

2.37.5. Finished fast OPT passes.

2.38. Executing IOPADMAP pass (mapping inputs/outputs to IO-PAD cells).
Mapping port blinky.clk using IBUF.
Mapping port blinky.led using OBUF.

2.39. Executing TECHMAP pass (map to technology primitives).

2.39.1. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/techmap.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/techmap.v' to AST representation.
Generating RTLIL representation for module `\_90_simplemap_bool_ops'.
Generating RTLIL representation for module `\_90_simplemap_reduce_ops'.
Generating RTLIL representation for module `\_90_simplemap_logic_ops'.
Generating RTLIL representation for module `\_90_simplemap_compare_ops'.
Generating RTLIL representation for module `\_90_simplemap_various'.
Generating RTLIL representation for module `\_90_simplemap_registers'.
Generating RTLIL representation for module `\_90_shift_ops_shr_shl_sshl_sshr'.
Generating RTLIL representation for module `\_90_shift_shiftx'.
Generating RTLIL representation for module `\_90_fa'.
Generating RTLIL representation for module `\_90_lcu_brent_kung'.
Generating RTLIL representation for module `\_90_alu'.
Generating RTLIL representation for module `\_90_macc'.
Generating RTLIL representation for module `\_90_alumacc'.
Generating RTLIL representation for module `\$__div_mod_u'.
Generating RTLIL representation for module `\$__div_mod_trunc'.
Generating RTLIL representation for module `\_90_div'.
Generating RTLIL representation for module `\_90_mod'.
Generating RTLIL representation for module `\$__div_mod_floor'.
Generating RTLIL representation for module `\_90_divfloor'.
Generating RTLIL representation for module `\_90_modfloor'.
Generating RTLIL representation for module `\_90_pow'.
Generating RTLIL representation for module `\_90_pmux'.
Generating RTLIL representation for module `\_90_demux'.
Generating RTLIL representation for module `\_90_lut'.
Successfully finished Verilog frontend.

2.39.2. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/cells_map.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/cells_map.v' to AST representation.
Generating RTLIL representation for module `\$__SHREG_'.
Generating RTLIL representation for module `\$__XILINX_SHREG_'.
Generating RTLIL representation for module `\$__XILINX_MUXF78'.
Successfully finished Verilog frontend.

2.39.3. Continuing TECHMAP pass.
No more expansions possible.
<suppressed ~78 debug messages>

2.40. Executing DFFLEGALIZE pass (convert FFs to types supported by the target).

2.41. Executing OPT_EXPR pass (perform const folding).
Optimizing module blinky.

2.42. Executing ABC pass (technology mapping using ABC).

2.42.1. Extracting gate netlist of module `\blinky' to `<abc-temp-dir>/input.blif'..
Extracted 1 gates and 2 wires to a netlist network with 1 inputs and 1 outputs.

2.42.1.1. Executing ABC.
Running ABC command: "<yosys-exe-dir>/yosys-abc" -s -f <abc-temp-dir>/abc.script 2>&1
ABC: ABC command line: "source <abc-temp-dir>/abc.script".
ABC: 
ABC: + read_blif <abc-temp-dir>/input.blif 
ABC: + read_lut <abc-temp-dir>/lutdefs.txt 
ABC: + strash 
ABC: + &get -n 
ABC: + &fraig -x 
ABC: + &put 
ABC: + scorr 
ABC: Warning: The network is combinational (run "fraig" or "fraig_sweep").
ABC: + dc2 
ABC: + dretime 
ABC: + strash 
ABC: + dch -f 
ABC: + if 
ABC: + mfs2 
ABC: + write_blif <abc-temp-dir>/output.blif 

2.42.1.2. Re-integrating ABC results.
ABC RESULTS:              $lut cells:        1
ABC RESULTS:        internal signals:        0
ABC RESULTS:           input signals:        1
ABC RESULTS:          output signals:        1
Removing temp directory.
Removed 0 unused cells and 2 unused wires.

2.43. Executing TECHMAP pass (map to technology primitives).

2.43.1. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/ff_map.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/ff_map.v' to AST representation.
Generating RTLIL representation for module `\$_DFFE_NP0P_'.
Generating RTLIL representation for module `\$_DFFE_PP0P_'.
Generating RTLIL representation for module `\$_DFFE_NP1P_'.
Generating RTLIL representation for module `\$_DFFE_PP1P_'.
Generating RTLIL representation for module `\$_DFFSRE_NPPP_'.
Generating RTLIL representation for module `\$_DFFSRE_PPPP_'.
Generating RTLIL representation for module `\$_SDFFE_NP0P_'.
Generating RTLIL representation for module `\$_SDFFE_PP0P_'.
Generating RTLIL representation for module `\$_SDFFE_NP1P_'.
Generating RTLIL representation for module `\$_SDFFE_PP1P_'.
Generating RTLIL representation for module `\$_DLATCH_NP0_'.
Generating RTLIL representation for module `\$_DLATCH_PP0_'.
Generating RTLIL representation for module `\$_DLATCH_NP1_'.
Generating RTLIL representation for module `\$_DLATCH_PP1_'.
Generating RTLIL representation for module `\$_DLATCH_NPP_'.
Generating RTLIL representation for module `\$_DLATCH_PPP_'.
Successfully finished Verilog frontend.

2.43.2. Continuing TECHMAP pass.
Using template $paramod\$_SDFFE_PP0P_\_TECHMAP_WIREINIT_Q_=1'0 for cells of type $_SDFFE_PP0P_.
Using template $paramod\$_SDFFE_PP0P_\_TECHMAP_WIREINIT_Q_=1'x for cells of type $_SDFFE_PP0P_.
No more expansions possible.
<suppressed ~65 debug messages>

2.44. Executing XILINX_SRL pass (Xilinx shift register extraction).

2.45. Executing TECHMAP pass (map to technology primitives).

2.45.1. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/lut_map.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/lut_map.v' to AST representation.
Generating RTLIL representation for module `\$lut'.
Successfully finished Verilog frontend.

2.45.2. Executing Verilog-2005 frontend: /usr/local/bin/../share/yosys/xilinx/cells_map.v
Parsing Verilog input from `/usr/local/bin/../share/yosys/xilinx/cells_map.v' to AST representation.
Generating RTLIL representation for module `\$__SHREG_'.
Generating RTLIL representation for module `\$__XILINX_SHREG_'.
Generating RTLIL representation for module `\$__XILINX_MUXF78'.
Successfully finished Verilog frontend.

2.45.3. Continuing TECHMAP pass.
Using template $paramod\$lut\WIDTH=32'00000000000000000000000000000001\LUT=2'01 for cells of type $lut.
No more expansions possible.
<suppressed ~20 debug messages>

2.46. Executing XILINX_DFFOPT pass (optimize FF control signal usage).
Optimizing FFs in blinky.

2.47. Executing OPT_LUT_INS pass (discard unused LUT inputs).
Optimizing LUTs in blinky.

2.48. Executing CLKBUFMAP pass (inserting clock buffers).
Inserting BUFG on blinky.$iopadmap$clk[0].
Removed 0 unused cells and 152 unused wires.

2.49. Executing HIERARCHY pass (managing design hierarchy).
Attribute `top' found on module `blinky'. Setting top module to blinky.

2.49.1. Analyzing design hierarchy..
Top module:  \blinky

2.49.2. Analyzing design hierarchy..
Top module:  \blinky
Removed 0 unused modules.

2.50. Printing statistics.

=== blinky ===

   Number of wires:                  9
   Number of wire bits:            101
   Number of public wires:           3
   Number of public wire bits:      26
   Number of ports:                  2
   Number of port bits:              2
   Number of memories:               0
   Number of memory bits:            0
   Number of processes:              0
   Number of cells:                 35
     BUFG                            1
     CARRY4                          6
     FDRE                           25
     IBUF                            1
     INV                             1
     OBUF                            1

   Estimated number of LCs:          0

2.51. Executing CHECK pass (checking for obvious problems).
Checking module blinky...
Found and reported 0 problems.

End of script. Logfile hash: 8f297e2860, CPU: user 1.28s system 0.02s, MEM: 131.02 MB peak
Yosys 0.52+104 (git sha1 3d1f2161d, clang++ 15.0.7 -fPIC -O3)
Time spent: 86% 19x read_verilog (1 sec), 3% 1x synth_xilinx (0 sec), ...
```
