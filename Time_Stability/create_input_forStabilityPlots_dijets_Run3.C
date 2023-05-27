#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "Math/MinimizerOptions.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"


void create_input_forStabilityPlots_dijets_Run3(Int_t doJSON)
{
  const int nMassBins = 103;
   
  double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

  TH2F *DijetMass_vsRun, *DeltaEtaJJ_vsRun, *DeltaPhiJJ_vsRun;
  TH2F *pT_vsRun, *eta_vsRun, *phi_vsRun, *CHF_vsRun, *NHF_vsRun, *NEMF_vsRun; 

  TH2F *DijetMass_vsNvtx, *DeltaEtaJJ_vsNvtx, *DeltaPhiJJ_vsNvtx;
  TH2F *pT_vsNvtx, *eta_vsNvtx, *phi_vsNvtx, *CHF_vsNvtx, *NHF_vsNvtx, *NEMF_vsNvtx;

  TH1F *Run;
 
  int run_start = 355374;
  int run_end   = 362104;
  int nbins     = run_end-run_start;

  Run = new TH1F ("Run","",nbins, run_start, run_end);

  DijetMass_vsRun = new TH2F ("DijetMass_vsRun","",nbins, run_start, run_end, nMassBins,massBoundaries);
  DeltaEtaJJ_vsRun = new TH2F ("DeltaEtaJJ_vsRun","",nbins, run_start, run_end, 40,0,2);
  DeltaPhiJJ_vsRun = new TH2F ("DeltaPhiJJ_vsRun","",nbins, run_start, run_end, 64,0,3.1416);
  pT_vsRun = new TH2F ("pT_vsRun","",nbins, run_start, run_end, 75,0,6000);
  eta_vsRun = new TH2F ("eta_vsRun","",nbins, run_start, run_end, 30,-3,3);
  phi_vsRun = new TH2F ("phi_vsRun","",nbins, run_start, run_end, 32,-3.2,3.2);
  CHF_vsRun = new TH2F ("CHF_vsRun","",nbins, run_start, run_end, 60,0,1.2);
  NHF_vsRun = new TH2F ("NHF_vsRun","",nbins, run_start, run_end, 60,0,1.2);
  NEMF_vsRun = new TH2F ("NEMF_vsRun","",nbins, run_start, run_end, 60,0,1.2);

  DijetMass_vsNvtx = new TH2F ("FourjetMass_vsNvtx","",100, 0, 100, nMassBins,massBoundaries);
  DeltaEtaJJ_vsNvtx = new TH2F ("DeltaEtaJJ_vsNvtx","",100, 0, 100, 40,0,2);
  DeltaPhiJJ_vsNvtx = new TH2F ("DeltaPhiJJ_vsNvtx","",100, 0, 100, 64,0,3.1416);
  pT_vsNvtx = new TH2F ("pT_vsNvtx","",100, 0, 100, 75,0,6000);
  eta_vsNvtx = new TH2F ("eta_vsNvtx","",100, 0, 100, 30,-3,3);
  phi_vsNvtx = new TH2F ("phi_vsNvtx","",100, 0, 100, 32,-3.2,3.2);
  CHF_vsNvtx = new TH2F ("CHF_vsNvtx","",100, 0, 100, 60,0,1.2);
  NHF_vsNvtx = new TH2F ("NHF_vsNvtx","",100, 0, 100, 60,0,1.2);
  NEMF_vsNvtx = new TH2F ("NEMF_vsNvtx","",100, 0, 100, 60,0,1.2);


   /////////initialize variables

  double run, lumi, event, weight, nVtx, PassJSON;
  double DijetMass, DeltaEtaJJ, DeltaPhiJJ;
  double pTwj1, pTwj2, etawj1, etawj2, phiwj1, phiwj2;
  double chargedHadEnFrac_j1, chargedHadEnFrac_j2, neutrElectromFrac_j1, neutrElectromFrac_j2, neutrHadEnFrac_j1, neutrHadEnFrac_j2;

  TChain *tree_data = new TChain("rootTupleTree/tree");

  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_jetmet/mkotsari/run3_data_summer22/wide_jets_puppi/runB_JSON/data_run3_summer22_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JeMET__Run2022C-PromptReco-v1_1_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JeMET__Run2022C-PromptReco-v1_2_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JeMET__Run2022C-PromptReco-v1_3_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JetHT__Run2022C-PromptReco-v1_1_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JetHT__Run2022C-PromptReco-v1_2_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JetHT__Run2022C-PromptReco-v1_3_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JeMET__Run2022D-PromptReco-v1_1_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JeMET__Run2022D-PromptReco-v2_1_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JeMET__Run2022D-PromptReco-v2_2_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JeMET__Run2022D-PromptReco-v2_3_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JeMET__Run2022D-PromptReco-v2_4_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/run3/wide_dijets_reduced_data/JeMET__Run2022D-PromptReco-v2_5_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runE/data_run3_summer22_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_0_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_1_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_2_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_3_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_4_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_5_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_6_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_7_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_8_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_9_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_10_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_11_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_12_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_13_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_14_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_15_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_16_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_17_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_18_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_19_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_20_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_21_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_22_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_23_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_24_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/maria/13p6_dijets/puppi/runF/data_run3_runF_summer22_25_reduced_skim.root");

  tree_data->SetBranchAddress("run",&run);
  tree_data->SetBranchAddress("lumi",&lumi);
  tree_data->SetBranchAddress("event",&event);
  tree_data->SetBranchAddress("mjj",&DijetMass);
  tree_data->SetBranchAddress("deltaETAjj",&DeltaEtaJJ);
  tree_data->SetBranchAddress("deltaPHIjj",&DeltaPhiJJ);
  tree_data->SetBranchAddress("pTWJ_j1",&pTwj1);
  tree_data->SetBranchAddress("pTWJ_j2",&pTwj2);
  tree_data->SetBranchAddress("etaWJ_j1",&etawj1);
  tree_data->SetBranchAddress("etaWJ_j2",&etawj2);
  tree_data->SetBranchAddress("phiWJ_j1",&phiwj1);
  tree_data->SetBranchAddress("phiWJ_j2",&phiwj2);
  tree_data->SetBranchAddress("PassJSON",&PassJSON);
  tree_data->SetBranchAddress("chargedHadEnFrac_j1",&chargedHadEnFrac_j1);
  tree_data->SetBranchAddress("chargedHadEnFrac_j2",&chargedHadEnFrac_j2);
  tree_data->SetBranchAddress("neutrElectromFrac_j1",&neutrElectromFrac_j1);
  tree_data->SetBranchAddress("neutrElectromFrac_j2",&neutrElectromFrac_j2);
  tree_data->SetBranchAddress("neutrHadEnFrac_j1",&neutrHadEnFrac_j1);
  tree_data->SetBranchAddress("neutrHadEnFrac_j2",&neutrHadEnFrac_j2);

  Int_t nentries_data = (Int_t)tree_data->GetEntries();
  std::cout << "Data: Number of entries =  " << nentries_data << std::endl;

  for (int i=0; i<nentries_data; i++)
  {
	tree_data->GetEntry(i);

	if (i%1000000==0) cout << " done " << i << " from " << nentries_data << endl;
      
 	if(DijetMass>1607 && DeltaEtaJJ<1.1 && ( (doJSON==0) || (doJSON==1 && PassJSON==1) ) )
	{
		Run->Fill(run);

		DijetMass_vsRun->Fill(run, DijetMass);
		DeltaEtaJJ_vsRun->Fill(run, DeltaEtaJJ);
		DeltaPhiJJ_vsRun->Fill(run, DeltaPhiJJ);
		pT_vsRun->Fill(run, pTwj1);
		pT_vsRun->Fill(run, pTwj2);
		eta_vsRun->Fill(run, etawj1);
		eta_vsRun->Fill(run, etawj2);
		phi_vsRun->Fill(run, phiwj1);
		phi_vsRun->Fill(run, phiwj2);
		CHF_vsRun->Fill(run, chargedHadEnFrac_j1);
		CHF_vsRun->Fill(run, chargedHadEnFrac_j2);
		NEMF_vsRun->Fill(run, neutrElectromFrac_j1);
		NEMF_vsRun->Fill(run, neutrElectromFrac_j2);
		NHF_vsRun->Fill(run, neutrHadEnFrac_j1);
		NHF_vsRun->Fill(run, neutrHadEnFrac_j2);


		DijetMass_vsNvtx->Fill(nVtx, DijetMass);
		DeltaEtaJJ_vsNvtx->Fill(nVtx, DeltaEtaJJ);
		DeltaPhiJJ_vsNvtx->Fill(nVtx, DeltaPhiJJ);
		pT_vsNvtx->Fill(nVtx, pTwj1);
		pT_vsNvtx->Fill(nVtx, pTwj2);
		eta_vsNvtx->Fill(nVtx, etawj1);
		eta_vsNvtx->Fill(nVtx, etawj2);
		phi_vsNvtx->Fill(nVtx, phiwj1);
		phi_vsNvtx->Fill(nVtx, phiwj2);
		CHF_vsNvtx->Fill(nVtx, chargedHadEnFrac_j1);
		CHF_vsNvtx->Fill(nVtx, chargedHadEnFrac_j2);
		NEMF_vsNvtx->Fill(nVtx, neutrElectromFrac_j1);
		NEMF_vsNvtx->Fill(nVtx, neutrElectromFrac_j2);
		NHF_vsNvtx->Fill(nVtx, neutrHadEnFrac_j1);
		NHF_vsNvtx->Fill(nVtx, neutrHadEnFrac_j2);

    	}
  } 

  TFile *foutput;
  if(doJSON==0) foutput =  new TFile("output_dijets/Run2022BCDEF_29p6fb-1_dijets_stability.root","RECREATE");
  if(doJSON==1) foutput =  new TFile("output_dijets/Run2022BCDEF_29p6fb-1_dijets_stability_cert_new.root","RECREATE");

  foutput->cd();
   
  Run->Write();

  DijetMass_vsRun->Write();
  DeltaEtaJJ_vsRun->Write();
  DeltaPhiJJ_vsRun->Write();
  pT_vsRun->Write();
  eta_vsRun->Write();
  phi_vsRun->Write();
  CHF_vsRun->Write();
  NHF_vsRun->Write();
  NEMF_vsRun->Write();

  DijetMass_vsNvtx->Write();
  DeltaEtaJJ_vsNvtx->Write();
  DeltaPhiJJ_vsNvtx->Write();
  pT_vsNvtx->Write();
  eta_vsNvtx->Write();
  phi_vsNvtx->Write();
  CHF_vsNvtx->Write();
  NHF_vsNvtx->Write();
  NEMF_vsNvtx->Write();

  foutput->Close();

}

