#!/bin/bash

#example: ./open_screens_QCDMC.sh 

pTbin="1400to1800"

for no in {1,2,3,8,9,10}
    do
	    screen -S list_QCDMC_"$pTbin"_"$no"of10 -dm bash -c "sleep 5; cmsenv; source runjob_QCDMC.sh $no $pTbin; exec bash"
done
