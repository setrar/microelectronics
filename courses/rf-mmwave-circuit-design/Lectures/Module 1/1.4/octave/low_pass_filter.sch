<Qucs Schematic 24.4.1>
<Properties>
  <View=67,66,709,445,1.74766,0,0>
  <Grid=10,10,1>
  <DataSet=low_pass_filter.dat>
  <DataDisplay=low_pass_filter.dpl>
  <OpenDisplay=0>
  <Script=low_pass_filter.m>
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
  <C C1 1 400 180 17 -26 0 1 "CL" 1 "" 0 "neutral" 0>
  <GND * 1 130 210 0 0 0 0>
  <GND * 1 400 210 0 0 0 0>
  <R R1 1 260 150 -26 15 0 0 "RS" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <Vac V1 1 130 180 18 -26 0 1 "1 V" 1 "100 MHz" 1 "0" 0 "0" 0 "0" 0 "0" 0>
  <.TR TR1 1 110 270 0 50 0 0 "lin" 1 "0" 1 "100 ns" 1 "50" 1 "Trapezoidal" 0 "2" 0 "1 ns" 0 "1e-16" 0 "150" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "26.85" 0 "1e-3" 0 "1e-6" 0 "1" 0 "CroutLU" 0 "no" 0 "yes" 0 "0" 0>
  <Eqn Variables 1 500 130 -23 14 0 0 "CL=1 pF" 1 "RS=1 KOhm" 1 "yes" 0>
  <NutmegEq PostProcessing 1 500 240 -21 14 0 0 "AC1" 1 "TF=20*log10(abs(V(out)/V(in)))" 1>
  <.AC AC1 1 250 270 0 31 0 0 "log" 1 "1 kHz" 1 "1 GHz" 1 "301" 1 "no" 0>
</Components>
<Wires>
  <290 150 400 150 "out" 342 120 54 "">
  <130 150 230 150 "in" 200 110 64 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
</Paintings>
