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

void create_hist_signal(int Suu, int Chi){

const int nMassBins = 103;
  
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

 
TH1D *h_FourjetMass = new TH1D("h_FourjetMass","", 103, massBoundaries);
TH1D *h_AverageDijetMass = new TH1D("h_Maverage","", 103, massBoundaries);
TH1D *h_DeltaEtaJJAK4 = new TH1D("h_DeltaEtaJJAK4","", 24, 0, 1.2);
TH1D *h_Masymmetry = new TH1D("h_Masymmetry","", 24, 0, 0.12);
TH1D *h_DeltaRAK4_First = new TH1D("h_DeltaRAK4_First","", 50, 0, 2.5);
TH1D *h_DeltaRAK4_Second = new TH1D("h_DeltaRAK4_Second","", 50, 0, 2.5);
TH1D *h_alpha = new TH1D("h_alpha","", 25, 0, 0.5);
TH2D *h_etaphi = new TH2D("h_etaphi","",24,-3.,3.,32,-3.2,3.2);
TH1D *h_phi_eta1p5to2 = new TH1D("h_phi_eta1p5to2","",32,-3.2,3.2);
TH1D *h_phi_NOTeta1p5to2 = new TH1D("h_phi_NOTeta1p5to2","",32,-3.2,3.2);  

double FourjetMass, Maverage, Masymmetry, DeltaEtaJJAK4, DeltaRAK4_First, DeltaRAK4_Second;
double alpha, etaAK4_j1, etaAK4_j2, etaAK4_j3, etaAK4_j4, phiAK4_j1, phiAK4_j2, phiAK4_j3, phiAK4_j4;
double run;

char fname[1024];
sprintf(fname,"root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/signal_diquarks/EOY2017/etalt1p5/EOY2017_Suu_Diquark_S%d_chi%d_etalt1p5_reduced_skim.root",Suu,Chi);

TFile *f = new TFile(fname,"READ");

TTree *tree = (TTree*)f->Get("rootTupleTree/tree");

tree->SetBranchAddress("FourjetMassAK4CHS",&FourjetMass);
tree->SetBranchAddress("MaverageAK4CHS",&Maverage);
tree->SetBranchAddress("MasymmetryAK4CHS",&Masymmetry);
tree->SetBranchAddress("DeltaEtaJJAK4CHS",&DeltaEtaJJAK4);
tree->SetBranchAddress("DeltaRAK4CHS_First",&DeltaRAK4_First);
tree->SetBranchAddress("DeltaRAK4CHS_Second",&DeltaRAK4_Second);
tree->SetBranchAddress("run",&run);
tree->SetBranchAddress("etaAK4CHS_j1",&etaAK4_j1);
tree->SetBranchAddress("etaAK4CHS_j2",&etaAK4_j2);
tree->SetBranchAddress("etaAK4CHS_j3",&etaAK4_j3);
tree->SetBranchAddress("etaAK4CHS_j4",&etaAK4_j4);
tree->SetBranchAddress("phiAK4CHS_j1",&phiAK4_j1);
tree->SetBranchAddress("phiAK4CHS_j2",&phiAK4_j2);
tree->SetBranchAddress("phiAK4CHS_j3",&phiAK4_j3);
tree->SetBranchAddress("phiAK4CHS_j4",&phiAK4_j4);

Int_t nentries=(Int_t)tree->GetEntries();
std::cout<<"File opened = "<<fname<<std::endl;
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{ 
	tree->GetEntry(i);

  	if (i%10000==0) cout << " done " << i << " from  " << nentries << endl;

    	if(Masymmetry<0.1 && DeltaEtaJJAK4<1.1 && DeltaRAK4_First<2.0 && DeltaRAK4_Second<2.0)
	{	
    		alpha=Maverage/FourjetMass; 
		if(alpha > 0.1)
		{
	     		h_FourjetMass->Fill(FourjetMass); 
			h_AverageDijetMass->Fill(Maverage);
			h_Masymmetry->Fill(Masymmetry);
			h_DeltaEtaJJAK4->Fill(DeltaEtaJJAK4);
			h_DeltaRAK4_First->Fill(DeltaRAK4_First);
			h_DeltaRAK4_Second->Fill(DeltaRAK4_Second);
			h_alpha->Fill(alpha);

			h_etaphi->Fill(etaAK4_j1, phiAK4_j1);
			h_etaphi->Fill(etaAK4_j2, phiAK4_j2);
			h_etaphi->Fill(etaAK4_j3, phiAK4_j3);
			h_etaphi->Fill(etaAK4_j4, phiAK4_j4);

			if(fabs(etaAK4_j1)>1.5 && fabs(etaAK4_j1)<2) h_phi_eta1p5to2->Fill(phiAK4_j1);
			if(fabs(etaAK4_j2)>1.5 && fabs(etaAK4_j2)<2) h_phi_eta1p5to2->Fill(phiAK4_j2);
			if(fabs(etaAK4_j3)>1.5 && fabs(etaAK4_j3)<2) h_phi_eta1p5to2->Fill(phiAK4_j3);
			if(fabs(etaAK4_j4)>1.5 && fabs(etaAK4_j4)<2) h_phi_eta1p5to2->Fill(phiAK4_j4);

			if(!(fabs(etaAK4_j1)>1.5 && fabs(etaAK4_j1)<2)) h_phi_NOTeta1p5to2->Fill(phiAK4_j1);
			if(!(fabs(etaAK4_j2)>1.5 && fabs(etaAK4_j2)<2)) h_phi_NOTeta1p5to2->Fill(phiAK4_j2);
			if(!(fabs(etaAK4_j3)>1.5 && fabs(etaAK4_j3)<2)) h_phi_NOTeta1p5to2->Fill(phiAK4_j3);
			if(!(fabs(etaAK4_j4)>1.5 && fabs(etaAK4_j4)<2)) h_phi_NOTeta1p5to2->Fill(phiAK4_j4);


		}

      	}//end of cuts
      
}// end of event loop

char foutname[1024];
sprintf(foutname,"rootfiles/etalt1p5_ResonanceShapes_EOY2017_Suu_Diquark_S%d_chi%d.root",Suu,Chi);

TFile *fout;
fout = new TFile(foutname,"RECREATE");
fout->cd();

h_FourjetMass->Write();
h_AverageDijetMass->Write();
h_Masymmetry->Write();
h_DeltaEtaJJAK4->Write();
h_DeltaRAK4_First->Write();
h_DeltaRAK4_Second->Write();
h_alpha->Write();
h_etaphi->Write();
h_phi_eta1p5to2->Write();
h_phi_NOTeta1p5to2->Write();

fout->Close();										

}
