#!/bin/bash

#example: ./open_screens_JetMET.sh 

era="C"

for no in {1..10}
do
	screen -S list_JetHT_era"$era"_"$no" -dm bash -c "sleep 5; cmsenv; source runjob_JetMET.sh $no $era; exec bash"
done
