
export SCRAM_ARCH=slc7_amd64_gcc11
source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 runtime -sh`

Suu=$1
Chi=$2

./main lists/Suu_Diquark_signals/Run3Summer22EE/list_Run3Summer22EE_S"$Suu"_chi"$Chi".txt config/cutFile_4jets_AK4PUPPI_MC.txt dijets/events /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/signal_diquarks/Run3Summer22EE/Summer22EE_V1_JECs/Run3Summer22EE_Suu_Diquark_S"$Suu"_chi"$Chi"__AK4PUPPI /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/signal_diquarks/Run3Summer22EE/Summer22EE_V1_JECs/Run3Summer22EE_Suu_Diquark_S"$Suu"_chi"$Chi"__AK4PUPPI

