# Trackervalidation Plots

## Overview

This tool is to meant to quickly asses if new CMSSW releases broke the generated plots.
This is done by comparing a selection of plots from a reference ROOT file with a newly generated ones, created with the CMSSW release in question.

## How to run

Either start through root... cmd here
From there on a GUI will start from which you can select the two ROOT files that you want to compare.

As another option it is possible to pass 2 commandline parameters. This just preloads the data so that one does not have to navigate the file-open dialog.
An example of such a call would look like
> TrackerplotsValidator /home/user/desktop/pre3.root /home/user/desktop/pre4.root

## Validation

Once in the GUI and the ROOT files are loaded, just proceed by clicking "Create Comparison Plots". This will result in a canvas containing the few plots useful for validation.
IMAGE HERE

Furthermore an output in the console is produced that looks something like 

=========================== Summary =========================== 

[ OK ] with 99% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TOB
[ OK ] with 98% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TIB
[ OK ] with 99% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TEC__MINUS
[ OK ] with 99% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TID__PLUS
[ OK ] with 98% intersection similarity 	Cluster Charge

=============================================================== 


This is useful for assesing at a quick glance if everything is ok, without having to look at the plots themselves.


If the result plots ought to be shared, one can "Save As..." on the canvas containing the plots, and save as pdf, etc.


## Adding new plots

If new plots should be added to the result plot view this is done by modifying

plot_names, plot_dirs 

variables in the source.

There is a 1 to 1 correspondance from plot_names to plot_dirs, since plot_dirs[i] + plot_names[i] constitues full path for a file in the DQM ROOT file. 


