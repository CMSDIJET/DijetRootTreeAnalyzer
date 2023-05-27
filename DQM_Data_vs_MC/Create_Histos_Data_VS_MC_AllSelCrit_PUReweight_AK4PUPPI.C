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

void Create_Histos_Data_VS_MC_AllSelCrit_PUReweight_AK4PUPPI(){

TFile *fpu = new TFile("AllRuns_34fb-1/PUReweight_AllRuns_PUPPI.root","READ");
TH1D *h_nVtx_ratio = (TH1D*)fpu->Get("h_nVtx_ratio");

TH1D *h_FourjetMass_data;
TH1D *h_FourjetMass_mc;

TH1D *h_Maverage_data;
TH1D *h_Maverage_mc;

TH1D *h_Dijet_Mass_1_data;
TH1D *h_Dijet_Mass_1_mc;

TH1D *h_Dijet_Mass_2_data;
TH1D *h_Dijet_Mass_2_mc;

TH1D *h_alpha_data;
TH1D *h_alpha_mc;

TH1D *h_pT_data, *h_pTj1_data, *h_pTj2_data, *h_pTj3_data, *h_pTj4_data;
TH1D *h_pT_mc, *h_pTj1_mc, *h_pTj2_mc, *h_pTj3_mc, *h_pTj4_mc;

TH1D *h_eta_data, *h_etaj1_data, *h_etaj2_data, *h_etaj3_data, *h_etaj4_data;
TH1D *h_eta_mc, *h_etaj1_mc, *h_etaj2_mc, *h_etaj3_mc, *h_etaj4_mc;

TH1D *h_phi_data, *h_phij1_data, *h_phij2_data, *h_phij3_data, *h_phij4_data;
TH1D *h_phi_mc, *h_phij1_mc, *h_phij2_mc, *h_phij3_mc, *h_phij4_mc;

TH1D *h_DeltaEtaJJ_data, *h_DeltaPhiJJ_data, *h_DeltaR_First_data, *h_DeltaR_Second_data, *h_METoverHT_data, *h_Masymmetry_data;
TH1D *h_DeltaEtaJJ_mc, *h_DeltaPhiJJ_mc, *h_DeltaR_First_mc, *h_DeltaR_Second_mc, *h_METoverHT_mc, *h_Masymmetry_mc; 

TH1D *h_chargedElectromFrac_data, *h_chargedElectromFrac_j1_data, *h_chargedElectromFrac_j2_data, *h_chargedElectromFrac_j3_data, *h_chargedElectromFrac_j4_data, *h_chargedHadEnFrac_data, *h_chargedHadEnFrac_j1_data, *h_chargedHadEnFrac_j2_data, *h_chargedHadEnFrac_j3_data, *h_chargedHadEnFrac_j4_data, *h_neutrElectromFrac_data, *h_neutrElectromFrac_j1_data, *h_neutrElectromFrac_j2_data, *h_neutrElectromFrac_j3_data, *h_neutrElectromFrac_j4_data, *h_neutrHadEnFrac_data, *h_neutrHadEnFrac_j1_data, *h_neutrHadEnFrac_j2_data, *h_neutrHadEnFrac_j3_data, *h_neutrHadEnFrac_j4_data, *h_photonEnFrac_data, *h_photonEnFrac_j1_data, *h_photonEnFrac_j2_data, *h_photonEnFrac_j3_data, *h_photonEnFrac_j4_data, *h_muEnFrac_data, *h_muEnFrac_j1_data, *h_muEnFrac_j2_data, *h_muEnFrac_j3_data, *h_muEnFrac_j4_data;
TH1D *h_chargedElectromFrac_mc, *h_chargedElectromFrac_j1_mc, *h_chargedElectromFrac_j2_mc, *h_chargedElectromFrac_j3_mc, *h_chargedElectromFrac_j4_mc, *h_chargedHadEnFrac_mc, *h_chargedHadEnFrac_j1_mc, *h_chargedHadEnFrac_j2_mc, *h_chargedHadEnFrac_j3_mc, *h_chargedHadEnFrac_j4_mc, *h_neutrElectromFrac_mc, *h_neutrElectromFrac_j1_mc, *h_neutrElectromFrac_j2_mc, *h_neutrElectromFrac_j3_mc, *h_neutrElectromFrac_j4_mc, *h_neutrHadEnFrac_mc, *h_neutrHadEnFrac_j1_mc, *h_neutrHadEnFrac_j2_mc, *h_neutrHadEnFrac_j3_mc, *h_neutrHadEnFrac_j4_mc, *h_photonEnFrac_mc, *h_photonEnFrac_j1_mc, *h_photonEnFrac_j2_mc, *h_photonEnFrac_j3_mc, *h_photonEnFrac_j4_mc, *h_muEnFrac_mc, *h_muEnFrac_j1_mc, *h_muEnFrac_j2_mc, *h_muEnFrac_j3_mc, *h_muEnFrac_j4_mc;

TH1D *h_chargedMult_data, *h_chargedMult_j1_data, *h_chargedMult_j2_data, *h_chargedMult_j3_data, *h_chargedMult_j4_data, *h_neutrMult_data, *h_neutrMult_j1_data, *h_neutrMult_j2_data, *h_neutrMult_j3_data, *h_neutrMult_j4_data, *h_photonMult_data, *h_photonMult_j1_data, *h_photonMult_j2_data, *h_photonMult_j3_data, *h_photonMult_j4_data;
TH1D *h_chargedMult_mc, *h_chargedMult_j1_mc, *h_chargedMult_j2_mc, *h_chargedMult_j3_mc, *h_chargedMult_j4_mc, *h_neutrMult_mc, *h_neutrMult_j1_mc, *h_neutrMult_j2_mc, *h_neutrMult_j3_mc, *h_neutrMult_j4_mc, *h_photonMult_mc, *h_photonMult_j1_mc, *h_photonMult_j2_mc, *h_photonMult_j3_mc, *h_photonMult_j4_mc;

TH1D *h_nVtx_data;
TH1D *h_nVtx_mc;

TH2D *h_etaphi_data, *h_etaphi_mc;

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

h_FourjetMass_data = new TH1D("h_FourjetMass_data","",103,massBoundaries);
h_FourjetMass_mc = new TH1D("h_FourjetMass_mc","",103,massBoundaries);

h_Maverage_data = new TH1D("h_Maverage_data","",103,massBoundaries);
h_Maverage_mc = new TH1D("h_Maverage_mc","",103,massBoundaries);

h_Dijet_Mass_1_data = new TH1D("h_Dijet_Mass_1_data","",103,massBoundaries);
h_Dijet_Mass_1_mc = new TH1D("h_Dijet_Mass_1_mc","",103,massBoundaries);

h_Dijet_Mass_2_data = new TH1D("h_Dijet_Mass_2_data","",103,massBoundaries);
h_Dijet_Mass_2_mc = new TH1D("h_Dijet_Mass_2_mc","",103,massBoundaries);

h_alpha_data = new TH1D("h_alpha_data","",50,0,0.5);
h_alpha_mc = new TH1D("h_alpha_mc","",50,0,0.5);

h_pT_data = new TH1D("h_pT_data","",85,0,6800);
h_pT_mc = new TH1D("h_pT_mc","",85,0,6800);

h_pTj1_data = new TH1D("h_pTj1_data","",85,0,6800);
h_pTj2_data = new TH1D("h_pTj2_data","",85,0,6800);
h_pTj3_data = new TH1D("h_pTj3_data","",85,0,6800);
h_pTj4_data = new TH1D("h_pTj4_data","",85,0,6800);
h_pTj1_mc = new TH1D("h_pTj1_mc","",85,0,6800);
h_pTj2_mc = new TH1D("h_pTj2_mc","",85,0,6800);
h_pTj3_mc = new TH1D("h_pTj3_mc","",85,0,6800);
h_pTj4_mc = new TH1D("h_pTj4_mc","",85,0,6800);

h_eta_data = new TH1D("h_eta_data","",30,-3,3);
h_eta_mc = new TH1D("h_eta_mc","",30,-3,3);

h_etaj1_data = new TH1D("h_etaj1_data","",30,-3,3);
h_etaj2_data = new TH1D("h_etaj2_data","",30,-3,3);
h_etaj3_data = new TH1D("h_etaj3_data","",30,-3,3);
h_etaj4_data = new TH1D("h_etaj4_data","",30,-3,3);
h_etaj1_mc = new TH1D("h_etaj1_mc","",30,-3,3);
h_etaj2_mc = new TH1D("h_etaj2_mc","",30,-3,3);
h_etaj3_mc = new TH1D("h_etaj3_mc","",30,-3,3);
h_etaj4_mc = new TH1D("h_etaj4_mc","",30,-3,3);

h_phi_data = new TH1D("h_phi_data","",32,-3.2,3.2);
h_phi_mc = new TH1D("h_phi_mc","",32,-3.2,3.2);

h_phij1_data = new TH1D("h_phij1_data","",32,-3.2,3.2);
h_phij2_data = new TH1D("h_phij2_data","",32,-3.2,3.2);
h_phij3_data = new TH1D("h_phij3_data","",32,-3.2,3.2);
h_phij4_data = new TH1D("h_phij4_data","",32,-3.2,3.2);
h_phij1_mc = new TH1D("h_phij1_mc","",32,-3.2,3.2);
h_phij2_mc = new TH1D("h_phij2_mc","",32,-3.2,3.2);
h_phij3_mc = new TH1D("h_phij3_mc","",32,-3.2,3.2);
h_phij4_mc = new TH1D("h_phij4_mc","",32,-3.2,3.2);

h_DeltaEtaJJ_data = new TH1D("h_DeltaEtaJJ_data","",40,0,2);
h_DeltaEtaJJ_mc = new TH1D("h_DeltaEtaJJ_mc","",40,0,2);

h_DeltaPhiJJ_data = new TH1D("h_DeltaPhiJJ_data","",64,0,3.1416);
h_DeltaPhiJJ_mc = new TH1D("h_DeltaPhiJJ_mc","",64,0,3.1416);

h_DeltaR_First_data = new TH1D("h_DeltaR_First_data","",40,0,4);
h_DeltaR_First_mc = new TH1D("h_DeltaR_First_mc","",40,0,4);
h_DeltaR_Second_data = new TH1D("h_DeltaR_Second_data","",40,0,4);
h_DeltaR_Second_mc = new TH1D("h_DeltaR_Second_mc","",40,0,4);

h_Masymmetry_data = new TH1D("h_Masymmetry_data","",40,0,0.2);
h_Masymmetry_mc = new TH1D("h_Masymmetry_mc","",40,0,0.2);

h_METoverHT_data = new TH1D("h_METoverHT_data","",60,0,1.2);
h_METoverHT_mc = new TH1D("h_METoverHT_mc","",60,0,1.2);

h_chargedElectromFrac_data = new TH1D("h_chargedElectromFrac_data","",60,0,1.2);
h_chargedElectromFrac_mc = new TH1D("h_chargedElectromFrac_mc","",60,0,1.2);
h_chargedElectromFrac_j1_data = new TH1D("h_chargedElectromFrac_j1_data","",60,0,1.2);
h_chargedElectromFrac_j2_data = new TH1D("h_chargedElectromFrac_j2_data","",60,0,1.2);
h_chargedElectromFrac_j3_data = new TH1D("h_chargedElectromFrac_j3_data","",60,0,1.2);
h_chargedElectromFrac_j4_data = new TH1D("h_chargedElectromFrac_j4_data","",60,0,1.2);
h_chargedElectromFrac_j1_mc = new TH1D("h_chargedElectromFrac_j1_mc","",60,0,1.2);
h_chargedElectromFrac_j2_mc = new TH1D("h_chargedElectromFrac_j2_mc","",60,0,1.2);
h_chargedElectromFrac_j3_mc = new TH1D("h_chargedElectromFrac_j3_mc","",60,0,1.2);
h_chargedElectromFrac_j4_mc = new TH1D("h_chargedElectromFrac_j4_mc","",60,0,1.2);

h_chargedHadEnFrac_data = new TH1D("h_chargedHadEnFrac_data","",60,0,1.2);
h_chargedHadEnFrac_mc = new TH1D("h_chargedHadEnFrac_mc","",60,0,1.2);
h_chargedHadEnFrac_j1_data = new TH1D("h_chargedHadEnFrac_j1_data","",60,0,1.2);
h_chargedHadEnFrac_j2_data = new TH1D("h_chargedHadEnFrac_j2_data","",60,0,1.2);
h_chargedHadEnFrac_j3_data = new TH1D("h_chargedHadEnFrac_j3_data","",60,0,1.2);
h_chargedHadEnFrac_j4_data = new TH1D("h_chargedHadEnFrac_j4_data","",60,0,1.2);
h_chargedHadEnFrac_j1_mc = new TH1D("h_chargedHadEnFrac_j1_mc","",60,0,1.2);
h_chargedHadEnFrac_j2_mc = new TH1D("h_chargedHadEnFrac_j2_mc","",60,0,1.2);
h_chargedHadEnFrac_j3_mc = new TH1D("h_chargedHadEnFrac_j3_mc","",60,0,1.2);
h_chargedHadEnFrac_j4_mc = new TH1D("h_chargedHadEnFrac_j4_mc","",60,0,1.2);

h_neutrElectromFrac_data = new TH1D("h_neutrElectromFrac_data","",60,0,1.2);
h_neutrElectromFrac_mc = new TH1D("h_neutrElectromFrac_mc","",60,0,1.2);
h_neutrElectromFrac_j1_data = new TH1D("h_neutrElectromFrac_j1_data","",60,0,1.2);
h_neutrElectromFrac_j2_data = new TH1D("h_neutrElectromFrac_j2_data","",60,0,1.2);
h_neutrElectromFrac_j3_data = new TH1D("h_neutrElectromFrac_j3_data","",60,0,1.2);
h_neutrElectromFrac_j4_data = new TH1D("h_neutrElectromFrac_j4_data","",60,0,1.2);
h_neutrElectromFrac_j1_mc = new TH1D("h_neutrElectromFrac_j1_mc","",60,0,1.2);
h_neutrElectromFrac_j2_mc = new TH1D("h_neutrElectromFrac_j2_mc","",60,0,1.2);
h_neutrElectromFrac_j3_mc = new TH1D("h_neutrElectromFrac_j3_mc","",60,0,1.2);
h_neutrElectromFrac_j4_mc = new TH1D("h_neutrElectromFrac_j4_mc","",60,0,1.2);

h_neutrHadEnFrac_data = new TH1D("h_neutrHadEnFrac_data","",60,0,1.2);
h_neutrHadEnFrac_mc = new TH1D("h_neutrHadEnFrac_mc","",60,0,1.2);
h_neutrHadEnFrac_j1_data = new TH1D("h_neutrHadEnFrac_j1_data","",60,0,1.2);
h_neutrHadEnFrac_j2_data = new TH1D("h_neutrHadEnFrac_j2_data","",60,0,1.2);
h_neutrHadEnFrac_j3_data = new TH1D("h_neutrHadEnFrac_j3_data","",60,0,1.2);
h_neutrHadEnFrac_j4_data = new TH1D("h_neutrHadEnFrac_j4_data","",60,0,1.2);
h_neutrHadEnFrac_j1_mc = new TH1D("h_neutrHadEnFrac_j1_mc","",60,0,1.2);
h_neutrHadEnFrac_j2_mc = new TH1D("h_neutrHadEnFrac_j2_mc","",60,0,1.2);
h_neutrHadEnFrac_j3_mc = new TH1D("h_neutrHadEnFrac_j3_mc","",60,0,1.2);
h_neutrHadEnFrac_j4_mc = new TH1D("h_neutrHadEnFrac_j4_mc","",60,0,1.2);

h_photonEnFrac_data = new TH1D("h_photonEnFrac_data","",60,0,1.2);
h_photonEnFrac_mc = new TH1D("h_photonEnFrac_mc","",60,0,1.2);
h_photonEnFrac_j1_data = new TH1D("h_photonEnFrac_j1_data","",60,0,1.2);
h_photonEnFrac_j2_data = new TH1D("h_photonEnFrac_j2_data","",60,0,1.2);
h_photonEnFrac_j3_data = new TH1D("h_photonEnFrac_j3_data","",60,0,1.2);
h_photonEnFrac_j4_data = new TH1D("h_photonEnFrac_j4_data","",60,0,1.2);
h_photonEnFrac_j1_mc = new TH1D("h_photonEnFrac_j1_mc","",60,0,1.2);
h_photonEnFrac_j2_mc = new TH1D("h_photonEnFrac_j2_mc","",60,0,1.2);
h_photonEnFrac_j3_mc = new TH1D("h_photonEnFrac_j3_mc","",60,0,1.2);
h_photonEnFrac_j4_mc = new TH1D("h_photonEnFrac_j4_mc","",60,0,1.2);

h_muEnFrac_data = new TH1D("h_muEnFrac_data","",60,0,1.2);
h_muEnFrac_mc = new TH1D("h_muEnFrac_mc","",60,0,1.2);
h_muEnFrac_j1_data = new TH1D("h_muEnFrac_j1_data","",60,0,1.2);
h_muEnFrac_j2_data = new TH1D("h_muEnFrac_j2_data","",60,0,1.2);
h_muEnFrac_j3_data = new TH1D("h_muEnFrac_j3_data","",60,0,1.2);
h_muEnFrac_j4_data = new TH1D("h_muEnFrac_j4_data","",60,0,1.2);
h_muEnFrac_j1_mc = new TH1D("h_muEnFrac_j1_mc","",60,0,1.2);
h_muEnFrac_j2_mc = new TH1D("h_muEnFrac_j2_mc","",60,0,1.2);
h_muEnFrac_j3_mc = new TH1D("h_muEnFrac_j3_mc","",60,0,1.2);
h_muEnFrac_j4_mc = new TH1D("h_muEnFrac_j4_mc","",60,0,1.2);

h_chargedMult_data = new TH1D("h_chargedMult_data","",50,0,100);
h_chargedMult_mc = new TH1D("h_chargedMult_mc","",50,0,100);
h_chargedMult_j1_data = new TH1D("h_chargedMult_j1_data","",50,0,100);
h_chargedMult_j2_data = new TH1D("h_chargedMult_j2_data","",50,0,100);
h_chargedMult_j3_data = new TH1D("h_chargedMult_j3_data","",50,0,100);
h_chargedMult_j4_data = new TH1D("h_chargedMult_j4_data","",50,0,100);
h_chargedMult_j1_mc = new TH1D("h_chargedMult_j1_mc","",50,0,100);
h_chargedMult_j2_mc = new TH1D("h_chargedMult_j2_mc","",50,0,100);
h_chargedMult_j3_mc = new TH1D("h_chargedMult_j3_mc","",50,0,100);
h_chargedMult_j4_mc = new TH1D("h_chargedMult_j4_mc","",50,0,100);

h_neutrMult_data = new TH1D("h_neutrMult_data","",50,0,100);
h_neutrMult_mc = new TH1D("h_neutrMult_mc","",50,0,100);
h_neutrMult_j1_data = new TH1D("h_neutrMult_j1_data","",50,0,100);
h_neutrMult_j2_data = new TH1D("h_neutrMult_j2_data","",50,0,100);
h_neutrMult_j3_data = new TH1D("h_neutrMult_j3_data","",50,0,100);
h_neutrMult_j4_data = new TH1D("h_neutrMult_j4_data","",50,0,100);
h_neutrMult_j1_mc = new TH1D("h_neutrMult_j1_mc","",50,0,100);
h_neutrMult_j2_mc = new TH1D("h_neutrMult_j2_mc","",50,0,100);
h_neutrMult_j3_mc = new TH1D("h_neutrMult_j3_mc","",50,0,100);
h_neutrMult_j4_mc = new TH1D("h_neutrMult_j4_mc","",50,0,100);

h_photonMult_data = new TH1D("h_photonMult_data","",50,0,100);
h_photonMult_mc = new TH1D("h_photonMult_mc","",50,0,100);
h_photonMult_j1_data = new TH1D("h_photonMult_j1_data","",50,0,100);
h_photonMult_j2_data = new TH1D("h_photonMult_j2_data","",50,0,100);
h_photonMult_j3_data = new TH1D("h_photonMult_j3_data","",50,0,100);
h_photonMult_j4_data = new TH1D("h_photonMult_j4_data","",50,0,100);
h_photonMult_j1_mc = new TH1D("h_photonMult_j1_mc","",50,0,100);
h_photonMult_j2_mc = new TH1D("h_photonMult_j2_mc","",50,0,100);
h_photonMult_j3_mc = new TH1D("h_photonMult_j3_mc","",50,0,100);
h_photonMult_j4_mc = new TH1D("h_photonMult_j4_mc","",50,0,100);

h_nVtx_data = new TH1D("h_nVtx_data","",100,0,100);
h_nVtx_mc = new TH1D("h_nVtx_mc","",100,0,100);

h_etaphi_data = new TH2D("h_etaphi_data","",16,-3.2,3.2,15,-3,3);
h_etaphi_mc = new TH2D("h_etaphi_mc","",16,-3.2,3.2,15,-3,3);

h_FourjetMass_mc->Sumw2();
h_Maverage_mc->Sumw2();
h_Dijet_Mass_1_mc->Sumw2();
h_Dijet_Mass_2_mc->Sumw2();
h_alpha_mc->Sumw2();
h_pT_mc->Sumw2();
h_pTj1_mc->Sumw2();
h_pTj2_mc->Sumw2();
h_pTj3_mc->Sumw2();
h_pTj4_mc->Sumw2();
h_eta_mc->Sumw2();
h_etaj1_mc->Sumw2();
h_etaj2_mc->Sumw2();
h_etaj3_mc->Sumw2();
h_etaj4_mc->Sumw2();
h_phi_mc->Sumw2();
h_phij1_mc->Sumw2();
h_phij2_mc->Sumw2();
h_phij3_mc->Sumw2();
h_phij4_mc->Sumw2();
h_DeltaEtaJJ_mc->Sumw2();
h_DeltaPhiJJ_mc->Sumw2();
h_DeltaR_First_mc->Sumw2();
h_DeltaR_Second_mc->Sumw2();
h_Masymmetry_mc->Sumw2();
h_METoverHT_mc->Sumw2();
h_chargedElectromFrac_mc->Sumw2();
h_chargedElectromFrac_j1_mc->Sumw2();
h_chargedElectromFrac_j2_mc->Sumw2();
h_chargedElectromFrac_j3_mc->Sumw2();
h_chargedElectromFrac_j4_mc->Sumw2();
h_chargedHadEnFrac_mc->Sumw2();
h_chargedHadEnFrac_j1_mc->Sumw2();
h_chargedHadEnFrac_j2_mc->Sumw2();
h_chargedHadEnFrac_j3_mc->Sumw2();
h_chargedHadEnFrac_j4_mc->Sumw2();
h_neutrElectromFrac_mc->Sumw2();
h_neutrElectromFrac_j1_mc->Sumw2();
h_neutrElectromFrac_j2_mc->Sumw2();
h_neutrElectromFrac_j3_mc->Sumw2();
h_neutrElectromFrac_j4_mc->Sumw2();
h_neutrHadEnFrac_mc->Sumw2();
h_neutrHadEnFrac_j1_mc->Sumw2();
h_neutrHadEnFrac_j2_mc->Sumw2();
h_neutrHadEnFrac_j3_mc->Sumw2();
h_neutrHadEnFrac_j4_mc->Sumw2();
h_photonEnFrac_mc->Sumw2();
h_photonEnFrac_j1_mc->Sumw2();
h_photonEnFrac_j2_mc->Sumw2();
h_photonEnFrac_j3_mc->Sumw2();
h_photonEnFrac_j4_mc->Sumw2();
h_muEnFrac_mc->Sumw2();
h_muEnFrac_j1_mc->Sumw2();
h_muEnFrac_j2_mc->Sumw2();
h_muEnFrac_j3_mc->Sumw2();
h_muEnFrac_j4_mc->Sumw2();
h_chargedMult_mc->Sumw2();
h_chargedMult_j1_mc->Sumw2();
h_chargedMult_j2_mc->Sumw2();
h_chargedMult_j3_mc->Sumw2();
h_chargedMult_j4_mc->Sumw2();
h_neutrMult_mc->Sumw2();
h_neutrMult_j1_mc->Sumw2();
h_neutrMult_j2_mc->Sumw2();
h_neutrMult_j3_mc->Sumw2();
h_neutrMult_j4_mc->Sumw2();
h_photonMult_mc->Sumw2();
h_photonMult_j1_mc->Sumw2();
h_photonMult_j2_mc->Sumw2();
h_photonMult_j3_mc->Sumw2();
h_photonMult_j4_mc->Sumw2();
h_nVtx_mc->Sumw2();
h_etaphi_mc->Sumw2();

double run, lumi, event, weight, nVtx, PassJSON, w;
double FourjetMass, Maverage, Dijet_Mass_1, Dijet_Mass_2, Masymmetry, DeltaEtaJJ, DeltaPhiJJ, DeltaR_First, DeltaR_Second, alpha, METoverHT;
double pTj1, pTj2, pTj3, pTj4, etaj1, etaj2, etaj3, etaj4, phij1, phij2, phij3, phij4;
double chargedElectromFrac_j1, chargedElectromFrac_j2, chargedElectromFrac_j3, chargedElectromFrac_j4, chargedHadEnFrac_j1, chargedHadEnFrac_j2, chargedHadEnFrac_j3, chargedHadEnFrac_j4, neutrElectromFrac_j1, neutrElectromFrac_j2, neutrElectromFrac_j3, neutrElectromFrac_j4, neutrHadEnFrac_j1, neutrHadEnFrac_j2, neutrHadEnFrac_j3, neutrHadEnFrac_j4, photonEnFrac_j1, photonEnFrac_j2, photonEnFrac_j3, photonEnFrac_j4, muEnFrac_j1, muEnFrac_j2, muEnFrac_j3, muEnFrac_j4, chargedMult_j1, chargedMult_j2, chargedMult_j3, chargedMult_j4, neutrMult_j1, neutrMult_j2, neutrMult_j3, neutrMult_j4, photonMult_j1, photonMult_j2, photonMult_j3, photonMult_j4;	


TChain *tree_data = new TChain("rootTupleTree/tree");

tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetHT__Run2022B-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetHT__Run2022C-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022C-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022D-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022D-PromptReco-v2__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022E-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022F-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022G-PromptReco-v1__AK4PUPPI_reduced_skim.root");

tree_data->SetBranchAddress("run",&run);
tree_data->SetBranchAddress("lumi",&lumi);
tree_data->SetBranchAddress("event",&event);
tree_data->SetBranchAddress("FourjetMassAK4PUPPI",&FourjetMass);
tree_data->SetBranchAddress("MaverageAK4PUPPI",&Maverage);
tree_data->SetBranchAddress("Dijet_MassAK4PUPPI_1",&Dijet_Mass_1);
tree_data->SetBranchAddress("Dijet_MassAK4PUPPI_2",&Dijet_Mass_2);
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
tree_data->SetBranchAddress("chargedElectromFracAK4PUPPI_j1",&chargedElectromFrac_j1);
tree_data->SetBranchAddress("chargedElectromFracAK4PUPPI_j2",&chargedElectromFrac_j2);
tree_data->SetBranchAddress("chargedElectromFracAK4PUPPI_j3",&chargedElectromFrac_j3);
tree_data->SetBranchAddress("chargedElectromFracAK4PUPPI_j4",&chargedElectromFrac_j4);
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
tree_data->SetBranchAddress("photonEnFracAK4PUPPI_j1",&photonEnFrac_j1);
tree_data->SetBranchAddress("photonEnFracAK4PUPPI_j2",&photonEnFrac_j2);
tree_data->SetBranchAddress("photonEnFracAK4PUPPI_j3",&photonEnFrac_j3);
tree_data->SetBranchAddress("photonEnFracAK4PUPPI_j4",&photonEnFrac_j4);
tree_data->SetBranchAddress("muEnFractAK4PUPPI_j1",&muEnFrac_j1);
tree_data->SetBranchAddress("muEnFractAK4PUPPI_j2",&muEnFrac_j2);
tree_data->SetBranchAddress("muEnFractAK4PUPPI_j3",&muEnFrac_j3);
tree_data->SetBranchAddress("muEnFractAK4PUPPI_j4",&muEnFrac_j4);
tree_data->SetBranchAddress("chargedMultAK4PUPPI_j1",&chargedMult_j1);
tree_data->SetBranchAddress("chargedMultAK4PUPPI_j2",&chargedMult_j2);
tree_data->SetBranchAddress("chargedMultAK4PUPPI_j3",&chargedMult_j3);
tree_data->SetBranchAddress("chargedMultAK4PUPPI_j4",&chargedMult_j4);
tree_data->SetBranchAddress("neutrMultAK4PUPPI_j1",&neutrMult_j1);
tree_data->SetBranchAddress("neutrMultAK4PUPPI_j2",&neutrMult_j2);
tree_data->SetBranchAddress("neutrMultAK4PUPPI_j3",&neutrMult_j3);
tree_data->SetBranchAddress("neutrMultAK4PUPPI_j4",&neutrMult_j4);
tree_data->SetBranchAddress("photonMultAK4PUPPI_j1",&photonMult_j1);
tree_data->SetBranchAddress("photonMultAK4PUPPI_j2",&photonMult_j2);
tree_data->SetBranchAddress("photonMultAK4PUPPI_j3",&photonMult_j3);
tree_data->SetBranchAddress("photonMultAK4PUPPI_j4",&photonMult_j4);
tree_data->SetBranchAddress("nVtx",&nVtx);
tree_data->SetBranchAddress("PassJSON",&PassJSON);


Int_t nentries_data = (Int_t)tree_data->GetEntries();
std::cout << "Data: Number of entries =  " << nentries_data << std::endl;

for (int i=0; i<nentries_data; i++){    //event loop
//for (int i=0; i<100000; i++){
	tree_data->GetEntry(i);

	if (i%1000000==0) cout << " done " << i << " from " << nentries_data << endl;

	if(PassJSON==0) continue;

	alpha=Maverage/FourjetMass; 

	if(FourjetMass>1607 && Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0 && alpha>0.1)
	{
		h_FourjetMass_data->Fill(FourjetMass);
		h_Maverage_data->Fill(Maverage); 
		h_Dijet_Mass_1_data->Fill(Dijet_Mass_1);
		h_Dijet_Mass_2_data->Fill(Dijet_Mass_2);
		h_Masymmetry_data->Fill(Masymmetry);
		h_DeltaEtaJJ_data->Fill(DeltaEtaJJ);
		h_DeltaPhiJJ_data->Fill(DeltaPhiJJ);
		h_DeltaR_First_data->Fill(DeltaR_First);
		h_DeltaR_Second_data->Fill(DeltaR_Second);
		h_METoverHT_data->Fill(METoverHT);
		h_alpha_data->Fill(alpha);

		h_pTj1_data->Fill(pTj1);
		h_pTj2_data->Fill(pTj2);
		h_pTj3_data->Fill(pTj3);
		h_pTj4_data->Fill(pTj4);
		h_pT_data->Fill(pTj1);
		h_pT_data->Fill(pTj2);
		h_pT_data->Fill(pTj3);
		h_pT_data->Fill(pTj4);

		h_etaj1_data->Fill(etaj1);
		h_etaj2_data->Fill(etaj2);
		h_etaj3_data->Fill(etaj3);
		h_etaj4_data->Fill(etaj4);
		h_eta_data->Fill(etaj1);
		h_eta_data->Fill(etaj2);
		h_eta_data->Fill(etaj3);
		h_eta_data->Fill(etaj4);

		h_phij1_data->Fill(phij1);
		h_phij2_data->Fill(phij2);
		h_phij3_data->Fill(phij3);
		h_phij4_data->Fill(phij4);
		h_phi_data->Fill(phij1);
		h_phi_data->Fill(phij2);
		h_phi_data->Fill(phij3);
		h_phi_data->Fill(phij4);

		h_chargedElectromFrac_j1_data->Fill(chargedElectromFrac_j1);
		h_chargedElectromFrac_j2_data->Fill(chargedElectromFrac_j2);
		h_chargedElectromFrac_j3_data->Fill(chargedElectromFrac_j3);
		h_chargedElectromFrac_j4_data->Fill(chargedElectromFrac_j4);
		h_chargedElectromFrac_data->Fill(chargedElectromFrac_j1);
		h_chargedElectromFrac_data->Fill(chargedElectromFrac_j2);
		h_chargedElectromFrac_data->Fill(chargedElectromFrac_j3);
		h_chargedElectromFrac_data->Fill(chargedElectromFrac_j4);

		h_chargedHadEnFrac_j1_data->Fill(chargedHadEnFrac_j1);
		h_chargedHadEnFrac_j2_data->Fill(chargedHadEnFrac_j2);
		h_chargedHadEnFrac_j3_data->Fill(chargedHadEnFrac_j3);
		h_chargedHadEnFrac_j4_data->Fill(chargedHadEnFrac_j4);
		h_chargedHadEnFrac_data->Fill(chargedHadEnFrac_j1);
		h_chargedHadEnFrac_data->Fill(chargedHadEnFrac_j2);
		h_chargedHadEnFrac_data->Fill(chargedHadEnFrac_j3);
		h_chargedHadEnFrac_data->Fill(chargedHadEnFrac_j4);

		h_neutrElectromFrac_j1_data->Fill(neutrElectromFrac_j1);
		h_neutrElectromFrac_j2_data->Fill(neutrElectromFrac_j2);
		h_neutrElectromFrac_j3_data->Fill(neutrElectromFrac_j3);
		h_neutrElectromFrac_j4_data->Fill(neutrElectromFrac_j4);
		h_neutrElectromFrac_data->Fill(neutrElectromFrac_j1);
		h_neutrElectromFrac_data->Fill(neutrElectromFrac_j2);
		h_neutrElectromFrac_data->Fill(neutrElectromFrac_j3);
		h_neutrElectromFrac_data->Fill(neutrElectromFrac_j4);

		h_neutrHadEnFrac_j1_data->Fill(neutrHadEnFrac_j1);
		h_neutrHadEnFrac_j2_data->Fill(neutrHadEnFrac_j2);
		h_neutrHadEnFrac_j3_data->Fill(neutrHadEnFrac_j3);
		h_neutrHadEnFrac_j4_data->Fill(neutrHadEnFrac_j4);
		h_neutrHadEnFrac_data->Fill(neutrHadEnFrac_j1);
		h_neutrHadEnFrac_data->Fill(neutrHadEnFrac_j2);
		h_neutrHadEnFrac_data->Fill(neutrHadEnFrac_j3);
		h_neutrHadEnFrac_data->Fill(neutrHadEnFrac_j4);

		h_photonEnFrac_j1_data->Fill(photonEnFrac_j1);
		h_photonEnFrac_j2_data->Fill(photonEnFrac_j2);
		h_photonEnFrac_j3_data->Fill(photonEnFrac_j3);
		h_photonEnFrac_j4_data->Fill(photonEnFrac_j4);
		h_photonEnFrac_data->Fill(photonEnFrac_j1);
		h_photonEnFrac_data->Fill(photonEnFrac_j2);
		h_photonEnFrac_data->Fill(photonEnFrac_j3);
		h_photonEnFrac_data->Fill(photonEnFrac_j4);

		h_muEnFrac_j1_data->Fill(muEnFrac_j1);
		h_muEnFrac_j2_data->Fill(muEnFrac_j2);
		h_muEnFrac_j3_data->Fill(muEnFrac_j3);
		h_muEnFrac_j4_data->Fill(muEnFrac_j4);
		h_muEnFrac_data->Fill(muEnFrac_j1);
		h_muEnFrac_data->Fill(muEnFrac_j2);
		h_muEnFrac_data->Fill(muEnFrac_j3);
		h_muEnFrac_data->Fill(muEnFrac_j4);

		h_chargedMult_j1_data->Fill(chargedMult_j1);
		h_chargedMult_j2_data->Fill(chargedMult_j2);
		h_chargedMult_j3_data->Fill(chargedMult_j3);
		h_chargedMult_j4_data->Fill(chargedMult_j4);
		h_chargedMult_data->Fill(chargedMult_j1);
		h_chargedMult_data->Fill(chargedMult_j2);
		h_chargedMult_data->Fill(chargedMult_j3);
		h_chargedMult_data->Fill(chargedMult_j4);

		h_neutrMult_j1_data->Fill(neutrMult_j1);
		h_neutrMult_j2_data->Fill(neutrMult_j2);
		h_neutrMult_j3_data->Fill(neutrMult_j3);
		h_neutrMult_j4_data->Fill(neutrMult_j4);
		h_neutrMult_data->Fill(neutrMult_j1);
		h_neutrMult_data->Fill(neutrMult_j2);
		h_neutrMult_data->Fill(neutrMult_j3);
		h_neutrMult_data->Fill(neutrMult_j4);

		h_photonMult_j1_data->Fill(photonMult_j1);
		h_photonMult_j2_data->Fill(photonMult_j2);
		h_photonMult_j3_data->Fill(photonMult_j3);
		h_photonMult_j4_data->Fill(photonMult_j4);
		h_photonMult_data->Fill(photonMult_j1);
		h_photonMult_data->Fill(photonMult_j2);
		h_photonMult_data->Fill(photonMult_j3);
		h_photonMult_data->Fill(photonMult_j4);

		h_nVtx_data->Fill(nVtx);

		h_etaphi_data->Fill(phij1,etaj1);
		h_etaphi_data->Fill(phij2,etaj2);
		h_etaphi_data->Fill(phij3,etaj3);
		h_etaphi_data->Fill(phij4,etaj4);

	}

}// end of event loop






TChain *tree_mc = new TChain("rootTupleTree/tree");

tree_mc->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/QCDFlat_Winter22/Winter22Run3_V1_JECs/QCDFlatMC_Winter22_AK4PUPPI_with_NOISE_FILTERS_reduced_skim.root");

tree_mc->SetBranchAddress("run",&run);
tree_mc->SetBranchAddress("lumi",&lumi);
tree_mc->SetBranchAddress("event",&event);
tree_mc->SetBranchAddress("FourjetMassAK4PUPPI",&FourjetMass);
tree_mc->SetBranchAddress("MaverageAK4PUPPI",&Maverage);
tree_mc->SetBranchAddress("Dijet_MassAK4PUPPI_1",&Dijet_Mass_1);
tree_mc->SetBranchAddress("Dijet_MassAK4PUPPI_2",&Dijet_Mass_2);
tree_mc->SetBranchAddress("MasymmetryAK4PUPPI",&Masymmetry);
tree_mc->SetBranchAddress("DeltaEtaJJAK4PUPPI",&DeltaEtaJJ);
tree_mc->SetBranchAddress("DeltaPhiJJAK4PUPPI",&DeltaPhiJJ);
tree_mc->SetBranchAddress("DeltaRAK4PUPPI_First",&DeltaR_First);
tree_mc->SetBranchAddress("DeltaRAK4PUPPI_Second",&DeltaR_Second);
tree_mc->SetBranchAddress("METoverHTAK4PUPPI",&METoverHT);
tree_mc->SetBranchAddress("pTAK4PUPPI_j1",&pTj1);
tree_mc->SetBranchAddress("pTAK4PUPPI_j2",&pTj2);
tree_mc->SetBranchAddress("pTAK4PUPPI_j3",&pTj3);
tree_mc->SetBranchAddress("pTAK4PUPPI_j4",&pTj4);
tree_mc->SetBranchAddress("etaAK4PUPPI_j1",&etaj1);
tree_mc->SetBranchAddress("etaAK4PUPPI_j2",&etaj2);
tree_mc->SetBranchAddress("etaAK4PUPPI_j3",&etaj3);
tree_mc->SetBranchAddress("etaAK4PUPPI_j4",&etaj4);
tree_mc->SetBranchAddress("phiAK4PUPPI_j1",&phij1);
tree_mc->SetBranchAddress("phiAK4PUPPI_j2",&phij2);
tree_mc->SetBranchAddress("phiAK4PUPPI_j3",&phij3);
tree_mc->SetBranchAddress("phiAK4PUPPI_j4",&phij4);
tree_mc->SetBranchAddress("chargedElectromFracAK4PUPPI_j1",&chargedElectromFrac_j1);
tree_mc->SetBranchAddress("chargedElectromFracAK4PUPPI_j2",&chargedElectromFrac_j2);
tree_mc->SetBranchAddress("chargedElectromFracAK4PUPPI_j3",&chargedElectromFrac_j3);
tree_mc->SetBranchAddress("chargedElectromFracAK4PUPPI_j4",&chargedElectromFrac_j4);
tree_mc->SetBranchAddress("chargedHadEnFracAK4PUPPI_j1",&chargedHadEnFrac_j1);
tree_mc->SetBranchAddress("chargedHadEnFracAK4PUPPI_j2",&chargedHadEnFrac_j2);
tree_mc->SetBranchAddress("chargedHadEnFracAK4PUPPI_j3",&chargedHadEnFrac_j3);
tree_mc->SetBranchAddress("chargedHadEnFracAK4PUPPI_j4",&chargedHadEnFrac_j4);
tree_mc->SetBranchAddress("neutrElectromFracAK4PUPPI_j1",&neutrElectromFrac_j1);
tree_mc->SetBranchAddress("neutrElectromFracAK4PUPPI_j2",&neutrElectromFrac_j2);
tree_mc->SetBranchAddress("neutrElectromFracAK4PUPPI_j3",&neutrElectromFrac_j3);
tree_mc->SetBranchAddress("neutrElectromFracAK4PUPPI_j4",&neutrElectromFrac_j4);
tree_mc->SetBranchAddress("neutrHadEnFracAK4PUPPI_j1",&neutrHadEnFrac_j1);
tree_mc->SetBranchAddress("neutrHadEnFracAK4PUPPI_j2",&neutrHadEnFrac_j2);
tree_mc->SetBranchAddress("neutrHadEnFracAK4PUPPI_j3",&neutrHadEnFrac_j3);
tree_mc->SetBranchAddress("neutrHadEnFracAK4PUPPI_j4",&neutrHadEnFrac_j4);
tree_mc->SetBranchAddress("photonEnFracAK4PUPPI_j1",&photonEnFrac_j1);
tree_mc->SetBranchAddress("photonEnFracAK4PUPPI_j2",&photonEnFrac_j2);
tree_mc->SetBranchAddress("photonEnFracAK4PUPPI_j3",&photonEnFrac_j3);
tree_mc->SetBranchAddress("photonEnFracAK4PUPPI_j4",&photonEnFrac_j4);
tree_mc->SetBranchAddress("muEnFractAK4PUPPI_j1",&muEnFrac_j1);
tree_mc->SetBranchAddress("muEnFractAK4PUPPI_j2",&muEnFrac_j2);
tree_mc->SetBranchAddress("muEnFractAK4PUPPI_j3",&muEnFrac_j3);
tree_mc->SetBranchAddress("muEnFractAK4PUPPI_j4",&muEnFrac_j4);
tree_mc->SetBranchAddress("chargedMultAK4PUPPI_j1",&chargedMult_j1);
tree_mc->SetBranchAddress("chargedMultAK4PUPPI_j2",&chargedMult_j2);
tree_mc->SetBranchAddress("chargedMultAK4PUPPI_j3",&chargedMult_j3);
tree_mc->SetBranchAddress("chargedMultAK4PUPPI_j4",&chargedMult_j4);
tree_mc->SetBranchAddress("neutrMultAK4PUPPI_j1",&neutrMult_j1);
tree_mc->SetBranchAddress("neutrMultAK4PUPPI_j2",&neutrMult_j2);
tree_mc->SetBranchAddress("neutrMultAK4PUPPI_j3",&neutrMult_j3);
tree_mc->SetBranchAddress("neutrMultAK4PUPPI_j4",&neutrMult_j4);
tree_mc->SetBranchAddress("photonMultAK4PUPPI_j1",&photonMult_j1);
tree_mc->SetBranchAddress("photonMultAK4PUPPI_j2",&photonMult_j2);
tree_mc->SetBranchAddress("photonMultAK4PUPPI_j3",&photonMult_j3);
tree_mc->SetBranchAddress("photonMultAK4PUPPI_j4",&photonMult_j4);
tree_mc->SetBranchAddress("nVtx",&nVtx);
tree_mc->SetBranchAddress("weight",&w);
//tree_mc->SetBranchAddress("weight",&weight);


Int_t nentries_mc = (Int_t)tree_mc->GetEntries();
std::cout << "MC: Number of entries =  " << nentries_mc << std::endl;

for (int i=0; i<nentries_mc; i++){    //event loop
//for (int i=0; i<100000; i++){
	tree_mc->GetEntry(i);

	if (i%1000000==0) cout << " done " << i << " from " << nentries_mc << endl;

	double puw;
	puw = h_nVtx_ratio->GetBinContent(nVtx+1);
        double weight = puw*w;

	alpha=Maverage/FourjetMass; 

	if(FourjetMass>1607 && Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0 && alpha>0.1 && event!=13640402 && event!=14664628)
	{
		h_FourjetMass_mc->Fill(FourjetMass, weight);
		h_Maverage_mc->Fill(Maverage, weight); 
		h_Dijet_Mass_1_mc->Fill(Dijet_Mass_1, weight);
		h_Dijet_Mass_2_mc->Fill(Dijet_Mass_2, weight);
		h_Masymmetry_mc->Fill(Masymmetry, weight);
		h_DeltaEtaJJ_mc->Fill(DeltaEtaJJ, weight);
		h_DeltaPhiJJ_mc->Fill(DeltaPhiJJ, weight);
		h_DeltaR_First_mc->Fill(DeltaR_First, weight);
		h_DeltaR_Second_mc->Fill(DeltaR_Second, weight);
		h_METoverHT_mc->Fill(METoverHT, weight);
		h_alpha_mc->Fill(alpha, weight);

		h_pTj1_mc->Fill(pTj1, weight);
		h_pTj2_mc->Fill(pTj2, weight);
		h_pTj3_mc->Fill(pTj3, weight);
		h_pTj4_mc->Fill(pTj4, weight);
		h_pT_mc->Fill(pTj1, weight);
		h_pT_mc->Fill(pTj2, weight);
		h_pT_mc->Fill(pTj3, weight);
		h_pT_mc->Fill(pTj4, weight);

		h_etaj1_mc->Fill(etaj1, weight);
		h_etaj2_mc->Fill(etaj2, weight);
		h_etaj3_mc->Fill(etaj3, weight);
		h_etaj4_mc->Fill(etaj4, weight);
		h_eta_mc->Fill(etaj1, weight);
		h_eta_mc->Fill(etaj2, weight);
		h_eta_mc->Fill(etaj3, weight);
		h_eta_mc->Fill(etaj4, weight);

		h_phij1_mc->Fill(phij1, weight);
		h_phij2_mc->Fill(phij2, weight);
		h_phij3_mc->Fill(phij3, weight);
		h_phij4_mc->Fill(phij4, weight);
		h_phi_mc->Fill(phij1, weight);
		h_phi_mc->Fill(phij2, weight);
		h_phi_mc->Fill(phij3, weight);
		h_phi_mc->Fill(phij4, weight);

		h_chargedElectromFrac_j1_mc->Fill(chargedElectromFrac_j1, weight);
		h_chargedElectromFrac_j2_mc->Fill(chargedElectromFrac_j2, weight);
		h_chargedElectromFrac_j3_mc->Fill(chargedElectromFrac_j3, weight);
		h_chargedElectromFrac_j4_mc->Fill(chargedElectromFrac_j4, weight);
		h_chargedElectromFrac_mc->Fill(chargedElectromFrac_j1, weight);
		h_chargedElectromFrac_mc->Fill(chargedElectromFrac_j2, weight);
		h_chargedElectromFrac_mc->Fill(chargedElectromFrac_j3, weight);
		h_chargedElectromFrac_mc->Fill(chargedElectromFrac_j4, weight);

		h_chargedHadEnFrac_j1_mc->Fill(chargedHadEnFrac_j1, weight);
		h_chargedHadEnFrac_j2_mc->Fill(chargedHadEnFrac_j2, weight);
		h_chargedHadEnFrac_j3_mc->Fill(chargedHadEnFrac_j3, weight);
		h_chargedHadEnFrac_j4_mc->Fill(chargedHadEnFrac_j4, weight);
		h_chargedHadEnFrac_mc->Fill(chargedHadEnFrac_j1, weight);
		h_chargedHadEnFrac_mc->Fill(chargedHadEnFrac_j2, weight);
		h_chargedHadEnFrac_mc->Fill(chargedHadEnFrac_j3, weight);
		h_chargedHadEnFrac_mc->Fill(chargedHadEnFrac_j4, weight);

		h_neutrElectromFrac_j1_mc->Fill(neutrElectromFrac_j1, weight);
		h_neutrElectromFrac_j2_mc->Fill(neutrElectromFrac_j2, weight);
		h_neutrElectromFrac_j3_mc->Fill(neutrElectromFrac_j3, weight);
		h_neutrElectromFrac_j4_mc->Fill(neutrElectromFrac_j4, weight);
		h_neutrElectromFrac_mc->Fill(neutrElectromFrac_j1, weight);
		h_neutrElectromFrac_mc->Fill(neutrElectromFrac_j2, weight);
		h_neutrElectromFrac_mc->Fill(neutrElectromFrac_j3, weight);
		h_neutrElectromFrac_mc->Fill(neutrElectromFrac_j4, weight);

		h_neutrHadEnFrac_j1_mc->Fill(neutrHadEnFrac_j1, weight);
		h_neutrHadEnFrac_j2_mc->Fill(neutrHadEnFrac_j2, weight);
		h_neutrHadEnFrac_j3_mc->Fill(neutrHadEnFrac_j3, weight);
		h_neutrHadEnFrac_j4_mc->Fill(neutrHadEnFrac_j4, weight);
		h_neutrHadEnFrac_mc->Fill(neutrHadEnFrac_j1, weight);
		h_neutrHadEnFrac_mc->Fill(neutrHadEnFrac_j2, weight);
		h_neutrHadEnFrac_mc->Fill(neutrHadEnFrac_j3, weight);
		h_neutrHadEnFrac_mc->Fill(neutrHadEnFrac_j4, weight);

		h_photonEnFrac_j1_mc->Fill(photonEnFrac_j1, weight);
		h_photonEnFrac_j2_mc->Fill(photonEnFrac_j2, weight);
		h_photonEnFrac_j3_mc->Fill(photonEnFrac_j3, weight);
		h_photonEnFrac_j4_mc->Fill(photonEnFrac_j4, weight);
		h_photonEnFrac_mc->Fill(photonEnFrac_j1, weight);
		h_photonEnFrac_mc->Fill(photonEnFrac_j2, weight);
		h_photonEnFrac_mc->Fill(photonEnFrac_j3, weight);
		h_photonEnFrac_mc->Fill(photonEnFrac_j4, weight);

		h_muEnFrac_j1_mc->Fill(muEnFrac_j1, weight);
		h_muEnFrac_j2_mc->Fill(muEnFrac_j2, weight);
		h_muEnFrac_j3_mc->Fill(muEnFrac_j3, weight);
		h_muEnFrac_j4_mc->Fill(muEnFrac_j4, weight);
		h_muEnFrac_mc->Fill(muEnFrac_j1, weight);
		h_muEnFrac_mc->Fill(muEnFrac_j2, weight);
		h_muEnFrac_mc->Fill(muEnFrac_j3, weight);
		h_muEnFrac_mc->Fill(muEnFrac_j4, weight);

		h_chargedMult_j1_mc->Fill(chargedMult_j1, weight);
		h_chargedMult_j2_mc->Fill(chargedMult_j2, weight);
		h_chargedMult_j3_mc->Fill(chargedMult_j3, weight);
		h_chargedMult_j4_mc->Fill(chargedMult_j4, weight);
		h_chargedMult_mc->Fill(chargedMult_j1, weight);
		h_chargedMult_mc->Fill(chargedMult_j2, weight);
		h_chargedMult_mc->Fill(chargedMult_j3, weight);
		h_chargedMult_mc->Fill(chargedMult_j4, weight);

		h_neutrMult_j1_mc->Fill(neutrMult_j1, weight);
		h_neutrMult_j2_mc->Fill(neutrMult_j2, weight);
		h_neutrMult_j3_mc->Fill(neutrMult_j3, weight);
		h_neutrMult_j4_mc->Fill(neutrMult_j4, weight);
		h_neutrMult_mc->Fill(neutrMult_j1, weight);
		h_neutrMult_mc->Fill(neutrMult_j2, weight);
		h_neutrMult_mc->Fill(neutrMult_j3, weight);
		h_neutrMult_mc->Fill(neutrMult_j4, weight);

		h_photonMult_j1_mc->Fill(photonMult_j1, weight);
		h_photonMult_j2_mc->Fill(photonMult_j2, weight);
		h_photonMult_j3_mc->Fill(photonMult_j3, weight);
		h_photonMult_j4_mc->Fill(photonMult_j4, weight);
		h_photonMult_mc->Fill(photonMult_j1, weight);
		h_photonMult_mc->Fill(photonMult_j2, weight);
		h_photonMult_mc->Fill(photonMult_j3, weight);
		h_photonMult_mc->Fill(photonMult_j4, weight);

		h_nVtx_mc->Fill(nVtx, weight);

		h_etaphi_mc->Fill(phij1, etaj1, weight);
		h_etaphi_mc->Fill(phij2, etaj2, weight);
		h_etaphi_mc->Fill(phij3, etaj3, weight);
		h_etaphi_mc->Fill(phij4, etaj4, weight);
	}

}// end of event loop

TFile *fout = new TFile("AllRuns_35fb-1/Histos_DataAllRuns2022_VS_QCDFlatMC_AllSelCrit_PUReweight_AK4PUPPI.root","RECREATE");
fout->cd();

h_FourjetMass_data->Write();
h_Maverage_data->Write();
h_Dijet_Mass_1_data->Write();
h_Dijet_Mass_2_data->Write();
h_alpha_data->Write();
h_pT_data->Write();
h_pTj1_data->Write();
h_pTj2_data->Write();
h_pTj3_data->Write();
h_pTj4_data->Write();
h_eta_data->Write();
h_etaj1_data->Write();
h_etaj2_data->Write();
h_etaj3_data->Write();
h_etaj4_data->Write();
h_phi_data->Write();
h_phij1_data->Write();
h_phij2_data->Write();
h_phij3_data->Write();
h_phij4_data->Write();
h_DeltaEtaJJ_data->Write();
h_DeltaPhiJJ_data->Write();
h_DeltaR_First_data->Write();
h_DeltaR_Second_data->Write();
h_Masymmetry_data->Write();
h_METoverHT_data->Write();
h_chargedElectromFrac_data->Write();
h_chargedElectromFrac_j1_data->Write();
h_chargedElectromFrac_j2_data->Write();
h_chargedElectromFrac_j3_data->Write();
h_chargedElectromFrac_j4_data->Write();
h_chargedHadEnFrac_data->Write();
h_chargedHadEnFrac_j1_data->Write();
h_chargedHadEnFrac_j2_data->Write();
h_chargedHadEnFrac_j3_data->Write();
h_chargedHadEnFrac_j4_data->Write();
h_neutrElectromFrac_data->Write();
h_neutrElectromFrac_j1_data->Write();
h_neutrElectromFrac_j2_data->Write();
h_neutrElectromFrac_j3_data->Write();
h_neutrElectromFrac_j4_data->Write();
h_neutrHadEnFrac_data->Write();
h_neutrHadEnFrac_j1_data->Write();
h_neutrHadEnFrac_j2_data->Write();
h_neutrHadEnFrac_j3_data->Write();
h_neutrHadEnFrac_j4_data->Write();
h_photonEnFrac_data->Write();
h_photonEnFrac_j1_data->Write();
h_photonEnFrac_j2_data->Write();
h_photonEnFrac_j3_data->Write();
h_photonEnFrac_j4_data->Write();
h_muEnFrac_data->Write();
h_muEnFrac_j1_data->Write();
h_muEnFrac_j2_data->Write();
h_muEnFrac_j3_data->Write();
h_muEnFrac_j4_data->Write();
h_chargedMult_data->Write();
h_chargedMult_j1_data->Write();
h_chargedMult_j2_data->Write();
h_chargedMult_j3_data->Write();
h_chargedMult_j4_data->Write();
h_neutrMult_data->Write();
h_neutrMult_j1_data->Write();
h_neutrMult_j2_data->Write();
h_neutrMult_j3_data->Write();
h_neutrMult_j4_data->Write();
h_photonMult_data->Write();
h_photonMult_j1_data->Write();
h_photonMult_j2_data->Write();
h_photonMult_j3_data->Write();
h_photonMult_j4_data->Write();
h_nVtx_data->Write();
h_etaphi_data->Write();

h_FourjetMass_mc->Write();
h_Maverage_mc->Write();
h_Dijet_Mass_1_mc->Write();
h_Dijet_Mass_2_mc->Write();
h_alpha_mc->Write();
h_pT_mc->Write();
h_pTj1_mc->Write();
h_pTj2_mc->Write();
h_pTj3_mc->Write();
h_pTj4_mc->Write();
h_eta_mc->Write();
h_etaj1_mc->Write();
h_etaj2_mc->Write();
h_etaj3_mc->Write();
h_etaj4_mc->Write();
h_phi_mc->Write();
h_phij1_mc->Write();
h_phij2_mc->Write();
h_phij3_mc->Write();
h_phij4_mc->Write();
h_DeltaEtaJJ_mc->Write();
h_DeltaPhiJJ_mc->Write();
h_DeltaR_First_mc->Write();
h_DeltaR_Second_mc->Write();
h_Masymmetry_mc->Write();
h_METoverHT_mc->Write();
h_chargedElectromFrac_mc->Write();
h_chargedElectromFrac_j1_mc->Write();
h_chargedElectromFrac_j2_mc->Write();
h_chargedElectromFrac_j3_mc->Write();
h_chargedElectromFrac_j4_mc->Write();
h_chargedHadEnFrac_mc->Write();
h_chargedHadEnFrac_j1_mc->Write();
h_chargedHadEnFrac_j2_mc->Write();
h_chargedHadEnFrac_j3_mc->Write();
h_chargedHadEnFrac_j4_mc->Write();
h_neutrElectromFrac_mc->Write();
h_neutrElectromFrac_j1_mc->Write();
h_neutrElectromFrac_j2_mc->Write();
h_neutrElectromFrac_j3_mc->Write();
h_neutrElectromFrac_j4_mc->Write();
h_neutrHadEnFrac_mc->Write();
h_neutrHadEnFrac_j1_mc->Write();
h_neutrHadEnFrac_j2_mc->Write();
h_neutrHadEnFrac_j3_mc->Write();
h_neutrHadEnFrac_j4_mc->Write();
h_photonEnFrac_mc->Write();
h_photonEnFrac_j1_mc->Write();
h_photonEnFrac_j2_mc->Write();
h_photonEnFrac_j3_mc->Write();
h_photonEnFrac_j4_mc->Write();
h_muEnFrac_mc->Write();
h_muEnFrac_j1_mc->Write();
h_muEnFrac_j2_mc->Write();
h_muEnFrac_j3_mc->Write();
h_muEnFrac_j4_mc->Write();
h_chargedMult_mc->Write();
h_chargedMult_j1_mc->Write();
h_chargedMult_j2_mc->Write();
h_chargedMult_j3_mc->Write();
h_chargedMult_j4_mc->Write();
h_neutrMult_mc->Write();
h_neutrMult_j1_mc->Write();
h_neutrMult_j2_mc->Write();
h_neutrMult_j3_mc->Write();
h_neutrMult_j4_mc->Write();
h_photonMult_mc->Write();
h_photonMult_j1_mc->Write();
h_photonMult_j2_mc->Write();
h_photonMult_j3_mc->Write();
h_photonMult_j4_mc->Write();
h_nVtx_mc->Write();
h_etaphi_mc->Write();

fout->Close();


}
