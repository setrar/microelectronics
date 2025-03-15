<Qucs Schematic 24.4.1>
<Properties>
  <View=66,425,1421,1254,0.819926,0,0>
  <Grid=10,10,1>
  <DataSet=SP_TestBench.dat>
  <DataDisplay=SP_TestBench.dpl>
  <OpenDisplay=0>
  <Script=SP_TestBench.m>
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
  <.AC AC1 1 970 710 0 31 0 0 "log" 1 "1e3" 1 "1e6" 1 "121" 1 "no" 0>
  <.DC DC1 1 970 610 0 31 0 0 "26.85" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "no" 0 "150" 0 "no" 0 "none" 0 "CroutLU" 0>
  <Sub S11_Probe1 1 250 530 -20 43 0 0 "S11_Probe.sch" 0 "50" 1>
  <S4Q_V V3 1 120 690 18 -26 0 1 "dc 0 ac 1" 1 "" 0 "" 0 "" 0 "" 0>
  <GND * 1 120 720 0 0 0 0>
  <R_SPICE R7 1 160 650 -24 -66 0 2 "50" 1 "" 0 "" 0 "" 0 "" 0 "2" 1 "R" 1>
  <Sub S21_Probe1 1 790 630 -60 -66 0 0 "S21_Probe.sch" 0 "50" 1>
  <R_SPICE R8 1 760 700 15 -26 0 1 "50" 1 "" 0 "" 0 "" 0 "" 0 "2" 1 "R" 1>
  <Sub S12_Probe1 1 230 860 -40 34 0 0 "S12_Probe.sch" 0 "50" 1>
  <GND * 1 170 1100 0 0 1 2>
  <R_SPICE R9 1 170 1070 26 -26 1 1 "50" 1 "" 0 "" 0 "" 0 "" 0 "2" 1 "R" 1>
  <R_SPICE R10 1 750 1030 -34 18 1 0 "50" 1 "" 0 "" 0 "" 0 "" 0 "2" 1 "R" 1>
  <Vac U1 1 780 1090 31 -40 1 1 "1 V" 1 "1 kHz" 1 "0" 0 "0" 0 "0" 0 "0" 0>
  <GND * 1 780 1120 0 0 1 2>
  <Sub S22_Probe1 1 760 910 -20 44 0 0 "S22_Probe.sch" 0 "50" 1>
  <GND * 1 760 740 0 0 0 0>
  <GND * 1 1200 780 0 0 0 0>
  <Vdc V4 1 1200 750 18 -26 0 1 "5 V" 1>
  <GND * 1 1300 780 0 0 0 0>
  <Vdc V2 1 1300 750 18 -26 0 1 "15 V" 1>
  <Sub Amp_CS 1 270 620 155 58 0 0 "Amplifier_CS.sch" 0>
  <Sub Amp_CS1 1 270 1000 155 58 0 0 "Amplifier_CS.sch" 0>
  <NutmegEq StoZ_Conversion_Template1 1 980 1060 -27 19 0 0 "ac" 1 "StoZ_Z0=50.0" 1 "StoZ_DelSxZ0=(  (1-V(nS11))*(1-V(nS22))-V(nS12)*V(nS21)  )/StoZ_Z0" 1 "Z11=(  (1+V(nS11))*(1-V(nS22))+V(nS12)*V(nS21) )/StoZ_DelSxZ0" 1 "Z12=2*V(nS12)/StoZ_DelSxZ0" 1 "Z21=2*V(nS21)/StoZ_DelSxZ0" 1 "Z22=((1-V(nS11))*(1+V(nS22))+V(nS12)*V(nS21))/StoZ_DelSxZ0" 1>
  <Sub Amp_CD 1 570 650 -35 28 0 0 "Amplifier_CD.sch" 0>
  <Sub Amp_CD1 1 560 1030 -35 28 0 0 "Amplifier_CD.sch" 0>
