#include "../include_functions.h"
//#include "TSpline3.h"


void Interpolate_DM_theoretical_values(double Coupling)
{
	

	int zMass = 0; double xsec=0.;  double widthF=0.; double coup=0.; double cutXsec=0; int evnt=0; int evntCut=0;

	ifstream input_1 ("/afs/cern.ch/work/d/dkarasav/public/Javier_limits/CMSSW_8_1_0/src/CMSDIJET/DijetRootTreeAnalyzer/C_scripts/WideDijetResonance/DMV_DM1_WithoutMjjCut_delta-eta_LT_1p1_v2.txt");
 //FILE *input_1 = fopen("/afs/cern.ch/work/d/dkarasav/public/limit_code_new/CMSSW_7_4_14/src/CMSDIJET/DijetRootTreeAnalyzer/Yulcin/WideDijetResonance/DMV_DM1_WithoutMjjCut.txt","r");
 
	if (input_1.fail())
	{
		exit(1);
	}
/*
	int zMass_ar[350];

	for (int i=0; i<350; i++)
	{
		zMass_ar[i]=-1;
	}
	*/
	bool flag_written;
	int k=0;


	double zMass_per500GeV[15];

	double xSec_ar_per500GeV[15];
	double cutxSec_ar_per500GeV[15];
	double widthF_ar_per500GeV[15];
	double coup_ar_per500GeV[15];
	int evnt_ar_per500GeV[15];
	int evntCut_ar_per500GeV[15];

	int jj =0;
	while (!input_1.eof())
	{

		input_1 >> zMass >> xsec >> widthF >> coup >> cutXsec >> evnt >>evntCut ;    //reads the txt file with the theory points
//		cout << zMass<< endl;
  // counting how many different masses there are in the .txt and filling the zMass_ar
//		flag_written = false;
/*
		int j=0;
		for (j=0; j<350; j++)
		{

	//		if ( zMass>3900 ) cout << zMass << zMass_ar[j];
			if (zMass_ar[j] == zMass)
			{
				flag_written=true;
			}
			if (flag_written==true) continue;
		}

		if (flag_written==false)
		{
			zMass_ar[k]=zMass;
			//if( zMass!=-1 ) cout << zMass_ar[k]<<  endl;
			k++;
		}
		*/
		if ( coup == Coupling && ( zMass == 1000 || zMass == 1500 || zMass == 2000 || zMass == 2500 || zMass == 3000 || zMass == 3500 || zMass == 4000 || zMass == 4500 || zMass == 5000 || zMass == 5500 || zMass == 6000 || zMass == 6500 || zMass == 7000 || zMass == 7500 || zMass == 8000 ) )
		{
	//		cout << "hi" << endl;
			xSec_ar_per500GeV[jj] = xsec;
			cutxSec_ar_per500GeV[jj] = cutXsec;
			zMass_per500GeV[jj]=1.0* zMass;
			widthF_ar_per500GeV[jj] = widthF;
			coup_ar_per500GeV[jj] = coup;
			evnt_ar_per500GeV[jj] = evnt;
			evntCut_ar_per500GeV[jj] = evntCut;
//			cout << zMass_per500GeV[jj] <<"   "<<xSec_ar_per500GeV[jj] <<"   "<< cutxSec_ar_per500GeV[jj] <<"   "<< endl;
			jj++;
		}

	

	}

			//sorted g_q coupling constant from 0.1 to 1     
	for (int kk=0; kk<15; kk++)                    //this for just sorts the "theory" arrays from low coupling to bigger
	{
    	for (int nn=kk+1; nn<15; nn++)
		{
                       // if(arCoup[nn]<arCoup[kk] && arCoup[nn]!=0)
	//		cout << arCutXsec[nn] <<  arCutXsec[kk] << endl;
        	if(zMass_per500GeV[nn] < zMass_per500GeV[kk] )
			{

				double c=xSec_ar_per500GeV[kk];
				double cutx=cutxSec_ar_per500GeV[kk];
				double m = zMass_per500GeV[kk];
				double w = widthF_ar_per500GeV[kk];
				double gq = coup_ar_per500GeV[kk];
				int N    = evnt_ar_per500GeV[kk];
				int Nc    = evntCut_ar_per500GeV[kk];

				widthF_ar_per500GeV[kk]=widthF_ar_per500GeV[nn];
				widthF_ar_per500GeV[nn]=w;

				coup_ar_per500GeV[kk]=coup_ar_per500GeV[nn];
				coup_ar_per500GeV[nn]=gq;

				evnt_ar_per500GeV[kk]=evnt_ar_per500GeV[nn];
				evnt_ar_per500GeV[nn]=N;

				evntCut_ar_per500GeV[kk]=evntCut_ar_per500GeV[nn];
				evntCut_ar_per500GeV[nn]=Nc;

				zMass_per500GeV[kk]=zMass_per500GeV[nn];
				zMass_per500GeV[nn]=m;

				xSec_ar_per500GeV[kk]=xSec_ar_per500GeV[nn];
				xSec_ar_per500GeV[nn]=c;

				cutxSec_ar_per500GeV[kk]=cutxSec_ar_per500GeV[nn];

				cutxSec_ar_per500GeV[nn]=cutx;
				
		//		cout << cutxSec_ar_per500GeV[nn] << endl;
			}
		}

	}
	
	TGraph *gr_xsec = new TGraph(15, zMass_per500GeV, xSec_ar_per500GeV);
	TSpline3 *spline_xsec = new TSpline3("spline_xsec",gr_xsec);

	TGraph *gr_cutXsec = new TGraph(15, zMass_per500GeV, cutxSec_ar_per500GeV);
	TSpline3 *spline_cutXsec = new TSpline3("spline_cutXsec",gr_cutXsec);

	TGraph *gr_widthF = new TGraph(15, zMass_per500GeV, widthF_ar_per500GeV);
	TSpline3 *spline_widthF = new TSpline3("spline_widthF",gr_widthF);

	for (int Med_Mass=5100; Med_Mass<=8000; Med_Mass+=100)
	{

		if ( Med_Mass%500== 0)continue;

		double Width =Med_Mass*(6*Coupling*Coupling/(4*3.141592653)+1/(12*3.141592653));
		cout << Med_Mass <<"\t"<< spline_xsec->Eval(Med_Mass) <<"\t"<< spline_widthF->Eval(Med_Mass) <<"\t"<< Coupling << "\t" <<spline_cutXsec->Eval(Med_Mass)<<"\t"<< 10000 <<"\t"<< 4000 << endl;
//		cout << Med_Mass <<"\t"<< spline_xsec->Eval(Med_Mass) <<"\t"<< Width <<"\t"<< Coupling << "\t" <<spline_cutXsec->Eval(Med_Mass)<<"\t"<< 10000 <<"\t"<< 4000 << endl;

//		cout << "\n" << endl;
	}




//	gr_xsec->Print();
//	gr_xsec->Draw();



//	cout << " Count = " << k;


}
