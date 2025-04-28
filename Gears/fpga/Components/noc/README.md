# NOC

In many 5G baseband SoCs (especially those designed for base stations, RUs, DUs, or even some high-end UE chips), **there is an internal Network-on-Chip (NoC)** that interconnects different IP blocks:  
- **Modem blocks** (e.g., LDPC encoder/decoder, polar coder/decoder)  
- **Massive MIMO processing units**  
- **Beamforming engines**  
- **Radio front-end control units**  
- **Packet processing engines** (for 5G NR over Ethernet, fronthaul like eCPRI)  
- **CPUs and accelerators (AI, PHY processing, etc.)**  

In those cases, the **5G baseband SoC** has **an embedded NoC** — but the **5G standard itself** doesn't say "use a NoC"; it's just **a practical design choice** for high-throughput chips.

🔹 **Examples of 5G components that may have an embedded NoC:**  
- Qualcomm's Snapdragon X-series modems  
- Marvell OCTEON Fusion chips  
- Intel and Nokia 5G FPGAs/ASICs  
- Xilinx/Zynq RFSoC devices (for 5G radio units)

In short:  
- **5G (as a technology)** does not *require* NoC, but  
- **5G chips (hardware implementations)** often *internally use* NoC to manage complexity, bandwidth, and parallelism.

<img src=images/NOC-explanation.png width='50%' height='50%' > </img>

# References

- [ ] [Network on Chip (NoC) with FPGAs|Part 1|Introduction](https://www.youtube.com/watch?v=iBAnGLZ6fMY)
- [ ] [Network on Chip (NoC) with FPGAs|Part 2|Design of a Torus NoC](https://www.youtube.com/watch?v=zVD0MJ00ZZQ)
