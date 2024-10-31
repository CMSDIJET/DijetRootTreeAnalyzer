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

std::ofstream outputfile;

const double xsec_ref = 0.01;
const int m4j_scans = 11; 
const double width = 0.05;

void print_signal_xsec_fractions(double m4j, double Maverage, double alpha);



void print_signal_xsec_fractions_for_all_signals(double alpha_true)
{

double m4j[m4j_scans]   = {2000, 3000, 4000, 5000, 6000, 7000, 8000, 8400, 8600, 9000, 10000};
//double alpha[alpha_scans] = {0.11};

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

char width_name[1024];
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char foutname[1024];
sprintf(foutname,"xsec_fractions/signal_xsec_fractions_W-%s_alpha%s.txt",width_name,alpha_true_name);

outputfile.open(foutname);

for(int i=1;i<=m4j_scans;i++)
{
  /*for (int j=1;j<=alpha_scans;j++)
  {	  
    print_signal_xsec_fractions(m4j[i-1],m4j[i-1]*alpha[j-1]);
  }*/
  print_signal_xsec_fractions(m4j[i-1],m4j[i-1]*alpha_true,alpha_true);
  
}


  outputfile.close();

}







void print_signal_xsec_fractions(double Suu_mass, double chi_mass, double alpha_true)

{

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
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

char filename[1024];
int entries[13], entries_sum=0;
double fractions[13];

for(int i=1;i<=13;i++)
{

sprintf(filename,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_NOMINAL_Suu-Diquark_W-%s_S-%.0f_chi-%.0f_alphabin%d.root",alpha_true_name,width_name,Suu_mass,chi_mass,i); 
TFile *f = new TFile(filename);

TH1D *h_FourjetMass = (TH1D *) f -> Get("h_FourjetMass");


f -> cd();
entries[i-1] = h_FourjetMass -> GetEntries();
entries_sum+= h_FourjetMass -> GetEntries();
}



for(int i=1;i<=13;i++)
{
fractions[i-1]= (double(entries[i-1])/entries_sum)*xsec_ref ; 
}

  outputfile << "\tif [ $Suu == " << Suu_mass << " ] && [ $Chi == " << chi_mass << " ] " << " # ref xsec = " << xsec_ref << " pb " << "\n" << "\tthen" << "\n" << "\t\t" << "fraction_array=(" << fractions[0] << "\t" << fractions[1] << "\t" << fractions[2] << "\t" << fractions[3] << "\t" << fractions[4] << "\t" << fractions[5] << "\t" << fractions[6] << "\t" << fractions[7] << "\t" << fractions[8] << "\t" << fractions[9] << "\t" << fractions[10] << "\t" << fractions[11] << "\t" << fractions[12] << " ) " << "\n" << "\tfi" << "\n" << endl;
  

}

