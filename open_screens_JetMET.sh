#!/bin/bash

#example: ./open_screens_JetMET.sh 

era="C"
version="v4"

for dataset in {0..1}
do
    for no in {1..10}
    do
	    screen -S list_JetMET"$dataset"_era"$era"_"$version"_"$no"of10 -dm bash -c "sleep 5; cmsenv; source runjob_JetMET.sh $no $era $dataset $version; exec bash"
    done
done
