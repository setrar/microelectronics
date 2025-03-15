%%% Post-processing Code for Qucs
%%% Eindhoven Unversity of Technology
%%% Authors: Prof. Dr. Peter Baltus
%%%          Dr. Carlos Mendes Jr.
%%% Circuit: S-Parameter Test Bench

%%%   SYSTEM STARTUP   %%%

% Initialize
clear all; close all; clc;

% Add path for Qucs handling functions (Use / instead of \)
addpath ("E:/Program Files/Qucs-S/share/qucs-s/octave");

%%%   SIMULATION   %%%

% Set and show available data
File      = mfilename;
Data      = [File '.dat.ngspice']; 
qdset     = loadQucsDataSet(Data);
showQucsDataSet(qdset);

# Extract variables from the Qucs simulation
[freq]    = loadQucsVariable(Data,"frequency");
[S11]     = 20*log10(abs(loadQucsVariable(Data,"ac.v(ns11)")));
[S12]     = 20*log10(abs(loadQucsVariable(Data,"ac.v(ns12)")));
[S21]     = 20*log10(abs(loadQucsVariable(Data,"ac.v(ns21)")));
[S22]     = 20*log10(abs(loadQucsVariable(Data,"ac.v(ns22)")));

# Load graphic toolkit
available_graphics_toolkits();
graphics_toolkit();
graphics_toolkit("gnuplot");

# Plot SP data from Qucs into Octave
figure;
subplot(2, 2, 1)
semilogx(freq,S11,"color","blue", "linewidth", 1);
grid on;
title("S11");
subplot(2, 2, 2)
semilogx(freq,S12,"color","blue", "linewidth", 1);
grid on;
title("S12")
subplot(2, 2, 3)
semilogx(freq,S21,"color","blue", "linewidth", 1);
grid on;
title("S21")
subplot(2, 2, 4)
semilogx(freq,S22,"color","blue", "linewidth", 1);
grid on;
title("S22")
