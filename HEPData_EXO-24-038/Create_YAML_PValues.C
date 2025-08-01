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

void Create_YAML_PValues(double alpha_true){

char alpha_true_name[1024];
if (alpha_true==0.25) sprintf(alpha_true_name,"0p25");
if (alpha_true==0.29) sprintf(alpha_true_name,"0p29");

char input_name_W0p015[1024], input_name_W0p05[1024], input_name_W0p1[1024], output_name[1024];
sprintf(input_name_W0p015,"inputs/pvalue_qq_pfdijetrun2_alpha%s_W-0p015_AsymptPlusHN.root", alpha_true_name);
sprintf(input_name_W0p05,"inputs/pvalue_qq_pfdijetrun2_alpha%s_W-0p05_AsymptPlusHN.root", alpha_true_name);
sprintf(input_name_W0p1,"inputs/pvalue_qq_pfdijetrun2_alpha%s_W-0p1_AsymptPlusHN.root", alpha_true_name);
TFile *f_W0p015 = new TFile(input_name_W0p015,"READ");
TFile *f_W0p05 = new TFile(input_name_W0p05,"READ");
TFile *f_W0p1 = new TFile(input_name_W0p1,"READ");

TGraph *pvalues_W0p015 = (TGraph*)f_W0p015->Get("Graph");
TGraph *pvalues_W0p05 = (TGraph*)f_W0p05->Get("Graph");
TGraph *pvalues_W0p1 = (TGraph*)f_W0p1->Get("Graph");

ofstream yaml_file;
sprintf(output_name,"outputs/Figure_011_PValues_AlphaTrue%s.yaml", alpha_true_name);
yaml_file.open(output_name);


//------------------- Resonance mass -------------------

yaml_file << "independent_variables:" << endl;

yaml_file << "- header:" << endl;
yaml_file << "    name: Four-jet resonance mass" << endl;
yaml_file << "    units: TeV" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<pvalues_W0p015->GetN(); i++)
{
        double x,y;
        pvalues_W0p015->GetPoint(i,x,y);
        yaml_file << "  - value: " << std::fixed << std::setprecision(1) << x/1000. << endl;
}



yaml_file << "dependent_variables:" << endl;

//------------------- W-0p015 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: Local $p$-value for $\\Gamma/M_{\\mathrm{Y}}$ = 1.5%" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<pvalues_W0p015->GetN(); i++)
{
	double x,y;
	pvalues_W0p015->GetPoint(i,x,y);
	yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}

//------------------- W-0p05 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: Local $p$-value for $\\Gamma/M_{\\mathrm{Y}}$ = 5%" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<pvalues_W0p05->GetN(); i++)
{
	double x,y;
	pvalues_W0p05->GetPoint(i,x,y);
	yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}

//------------------- W-0p1 -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: Local $p$-value for $\\Gamma/M_{\\mathrm{Y}}$ = 10%" << endl;
yaml_file << "  values:" << endl;

for (int i=0; i<pvalues_W0p1->GetN(); i++)
{
	double x,y;
	pvalues_W0p1->GetPoint(i,x,y);
	yaml_file << "  - value: " << std::fixed << std::setprecision(10) << y << endl;
}



}
