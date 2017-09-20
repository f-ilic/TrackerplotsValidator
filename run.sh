#!/bin/sh


# take input file query and find all the corresponding datasets
# this means that for each queried resource there may be multiple
# files. These files are collected in $LIST, which are then passed
# to the harvesting script.
COUNTER=1
for var in $@
do
    LIST="$(das_client.py --query="file dataset=$var" | grep /store)"
    cmsRun harvesting.py $LIST
    mv DQM_V0001_R000000001__Global__CMSSW_X_Y_Z__RECO.root harvested_$COUNTER.root
    COUNTER=$[$COUNTER +1]
done


# Show as what the output files are saved.
# I decided against just a pre/postfix to the name of the input file, since the 
# filenames/paths are very long, e.g.:
# /RelValSingleMuPt10/CMSSW_9_3_0_pre3-92X_upgrade2017_realistic_v10_resub-v1/DQMIO
echo '\n\n=============================== Summary ==============================='
COUNTER=1
for var in $@
do
    echo "harvested_$COUNTER.root <== $var"
    COUNTER=$[$COUNTER +1]
done
echo '======================================================================='


# after all the dqm data has been harvested we start the
# validator. If exactly two input sources were specified we assume
# the user wants to compare <src1> to <src2>.
if [ "$#" -eq 2 ]; then
   root -x 'TrackerplotsValidator.C("harvested_1.root","harvested_2.root")'
else
	root -x TrackerplotsValidator.C
fi
