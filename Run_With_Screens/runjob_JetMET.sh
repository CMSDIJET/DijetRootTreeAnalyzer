
export SCRAM_ARCH=slc7_amd64_gcc11
source /afs/cern.ch/cms/cmsset_default.sh
eval `scramv1 runtime -sh`

no=$1
era=$2
dataset=$3
version=$4

./main lists/2023_promptreco/list_JetMET"$dataset"_Run2022"$era"-PromptReco-"$version"_"$no"of10.txt config/cutFile_4jets_AK4PUPPI.txt dijets/events /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/2023/Winter23Prompt23_V1_MC_08June2023/JetMET"$dataset"__Run2023"$era"-PromptReco-"$version"__AK4PUPPI_"$no"of10 /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/2023/Winter23Prompt23_V1_MC_08June2023/JetMET"$dataset"__Run2023"$era"-PromptReco-"$version"__AK4PUPPI_"$no"of10
