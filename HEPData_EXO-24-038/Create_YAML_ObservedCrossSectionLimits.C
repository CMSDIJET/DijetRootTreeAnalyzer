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
#include "TMath.h"
#include "TLatex.h"

void Create_YAML_ObservedCrossSectionLimits(double alpha_true){

char alpha_true_name[1024];
if (alpha_true==0.11) sprintf(alpha_true_name,"0p11");
if (alpha_true==0.13) sprintf(alpha_true_name,"0p13");
if (alpha_true==0.15) sprintf(alpha_true_name,"0p15");
if (alpha_true==0.17) sprintf(alpha_true_name,"0p17");
if (alpha_true==0.19) sprintf(alpha_true_name,"0p19");
if (alpha_true==0.21) sprintf(alpha_true_name,"0p21");
if (alpha_true==0.23) sprintf(alpha_true_name,"0p23");
if (alpha_true==0.25) sprintf(alpha_true_name,"0p25");
if (alpha_true==0.27) sprintf(alpha_true_name,"0p27");
if (alpha_true==0.29) sprintf(alpha_true_name,"0p29");
if (alpha_true==0.31) sprintf(alpha_true_name,"0p31");
if (alpha_true==0.33) sprintf(alpha_true_name,"0p33");
if (alpha_true==0.42) sprintf(alpha_true_name,"0p42");

char input_name_W0p015[1024], input_name_W0p05[1024], input_name_W0p1[1024], output_name[1024];
sprintf(input_name_W0p015,"inputs/AsymptPlusHNLimitVsMass_alpha%s_W-0p015.root", alpha_true_name);
sprintf(input_name_W0p05,"inputs/AsymptPlusHNLimitVsMass_alpha%s_W-0p05.root", alpha_true_name);
sprintf(input_name_W0p1,"inputs/AsymptPlusHNLimitVsMass_alpha%s_W-0p1.root", alpha_true_name);
TFile *f_W0p015 = new TFile(input_name_W0p015,"READ");
TFile *f_W0p05 = new TFile(input_name_W0p05,"READ");
TFile *f_W0p1 = new TFile(input_name_W0p1,"READ");

TGraph *obs_W0p015 = (TGraph*)f_W0p015->Get("obs_qq_pfdijetrun2");
TGraph *obs_W0p05 = (TGraph*)f_W0p05->Get("obs_qq_pfdijetrun2");
TGraph *obs_W0p1 = (TGraph*)f_W0p1->Get("obs_qq_pfdijetrun2");

TGraph *diqSuu_W0p015 = (TGraph*)f_W0p015->Get("DiquarkSuu");
TGraph *diqSuu_W0p05 = (TGraph*)f_W0p05->Get("DiquarkSuu");
TGraph *diqSuu_W0p1 = (TGraph*)f_W0p1->Get("DiquarkSuu");

TGraph *diqSdd_W0p015 = (TGraph*)f_W0p015->Get("DiquarkSddCorrWithPartonLevelAcc");
TGraph *diqSdd_W0p05 = (TGraph*)f_W0p05->Get("DiquarkSddCorrWithPartonLevelAcc");
TGraph *diqSdd_W0p1 = (TGraph*)f_W0p1->Get("DiquarkSddCorrWithPartonLevelAcc");

TGraph *exp = (TGraph*)f_W0p015->Get("exp_qq_pfdijetrun2");

ofstream yaml_file;
sprintf(output_name,"outputs/Figure_010_XSEC_ObsLimits_AlphaTrue%s.yaml", alpha_true_name);
yaml_file.open(output_name);


//------------------- Resonance mass -------------------

yaml_file << "independent_variables:" << endl;

yaml_file << "- header:" << endl;
yaml_file << "    name: Four-jet resonance mass" << endl;
yaml_file << "    units: TeV" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<exp->GetN(); i++)
{
        double x,y;
        exp->GetPoint(i,x,y);
        yaml_file << "  - value: " << std::fixed << std::setprecision(1) << x/1000. << endl;
}



yaml_file << "dependent_variables:" << endl;

//------------------- Observed W-0p015 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL observed limits on $\\sigma\\mathcal{B}\\it{A}$ for $\\Gamma/M_{\\mathrm{Y}}$ = 1.5%" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<obs_W0p015->GetN(); i++)
{
	double x,y;
	obs_W0p015->GetPoint(i,x,y);
	yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}

//------------------- Observed W-0p05 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL observed limits on $\\sigma\\mathcal{B}\\it{A}$ for $\\Gamma/M_{\\mathrm{Y}}$ = 5%" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<obs_W0p05->GetN(); i++)
{
	double x,y;
	obs_W0p05->GetPoint(i,x,y);
	yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}

