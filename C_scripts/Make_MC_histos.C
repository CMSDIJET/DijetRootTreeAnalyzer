#include "TF1.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "setTDRStyle_teliko.C"
#include "stdio.h"
#include "stdlib.h"

 void Make_MC_histos(Int_t which){

  double mcut_low=1250.;
  double mcut_high=1250.;
  char name[1024]; 

  TH1D *h_mjj,*h_mjj_high,*h_ratio_MC,*h_mjj_1GeVbin,*h_mjj_high_1GeVbin,*h_mjj_middle_1GeVbin,*h_mjj_middle;

   const int nMassBins = 102;
   double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509,
     4686,  4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8752, 9067, 9391, 9726, 10072, 
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

    sprintf(name,"h_mjj");
    h_mjj= new TH1D(name,"",nMassBins,massBoundaries);

	sprintf(name,"h_mjj_middle");
    h_mjj_middle= new TH1D(name,"",nMassBins,massBoundaries);

    sprintf(name,"h_mjj_1GeVbin");
    h_mjj_1GeVbin= new TH1D(name,"",14000,0,14000);

	sprintf(name,"h_mjj_middle_1GeVbin");
    h_mjj_middle_1GeVbin= new TH1D(name,"",14000,0,14000);

    sprintf(name,"h_mjj_high");
    h_mjj_high= new TH1D(name,"",nMassBins,massBoundaries);

    sprintf(name,"h_mjj_high_1GeVbin");
    h_mjj_high_1GeVbin= new TH1D(name,"",14000,0,14000);

    sprintf(name,"h_ratio_MC");
    h_ratio_MC= new TH1D(name,"",nMassBins,massBoundaries);
  
    h_mjj->Sumw2();
	h_mjj_middle->Sumw2();
    h_mjj_high->Sumw2();
	h_mjj_1GeVbin->Sumw2();
	h_mjj_middle_1GeVbin->Sumw2();
    h_mjj_high_1GeVbin->Sumw2();
    h_ratio_MC->Sumw2();

 double met_ov_sumet,MET, chf, nhf, cemf, nemf, muf, cm,pm, nm ,chf_j2,nhf_j2,cemf_j2,nemf_j2,muf_j2;
  double etaAK4_j1, etaAK4_j2, ptAK4_j1,ptAK4_j2, phiAK4_j1, phiAK4_j2,etaWJ_j1, etaWJ_j2, ptWJ_j1,ptWJ_j2, phiWJ_j1,phiWJ_j2, mjj, Dijet_MassAK4, deltaETAjj, deltaPHIjj,cm_j2,pm_j2,nm_j2,nVtx,CosThetaStarWJ, w;



  TFile *f ;


	if(which==1) f = TFile::Open("/eos/cms/store/user/dkarasav/small_trees/small_tree_MC_2016.root","READ");
	if(which==2) f = TFile::Open("/eos/cms/store/user/dkarasav/small_trees/small_tree_MC_2017.root","READ");

	TTree *tree = (TTree*)(f->Get("t1"));
	
    tree->SetBranchAddress("metSig",&met_ov_sumet);
    tree->SetBranchAddress("MET",&MET);
    tree->SetBranchAddress("chargedHadEnFrac_j1",&chf);
    tree->SetBranchAddress("neutrHadEnFrac_j1",&nhf);
    tree->SetBranchAddress("chargedElectromFrac_j1",&cemf);
    tree->SetBranchAddress("neutrElectromFrac_j1",&nemf);
    tree->SetBranchAddress("muEnFract_j1",&muf);
    tree->SetBranchAddress("chargedHadEnFrac_j2",&chf_j2);
    tree->SetBranchAddress("neutrHadEnFrac_j2",&nhf_j2);
    tree->SetBranchAddress("chargedElectromFrac_j2",&cemf_j2);
    tree->SetBranchAddress("neutrElectromFrac_j2",&nemf_j2);
    tree->SetBranchAddress("muEnFract_j2",&muf_j2);
    tree->SetBranchAddress("etaAK4_j1",&etaAK4_j1);
    tree->SetBranchAddress("etaAK4_j2",&etaAK4_j2);
    tree->SetBranchAddress("pTAK4_j1",&ptAK4_j1);
    tree->SetBranchAddress("pTAK4_j2",&ptAK4_j2);
    tree->SetBranchAddress("phiAK4_j1",&phiAK4_j1);
    tree->SetBranchAddress("phiAK4_j2",&phiAK4_j2);
    tree->SetBranchAddress("etaWJ_j1",&etaWJ_j1);
    tree->SetBranchAddress("etaWJ_j2",&etaWJ_j2);
    tree->SetBranchAddress("ptWJ_j1",&ptWJ_j1);
    tree->SetBranchAddress("ptWJ_j2",&ptWJ_j2);
    tree->SetBranchAddress("phiWJ_j1",&phiWJ_j1);
    tree->SetBranchAddress("phiWJ_j2",&phiWJ_j2);
    tree->SetBranchAddress("mjj", &mjj);
    tree->SetBranchAddress("Dijet_MassAK4", &Dijet_MassAK4);
    tree->SetBranchAddress("deltaETAjj", &deltaETAjj);
    tree->SetBranchAddress("deltaPHIjj", &deltaPHIjj);
    tree->SetBranchAddress("chargedMult_j1",&cm);
    tree->SetBranchAddress("neutrMult_j1",&nm);
    tree->SetBranchAddress("photonMult_j1",&pm);
    tree->SetBranchAddress("chargedMult_j2",&cm_j2);
    tree->SetBranchAddress("neutrMult_j2",&nm_j2);
    tree->SetBranchAddress("photonMult_j2",&pm_j2);
    tree->SetBranchAddress("nVtx",&nVtx);	
    tree->SetBranchAddress("CosThetaStarWJ",&CosThetaStarWJ);
    tree->SetBranchAddress("weight",&w);


    Int_t nentries=(Int_t)tree->GetEntries(); 

	std::cout << "Initializing loop to create the histograms of SR, CR1, CR2 " << endl;

    std::cout<<"Number of entries =  "<<nentries<<std::endl;
   
    for (int i=0; i<nentries; i++)//event loop
	 {    
		tree->GetEntry(i);
		if (i%1000000==0) cout << " Entry reached: "<< i<<"\n";
	//	if(w>5.5 && ptWJ_j1>1000) continue;  //if statement to cut problematic events on 300-470 pt hat bin  for 2017 MC-QCD
		if( chf!=0 || nhf!=0 || cemf!=0 || nemf!=0 || muf!=0  || chf_j2!=0 || nhf_j2!=0 || cemf_j2!=0 || nemf_j2!=0 || muf_j2!=0) //this is necessary becasue the analyzer, when an event doesn't pass the cuts, fills all the variables with 0
		 {  
			if (mjj>6000 && w>8.) continue;
			if(fabs(etaWJ_j1-etaWJ_j2)<1.1 && mjj>mcut_low  && mjj<14000 && ptWJ_j2<6500 && ptWJ_j1<6500 )
			 {
			    h_mjj->Fill(mjj,w);
			    h_mjj_1GeVbin->Fill(mjj,w);
			 } //end of Delta eta cut
			if(fabs(etaWJ_j1-etaWJ_j2)>=1.1 && fabs(etaWJ_j1-etaWJ_j2)<1.5 && mjj>mcut_low  && mjj<14000 && ptWJ_j2<6500 && ptWJ_j1<6500 )
			 {
			    h_mjj_middle->Fill(mjj,w);
			    h_mjj_middle_1GeVbin->Fill(mjj,w);
			 } //end of Delta eta cut
			if(fabs(etaWJ_j1-etaWJ_j2)>=1.5 && fabs(etaWJ_j1-etaWJ_j2)<=2.6 && mjj>mcut_high  && mjj<14000 && ptWJ_j2<6500 && ptWJ_j1<6500 )
			 {
			    h_mjj_high->Fill(mjj,w);
			    h_mjj_high_1GeVbin->Fill(mjj,w);
			 } //end of Delta eta cut
		 } //end of if necessary from analyzer
	 }// end of event loop

//h_ratio_MC->Divide(h_mjj,h_mjj_high);

	//creating MC ratio with correct errors
	for (int i=0; i<h_mjj_high->GetNbinsX(); i++)
	 { 
		if(h_mjj_high->GetBinContent(i)>0)
		 {
			double sr  = h_mjj->GetBinContent(i);
			double esr = h_mjj->GetBinError(i);
			double cr  = h_mjj_high->GetBinContent(i);
			double ecr = h_mjj_high->GetBinError(i);
			if(cr>0)
			 {
				h_ratio_MC->SetBinContent(i,sr/cr);
				h_ratio_MC->SetBinError(i, sqrt( pow(esr/cr,2) + pow(sr*ecr/(cr*cr),2) ) );
			 }
		 }
	 }

	h_ratio_MC->Draw();



	TFile *fout;
	if(which==1) fout = new TFile("/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/Nick_Wardle_scripts/ATLAS_crash_tests/histos_MC16_pythia_mjjCut1250.root","RECREATE");
	if(which==2) fout = new TFile("/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/output_root_files/Double_sideband_MC_pythia_2017_merged.root","RECREATE");

	fout->cd();
	h_mjj->Write();
	h_mjj_high->Write();
	h_mjj_middle->Write();
	h_ratio_MC->Write();
	h_mjj_1GeVbin->Write();
	h_mjj_high_1GeVbin->Write();
	h_mjj_middle_1GeVbin->Write();

	fout->Close();

}
