#!/bin/sh

cd /afs/cern.ch/work/z/zhixing/private/CMSSW_7_4_14/src/CMSDIJET/DijetRootTreeAnalyzer/GetMass_2016/unfinished/

eval `scramv1 runtime -sh`

python GetMass.py -i filelist_27.txt -o /tmp/outputt_27.root

mv /tmp/outputt_27.root /afs/cern.ch/work/z/zhixing/private/CMSSW_7_4_14/src/CMSDIJET/DijetRootTreeAnalyzer/GetMass_2016/unfinished/

