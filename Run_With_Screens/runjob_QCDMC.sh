
export SCRAM_ARCH=slc7_amd64_gcc11
source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 runtime -sh`

no=$1
pTbin=$2


./main lists/2022_QCDMC/list_Run3Summer22EE_PT-"$pTbin"_"$no"of10.txt config/cutFile_4jets_AK4PUPPI_MC.txt dijets/events /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22EE/Summer22EERun3_V1_JECs/QCD_PT-"$pTbin"_TuneCP5_13p6TeV_pythia8__Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1_ext1-v2__AK4PUPPI_"$no"of10 /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22EE/Summer22EERun3_V1_JECs/QCD_PT-"$pTbin"_TuneCP5_13p6TeV_pythia8__Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1_ext1-v2__AK4PUPPI_"$no"of10


#./main lists/2022_QCDMC/list_Run3Summer22_PT-"$pTbin"_"$no"of10.txt config/cutFile_4jets_AK4PUPPI_MC.txt dijets/events /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22/Summer22Run3_V1_JECs/QCD_PT-"$pTbin"_TuneCP5_13p6TeV_pythia8__Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12_ext1-v2__AK4PUPPI_"$no"of10 /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22/Summer22Run3_V1_JECs/QCD_PT-"$pTbin"_TuneCP5_13p6TeV_pythia8__Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12_ext1-v2__AK4PUPPI_"$no"of10
