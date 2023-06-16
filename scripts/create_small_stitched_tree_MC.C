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
#include "TH1.h"

void create_small_stitched_tree_MC(){

    float lumi = 35182;
	
    double cross_section[10] = {445800.0, 113700.0, 7589.0, 626.4, 178.6, 30.57, 8.92, 0.8103, 0.1148, 0.007542}; 
    char PtHatBin[10][50] = {"120to170" , "170to300" , "300to470" , "470to600" , "600to800" , "800to1000" , "1000to1400", "1400to1800", "1800to2400", "2400to3200"}; 
    long double weight[10];
	
	  
    double DDR_AK4PUPPI, DeltaAK4PUPPI_1, DeltaAK4PUPPI_2, DeltaEtaJJAK4PUPPI, DeltaPhiJJAK4PUPPI, DeltaRAK4PUPPI_First, DeltaRAK4PUPPI_Second, DeltaR_AK4PUPPI, DeltaRapidityAK4PUPPI, Dijet_MassAK4PUPPI_1, Dijet_MassAK4PUPPI_2, ETA_AK4PUPPI_1, ETA_AK4PUPPI_2, FourjetMassAK4PUPPI, HTAK4PUPPI, IdTightAK4PUPPI_j1, IdTightAK4PUPPI_j2, IdTightAK4PUPPI_j3, IdTightAK4PUPPI_j4, MET, METoverHTAK4PUPPI, MasymmetryAK4PUPPI, MaverageAK4PUPPI, Nak4puppi, PTAK4PUPPI_firstcomb_1, PTAK4PUPPI_firstcomb_2, PTAK4PUPPI_secondcomb_1, PTAK4PUPPI_secondcomb_2, RapidityAK4PUPPI_1, RapidityAK4PUPPI_2, chargedElectromFracAK4PUPPI_j1, chargedElectromFracAK4PUPPI_j2, chargedElectromFracAK4PUPPI_j3, chargedElectromFracAK4PUPPI_j4, chargedHadEnFracAK4PUPPI_j1, chargedHadEnFracAK4PUPPI_j2, chargedHadEnFracAK4PUPPI_j3, chargedHadEnFracAK4PUPPI_j4, chargedMultAK4PUPPI_j1, chargedMultAK4PUPPI_j2, chargedMultAK4PUPPI_j3, chargedMultAK4PUPPI_j4, eleEnFractAK4PUPPI_j1, eleEnFractAK4PUPPI_j2, eleEnFractAK4PUPPI_j3, eleEnFractAK4PUPPI_j4, etaAK4PUPPI_j1, etaAK4PUPPI_j2, etaAK4PUPPI_j3, etaAK4PUPPI_j4, event, jetJecAK4PUPPI_j1, jetJecAK4PUPPI_j2, jetJecAK4PUPPI_j3, jetJecAK4PUPPI_j4, jetJecUncAK4PUPPI_j1, jetJecUncAK4PUPPI_j2, jetJecUncAK4PUPPI_j3, jetJecUncAK4PUPPI_j4, LS, metSig, muEnFractAK4PUPPI_j1, muEnFractAK4PUPPI_j2, muEnFractAK4PUPPI_j3, muEnFractAK4PUPPI_j4, nVtx, neutrElectromFracAK4PUPPI_j1, neutrElectromFracAK4PUPPI_j2, neutrElectromFracAK4PUPPI_j3, neutrElectromFracAK4PUPPI_j4, neutrHadEnFracAK4PUPPI_j1, neutrHadEnFracAK4PUPPI_j2, neutrHadEnFracAK4PUPPI_j3, neutrHadEnFracAK4PUPPI_j4, neutrMultAK4PUPPI_j1, neutrMultAK4PUPPI_j2, neutrMultAK4PUPPI_j3, neutrMultAK4PUPPI_j4, pTAK4PUPPI_j1, pTAK4PUPPI_j2, pTAK4PUPPI_j3, pTAK4PUPPI_j4, passFilter_BadChargedCandidate, passFilter_BadPFMuon, passFilter_EcalDeadCellTriggerPrimitive, passFilter_HBHENoise, passFilter_HBHENoiseIso, passFilter_eeBadSc, passFilter_globalSuperTightHalo2016, passFilter_goodVertices, phiAK4PUPPI_j1, phiAK4PUPPI_j2, phiAK4PUPPI_j3, phiAK4PUPPI_j4, photonEnFracAK4PUPPI_j1, photonEnFracAK4PUPPI_j2, photonEnFracAK4PUPPI_j3, photonEnFracAK4PUPPI_j4, photonMultAK4PUPPI_j1, photonMultAK4PUPPI_j2, photonMultAK4PUPPI_j3, photonMultAK4PUPPI_j4, run, trueVtx, w; 

    char pTbin[50];

    TFile *fout;

    //fout = new TFile("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22/Summer22Run3_V1_JECs/Stitched_QCD_PT-120to3200_TuneCP5_13p6TeV_pythia8__Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12_ext1-v2__AK4PUPPI_35p182fb-1_reduced_skim.root","recreate");
fout = new TFile("/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22EE/Summer22EERun3_V1_JECs/Stitched_QCD_PT-120to3200_TuneCP5_13p6TeV_pythia8__Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1_ext1-v2__AK4PUPPI_35p182fb-1_reduced_skim.root","recreate");

    TTree t1("tree","tree");

    t1.Branch("DDR_AK4PUPPI",&DDR_AK4PUPPI, "DDR_AK4PUPPI/D");
    t1.Branch("DeltaAK4PUPPI_1",&DeltaAK4PUPPI_1, "DeltaAK4PUPPI_1/D");
    t1.Branch("DeltaAK4PUPPI_2",&DeltaAK4PUPPI_2, "DeltaAK4PUPPI_2/D");
    t1.Branch("DeltaEtaJJAK4PUPPI",&DeltaEtaJJAK4PUPPI,"DeltaEtaJJAK4PUPPI/D");
    t1.Branch("DeltaPhiJJAK4PUPPI",&DeltaPhiJJAK4PUPPI,"DeltaPhiJJAK4PUPPI/D");
    t1.Branch("DeltaRAK4PUPPI_First",&DeltaRAK4PUPPI_First,"DeltaRAK4PUPPI_First/D");
    t1.Branch("DeltaRAK4PUPPI_Second",&DeltaRAK4PUPPI_Second,"DeltaRAK4PUPPI_Second/D");
    t1.Branch("DeltaR_AK4PUPPI",&DeltaR_AK4PUPPI,"DeltaR_AK4PUPPI/D");
    t1.Branch("DeltaRapidityAK4PUPPI",&DeltaRapidityAK4PUPPI,"DeltaRapidityAK4PUPPI/D");
    t1.Branch("Dijet_MassAK4PUPPI_1",&Dijet_MassAK4PUPPI_1,"Dijet_MassAK4PUPPI_1/D");  
    t1.Branch("Dijet_MassAK4PUPPI_2",&Dijet_MassAK4PUPPI_2,"Dijet_MassAK4PUPPI_2/D");
    t1.Branch("ETA_AK4PUPPI_1",&ETA_AK4PUPPI_1,"ETA_AK4PUPPI_1/D");
    t1.Branch("ETA_AK4PUPPI_2",&ETA_AK4PUPPI_2,"ETA_AK4PUPPI_2/D");
    t1.Branch("FourjetMassAK4PUPPI",&FourjetMassAK4PUPPI,"FourjetMassAK4PUPPI/D");
    t1.Branch("HTAK4PUPPI",&HTAK4PUPPI,"HTAK4PUPPI/D");
    t1.Branch("IdTightAK4PUPPI_j1",&IdTightAK4PUPPI_j1,"IdTightAK4PUPPI_j1/D");
    t1.Branch("IdTightAK4PUPPI_j2",&IdTightAK4PUPPI_j2,"IdTightAK4PUPPI_j2/D");
    t1.Branch("IdTightAK4PUPPI_j3",&IdTightAK4PUPPI_j3,"IdTightAK4PUPPI_j3/D");
    t1.Branch("IdTightAK4PUPPI_j4",&IdTightAK4PUPPI_j4,"IdTightAK4PUPPI_j4/D");
    t1.Branch("MET",&MET,"MET/D");
    t1.Branch("METoverHTAK4PUPPI",&METoverHTAK4PUPPI,"METoverHTAK4PUPPI/D");
    t1.Branch("MasymmetryAK4PUPPI",&MasymmetryAK4PUPPI,"MasymmetryAK4PUPPI/D");
    t1.Branch("MaverageAK4PUPPI",&MaverageAK4PUPPI,"MaverageAK4PUPPI/D");
    t1.Branch("Nak4puppi",&Nak4puppi,"Nak4puppi/D");
    t1.Branch("PTAK4PUPPI_firstcomb_1",&PTAK4PUPPI_firstcomb_1,"PTAK4PUPPI_firstcomb_1/D");
    t1.Branch("PTAK4PUPPI_firstcomb_2",&PTAK4PUPPI_firstcomb_2,"PTAK4PUPPI_firstcomb_2/D");
    t1.Branch("PTAK4PUPPI_secondcomb_1",&PTAK4PUPPI_secondcomb_1,"PTAK4PUPPI_secondcomb_1/D");
    t1.Branch("PTAK4PUPPI_secondcomb_2",&PTAK4PUPPI_secondcomb_2,"PTAK4PUPPI_secondcomb_2/D");
    t1.Branch("RapidityAK4PUPPI_1",&RapidityAK4PUPPI_1,"RapidityAK4PUPPI_1/D");
    t1.Branch("RapidityAK4PUPPI_2",&RapidityAK4PUPPI_2,"RapidityAK4PUPPI_2/D");
    t1.Branch("chargedElectromFracAK4PUPPI_j1",&chargedElectromFracAK4PUPPI_j1,"chargedElectromFracAK4PUPPI_j1/D");
    t1.Branch("chargedElectromFracAK4PUPPI_j2",&chargedElectromFracAK4PUPPI_j2,"chargedElectromFracAK4PUPPI_j2/D");
    t1.Branch("chargedElectromFracAK4PUPPI_j3",&chargedElectromFracAK4PUPPI_j3,"chargedElectromFracAK4PUPPI_j3/D");
    t1.Branch("chargedElectromFracAK4PUPPI_j4",&chargedElectromFracAK4PUPPI_j4,"chargedElectromFracAK4PUPPI_j4/D");
    t1.Branch("chargedHadEnFracAK4PUPPI_j1",&chargedHadEnFracAK4PUPPI_j1,"chargedHadEnFracAK4PUPPI_j1/D");
    t1.Branch("chargedHadEnFracAK4PUPPI_j2",&chargedHadEnFracAK4PUPPI_j2,"chargedHadEnFracAK4PUPPI_j2/D");
    t1.Branch("chargedHadEnFracAK4PUPPI_j3",&chargedHadEnFracAK4PUPPI_j3,"chargedHadEnFracAK4PUPPI_j3/D");
    t1.Branch("chargedHadEnFracAK4PUPPI_j4",&chargedHadEnFracAK4PUPPI_j4,"chargedHadEnFracAK4PUPPI_j4/D");
    t1.Branch("chargedMultAK4PUPPI_j1",&chargedMultAK4PUPPI_j1,"chargedMultAK4PUPPI_j1/D");
    t1.Branch("chargedMultAK4PUPPI_j2",&chargedMultAK4PUPPI_j2,"chargedMultAK4PUPPI_j2/D");
    t1.Branch("chargedMultAK4PUPPI_j3",&chargedMultAK4PUPPI_j3,"chargedMultAK4PUPPI_j3/D");
    t1.Branch("chargedMultAK4PUPPI_j4",&chargedMultAK4PUPPI_j4,"chargedMultAK4PUPPI_j4/D");
    t1.Branch("eleEnFractAK4PUPPI_j1",&eleEnFractAK4PUPPI_j1,"eleEnFractAK4PUPPI_j1/D");
    t1.Branch("eleEnFractAK4PUPPI_j2",&eleEnFractAK4PUPPI_j2,"eleEnFractAK4PUPPI_j2/D");
    t1.Branch("eleEnFractAK4PUPPI_j3",&eleEnFractAK4PUPPI_j3,"eleEnFractAK4PUPPI_j3/D");
    t1.Branch("eleEnFractAK4PUPPI_j4",&eleEnFractAK4PUPPI_j4,"eleEnFractAK4PUPPI_j4/D");
    t1.Branch("etaAK4PUPPI_j1",&etaAK4PUPPI_j1,"etaAK4PUPPI_j1/D");
    t1.Branch("etaAK4PUPPI_j2",&etaAK4PUPPI_j2,"etaAK4PUPPI_j2/D");
    t1.Branch("etaAK4PUPPI_j3",&etaAK4PUPPI_j3,"etaAK4PUPPI_j3/D");
    t1.Branch("etaAK4PUPPI_j4",&etaAK4PUPPI_j4,"etaAK4PUPPI_j4/D");
    t1.Branch("event",&event,"event/D");
    t1.Branch("jetJecAK4PUPPI_j1",&jetJecAK4PUPPI_j1,"jetJecAK4PUPPI_j1/D");
    t1.Branch("jetJecAK4PUPPI_j2",&jetJecAK4PUPPI_j2,"jetJecAK4PUPPI_j2/D");
    t1.Branch("jetJecAK4PUPPI_j3",&jetJecAK4PUPPI_j3,"jetJecAK4PUPPI_j3/D");
    t1.Branch("jetJecAK4PUPPI_j4",&jetJecAK4PUPPI_j4,"jetJecAK4PUPPI_j4/D");
    t1.Branch("jetJecUncAK4PUPPI_j1",&jetJecUncAK4PUPPI_j1,"jetJecUncAK4PUPPI_j1/D");
    t1.Branch("jetJecUncAK4PUPPI_j2",&jetJecUncAK4PUPPI_j2,"jetJecUncAK4PUPPI_j2/D");
    t1.Branch("jetJecUncAK4PUPPI_j3",&jetJecUncAK4PUPPI_j3,"jetJecUncAK4PUPPI_j3/D");
    t1.Branch("jetJecUncAK4PUPPI_j4",&jetJecUncAK4PUPPI_j4,"jetJecUncAK4PUPPI_j4/D");
    t1.Branch("lumi",&LS,"lumi/D");
    t1.Branch("metSig",&metSig,"metSig/D");
    t1.Branch("muEnFractAK4PUPPI_j1",&muEnFractAK4PUPPI_j1,"muEnFractAK4PUPPI_j1/D");
    t1.Branch("muEnFractAK4PUPPI_j2",&muEnFractAK4PUPPI_j2,"muEnFractAK4PUPPI_j2/D");
    t1.Branch("muEnFractAK4PUPPI_j3",&muEnFractAK4PUPPI_j3,"muEnFractAK4PUPPI_j3/D");
    t1.Branch("muEnFractAK4PUPPI_j4",&muEnFractAK4PUPPI_j4,"muEnFractAK4PUPPI_j4/D");
    t1.Branch("nVtx",&nVtx,"nVtx/D");
    t1.Branch("neutrElectromFracAK4PUPPI_j1",&neutrElectromFracAK4PUPPI_j1,"neutrElectromFracAK4PUPPI_j1/D");
    t1.Branch("neutrElectromFracAK4PUPPI_j2",&neutrElectromFracAK4PUPPI_j2,"neutrElectromFracAK4PUPPI_j2/D");
    t1.Branch("neutrElectromFracAK4PUPPI_j3",&neutrElectromFracAK4PUPPI_j3,"neutrElectromFracAK4PUPPI_j3/D");
    t1.Branch("neutrElectromFracAK4PUPPI_j4",&neutrElectromFracAK4PUPPI_j4,"neutrElectromFracAK4PUPPI_j4/D");
    t1.Branch("neutrHadEnFracAK4PUPPI_j1",&neutrHadEnFracAK4PUPPI_j1,"neutrHadEnFracAK4PUPPI_j1/D");
    t1.Branch("neutrHadEnFracAK4PUPPI_j2",&neutrHadEnFracAK4PUPPI_j2,"neutrHadEnFracAK4PUPPI_j2/D");
    t1.Branch("neutrHadEnFracAK4PUPPI_j3",&neutrHadEnFracAK4PUPPI_j3,"neutrHadEnFracAK4PUPPI_j3/D");
    t1.Branch("neutrHadEnFracAK4PUPPI_j4",&neutrHadEnFracAK4PUPPI_j4,"neutrHadEnFracAK4PUPPI_j4/D");
    t1.Branch("neutrMultAK4PUPPI_j1",&neutrMultAK4PUPPI_j1,"neutrMultAK4PUPPI_j1/D");
    t1.Branch("neutrMultAK4PUPPI_j2",&neutrMultAK4PUPPI_j2,"neutrMultAK4PUPPI_j2/D");
    t1.Branch("neutrMultAK4PUPPI_j3",&neutrMultAK4PUPPI_j3,"neutrMultAK4PUPPI_j3/D");
    t1.Branch("neutrMultAK4PUPPI_j4",&neutrMultAK4PUPPI_j4,"neutrMultAK4PUPPI_j4/D");
    t1.Branch("pTAK4PUPPI_j1",&pTAK4PUPPI_j1,"pTAK4PUPPI_j1/D");
    t1.Branch("pTAK4PUPPI_j2",&pTAK4PUPPI_j2,"pTAK4PUPPI_j2/D");
    t1.Branch("pTAK4PUPPI_j3",&pTAK4PUPPI_j3,"pTAK4PUPPI_j3/D");
    t1.Branch("pTAK4PUPPI_j4",&pTAK4PUPPI_j4,"pTAK4PUPPI_j4/D");
    t1.Branch("passFilter_BadChargedCandidate",&passFilter_BadChargedCandidate,"passFilter_BadChargedCandidate/D");
    t1.Branch("passFilter_BadPFMuon",&passFilter_BadPFMuon,"passFilter_BadPFMuon/D");
    t1.Branch("passFilter_EcalDeadCellTriggerPrimitive",&passFilter_EcalDeadCellTriggerPrimitive,"passFilter_EcalDeadCellTriggerPrimitive/D");
    t1.Branch("passFilter_HBHENoise",&passFilter_HBHENoise,"passFilter_HBHENoise/D");
    t1.Branch("passFilter_HBHENoiseIso",&passFilter_HBHENoiseIso,"passFilter_HBHENoiseIso/D");
    t1.Branch("passFilter_eeBadSc",&passFilter_eeBadSc,"passFilter_eeBadSc/D");
    t1.Branch("passFilter_globalSuperTightHalo2016",&passFilter_globalSuperTightHalo2016,"passFilter_globalSuperTightHalo2016/D");
    t1.Branch("passFilter_goodVertices",&passFilter_goodVertices,"passFilter_goodVertices/D");
    t1.Branch("phiAK4PUPPI_j1",&phiAK4PUPPI_j1,"phiAK4PUPPI_j1/D");
    t1.Branch("phiAK4PUPPI_j2",&phiAK4PUPPI_j2,"phiAK4PUPPI_j2/D");
    t1.Branch("phiAK4PUPPI_j3",&phiAK4PUPPI_j3,"phiAK4PUPPI_j3/D");
    t1.Branch("phiAK4PUPPI_j4",&phiAK4PUPPI_j4,"phiAK4PUPPI_j4/D");
    t1.Branch("photonEnFracAK4PUPPI_j1",&photonEnFracAK4PUPPI_j1,"photonEnFracAK4PUPPI_j1/D");
    t1.Branch("photonEnFracAK4PUPPI_j2",&photonEnFracAK4PUPPI_j2,"photonEnFracAK4PUPPI_j2/D");
    t1.Branch("photonEnFracAK4PUPPI_j3",&photonEnFracAK4PUPPI_j3,"photonEnFracAK4PUPPI_j3/D");
    t1.Branch("photonEnFracAK4PUPPI_j4",&photonEnFracAK4PUPPI_j4,"photonEnFracAK4PUPPI_j4/D");
    t1.Branch("photonMultAK4PUPPI_j1",&photonMultAK4PUPPI_j1,"photonMultAK4PUPPI_j1/D");
    t1.Branch("photonMultAK4PUPPI_j2",&photonMultAK4PUPPI_j2,"photonMultAK4PUPPI_j2/D");
    t1.Branch("photonMultAK4PUPPI_j3",&photonMultAK4PUPPI_j3,"photonMultAK4PUPPI_j3/D");
    t1.Branch("photonMultAK4PUPPI_j4",&photonMultAK4PUPPI_j4,"photonMultAK4PUPPI_j4/D");	
    t1.Branch("run",&run,"run/D");
    t1.Branch("trueVtx",&trueVtx,"trueVtx/D");
    t1.Branch("weight",&w,"weight/D");
    t1.Branch("pTbin",&pTbin,"pTbin/C");

    std::cout<<"Calculating the weights of each pt-hat bin file... "  << std::endl;
    int Ntotal=0;

    TFile *f1;
    TTree *tree;
    for(int fl=0; fl<10; fl++) 
    { 
    		char input_directory[300];
		//strcpy(input_directory,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22/Summer22Run3_V1_JECs/QCD_PT-");
		strcpy(input_directory,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22EE/Summer22EERun3_V1_JECs/QCD_PT-");
		strcat(input_directory,PtHatBin[fl]);
		char file_name[200];
		//sprintf(file_name,"_TuneCP5_13p6TeV_pythia8__Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12_ext1-v2__AK4PUPPI_reduced_skim.root");
		sprintf(file_name,"_TuneCP5_13p6TeV_pythia8__Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1_ext1-v2__AK4PUPPI_reduced_skim.root");
		strcat(input_directory,file_name);
		f1 = TFile::Open(input_directory,"READ");

	        TH1D *h_Nev = (TH1D*)f1->Get("DijetFilter/EventCount/EventCounter");
	        int Nev = h_Nev->GetBinContent(2);

		tree = (TTree*)f1->Get("rootTupleTree/tree");

		Ntotal = Ntotal + tree->GetEntries();
		weight[fl] = cross_section[fl]*lumi/Nev;
	        std::cout<< "pT bin : " << PtHatBin[fl] << " processed Generated Events "<< Nev <<", Events:  " << tree->GetEntries() << ", Weight is " << weight[fl] << std::endl;
		//weight[fl]=1.;

		delete tree;
		f1->Close();
    }  

    cout << " Total number of events: " << Ntotal << endl;
	
    for(Int_t fl=0; fl<10; fl++)  
    {  
		char input_directory[300];
		//strcpy(input_directory,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22/Summer22Run3_V1_JECs/QCD_PT-");
		strcpy(input_directory,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/Run3Summer22EE/Summer22EERun3_V1_JECs/QCD_PT-");
		strcat(input_directory,PtHatBin[fl]);
		char file_name[200];
		//sprintf(file_name,"_TuneCP5_13p6TeV_pythia8__Run3Summer22MiniAODv3-124X_mcRun3_2022_realistic_v12_ext1-v2__AK4PUPPI_reduced_skim.root");
		sprintf(file_name,"_TuneCP5_13p6TeV_pythia8__Run3Summer22EEMiniAODv3-124X_mcRun3_2022_realistic_postEE_v1_ext1-v2__AK4PUPPI_reduced_skim.root");
		strcat(input_directory,file_name);
		f1 = TFile::Open(input_directory,"READ");
		tree = (TTree*)f1->Get("rootTupleTree/tree");

     		tree->SetBranchAddress("DDR_AK4PUPPI",&DDR_AK4PUPPI);
    		tree->SetBranchAddress("DeltaAK4PUPPI_1",&DeltaAK4PUPPI_1);
    		tree->SetBranchAddress("DeltaAK4PUPPI_2",&DeltaAK4PUPPI_2);
    		tree->SetBranchAddress("DeltaEtaJJAK4PUPPI",&DeltaEtaJJAK4PUPPI);
    		tree->SetBranchAddress("DeltaPhiJJAK4PUPPI",&DeltaPhiJJAK4PUPPI);
    		tree->SetBranchAddress("DeltaRAK4PUPPI_First",&DeltaRAK4PUPPI_First);
    		tree->SetBranchAddress("DeltaRAK4PUPPI_Second",&DeltaRAK4PUPPI_Second);
    		tree->SetBranchAddress("DeltaR_AK4PUPPI",&DeltaR_AK4PUPPI);
    		tree->SetBranchAddress("DeltaRapidityAK4PUPPI",&DeltaRapidityAK4PUPPI);
    		tree->SetBranchAddress("Dijet_MassAK4PUPPI_1",&Dijet_MassAK4PUPPI_1);  
    		tree->SetBranchAddress("Dijet_MassAK4PUPPI_2",&Dijet_MassAK4PUPPI_2);
    		tree->SetBranchAddress("ETA_AK4PUPPI_1",&ETA_AK4PUPPI_1);
    		tree->SetBranchAddress("ETA_AK4PUPPI_2",&ETA_AK4PUPPI_2);
    		tree->SetBranchAddress("FourjetMassAK4PUPPI",&FourjetMassAK4PUPPI);
    		tree->SetBranchAddress("HTAK4PUPPI",&HTAK4PUPPI);
    		tree->SetBranchAddress("IdTightAK4PUPPI_j1",&IdTightAK4PUPPI_j1);
    		tree->SetBranchAddress("IdTightAK4PUPPI_j2",&IdTightAK4PUPPI_j2);
    		tree->SetBranchAddress("IdTightAK4PUPPI_j3",&IdTightAK4PUPPI_j3);
    		tree->SetBranchAddress("IdTightAK4PUPPI_j4",&IdTightAK4PUPPI_j4);
    		tree->SetBranchAddress("MET",&MET);
    		tree->SetBranchAddress("METoverHTAK4PUPPI",&METoverHTAK4PUPPI);
    		tree->SetBranchAddress("MasymmetryAK4PUPPI",&MasymmetryAK4PUPPI);
    		tree->SetBranchAddress("MaverageAK4PUPPI",&MaverageAK4PUPPI);
    		tree->SetBranchAddress("Nak4puppi",&Nak4puppi);
    		tree->SetBranchAddress("PTAK4PUPPI_firstcomb_1",&PTAK4PUPPI_firstcomb_1);
    		tree->SetBranchAddress("PTAK4PUPPI_firstcomb_2",&PTAK4PUPPI_firstcomb_2);
    		tree->SetBranchAddress("PTAK4PUPPI_secondcomb_1",&PTAK4PUPPI_secondcomb_1);
    		tree->SetBranchAddress("PTAK4PUPPI_secondcomb_2",&PTAK4PUPPI_secondcomb_2);
    		tree->SetBranchAddress("RapidityAK4PUPPI_1",&RapidityAK4PUPPI_1);
    		tree->SetBranchAddress("RapidityAK4PUPPI_2",&RapidityAK4PUPPI_2);
    		tree->SetBranchAddress("chargedElectromFracAK4PUPPI_j1",&chargedElectromFracAK4PUPPI_j1);
    		tree->SetBranchAddress("chargedElectromFracAK4PUPPI_j2",&chargedElectromFracAK4PUPPI_j2);
    		tree->SetBranchAddress("chargedElectromFracAK4PUPPI_j3",&chargedElectromFracAK4PUPPI_j3);
    		tree->SetBranchAddress("chargedElectromFracAK4PUPPI_j4",&chargedElectromFracAK4PUPPI_j4);
    		tree->SetBranchAddress("chargedHadEnFracAK4PUPPI_j1",&chargedHadEnFracAK4PUPPI_j1);
    		tree->SetBranchAddress("chargedHadEnFracAK4PUPPI_j2",&chargedHadEnFracAK4PUPPI_j2);
    		tree->SetBranchAddress("chargedHadEnFracAK4PUPPI_j3",&chargedHadEnFracAK4PUPPI_j3);
    		tree->SetBranchAddress("chargedHadEnFracAK4PUPPI_j4",&chargedHadEnFracAK4PUPPI_j4);
    		tree->SetBranchAddress("chargedMultAK4PUPPI_j1",&chargedMultAK4PUPPI_j1);
    		tree->SetBranchAddress("chargedMultAK4PUPPI_j2",&chargedMultAK4PUPPI_j2);
    		tree->SetBranchAddress("chargedMultAK4PUPPI_j3",&chargedMultAK4PUPPI_j3);
    		tree->SetBranchAddress("chargedMultAK4PUPPI_j4",&chargedMultAK4PUPPI_j4);
    		tree->SetBranchAddress("eleEnFractAK4PUPPI_j1",&eleEnFractAK4PUPPI_j1);
    		tree->SetBranchAddress("eleEnFractAK4PUPPI_j2",&eleEnFractAK4PUPPI_j2);
    		tree->SetBranchAddress("eleEnFractAK4PUPPI_j3",&eleEnFractAK4PUPPI_j3);
    		tree->SetBranchAddress("eleEnFractAK4PUPPI_j4",&eleEnFractAK4PUPPI_j4);
    		tree->SetBranchAddress("etaAK4PUPPI_j1",&etaAK4PUPPI_j1);
    		tree->SetBranchAddress("etaAK4PUPPI_j2",&etaAK4PUPPI_j2);
    		tree->SetBranchAddress("etaAK4PUPPI_j3",&etaAK4PUPPI_j3);
    		tree->SetBranchAddress("etaAK4PUPPI_j4",&etaAK4PUPPI_j4);
    		tree->SetBranchAddress("event",&event);
    		tree->SetBranchAddress("jetJecAK4PUPPI_j1",&jetJecAK4PUPPI_j1);
    		tree->SetBranchAddress("jetJecAK4PUPPI_j2",&jetJecAK4PUPPI_j2);
    		tree->SetBranchAddress("jetJecAK4PUPPI_j3",&jetJecAK4PUPPI_j3);
    		tree->SetBranchAddress("jetJecAK4PUPPI_j4",&jetJecAK4PUPPI_j4);
    		tree->SetBranchAddress("jetJecUncAK4PUPPI_j1",&jetJecUncAK4PUPPI_j1);
    		tree->SetBranchAddress("jetJecUncAK4PUPPI_j2",&jetJecUncAK4PUPPI_j2);
    		tree->SetBranchAddress("jetJecUncAK4PUPPI_j3",&jetJecUncAK4PUPPI_j3);
    		tree->SetBranchAddress("jetJecUncAK4PUPPI_j4",&jetJecUncAK4PUPPI_j4);
    		tree->SetBranchAddress("lumi",&LS);
    		tree->SetBranchAddress("metSig",&metSig);
    		tree->SetBranchAddress("muEnFractAK4PUPPI_j1",&muEnFractAK4PUPPI_j1);
    		tree->SetBranchAddress("muEnFractAK4PUPPI_j2",&muEnFractAK4PUPPI_j2);
    		tree->SetBranchAddress("muEnFractAK4PUPPI_j3",&muEnFractAK4PUPPI_j3);
    		tree->SetBranchAddress("muEnFractAK4PUPPI_j4",&muEnFractAK4PUPPI_j4);
    		tree->SetBranchAddress("nVtx",&nVtx);
    		tree->SetBranchAddress("neutrElectromFracAK4PUPPI_j1",&neutrElectromFracAK4PUPPI_j1);
    		tree->SetBranchAddress("neutrElectromFracAK4PUPPI_j2",&neutrElectromFracAK4PUPPI_j2);
    		tree->SetBranchAddress("neutrElectromFracAK4PUPPI_j3",&neutrElectromFracAK4PUPPI_j3);
    		tree->SetBranchAddress("neutrElectromFracAK4PUPPI_j4",&neutrElectromFracAK4PUPPI_j4);
    		tree->SetBranchAddress("neutrHadEnFracAK4PUPPI_j1",&neutrHadEnFracAK4PUPPI_j1);
    		tree->SetBranchAddress("neutrHadEnFracAK4PUPPI_j2",&neutrHadEnFracAK4PUPPI_j2);
    		tree->SetBranchAddress("neutrHadEnFracAK4PUPPI_j3",&neutrHadEnFracAK4PUPPI_j3);
    		tree->SetBranchAddress("neutrHadEnFracAK4PUPPI_j4",&neutrHadEnFracAK4PUPPI_j4);
    		tree->SetBranchAddress("neutrMultAK4PUPPI_j1",&neutrMultAK4PUPPI_j1);
    		tree->SetBranchAddress("neutrMultAK4PUPPI_j2",&neutrMultAK4PUPPI_j2);
    		tree->SetBranchAddress("neutrMultAK4PUPPI_j3",&neutrMultAK4PUPPI_j3);
    		tree->SetBranchAddress("neutrMultAK4PUPPI_j4",&neutrMultAK4PUPPI_j4);
    		tree->SetBranchAddress("pTAK4PUPPI_j1",&pTAK4PUPPI_j1);
    		tree->SetBranchAddress("pTAK4PUPPI_j2",&pTAK4PUPPI_j2);
    		tree->SetBranchAddress("pTAK4PUPPI_j3",&pTAK4PUPPI_j3);
    		tree->SetBranchAddress("pTAK4PUPPI_j4",&pTAK4PUPPI_j4);
    		tree->SetBranchAddress("passFilter_BadChargedCandidate",&passFilter_BadChargedCandidate);
    		tree->SetBranchAddress("passFilter_BadPFMuon",&passFilter_BadPFMuon);
    		tree->SetBranchAddress("passFilter_EcalDeadCellTriggerPrimitive",&passFilter_EcalDeadCellTriggerPrimitive);
    		tree->SetBranchAddress("passFilter_HBHENoise",&passFilter_HBHENoise);
    		tree->SetBranchAddress("passFilter_HBHENoiseIso",&passFilter_HBHENoiseIso);
    		tree->SetBranchAddress("passFilter_eeBadSc",&passFilter_eeBadSc);
    		tree->SetBranchAddress("passFilter_globalSuperTightHalo2016",&passFilter_globalSuperTightHalo2016);
    		tree->SetBranchAddress("passFilter_goodVertices",&passFilter_goodVertices);
    		tree->SetBranchAddress("phiAK4PUPPI_j1",&phiAK4PUPPI_j1);
    		tree->SetBranchAddress("phiAK4PUPPI_j2",&phiAK4PUPPI_j2);
    		tree->SetBranchAddress("phiAK4PUPPI_j3",&phiAK4PUPPI_j3);
    		tree->SetBranchAddress("phiAK4PUPPI_j4",&phiAK4PUPPI_j4);
    		tree->SetBranchAddress("photonEnFracAK4PUPPI_j1",&photonEnFracAK4PUPPI_j1);
    		tree->SetBranchAddress("photonEnFracAK4PUPPI_j2",&photonEnFracAK4PUPPI_j2);
    		tree->SetBranchAddress("photonEnFracAK4PUPPI_j3",&photonEnFracAK4PUPPI_j3);
    		tree->SetBranchAddress("photonEnFracAK4PUPPI_j4",&photonEnFracAK4PUPPI_j4);
    		tree->SetBranchAddress("photonMultAK4PUPPI_j1",&photonMultAK4PUPPI_j1);
    		tree->SetBranchAddress("photonMultAK4PUPPI_j2",&photonMultAK4PUPPI_j2);
    		tree->SetBranchAddress("photonMultAK4PUPPI_j3",&photonMultAK4PUPPI_j3);
    		tree->SetBranchAddress("photonMultAK4PUPPI_j4",&photonMultAK4PUPPI_j4);	
    		tree->SetBranchAddress("run",&run);
    		tree->SetBranchAddress("trueVtx",&trueVtx);

	        Int_t nentries=(Int_t)tree->GetEntries(); 
	        cout << "Now proccessing pT bin : " << PtHatBin[fl] << " Number of entries =  "<< nentries << endl ;
   
	        for (int i=0; i<nentries; i++)    //event loop
	        //for (int i=0; i<1000; i++)    //event loop
	        {
	
	   		tree->GetEntry(i);
	   		if (i%1000000==0) cout << " Reached entry: "<< i<<"\n";
	   		
	  		w = weight[fl];
			strcpy(pTbin,PtHatBin[fl]);
			t1.Fill();
		  
		}// end of event loop

		delete tree;
		f1->Close();
    } //end of loop on pt Hat bins

    cout << "loop finished! "<< endl;

    fout->cd();
    TDirectoryFile *dir = new TDirectoryFile("rootTupleTree","rootTupleTree");
    dir->cd();
    t1.Write();
    fout->Close();


}
