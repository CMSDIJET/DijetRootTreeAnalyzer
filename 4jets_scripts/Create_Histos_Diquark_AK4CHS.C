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

void Create_Histos_Diquark_AK4CHS(double width, int Suu, int Chi, int alphabin){

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

double alpha_low, alpha_high;
char alpha_name[1024];
if (alphabin==1) {alpha_low = 0.10; alpha_high = 0.12; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==2) {alpha_low = 0.12; alpha_high = 0.14; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==3) {alpha_low = 0.14; alpha_high = 0.16; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==4) {alpha_low = 0.16; alpha_high = 0.18; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==5) {alpha_low = 0.18; alpha_high = 0.20; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==6) {alpha_low = 0.20; alpha_high = 0.22; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==7) {alpha_low = 0.22; alpha_high = 0.24; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==8) {alpha_low = 0.24; alpha_high = 0.26; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==9) {alpha_low = 0.26; alpha_high = 0.28; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==10) {alpha_low = 0.28; alpha_high = 0.30; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==11) {alpha_low = 0.30; alpha_high = 0.32; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==12) {alpha_low = 0.32; alpha_high = 0.34; sprintf(alpha_name,"alphabin%d",alphabin);}
if (alphabin==13) {alpha_low = 0.34; alpha_high = 100.; sprintf(alpha_name,"alphabin%d",alphabin);}

if (alphabin==0) {alpha_low = 0.10; alpha_high = 100.; sprintf(alpha_name,"alphagt0p1");} //for inclusive


cout << "Width = " << width*100. << "%" << endl;
cout << "M(S) = " << Suu << " GeV, M(chi) = " << Chi << " GeV" << endl;
cout << "Alpha bin: [" << alpha_low << ", " << alpha_high << "]" << endl;

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

const int nEtaBins = 82;

double EtaBins[nEtaBins+1] = {-5.191, -4.889, -4.716, -4.538, -4.363, -4.191, -4.013, -3.839, -3.664, 
	 -3.489, -3.314, -3.139, -2.964, -2.853, -2.650, -2.500, -2.322, -2.172, 
	 -2.043, -1.930, -1.830, -1.740, -1.653, -1.566, -1.479, -1.392, -1.305, 
	 -1.218, -1.131, -1.044, -0.957, -0.879, -0.783, -0.696, -0.609, -0.522, 
	 -0.435, -0.348, -0.261, -0.174, -0.087, 
	 +0.000,
	 +0.087, +0.174, +0.261, +0.348, +0.435, +0.522, +0.609, +0.696, +0.783, 
	 +0.879, +0.957, +1.044, +1.131, +1.218, +1.305, +1.392, +1.479, +1.566, 
	 +1.653, +1.740, +1.830, +1.930, +2.043, +2.172, +2.322, +2.500, +2.650, 
	 +2.853, +2.964, +3.139, +3.314, +3.489, +3.664, +3.839, +4.013, +4.191, 
	 +4.363, +4.538, +4.716, +4.889, +5.191};

TH1D *h_FourjetMass;
TH1D *h_FourjetMass1GeV;
TH1D *h_Maverage;
TH1D *h_Dijet_Mass_1;
TH1D *h_Dijet_Mass_2;
TH1D *h_alpha;
TH1D *h_pT, *h_pTj1, *h_pTj2, *h_pTj3, *h_pTj4;
TH1D *h_eta, *h_etaj1, *h_etaj2, *h_etaj3, *h_etaj4;
TH1D *h_phi, *h_phij1, *h_phij2, *h_phij3, *h_phij4;
TH1D *h_DeltaEtaJJ, *h_DeltaPhiJJ, *h_DeltaR_First, *h_DeltaR_Second, *h_METoverHT, *h_Masymmetry; 
TH1D *h_chargedElectromFrac, *h_chargedElectromFrac_j1, *h_chargedElectromFrac_j2, *h_chargedElectromFrac_j3, *h_chargedElectromFrac_j4, *h_chargedHadEnFrac, *h_chargedHadEnFrac_j1, *h_chargedHadEnFrac_j2, *h_chargedHadEnFrac_j3, *h_chargedHadEnFrac_j4, *h_neutrElectromFrac, *h_neutrElectromFrac_j1, *h_neutrElectromFrac_j2, *h_neutrElectromFrac_j3, *h_neutrElectromFrac_j4, *h_neutrHadEnFrac, *h_neutrHadEnFrac_j1, *h_neutrHadEnFrac_j2, *h_neutrHadEnFrac_j3, *h_neutrHadEnFrac_j4, *h_photonEnFrac, *h_photonEnFrac_j1, *h_photonEnFrac_j2, *h_photonEnFrac_j3, *h_photonEnFrac_j4, *h_muEnFrac, *h_muEnFrac_j1, *h_muEnFrac_j2, *h_muEnFrac_j3, *h_muEnFrac_j4;
TH1D *h_chargedMult, *h_chargedMult_j1, *h_chargedMult_j2, *h_chargedMult_j3, *h_chargedMult_j4, *h_neutrMult, *h_neutrMult_j1, *h_neutrMult_j2, *h_neutrMult_j3, *h_neutrMult_j4, *h_photonMult, *h_photonMult_j1, *h_photonMult_j2, *h_photonMult_j3, *h_photonMult_j4;
TH1D *h_nVtx;
TH2D *h_etaphi;


h_FourjetMass = new TH1D("h_FourjetMass","",103,massBoundaries);
h_FourjetMass1GeV = new TH1D("h_FourjetMass1GeV","",13999,1,14000);
h_Maverage = new TH1D("h_Maverage","",103,massBoundaries);
h_Dijet_Mass_1 = new TH1D("h_Dijet_Mass_1","",103,massBoundaries);
h_Dijet_Mass_2 = new TH1D("h_Dijet_Mass_2","",103,massBoundaries);
h_alpha = new TH1D("h_alpha","",50,0,0.5);
h_pT = new TH1D("h_pT","",85,0,6800);
h_pTj1 = new TH1D("h_pTj1","",85,0,6800);
h_pTj2 = new TH1D("h_pTj2","",85,0,6800);
h_pTj3 = new TH1D("h_pTj3","",85,0,6800);
h_pTj4 = new TH1D("h_pTj4","",85,0,6800);
h_eta = new TH1D("h_eta","",300,-3,3);
h_etaj1 = new TH1D("h_etaj1","",30,-3,3);
h_etaj2 = new TH1D("h_etaj2","",30,-3,3);
h_etaj3 = new TH1D("h_etaj3","",30,-3,3);
h_etaj4 = new TH1D("h_etaj4","",30,-3,3);
h_phi = new TH1D("h_phi","",36,-3.1416,3.1416);
h_phij1 = new TH1D("h_phij1","",36,-3.1416,3.1416);
h_phij2 = new TH1D("h_phij2","",36,-3.1416,3.1416);
h_phij3 = new TH1D("h_phij3","",36,-3.1416,3.1416);
h_phij4 = new TH1D("h_phij4","",36,-3.1416,3.1416);
h_DeltaEtaJJ = new TH1D("h_DeltaEtaJJ","",60,0,6);
h_DeltaPhiJJ = new TH1D("h_DeltaPhiJJ","",64,0,3.1416);
h_DeltaR_First = new TH1D("h_DeltaR_First","",30,0,6);
h_DeltaR_Second = new TH1D("h_DeltaR_Second","",30,0,6);
h_Masymmetry = new TH1D("h_Masymmetry","",100,0,1.);
h_METoverHT = new TH1D("h_METoverHT","",60,0,1.2);
h_chargedElectromFrac = new TH1D("h_chargedElectromFrac","",60,0,1.2);
h_chargedElectromFrac_j1 = new TH1D("h_chargedElectromFrac_j1","",60,0,1.2);
h_chargedElectromFrac_j2 = new TH1D("h_chargedElectromFrac_j2","",60,0,1.2);
h_chargedElectromFrac_j3 = new TH1D("h_chargedElectromFrac_j3","",60,0,1.2);
h_chargedElectromFrac_j4 = new TH1D("h_chargedElectromFrac_j4","",60,0,1.2);
h_chargedHadEnFrac = new TH1D("h_chargedHadEnFrac","",60,0,1.2);
h_chargedHadEnFrac_j1 = new TH1D("h_chargedHadEnFrac_j1","",60,0,1.2);
h_chargedHadEnFrac_j2 = new TH1D("h_chargedHadEnFrac_j2","",60,0,1.2);
h_chargedHadEnFrac_j3 = new TH1D("h_chargedHadEnFrac_j3","",60,0,1.2);
h_chargedHadEnFrac_j4 = new TH1D("h_chargedHadEnFrac_j4","",60,0,1.2);
h_neutrElectromFrac = new TH1D("h_neutrElectromFrac","",60,0,1.2);
h_neutrElectromFrac_j1 = new TH1D("h_neutrElectromFrac_j1","",60,0,1.2);
h_neutrElectromFrac_j2 = new TH1D("h_neutrElectromFrac_j2","",60,0,1.2);
h_neutrElectromFrac_j3 = new TH1D("h_neutrElectromFrac_j3","",60,0,1.2);
h_neutrElectromFrac_j4 = new TH1D("h_neutrElectromFrac_j4","",60,0,1.2);
h_neutrHadEnFrac = new TH1D("h_neutrHadEnFrac","",60,0,1.2);
h_neutrHadEnFrac_j1 = new TH1D("h_neutrHadEnFrac_j1","",60,0,1.2);
h_neutrHadEnFrac_j2 = new TH1D("h_neutrHadEnFrac_j2","",60,0,1.2);
h_neutrHadEnFrac_j3 = new TH1D("h_neutrHadEnFrac_j3","",60,0,1.2);
h_neutrHadEnFrac_j4 = new TH1D("h_neutrHadEnFrac_j4","",60,0,1.2);
h_photonEnFrac = new TH1D("h_photonEnFrac","",60,0,1.2);
h_photonEnFrac_j1 = new TH1D("h_photonEnFrac_j1","",60,0,1.2);
h_photonEnFrac_j2 = new TH1D("h_photonEnFrac_j2","",60,0,1.2);
h_photonEnFrac_j3 = new TH1D("h_photonEnFrac_j3","",60,0,1.2);
h_photonEnFrac_j4 = new TH1D("h_photonEnFrac_j4","",60,0,1.2);
h_muEnFrac = new TH1D("h_muEnFrac","",60,0,1.2);
h_muEnFrac_j1 = new TH1D("h_muEnFrac_j1","",60,0,1.2);
h_muEnFrac_j2 = new TH1D("h_muEnFrac_j2","",60,0,1.2);
h_muEnFrac_j3 = new TH1D("h_muEnFrac_j3","",60,0,1.2);
h_muEnFrac_j4 = new TH1D("h_muEnFrac_j4","",60,0,1.2);
h_chargedMult = new TH1D("h_chargedMult","",50,0,100);
h_chargedMult_j1 = new TH1D("h_chargedMult_j1","",50,0,100);
h_chargedMult_j2 = new TH1D("h_chargedMult_j2","",50,0,100);
h_chargedMult_j3 = new TH1D("h_chargedMult_j3","",50,0,100);
h_chargedMult_j4 = new TH1D("h_chargedMult_j4","",50,0,100);
h_neutrMult = new TH1D("h_neutrMult","",50,0,100);
h_neutrMult_j1 = new TH1D("h_neutrMult_j1","",50,0,100);
h_neutrMult_j2 = new TH1D("h_neutrMult_j2","",50,0,100);
h_neutrMult_j3 = new TH1D("h_neutrMult_j3","",50,0,100);
h_neutrMult_j4 = new TH1D("h_neutrMult_j4","",50,0,100);
h_photonMult = new TH1D("h_photonMult","",50,0,100);
h_photonMult_j1 = new TH1D("h_photonMult_j1","",50,0,100);
h_photonMult_j2 = new TH1D("h_photonMult_j2","",50,0,100);
h_photonMult_j3 = new TH1D("h_photonMult_j3","",50,0,100);
h_photonMult_j4 = new TH1D("h_photonMult_j4","",50,0,100);
h_nVtx = new TH1D("h_nVtx","",100,0,100);
h_etaphi = new TH2D("h_etaphi","",nEtaBins,EtaBins,72,-3.1415927,3.1415927);

double run, lumi, event, nVtx;
double FourjetMass, Maverage, Dijet_Mass_1, Dijet_Mass_2, Masymmetry, DeltaEtaJJ, DeltaPhiJJ, DeltaR_First, DeltaR_Second, alpha, METoverHT;
double pTj1, pTj2, pTj3, pTj4, etaj1, etaj2, etaj3, etaj4, phij1, phij2, phij3, phij4;
double chargedElectromFrac_j1, chargedElectromFrac_j2, chargedElectromFrac_j3, chargedElectromFrac_j4, chargedHadEnFrac_j1, chargedHadEnFrac_j2, chargedHadEnFrac_j3, chargedHadEnFrac_j4, neutrElectromFrac_j1, neutrElectromFrac_j2, neutrElectromFrac_j3, neutrElectromFrac_j4, neutrHadEnFrac_j1, neutrHadEnFrac_j2, neutrHadEnFrac_j3, neutrHadEnFrac_j4, photonEnFrac_j1, photonEnFrac_j2, photonEnFrac_j3, photonEnFrac_j4, muEnFrac_j1, muEnFrac_j2, muEnFrac_j3, muEnFrac_j4, chargedMult_j1, chargedMult_j2, chargedMult_j3, chargedMult_j4, neutrMult_j1, neutrMult_j2, neutrMult_j3, neutrMult_j4, photonMult_j1, photonMult_j2, photonMult_j3, photonMult_j4;	

TChain *tree_mc = new TChain("rootTupleTree/tree");

char fname[1024];
//sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/reduced_trees/Suu_Diquarks/RunIIFall17MiniAODv2/MC2017_Suu_Diquark_S%d_chi%d_reduced_skim.root",Suu,Chi);

sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_NOMINAL/RunIISummer20UL18_Suu-Diquark_W-%s_S-%d_chi-%d__AK4CHS_reduced_skim.root",width_name,Suu,Chi);

cout << "Reduced file: " << fname << endl;

tree_mc->Add(fname);

tree_mc->SetBranchAddress("run",&run);
tree_mc->SetBranchAddress("lumi",&lumi);
tree_mc->SetBranchAddress("event",&event);
tree_mc->SetBranchAddress("FourjetMassAK4CHS",&FourjetMass);
tree_mc->SetBranchAddress("MaverageAK4CHS",&Maverage);
tree_mc->SetBranchAddress("Dijet_MassAK4CHS_1",&Dijet_Mass_1);
tree_mc->SetBranchAddress("Dijet_MassAK4CHS_2",&Dijet_Mass_2);
tree_mc->SetBranchAddress("MasymmetryAK4CHS",&Masymmetry);
tree_mc->SetBranchAddress("DeltaEtaJJAK4CHS",&DeltaEtaJJ);
tree_mc->SetBranchAddress("DeltaPhiJJAK4CHS",&DeltaPhiJJ);
tree_mc->SetBranchAddress("DeltaRAK4CHS_First",&DeltaR_First);
tree_mc->SetBranchAddress("DeltaRAK4CHS_Second",&DeltaR_Second);
tree_mc->SetBranchAddress("METoverHTAK4CHS",&METoverHT);
tree_mc->SetBranchAddress("pTAK4CHS_j1",&pTj1);
tree_mc->SetBranchAddress("pTAK4CHS_j2",&pTj2);
tree_mc->SetBranchAddress("pTAK4CHS_j3",&pTj3);
tree_mc->SetBranchAddress("pTAK4CHS_j4",&pTj4);
tree_mc->SetBranchAddress("etaAK4CHS_j1",&etaj1);
tree_mc->SetBranchAddress("etaAK4CHS_j2",&etaj2);
tree_mc->SetBranchAddress("etaAK4CHS_j3",&etaj3);
tree_mc->SetBranchAddress("etaAK4CHS_j4",&etaj4);
tree_mc->SetBranchAddress("phiAK4CHS_j1",&phij1);
tree_mc->SetBranchAddress("phiAK4CHS_j2",&phij2);
tree_mc->SetBranchAddress("phiAK4CHS_j3",&phij3);
tree_mc->SetBranchAddress("phiAK4CHS_j4",&phij4);
tree_mc->SetBranchAddress("chargedElectromFracAK4CHS_j1",&chargedElectromFrac_j1);
tree_mc->SetBranchAddress("chargedElectromFracAK4CHS_j2",&chargedElectromFrac_j2);
tree_mc->SetBranchAddress("chargedElectromFracAK4CHS_j3",&chargedElectromFrac_j3);
tree_mc->SetBranchAddress("chargedElectromFracAK4CHS_j4",&chargedElectromFrac_j4);
tree_mc->SetBranchAddress("chargedHadEnFracAK4CHS_j1",&chargedHadEnFrac_j1);
tree_mc->SetBranchAddress("chargedHadEnFracAK4CHS_j2",&chargedHadEnFrac_j2);
tree_mc->SetBranchAddress("chargedHadEnFracAK4CHS_j3",&chargedHadEnFrac_j3);
tree_mc->SetBranchAddress("chargedHadEnFracAK4CHS_j4",&chargedHadEnFrac_j4);
tree_mc->SetBranchAddress("neutrElectromFracAK4CHS_j1",&neutrElectromFrac_j1);
tree_mc->SetBranchAddress("neutrElectromFracAK4CHS_j2",&neutrElectromFrac_j2);
tree_mc->SetBranchAddress("neutrElectromFracAK4CHS_j3",&neutrElectromFrac_j3);
tree_mc->SetBranchAddress("neutrElectromFracAK4CHS_j4",&neutrElectromFrac_j4);
tree_mc->SetBranchAddress("neutrHadEnFracAK4CHS_j1",&neutrHadEnFrac_j1);
tree_mc->SetBranchAddress("neutrHadEnFracAK4CHS_j2",&neutrHadEnFrac_j2);
tree_mc->SetBranchAddress("neutrHadEnFracAK4CHS_j3",&neutrHadEnFrac_j3);
tree_mc->SetBranchAddress("neutrHadEnFracAK4CHS_j4",&neutrHadEnFrac_j4);
tree_mc->SetBranchAddress("photonEnFracAK4CHS_j1",&photonEnFrac_j1);
tree_mc->SetBranchAddress("photonEnFracAK4CHS_j2",&photonEnFrac_j2);
tree_mc->SetBranchAddress("photonEnFracAK4CHS_j3",&photonEnFrac_j3);
tree_mc->SetBranchAddress("photonEnFracAK4CHS_j4",&photonEnFrac_j4);
tree_mc->SetBranchAddress("muEnFractAK4CHS_j1",&muEnFrac_j1);
tree_mc->SetBranchAddress("muEnFractAK4CHS_j2",&muEnFrac_j2);
tree_mc->SetBranchAddress("muEnFractAK4CHS_j3",&muEnFrac_j3);
tree_mc->SetBranchAddress("muEnFractAK4CHS_j4",&muEnFrac_j4);
tree_mc->SetBranchAddress("chargedMultAK4CHS_j1",&chargedMult_j1);
tree_mc->SetBranchAddress("chargedMultAK4CHS_j2",&chargedMult_j2);
tree_mc->SetBranchAddress("chargedMultAK4CHS_j3",&chargedMult_j3);
tree_mc->SetBranchAddress("chargedMultAK4CHS_j4",&chargedMult_j4);
tree_mc->SetBranchAddress("neutrMultAK4CHS_j1",&neutrMult_j1);
tree_mc->SetBranchAddress("neutrMultAK4CHS_j2",&neutrMult_j2);
tree_mc->SetBranchAddress("neutrMultAK4CHS_j3",&neutrMult_j3);
tree_mc->SetBranchAddress("neutrMultAK4CHS_j4",&neutrMult_j4);
tree_mc->SetBranchAddress("photonMultAK4CHS_j1",&photonMult_j1);
tree_mc->SetBranchAddress("photonMultAK4CHS_j2",&photonMult_j2);
tree_mc->SetBranchAddress("photonMultAK4CHS_j3",&photonMult_j3);
tree_mc->SetBranchAddress("photonMultAK4CHS_j4",&photonMult_j4);
tree_mc->SetBranchAddress("nVtx",&nVtx);


//Old format of reduced trees
/*tree_mc->SetBranchAddress("run",&run);
tree_mc->SetBranchAddress("lumi",&lumi);
tree_mc->SetBranchAddress("event",&event);
tree_mc->SetBranchAddress("FourjetMass",&FourjetMass);
tree_mc->SetBranchAddress("Maverage",&Maverage);
tree_mc->SetBranchAddress("Dijet_MassAK4_1",&Dijet_Mass_1);
tree_mc->SetBranchAddress("Dijet_MassAK4_2",&Dijet_Mass_2);
tree_mc->SetBranchAddress("Masymmetry",&Masymmetry);
tree_mc->SetBranchAddress("DeltaEtaJJAK4",&DeltaEtaJJ);
tree_mc->SetBranchAddress("DeltaPhiJJAK4",&DeltaPhiJJ);
tree_mc->SetBranchAddress("DeltaRAK4_First",&DeltaR_First);
tree_mc->SetBranchAddress("DeltaRAK4_Second",&DeltaR_Second);
tree_mc->SetBranchAddress("METoverHTAK4",&METoverHT);
tree_mc->SetBranchAddress("pTAK4_j1",&pTj1);
tree_mc->SetBranchAddress("pTAK4_j2",&pTj2);
tree_mc->SetBranchAddress("pTAK4_j3",&pTj3);
tree_mc->SetBranchAddress("pTAK4_j4",&pTj4);
tree_mc->SetBranchAddress("etaAK4_j1",&etaj1);
tree_mc->SetBranchAddress("etaAK4_j2",&etaj2);
tree_mc->SetBranchAddress("etaAK4_j3",&etaj3);
tree_mc->SetBranchAddress("etaAK4_j4",&etaj4);
tree_mc->SetBranchAddress("phiAK4_j1",&phij1);
tree_mc->SetBranchAddress("phiAK4_j2",&phij2);
tree_mc->SetBranchAddress("phiAK4_j3",&phij3);
tree_mc->SetBranchAddress("phiAK4_j4",&phij4);
tree_mc->SetBranchAddress("chargedElectromFrac_j1",&chargedElectromFrac_j1);
tree_mc->SetBranchAddress("chargedElectromFrac_j2",&chargedElectromFrac_j2);
tree_mc->SetBranchAddress("chargedElectromFrac_j3",&chargedElectromFrac_j3);
tree_mc->SetBranchAddress("chargedElectromFrac_j4",&chargedElectromFrac_j4);
tree_mc->SetBranchAddress("chargedHadEnFrac_j1",&chargedHadEnFrac_j1);
tree_mc->SetBranchAddress("chargedHadEnFrac_j2",&chargedHadEnFrac_j2);
tree_mc->SetBranchAddress("chargedHadEnFrac_j3",&chargedHadEnFrac_j3);
tree_mc->SetBranchAddress("chargedHadEnFrac_j4",&chargedHadEnFrac_j4);
tree_mc->SetBranchAddress("neutrElectromFrac_j1",&neutrElectromFrac_j1);
tree_mc->SetBranchAddress("neutrElectromFrac_j2",&neutrElectromFrac_j2);
tree_mc->SetBranchAddress("neutrElectromFrac_j3",&neutrElectromFrac_j3);
tree_mc->SetBranchAddress("neutrElectromFrac_j4",&neutrElectromFrac_j4);
tree_mc->SetBranchAddress("neutrHadEnFrac_j1",&neutrHadEnFrac_j1);
tree_mc->SetBranchAddress("neutrHadEnFrac_j2",&neutrHadEnFrac_j2);
tree_mc->SetBranchAddress("neutrHadEnFrac_j3",&neutrHadEnFrac_j3);
tree_mc->SetBranchAddress("neutrHadEnFrac_j4",&neutrHadEnFrac_j4);
tree_mc->SetBranchAddress("photonEnFrac_j1",&photonEnFrac_j1);
tree_mc->SetBranchAddress("photonEnFrac_j2",&photonEnFrac_j2);
tree_mc->SetBranchAddress("photonEnFrac_j3",&photonEnFrac_j3);
tree_mc->SetBranchAddress("photonEnFrac_j4",&photonEnFrac_j4);
tree_mc->SetBranchAddress("muEnFract_j1",&muEnFrac_j1);
tree_mc->SetBranchAddress("muEnFract_j2",&muEnFrac_j2);
tree_mc->SetBranchAddress("muEnFract_j3",&muEnFrac_j3);
tree_mc->SetBranchAddress("muEnFract_j4",&muEnFrac_j4);
tree_mc->SetBranchAddress("chargedMult_j1",&chargedMult_j1);
tree_mc->SetBranchAddress("chargedMult_j2",&chargedMult_j2);
tree_mc->SetBranchAddress("chargedMult_j3",&chargedMult_j3);
tree_mc->SetBranchAddress("chargedMult_j4",&chargedMult_j4);
tree_mc->SetBranchAddress("neutrMult_j1",&neutrMult_j1);
tree_mc->SetBranchAddress("neutrMult_j2",&neutrMult_j2);
tree_mc->SetBranchAddress("neutrMult_j3",&neutrMult_j3);
tree_mc->SetBranchAddress("neutrMult_j4",&neutrMult_j4);
tree_mc->SetBranchAddress("photonMult_j1",&photonMult_j1);
tree_mc->SetBranchAddress("photonMult_j2",&photonMult_j2);
tree_mc->SetBranchAddress("photonMult_j3",&photonMult_j3);
tree_mc->SetBranchAddress("photonMult_j4",&photonMult_j4);
tree_mc->SetBranchAddress("nVtx",&nVtx);
*/

Int_t nentries_mc = (Int_t)tree_mc->GetEntries();
std::cout << "MC: Number of entries =  " << nentries_mc << std::endl;

for (int i=0; i<nentries_mc; i++){    //event loop
//for (int i=0; i<100; i++){
	tree_mc->GetEntry(i);

	if (i%20000==0) cout << " done " << i << " from " << nentries_mc << endl;

	alpha=Maverage/FourjetMass; 

	//if(Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0 && alpha>alpha_low && alpha<alpha_high)
	if(FourjetMass>0)
	{
		h_FourjetMass->Fill(FourjetMass);
		h_FourjetMass1GeV->Fill(FourjetMass);
		h_Maverage->Fill(Maverage); 
		h_Dijet_Mass_1->Fill(Dijet_Mass_1);
		h_Dijet_Mass_2->Fill(Dijet_Mass_2);
		h_Masymmetry->Fill(Masymmetry);
		h_DeltaEtaJJ->Fill(DeltaEtaJJ);
		h_DeltaPhiJJ->Fill(DeltaPhiJJ);
		h_DeltaR_First->Fill(DeltaR_First);
		h_DeltaR_Second->Fill(DeltaR_Second);
		h_METoverHT->Fill(METoverHT);
		h_alpha->Fill(alpha);

		h_pTj1->Fill(pTj1);
		h_pTj2->Fill(pTj2);
		h_pTj3->Fill(pTj3);
		h_pTj4->Fill(pTj4);
		h_pT->Fill(pTj1);
		h_pT->Fill(pTj2);
		h_pT->Fill(pTj3);
		h_pT->Fill(pTj4);

		h_etaj1->Fill(etaj1);
		h_etaj2->Fill(etaj2);
		h_etaj3->Fill(etaj3);
		h_etaj4->Fill(etaj4);
		h_eta->Fill(etaj1);
		h_eta->Fill(etaj2);
		h_eta->Fill(etaj3);
		h_eta->Fill(etaj4);

		h_phij1->Fill(phij1);
		h_phij2->Fill(phij2);
		h_phij3->Fill(phij3);
		h_phij4->Fill(phij4);
		h_phi->Fill(phij1);
		h_phi->Fill(phij2);
		h_phi->Fill(phij3);
		h_phi->Fill(phij4);

		h_chargedElectromFrac_j1->Fill(chargedElectromFrac_j1);
		h_chargedElectromFrac_j2->Fill(chargedElectromFrac_j2);
		h_chargedElectromFrac_j3->Fill(chargedElectromFrac_j3);
		h_chargedElectromFrac_j4->Fill(chargedElectromFrac_j4);
		h_chargedElectromFrac->Fill(chargedElectromFrac_j1);
		h_chargedElectromFrac->Fill(chargedElectromFrac_j2);
		h_chargedElectromFrac->Fill(chargedElectromFrac_j3);
		h_chargedElectromFrac->Fill(chargedElectromFrac_j4);

		h_chargedHadEnFrac_j1->Fill(chargedHadEnFrac_j1);
		h_chargedHadEnFrac_j2->Fill(chargedHadEnFrac_j2);
		h_chargedHadEnFrac_j3->Fill(chargedHadEnFrac_j3);
		h_chargedHadEnFrac_j4->Fill(chargedHadEnFrac_j4);
		h_chargedHadEnFrac->Fill(chargedHadEnFrac_j1);
		h_chargedHadEnFrac->Fill(chargedHadEnFrac_j2);
		h_chargedHadEnFrac->Fill(chargedHadEnFrac_j3);
		h_chargedHadEnFrac->Fill(chargedHadEnFrac_j4);

		h_neutrElectromFrac_j1->Fill(neutrElectromFrac_j1);
		h_neutrElectromFrac_j2->Fill(neutrElectromFrac_j2);
		h_neutrElectromFrac_j3->Fill(neutrElectromFrac_j3);
		h_neutrElectromFrac_j4->Fill(neutrElectromFrac_j4);
		h_neutrElectromFrac->Fill(neutrElectromFrac_j1);
		h_neutrElectromFrac->Fill(neutrElectromFrac_j2);
		h_neutrElectromFrac->Fill(neutrElectromFrac_j3);
		h_neutrElectromFrac->Fill(neutrElectromFrac_j4);

		h_neutrHadEnFrac_j1->Fill(neutrHadEnFrac_j1);
		h_neutrHadEnFrac_j2->Fill(neutrHadEnFrac_j2);
		h_neutrHadEnFrac_j3->Fill(neutrHadEnFrac_j3);
		h_neutrHadEnFrac_j4->Fill(neutrHadEnFrac_j4);
		h_neutrHadEnFrac->Fill(neutrHadEnFrac_j1);
		h_neutrHadEnFrac->Fill(neutrHadEnFrac_j2);
		h_neutrHadEnFrac->Fill(neutrHadEnFrac_j3);
		h_neutrHadEnFrac->Fill(neutrHadEnFrac_j4);

		h_photonEnFrac_j1->Fill(photonEnFrac_j1);
		h_photonEnFrac_j2->Fill(photonEnFrac_j2);
		h_photonEnFrac_j3->Fill(photonEnFrac_j3);
		h_photonEnFrac_j4->Fill(photonEnFrac_j4);
		h_photonEnFrac->Fill(photonEnFrac_j1);
		h_photonEnFrac->Fill(photonEnFrac_j2);
		h_photonEnFrac->Fill(photonEnFrac_j3);
		h_photonEnFrac->Fill(photonEnFrac_j4);

		h_muEnFrac_j1->Fill(muEnFrac_j1);
		h_muEnFrac_j2->Fill(muEnFrac_j2);
		h_muEnFrac_j3->Fill(muEnFrac_j3);
		h_muEnFrac_j4->Fill(muEnFrac_j4);
		h_muEnFrac->Fill(muEnFrac_j1);
		h_muEnFrac->Fill(muEnFrac_j2);
		h_muEnFrac->Fill(muEnFrac_j3);
		h_muEnFrac->Fill(muEnFrac_j4);

		h_chargedMult_j1->Fill(chargedMult_j1);
		h_chargedMult_j2->Fill(chargedMult_j2);
		h_chargedMult_j3->Fill(chargedMult_j3);
		h_chargedMult_j4->Fill(chargedMult_j4);
		h_chargedMult->Fill(chargedMult_j1);
		h_chargedMult->Fill(chargedMult_j2);
		h_chargedMult->Fill(chargedMult_j3);
		h_chargedMult->Fill(chargedMult_j4);

		h_neutrMult_j1->Fill(neutrMult_j1);
		h_neutrMult_j2->Fill(neutrMult_j2);
		h_neutrMult_j3->Fill(neutrMult_j3);
		h_neutrMult_j4->Fill(neutrMult_j4);
		h_neutrMult->Fill(neutrMult_j1);
		h_neutrMult->Fill(neutrMult_j2);
		h_neutrMult->Fill(neutrMult_j3);
		h_neutrMult->Fill(neutrMult_j4);

		h_photonMult_j1->Fill(photonMult_j1);
		h_photonMult_j2->Fill(photonMult_j2);
		h_photonMult_j3->Fill(photonMult_j3);
		h_photonMult_j4->Fill(photonMult_j4);
		h_photonMult->Fill(photonMult_j1);
		h_photonMult->Fill(photonMult_j2);
		h_photonMult->Fill(photonMult_j3);
		h_photonMult->Fill(photonMult_j4);

		h_nVtx->Fill(nVtx);

		h_etaphi->Fill(etaj1, phij1);
		h_etaphi->Fill(etaj2, phij2);
		h_etaphi->Fill(etaj3, phij3);
		h_etaphi->Fill(etaj4, phij4);

	}


}// end of event loop


char outputfilename[1024];

sprintf(outputfilename,"signal_histos_NoSelectionCuts/ResonanceShapes_RunIISummer20UL18_Suu-Diquark_W-%s_S-%d_chi-%d_NoSelectionCuts.root",width_name,Suu,Chi);
//sprintf(outputfilename,"signal_histos_NoSelectionCuts/ResonanceShapes_RunIIFall17_Suu-Diquark_W-%s_S-%d_chi-%d_NoSelectionCuts.root",width_name,Suu,Chi);


TFile *fout = new TFile(outputfilename,"RECREATE");
fout->cd();

h_FourjetMass->Write();
h_FourjetMass1GeV->Write();
h_Maverage->Write();
h_Dijet_Mass_1->Write();
h_Dijet_Mass_2->Write();
h_alpha->Write();
h_pT->Write();
h_pTj1->Write();
h_pTj2->Write();
h_pTj3->Write();
h_pTj4->Write();
h_eta->Write();
h_etaj1->Write();
h_etaj2->Write();
h_etaj3->Write();
h_etaj4->Write();
h_phi->Write();
h_phij1->Write();
h_phij2->Write();
h_phij3->Write();
h_phij4->Write();
h_DeltaEtaJJ->Write();
h_DeltaPhiJJ->Write();
h_DeltaR_First->Write();
h_DeltaR_Second->Write();
h_Masymmetry->Write();
h_METoverHT->Write();
h_chargedElectromFrac->Write();
h_chargedElectromFrac_j1->Write();
h_chargedElectromFrac_j2->Write();
h_chargedElectromFrac_j3->Write();
h_chargedElectromFrac_j4->Write();
h_chargedHadEnFrac->Write();
h_chargedHadEnFrac_j1->Write();
h_chargedHadEnFrac_j2->Write();
h_chargedHadEnFrac_j3->Write();
h_chargedHadEnFrac_j4->Write();
h_neutrElectromFrac->Write();
h_neutrElectromFrac_j1->Write();
h_neutrElectromFrac_j2->Write();
h_neutrElectromFrac_j3->Write();
h_neutrElectromFrac_j4->Write();
h_neutrHadEnFrac->Write();
h_neutrHadEnFrac_j1->Write();
h_neutrHadEnFrac_j2->Write();
h_neutrHadEnFrac_j3->Write();
h_neutrHadEnFrac_j4->Write();
h_photonEnFrac->Write();
h_photonEnFrac_j1->Write();
h_photonEnFrac_j2->Write();
h_photonEnFrac_j3->Write();
h_photonEnFrac_j4->Write();
h_muEnFrac->Write();
h_muEnFrac_j1->Write();
h_muEnFrac_j2->Write();
h_muEnFrac_j3->Write();
h_muEnFrac_j4->Write();
h_chargedMult->Write();
h_chargedMult_j1->Write();
h_chargedMult_j2->Write();
h_chargedMult_j3->Write();
h_chargedMult_j4->Write();
h_neutrMult->Write();
h_neutrMult_j1->Write();
h_neutrMult_j2->Write();
h_neutrMult_j3->Write();
h_neutrMult_j4->Write();
h_photonMult->Write();
h_photonMult_j1->Write();
h_photonMult_j2->Write();
h_photonMult_j3->Write();
h_photonMult_j4->Write();
h_nVtx->Write();
h_etaphi->Write();

fout->Close();


}
