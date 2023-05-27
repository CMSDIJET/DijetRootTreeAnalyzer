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

void PUReweight(){

TH1D *h_nVtx_data;
TH1D *h_nVtx_mc;
TH1D *h_nVtx_ratio;

h_nVtx_data = new TH1D("h_nVtx_data","",100,-0.5,99.5);
h_nVtx_mc = new TH1D("h_nVtx_mc","",100,-0.5,99.5);
h_nVtx_ratio = new TH1D("h_nVtx_ratio","",100,-0.5,99.5);

h_nVtx_mc->Sumw2();

double run, lumi, event, weight, nVtx, PassJSON;
double FourjetMass, Maverage, Dijet_Mass_1, Dijet_Mass_2, Masymmetry, DeltaEtaJJ, DeltaR_First, DeltaR_Second, alpha;

TChain *tree_data = new TChain("rootTupleTree/tree");

tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetHT__Run2022B-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetHT__Run2022C-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022C-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022D-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022D-PromptReco-v2__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022E-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022F-PromptReco-v1__AK4PUPPI_reduced_skim.root");
tree_data->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/data/promptReco/Winter22Run3_FullJECs/JetMET__Run2022G-PromptReco-v1__AK4PUPPI_reduced_skim.root");


tree_data->SetBranchAddress("run",&run);
tree_data->SetBranchAddress("lumi",&lumi);
tree_data->SetBranchAddress("event",&event);
tree_data->SetBranchAddress("nVtx",&nVtx);
tree_data->SetBranchAddress("PassJSON",&PassJSON);
tree_data->SetBranchAddress("FourjetMassAK4PUPPI",&FourjetMass);
tree_data->SetBranchAddress("MaverageAK4PUPPI",&Maverage);
tree_data->SetBranchAddress("Dijet_MassAK4PUPPI_1",&Dijet_Mass_1);
tree_data->SetBranchAddress("Dijet_MassAK4PUPPI_2",&Dijet_Mass_2);
tree_data->SetBranchAddress("MasymmetryAK4PUPPI",&Masymmetry);
tree_data->SetBranchAddress("DeltaEtaJJAK4PUPPI",&DeltaEtaJJ);
tree_data->SetBranchAddress("DeltaRAK4PUPPI_First",&DeltaR_First);
tree_data->SetBranchAddress("DeltaRAK4PUPPI_Second",&DeltaR_Second);

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
		h_nVtx_data->Fill(nVtx);
	}

}// end of event loop



TChain *tree_mc = new TChain("rootTupleTree/tree");

tree_mc->Add("root:://eoscms///eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/reduced_trees/QCDMC/QCDFlat_Winter22/Winter22Run3/QCDFlatMC_Winter22_AK4PUPPI_reduced_skim.root");

tree_mc->SetBranchAddress("run",&run);
tree_mc->SetBranchAddress("lumi",&lumi);
tree_mc->SetBranchAddress("event",&event);
tree_mc->SetBranchAddress("nVtx",&nVtx);
tree_mc->SetBranchAddress("weight",&weight);
tree_mc->SetBranchAddress("FourjetMassAK4PUPPI",&FourjetMass);
tree_mc->SetBranchAddress("MaverageAK4PUPPI",&Maverage);
tree_mc->SetBranchAddress("Dijet_MassAK4PUPPI_1",&Dijet_Mass_1);
tree_mc->SetBranchAddress("Dijet_MassAK4PUPPI_2",&Dijet_Mass_2);
tree_mc->SetBranchAddress("MasymmetryAK4PUPPI",&Masymmetry);
tree_mc->SetBranchAddress("DeltaEtaJJAK4PUPPI",&DeltaEtaJJ);
tree_mc->SetBranchAddress("DeltaRAK4PUPPI_First",&DeltaR_First);
tree_mc->SetBranchAddress("DeltaRAK4PUPPI_Second",&DeltaR_Second);

Int_t nentries_mc = (Int_t)tree_mc->GetEntries();
std::cout << "MC: Number of entries =  " << nentries_mc << std::endl;

for (int i=0; i<nentries_mc; i++){    //event loop
//for (int i=0; i<100000; i++){
	tree_mc->GetEntry(i);

	if (i%1000000==0) cout << " done " << i << " from " << nentries_mc << endl;

	alpha=Maverage/FourjetMass;

	if(FourjetMass>1607 && Masymmetry<0.1 && DeltaEtaJJ<1.1 && DeltaR_First<2.0 && DeltaR_Second<2.0 && alpha>0.1 && event!=13640402 && event!=14664628)
	{
		h_nVtx_mc->Fill(nVtx, weight);
	}

}// end of event loop

h_nVtx_ratio->Divide(h_nVtx_data, h_nVtx_mc);

TFile *fout = new TFile("AllRuns_34fb-1/PUReweight_AllRuns_PUPPI.root","RECREATE");
fout->cd();

h_nVtx_data->Write();
h_nVtx_mc->Write();
h_nVtx_ratio->Write();

fout->Close();


}
