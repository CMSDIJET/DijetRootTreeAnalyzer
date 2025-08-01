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

void Create_Mass_Histos_Diquarks_AK4CHS(double width, double alpha_true, double Suu){

char width_name[1024];
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char alpha_true_name[1024];
if (alpha_true==0.11) sprintf(alpha_true_name,"0p11");
if (alpha_true==0.13) sprintf(alpha_true_name,"0p13");
if (alpha_true==0.15) sprintf(alpha_true_name,"0p15");
if (alpha_true==0.17) sprintf(alpha_true_name,"0p17");
if (alpha_true==0.19) sprintf(alpha_true_name,"0p19");
if (alpha_true==0.21) sprintf(alpha_true_name,"0p21");
if (alpha_true==0.23) sprintf(alpha_true_name,"0p23");
if (alpha_true==0.25) sprintf(alpha_true_name,"0p25");
if (alpha_true==0.27) sprintf(alpha_true_name,"0p27");
if (alpha_true==0.29) sprintf(alpha_true_name,"0p29");
if (alpha_true==0.31) sprintf(alpha_true_name,"0p31");
if (alpha_true==0.33) sprintf(alpha_true_name,"0p33");
if (alpha_true==0.42) sprintf(alpha_true_name,"0p42");


//cout << "Width = " << width*100. << "%" << endl;
//cout << "M(S) = " << Suu << " GeV, M(chi) = " << Suu*alpha_true << " GeV" << endl;


const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};
        


TH1D *h_FourjetMass_alphagt0p1 = new TH1D("h_FourjetMass_alphagt0p1","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin1 = new TH1D("h_FourjetMass_alphabin1","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin2 = new TH1D("h_FourjetMass_alphabin2","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin3 = new TH1D("h_FourjetMass_alphabin3","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin4 = new TH1D("h_FourjetMass_alphabin4","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin5 = new TH1D("h_FourjetMass_alphabin5","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin6 = new TH1D("h_FourjetMass_alphabin6","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin7 = new TH1D("h_FourjetMass_alphabin7","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin8 = new TH1D("h_FourjetMass_alphabin8","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin9 = new TH1D("h_FourjetMass_alphabin9","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin10 = new TH1D("h_FourjetMass_alphabin10","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin11 = new TH1D("h_FourjetMass_alphabin11","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin12 = new TH1D("h_FourjetMass_alphabin12","",nMassBins,massBoundaries);
TH1D *h_FourjetMass_alphabin13 = new TH1D("h_FourjetMass_alphabin13","",nMassBins,massBoundaries);


double FourjetMass, Maverage, Masymmetry, DeltaEtaJJ, DeltaR_First, DeltaR_Second, alpha;

TChain *tree_mc = new TChain("rootTupleTree/tree");

char fname[1024];

//NOMINAL
sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_NOMINAL/RunIISummer20UL18_Suu-Diquark_W-%s_S-%.0f_chi-%.0f__AK4CHS_reduced_skim.root",width_name,Suu,Suu*alpha_true);

//cout << "Reduced file used: " << fname << endl;

tree_mc->Add(fname);

tree_mc->SetBranchAddress("FourjetMassAK4CHS",&FourjetMass);
tree_mc->SetBranchAddress("MaverageAK4CHS",&Maverage);
tree_mc->SetBranchAddress("MasymmetryAK4CHS",&Masymmetry);	
tree_mc->SetBranchAddress("DeltaEtaJJAK4CHS",&DeltaEtaJJ);
tree_mc->SetBranchAddress("DeltaRAK4CHS_First",&DeltaR_First);
tree_mc->SetBranchAddress("DeltaRAK4CHS_Second",&DeltaR_Second);

Int_t nentries_mc = (Int_t)tree_mc->GetEntries();
//std::cout << "MC: Number of entries =  " << nentries_mc << std::endl;

for (int i=0; i<nentries_mc; i++){ 

	tree_mc->GetEntry(i);

	//if (i%20000==0) cout << " done " << i << " from " << nentries_mc << endl;

	alpha=Maverage/FourjetMass; 

	if(Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0)
	{
	    if(alpha>0.10)                h_FourjetMass_alphagt0p1->Fill(FourjetMass);
	    if(alpha>0.10 && alpha<0.12)  h_FourjetMass_alphabin1->Fill(FourjetMass);
	    if(alpha>0.12 && alpha<0.14)  h_FourjetMass_alphabin2->Fill(FourjetMass);
	    if(alpha>0.14 && alpha<0.16)  h_FourjetMass_alphabin3->Fill(FourjetMass);
	    if(alpha>0.16 && alpha<0.18)  h_FourjetMass_alphabin4->Fill(FourjetMass);
	    if(alpha>0.18 && alpha<0.20)  h_FourjetMass_alphabin5->Fill(FourjetMass);
	    if(alpha>0.20 && alpha<0.22)  h_FourjetMass_alphabin6->Fill(FourjetMass);
	    if(alpha>0.22 && alpha<0.24)  h_FourjetMass_alphabin7->Fill(FourjetMass);
	    if(alpha>0.24 && alpha<0.26)  h_FourjetMass_alphabin8->Fill(FourjetMass);
	    if(alpha>0.26 && alpha<0.28)  h_FourjetMass_alphabin9->Fill(FourjetMass);
	    if(alpha>0.28 && alpha<0.30)  h_FourjetMass_alphabin10->Fill(FourjetMass);
	    if(alpha>0.30 && alpha<0.32)  h_FourjetMass_alphabin11->Fill(FourjetMass);
	    if(alpha>0.32 && alpha<0.34)  h_FourjetMass_alphabin12->Fill(FourjetMass);
	    if(alpha>0.34)                h_FourjetMass_alphabin13->Fill(FourjetMass); 	
	}


}// end of event loop



char foutname[1024];

//NOMINAL
sprintf(foutname,"rootfiles/Suu-Diquark_W-%s_S-%.0f_chi-%.0f.root",width_name,Suu,Suu*alpha_true);


TFile *fout = new TFile(foutname,"RECREATE");
fout->cd();

h_FourjetMass_alphagt0p1->Write();
h_FourjetMass_alphabin1->Write();
h_FourjetMass_alphabin2->Write();
h_FourjetMass_alphabin3->Write();
h_FourjetMass_alphabin4->Write();
h_FourjetMass_alphabin5->Write();
h_FourjetMass_alphabin6->Write();
h_FourjetMass_alphabin7->Write();
h_FourjetMass_alphabin8->Write();
h_FourjetMass_alphabin9->Write();
h_FourjetMass_alphabin10->Write();
h_FourjetMass_alphabin11->Write();
h_FourjetMass_alphabin12->Write();
h_FourjetMass_alphabin13->Write();

fout->Close();


}
