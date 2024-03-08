
export SCRAM_ARCH=el9_amd64_gcc11
source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 runtime -sh`

width=$1
Suu=$2
Chi=$3

./main lists/Suu_Diquark_signals/RunIISummer20UL18MiniAODv2/list_W-"$width"_S-"$Suu"_chi-"$Chi"_big_list.txt config/cutFiles/cutFile_4jets_AK4CHS_MC.txt dijets/events /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/full_grid/RunIISummer20UL18_Suu-Diquark_W-"$width"_S-"$Suu"_chi-"$Chi"__AK4CHS /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/full_grid/RunIISummer20UL18_Suu-Diquark_W-"$width"_S-"$Suu"_chi-"$Chi"__AK4CHS

