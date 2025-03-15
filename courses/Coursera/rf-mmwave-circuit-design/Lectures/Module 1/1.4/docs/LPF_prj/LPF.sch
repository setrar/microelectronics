<Qucs Schematic 24.4.1>
<Properties>
  <View=257,143,951,553,1.61671,0,0>
  <Grid=10,10,1>
  <DataSet=LPF.dat>
  <DataDisplay=LPF.dpl>
  <OpenDisplay=1>
  <Script=LPF.m>
  <RunScript=1>
  <showFrame=0>
  <FrameText0=Title>
  <FrameText1=Drawn By:>
  <FrameText2=Date:>
  <FrameText3=Revision:>
</Properties>
<Symbol>
</Symbol>
<Components>
  <GND * 1 690 280 0 0 0 0>
  <GND * 1 360 280 0 0 0 0>
  <C C1 1 690 250 17 -26 0 1 "CL" 1 "" 0 "neutral" 0>
  <R R1 1 530 220 -26 15 0 0 "RS" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <Vac V1 1 360 250 18 -26 0 1 "1 V" 1 "200 MHz" 1 "0" 0 "0" 0 "0" 0 "0" 0>
  <.TR TR1 1 310 380 0 50 0 0 "lin" 1 "0" 1 "50 ns" 1 "50" 0 "Trapezoidal" 0 "2" 0 "1 ns" 0 "1e-16" 0 "150" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "26.85" 0 "1e-3" 0 "1e-6" 0 "1" 0 "CroutLU" 0 "no" 0 "yes" 0 "0" 0>
  <.AC AC1 1 470 380 0 31 0 0 "log" 1 "1 kHz" 1 "1 GHz" 1 "301" 1 "no" 0>
  <Eqn Variables 1 880 220 -30 16 0 0 "RS=1 kOhm" 1 "CL=1 pF" 1 "yes" 0>
  <NutmegEq PostProcessing 0 690 390 -26 16 0 0 "ac" 1 "TF=20*log10(abs(V(out)/V(in)))" 1>
</Components>
<Wires>
  <560 220 690 220 "out" 660 190 72 "">
  <360 220 500 220 "in" 450 190 61 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
