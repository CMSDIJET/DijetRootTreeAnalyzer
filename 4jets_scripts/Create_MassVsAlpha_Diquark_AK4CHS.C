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

void Create_MassVsAlpha_Diquark_AK4CHS(double width, int Suu, int Chi){

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.07) sprintf(width_name,"0p07");
if (width==0.1) sprintf(width_name,"0p1");


cout << "Width = " << width*100. << "%" << endl;
cout << "M(S) = " << Suu << " GeV, M(chi) = " << Chi << " GeV" << endl;

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1/1000., 3/1000., 6/1000., 10/1000., 16/1000., 23/1000., 31/1000., 40/1000., 50/1000., 61/1000., 74/1000., 88/1000., 103/1000., 119/1000., 137/1000., 156/1000., 176/1000., 197/1000., 220/1000., 244/1000., 270/1000., 296/1000., 325/1000.,
     354/1000., 386/1000., 419/1000., 453/1000., 489/1000., 526/1000., 565/1000., 606/1000., 649/1000., 693/1000., 740/1000., 788/1000., 838/1000., 890/1000., 944/1000., 1000/1000., 1058/1000., 1118/1000., 1181/1000., 1246/1000., 1313/1000., 1383/1000., 1455/1000., 1530/1000., 1607/1000.,
     1687/1000.,1770/1000., 1856/1000., 1945/1000., 2037/1000., 2132/1000., 2231/1000., 2332/1000., 2438/1000., 2546/1000., 2659/1000., 2775/1000., 2895/1000., 3019/1000., 3147/1000., 3279/1000., 3416/1000., 3558/1000., 3704/1000., 3854/1000., 4010/1000., 4171/1000., 4337/1000., 
     4509/1000.,
     4686/1000., 4869/1000., 5058/1000., 5253/1000., 5455/1000., 5663/1000., 5877/1000., 6099/1000., 6328/1000., 6564/1000., 6808/1000., 7060/1000., 7320/1000., 7589/1000., 7866/1000., 8152/1000., 8447/1000., 8752/1000., 9067/1000., 9391/1000., 9726/1000., 10072/1000.,
     10430/1000.,
     10798/1000., 11179/1000., 11571/1000., 11977/1000., 12395/1000., 12827/1000., 13272/1000., 13732/1000., 14000/1000.};

//const int nAlphaBins = 13;

//double alphaBoundaries[nAlphaBins+1] = {0.10, 0.12, 0.14, 0.16, 0.18, 0.20, 0.22, 0.24, 0.26, 0.28, 0.30, 0.32, 0.34, 0.5};

TH2D *h_M4J_vs_alpha;

h_M4J_vs_alpha = new TH2D("h_M4J_vs_alpha","",nMassBins,massBoundaries,20,0.10,0.50);


double run, lumi, event, nVtx;
double FourjetMass, Maverage, Dijet_Mass_1, Dijet_Mass_2, Masymmetry, DeltaEtaJJ, DeltaPhiJJ, DeltaR_First, DeltaR_Second, alpha, METoverHT;
double pTj1, pTj2, pTj3, pTj4, etaj1, etaj2, etaj3, etaj4, phij1, phij2, phij3, phij4;
double chargedElectromFrac_j1, chargedElectromFrac_j2, chargedElectromFrac_j3, chargedElectromFrac_j4, chargedHadEnFrac_j1, chargedHadEnFrac_j2, chargedHadEnFrac_j3, chargedHadEnFrac_j4, neutrElectromFrac_j1, neutrElectromFrac_j2, neutrElectromFrac_j3, neutrElectromFrac_j4, neutrHadEnFrac_j1, neutrHadEnFrac_j2, neutrHadEnFrac_j3, neutrHadEnFrac_j4, photonEnFrac_j1, photonEnFrac_j2, photonEnFrac_j3, photonEnFrac_j4, muEnFrac_j1, muEnFrac_j2, muEnFrac_j3, muEnFrac_j4, chargedMult_j1, chargedMult_j2, chargedMult_j3, chargedMult_j4, neutrMult_j1, neutrMult_j2, neutrMult_j3, neutrMult_j4, photonMult_j1, photonMult_j2, photonMult_j3, photonMult_j4;	

TChain *tree_mc = new TChain("rootTupleTree/tree");

char fname[1024];
sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_NOMINAL/RunIISummer20UL18_Suu-Diquark_W-%s_S-%d_chi-%d__AK4CHS_reduced_skim.root",width_name,Suu,Chi);

//sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/reduced_trees/Suu_Diquarks/RunIIFall17MiniAODv2/MC2017_Suu_Diquark_S%d_chi%d_reduced_skim.root",Suu,Chi);

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

	if(Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0)
	{
		h_M4J_vs_alpha->Fill(FourjetMass/1000.,alpha);
	}


}// end of event loop

h_M4J_vs_alpha->Scale(1./h_M4J_vs_alpha->Integral());

char outputfilename[1024];

sprintf(outputfilename,"signal_histos_Alpha/M4JvsAlpha_Suu-Diquark_W-%s_S-%d_chi-%d.root",width_name,Suu,Chi);

TFile *fout = new TFile(outputfilename,"RECREATE");
fout->cd();

h_M4J_vs_alpha->Write();

fout->Close();


}
