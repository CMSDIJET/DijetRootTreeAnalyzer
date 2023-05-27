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

void Create_Histos_QCDMC_4jets(){

TH1D *h_FourjetMass_mc;

TH1D *h_Maverage_mc;

TH1D *h_Dijet_Mass_1_mc;

TH1D *h_Dijet_Mass_2_mc;

TH1D *h_alpha_mc;

TH1D *h_pT_mc, *h_pTj1_mc, *h_pTj2_mc, *h_pTj3_mc, *h_pTj4_mc;

TH1D *h_eta_mc, *h_etaj1_mc, *h_etaj2_mc, *h_etaj3_mc, *h_etaj4_mc;

TH1D *h_phi_mc, *h_phij1_mc, *h_phij2_mc, *h_phij3_mc, *h_phij4_mc;

TH1D *h_DeltaEtaJJ_mc, *h_DeltaPhiJJ_mc, *h_DeltaR_First_mc, *h_DeltaR_Second_mc, *h_METoverHT_mc, *h_Masymmetry_mc; 

TH1D *h_chargedElectromFrac_mc, *h_chargedElectromFrac_j1_mc, *h_chargedElectromFrac_j2_mc, *h_chargedElectromFrac_j3_mc, *h_chargedElectromFrac_j4_mc, *h_chargedHadEnFrac_mc, *h_chargedHadEnFrac_j1_mc, *h_chargedHadEnFrac_j2_mc, *h_chargedHadEnFrac_j3_mc, *h_chargedHadEnFrac_j4_mc, *h_neutrElectromFrac_mc, *h_neutrElectromFrac_j1_mc, *h_neutrElectromFrac_j2_mc, *h_neutrElectromFrac_j3_mc, *h_neutrElectromFrac_j4_mc, *h_neutrHadEnFrac_mc, *h_neutrHadEnFrac_j1_mc, *h_neutrHadEnFrac_j2_mc, *h_neutrHadEnFrac_j3_mc, *h_neutrHadEnFrac_j4_mc, *h_photonEnFrac_mc, *h_photonEnFrac_j1_mc, *h_photonEnFrac_j2_mc, *h_photonEnFrac_j3_mc, *h_photonEnFrac_j4_mc, *h_muEnFrac_mc, *h_muEnFrac_j1_mc, *h_muEnFrac_j2_mc, *h_muEnFrac_j3_mc, *h_muEnFrac_j4_mc;

TH1D *h_chargedMult_mc, *h_chargedMult_j1_mc, *h_chargedMult_j2_mc, *h_chargedMult_j3_mc, *h_chargedMult_j4_mc, *h_neutrMult_mc, *h_neutrMult_j1_mc, *h_neutrMult_j2_mc, *h_neutrMult_j3_mc, *h_neutrMult_j4_mc, *h_photonMult_mc, *h_photonMult_j1_mc, *h_photonMult_j2_mc, *h_photonMult_j3_mc, *h_photonMult_j4_mc;

TH1D *h_nVtx_mc;

TH2D *h_etaphi_mc;

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

h_FourjetMass_mc = new TH1D("h_FourjetMass_mc","",103,massBoundaries);

h_Maverage_mc = new TH1D("h_Maverage_mc","",103,massBoundaries);

h_Dijet_Mass_1_mc = new TH1D("h_Dijet_Mass_1_mc","",103,massBoundaries);

h_Dijet_Mass_2_mc = new TH1D("h_Dijet_Mass_2_mc","",103,massBoundaries);

h_alpha_mc = new TH1D("h_alpha_mc","",50,0,0.5);

h_pT_mc = new TH1D("h_pT_mc","",75,0,6000);

h_pTj1_mc = new TH1D("h_pTj1_mc","",75,0,6000);
h_pTj2_mc = new TH1D("h_pTj2_mc","",75,0,6000);
h_pTj3_mc = new TH1D("h_pTj3_mc","",75,0,6000);
h_pTj4_mc = new TH1D("h_pTj4_mc","",75,0,6000);

h_eta_mc = new TH1D("h_eta_mc","",30,-3,3);

h_etaj1_mc = new TH1D("h_etaj1_mc","",30,-3,3);
h_etaj2_mc = new TH1D("h_etaj2_mc","",30,-3,3);
h_etaj3_mc = new TH1D("h_etaj3_mc","",30,-3,3);
h_etaj4_mc = new TH1D("h_etaj4_mc","",30,-3,3);

h_phi_mc = new TH1D("h_phi_mc","",32,-3.2,3.2);

h_phij1_mc = new TH1D("h_phij1_mc","",32,-3.2,3.2);
h_phij2_mc = new TH1D("h_phij2_mc","",32,-3.2,3.2);
h_phij3_mc = new TH1D("h_phij3_mc","",32,-3.2,3.2);
h_phij4_mc = new TH1D("h_phij4_mc","",32,-3.2,3.2);

h_DeltaEtaJJ_mc = new TH1D("h_DeltaEtaJJ_mc","",40,0,2);

h_DeltaPhiJJ_mc = new TH1D("h_DeltaPhiJJ_mc","",64,0,3.1416);

h_DeltaR_First_mc = new TH1D("h_DeltaR_First_mc","",40,0,4);
h_DeltaR_Second_mc = new TH1D("h_DeltaR_Second_mc","",40,0,4);

h_Masymmetry_mc = new TH1D("h_Masymmetry_mc","",40,0,0.2);

h_METoverHT_mc = new TH1D("h_METoverHT_mc","",60,0,1.2);

h_chargedElectromFrac_mc = new TH1D("h_chargedElectromFrac_mc","",30,0,1.2);
h_chargedElectromFrac_j1_mc = new TH1D("h_chargedElectromFrac_j1_mc","",30,0,1.2);
h_chargedElectromFrac_j2_mc = new TH1D("h_chargedElectromFrac_j2_mc","",30,0,1.2);
h_chargedElectromFrac_j3_mc = new TH1D("h_chargedElectromFrac_j3_mc","",30,0,1.2);
h_chargedElectromFrac_j4_mc = new TH1D("h_chargedElectromFrac_j4_mc","",30,0,1.2);

h_chargedHadEnFrac_mc = new TH1D("h_chargedHadEnFrac_mc","",30,0,1.2);
h_chargedHadEnFrac_j1_mc = new TH1D("h_chargedHadEnFrac_j1_mc","",30,0,1.2);
h_chargedHadEnFrac_j2_mc = new TH1D("h_chargedHadEnFrac_j2_mc","",30,0,1.2);
h_chargedHadEnFrac_j3_mc = new TH1D("h_chargedHadEnFrac_j3_mc","",30,0,1.2);
h_chargedHadEnFrac_j4_mc = new TH1D("h_chargedHadEnFrac_j4_mc","",30,0,1.2);

h_neutrElectromFrac_mc = new TH1D("h_neutrElectromFrac_mc","",30,0,1.2);
h_neutrElectromFrac_j1_mc = new TH1D("h_neutrElectromFrac_j1_mc","",30,0,1.2);
h_neutrElectromFrac_j2_mc = new TH1D("h_neutrElectromFrac_j2_mc","",30,0,1.2);
h_neutrElectromFrac_j3_mc = new TH1D("h_neutrElectromFrac_j3_mc","",30,0,1.2);
h_neutrElectromFrac_j4_mc = new TH1D("h_neutrElectromFrac_j4_mc","",30,0,1.2);

h_neutrHadEnFrac_mc = new TH1D("h_neutrHadEnFrac_mc","",30,0,1.2);
h_neutrHadEnFrac_j1_mc = new TH1D("h_neutrHadEnFrac_j1_mc","",30,0,1.2);
h_neutrHadEnFrac_j2_mc = new TH1D("h_neutrHadEnFrac_j2_mc","",30,0,1.2);
h_neutrHadEnFrac_j3_mc = new TH1D("h_neutrHadEnFrac_j3_mc","",30,0,1.2);
h_neutrHadEnFrac_j4_mc = new TH1D("h_neutrHadEnFrac_j4_mc","",30,0,1.2);

h_photonEnFrac_mc = new TH1D("h_photonEnFrac_mc","",30,0,1.2);
h_photonEnFrac_j1_mc = new TH1D("h_photonEnFrac_j1_mc","",30,0,1.2);
h_photonEnFrac_j2_mc = new TH1D("h_photonEnFrac_j2_mc","",30,0,1.2);
h_photonEnFrac_j3_mc = new TH1D("h_photonEnFrac_j3_mc","",30,0,1.2);
h_photonEnFrac_j4_mc = new TH1D("h_photonEnFrac_j4_mc","",30,0,1.2);

h_muEnFrac_mc = new TH1D("h_muEnFrac_mc","",30,0,1.2);
h_muEnFrac_j1_mc = new TH1D("h_muEnFrac_j1_mc","",30,0,1.2);
h_muEnFrac_j2_mc = new TH1D("h_muEnFrac_j2_mc","",30,0,1.2);
h_muEnFrac_j3_mc = new TH1D("h_muEnFrac_j3_mc","",30,0,1.2);
h_muEnFrac_j4_mc = new TH1D("h_muEnFrac_j4_mc","",30,0,1.2);

h_chargedMult_mc = new TH1D("h_chargedMult_mc","",50,0,100);
h_chargedMult_j1_mc = new TH1D("h_chargedMult_j1_mc","",50,0,100);
h_chargedMult_j2_mc = new TH1D("h_chargedMult_j2_mc","",50,0,100);
h_chargedMult_j3_mc = new TH1D("h_chargedMult_j3_mc","",50,0,100);
h_chargedMult_j4_mc = new TH1D("h_chargedMult_j4_mc","",50,0,100);

h_neutrMult_mc = new TH1D("h_neutrMult_mc","",50,0,100);
h_neutrMult_j1_mc = new TH1D("h_neutrMult_j1_mc","",50,0,100);
h_neutrMult_j2_mc = new TH1D("h_neutrMult_j2_mc","",50,0,100);
h_neutrMult_j3_mc = new TH1D("h_neutrMult_j3_mc","",50,0,100);
h_neutrMult_j4_mc = new TH1D("h_neutrMult_j4_mc","",50,0,100);

h_photonMult_mc = new TH1D("h_photonMult_mc","",50,0,100);
h_photonMult_j1_mc = new TH1D("h_photonMult_j1_mc","",50,0,100);
h_photonMult_j2_mc = new TH1D("h_photonMult_j2_mc","",50,0,100);
h_photonMult_j3_mc = new TH1D("h_photonMult_j3_mc","",50,0,100);
h_photonMult_j4_mc = new TH1D("h_photonMult_j4_mc","",50,0,100);

h_nVtx_mc = new TH1D("h_nVtx_mc","",70,0,70);

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

double run, lumi, event, weight, nVtx, PassJSON, passFilter_BadChargedCandidate, passFilter_BadPFMuon, passFilter_EcalDeadCellTriggerPrimitive, passFilter_HBHENoise, passFilter_HBHENoiseIso, passFilter_eeBadSc, passFilter_globalSuperTightHalo2016, passFilter_goodVertices;
double FourjetMass, Maverage, Dijet_Mass_1, Dijet_Mass_2, Masymmetry, DeltaEtaJJ, DeltaPhiJJ, DeltaR_First, DeltaR_Second, alpha, METoverHT;
double pTj1, pTj2, pTj3, pTj4, etaj1, etaj2, etaj3, etaj4, phij1, phij2, phij3, phij4;
double chargedElectromFrac_j1, chargedElectromFrac_j2, chargedElectromFrac_j3, chargedElectromFrac_j4, chargedHadEnFrac_j1, chargedHadEnFrac_j2, chargedHadEnFrac_j3, chargedHadEnFrac_j4, neutrElectromFrac_j1, neutrElectromFrac_j2, neutrElectromFrac_j3, neutrElectromFrac_j4, neutrHadEnFrac_j1, neutrHadEnFrac_j2, neutrHadEnFrac_j3, neutrHadEnFrac_j4, photonEnFrac_j1, photonEnFrac_j2, photonEnFrac_j3, photonEnFrac_j4, muEnFrac_j1, muEnFrac_j2, muEnFrac_j3, muEnFrac_j4, chargedMult_j1, chargedMult_j2, chargedMult_j3, chargedMult_j4, neutrMult_j1, neutrMult_j2, neutrMult_j3, neutrMult_j4, photonMult_j1, photonMult_j2, photonMult_j3, photonMult_j4;	


TChain *tree_mc = new TChain("rootTupleTree/tree");

tree_mc->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/QCDFlat_Winter22/Winter22Run3/QCDFlatMC_Winter22_AK4PUPPI_with_NOISE_FILTERS_etalt3_reduced_skim.root");

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

for (int i=0; i<nentries_mc; i++){    //event loop
//for (int i=0; i<100000; i++){
	tree_mc->GetEntry(i);

	if (i%1000000==0) cout << " done " << i << " from " << nentries_mc << endl;

	alpha=Maverage/FourjetMass; 

	if(FourjetMass>1607 && Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0 && alpha>0.1 && event!=13640402 && event!=14664628 && passFilter_BadChargedCandidate==1)
	//if(FourjetMass>1607 && Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0 && alpha>0.1 && event!=13640402 && event!=14664628)
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

TFile *fout = new TFile("Paired_Dijet_Analysis_etalt3/Histos_QCDFlatMC_AllSelCrit_AK4PUPPI_withBadChargedCandidate.root","RECREATE");
//TFile *fout = new TFile("Paired_Dijet_Analysis_etalt3/Histos_QCDFlatMC_AllSelCrit_AK4PUPPI_withoutNoiseFilters.root","RECREATE");
fout->cd();

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
