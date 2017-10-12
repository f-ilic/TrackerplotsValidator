# Trackerplots Validator

## Overview

The purpose of this tool is to
   * Generate local harvested files of DQMIO files that can be located through https://cmsweb.cern.ch/das/. das_client.py is used to find all corresponding resources to a configuration.
   * Compare plots from two harvested files and calculate a similarity measure


If you are executing this remotely (e.g. lxplus) make sure to ssh with -Y/-X so that X11 is being forwarded so that you can view the resulting output plots.

## How to run the code
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
./run.sh <src1> <src2> ... <srcX>
```
The call to <code>./run.sh</code> could look like

```
./run.sh "/RelValSingleMuPt10/CMSSW_9_3_0_pre3-92X_upgrade2017_realistic_v10_resub-v1/DQMIO" "/RelValSingleMuPt10/CMSSW_9_3_0_pre5-93X_mc2017_realistic_v2-v1/DQMIO"
```
To find the correct DQMIO name you can browse https://cmsweb.cern.ch/das/ .


All the sources passed as parameters <code>src1, src2, ... srcX</code> will be opened and harvested. The outputs produced will have the name format <code>harvested_1, harvested_2, ... harvested_X</code> and will be saved in the folder <code>run.sh</code> has been called from.
<code>src1</code> will be displayed as <b>Reference</b> and <code>src2</code> as <b>Current</b>.

If 2 files were given as input, the TrackermapsValidator will start up with the two datasets preloaded.
If not, you are prompted to select a <b>Reference</b> and the <b>Current</b> ROOT file and click on "Create Comparison Plot".


If you already have harvested files that you want to compare its enough just to call
```
root -x TrackermapsValidator.C
```

You can also pass the two files as parameters
```
root -x 'TrackermapsValidator.C("harvested_1.root", "harvested_2.root")'
```

## Validation

Once in the GUI and the ROOT files are loaded, just proceed by clicking "Create Comparison Plots". This will result in a canvas containing the few plots useful for validation.

<img src="https://raw.githubusercontent.com/imKuehlschrank/TrackerplotsValidator/master/doc/demo.png" width="500">

Additionally console output showing the similarity between the two files for each plot is generated, e.g.

```
=========================== Summary ===========================
Reference: 	/afs/cern.ch/user/f/filic/TrackerplotsValidator/harvested_1.root
Current: 	/afs/cern.ch/user/f/filic/TrackerplotsValidator/harvested_2.root

[ OK ] 98% similarity 	Summary_ClusterStoNCorr_OnTrack__TOB
[ OK ] 98% similarity 	Summary_ClusterStoNCorr_OnTrack__TIB
[ OK ] 98% similarity 	Summary_ClusterStoNCorr_OnTrack__TEC__MINUS
[ OK ] 97% similarity 	Summary_ClusterStoNCorr_OnTrack__TID__PLUS
[ OK ] 98% similarity 	charge_PXBarrel
[ OK ] 98% similarity 	charge_PXForward

===============================================================

```

The <code>[ OK ] / [FAIL]</code> message is a simple thresholding if the similarity between Refrence and Current is greater than 95%.

Intersection similarity is used as the similarity measure;

<img src="https://raw.githubusercontent.com/imKuehlschrank/TrackerplotsValidator/master/doc/similarity.png">

This is useful for assesing at a quick glance if everything is ok, without having to look at the plots themselves.

Additionally the plot is saved as <code>output.png</code>. If you need another format save the plots directly from the canvas <code>"Save as..."</code> (pdf).

## Adding new plots

To add new plots modify the variables
```
plot_names
plot_dirs
```
in the function <code>Validator::initResources()</code>

<code>plot_names</code> and <code>plot_dirs</code> <b>must</b> have the same number of elements since <code>plot_dirs[i] + plot_names[i]</code> is the path of one resource in the DQM file.

Additionally you might have to change the number of subplot-splits by adjusting
```
void Validator::createComparisonPlots() {
   ...
   // change this if you are adding/removing plots //
   resultCanvas->Divide(2, 3); // 2 columns, 3 rows
   ...
}
```

## What does run.sh do?

The whole pipeline is run with <code>run.sh</code>.

The first step there is to find the individual files belonging to the configuration name. This is done with <code>das_client.py --query</code>. This yields a list of filenames which are then passed to <code>harvesting.py</code> which generates the harvested files. These files are then opened with <code>root -x TrackerplotsValidator.C</code> where the plots are displayed.
