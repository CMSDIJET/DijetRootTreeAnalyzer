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

 void create_small_tree_MC(){


	float lumi;
	lumi=58830.0;

	double mcut_low = 800;


//  	double cross_section[15] = { 1246000000,106900000, 15710000 ,2336000 ,407300.,103500., 6830.,552.1,156.5,0.8369012*26.28, 7.47, 0.6484, 0.08743, 0.005236, 0.0001357};
 // 	double cross_section[15] = { 1246000000,106900000, 0.992951*15710000 ,2336000 ,407300.,0.997644*103500., 0.998084*6830.,0.995483*552.1, 156.5, 0.8369012*26.28, 7.47, 0.6484, 0.08743, 0.830556*0.005236, 0.0001357};    // xsec for 2018,  corrected for processed % of 2018 events.
	// 15-30: 1246000000, 30-50: 106900000
	  //double cross_section_mad[8] = {  1899000 ,156500 ,38970,4150.,1000,184.4,21.31, 4.16 };
	  //double cross_section_mad_en[8] = {  1321000. ,87950.,17570.,1512.,320., 50.26, 4.41, 0.87 };



	double cross_section[15] = { 1820000000,138900000, 19100000 ,2735000 ,467500.,117400., 7753.,642.1, 185.9, 32.05, 9.365	, 0.8398, 0.1124, 0.006752, 0.0001626}; //xsec of 2017

	char PtHatBin[15][50] = {"15to30" , "30to50", "50to80", "80to120", "120to170" , "170to300" , "300to470" , "470to600" , "600to800" , "800to1000" , "1000to1400", "1400to1800", "1800to2400", "2400to3200", "3200toInf"  }; //ptHatBins of MC
	 // double weight[15];
	long double weight[15];
	  

	double met_ov_sumet,MET, chf, nhf, cemf, nemf, muf, cm,pm, nm ,chf_j2,nhf_j2,cemf_j2,nemf_j2,muf_j2;
	double etaAK4_j1, etaAK4_j2, ptAK4_j1,ptAK4_j2, phiAK4_j1, phiAK4_j2,etaWJ_j1, etaWJ_j2, ptWJ_j1,ptWJ_j2, phiWJ_j1,phiWJ_j2, mjj, Dijet_MassAK4, deltaETAjj, deltaPHIjj,cm_j2,pm_j2,nm_j2,nVtx,CosThetaStarWJ;
	double PassJSON,run,lumin,event;

     double w;
   	 char pTbin[50];

	TFile *fout;
//	fout=new TFile("/eos/cms/store/user/dkarasav/small_trees/small_tree_MC_2018_xsec17_newJec.root","recreate");                                 //CREATING NEW TREE
	fout=new TFile("/eos/cms/store/user/dkarasav/small_trees/small_tree_MC_2018_xsec17_newJec_mjjCut800.root","recreate");                                 //CREATING NEW TREE

	TTree t1("t1","tree");
	 


    t1.Branch("metSig",&met_ov_sumet,"metSig/D");
    t1.Branch("MET",&MET,"MET/D"); 
    t1.Branch("chargedHadEnFrac_j1",&chf,"chargedHadEnFrac_j1/D");
    t1.Branch("neutrHadEnFrac_j1",&nhf,"neutrHadEnFrac_j1/D");
    t1.Branch("chargedElectromFrac_j1",&cemf,"chargedElectromFrac_j1/D");
    t1.Branch("neutrElectromFrac_j1",&nemf,"neutrElectromFrac_j1/D");
    t1.Branch("muEnFract_j1",&muf,"muEnFract_j1/D");
    t1.Branch("chargedHadEnFrac_j2",&chf_j2,"chargedHadEnFrac_j2/D");
    t1.Branch("neutrHadEnFrac_j2",&nhf_j2,"neutrHadEnFrac_j2/D");
    t1.Branch("chargedElectromFrac_j2",&cemf_j2,"chargedElectromFrac_j2/D");
    t1.Branch("neutrElectromFrac_j2",&nemf_j2,"neutrElectromFrac_j2/D");
    t1.Branch("muEnFract_j2",&muf_j2,"muEnFract_j2/D");
    t1.Branch("etaAK4_j1",&etaAK4_j1,"etaAK4_j1/D");
    t1.Branch("etaAK4_j2",&etaAK4_j2,"etaAK4_j2/D");
    t1.Branch("pTAK4_j1",&ptAK4_j1,"pTAK4_j1/D");
    t1.Branch("pTAK4_j2",&ptAK4_j2,"pTAK4_j2/D");
    t1.Branch("phiAK4_j1",&phiAK4_j1,"phiAK4_j1/D");
    t1.Branch("phiAK4_j2",&phiAK4_j2,"phiAK4_j2/D");
    t1.Branch("etaWJ_j1",&etaWJ_j1,"etaWJ_j1/D");
    t1.Branch("etaWJ_j2",&etaWJ_j2,"etaWJ_j2/D");
    t1.Branch("ptWJ_j1",&ptWJ_j1,"ptWJ_j1/D");
    t1.Branch("ptWJ_j2",&ptWJ_j2,"ptWJ_j2/D");
    t1.Branch("phiWJ_j1",&phiWJ_j1,"phiWJ_j1/D");
    t1.Branch("phiWJ_j2",&phiWJ_j2,"phiWJ_j2/D");
    t1.Branch("mjj",&mjj,"mjj/D");
    t1.Branch("Dijet_MassAK4", &Dijet_MassAK4,"Dijet_MassAK4/D");
    t1.Branch("deltaETAjj", &deltaETAjj,"deltaETAjj/D");
    t1.Branch("deltaPHIjj", &deltaPHIjj,"deltaPHIjj/D");
    t1.Branch("chargedMult_j1",&cm,"chargedMult_j1/D");
    t1.Branch("neutrMult_j1",&nm,"neutrMult_j1/D");
    t1.Branch("photonMult_j1",&pm,"photonMult_j1/D");
    t1.Branch("chargedMult_j2",&cm_j2,"chargedMult_j2/D");
    t1.Branch("neutrMult_j2",&nm_j2,"neutrMult_j2/D");
    t1.Branch("photonMult_j2",&pm_j2,"photonMult_j2/D");
    t1.Branch("nVtx",&nVtx,"nVtx/D");	
    t1.Branch("CosThetaStarWJ",&CosThetaStarWJ,"CosThetaStarWJ/D");
    t1.Branch("run",&run,"run/D");
    t1.Branch("event",&event,"event/D");
    t1.Branch("lumi",&lumin,"lumi/D");
    t1.Branch("weight",&w,"weight/D");
    t1.Branch("pTbin",&pTbin,"pTbin/C");


	std::cout<<"Calculating the weights of each pt-hat bin file... "  << std::endl;
	int Ntotal;

	TFile *f1;

	TTree *tree;
	for(int fl=1; fl<15; fl++)
	{ 
		char input_directory[300];
		strcpy(input_directory,"/eos/cms/store/user/dkarasav/QCD_Autumn18_JEC18/Pt_");
		strcat(input_directory,PtHatBin[fl]);
		char file_name[200];
		sprintf(file_name,"_QCD_TuneCP5_13TeV_pythia8_Autumn18_reduced_skim.root");
		strcat(input_directory,file_name);
		f1 = TFile::Open(input_directory,"READ");
	    TH1D *h_Nev = (TH1D*)f1->Get("DijetFilter/EventCount/EventCounter");
	    int Nev = h_Nev->GetBinContent(2);
		tree = (TTree*)f1->Get("rootTupleTree/tree");
		Ntotal = Ntotal + tree->GetEntries();

	    //std::cout<<"Events "<<Nev<<std::endl;
		weight[fl] = cross_section[fl]*lumi/Nev;
	    std::cout<< "pT bin : " << PtHatBin[fl] << "processed Generated Events"<< Nev <<", Events:  " << tree->GetEntries() << ", Weight is " << weight[fl] << std::endl;
		//weight[fl]=1.;

		delete tree;
		f1->Close();
	}  

	cout << " Total number of events: " << Ntotal << endl;
	
	
	

	for(Int_t fl=1;fl<15;fl++)
	{  
		char input_directory[300];
		strcpy(input_directory,"/eos/cms/store/user/dkarasav/QCD_Autumn18_JEC18/Pt_");
		strcat(input_directory,PtHatBin[fl]);
		char file_name[200];
		sprintf(file_name,"_QCD_TuneCP5_13TeV_pythia8_Autumn18_reduced_skim.root");
		strcat(input_directory,file_name);
		f1 = TFile::Open(input_directory,"READ");
		tree = (TTree*)f1->Get("rootTupleTree/tree");
		



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
		tree->SetBranchAddress("pTWJ_j1",&ptWJ_j1);
		tree->SetBranchAddress("pTWJ_j2",&ptWJ_j2);
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
		tree->SetBranchAddress("run",&run);
		tree->SetBranchAddress("event",&event);	
		tree->SetBranchAddress("lumi",&lumin);

		Int_t nentries=(Int_t)tree->GetEntries(); 
		cout << "Now proccessing pT bin : " << PtHatBin[fl] <<  "Number of entries =  "<< nentries << endl ;
   

		for (int i=0; i<nentries; i++)    //event loop
	//    for (int i=0; i<1000; i++)    //event loop
		{

		
		   tree->GetEntry(i);
		   if (i%5000000==0) cout << " Reached entry: "<< i<<"\n";
		  // if(chf!=0 || nhf!=0 || cemf!=0 || nemf!=0 || muf!=0 || chf_j2!=0 || nhf_j2!=0 || cemf_j2!=0 || nemf_j2!=0 || muf_j2!=0){  
		   //this is necessary becasue the analyzer, when an event doesn't pass the cuts, fills all the variables with 0
		  // if(met_ov_sumet<0.5 && mjj>mcut_low && mjj<14000 && ptWJ_j2<6500 && ptWJ_j1<6500 ){
		   if( mjj>mcut_low && mjj<14000 && ptWJ_j2<6500 && ptWJ_j1<6500 )
			{
		       
				w = weight[fl];
				strcpy(pTbin,PtHatBin[fl]);
				t1.Fill();
		
		    } //end of Delta Eta, mjj, pt cut
		                                                     	//}//end of if, necessary from analyzer   
		}// end of event loop

	delete tree;
	f1->Close();
	} //end of loop on pt Hat bins

	cout << "loop finished! "<< endl;

	fout->cd();

	t1.Write();

	fout->Close();


}
