//#include "calculate_coupling_crossing.h"
//#include <iostream>
//#include <iomanip>
//#include <fstream>
//#include "stdio.h"
//#include "stdlib.h"
//#include "iostream"



#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TColor.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TLegend.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TGraph2D.h"
#include "TGraph.h"
#include "TPaletteAxis.h"
#include "iostream"
#include "math.h"
//#include "CMS_lumi.h"
#include "stdio.h"
#include "stdlib.h"
#include <fstream>   
#include "TMath.h" 
#include <iostream>
#include <iomanip>

//root -l
// .x Produce_coupling_txt.C > coupling_output.txt
//using namespace std;
double calculate_coupling_crossing(string inputFileName,double zm,int arg3);
void Produce_coupling_txt()
{
//	gSystem->Load("calculate_coupling_crossing_Ratio_Method_higher_widths_C.so");
//	std::ofstream οutput("test.txt",ios::out);

	ofstream οutput;
	οutput.open("coupling_output.txt");
	cout.precision(6);


	for (int zm=2700; zm<5100; zm=zm+100)
	{ 
		if(zm==1600) οutput <<"#Mass     obs     expPlus2    expPlus    exp    expMinus     expMinus2 ";
		οutput << std::fixed << std::setprecision(6) << zm << "\t" ; 
		οutput << std::fixed << std::setprecision(6) << calculate_coupling_crossing("xsecUL_Asymptotic_qq_PFDijet2017MC.root",zm,0)<<"\t";
		οutput << std::fixed << std::setprecision(6) << calculate_coupling_crossing("xsecUL_Asymptotic_qq_PFDijet2017MC.root",zm,1)<<"\t";
		οutput << std::fixed << std::setprecision(6) << calculate_coupling_crossing("xsecUL_Asymptotic_qq_PFDijet2017MC.root",zm,2)<<"\t";
		οutput << std::fixed << std::setprecision(6) << calculate_coupling_crossing("xsecUL_Asymptotic_qq_PFDijet2017MC.root",zm,3)<<"\t";
		οutput << std::fixed << std::setprecision(6) << calculate_coupling_crossing("xsecUL_Asymptotic_qq_PFDijet2017MC.root",zm,4)<<"\t";
		οutput << std::fixed << std::setprecision(6) << calculate_coupling_crossing("xsecUL_Asymptotic_qq_PFDijet2017MC.root",zm,5)<<"\t";
		οutput << std::fixed << std::setprecision(6) << "\n" ;  
	}

	οutput.close();

}

