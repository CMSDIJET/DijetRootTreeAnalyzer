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
#include "TH1.h"

 void create_Ratio_Method_inputs(){

   double mcut_high = 2438.0;		//cut filling predictions
   double mcut_low = 1530.0;         //cut filling data histograms


  TFile *fMC = TFile::Open("/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/output_root_files/Double_sideband_MC_pythia_2017_merged.root","READ");
  
//  TFile *fdata = TFile::Open("/eos/cms/store/user/dkarasav/small_trees/small_tree_rereco_runsABC_promptreco_D_2018_JEC2018_complete.root","READ");




	//TH1D *h_ratio_MC = (TH1D*)(fMC->Get("h_ratio_MC"));
	TH1D *h_mjj_MC = (TH1D*)(fMC->Get("h_mjj"));
	TH1D *h_mjj_middle_MC = (TH1D*)(fMC->Get("h_mjj_middle"));
	TH1D *h_mjj_high_MC = (TH1D*)(fMC->Get("h_mjj_high"));
	TH1D *h_mjj_1GeVbin_MC = (TH1D*)(fMC->Get("h_mjj_1GeVbin"));
	TH1D *h_mjj_middle_1GeVbin_MC = (TH1D*)(fMC->Get("h_mjj_middle_1GeVbin"));
	TH1D *h_mjj_high_1GeVbin_MC = (TH1D*)(fMC->Get("h_mjj_high_1GeVbin"));




  TH1D *h_mjj,*h_mjj_high,*h_mjj_1GeVbin,*h_mjj_high_1GeVbin,*h_ratio_MC_1GeVbin,*h_mjj_middle,*h_mjj_middle_1GeVbin,*h_ratio_MC,*h_ratio_MC_middle,*h_ratio_MC_middle_1GeVbin;

   const int nMassBins = 102;   
   double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

    Char_t name[1024];

    sprintf(name,"h_mjj");
    h_mjj= new TH1D(name,"",nMassBins,massBoundaries);
    h_mjj->Sumw2();

	sprintf(name,"h_mjj_middle");
    h_mjj_middle= new TH1D(name,"",nMassBins,massBoundaries);
    h_mjj_middle->Sumw2();
     
    sprintf(name,"h_mjj_high");
    h_mjj_high= new TH1D(name,"",nMassBins,massBoundaries);
    h_mjj_high->Sumw2();

	sprintf(name,"h_ratio_MC");
    h_ratio_MC= new TH1D(name,"",nMassBins,massBoundaries);
    h_ratio_MC->Sumw2();

	sprintf(name,"h_ratio_MC_middle");
    h_ratio_MC_middle= new TH1D(name,"",nMassBins,massBoundaries);
    h_ratio_MC_middle->Sumw2();

    sprintf(name,"h_ratio_MC_1GeVbin");
    h_ratio_MC_1GeVbin= new TH1D(name,"",14000,0,14000);
    h_ratio_MC_1GeVbin->Sumw2();  

	sprintf(name,"h_ratio_MC_middle_1GeVbin");
    h_ratio_MC_middle_1GeVbin= new TH1D(name,"",14000,0,14000);
    h_ratio_MC_middle_1GeVbin->Sumw2();    
   
    sprintf(name,"h_mjj_1GeVbin");
    h_mjj_1GeVbin= new TH1D(name,"",14000,0,14000);
    h_mjj_1GeVbin->Sumw2();

	sprintf(name,"h_mjj_middle_1GeVbin");
    h_mjj_middle_1GeVbin= new TH1D(name,"",14000,0,14000);
    h_mjj_middle_1GeVbin->Sumw2();

    sprintf(name,"h_mjj_high_1GeVbin");
    h_mjj_high_1GeVbin= new TH1D(name,"",14000,0,14000);
    h_mjj_high_1GeVbin->Sumw2();

   double met_ov_sumet,MET, chf, nhf, cemf, nemf, muf, cm,pm, nm ,chf_j2,nhf_j2,cemf_j2,nemf_j2,muf_j2;
   double etaAK4_j1, etaAK4_j2, ptAK4_j1,ptAK4_j2, phiAK4_j1, phiAK4_j2,etaWJ_j1, etaWJ_j2, ptWJ_j1,ptWJ_j2, phiWJ_j1,phiWJ_j2, mjj, Dijet_MassAK4, deltaETAjj, deltaPHIjj,cm_j2,pm_j2,nm_j2,nVtx,CosThetaStarWJ;
   double PassJSON,run,lumin,event;
   
   


//TTree *tree = (TTree*)(fdata->Get("t1"));

	TChain *tree = new TChain("t1");
	Char_t filechain[1024];

//	tree->Add("/eos/cms/store/user/dkarasav/small_trees/small_tree_2016_2017_newJEC.root"); //PAS result
	tree->Add("/eos/cms/store/user/dkarasav/small_trees/small_tree_2016_AugV11.root");
	tree->Add("/eos/cms/store/user/dkarasav/small_trees/small_tree_2017_v6.root");
	tree->Add("/eos/cms/store/user/dkarasav/small_trees/small_tree_rereco_runsABC_promptreco_D_2018_JEC2018_V10.root");
  
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
    tree->SetBranchAddress("PassJSON",&PassJSON);   	
    tree->SetBranchAddress("run",&run);
    tree->SetBranchAddress("event",&event);
    tree->SetBranchAddress("lumi",&lumin);



	//first event loop to create the Dratio of Data vs MC and get the correction
    int nentries=(Int_t)tree->GetEntries(); 
    std::cout<<"Number of entries =  "<<nentries<<std::endl;
    for (int i=0; i<nentries; i++)//event loop
	 {    
		tree->GetEntry(i);
		if (i%1000000==0) cout << " Entry reached: "<< i<<"\n";
	//	if(run>320065) continue ;
	//	if ( run>319077 && (  ( fabs(phiWJ_j1)>0.87 && fabs(phiWJ_j1)<1.57  ) || ( fabs(phiWJ_j2)>0.87 && fabs(phiWJ_j2)<1.57  )  ) )cout << " phi j1 = "<< phiWJ_j1 << " phi j2 = "<< phiWJ_j2 << " mjj = "<<  mjj << endl;
//	if ( run < 320497 ) continue;
//	if ( run>319077 && (  ( fabs(phiWJ_j1)>0.87 && fabs(phiWJ_j1)<1.57  ) || ( fabs(phiWJ_j2)>0.87 && fabs(phiWJ_j2)<1.57  )  ) )continue;
//		if ( run>319077 && (  ( fabs(phiWJ_j1)>0.87 && fabs(phiWJ_j1)<1.57  ) || ( fabs(phiWJ_j2)>0.87 && fabs(phiWJ_j2)<1.57  )  ) )
//		{
	
		//if (run < 290000) continue;   // ">" for 2016 or "<" for 2017 
		if( chf!=0 || nhf!=0 || cemf!=0 || nemf!=0 || muf!=0  || chf_j2!=0 || nhf_j2!=0 || cemf_j2!=0 || nemf_j2!=0 || muf_j2!=0) //this is necessary becasue the analyzer, when an event doesn't pass the cuts, fills all the variables with 0
		 {  
			if(met_ov_sumet<0.5 && fabs(etaWJ_j1-etaWJ_j2)<1.1 && mjj>mcut_low  && mjj<14000 && ptWJ_j2<6500 && ptWJ_j1<6500 && PassJSON==1 )
			 {
			    h_mjj->Fill(mjj);
			    h_mjj_1GeVbin->Fill(mjj);
			 } //end of Delta eta cut
			if(met_ov_sumet<0.5 && fabs(etaWJ_j1-etaWJ_j2)>=1.1 && fabs(etaWJ_j1-etaWJ_j2)<=1.5 && mjj>mcut_low  && mjj<14000 && ptWJ_j2<6500 && ptWJ_j1<6500 && PassJSON==1 )
			 {
			    h_mjj_middle->Fill(mjj);
			    h_mjj_middle_1GeVbin->Fill(mjj);
			 } //end of Delta eta cut
			if(met_ov_sumet<0.5 && fabs(etaWJ_j1-etaWJ_j2)>1.5 && fabs(etaWJ_j1-etaWJ_j2)<=2.6 && mjj>mcut_high  && mjj<14000 && ptWJ_j2<6500 && ptWJ_j1<6500 && PassJSON==1 )
			 {
			    h_mjj_high->Fill(mjj);
			    h_mjj_high_1GeVbin->Fill(mjj);
			 } //end of Delta eta cut
		 }// end of if necessary from analyzer
//		}
	 }// end of event loop

/*
	h_mjj->Scale(0.816232);
	h_mjj_1GeVbin->Scale(0.816232);
	h_mjj_middle->Scale(0.816232);
	h_mjj_middle_1GeVbin->Scale(0.816232);
	h_mjj_high->Scale(0.816232);
	h_mjj_high_1GeVbin->Scale(0.816232);
*/

	//rescaling the MC histograms to the data before creating the MC ratio: 

	h_mjj_MC->Scale(h_mjj_1GeVbin->Integral(mcut_high+1,8752) / h_mjj_1GeVbin_MC->Integral(mcut_high+1,8752) );   //scale MC SR for Data SR

//	h_mjj_MC->Scale(  h_mjj_middle_1GeVbin->Integral(mcut_high+1,8752) / h_mjj_middle_1GeVbin_MC->Integral(mcut_high+1,8752) );  //scale MC SR from Data CRmiddle

	h_mjj_middle_MC->Scale( h_mjj_middle_1GeVbin->Integral(mcut_high+1,8752) / h_mjj_middle_1GeVbin_MC->Integral(mcut_high+1,8752) );
	h_mjj_high_MC->Scale( h_mjj_high_1GeVbin->Integral(mcut_high+1,8752) / h_mjj_high_1GeVbin_MC->Integral(mcut_high+1,8752) );

	
/*

	h_mjj_MC->Scale(h_mjj_1GeVbin->Integral(2232,8152) / h_mjj_1GeVbin_MC->Integral(2232,8152) );
	h_mjj_middle_MC->Scale(h_mjj_middle_1GeVbin->Integral(2232,8152) / h_mjj_middle_1GeVbin_MC->Integral(2232,8152) );
	h_mjj_high_MC->Scale(h_mjj_high_1GeVbin->Integral(2232,8152) / h_mjj_high_1GeVbin_MC->Integral(2232,8152) );



	h_mjj_MC->Scale(h_mjj_1GeVbin->Integral(2439,8152) / h_mjj_1GeVbin_MC->Integral(2439,8152) );
	h_mjj_middle_MC->Scale(h_mjj_middle_1GeVbin->Integral(2439,8152) / h_mjj_middle_1GeVbin_MC->Integral(2439,8152) );
	h_mjj_high_MC->Scale(h_mjj_high_1GeVbin->Integral(2439,8152) / h_mjj_high_1GeVbin_MC->Integral(2439,8152) );
*/
		//creating MC ratio with correct errors
	for (int i=0; i<h_mjj_high_MC->GetNbinsX(); i++)
	 { 
		//if (h_mjj->GetBinCenter(i)>2438 && h_mjj->GetBinCenter(i)<8152 && h_mjj->GetBinContent(i)==0 ) h_mjj->SetBinError(i,1.0); //set poison error on zero content data bins (nothing to do with MC histos)
		//if (h_mjj_middle->GetBinCenter(i)>2438 && h_mjj_middle->GetBinCenter(i)<8152 && h_mjj_middle->GetBinContent(i)==0 ) h_mjj_middle->SetBinError(i,1.0); //set poison error on zero content data bins (nothing to do with MC histos)
		if(h_mjj_high_MC->GetBinContent(i)>0)
		 {
			double sr  = h_mjj_MC->GetBinContent(i);
			double esr = h_mjj_MC->GetBinError(i);
			double cr  = h_mjj_high_MC->GetBinContent(i);
			double ecr = h_mjj_high_MC->GetBinError(i);
			if(cr>0)
			 {
				h_ratio_MC->SetBinContent(i,sr/cr);
				h_ratio_MC->SetBinError(i, sqrt( pow(esr/cr,2) + pow(sr*ecr/(cr*cr),2) ) );
			 }
		 }
	 }

	//creating MC ratio middle with correct errors
	for (int i=0; i<h_mjj_high_MC->GetNbinsX(); i++)
	 { 
		if(h_mjj_high_MC->GetBinContent(i)>0)
		 {
			double sr  = h_mjj_middle_MC->GetBinContent(i);
			double esr = h_mjj_middle_MC->GetBinError(i);
			double cr  = h_mjj_high_MC->GetBinContent(i);
			double ecr = h_mjj_high_MC->GetBinError(i);
			if(cr>0)
			 {
				h_ratio_MC_middle->SetBinContent(i,sr/cr);
				h_ratio_MC_middle->SetBinError(i, sqrt( pow(esr/cr,2) + pow(sr*ecr/(cr*cr),2) ) );
			 }
		 }
	 }

	//creating the interpolated 1GeVbin MC ratio 
	for (int i=0; i<h_ratio_MC_1GeVbin->GetNbinsX(); i++) 
	 { 
		double mass = h_ratio_MC_1GeVbin->GetBinCenter(i);
		double smooth_MC = h_ratio_MC->Interpolate(mass);
		if( mass>mcut_low) h_ratio_MC_1GeVbin->SetBinContent(i,smooth_MC);

	 }

	//creating the interpolated 1GeVbin MC ratio middle
	for (int i=0; i<h_ratio_MC_middle_1GeVbin->GetNbinsX(); i++) 
	 { 
		double mass = h_ratio_MC_middle_1GeVbin->GetBinCenter(i);
		double smooth_MC = h_ratio_MC_middle->Interpolate(mass);
		if(mass>mcut_low) h_ratio_MC_middle_1GeVbin->SetBinContent(i,smooth_MC);

	 }

/*
	h_mjj->Scale(1.22514);
	h_mjj_1GeVbin->Scale(1.22514);
	h_mjj_middle->Scale(1.21983);
	h_mjj_middle_1GeVbin->Scale(1.21983);
	h_mjj_high->Scale(1.23178);
	h_mjj_high_1GeVbin->Scale(1.23178);
*/

	TFile *fout = new TFile("/afs/cern.ch/work/d/dkarasav/public/double_sideband_ratio_method/output_root_files/Double_sideband_inputs_16AugV11_17v6_18v10_SR_Scale.root","RECREATE");
	


     h_mjj_MC->SetName("h_mjj_MC");
	 h_mjj_1GeVbin_MC->SetName("h_mjj_MC_1GeVbin");
	 h_mjj_middle_MC->SetName("h_mjj_middle_MC");
	 h_mjj_middle_1GeVbin_MC->SetName("h_mjj_middle_MC_1GeVbin");
	 h_mjj_high_MC->SetName("h_mjj_high_MC");
	 h_mjj_high_1GeVbin_MC->SetName("h_mjj_high_MC_1GeVbin");

	 fout->cd();
	 h_mjj->Write();
	 h_mjj_1GeVbin->Write();
	 h_mjj_middle->Write();
 	 h_mjj_middle_1GeVbin->Write();
	 h_mjj_high->Write();
	 h_mjj_high_1GeVbin->Write();
 	 h_ratio_MC->Write();
 	 h_ratio_MC_middle->Write();
 	 h_ratio_MC_1GeVbin->Write();
 	 h_ratio_MC_middle_1GeVbin->Write();
	 h_mjj_MC->Write();
	 h_mjj_1GeVbin_MC->Write();
	 h_mjj_middle_MC->Write();
 	 h_mjj_middle_1GeVbin_MC->Write();
	 h_mjj_high_MC->Write();
	 h_mjj_high_1GeVbin_MC->Write();

	fout->Close();


}
