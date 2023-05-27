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

void create_hist_data(){

const int nMassBins = 103;
  
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

 
TH1D *h_FourjetMass = new TH1D("h_FourjetMass_AllData","", 103, massBoundaries);
TH1D *h_AverageDijetMass = new TH1D("h_AverageDijetMass_AllData","", 103, massBoundaries);
  
double FourjetMass, Maverage, Masymmetry, DeltaEtaJJAK4, DeltaRAK4_First, DeltaRAK4_Second;
double alpha;
double PassJSON, run;

TChain *tree = new TChain("rootTupleTree/tree");

tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetHT__Run2022B-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetHT__Run2022C-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022C-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022D-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022D-PromptReco-v2__AK4PUPPI_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022E-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022F-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Jan2023_forSync/JetMET__Run2022G-PromptReco-v1__AK4PUPPI_reduced_skim.root");

tree->SetBranchAddress("FourjetMassAK4PUPPI",&FourjetMass);
tree->SetBranchAddress("MaverageAK4PUPPI",&Maverage);
tree->SetBranchAddress("MasymmetryAK4PUPPI",&Masymmetry);
tree->SetBranchAddress("DeltaEtaJJAK4PUPPI",&DeltaEtaJJAK4);
tree->SetBranchAddress("DeltaRAK4PUPPI_First",&DeltaRAK4_First);
tree->SetBranchAddress("DeltaRAK4PUPPI_Second",&DeltaRAK4_Second);
tree->SetBranchAddress("PassJSON",&PassJSON);
tree->SetBranchAddress("run",&run);

Int_t nentries=(Int_t)tree->GetEntries();
std::cout<<"Number of entries =  "<<nentries<<std::endl;

for (int i=0; i<nentries; i++)
{ 
	tree->GetEntry(i);

  	if (i%10000000==0) cout << " done " << i << " from  " << nentries << endl;

    	if(FourjetMass>1607 && Masymmetry<0.1 && DeltaEtaJJAK4<1.1 && DeltaRAK4_First<2.0 && DeltaRAK4_Second<2.0 && PassJSON==1)
	{	
 
    		alpha=Maverage/FourjetMass; 
		if(alpha > 0.1)
		{
	     		h_FourjetMass->Fill(FourjetMass); 
			h_AverageDijetMass->Fill(Maverage);
		}

      	}//end of cuts
      
}// end of event loop

TFile *fout;
fout = new TFile("Histos_AllData.root","RECREATE");
fout->cd();

h_FourjetMass->Write();
h_AverageDijetMass->Write();

fout->Close();										

}