double calculate_coupling_crossing(string inputFileName,double zm,int arg3)
{
  
	gROOT->SetBatch(kTRUE);
  //setTDRStyle();

  // Set the color palette
	bool useNicksPalette = true;
	int ncontours        = 999;

	if (useNicksPalette)
	{    
		TColor::InitializeColors();
		Double_t stops[9] = { 0.0000, 0.1250, 0.2500, 0.3750, 0.5000, 0.6250, 0.7500, 0.8750, 1.0000};
		Double_t red[9]   = { 243./255., 243./255., 240./255., 240./255., 241./255., 239./255., 1150./255., 151./255., 129./255.};
		Double_t green[9] = {   0./255.,  46./255.,  99./255., 149./255., 194./255., 220./255., 183./255., 166./255., 147./255.};
		Double_t blue[9]  = {   6./255.,   8./255.,  36./255.,  91./255., 169./255., 235./255., 246./255., 240./255., 233./255.};
		TColor::CreateGradientColorTable(9, stops, red, green, blue, ncontours);
	}
	else gStyle->SetPalette(70);  
	gStyle->SetNumberContours(ncontours);
 
	TGraph* grXsec = new TGraph();
	TGraph* grobs = new TGraph();
	TGraph* grexp = new TGraph();
	TGraph* grexp_1sigma_up   = new TGraphErrors();
	TGraph* grexp_2sigma_up   = new TGraphErrors();
	TGraph* grexp_1sigma_dw   = new TGraphErrors();
	TGraph* grexp_2sigma_dw   = new TGraphErrors();

	int expcounter          = 0;
	int exp_up_counter_1s   = 0;
	int exp_down_counter_1s = 0;
	int exp_up_counter_2s   = 0;
	int exp_down_counter_2s = 0;
	int obscounter          = 0;

	int medMin = 0;
	double medMax = 0.6;
	vector<int> medMassList;
 
  // This is where all the plots are made
//string width[]={"0p3","0p25","0p2","0p15","0p1","0p05","0p01"};
	string width[]={"0p01","0p05","0p1","0p15","0p2","0p25","0p3","0p35","0p4","0p45","0p5","0p55"};
//string width[]={"01percent","05percent","1percent","15percent","2percent","25percent","3percent"};
	double width_[]={0.01,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55};
//double width_[]={0.3,0.25,0.2,0.15,0.1,0.05,0.01};
	float width_limit[12][12];
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<12; j++)
		{
			width_limit[i][j]=0;
		}
	}

	for(int w=0; w<12; w++)
	{
//		string inputFileName1= "/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/Final_Results_EXO-19-012/Stiched_limits/Wide_resonances/limits/Spin_1/Correct_shapes/"+width[w]+"/"+inputFileName;
		string inputFileName1= "../../EXO_19-012/Wide_resonances/limits/qq_"+width[w]+"/"+inputFileName;
//  cout<<" file name = "<<inputFileName1<<endl;
		TFile *file = TFile::Open(inputFileName1.c_str(),"READ");
		TTree *tree = (TTree*)file->Get("xsecTree");
		double mass;
		double xsecULObs_PFDijet2016;
		double xsecULExpPlus2_PFDijet2016;
		double xsecULExpPlus_PFDijet2016;
		double xsecULExp_PFDijet2016;
		double xsecULExpMinus_PFDijet2016;
		double xsecULExpMinus2_PFDijet2016;
		tree->SetBranchAddress("mass", &mass);
		tree->SetBranchAddress("xsecULObs_PFDijet2017MC", &xsecULObs_PFDijet2016);
		tree->SetBranchAddress("xsecULExpPlus2_PFDijet2017MC", &xsecULExpPlus2_PFDijet2016);
		tree->SetBranchAddress("xsecULExpPlus_PFDijet2017MC", &xsecULExpPlus_PFDijet2016);
		tree->SetBranchAddress("xsecULExp_PFDijet2017MC", &xsecULExp_PFDijet2016);
		tree->SetBranchAddress("xsecULExpMinus_PFDijet2017MC", &xsecULExpMinus_PFDijet2016);
		tree->SetBranchAddress("xsecULExpMinus2_PFDijet2017MC", &xsecULExpMinus2_PFDijet2016);

		for (int i = 0; i < tree->GetEntries(); i++)
		{
			tree->GetEntry(i);    
			if (mass!=zm) continue;                    //with this : the loop is skipped when mass!=zm -- it is done only for mass==zm
			grexp->SetPoint(expcounter, double(width_[w]), xsecULExp_PFDijet2016);
			expcounter++;
			//cout<<"mass =" <<mass<<endl;
			//cout<<" X = "<<width_[w]<<" Y xsecULObs ="<<xsecULObs_PFDijet2016<<endl;
			//cout<<" X = "<<width_[w]<<" Y xsecULExpplus2 ="<<xsecULExpPlus2_PFDijet2016 << endl;
			//cout<<" X = "<<width_[w]<<" Y xsecULExpPlus "<<xsecULExpPlus_PFDijet2016<<endl;
			//cout<<" X = "<<width_[w]<<" Y xsecULExp ="<<xsecULExp_PFDijet2016<<endl;	
			//cout<<" X = "<<width_[w]<<" Y xsecULExpMinus ="<<xsecULExpMinus_PFDijet2016<<endl;
			//cout<<" X = "<<width_[w]<<" Y xsecULExpMinus2 ="<<xsecULExpMinus2_PFDijet2016<<endl;
			width_limit[w][0]=xsecULObs_PFDijet2016;
			width_limit[w][1]=xsecULExpPlus2_PFDijet2016;
			width_limit[w][2]=xsecULExpPlus_PFDijet2016;
			width_limit[w][3]=xsecULExp_PFDijet2016;
			width_limit[w][4]=xsecULExpMinus_PFDijet2016;
			width_limit[w][5]=xsecULExpMinus2_PFDijet2016;
			medMassList.push_back(mass);

			grobs->SetPoint(obscounter, double(width_[w]),xsecULObs_PFDijet2016 );
			obscounter++;

			// 1 sigma dw
			grexp_1sigma_dw->SetPoint(exp_down_counter_1s, double(width_[w]),xsecULExpMinus_PFDijet2016 );      
			exp_down_counter_1s++;
			// 1 sigma up
			grexp_1sigma_up->SetPoint(exp_up_counter_1s, double(width_[w]),xsecULExpPlus_PFDijet2016 );      
			exp_up_counter_1s++;

			// 2 sigma dw
			grexp_2sigma_dw->SetPoint(exp_down_counter_2s, double(width_[w]),xsecULExpMinus2_PFDijet2016 );      
			exp_down_counter_2s++;
			// 2 sigma up
			grexp_2sigma_up->SetPoint(exp_up_counter_2s, double(width_[w]),xsecULExpPlus2_PFDijet2016 );      
			exp_up_counter_2s++;

		}
  
		tree->ResetBranchAddresses();
		file->Close();
//		delete tree;
//		delete file;
	}

