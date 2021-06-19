#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "setTDRStyle_teliko.C"
#include "TH1.h"

 void create_small_tree(){

   double met_ov_sumet,MET, chf, nhf, cemf, nemf, muf, cm,pm, nm ,chf_j2,nhf_j2,cemf_j2,nemf_j2,muf_j2;
   double etaAK4_j1, etaAK4_j2, ptAK4_j1,ptAK4_j2, phiAK4_j1, phiAK4_j2,etaWJ_j1, etaWJ_j2, ptWJ_j1,ptWJ_j2, phiWJ_j1,phiWJ_j2, mjj, Dijet_MassAK4, deltaETAjj, deltaPHIjj,cm_j2,pm_j2,nm_j2,nVtx,CosThetaStarWJ;
   double PassJSON,run,lumin,event;
   double mcut_low = 1530;
     
   	    
	TFile *fout;
	// fout=new TFile("/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/output_root_files/small_tree_rereco_runsABC_promptreco_D_2018_JEC2017_complete.root","recreate");                                 //CREATING NEW TREE
	fout=new TFile("/eos/cms/store/user/dkarasav/small_trees/small_tree_17_JEC_v32.root","recreate"); 	 
	TTree t1("t1","tree");
	 


    t1.Branch("metSig",&met_ov_sumet,"metSig/D");
    t1.Branch("MET",&MET,"MET/D"); 
    t1.Branch("chargedHadEnFrac_j1",&chf,"chargedHadEnFrac_j1/D");
    t1.Branch("neutrHadEnFrac_j1",&nhf,"neutrHadEnFrac_j1/D");
    t1.Branch("chargedElectromFrac_j1",&cemf,"chargedElectromFrac_j1/D");
    t1.Branch("neutrElectromFrac_j1",&nemf,"neutrElectromFrac_j1/D");
    t1.Branch("muEnFract_j1",&muf,"muEnFract_j1/D");
    t1.Branch("chargedHadEnFrac_j2",&chf_j2,"chargedHadEnFrac_j2/D");
    t1.Branch("neutrHadEnFrac_j2",&nhf_j2,"neutrHadEnFrac_j2/D");
    t1.Branch("chargedElectromFrac_j2",&cemf_j2,"chargedElectromFrac_j2/D");
    t1.Branch("neutrElectromFrac_j2",&nemf_j2,"neutrElectromFrac_j2/D");
    t1.Branch("muEnFract_j2",&muf_j2,"muEnFract_j2/D");
    t1.Branch("etaAK4_j1",&etaAK4_j1,"etaAK4_j1/D");
    t1.Branch("etaAK4_j2",&etaAK4_j2,"etaAK4_j2/D");
    t1.Branch("pTAK4_j1",&ptAK4_j1,"pTAK4_j1/D");
    t1.Branch("pTAK4_j2",&ptAK4_j2,"pTAK4_j2/D");
    t1.Branch("phiAK4_j1",&phiAK4_j1,"phiAK4_j1/D");
    t1.Branch("phiAK4_j2",&phiAK4_j2,"phiAK4_j2/D");
    t1.Branch("etaWJ_j1",&etaWJ_j1,"etaWJ_j1/D");
    t1.Branch("etaWJ_j2",&etaWJ_j2,"etaWJ_j2/D");
    t1.Branch("ptWJ_j1",&ptWJ_j1,"ptWJ_j1/D");
    t1.Branch("ptWJ_j2",&ptWJ_j2,"ptWJ_j2/D");
    t1.Branch("phiWJ_j1",&phiWJ_j1,"phiWJ_j1/D");
    t1.Branch("phiWJ_j2",&phiWJ_j2,"phiWJ_j2/D");
    t1.Branch("mjj",&mjj,"mjj/D");
    t1.Branch("Dijet_MassAK4", &Dijet_MassAK4,"Dijet_MassAK4/D");
    t1.Branch("deltaETAjj", &deltaETAjj,"deltaETAjj/D");
    t1.Branch("deltaPHIjj", &deltaPHIjj,"deltaPHIjj/D");
    t1.Branch("chargedMult_j1",&cm,"chargedMult_j1/D");
    t1.Branch("neutrMult_j1",&nm,"neutrMult_j1/D");
    t1.Branch("photonMult_j1",&pm,"photonMult_j1/D");
    t1.Branch("chargedMult_j2",&cm_j2,"chargedMult_j2/D");
    t1.Branch("neutrMult_j2",&nm_j2,"neutrMult_j2/D");
    t1.Branch("photonMult_j2",&pm_j2,"photonMult_j2/D");
    t1.Branch("nVtx",&nVtx,"nVtx/D");	
    t1.Branch("CosThetaStarWJ",&CosThetaStarWJ,"CosThetaStarWJ/D");
    t1.Branch("PassJSON",&PassJSON,"PassJSON/D");   	
    t1.Branch("run",&run,"run/D");
    t1.Branch("event",&event,"event/D");
    t1.Branch("lumi",&lumin,"lumi/D");


   TChain *tree = new TChain("rootTupleTree/tree");
	Char_t filechain[1024];


	//re-reco 2018 with 2018 preliminary residualJECs
	

/*
	for(Int_t kk=0;kk<=36;kk++) //rereco run A
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_2018_JEC_Autumn18_V8/JetHT__Run2018A-17Sep2018_JEC2017__MINIAOD_%d_reduced_skim.root",kk); //For many reduced files
		tree->Add(filechain);
	}

	for(Int_t kk=0;kk<=17;kk++) //rereco run B
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_2018_JEC_Autumn18_V8/JetHT__Run2018B-17Sep2018_JEC2017__MINIAOD_%d_reduced_skim.root",kk); //For many reduced files
		tree->Add(filechain);
	}

	for(Int_t kk=0;kk<=17;kk++) //rereco run C complete
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/group/phys_jetmet/dimitris/data_2018_residualJEC_13_3_19/RunC/JetHT__Run2018C-17Sep2018-v1__MINIAOD_%d_reduced_skim.root",kk); //For many reduced files
		tree->Add(filechain);
	}


		//prompt-reco 2018 with 2018 residual JECs ( magda's processing) 

	for(int j=1 ; j<=31; j++) //prompt-reco run D
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/group/phys_jetmet/dimitris/data_2018_residualJEC_13_3_19/RunD/JetHT__Run2018D-17Sep2018-v1__MINIAOD_%d_reduced_skim.root",j); //For many reduced files
		tree->Add(filechain);
	}

	//prompt-reco 2018 with 2018 residual JECs ( dimitris's processing) 

	for(int j=0 ; j<=10; j++) // prompt-reco run D
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/group/phys_jetmet/dimitris/data_2018_residualJEC_13_3_19/RunD/JetHT__Run2018D-17Sep2018-v1__MINIAOD_rest_%d_reduced_skim.root",j); //For many reduced files
		tree->Add(filechain);
	}
*/



	//re-reco 2017 data with 2017 JECs
/*
	//run B
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017/JetHT_Run2017B-17Nov2017-v1_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017/JetHT_Run2017B-17Nov2017-v1_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017/JetHT_Run2017B-17Nov2017-v1_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017/JetHT_Run2017B-17Nov2017-v1_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017/JetHT_Run2017B-17Nov2017-v1_5_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017/JetHT_Run2017B-17Nov2017-v1_6_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017/JetHT_Run2017B-17Nov2017-v1_7_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017/JetHT_Run2017B-17Nov2017-v1_8_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017/JetHT_Run2017B-17Nov2017-v1_9_reduced_skim.root");

	//tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JEC2017ksana.root");

	//run C
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_5_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_6_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_7_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_8_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_9_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_10_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_11_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_12_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_13_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_14_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_15_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_16_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_17_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017C-17Nov2017-v1_18_reduced_skim.root");
	//run D
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_5_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_6_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_7_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_8_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_9_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017D-17Nov2017-v1_10_reduced_skim.root");
	//run E
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_5_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_6_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_7_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_8_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_9_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_10_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_11_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_12_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_13_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_14_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017E-17Nov2017-v1_15_reduced_skim.root");
	//run F
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_5_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_6_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_7_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_8_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_9_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_10_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_11_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_12_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_13_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_14_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_15_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_16_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_17_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_18_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_19_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/magda/reduced_trees_JetHT_17Nov2017-v1_JEC2017//JetHT_Run2017F-17Nov2017-v1_20_reduced_skim.root");
*/



	//re-reco 2017 data with 2017 JEC v32


	for(Int_t kk=1;kk<=9;kk++) //rereco run B
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/user/mdiamant/2017_2Jets_JECFall17v32/JetHT_Run2017B-17Nov2017-v1_%i_reduced_skim.root",kk); //For many reduced files
		tree->Add(filechain);
	}

	for(Int_t kk=1;kk<=18;kk++) //rereco run C
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/user/mdiamant/2017_2Jets_JECFall17v32/JetHT_Run2017C-17Nov2017-v1_%i_reduced_skim.root",kk); //For many reduced files
		tree->Add(filechain);
	}

	for(Int_t kk=1;kk<=10;kk++) //rereco run D
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/user/mdiamant/2017_2Jets_JECFall17v32/JetHT_Run2017D-17Nov2017-v1_%i_reduced_skim.root",kk); //For many reduced files
		tree->Add(filechain);
	}

	for(Int_t kk=1;kk<=15;kk++) //rereco run E		
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/user/mdiamant/2017_2Jets_JECFall17v32/JetHT_Run2017E-17Nov2017-v1_%i_reduced_skim.root",kk); //For many reduced files
		tree->Add(filechain);
	}

	for(Int_t kk=1;kk<=20;kk++) //rereco run F	
	{  
		sprintf(filechain,"root://eoscms//eos/cms/store/user/mdiamant/2017_2Jets_JECFall17v32/JetHT_Run2017F-17Nov2017-v1_%i_reduced_skim.root",kk); //For many reduced files
		tree->Add(filechain);
	}


 // these are 2016 Data reduced trees
