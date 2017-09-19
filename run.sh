#!/bin/sh

COUNTER=1
for var in $@
do
	LIST="$(das_client.py --query="file dataset=$var" | grep /store)"
    cmsRun harvesting.py $LIST
    mv DQM_V0001_R000000001__Global__CMSSW_X_Y_Z__RECO.root harvested_$COUNTER.root
    COUNTER=$[$COUNTER +1]
done



echo '=============================== Summary ==============================='
COUNTER=1
for var in $@
do
    echo "Saving $var as harvested_$COUNTER.root"
    COUNTER=$[$COUNTER +1]
done

root -x TrackerplotsValidator.C