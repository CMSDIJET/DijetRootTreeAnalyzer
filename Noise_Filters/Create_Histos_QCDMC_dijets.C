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

void Create_Histos_QCDMC_dijets(){

TH1D *h_DijetMass_mc;

TH1D *h_pT_mc, *h_pTwj1_mc, *h_pTwj2_mc;

TH1D *h_eta_mc, *h_etawj1_mc, *h_etawj2_mc;

TH1D *h_phi_mc, *h_phiwj1_mc, *h_phiwj2_mc;

TH1D *h_DeltaEtaJJ_mc, *h_DeltaPhiJJ_mc; 

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

h_DijetMass_mc = new TH1D("h_DijetMass_mc","",103,massBoundaries);

h_pT_mc = new TH1D("h_pT_mc","",75,0,6000);

h_pTwj1_mc = new TH1D("h_pTwj1_mc","",75,0,6000);
h_pTwj2_mc = new TH1D("h_pTwj2_mc","",75,0,6000);

h_eta_mc = new TH1D("h_eta_mc","",30,-3,3);

h_etawj1_mc = new TH1D("h_etawj1_mc","",30,-3,3);
h_etawj2_mc = new TH1D("h_etawj2_mc","",30,-3,3);

h_phi_mc = new TH1D("h_phi_mc","",32,-3.2,3.2);

h_phiwj1_mc = new TH1D("h_phiwj1_mc","",32,-3.2,3.2);
h_phiwj2_mc = new TH1D("h_phiwj2_mc","",32,-3.2,3.2);

h_DeltaEtaJJ_mc = new TH1D("h_DeltaEtaJJ_mc","",40,0,2);

h_DeltaPhiJJ_mc = new TH1D("h_DeltaPhiJJ_mc","",64,0,3.1416);

h_DijetMass_mc->Sumw2();
h_pT_mc->Sumw2();
h_pTwj1_mc->Sumw2();
h_pTwj2_mc->Sumw2();
h_eta_mc->Sumw2();
h_etawj1_mc->Sumw2();
h_etawj2_mc->Sumw2();
h_phi_mc->Sumw2();
h_phiwj1_mc->Sumw2();
h_phiwj2_mc->Sumw2();
h_DeltaEtaJJ_mc->Sumw2();
h_DeltaPhiJJ_mc->Sumw2();

double run, lumi, event, weight, nVtx, PassJSON, passFilter_BadChargedCandidate, passFilter_BadPFMuon, passFilter_EcalDeadCellTriggerPrimitive, passFilter_HBHENoise, passFilter_HBHENoiseIso, passFilter_eeBadSc, passFilter_globalSuperTightHalo2016, passFilter_goodVertices;
double DijetMass, DeltaEtaJJ, DeltaPhiJJ, METoverHT;
double pTwj1, pTwj2, etawj1, etawj2, phiwj1, phiwj2;


TChain *tree_mc = new TChain("rootTupleTree/tree");

tree_mc->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/dijets_Run3/reduced_trees/QCD_Winter22Run3_noise_filters/QCDFlatMC_Winter22_AK4PUPPI_with_NOISE_FILTERS_reduced_skim.root");

tree_mc->SetBranchAddress("run",&run);
tree_mc->SetBranchAddress("lumi",&lumi);
tree_mc->SetBranchAddress("event",&event);
tree_mc->SetBranchAddress("mjj",&DijetMass);
tree_mc->SetBranchAddress("deltaETAjj",&DeltaEtaJJ);
tree_mc->SetBranchAddress("deltaPHIjj",&DeltaPhiJJ);
tree_mc->SetBranchAddress("METoverHTAK8",&METoverHT);
tree_mc->SetBranchAddress("pTWJ_j1",&pTwj1);
tree_mc->SetBranchAddress("pTWJ_j2",&pTwj2);
tree_mc->SetBranchAddress("etaWJ_j1",&etawj1);
tree_mc->SetBranchAddress("etaWJ_j2",&etawj2);
tree_mc->SetBranchAddress("phiWJ_j1",&phiwj1);
tree_mc->SetBranchAddress("phiWJ_j2",&phiwj2);
tree_mc->SetBranchAddress("passFilter_BadChargedCandidate",&passFilter_BadChargedCandidate);
tree_mc->SetBranchAddress("passFilter_BadPFMuon",&passFilter_BadPFMuon);
tree_mc->SetBranchAddress("passFilter_EcalDeadCellTriggerPrimitive",&passFilter_EcalDeadCellTriggerPrimitive);
tree_mc->SetBranchAddress("passFilter_HBHENoise",&passFilter_HBHENoise);
tree_mc->SetBranchAddress("passFilter_HBHENoiseIso",&passFilter_HBHENoiseIso);
tree_mc->SetBranchAddress("passFilter_eeBadSc",&passFilter_eeBadSc);
tree_mc->SetBranchAddress("passFilter_globalSuperTightHalo2016",&passFilter_globalSuperTightHalo2016);
tree_mc->SetBranchAddress("passFilter_goodVertices",&passFilter_goodVertices);
tree_mc->SetBranchAddress("weight",&weight);


Int_t nentries_mc = (Int_t)tree_mc->GetEntries();
std::cout << "MC: Number of entries =  " << nentries_mc << std::endl;

for (int i=0; i<nentries_mc; i++){
	tree_mc->GetEntry(i);

	if (i%1000000==0) cout << " done " << i << " from " << nentries_mc << endl;
 

	//if(DijetMass>1607 && DeltaEtaJJ<1.1 && DeltaPhiJJ>2.7 && event!=13640402 && event!=14664628)
	if(DijetMass>1607 && DeltaEtaJJ<1.1 && DeltaPhiJJ>2.7 && event!=13640402 && event!=14664628 && passFilter_BadChargedCandidate==1)
	{
		h_DijetMass_mc->Fill(DijetMass, weight);
		h_DeltaEtaJJ_mc->Fill(DeltaEtaJJ, weight);
		h_DeltaPhiJJ_mc->Fill(DeltaPhiJJ, weight);

		h_pTwj1_mc->Fill(pTwj1, weight);
		h_pTwj2_mc->Fill(pTwj2, weight);
		h_pT_mc->Fill(pTwj1, weight);
		h_pT_mc->Fill(pTwj2, weight);

		h_etawj1_mc->Fill(etawj1, weight);
		h_etawj2_mc->Fill(etawj2, weight);
		h_eta_mc->Fill(etawj1, weight);
		h_eta_mc->Fill(etawj2, weight);

		h_phiwj1_mc->Fill(phiwj1, weight);
		h_phiwj2_mc->Fill(phiwj2, weight);
		h_phi_mc->Fill(phiwj1, weight);
		h_phi_mc->Fill(phiwj2, weight);
	}

}// end of event loop

TFile *fout = new TFile("Dijet_Analysis_etalt3/Histos_QCDFlatMC_AllSelCrit_AK4PUPPI_withBadChargedCandidate.root","RECREATE");
//TFile *fout = new TFile("Dijet_Analysis_etalt3/Histos_QCDFlatMC_AllSelCrit_AK4PUPPI_withoutNoiseFilters.root","RECREATE");
fout->cd();

h_DijetMass_mc->Write();
h_pT_mc->Write();
h_pTwj1_mc->Write();
h_pTwj2_mc->Write();
h_eta_mc->Write();
h_etawj1_mc->Write();
h_etawj2_mc->Write();
h_phi_mc->Write();
h_phiwj1_mc->Write();
h_phiwj2_mc->Write();
h_DeltaEtaJJ_mc->Write();
h_DeltaPhiJJ_mc->Write();

fout->Close();


}