/*

	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/deguio/fall16_red_cert/moriond16_v1_36fb_23SeptJEC/moriond16_v1_36fb_23SeptJEC_20161211_210603/merged/rootfile_moriond16_v1_36fb_moriond16_v1_36fb_23SeptJEC_20161211_210603_reduced_skim1.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/deguio/fall16_red_cert/moriond16_v1_36fb_23SeptJEC/moriond16_v1_36fb_23SeptJEC_20161211_210603/merged/rootfile_moriond16_v1_36fb_moriond16_v1_36fb_23SeptJEC_20161211_210603_reduced_skim2.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/deguio/fall16_red_cert/moriond16_v1_36fb_23SeptJEC/moriond16_v1_36fb_23SeptJEC_20161211_210603/merged/rootfile_moriond16_v1_36fb_moriond16_v1_36fb_23SeptJEC_20161211_210603_reduced_skim3.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/deguio/fall16_red_cert/moriond16_v1_36fb_23SeptJEC/moriond16_v1_36fb_23SeptJEC_20161211_210603/merged/rootfile_moriond16_v1_36fb_moriond16_v1_36fb_23SeptJEC_20161211_210603_reduced_skim4.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/deguio/fall16_red_cert/moriond16_v1_36fb_23SeptJEC/moriond16_v1_36fb_23SeptJEC_20161211_210603/merged/rootfile_moriond16_v1_36fb_moriond16_v1_36fb_23SeptJEC_20161211_210603_reduced_skim5.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/deguio/fall16_red_cert/moriond16_v1_36fb_23SeptJEC/moriond16_v1_36fb_23SeptJEC_20161211_210603/merged/rootfile_moriond16_v1_36fb_moriond16_v1_36fb_23SeptJEC_20161211_210603_reduced_skim6.root");
	tree->Add("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/deguio/fall16_red_cert/moriond16_v1_36fb_23SeptJEC/moriond16_v1_36fb_23SeptJEC_20161211_210603/merged/rootfile_moriond16_v1_36fb_moriond16_v1_36fb_23SeptJEC_20161211_210603_reduced_skim7.root");

*/