//------------------- Observed W-0p05 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL observed limits on $\\sigma\\mathcal{B}\\it{A}$ for $\\Gamma/M_{\\mathrm{Y}}$ = 10%" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<obs_W0p1->GetN(); i++)
{
	double x,y;
	obs_W0p1->GetPoint(i,x,y);
	yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}



//------------------- Diquark Suu W-0p015 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: $\\sigma\\mathcal{B}\\it{A}$ of $\\mathrm{S}_{\\mathrm{uu}}$ diquark with $\\Gamma/M_{\\mathrm{S}}$ = 1.5%" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int mass=2000; mass<=10000; mass=mass+100)
{
	double x,y;
	bool flag = false;
	for(int i=0; i<diqSuu_W0p015->GetN(); i++)
	{
		diqSuu_W0p015->GetPoint(i,x,y);
		if(x==mass) 
		{
			flag = true;
			break;
		}
	}

	if(flag==false)
	{
		yaml_file << "  - value: '-'" << endl;
	}
	else
	{
		yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
	}
}


//------------------- Diquark Suu W-0p05 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: $\\sigma\\mathcal{B}\\it{A}$ of $\\mathrm{S}_{\\mathrm{uu}}$ diquark with $\\Gamma/M_{\\mathrm{S}}$ = 5%" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int mass=2000; mass<=10000; mass=mass+100)
{
	double x,y;
	bool flag = false;
	for(int i=0; i<diqSuu_W0p05->GetN(); i++)
	{
		diqSuu_W0p05->GetPoint(i,x,y);
		if(x==mass) 
		{
			flag = true;
			break;
		}
	}

	if(flag==false)
	{
		yaml_file << "  - value: '-'" << endl;
	}
	else
	{
		yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
	}
}

//------------------- Diquark Suu W-0p1 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: $\\sigma\\mathcal{B}\\it{A}$ of $\\mathrm{S}_{\\mathrm{uu}}$ diquark with $\\Gamma/M_{\\mathrm{S}}$ = 10%" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int mass=2000; mass<=10000; mass=mass+100)
{
	double x,y;
	bool flag = false;
	for(int i=0; i<diqSuu_W0p1->GetN(); i++)
	{
		diqSuu_W0p1->GetPoint(i,x,y);
		if(x==mass) 
		{
			flag = true;
			break;
		}
	}

	if(flag==false)
	{
		yaml_file << "  - value: '-'" << endl;
	}
	else
	{
		yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
	}
}


//------------------- Diquark Sdd W-0p015 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: $\\sigma\\mathcal{B}\\it{A}$ of $\\mathrm{S}_{\\mathrm{dd}}$ diquark with $\\Gamma/M_{\\mathrm{S}}$ = 1.5%" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int mass=2000; mass<=10000; mass=mass+100)
{
	double x,y;
	bool flag = false;
	for(int i=0; i<diqSdd_W0p015->GetN(); i++)
	{
		diqSdd_W0p015->GetPoint(i,x,y);
		if(x==mass) 
		{
			flag = true;
			break;
		}
	}

	if(flag==false)
	{
		yaml_file << "  - value: '-'" << endl;
	}
	else
	{
		yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
	}
}

//------------------- Diquark Sdd W-0p05 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: $\\sigma\\mathcal{B}\\it{A}$ of $\\mathrm{S}_{\\mathrm{dd}}$ diquark with $\\Gamma/M_{\\mathrm{S}}$ = 5%" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int mass=2000; mass<=10000; mass=mass+100)
{
	double x,y;
	bool flag = false;
	for(int i=0; i<diqSdd_W0p05->GetN(); i++)
	{
		diqSdd_W0p05->GetPoint(i,x,y);
		if(x==mass) 
		{
			flag = true;
			break;
		}
	}

	if(flag==false)
	{
		yaml_file << "  - value: '-'" << endl;
	}
	else
	{
		yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
	}
}

//------------------- Diquark Sdd W-0p1 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: $\\sigma\\mathcal{B}\\it{A}$ of $\\mathrm{S}_{\\mathrm{dd}}$ diquark with $\\Gamma/M_{\\mathrm{S}}$ = 10%" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int mass=2000; mass<=10000; mass=mass+100)
{
	double x,y;
	bool flag = false;
	for(int i=0; i<diqSdd_W0p1->GetN(); i++)
	{
		diqSdd_W0p1->GetPoint(i,x,y);
		if(x==mass) 
		{
			flag = true;
			break;
		}
	}

	if(flag==false)
	{
		yaml_file << "  - value: '-'" << endl;
	}
	else
	{
		yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
	}
}





}