// until here it has created the +-1,2 sigma bands 
 

	ifstream input_1 ("../../inputs/DMV_DM1_WithoutMjjCut_delta-eta_LT_1p1_v2_InterpolationAdded.txt"); 
	if (input_1.fail())
	{ 
		cout << " file: ../../inputs/DMV_DM1_WithoutMjjCut_delta-eta_LT_1p1_v2_InterpolationAdded.txt not found." << endl;
		exit(1);
	}
  
	int zMass = 0; double xsec=0.;  double widthF=0.; double coup=0.; double cutXsec=0; int evnt=0; int evntCut=0;
	int j=0;
	int k=-1;
	double arCoup[12];
	double arXsec[12];
	double arCutXsec[12];
	double arWidthF[12];
	double arWidthF_over_zm[12];

	for (int s=0; s<12; ++s)
	{   //this loop initializes the values for the arrays defined above
		arCoup[s]=0;
		arXsec[s]=0;
		arCutXsec[s]=0;
		arWidthF[s]=0;
		arWidthF_over_zm[s]=0;
  
	}


	ifstream input_kFactor ("../../inputs/DM_k_factor_v3.txt"); 
	if (input_kFactor.fail())
	{ 
		cout << "file: ../../inputs/DM_k_factor_v3.txt not found.  " << endl;
		exit(1);
	}
  
	double kFactor = 0; 
	int kFactor_mass = 0;
	double arkFactor[250];
	int arkFactor_mass[250];
	
	for (int jj=0; jj<250; jj++) //initialazing arrays for k factors
	{
		arkFactor[jj] = 0.;
		arkFactor_mass[jj] = 0;
	}

	j=0;

	while (!input_kFactor.eof()) //reading file with k factors
	{
		
		input_kFactor >> kFactor_mass >> kFactor ;
//		cout << " mass = " <<kFactor_mass << "  factor "<<  kFactor <<endl;
		if (!input_kFactor.fail())
		{
			arkFactor[j]= kFactor;
			arkFactor_mass[j]= kFactor_mass;
//			cout << " Mass = " << arkFactor_mass[j]  << "   kFactor = " << arkFactor[j]<< " j " << j << endl;
			j++;
		}
	}

