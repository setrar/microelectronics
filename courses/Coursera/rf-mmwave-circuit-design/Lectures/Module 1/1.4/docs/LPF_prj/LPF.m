%%% Post-processing Code for Qucs
%%% Eindhoven Unversity of Technology
%%% Authors: Prof. Dr. Peter Baltus
%%%          Dr. Carlos Mendes Jr.
%%% Circuit: LPF

%%%   SYSTEM STARTUP   %%%

% Initialize
clear all; close all; clc;

%%%   SIMULATION   %%%

% Set and show available data
File      = 'LPF';
Data      = [File '.dat.ngspice'];
qdset     = loadQucsDataSet(Data);
showQucsDataSet(qdset);


