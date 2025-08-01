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

void Create_YAML_CrossSectionLimits(double width, double alpha_true){

char width_name[1024];
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

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

char input_name[1024], output_name[1024];
sprintf(input_name,"inputs/AsymptPlusHNLimitVsMass_alpha%s_W-%s.root", alpha_true_name, width_name);
TFile *f = new TFile(input_name,"READ");

TGraph *obs = (TGraph*)f->Get("obs_qq_pfdijetrun2");
TGraph *exp = (TGraph*)f->Get("exp_qq_pfdijetrun2");
TGraphAsymmErrors *unc_1s = (TGraphAsymmErrors*)f->Get("exp1sigma_qq_pfdijetrun2");
TGraphAsymmErrors *unc_2s = (TGraphAsymmErrors*)f->Get("exp2sigma_qq_pfdijetrun2");
TGraph *diqSuu = (TGraph*)f->Get("DiquarkSuu");
TGraph *diqSdd = (TGraph*)f->Get("DiquarkSddCorrWithPartonLevelAcc");

ofstream yaml_file;
sprintf(output_name,"outputs/Figure_009_XSEC_Limits_AlphaTrue%s_W-%s.yaml", alpha_true_name, width_name);
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

//------------------- Observed -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL observed limits on $\\sigma\\mathcal{B}\\it{A}$" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<obs->GetN(); i++)
{
	double x,y;
	obs->GetPoint(i,x,y);
	yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}

//------------------- Expected -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL expected limits on $\\sigma\\mathcal{B}\\it{A}$" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<exp->GetN(); i++)
{
	double x, y;
	exp->GetPoint(i,x,y);
	yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
	yaml_file << "    errors:" << endl;
        yaml_file << "    - label: \"1 s.d.\"" << endl;
        yaml_file << "      asymerror:" << endl;
        yaml_file << "        plus: " << std::fixed << std::setprecision(10) << unc_1s->GetErrorYhigh(i) << endl;
        yaml_file << "        minus: -" << std::fixed << std::setprecision(10) << unc_1s->GetErrorYlow(i) << endl;
        yaml_file << "    - label: \"2 s.d.\"" << endl;
        yaml_file << "      asymerror:" << endl;
        yaml_file << "        plus: " << std::fixed << std::setprecision(10) << unc_2s->GetErrorYhigh(i) << endl;
        yaml_file << "        minus: -" << std::fixed << std::setprecision(10) << unc_2s->GetErrorYlow(i) << endl;
}

//------------------- Diquarks -------------------

yaml_file << "- header:" << endl;
//yaml_file << "    name: $\\mathrm{uu} \\rightarrow \\mathrm{S}_{\\mathrm{uu}} \\rightarrow \\chi\\chi \\rightarrow (\\mathrm{ug})(\\mathrm{ug})$" << endl;
yaml_file << "    name: Cross section of $\\mathrm{S}_{\\mathrm{uu}}$ diquark" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int mass=2000; mass<=10000; mass=mass+100)
{
	double x,y;
	bool flag = false;
	for(int i=0; i<diqSuu->GetN(); i++)
	{
		diqSuu->GetPoint(i,x,y);
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


yaml_file << "- header:" << endl;
//yaml_file << "    name: $\\mathrm{dd} \\rightarrow \\mathrm{S}_{\\mathrm{dd}} \\rightarrow \\omega\\omega \\rightarrow (\\mathrm{dg})(\\mathrm{dg})$" << endl;
yaml_file << "    name: Cross section of $\\mathrm{S}_{\\mathrm{dd}}$ diquark" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int mass=2000; mass<=10000; mass=mass+100)
{
        double x,y;
        bool flag = false;
        for(int i=0; i<diqSdd->GetN(); i++)
        {
                diqSdd->GetPoint(i,x,y);
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