//REading txt file with theory xsec & coupling values.
	double k_factor_correction = 1.;
	j=0;
	while (!input_1.eof())
	{  
	    input_1 >> zMass >> xsec >> widthF >> coup >> cutXsec >> evnt >>evntCut ;    //reads the txt file with the theory points
		for (int jj=0; jj<250; jj++)
		{

		//	cout << zMass << "    "  <<arkFactor_mass[jj]<< endl;
			if ( zMass==arkFactor_mass[jj] )
			{
				k_factor_correction = arkFactor[jj] ;
			}
		}
  //		  cout << " z Mass  " << zMass << " xsec " << xsec << endl;
 // //		cout << " zMass = " << zMass<< "   k factor = " << k_factor_correction <<  endl;
    	if (!input_1.fail())
		{    
			k++;
		    if( zMass==zm)   //for the lines of the input .txt that have the correct zMass it saves the values in the corresponding arrays
			{
				arCoup[j]=coup;
				arXsec[j]=k_factor_correction*xsec;
				arCutXsec[j]=k_factor_correction*cutXsec;
				arWidthF[j]=widthF;
				arWidthF_over_zm[j] = widthF/zm;
		//		cout << " gq = " << arCoup[j] << "  Xsec = " << arXsec[j] << "  XsecCut = " << arCutXsec[j] << "  Width = " << arWidthF[j] << "  G/M = " << arWidthF_over_zm[j] << endl;
				j++;
//				cout << " gq = " << arCoup[j] << "  Xsec = " << arXsec[j] << "  XsecCut = " << arCutXsec[j] << "  Width = " << arWidthF[j] << "  G/M = " << arWidthF_over_zm[j] << endl;
			}
		}
   
	}

  
	//sorted g_q coupling constant from 0.1 to 1     
	for (int kk=0; kk<12; ++kk)                    //these "for" just sort the "theory" arrays from low coupling to bigger
	{
    	for (int nn=kk+1; nn<12; ++nn)
		{
			//if(arCoup[nn]<arCoup[kk] && arCoup[nn]!=0)
			//cout << arCutXsec[nn] <<  arCutXsec[kk] << endl;
        	if(arCoup[nn]<arCoup[kk] )
			{
				double c=arCoup[kk];
				double x=arXsec[kk];
				double cutx=arCutXsec[kk];
				double ww=arWidthF[kk];
				double yy=arWidthF_over_zm[kk];
				arCoup[kk]=arCoup[nn];
				arCoup[nn]=c;
				arXsec[kk]=arXsec[nn];
				arCutXsec[kk]=arCutXsec[nn];
				arXsec[nn]=x;
				arCutXsec[nn]=cutx;
				arWidthF[kk]=arWidthF[nn];
				arWidthF[nn]=ww;
				arWidthF_over_zm[kk]=arWidthF_over_zm[nn];
				arWidthF_over_zm[nn]=yy;
		//		cout << arCutXsec[nn] << endl;
			}
		}
	}
  
     // seted xsec acording to q_q
	for (int tt=0; tt<12; ++tt)
	{
		if (arCutXsec[tt]!=0) grXsec->SetPoint(tt,arWidthF[tt]/zm , arCutXsec[tt]);
	//	cout <<" arcopling ="<<arCoup[tt]<<" X ="<<arWidthF[tt]/zm <<" xsec Y ="<<arCutXsec[tt]<<endl;
	} 
  

    
	double x1=0, y1=0, x2=0, y2=0;
    double x_min=0, y_min=0 ;
    long double d=0 ,d_ini=0, d_fin=0;
    double intersection_X=0, intersection_Y=0;
    long double d_min=100;
    double x_1=0, y_1=0;
    //std::cout << " Program to find the intersecting point of two lines:\n";
    
    TGraph* grExperimental = new TGraph();
  

    if (arg3==0) grExperimental = (TGraph*)grobs->Clone();
    if (arg3==1) grExperimental = (TGraph*)grexp_2sigma_up->Clone();
    if (arg3==2) grExperimental = (TGraph*)grexp_1sigma_up->Clone();
    if (arg3==3) grExperimental = (TGraph*)grexp->Clone();
    if (arg3==4) grExperimental = (TGraph*)grexp_1sigma_dw->Clone();
    if (arg3==5) grExperimental = (TGraph*)grexp_2sigma_dw->Clone();

	TGraph *grCoupling_vs_width = new TGraph(11,arWidthF_over_zm,arCoup);


	for (int i=0; i<10000; i++)
	{

		if (d_min < 0.0001) continue;

		x1= 0.01 + 0.0001*(i+1)*0.59;
		x2= 0.01 + 0.0001*(i+1)*0.59;
     //grobs->SetBit(grobs->kIsSortedX);       // this is to declare that the Graph is sorted in X axis ( makes the Eval (interpolation ) command faster)
     //grXsec->SetBit(grXsec->kIsSortedX);
		y1=grExperimental->Eval(x1,0,"");        //interpolated y coordinate of experimental curve
		y2=grXsec->Eval(x2,0,"");       //interpolated y coordinate of theory curve  
		d = sqrt ( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
		if(i==0) d_ini = d;  //saving the initial distance to check for correct minimization
		if(i==9999) d_fin=d; //saving the final distance to check for correct minimization
		if (d < 0.0001 ) d_min = d;
		if (d < d_min)
		{ 
			d_min = d;
			x_min = x1;
			y_min = y1;    
//	cout << "G/M = "<<  x1 <<"   d_min = "<<d_min << endl;        
		}

//	cout << "x"<<d_min << endl;
	}    
	intersection_X = x_min;
	intersection_Y = y_min;

	//	cout << intersection_X << endl;
       
	double final_coupling = grCoupling_vs_width->Eval(x_min,0,"");
	//std::cout << " final coupling value ="<< final_coupling <<std::endl;
	//std::cout << std::fixed;
	//std::cout << std::setprecision(6);
	std::cout << std::setprecision(6) << std::fixed;
	if(d_min!=d_ini && d_min!=d_fin && d_min<0.005) std::cout <<  final_coupling<< "   ";
	else   std::cout << "  2.500000  "; // if no crossing found, set a large limit value in order to make the plot.
        
	if(d_min!=d_ini && d_min!=d_fin && d_min<0.005) return final_coupling;
	else   return  2.500000; // if no crossing found, set a large limit value in order to make the plot.


	//return final_coupling; 

	delete grXsec;
	delete grobs;
	delete grexp;
	delete grexp_1sigma_up;
	delete grexp_2sigma_up;
	delete grexp_1sigma_dw;
	delete grexp_2sigma_dw;
	delete grExperimental;
	delete grCoupling_vs_width;

/*
	if (arg3==0) delete grobs;
    if (arg3==1) delete grexp_2sigma_up;
    if (arg3==2) delete grexp_1sigma_up;
    if (arg3==3) delete grexp;
    if (arg3==4) delete grexp_1sigma_dw;
    if (arg3==5) delete grexp_2sigma_dw;
*/


}


