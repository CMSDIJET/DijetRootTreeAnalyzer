#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Calculate_pseudosignificance_3600.C"
using namespace std;

void calculate_product_of_sigma_BR_acc_eff_SuuModel(double width, double alpha_true, double S) {

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

char fname[1024];
sprintf(fname, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/gridpacks/Suu_Diquark/Wide_Resonances_13TeV/full_grid/log/Suu_Diquark_13TeV_W-%s_S%.0f_chi%.0f.log", width_name, S, alpha_true*S);
ifstream file(fname);

string line;
bool found = false; // Flag to check if the block is found

while (getline(file, line))
{
    // Look for the specific block identifier
    if (line.find("=== Results Summary for run: pilotrun tag: tag_1 ===") != string::npos)
    {
        found = true; // Mark that the block has been found
        break;
    }
}

double cross_section = 0;

if (found)
{
    // Read lines until the cross-section value is found
    while (getline(file, line))
    {
        if (line.find("Cross-section") != string::npos)
        {
            size_t pos = line.find(":");
            if (pos != string::npos)
            {
                string value_part = line.substr(pos + 1);
                istringstream iss(value_part);
                if (iss >> cross_section)
                {
                    cout << "Extracted Cross-section: " << cross_section << " pb" << endl;
                }
                else
                {
                    cerr << "Error: Could not parse cross-section value." << endl;
                }
            }
            break;
        }
    }
}
else
{
    cerr << "Error: Specified block not found in the log file." << endl;
}

file.close();

cout << "...." << endl;

cout << "___________________________________________" << endl;

cout << "sigma x B = " << cross_section << endl;


//_______________________________________________________________________
/*
TFile *f;
TTree *t;
double acc;

if(width!=0.0043)
{
    sprintf(fname, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_NOMINAL/RunIISummer20UL18_Suu-Diquark_W-%s_S-%.0f_chi-%.0f__AK4CHS_reduced_skim.root", width_name, S, S*alpha_true);

    f = new TFile(fname, "READ");

    t = (TTree*)f->Get("rootTupleTree/tree");

    acc = double(t->GetEntries("DeltaEtaJJAK4CHS<1.1 && DeltaRAK4CHS_First<2. && DeltaRAK4CHS_Second<2. && MasymmetryAK4CHS<0.1 && MaverageAK4CHS/FourjetMassAK4CHS>0.1")) / t->GetEntries();
}
else
{
     if(S!=10000 && S!=11000) sprintf(fname, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/reduced_trees/Suu_Diquarks/RunIIFall17MiniAODv2/MC2017_Suu_Diquark_S%.0f_chi%.0f_reduced_skim.root", S, S*alpha_true);
     if(S==10000 || S==11000) sprintf(fname, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/reduced_trees/Suu_Diquarks/RunIIFall17MiniAODv2/Summer20UL18_Suu_Diquark_S%.0f_chi%.0f_reduced_skim.root", S, S*alpha_true);

    f = new TFile(fname, "READ");

    t = (TTree*)f->Get("rootTupleTree/tree");

    acc = double(t->GetEntries("DeltaEtaJJAK4<1.1 && DeltaRAK4_First<2. && DeltaRAK4_Second<2. && Masymmetry<0.1 && Maverage/FourjetMass>0.1")) / t->GetEntries();
}    


cout << "___________________________________________" << endl;

cout << "A = " << acc << endl;

//cout << "sigma x B x A = " << cross_section*acc << endl;
*/
//_______________________________________________________________________


gROOT->ProcessLine(".L Calculate_pseudosignificance_3600.C");
double bin = Calculate_pseudosignificance_3600(width, alpha_true, S); // Example args

sprintf(fname, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_NOMINAL_Suu-Diquark_W-%s_S-%.0f_chi-%.0f_alphagt0p1.root", alpha_true_name, width_name, S, S*alpha_true);

TFile *fhist = new TFile(fname, "READ");

TH1D *h = (TH1D*)fhist->Get("h_FourjetMass");

double eff = double(h->Integral(bin, 103))/h->Integral();

cout << "___________________________________________" << endl;

cout << "eff = " << eff << endl;



cout << "___________________________________________" << endl;
cout << "___________________________________________" << endl;

//cout << "sigma x B x A x eff = " << cross_section*acc*eff << endl;

}
