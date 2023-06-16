
This is a README to: 
1) create small lists for big tree inputs.
2)submit condor jobs in order to produce reduced trees for Data and MC.
3) check outputs, for trees that did not close correctly.



You must already have a CMSSW release installed and make sure that the analyzer is running without errors - lists, config files, analyzers all are assumed to be ready.


######################################### Create big tree lists ####################

./bash_scripts/create_small_lists.sh -path /eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/Run2017E-09Aug2019_UL2017-v1/JetHT/crab_JetHT__Run2017E-09Aug2019_UL2017-v1__MINIAOD/191028_095603/ -dir lists/UL_2017_data/ -name UL_2017_RunE -size 50


#########################################################################################################################################

This is a README to submit jobs in HT condor in order to produce reduced trees. The first part is for Data and the second for MC.

You must already have a CMSSW release installed and make sure that the analyzer is running without errors - lists, config files, analyzers all are assumed to be ready.


====================================================== Send condor jobs for Data  ======================================================

!!!!!Important NOTE: for data, you need to have a different .txt cutfile for each run so that condor gets the correct JSON files. 

Everything from now on will assume you are on the DijetRootTreeAnalyzer directory of your CMSSW release.

1) Make a directory named "Condor_Outputs" to store the log files of condor jobs.

mkdir Condor_Outputs

2) Set up the config information in the script "bas_scripts/create_list_config.sh"

Open the script. Inside it there are some config variables to be set for each big tree set.


This is what they look like in the script:


#########################################Config variables that need to be set right for set of big trees####################

Output_base_name="JetHT__Run2018A-17Sep2018-v1__MINIAOD"                                    <-- (e.g. of output: JetHT__Run2018A-17Sep2018-v1__MINIAOD_11_reduced_skim.root ) 

splitted_list_base_name="lists/Rereco_2018/RunA/JetHT__Run2018A-17Sep2018-v1__MINIAOD"      <-- (full name would be: JetHT__Run2018A-17Sep2018-v1__MINIAOD_21.txt)

cutFile="config/cutFile_mainDijetSelection_JetHT_Run2017A-17Nov2017-v1.txt"                 <-- The cutFile you are using.   

Release="CMSSW_10_1_5"                                                                      <-- The CMSSW release you are using

Release_local_path="/afs/cern.ch/work/d/dkarasav/public/CMSSW_10_1_5"                       <-- Your local path to the CMSSW release you run the reduced trees.

Analyzer="analysisClass_mainDijetSelection_cemf_lt_0p8.C"                                   <-- The analyzer you are using

Architecture="slc6_amd64_gcc630"                                                            <-- The architecture of the current release.


#####################################################################################################################



3) Run the "bash_scripts/Submit_many_condor_jobs.sh" script

./bash_scripts/Submit_many_condor_jobs.sh -i 0 -f 30 -dir /eos/cms/store/user/dkarasav/JetHT_Run2018-reReco_reduced_trees/JetHT__Run2018A-17Sep2018-v1__MINIAOD/ -log_dir Condor_Outputs/logs_JetHT__Run2018A-17Sep2018-v1__MINIAOD -job_time tomorrow

Explanation of arguments: 

 -i 'Number_of_first_list_to_be_submited'
 -f 'Number_of_last_list_to_be_submited'
 -dir 'Output_directory'
 -log_dir log_file_directory
 -job_time 'condor keyword for maximum time of job'

 choices for "job_time" keywords are: 
	espresso     = 20 minutes
	microcentury = 1 hour
	longlunch    = 2 hours
	workday      = 8 hours
	tomorrow     = 1 day
	testmatch    = 3 days
	nextweek     = 1 week



In this example lists from 0 to 30 will be produced and the output reduced trees would be stored at /eos/cms/store/user/dkarasav/JetHT_Run2018-reReco_reduced_trees/JetHT__Run2018A-17Sep2018-v1__MINIAOD/

The log files can be found at Condor_Outputs/logs_JetHT__Run2018A-17Sep2018-v1__MINIAOD


4) To make sure that the code will run you can use the "bash_scripts/Run_reduced_trees_locally.sh" to  run one list locally to see if everything is ok.


	Run the script as follows:
 
./bash_scripts/Run_reduce_trees_localy.sh -i 1 -dir local_run_test/ -log_dir Condor_Outputs/local_run/ 

This will run the defined list 1, and save the output on the "local_run_test" local directory. The configs will be found on Condor_Outputs/local_run/ directory.

	 If this works do step 4 to sumbit jobs in condor. 



====================================================== for MC big trees ======================================================

The idea is basically the same, but you can use pThat Bins arguments now. 


Everything from now on will assume you are on the DijetRootTreeAnalyzer directory of your CMSSW release.

1) Make a directory named "Condor_Outputs" to store the log files of condor jobs.

mkdir Condor_Outputs

2) Set up the config information in the script "create_list_config_MC.sh"

Set the configuration just like on data case, with one difference ( needs optimization ): 

The lists names are not set on the start, but in the line 64.

	For example, for my lists, with names: "lists/MC2017/QCD_Pt_50to80_TuneCP5_13TeV_pythia8_1.txt", "lists/MC2017/QCD_Pt_600to800_TuneCP5_13TeV_pythia8_5.txt", etc....

	I set it like this: 

	echo "list_name=\"lists/MC2017/QCD_Pt_"$PtHatBin_start"to"$PtHatBin_end"_TuneCP5_13TeV_pythia8_"$list_No".txt\"" >> "$log_directory"/config_file_"$list_No".txt 

	Everything else is the same.



3) Run the "Submit_many_condor_jobs_MC.sh" script

./bash_scripts/Submit_many_condor_jobs_MC.sh -i 1 -f 2 -pT_bin_low 50 -pT_bin_high 80 -dir /afs/cern.ch/work/d/dkarasav/public/Analyzer/CMSSW_9_4_0/src/CMSDIJET/DijetRootTreeAnalyzer/deleteme/ -log_dir Condor_Outputs/testing -job_time tomorrow


4) To make sure that the code will run you can use the "Run_reduced_trees_locally_MC.sh" to  run 1 list locally to see if everything is ok.

	
	Run the script as follows: 

./bash_scripts/Run_reduce_trees_localy_MC.sh -i 1 -dir deleteme/ -log_dir Condor_Outputs/hoho/ -pT_bin_low 170 -pT_bin_high 300





====================================================== check reduced trees for trees that did not close correctly ======================================================

Sometimes the output reduced_skim.root files do not "close" correctly and they become unreadable. 
This script checks automatically all the reduced trees in a directory to spot any files that trees did not close correctly. 

Just do: 

./bash_scripts/check_reduced_trees.sh /eos/cms/store/group/phys_jetmet/dimitris/Autumn18_Puppi_btb_reduced_AK8/ 

If some trees did not close you will see the warnings printed in the terminal. If all trees were closed succesfully you will see a corresponding message for success.


