# Trackerplots Validator

## Overview

This tool is to meant to quickly assess if new CMSSW releases broke the generated plots.
This is done by comparing a selection of plots from a reference DQM ROOT to a file created with the CMSSW release in question.

## How to run
```
git clone git@github.com:imKuehlschrank/TrackerplotsValidator.git
cd TrackerplotsValidator
root -x TrackerplotsValidator.C
```

This starts the program prompting you to select a <b>Reference</b> and the <b>Current</b> ROOT file.
(If you are executing this remotely e.g. lxplus, make sure to ssh with -Y/-X so that X11 is being forwarded)

## Validation

Once in the GUI and the ROOT files are loaded, just proceed by clicking "Create Comparison Plots". This will result in a canvas containing the few plots useful for validation.

<img src="https://raw.githubusercontent.com/imKuehlschrank/TrackerplotsValidator/master/doc/demo.png" width="500">

Furthermore an output in the console is generated that looks something like 

```
=========================== Summary =========================== 
Reference: 	/home/fil/projects/TrackerplotsValidator/pre3.root
Current: 	/home/fil/projects/TrackerplotsValidator/pre5.root

[ OK ] 99% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TOB
[ OK ] 98% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TIB
[ OK ] 99% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TEC__MINUS
[ OK ] 99% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TID__PLUS
[ OK ] 98% intersection similarity 	Cluster Charge
[ OK ] 99% intersection similarity 	Cluster Charge

=============================================================== 

```

The [ OK ] / [FAIL] message is a simple thresholding if the similarity between Refrence and Current is greater than 95%.

This is useful for assesing at a quick glance if everything is ok, without having to look at the plots themselves.
Saving the canvas is done easily with "Save as..." (pdf).


## Adding new plots

If new plots should be added to the result plot view this is done by modifying
```
plot_names
plot_dirs 
```
in the function <code>Validator::initResources()</code>


There is a 1 to 1 correspondance from <code>plot_names</code> to <code>plot_dirs</code>, since <code>plot_dirs[i] + plot_names[i]</code> constitues full path for a file in the DQM ROOT file. Therefore there must always be the same number of elements in both vectors.
