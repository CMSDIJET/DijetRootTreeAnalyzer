#!/bin/bash

#example: ./open_screens_Muon.sh

era="B"

for no in {1..10}
do
	screen -S list_SingleMuon_era"$era"_"$no" -dm bash -c "sleep 5; cmsenv; source runjob_Muon.sh $no $era; exec bash"
done	
