
export SCRAM_ARCH=slc7_amd64_gcc10
source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 runtime -sh`

no=$1
era=$2

./main lists/2022_promptreco/list_JetHT_Run2022"$era"-PromptReco-v1_"$no"of10.txt config/cutFile_4Jets/cutFile_4jets_AK4PUPPI_forTriggerEfficiency_JetMET.txt dijets/events /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/trigger_efficiency/2022_PromptReco/JetHT_Run2022"$era"-PromptReco-v1_"$no"of10 /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/trigger_efficiency/2022_PromptReco/JetHT_Run2022"$era"-PromptReco-v1_"$no"of10
