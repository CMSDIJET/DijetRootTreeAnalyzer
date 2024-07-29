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

void Create_Mass_Histos_Diquarks_AK4CHS(double width, double alpha_true, int Suu, int alphabin){

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

double alpha_low, alpha_high;
char alphabin_name[1024];
if (alphabin==1) {alpha_low = 0.10; alpha_high = 0.12; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==2) {alpha_low = 0.12; alpha_high = 0.14; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==3) {alpha_low = 0.14; alpha_high = 0.16; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==4) {alpha_low = 0.16; alpha_high = 0.18; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==5) {alpha_low = 0.18; alpha_high = 0.20; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==6) {alpha_low = 0.20; alpha_high = 0.22; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==7) {alpha_low = 0.22; alpha_high = 0.24; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==8) {alpha_low = 0.24; alpha_high = 0.26; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==9) {alpha_low = 0.26; alpha_high = 0.28; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==10) {alpha_low = 0.28; alpha_high = 0.30; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==11) {alpha_low = 0.30; alpha_high = 0.32; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==12) {alpha_low = 0.32; alpha_high = 0.34; sprintf(alphabin_name,"alphabin%d",alphabin);}
if (alphabin==13) {alpha_low = 0.34; alpha_high = 100.; sprintf(alphabin_name,"alphabin%d",alphabin);}

if (alphabin==0) {alpha_low = 0.10; alpha_high = 100.; sprintf(alphabin_name,"alphagt0p1");} //for inclusive


cout << "Width = " << width*100. << "%" << endl;
cout << "M(S) = " << Suu << " GeV, M(chi) = " << Suu*alpha_true << " GeV" << endl;
cout << "Alpha bin: [" << alpha_low << ", " << alpha_high << "]" << endl;


TH1D *h_FourjetMass, *h_FourjetMass1GeV, *h_FourjetMass100GeV, *h_Maverage;


//const int nMassBins = 103;
const int nMassBins = 35;
   
//double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
//     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
//     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
//     4509,
//     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
//     10430,
//     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};
     
double massBoundaries[nMassBins+1] = {1, 10, 31, 61, 103, 156, 220, 296, 386, 489, 606, 740, 890, 1058, 1246, 1455, 1687, 1945, 2231, 2546, 2895, 3279, 3704, 4171, 4686, 5253, 5877, 6564, 7320, 8152, 9067, 10072, 11179, 12395, 13732, 14000};     


h_FourjetMass = new TH1D("h_FourjetMass","",nMassBins,massBoundaries);
h_FourjetMass1GeV = new TH1D("h_FourjetMass1GeV","",13999,1,14000);
h_FourjetMass100GeV = new TH1D("h_FourjetMass100GeV","",140,0,14000);
h_Maverage = new TH1D("h_Maverage","",nMassBins,massBoundaries);

double FourjetMass, Maverage, Masymmetry, DeltaEtaJJ, DeltaR_First, DeltaR_Second, alpha;

TChain *tree_mc = new TChain("rootTupleTree/tree");

char fname[1024];

//NOMINAL
if(width!=0.0043) sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_NOMINAL/RunIISummer20UL18_Suu-Diquark_W-%s_S-%d_chi-%.0f__AK4CHS_reduced_skim.root",width_name,Suu,Suu*alpha_true);

//JESup
//if(width!=0.0043) sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_JESup/RunIISummer20UL18_Suu-Diquark_W-%s_S-%d_chi-%.0f__AK4CHS_reduced_skim.root",width_name,Suu,Suu*alpha_true);

//JESdown
//if(width!=0.0043) sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_JESdown/RunIISummer20UL18_Suu-Diquark_W-%s_S-%d_chi-%.0f__AK4CHS_reduced_skim.root",width_name,Suu,Suu*alpha_true);

//JERup
//if(width!=0.0043) sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_JERup/RunIISummer20UL18_Suu-Diquark_W-%s_S-%d_chi-%.0f__AK4CHS_reduced_skim.root",width_name,Suu,Suu*alpha_true);

if(width==0.0043) sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/reduced_trees/Suu_Diquarks/RunIIFall17MiniAODv2/MC2017_Suu_Diquark_S%d_chi%.0f_reduced_skim.root",Suu,Suu*alpha_true);

cout << "Reduced file used: " << fname << endl;

tree_mc->Add(fname);

tree_mc->SetBranchAddress("FourjetMassAK4CHS",&FourjetMass);
tree_mc->SetBranchAddress("MaverageAK4CHS",&Maverage);
tree_mc->SetBranchAddress("MasymmetryAK4CHS",&Masymmetry);	
tree_mc->SetBranchAddress("DeltaEtaJJAK4CHS",&DeltaEtaJJ);
tree_mc->SetBranchAddress("DeltaRAK4CHS_First",&DeltaR_First);
tree_mc->SetBranchAddress("DeltaRAK4CHS_Second",&DeltaR_Second);

//tree_mc->SetBranchAddress("FourjetMass",&FourjetMass);
//tree_mc->SetBranchAddress("Maverage",&Maverage);
//tree_mc->SetBranchAddress("Masymmetry",&Masymmetry);	
//tree_mc->SetBranchAddress("DeltaEtaJJAK4",&DeltaEtaJJ);
//tree_mc->SetBranchAddress("DeltaRAK4_First",&DeltaR_First);
//tree_mc->SetBranchAddress("DeltaRAK4_Second",&DeltaR_Second);

Int_t nentries_mc = (Int_t)tree_mc->GetEntries();
std::cout << "MC: Number of entries =  " << nentries_mc << std::endl;

for (int i=0; i<nentries_mc; i++){ 

	tree_mc->GetEntry(i);

	if (i%20000==0) cout << " done " << i << " from " << nentries_mc << endl;

	alpha=Maverage/FourjetMass; 

	if(Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0 && alpha>alpha_low && alpha<alpha_high)
	//if(FourjetMass>0)
	{
		h_FourjetMass->Fill(FourjetMass);
		h_FourjetMass1GeV->Fill(FourjetMass);
		h_FourjetMass100GeV->Fill(FourjetMass);
		h_Maverage->Fill(Maverage);
	}


}// end of event loop

h_FourjetMass->Scale(1./h_FourjetMass->Integral());
h_FourjetMass1GeV->Scale(1./h_FourjetMass1GeV->Integral());
h_FourjetMass100GeV->Scale(1./h_FourjetMass100GeV->Integral());
h_Maverage->Scale(1./h_Maverage->Integral());

char foutname[1024];

//NOMINAL
if(width!=0.0043) sprintf(foutname,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/Rebinned_ResonanceShapes_NOMINAL_Suu-Diquark_W-%s_S-%d_chi-%.0f_%s.root",alpha_true_name,width_name,Suu,Suu*alpha_true,alphabin_name);

//JESup
//if(width!=0.0043) sprintf(foutname,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_JESup_Suu-Diquark_W-%s_S-%d_chi-%.0f_%s.root",alpha_true_name,width_name,Suu,Suu*alpha_true,alphabin_name);

//JESdown
//if(width!=0.0043) sprintf(foutname,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_JESdown_Suu-Diquark_W-%s_S-%d_chi-%.0f_%s.root",alpha_true_name,width_name,Suu,Suu*alpha_true,alphabin_name);

//JERUp
//if(width!=0.0043) sprintf(foutname,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_JERup_Suu-Diquark_W-%s_S-%d_chi-%.0f_%s.root",alpha_true_name,width_name,Suu,Suu*alpha_true,alphabin_name);

if(width==0.0043) sprintf(foutname,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/Rebinned_ResonanceShapes_NOMINAL_Suu-Diquark_W-%s_S-%d_chi-%.0f_%s.root",alpha_true_name,width_name,Suu,Suu*alpha_true,alphabin_name);

TFile *fout = new TFile(foutname,"RECREATE");
fout->cd();

h_FourjetMass1GeV->Write();
h_FourjetMass100GeV->Write();
h_FourjetMass->Write();
h_Maverage->Write();

fout->Close();


}
