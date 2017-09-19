# Trackerplots Validator

## Overview

This tool is to meant to quickly assess if new CMSSW releases broke the generated plots.
This is done by comparing a selection of plots from a reference DQM ROOT to a file created with the CMSSW release in question.

## How to run
Example:
```
cmsrel CMSSW_9_3_0
cd CMSSW_9_3_0
cmsenv
cd ../

voms-proxy-init -voms cms

git clone git@github.com:imKuehlschrank/TrackerplotsValidator.git
cd TrackerplotsValidator
chmod +x run.sh
./run.sh <ref> <cur>
```
The call to <code>./run.sh</code> could look for example like

```
./run.sh "/RelValSingleMuPt10/CMSSW_9_3_0_pre3-92X_upgrade2017_realistic_v10_resub-v1/DQMIO" "/RelValSingleMuPt10/CMSSW_9_3_0_pre5-93X_mc2017_realistic_v2-v1/DQMIO"
```
To find the correct DQMIO name you can browse https://cmsweb.cern.ch/das/ .


This starts the program which first pools file names together which are then harvested. After all of that is done you are prompted you to select a <b>Reference</b> and the <b>Current</b> ROOT file. Here you select the output files that were just generated.
(If you are executing this remotely e.g. lxplus, make sure to ssh with -Y/-X so that X11 is being forwarded).

## Validation

Once in the GUI and the ROOT files are loaded, just proceed by clicking "Create Comparison Plots". This will result in a canvas containing the few plots useful for validation.

<img src="https://raw.githubusercontent.com/imKuehlschrank/TrackerplotsValidator/master/doc/demo.png" width="500">

Furthermore an output in the console is generated that looks something like

```
=========================== Summary ===========================
Reference: 	/afs/cern.ch/user/f/filic/TrackerplotsValidator/harvested_1.root
Current: 	/afs/cern.ch/user/f/filic/TrackerplotsValidator/harvested_2.root

[ OK ] 98% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TOB
[ OK ] 98% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TIB
[ OK ] 98% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TEC__MINUS
[ OK ] 97% intersection similarity 	Summary_ClusterStoNCorr_OnTrack__TID__PLUS
[ OK ] 98% intersection similarity 	charge_PXBarrel
[ OK ] 98% intersection similarity 	charge_PXForward

===============================================================

```

The [ OK ] / [FAIL] message is a simple thresholding if the similarity between Refrence and Current is greater than 95%.

This is useful for assesing at a quick glance if everything is ok, without having to look at the plots themselves.
Saving the canvas is done easily with "Save as..." (pdf).


## Adding new plots

To add new plots modify the variables
```
plot_names
plot_dirs
```
in the function <code>Validator::initResources()</code>


There is a 1 to 1 correspondance from <code>plot_names</code> to <code>plot_dirs</code>, since <code>plot_dirs[i] + plot_names[i]</code> is one full path for a file in the DQM ROOT file. Therefore there must always be the same number of elements in both vectors.
