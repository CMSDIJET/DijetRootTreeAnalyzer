#include "TH1D.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "Math/MinimizerOptions.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TEllipse.h"

void Plot_data_vs_bkgtoy(int alphabin){

char alpha_name[1024];

if(alphabin==1) sprintf(alpha_name,"0.10 < #alpha < 0.12");
if(alphabin==2) sprintf(alpha_name,"0.12 < #alpha < 0.14");
if(alphabin==3) sprintf(alpha_name,"0.14 < #alpha < 0.16");
if(alphabin==4) sprintf(alpha_name,"0.16 < #alpha < 0.18");
if(alphabin==5) sprintf(alpha_name,"0.18 < #alpha < 0.20");
if(alphabin==6) sprintf(alpha_name,"0.20 < #alpha < 0.22");
if(alphabin==7) sprintf(alpha_name,"0.22 < #alpha < 0.24");
if(alphabin==8) sprintf(alpha_name,"0.24 < #alpha < 0.26");
if(alphabin==9) sprintf(alpha_name,"0.26 < #alpha < 0.28");
if(alphabin==10) sprintf(alpha_name,"0.28 < #alpha < 0.30");
if(alphabin==11) sprintf(alpha_name,"0.30 < #alpha < 0.32");
if(alphabin==12) sprintf(alpha_name,"0.32 < #alpha < 0.34");
if(alphabin==13) sprintf(alpha_name,"#alpha > 0.34");

char fname_data[1024], fname_bkgtoy[1024];
sprintf(fname_data,"inputs/run2/data/HISTOS_4J_Alldata_SR_alphabin%d.root",alphabin);
sprintf(fname_bkgtoy,"inputs/run2/ToysFromData/FixedBinning_HISTOS_4J_Toy_SR_alphabin%d.root",alphabin);

TFile *f_data = new TFile(fname_data,"READ");
TFile *f_bkgtoy = new TFile(fname_bkgtoy,"READ");

TH1D *h_data = (TH1D*)f_data->Get("h_FourjetMass"); 
TH1D *h_bkgtoy = (TH1D*)f_bkgtoy->Get("h_FourjetMass");

TH1D *h_addition = (TH1D*)h_data->Clone();
h_addition->Add(h_bkgtoy);

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetLogy(1);
c->SetTickx(1);
c->SetTicky(1);

h_data->SetTitle("");
h_bkgtoy->SetTitle("");
h_addition->SetTitle("");
h_data->SetStats(0);
h_bkgtoy->SetStats(0);
h_addition->SetStats(0);

h_data->GetXaxis()->SetRangeUser(1607, 10072);
h_bkgtoy->GetXaxis()->SetRangeUser(1607, 10072);
h_addition->GetXaxis()->SetRangeUser(1607, 10072);
h_data->GetYaxis()->SetTitle("Events");
h_data->GetYaxis()->SetTitleSize(0.05);
h_data->GetYaxis()->SetTitleOffset(0.9);
h_data->GetYaxis()->SetLabelSize(0.04);
h_data->GetXaxis()->SetTitle("Four-jet mass [GeV]");
h_data->GetXaxis()->SetTitleSize(0.05);
h_data->GetXaxis()->SetTitleOffset(0.9);
h_data->GetXaxis()->SetLabelSize(0.04);
h_data->SetMinimum(0.5);
h_data->SetMaximum(30000.);

h_data->SetMarkerSize(1.2);
h_bkgtoy->SetMarkerSize(1.2);
h_addition->SetMarkerSize(0.8);
h_data->SetMarkerStyle(8);
h_bkgtoy->SetMarkerStyle(8);
h_addition->SetMarkerStyle(8);
h_data->SetMarkerColor(kBlue);
h_bkgtoy->SetMarkerColor(kRed+1);
h_addition->SetMarkerColor(kBlack);
h_data->SetLineColor(kBlue);
h_bkgtoy->SetLineColor(kRed+1);
h_addition->SetLineColor(kBlack);

h_data->Draw("PE1");
h_bkgtoy->Draw("PE1 same");
h_addition->Draw("PE1 same");

cout<<"Integral of data = "<<h_data->Integral()<<endl;
cout<<"Integral of bkg toy = "<<h_bkgtoy->Integral()<<endl;
cout<<"Integral of addition = "<<h_addition->Integral()<<endl;

char legname[1024];
sprintf(legname,"#alpha bin %d",alphabin);

TLegend *leg = new TLegend(0.42,0.57,0.72,0.87,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.04); //0.038
leg->AddEntry((TObject*)0,legname,"");
leg->AddEntry((TObject*)0,alpha_name,"");
leg->AddEntry(h_data,"CMS RunII data","PE");
leg->AddEntry(h_bkgtoy,"Bkg toy","PE");
leg->AddEntry(h_addition,"CMS RunII Data + Bkg toy","PE");
leg->Draw();


char cname_1[1024], cname_2[1024];

sprintf(cname_1,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/plots/Data_vs_BkgToy_alphabin%d.png",alphabin);
sprintf(cname_2,"output/Wide_Resonances_CMSRunIIPlusBkgToyPlusATLASEvent/plots/Data_vs_BkgToy_alphabin%d.pdf",alphabin);

c->SaveAs(cname_1);
c->SaveAs(cname_2);

char foutname[1024];
sprintf(foutname,"inputs/run2/pseudodata_CMSRunIIPlusBkgToyPlusATLASEvent/HISTOS_4J_CMSRunIIPlusBkgToyPlusATLASEvent_SR_alphabin%d.root",alphabin);

TFile *fout = new TFile(foutname,"RECREATE");
fout->cd();
h_addition->Write();


}
