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

void create_hist_etaphi_all_signals_Run2(){

TH2D *h_etaphi = new TH2D("h_etaphi","",24,-3.,3.,32,-3.2,3.2);
TH1D *h_phi_eta1p5to2 = new TH1D("h_phi_eta1p5to2","",32,-3.2,3.2);
TH1D *h_phi_NOTeta1p5to2 = new TH1D("h_phi_NOTeta1p5to2","",32,-3.2,3.2);  

double FourjetMass, Maverage, Masymmetry, DeltaEtaJJAK4, DeltaRAK4_First, DeltaRAK4_Second;
double alpha, etaAK4_j1, etaAK4_j2, etaAK4_j3, etaAK4_j4, phiAK4_j1, phiAK4_j2, phiAK4_j3, phiAK4_j4;
double run;

TChain *tree = new TChain("rootTupleTree/tree");

tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S2000_chi300_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S2000_chi500_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S2000_chi660_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S4000_chi1320_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S4000_chi600_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S5000_chi1250_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S7000_chi1750_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S8000_chi1200_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S8000_chi2640_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S3000_chi750_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S4000_chi1000_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S3000_chi450_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S7000_chi1050_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S3000_chi990_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S6000_chi1740_reduced_skim.root");

tree->SetBranchAddress("FourjetMass",&FourjetMass);
tree->SetBranchAddress("Maverage",&Maverage);
tree->SetBranchAddress("Masymmetry",&Masymmetry);
tree->SetBranchAddress("DeltaEtaJJAK4",&DeltaEtaJJAK4);
tree->SetBranchAddress("DeltaRAK4_First",&DeltaRAK4_First);
tree->SetBranchAddress("DeltaRAK4_Second",&DeltaRAK4_Second);
tree->SetBranchAddress("run",&run);
tree->SetBranchAddress("etaAK4_j1",&etaAK4_j1);
tree->SetBranchAddress("etaAK4_j2",&etaAK4_j2);
tree->SetBranchAddress("etaAK4_j3",&etaAK4_j3);
tree->SetBranchAddress("etaAK4_j4",&etaAK4_j4);
tree->SetBranchAddress("phiAK4_j1",&phiAK4_j1);
tree->SetBranchAddress("phiAK4_j2",&phiAK4_j2);
tree->SetBranchAddress("phiAK4_j3",&phiAK4_j3);
tree->SetBranchAddress("phiAK4_j4",&phiAK4_j4);

Int_t nentries=(Int_t)tree->GetEntries();
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
			h_etaphi->Fill(etaAK4_j1, phiAK4_j1);
			h_etaphi->Fill(etaAK4_j2, phiAK4_j2);
			h_etaphi->Fill(etaAK4_j3, phiAK4_j3);
			h_etaphi->Fill(etaAK4_j4, phiAK4_j4);

			if(etaAK4_j1>1.5 && etaAK4_j1<2) h_phi_eta1p5to2->Fill(phiAK4_j1);
			if(etaAK4_j2>1.5 && etaAK4_j2<2) h_phi_eta1p5to2->Fill(phiAK4_j2);
			if(etaAK4_j3>1.5 && etaAK4_j3<2) h_phi_eta1p5to2->Fill(phiAK4_j3);
			if(etaAK4_j4>1.5 && etaAK4_j4<2) h_phi_eta1p5to2->Fill(phiAK4_j4);

			if(!(etaAK4_j1>1.5 && etaAK4_j1<2)) h_phi_NOTeta1p5to2->Fill(phiAK4_j1);
			if(!(etaAK4_j2>1.5 && etaAK4_j2<2)) h_phi_NOTeta1p5to2->Fill(phiAK4_j2);
			if(!(etaAK4_j3>1.5 && etaAK4_j3<2)) h_phi_NOTeta1p5to2->Fill(phiAK4_j3);
			if(!(etaAK4_j4>1.5 && etaAK4_j4<2)) h_phi_NOTeta1p5to2->Fill(phiAK4_j4);


		}

      	}//end of cuts
      
}// end of event loop

char foutname[1024];
sprintf(foutname,"rootfiles/etaphi_EOY2017_allsignals.root");

TFile *fout;
fout = new TFile(foutname,"RECREATE");
fout->cd();

h_etaphi->Write();
h_phi_eta1p5to2->Write();
h_phi_NOTeta1p5to2->Write();

fout->Close();										

}
