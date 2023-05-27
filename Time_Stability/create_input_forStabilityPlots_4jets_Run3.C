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


void create_input_forStabilityPlots_4jets_Run3(Int_t doJSON)
{
  const int nMassBins = 103;
   
  double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};


  TH2F *METoverHT_vsRun;
  TH2F *FourjetMass_vsRun, *Maverage_vsRun, *alpha_vsRun, *Masymmetry_vsRun, *DeltaEtaJJ_vsRun, *DeltaPhiJJ_vsRun, *DeltaR1_vsRun, *DeltaR2_vsRun;
  TH2F *pT_vsRun, *eta_vsRun, *phi_vsRun, *CHF_vsRun, *NHF_vsRun, *NEMF_vsRun; 

  TH2F *METoverHT_vsNvtx;
  TH2F *FourjetMass_vsNvtx, *Maverage_vsNvtx, *alpha_vsNvtx, *Masymmetry_vsNvtx, *DeltaEtaJJ_vsNvtx, *DeltaPhiJJ_vsNvtx, *DeltaR1_vsNvtx, *DeltaR2_vsNvtx;
  TH2F *pT_vsNvtx, *eta_vsNvtx, *phi_vsNvtx, *CHF_vsNvtx, *NHF_vsNvtx, *NEMF_vsNvtx;

  TH1F *Run;
 
  int run_start = 355374;
  int run_end   = 362104;
  int nbins     = run_end-run_start;

  Run = new TH1F ("Run","",nbins, run_start, run_end);

  METoverHT_vsRun = new TH2F ("METoverHT_vsRun","",nbins, run_start, run_end,100,0,1);
  FourjetMass_vsRun = new TH2F ("FourjetMass_vsRun","",nbins, run_start, run_end, nMassBins,massBoundaries);
  Maverage_vsRun = new TH2F ("Maverage_vsRun","",nbins, run_start, run_end, nMassBins,massBoundaries);
  alpha_vsRun = new TH2F("alpha_vsRun","",nbins, run_start, run_end, 50,0,0.5);
  Masymmetry_vsRun = new TH2F ("Masymmetry_vsRun","",nbins, run_start, run_end, 40,0,0.2);
  DeltaEtaJJ_vsRun = new TH2F ("DeltaEtaJJ_vsRun","",nbins, run_start, run_end, 40,0,2);
  DeltaPhiJJ_vsRun = new TH2F ("DeltaPhiJJ_vsRun","",nbins, run_start, run_end, 64,0,3.1416);
  DeltaR1_vsRun = new TH2F ("DeltaR1_vsRun","",nbins, run_start, run_end, 40,0,4);
  DeltaR2_vsRun = new TH2F ("DeltaR2_vsRun","",nbins, run_start, run_end, 40,0,4);
  pT_vsRun = new TH2F ("pT_vsRun","",nbins, run_start, run_end, 75,0,6000);
  eta_vsRun = new TH2F ("eta_vsRun","",nbins, run_start, run_end, 30,-3,3);
  phi_vsRun = new TH2F ("phi_vsRun","",nbins, run_start, run_end, 32,-3.2,3.2);
  CHF_vsRun = new TH2F ("CHF_vsRun","",nbins, run_start, run_end, 60,0,1.2);
  NHF_vsRun = new TH2F ("NHF_vsRun","",nbins, run_start, run_end, 60,0,1.2);
  NEMF_vsRun = new TH2F ("NEMF_vsRun","",nbins, run_start, run_end, 60,0,1.2);

  METoverHT_vsNvtx = new TH2F ("METoverHT_vsNvtx","",100, 0, 100,100,0,1);
  FourjetMass_vsNvtx = new TH2F ("FourjetMass_vsNvtx","",100, 0, 100, nMassBins,massBoundaries);
  Maverage_vsNvtx = new TH2F ("Maverage_vsNvtx","",100, 0, 100, nMassBins,massBoundaries);
  alpha_vsNvtx = new TH2F("alpha_vsNvtx","",100, 0, 100, 50,0,0.5);
  Masymmetry_vsNvtx = new TH2F ("Masymmetry_vsNvtx","",100, 0, 100, 40,0,0.2);
  DeltaEtaJJ_vsNvtx = new TH2F ("DeltaEtaJJ_vsNvtx","",100, 0, 100, 40,0,2);
  DeltaPhiJJ_vsNvtx = new TH2F ("DeltaPhiJJ_vsNvtx","",100, 0, 100, 64,0,3.1416);
  DeltaR1_vsNvtx = new TH2F ("DeltaR1_vsNvtx","",100, 0, 100, 40,0,4);
  DeltaR2_vsNvtx = new TH2F ("DeltaR2_vsNvtx","",100, 0, 100, 40,0,4);
  pT_vsNvtx = new TH2F ("pT_vsNvtx","",100, 0, 100, 75,0,6000);
  eta_vsNvtx = new TH2F ("eta_vsNvtx","",100, 0, 100, 30,-3,3);
  phi_vsNvtx = new TH2F ("phi_vsNvtx","",100, 0, 100, 32,-3.2,3.2);
  CHF_vsNvtx = new TH2F ("CHF_vsNvtx","",100, 0, 100, 60,0,1.2);
  NHF_vsNvtx = new TH2F ("NHF_vsNvtx","",100, 0, 100, 60,0,1.2);
  NEMF_vsNvtx = new TH2F ("NEMF_vsNvtx","",100, 0, 100, 60,0,1.2);


   /////////initialize variables

  double run, lumi, event, weight, nVtx, PassJSON;
  double FourjetMass, Maverage, Masymmetry, DeltaEtaJJ, DeltaPhiJJ, DeltaR_First, DeltaR_Second, alpha, METoverHT;
  double pTj1, pTj2, pTj3, pTj4, etaj1, etaj2, etaj3, etaj4, phij1, phij2, phij3, phij4;
  double chargedHadEnFrac_j1, chargedHadEnFrac_j2, chargedHadEnFrac_j3, chargedHadEnFrac_j4, neutrElectromFrac_j1, neutrElectromFrac_j2, neutrElectromFrac_j3, neutrElectromFrac_j4, neutrHadEnFrac_j1, neutrHadEnFrac_j2, neutrHadEnFrac_j3, neutrHadEnFrac_j4;

  TChain *tree_data = new TChain("rootTupleTree/tree");

  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetHT__Run2022B-PromptReco-v1__AK4PUPPI_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetHT__Run2022C-PromptReco-v1__AK4PUPPI_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022C-PromptReco-v1__AK4PUPPI_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022D-PromptReco-v1__AK4PUPPI_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022D-PromptReco-v2__AK4PUPPI_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022E-PromptReco-v1__AK4PUPPI_reduced_skim.root");
  tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022F-PromptReco-v1__AK4PUPPI_reduced_skim.root");

  tree_data->SetBranchAddress("run",&run);
  tree_data->SetBranchAddress("lumi",&lumi);
  tree_data->SetBranchAddress("event",&event);
  tree_data->SetBranchAddress("FourjetMassAK4PUPPI",&FourjetMass);
  tree_data->SetBranchAddress("MaverageAK4PUPPI",&Maverage);
  tree_data->SetBranchAddress("MasymmetryAK4PUPPI",&Masymmetry);
  tree_data->SetBranchAddress("DeltaEtaJJAK4PUPPI",&DeltaEtaJJ);
  tree_data->SetBranchAddress("DeltaPhiJJAK4PUPPI",&DeltaPhiJJ);
  tree_data->SetBranchAddress("DeltaRAK4PUPPI_First",&DeltaR_First);
  tree_data->SetBranchAddress("DeltaRAK4PUPPI_Second",&DeltaR_Second);
  tree_data->SetBranchAddress("METoverHTAK4PUPPI",&METoverHT);
  tree_data->SetBranchAddress("pTAK4PUPPI_j1",&pTj1);
  tree_data->SetBranchAddress("pTAK4PUPPI_j2",&pTj2);
  tree_data->SetBranchAddress("pTAK4PUPPI_j3",&pTj3);
  tree_data->SetBranchAddress("pTAK4PUPPI_j4",&pTj4);
  tree_data->SetBranchAddress("etaAK4PUPPI_j1",&etaj1);
  tree_data->SetBranchAddress("etaAK4PUPPI_j2",&etaj2);
  tree_data->SetBranchAddress("etaAK4PUPPI_j3",&etaj3);
  tree_data->SetBranchAddress("etaAK4PUPPI_j4",&etaj4);
  tree_data->SetBranchAddress("phiAK4PUPPI_j1",&phij1);
  tree_data->SetBranchAddress("phiAK4PUPPI_j2",&phij2);
  tree_data->SetBranchAddress("phiAK4PUPPI_j3",&phij3);
  tree_data->SetBranchAddress("phiAK4PUPPI_j4",&phij4);
  tree_data->SetBranchAddress("chargedHadEnFracAK4PUPPI_j1",&chargedHadEnFrac_j1);
  tree_data->SetBranchAddress("chargedHadEnFracAK4PUPPI_j2",&chargedHadEnFrac_j2);
  tree_data->SetBranchAddress("chargedHadEnFracAK4PUPPI_j3",&chargedHadEnFrac_j3);
  tree_data->SetBranchAddress("chargedHadEnFracAK4PUPPI_j4",&chargedHadEnFrac_j4);
  tree_data->SetBranchAddress("neutrElectromFracAK4PUPPI_j1",&neutrElectromFrac_j1);
  tree_data->SetBranchAddress("neutrElectromFracAK4PUPPI_j2",&neutrElectromFrac_j2);
  tree_data->SetBranchAddress("neutrElectromFracAK4PUPPI_j3",&neutrElectromFrac_j3);
  tree_data->SetBranchAddress("neutrElectromFracAK4PUPPI_j4",&neutrElectromFrac_j4);
  tree_data->SetBranchAddress("neutrHadEnFracAK4PUPPI_j1",&neutrHadEnFrac_j1);
  tree_data->SetBranchAddress("neutrHadEnFracAK4PUPPI_j2",&neutrHadEnFrac_j2);
  tree_data->SetBranchAddress("neutrHadEnFracAK4PUPPI_j3",&neutrHadEnFrac_j3);
  tree_data->SetBranchAddress("neutrHadEnFracAK4PUPPI_j4",&neutrHadEnFrac_j4);
  tree_data->SetBranchAddress("nVtx",&nVtx);
  tree_data->SetBranchAddress("PassJSON",&PassJSON);

  Int_t nentries_data = (Int_t)tree_data->GetEntries();
  std::cout << "Data: Number of entries =  " << nentries_data << std::endl;

  for (int i=0; i<nentries_data; i++)
  {
	tree_data->GetEntry(i);

	if (i%1000000==0) cout << " done " << i << " from " << nentries_data << endl;

	alpha=Maverage/FourjetMass; 
      
 	//if(FourjetMass>1607 && Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0 && alpha>0.1 && ( (doJSON==0) || (doJSON==1 && PassJSON==1) ) )
 	if(FourjetMass>1607 && DeltaEtaJJ<1.1 && ( (doJSON==0) || (doJSON==1 && PassJSON==1) ) )
	{
		Run->Fill(run);

		FourjetMass_vsRun->Fill(run, FourjetMass);
		Maverage_vsRun->Fill(run, Maverage); 
		Masymmetry_vsRun->Fill(run, Masymmetry);
		DeltaEtaJJ_vsRun->Fill(run, DeltaEtaJJ);
		DeltaPhiJJ_vsRun->Fill(run, DeltaPhiJJ);
		DeltaR1_vsRun->Fill(run, DeltaR_First);
		DeltaR2_vsRun->Fill(run, DeltaR_Second);
		METoverHT_vsRun->Fill(run, METoverHT);
		alpha_vsRun->Fill(run, alpha);
		pT_vsRun->Fill(run, pTj1);
		pT_vsRun->Fill(run, pTj2);
		pT_vsRun->Fill(run, pTj3);
		pT_vsRun->Fill(run, pTj4);
		eta_vsRun->Fill(run, etaj1);
		eta_vsRun->Fill(run, etaj2);
		eta_vsRun->Fill(run, etaj3);
		eta_vsRun->Fill(run, etaj4);
		phi_vsRun->Fill(run, phij1);
		phi_vsRun->Fill(run, phij2);
		phi_vsRun->Fill(run, phij3);
		phi_vsRun->Fill(run, phij4);
		CHF_vsRun->Fill(run, chargedHadEnFrac_j1);
		CHF_vsRun->Fill(run, chargedHadEnFrac_j2);
		CHF_vsRun->Fill(run, chargedHadEnFrac_j3);
		CHF_vsRun->Fill(run, chargedHadEnFrac_j4);
		NEMF_vsRun->Fill(run, neutrElectromFrac_j1);
		NEMF_vsRun->Fill(run, neutrElectromFrac_j2);
		NEMF_vsRun->Fill(run, neutrElectromFrac_j3);
		NEMF_vsRun->Fill(run, neutrElectromFrac_j4);
		NHF_vsRun->Fill(run, neutrHadEnFrac_j1);
		NHF_vsRun->Fill(run, neutrHadEnFrac_j2);
		NHF_vsRun->Fill(run, neutrHadEnFrac_j3);
		NHF_vsRun->Fill(run, neutrHadEnFrac_j4);


		FourjetMass_vsNvtx->Fill(nVtx, FourjetMass);
		Maverage_vsNvtx->Fill(nVtx, Maverage); 
		Masymmetry_vsNvtx->Fill(nVtx, Masymmetry);
		DeltaEtaJJ_vsNvtx->Fill(nVtx, DeltaEtaJJ);
		DeltaPhiJJ_vsNvtx->Fill(nVtx, DeltaPhiJJ);
		DeltaR1_vsNvtx->Fill(nVtx, DeltaR_First);
		DeltaR2_vsNvtx->Fill(nVtx, DeltaR_Second);
		METoverHT_vsNvtx->Fill(nVtx, METoverHT);
		alpha_vsNvtx->Fill(nVtx, alpha);
		pT_vsNvtx->Fill(nVtx, pTj1);
		pT_vsNvtx->Fill(nVtx, pTj2);
		pT_vsNvtx->Fill(nVtx, pTj3);
		pT_vsNvtx->Fill(nVtx, pTj4);
		eta_vsNvtx->Fill(nVtx, etaj1);
		eta_vsNvtx->Fill(nVtx, etaj2);
		eta_vsNvtx->Fill(nVtx, etaj3);
		eta_vsNvtx->Fill(nVtx, etaj4);
		phi_vsNvtx->Fill(nVtx, phij1);
		phi_vsNvtx->Fill(nVtx, phij2);
		phi_vsNvtx->Fill(nVtx, phij3);
		phi_vsNvtx->Fill(nVtx, phij4);
		CHF_vsNvtx->Fill(nVtx, chargedHadEnFrac_j1);
		CHF_vsNvtx->Fill(nVtx, chargedHadEnFrac_j2);
		CHF_vsNvtx->Fill(nVtx, chargedHadEnFrac_j3);
		CHF_vsNvtx->Fill(nVtx, chargedHadEnFrac_j4);
		NEMF_vsNvtx->Fill(nVtx, neutrElectromFrac_j1);
		NEMF_vsNvtx->Fill(nVtx, neutrElectromFrac_j2);
		NEMF_vsNvtx->Fill(nVtx, neutrElectromFrac_j3);
		NEMF_vsNvtx->Fill(nVtx, neutrElectromFrac_j4);
		NHF_vsNvtx->Fill(nVtx, neutrHadEnFrac_j1);
		NHF_vsNvtx->Fill(nVtx, neutrHadEnFrac_j2);
		NHF_vsNvtx->Fill(nVtx, neutrHadEnFrac_j3);
		NHF_vsNvtx->Fill(nVtx, neutrHadEnFrac_j4);

    	}
  } 

  TFile *foutput;
  if(doJSON==0) foutput =  new TFile("output_4jets/Run2022BCDEF_29p8fb-1_stability_onlyMassAndDeltaEtaCut.root","RECREATE");
  if(doJSON==1) foutput =  new TFile("output_4jets/Run2022BCDEF_29p8fb-1_stability_onlyMassAndDeltaEtaCut_cert.root","RECREATE");

  foutput->cd();
   
  Run->Write();

  FourjetMass_vsRun->Write();
  Maverage_vsRun->Write();
  Masymmetry_vsRun->Write();
  DeltaEtaJJ_vsRun->Write();
  DeltaPhiJJ_vsRun->Write();
  DeltaR1_vsRun->Write();
  DeltaR2_vsRun->Write();
  METoverHT_vsRun->Write();
  alpha_vsRun->Write();
  pT_vsRun->Write();
  eta_vsRun->Write();
  phi_vsRun->Write();
  CHF_vsRun->Write();
  NHF_vsRun->Write();
  NEMF_vsRun->Write();

  FourjetMass_vsNvtx->Write();
  Maverage_vsNvtx->Write();
  Masymmetry_vsNvtx->Write();
  DeltaEtaJJ_vsNvtx->Write();
  DeltaPhiJJ_vsNvtx->Write();
  DeltaR1_vsNvtx->Write();
  DeltaR2_vsNvtx->Write();
  METoverHT_vsNvtx->Write();
  alpha_vsNvtx->Write();
  pT_vsNvtx->Write();
  eta_vsNvtx->Write();
  phi_vsNvtx->Write();
  CHF_vsNvtx->Write();
  NHF_vsNvtx->Write();
  NEMF_vsNvtx->Write();

  foutput->Close();

}