</Components>
<Wires>
  <190 550 190 650 "" 0 0 0 "">
  <120 650 130 650 "" 0 0 0 "">
  <120 650 120 660 "" 0 0 0 "">
  <710 650 760 650 "" 0 0 0 "">
  <710 550 710 650 "" 0 0 0 "">
  <760 650 760 670 "" 0 0 0 "">
  <170 880 170 1030 "" 0 0 0 "">
  <780 1030 780 1060 "" 0 0 0 "">
  <710 930 720 930 "" 0 0 0 "">
  <710 1030 720 1030 "" 0 0 0 "">
  <710 930 710 1030 "" 0 0 0 "">
  <760 730 760 740 "" 0 0 0 "">
  <170 1030 170 1040 "" 0 0 0 "">
  <190 650 430 650 "" 0 0 0 "">
  <170 1030 430 1030 "" 0 0 0 "">
  <600 650 710 650 "" 0 0 0 "">
  <490 650 540 650 "" 0 0 0 "">
  <570 580 570 610 "" 0 0 0 "">
  <590 1030 710 1030 "" 0 0 0 "">
  <490 1030 530 1030 "" 0 0 0 "">
  <560 960 560 990 "" 0 0 0 "">
  <1200 690 1200 720 "" 0 0 0 "">
  <1300 690 1300 720 "" 0 0 0 "">
  <460 580 460 610 "" 0 0 0 "">
  <460 960 460 990 "" 0 0 0 "">
  <310 550 310 550 "nS11" 320 520 0 "">
  <830 550 830 550 "nS21" 830 510 0 "">
  <290 880 290 880 "nS12" 300 840 0 "">
  <840 930 840 930 "nS22" 840 890 0 "">
  <570 580 570 580 "VCC_15" 600 540 0 "">
  <560 960 560 960 "VCC_15" 590 920 0 "">
  <1200 690 1200 690 "VCC_5" 1210 650 0 "">
  <1300 690 1300 690 "VCC_15" 1310 650 0 "">
  <460 580 460 580 "VCC_5" 470 550 0 "">
  <460 960 460 960 "VCC_5" 470 930 0 "">
</Wires>
<Diagrams>
</Diagrams>
<Paintings>
  <Text 440 730 12 #000000 0 "S11 and S21 Test bench">
  <Rectangle 370 520 310 200 #ff0000 2 1 #c0c0c0 1 0>
  <Text 420 480 20 #ff0000 0 "Device Under Test">
  <Text 640 620 12 #ff0000 0 "OUT">
  <Text 380 620 12 #ff0000 0 "IN">
  <Rectangle 370 900 310 200 #ff0000 2 1 #c0c0c0 1 0>
  <Text 420 860 20 #ff0000 0 "Device Under Test">
  <Text 640 1000 12 #ff0000 0 "OUT">
  <Text 380 1000 12 #ff0000 0 "IN">
  <Text 960 510 12 #000000 0 "Based on:\nhttps://qucs-help.readthedocs.io/en/spice4qucs/RF.html">
  <Text 960 470 16 #000000 0 "S-Parameter Test Bench">
  <Rectangle 950 600 180 270 #000000 0 1 #c0c0c0 1 0>
  <Text 960 570 16 #000000 0 "Simulation Setup">
  <Rectangle 1170 600 210 270 #000000 0 1 #c0c0c0 1 0>
  <Text 1170 570 16 #000000 0 "Power Supply">
  <Rectangle 950 500 430 60 #000000 0 1 #c0c0c0 1 0>
  <Text 450 1110 12 #000000 0 "S22 and S12 Test bench">
  <Rectangle 950 890 270 140 #000000 0 1 #c0c0c0 1 0>
  <Text 960 890 12 #000000 0 "RF and millimeter-wave circuit design \nEindhoven University of Technology\nDepartment of Electrical Engineering\nIntegrated Circuits Group\n\ndr. Carlos Mendes Jr \nprof. dr. ir. Peter Baltus \nprof. dr. Marion Matters ">
</Paintings>
