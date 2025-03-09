# XTensa ISA


- [ ] [ESP32 instruction set or assembly (ASM) programming docs?](https://esp32.com/viewtopic.php?t=17549)
  
  > For what it's worth, the ESP32-C3 will have a RiscV ISA which is fully documented. If that chip fits your specs, you could decide to wait until that is released.

- [ ] [Xtensa® Instruction Set Architecture (ISA) Summary](https://www.cadence.com/content/dam/cadence-www/global/en_US/documents/tools/ip/tensilica-ip/isa-summary.pdf) [:roll_of_paper: isa-summary.pdf](docs/isa-summary.pdf)
- [ ] [Xtensa® Instruction Set Architecture (ISA)](https://0x04.net/~mwk/doc/xtensa.pdf) [:roll_of_paper: isa-summary.pdf](docs/xtensa.pdf)

- [ ] [XTensa TIE Documentation](https://community.cadence.com/cadence_technology_forums/f/digital-implementation/57721/xtensa-tie-documentation) TIE Language—The Fast Path to High-Performance Embedded SoC Processing

While using custom [RTL](https://en.wikipedia.org/wiki/Register-transfer_level) accelerator blocks in data-intensive functions can provide high performance,
they may require long design and verification cycle times. As an alternative, processor-based designs
can reduce time-to-market and improve design flexibility while still achieving reasonable performance.
Optimizing Cadence® Tensilica® Xtensa® processors with new instructions and additional bandwidth
using the `Tensilica Instruction Extension` (TIE) language enables you to compute and move data tens
or hundreds of times faster than conventional processors, resulting in an SoC that is smaller, cheaper,
faster, and consumes less energy. This white paper introduces the easy-to-use TIE language—which
is `similar to Verilog—as` well as TIE techniques for accelerating computation and communication in an
Xtensa processor.


## Assembly Code

[xtensa_vectors.S](https://github.com/espressif/esp-idf/blob/master/components/xtensa/xtensa_vectors.S)
