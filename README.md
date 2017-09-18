# Trackerplots Validator

## Overview

This tool is to meant to quickly assess if new CMSSW releases broke the generated plots.
This is done by comparing a selection of plots from a reference DQM ROOT to a file created with the CMSSW release in question.

## How to run
Assuming that you are on lxplus:
<code>
git clone git@github.com:imKuehlschrank/TrackerplotsValidator.git
</code>

<code>
cd TrackerplotsValidator
</code>

<code>
root -x TrackerplotsValidator.C
</code>


On your own machine with ROOT installed:
<code>
git clone git@github.com:imKuehlschrank/TrackerplotsValidator.git
</code>

<code>
cd TrackerplotsValidator
</code>

<code>
/path/to/root -x TrackerplotsValidator.C
</code>


This starts the program prompting you to select a <b>Reference</b> and the <b>Current</b> ROOT file.

## Validation

Once in the GUI and the ROOT files are loaded, just proceed by clicking "Create Comparison Plots". This will result in a canvas containing the few plots useful for validation.

<img src="https://raw.githubusercontent.com/imKuehlschrank/TrackerplotsValidator/master/doc/demo.png" width="200">

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