//until here


// 2016 data with Summer 16 JEC: 

/*

	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_5_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_6_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_7_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_8_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_9_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016B_10_reduced_skim.root");

	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016C_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016C_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016C_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016C_4_reduced_skim.root");

	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016D_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016D_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016D_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016D_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016D_5_reduced_skim.root");

	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016E_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016E_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016E_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016E_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016E_5_reduced_skim.root");

	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016F_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016F_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016F_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016F_4_reduced_skim.root");

	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016G_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016G_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016G_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016G_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016G_5_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016G_6_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016G_7_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016G_8_reduced_skim.root");

	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016H_1_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016H_2_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016H_3_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016H_4_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016H_5_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016H_6_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016H_7_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016H_8_reduced_skim.root");
	tree->Add("/eos/cms/store/group/phys_jetmet/magda/reduced_trees_2016_JEC_Summer16-23Sep2016-V4/JetHT_Run2016H_9_reduced_skim.root");

*/



    tree->SetBranchAddress("metSig",&met_ov_sumet);
    tree->SetBranchAddress("MET",&MET); 
    tree->SetBranchAddress("chargedHadEnFrac_j1",&chf);
    tree->SetBranchAddress("neutrHadEnFrac_j1",&nhf);
    tree->SetBranchAddress("chargedElectromFrac_j1",&cemf);
    tree->SetBranchAddress("neutrElectromFrac_j1",&nemf);
    tree->SetBranchAddress("muEnFract_j1",&muf);
    tree->SetBranchAddress("chargedHadEnFrac_j2",&chf_j2);
    tree->SetBranchAddress("neutrHadEnFrac_j2",&nhf_j2);
    tree->SetBranchAddress("chargedElectromFrac_j2",&cemf_j2);
    tree->SetBranchAddress("neutrElectromFrac_j2",&nemf_j2);
    tree->SetBranchAddress("muEnFract_j2",&muf_j2);
    tree->SetBranchAddress("etaAK4_j1",&etaAK4_j1);
    tree->SetBranchAddress("etaAK4_j2",&etaAK4_j2);
    tree->SetBranchAddress("pTAK4_j1",&ptAK4_j1);
    tree->SetBranchAddress("pTAK4_j2",&ptAK4_j2);
    tree->SetBranchAddress("phiAK4_j1",&phiAK4_j1);
    tree->SetBranchAddress("phiAK4_j2",&phiAK4_j2);
    tree->SetBranchAddress("etaWJ_j1",&etaWJ_j1);
    tree->SetBranchAddress("etaWJ_j2",&etaWJ_j2);
    tree->SetBranchAddress("pTWJ_j1",&ptWJ_j1);
    tree->SetBranchAddress("pTWJ_j2",&ptWJ_j2);
    tree->SetBranchAddress("phiWJ_j1",&phiWJ_j1);
    tree->SetBranchAddress("phiWJ_j2",&phiWJ_j2);
    tree->SetBranchAddress("mjj", &mjj);
    tree->SetBranchAddress("Dijet_MassAK4", &Dijet_MassAK4);
    tree->SetBranchAddress("deltaETAjj", &deltaETAjj);
    tree->SetBranchAddress("deltaPHIjj", &deltaPHIjj);
    tree->SetBranchAddress("chargedMult_j1",&cm);
    tree->SetBranchAddress("neutrMult_j1",&nm);
    tree->SetBranchAddress("photonMult_j1",&pm);
    tree->SetBranchAddress("chargedMult_j2",&cm_j2);
    tree->SetBranchAddress("neutrMult_j2",&nm_j2);
    tree->SetBranchAddress("photonMult_j2",&pm_j2);
    tree->SetBranchAddress("nVtx",&nVtx);	
    tree->SetBranchAddress("CosThetaStarWJ",&CosThetaStarWJ);
    tree->SetBranchAddress("PassJSON",&PassJSON);   	
    tree->SetBranchAddress("run",&run);
    tree->SetBranchAddress("event",&event);
    tree->SetBranchAddress("lumi",&lumin);

    int nentries=(Int_t)tree->GetEntries(); 
    std::cout<<"Number of entries =  "<<nentries<<std::endl;
	for (int i=0; i<nentries; i++)    //event loop
	 {     //for (int i=0; i<1000; i++){    //event loop
		tree->GetEntry(i);
		if (i%2000000==0) cout << " Reached entry: "<< i<<"\n";
		if(chf!=0 || nhf!=0 || cemf!=0 || nemf!=0 || muf!=0 || chf_j2!=0 || nhf_j2!=0 || cemf_j2!=0 || nemf_j2!=0 || muf_j2!=0)   //this is necessary becasue the analyzer, when an event doesn't pass the cuts, fills all the variables with 0
		 {
			if(met_ov_sumet<0.5 && fabs(etaWJ_j1-etaWJ_j2)<2.6 && mjj>mcut_low && mjj<14000 && ptWJ_j2<6500 && ptWJ_j1<6500 && PassJSON==1)
			 {
				t1.Fill();
			 } //end of Delta Eta, mjj, pt cut
		 }//end of if, necessary from analyzer   
	 }// end of event loop





	fout->cd();
	t1.Write();

	fout->Close();


}
