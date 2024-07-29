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

void Create_alpha_Histos_Diquarks_AK4CHS(double width, double alpha_true, int Suu){

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
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



cout << "Width = " << width*100. << "%" << endl;
cout << "M(S) = " << Suu << " GeV, M(chi) = " << Suu*alpha_true << " GeV" << endl;


TH1D *h_alpha;

const int nAlphaBins = 13;
   
     
double AlphaBoundaries[nAlphaBins+1] = {0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.50};     


h_alpha = new TH1D("h_alpha","",nAlphaBins,AlphaBoundaries);


double FourjetMass, Maverage, Masymmetry, DeltaEtaJJ, DeltaR_First, DeltaR_Second, alpha;

TChain *tree_mc = new TChain("rootTupleTree/tree");

char fname[1024];

if(width!=0.0043) sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_NOMINAL/RunIISummer20UL18_Suu-Diquark_W-%s_S-%d_chi-%.0f__AK4CHS_reduced_skim.root",width_name,Suu,Suu*alpha_true);

if(width==0.0043) sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/reduced_trees/Suu_Diquarks/RunIIFall17MiniAODv2/MC2017_Suu_Diquark_S%d_chi%.0f_reduced_skim.root",Suu,Suu*alpha_true);

cout << "Reduced file used: " << fname << endl;

tree_mc->Add(fname);

if(width!=0.0043)
{
    tree_mc->SetBranchAddress("FourjetMassAK4CHS",&FourjetMass);
    tree_mc->SetBranchAddress("MaverageAK4CHS",&Maverage);
    tree_mc->SetBranchAddress("MasymmetryAK4CHS",&Masymmetry);	
    tree_mc->SetBranchAddress("DeltaEtaJJAK4CHS",&DeltaEtaJJ);
    tree_mc->SetBranchAddress("DeltaRAK4CHS_First",&DeltaR_First);
    tree_mc->SetBranchAddress("DeltaRAK4CHS_Second",&DeltaR_Second);
}
else
{
    tree_mc->SetBranchAddress("FourjetMass",&FourjetMass);
    tree_mc->SetBranchAddress("Maverage",&Maverage);
    tree_mc->SetBranchAddress("Masymmetry",&Masymmetry);	
    tree_mc->SetBranchAddress("DeltaEtaJJAK4",&DeltaEtaJJ);
    tree_mc->SetBranchAddress("DeltaRAK4_First",&DeltaR_First);
    tree_mc->SetBranchAddress("DeltaRAK4_Second",&DeltaR_Second);
}

Int_t nentries_mc = (Int_t)tree_mc->GetEntries();
std::cout << "MC: Number of entries =  " << nentries_mc << std::endl;

for (int i=0; i<nentries_mc; i++){ 

	tree_mc->GetEntry(i);

	if (i%20000==0) cout << " done " << i << " from " << nentries_mc << endl;

	alpha=Maverage/FourjetMass; 

	if(Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0 && alpha>0.1)
	{
		h_alpha->Fill(alpha);
	}


}// end of event loop

h_alpha->Scale(1./h_alpha->Integral());


char foutname[1024];

if(width!=0.0043) sprintf(foutname,"signal_histos_Alpha/AlphaShapes_Suu-Diquark_W-%s_S-%d_chi-%.0f.root",width_name,Suu,Suu*alpha_true);

if(width==0.0043) sprintf(foutname,"signal_histos_Alpha/AlphaShapes_Suu-Diquark_W-%s_S-%d_chi-%.0f.root",width_name,Suu,Suu*alpha_true);

TFile *fout = new TFile(foutname,"RECREATE");
fout->cd();

h_alpha->Write();


fout->Close();


}
