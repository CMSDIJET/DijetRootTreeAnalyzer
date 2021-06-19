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


	//xsecUL_Asymptotic_gg_PFDijet2017MC.root

void Stitch_limits(){

	double method_change_mass = 3000.;

	
	double mass_SF, xsecUL0_SF, xsecUL1_SF,	xsecUL2_SF, xsecUL3_SF, xsecUL4_SF, xsecUL5_SF;	
	double mass_RM, xsecUL0_RM, xsecUL1_RM,	xsecUL2_RM, xsecUL3_RM, xsecUL4_RM, xsecUL5_RM;	
	double mass_Combined, xsecUL0_Combined, xsecUL1_Combined, xsecUL2_Combined, xsecUL3_Combined, xsecUL4_Combined, xsecUL5_Combined;
	
	
	char *limits1_directory = "Fit_method_results/limits/";       	 //directory with Standard Fit limits
	char *limits2_directory = "Ratio_method_results/limits/";  		 //directory with Ratio Method limits	
	char *combined_directory ="Stiched_results/limits/" ;
//	char *combined_directory ="deleteme/" ;
	char *resonance = "qq";          // give the resonance type 

	cout << " Output directory: " << combined_directory << endl;

	int year = 2017;
	char box1[300], box2[300];

		if      ( year == 2016)
		{
			strcpy(box1,"_PFDijet2016");
			strcpy(box2,"_PFDijet2016MC");
		}
		else if ( year == 2017)
		{
			strcpy(box1,"_PFDijet2017");
			strcpy(box2,"_PFDijet2017MC");
		}
	//output directory
	char output_directory[300];
	strcpy(output_directory,"/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/");
	strcat(output_directory,combined_directory);
	strcat(output_directory,"xsecUL_Asymptotic_");
    strcat(output_directory,resonance);
	strcat(output_directory,box2);	
	strcat(output_directory,".root");

	//full path until the 1st limit file   //Standard Fit limit file
	char input1_directory[300];
	strcpy(input1_directory,"/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/");
	strcat(input1_directory,limits1_directory);
	strcat(input1_directory,"xsecUL_Asymptotic_");
    strcat(input1_directory,resonance);
	strcat(input1_directory,box1);				
	strcat(input1_directory,".root");

	//full path until the 2nd limit file
	char input2_directory[300];
	strcpy(input2_directory,"/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/");
	strcat(input2_directory,limits2_directory);
	strcat(input2_directory,"xsecUL_Asymptotic_");
    strcat(input2_directory,resonance);
	strcat(input2_directory,box2);	
	strcat(input2_directory,".root");

	cout <<" hi " << endl;

////////////////////////creating strings to define and read branches dynamically///////////////////////////

	//Standard Fit tree with no 'MC' on box
	char xsecObs[100];
	strcpy(xsecObs,"xsecULObs");
	strcat(xsecObs,box1);

	char xsecExpPlus2[100];
	strcpy(xsecExpPlus2,"xsecULExpPlus2");
	strcat(xsecExpPlus2,box1);

	char xsecExpPlus[100];
	strcpy(xsecExpPlus,"xsecULExpPlus");
	strcat(xsecExpPlus,box1);

	char xsecExp[100];
	strcpy(xsecExp,"xsecULExp");
	strcat(xsecExp,box1);

	char xsecExpMinus[100];
	strcpy(xsecExpMinus,"xsecULExpMinus");
	strcat(xsecExpMinus,box1);

	char xsecExpMinus2[100];
	strcpy(xsecExpMinus2,"xsecULExpMinus2");
	strcat(xsecExpMinus2,box1);

	//Ratio Method tree with MC on box
	char xsecObsMC[100];
	strcpy(xsecObsMC,"xsecULObs");
	strcat(xsecObsMC,box2);

	char xsecExpPlus2MC[100];
	strcpy(xsecExpPlus2MC,"xsecULExpPlus2");
	strcat(xsecExpPlus2MC,box2);

	char xsecExpPlusMC[100];
	strcpy(xsecExpPlusMC,"xsecULExpPlus");
	strcat(xsecExpPlusMC,box2);

	char xsecExpMC[100];
	strcpy(xsecExpMC,"xsecULExp");
	strcat(xsecExpMC,box2);

	char xsecExpMinusMC[100];
	strcpy(xsecExpMinusMC,"xsecULExpMinus");
	strcat(xsecExpMinusMC,box2);

	char xsecExpMinus2MC[100];
	strcpy(xsecExpMinus2MC,"xsecULExpMinus2");
	strcat(xsecExpMinus2MC,box2);


//////creating strings with "/D" on end//////////////////////////
	char xsecObsD[100];
	strcpy(xsecObsD,"xsecULObs");
	strcat(xsecObsD,box2);
	strcat(xsecObsD,"/D");

	char xsecExpPlus2D[100];
	strcpy(xsecExpPlus2D,"xsecULExpPlus2");
	strcat(xsecExpPlus2D,box2);
	strcat(xsecExpPlus2D,"/D");

	char xsecExpPlusD[100];
	strcpy(xsecExpPlusD,"xsecULExpPlus");
	strcat(xsecExpPlusD,box2);
	strcat(xsecExpPlusD,"/D");

	char xsecExpD[100];
	strcpy(xsecExpD,"xsecULExp");
	strcat(xsecExpD,box2);
	strcat(xsecExpD,"/D");

	char xsecExpMinusD[100];
	strcpy(xsecExpMinusD,"xsecULExpMinus");
	strcat(xsecExpMinusD,box2);
	strcat(xsecExpMinusD,"/D");

	char xsecExpMinus2D[100];
	strcpy(xsecExpMinus2D,"xsecULExpMinus2");
	strcat(xsecExpMinus2D,box2);
	strcat(xsecExpMinus2D,"/D");


	TFile *fout;
	fout=new TFile(output_directory,"recreate");                                 //CREATING NEW TREE
	TTree xsecTree("xsecTree","tree");
	xsecTree.Branch("mass",&mass_Combined,"mass/D");
	xsecTree.Branch(xsecObsMC,&xsecUL0_Combined,xsecObsD);    //obs_limits
	xsecTree.Branch(xsecExpPlus2MC,&xsecUL1_Combined,xsecExpPlus2D);    //exp +2s limit
	xsecTree.Branch(xsecExpPlusMC,&xsecUL2_Combined,xsecExpPlusD);    //exp +1s limit
	xsecTree.Branch(xsecExpMC,&xsecUL3_Combined,xsecExpD);    //exp limit
	xsecTree.Branch(xsecExpMinusMC,&xsecUL4_Combined,xsecExpMinusD);    //exp -1s limit
	xsecTree.Branch(xsecExpMinus2MC,&xsecUL5_Combined,xsecExpMinus2D);    //exp -2s limit

		cout <<" hi " << endl;

	TFile *f1 = new TFile(input1_directory);       //Standard Fit limit file
	TTree * tree1 = (TTree*) f1->Get("xsecTree");
	tree1->SetBranchAddress("mass",&mass_SF);
	tree1->SetBranchAddress(xsecObs,&xsecUL0_SF);
	tree1->SetBranchAddress(xsecExpPlus2,&xsecUL1_SF);
	tree1->SetBranchAddress(xsecExpPlus,&xsecUL2_SF);
	tree1->SetBranchAddress(xsecExp,&xsecUL3_SF);
	tree1->SetBranchAddress(xsecExpMinus,&xsecUL4_SF);
	tree1->SetBranchAddress(xsecExpMinus2,&xsecUL5_SF);

	cout <<" hi " << endl;

	TFile *f2 = new TFile(input2_directory);       //Ratio Method limit file
	TTree * tree2 = (TTree*) f2->Get("xsecTree");
	tree2->SetBranchAddress("mass",&mass_RM);
	tree2->SetBranchAddress(xsecObsMC,&xsecUL0_RM);
	tree2->SetBranchAddress(xsecExpPlus2MC,&xsecUL1_RM);
	tree2->SetBranchAddress(xsecExpPlusMC,&xsecUL2_RM);
	tree2->SetBranchAddress(xsecExpMC,&xsecUL3_RM);
	tree2->SetBranchAddress(xsecExpMinusMC,&xsecUL4_RM);
	tree2->SetBranchAddress(xsecExpMinus2MC,&xsecUL5_RM);

		cout <<" hi " << endl;

	int nentries1=(Int_t)tree1->GetEntries(); 
	int nentries2=(Int_t)tree2->GetEntries(); 

	cout << "n1 "<<nentries1 <<"   n2 "<<nentries2 << endl;
 
	for (int i=0; i<nentries1+1; i++) //event loop
	 {    
		if (i<=fabs(nentries1-nentries2)) 
		 {
			tree1->GetEntry(i);
			mass_Combined    = mass_SF;
			xsecUL0_Combined = xsecUL0_SF;
			xsecUL1_Combined = xsecUL1_SF;
			xsecUL2_Combined = xsecUL2_SF;
			xsecUL3_Combined = xsecUL3_SF;
			xsecUL4_Combined = xsecUL4_SF;
			xsecUL5_Combined = xsecUL5_SF;
			cout << "  mass SF = " << mass_SF << "  mass RM = " << mass_RM<< endl;
		 }
		else 
		 {
			tree1->GetEntry(i);
			tree2->GetEntry(i-fabs(nentries1-nentries2)-1);
			cout << "  mass SF = " << mass_SF << "  mass RM = " << mass_RM<< endl;
			if (mass_SF < method_change_mass)  
			 {
				mass_Combined    = mass_SF;
				xsecUL0_Combined = xsecUL0_SF;
				xsecUL1_Combined = xsecUL1_SF;
				xsecUL2_Combined = xsecUL2_SF;
				xsecUL3_Combined = xsecUL3_SF;
				xsecUL4_Combined = xsecUL4_SF;
				xsecUL5_Combined = xsecUL5_SF;
			 }
			else 
			 {
				mass_Combined    = mass_RM;
				xsecUL0_Combined = xsecUL0_RM;
				xsecUL1_Combined = xsecUL1_RM;
				xsecUL2_Combined = xsecUL2_RM;
				xsecUL3_Combined = xsecUL3_RM;
				xsecUL4_Combined = xsecUL4_RM;
				xsecUL5_Combined = xsecUL5_RM;
			 }
		 }
	//	cout << " mass = " << mass_Combined << "  exp = " << xsecUL3_Combined << " obs = " << xsecUL0_Combined << endl; 
		xsecTree.Fill();
     }// end of event loop

	cout<<" Method change happened on mass " <<   method_change_mass << " GeV "<<endl;
	fout->cd();
	xsecTree.Write();
	fout->Close();
}
