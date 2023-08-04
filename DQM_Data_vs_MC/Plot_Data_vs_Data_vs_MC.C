

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

void Plot_Data_vs_Data_vs_MC(char jetAlgo[1024], char run1[1024], char run2[1024], char var[1024]){

char fname_data1[1024], fname_data2[1024], fname_mc1[1024], fname_mc2[1024];
sprintf(fname_data1,"data_histos/2023/Histos_AK4%s_%s_27p11fb-1_Winter23Prompt23_RunC_V2_DATA.root",jetAlgo,run1);
sprintf(fname_data2,"data_histos/2022/Jul2023_withL2L3residuals/Histos_AK4%s_%s.root",jetAlgo,run2);
sprintf(fname_mc1,"mc_histos/Histos_Run3Summer22_Stitched_QCD_PT-120toInf_35084pb-1_PUReweighted.root");
sprintf(fname_mc2,"mc_histos/Histos_Run3Summer22EE_Stitched_QCD_PT-120toInf_35084pb-1_PUReweighted.root");

//sprintf(fname_mc1,"mc_histos/Histos_Run3Summer22_Stitched_QCD_PT-120toInf_35084pb-1.root");
//sprintf(fname_mc2,"mc_histos/Histos_Run3Summer22EE_Stitched_QCD_PT-120toInf_35084pb-1.root");

char xaxistitle[1024];
double xmin, xmax;

if(strcmp(var,"FourjetMass")==0) {sprintf(xaxistitle,"Four-jet mass [GeV]");  xmin = 1607; xmax = 9067;}
if(strcmp(var,"Maverage")==0) {sprintf(xaxistitle,"Average dijet mass [GeV]");  xmin = 1; xmax = 3019;}
if(strcmp(var,"alpha")==0) {sprintf(xaxistitle,"#alpha = Average dijet mass / Four-jet mass"); xmin=0; xmax=0.5;}
if(strcmp(var,"DeltaEtaJJ")==0) {sprintf(xaxistitle,"|#Delta#eta| between two pairs"); xmin=0; xmax=1.1;}
if(strcmp(var,"DeltaPhiJJ")==0) {sprintf(xaxistitle,"|#Delta#phi| between two pairs"); xmin=0; xmax=3.1416;}
if(strcmp(var,"Masymmetry")==0) {sprintf(xaxistitle,"Mass asymmetry"); xmin=0; xmax=0.1;}
if(strcmp(var,"DeltaR1")==0) {sprintf(xaxistitle,"#DeltaR_{1}"); xmin=0; xmax=2;}
if(strcmp(var,"DeltaR2")==0) {sprintf(xaxistitle,"#DeltaR_{2}"); xmin=0; xmax=2;}
if(strcmp(var,"pT")==0) {sprintf(xaxistitle,"p_{T} of the 4 leading jets [GeV]"); xmin=0; xmax=4500;}
if(strcmp(var,"pTj1")==0) {sprintf(xaxistitle,"p_{T} of leading jet [GeV]"); xmin=0; xmax=4500;}
if(strcmp(var,"pTj2")==0) {sprintf(xaxistitle,"p_{T} of sub-leading jet [GeV]"); xmin=0; xmax=4500;}
if(strcmp(var,"pTj3")==0) {sprintf(xaxistitle,"p_{T} of third jet [GeV]"); xmin=0; xmax=4500;}
if(strcmp(var,"pTj4")==0) {sprintf(xaxistitle,"p_{T} of fourth jet [GeV]"); xmin=0; xmax=4500;}
if(strcmp(var,"eta")==0) {sprintf(xaxistitle,"#eta of the 4 leading jets"); xmin=-3; xmax=3;}
if(strcmp(var,"etaj1")==0) {sprintf(xaxistitle,"#eta of leading jet"); xmin=-3; xmax=3;}
if(strcmp(var,"etaj2")==0) {sprintf(xaxistitle,"#eta of sub-leading jet"); xmin=-3; xmax=3;}
if(strcmp(var,"etaj3")==0) {sprintf(xaxistitle,"#eta of third jet"); xmin=-3; xmax=3;}
if(strcmp(var,"etaj4")==0) {sprintf(xaxistitle,"#eta of fourth jet"); xmin=-3; xmax=3;}
if(strcmp(var,"phi")==0) {sprintf(xaxistitle,"#phi of the 4 leading jets"); xmin=-3.2; xmax=3.2;}
if(strcmp(var,"phij1")==0) {sprintf(xaxistitle,"#phi of leading jet"); xmin=-3.2; xmax=3.2;}
if(strcmp(var,"phij2")==0) {sprintf(xaxistitle,"#phi of sub-leading jet"); xmin=-3.2; xmax=3.2;}
if(strcmp(var,"phij3")==0) {sprintf(xaxistitle,"#phi of third jet"); xmin=-3.2; xmax=3.2;}
if(strcmp(var,"phij4")==0) {sprintf(xaxistitle,"#phi of fourth jet"); xmin=-3.2; xmax=3.2;}
if(strcmp(var,"CHF")==0) {sprintf(xaxistitle,"CHF of the 4 leading jets");  xmin = 0; xmax = 1.2;}
if(strcmp(var,"CEMF")==0) {sprintf(xaxistitle,"CEMF of the 4 leading jets");  xmin = 0; xmax = 1.2;}
if(strcmp(var,"NHF")==0) {sprintf(xaxistitle,"NHF of the 4 leading jets");  xmin = 0; xmax = 1.2;}
if(strcmp(var,"NEMF")==0) {sprintf(xaxistitle,"NEMF of the 4 leading jets");  xmin = 0; xmax = 1.2;}
if(strcmp(var,"CM")==0) {sprintf(xaxistitle,"Charged multiplicity of the 4 leading jets");  xmin = 0; xmax = 100;}
if(strcmp(var,"NM")==0) {sprintf(xaxistitle,"Neutral multiplicity of the 4 leading jets");  xmin = 0; xmax = 100;}
if(strcmp(var,"METoverHT")==0) {sprintf(xaxistitle,"MET / H_{T}");  xmin = 0; xmax = 1.2;}
if(strcmp(var,"nVtx")==0) {sprintf(xaxistitle,"Number of vertices");  xmin = 0; xmax = 100;}

TPaveText *cms = new TPaveText(0.17,0.95,0.32,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TFile *f_data1 = new TFile(fname_data1,"READ");
TFile *f_data2 = new TFile(fname_data2,"READ");
TFile *f_mc1 = new TFile(fname_mc1,"READ");
TFile *f_mc2 = new TFile(fname_mc2,"READ");
cout << "Data file 1 used: " << fname_data1 << endl;
cout << "Data file 2 used: " << fname_data2 << endl;
cout << "MC file 1 used: " << fname_mc1 << endl;
cout << "MC file 2 used: " << fname_mc2 << endl;

char hname_data[1024], hname_mc[1024];
char hvar[1024];

sprintf(hvar,"%s",var);
if(strcmp(var,"DeltaR1")==0) sprintf(hvar,"DeltaR_First");
if(strcmp(var,"DeltaR2")==0) sprintf(hvar,"DeltaR_Second");
if(strcmp(var,"CHF")==0) sprintf(hvar,"chargedHadEnFrac");
if(strcmp(var,"CHF")==0) sprintf(hvar,"chargedHadEnFrac");
if(strcmp(var,"NHF")==0) sprintf(hvar,"neutrHadEnFrac");
if(strcmp(var,"NEMF")==0) sprintf(hvar,"neutrElectromFrac");
if(strcmp(var,"CEMF")==0) sprintf(hvar,"chargedElectromFrac");
if(strcmp(var,"CM")==0) sprintf(hvar,"chargedMult");
if(strcmp(var,"NM")==0) sprintf(hvar,"neutrMult");

sprintf(hname_data,"h_%s_data",hvar);
sprintf(hname_mc,"h_%s_mc",hvar);

TH1D *h1 = (TH1D*)f_data1->Get(hname_data);
TH1D *h1_2 = (TH1D*)f_data2->Get(hname_data);
TH1D *h2 = (TH1D*)f_mc1->Get(hname_mc);
TH1D *h2_2 = (TH1D*)f_mc2->Get(hname_mc);

TCanvas *c = new TCanvas("c","",600,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);

TPad *pad1r = new TPad("pad1", "pad1", 0, 0.38, 1, 1);
pad1r->SetRightMargin(0.05);
pad1r->SetTopMargin(0.07);
pad1r->SetLeftMargin(0.13);
pad1r->SetBottomMargin(0.01);
pad1r->SetFillColor(0);
pad1r->SetBorderMode(0);
pad1r->SetFrameFillStyle(0);
pad1r->SetFrameBorderMode(0);
pad1r->Draw();
pad1r->cd();
pad1r->cd()->SetLogy(1);
if(strcmp(var,"DeltaEtaJJ")==0) pad1r->cd()->SetLogy(0);
pad1r->SetTickx(1);
pad1r->SetTicky(1);

h1->SetTitle("");
h1->SetStats(0);
h1->GetXaxis()->SetRangeUser(xmin, xmax);
h2->GetXaxis()->SetRangeUser(xmin, xmax);
//h1->GetYaxis()->SetTitle("Entries");
h1->GetYaxis()->SetTitle("Normalized to no. of events in 2023");
//h1->GetYaxis()->SetTitle("Normalized to 17.59 fb^{-1}");
h1->GetYaxis()->SetTitleSize(0.06); //0.07
h1->GetYaxis()->SetTitleOffset(0.9);
h1->SetMarkerColor(kBlack);
h1->SetMarkerStyle(8);
h1->SetMarkerSize(0.8);
h1->SetLineColor(kBlack);
h1->GetXaxis()->SetLabelOffset(1000);
h1->GetYaxis()->SetLabelSize(0.04);
h1->SetMinimum(0.2);
//h1->SetMaximum(100000);

h1_2->SetLineColor(kViolet);
h1_2->SetMarkerColor(kViolet);
h1_2->SetMarkerStyle(21);
h1_2->SetMarkerSize(0.8);
h1_2->SetLineWidth(2);

h2->SetLineColor(kBlue);
h2->SetLineWidth(3);

h2_2->SetLineColor(kRed);
h2_2->SetLineWidth(3);


h1_2->Scale(h1->Integral()/h1_2->Integral());
h2->Scale(h1->Integral()/h2->Integral());
h2_2->Scale(h1->Integral()/h2_2->Integral());

//h1_2->Scale(17.59/35.08);
//h2->Scale(17.59/35.084);
//h2_2->Scale(17.59/35.084);


h1->Draw("PE1");
//h1_2->Draw("PE1 same");
h2->Draw("hist same");
h2_2->Draw("hist same");
h1_2->Draw("PE1 same");
h1->Draw("PE1 same");

//cout << "2023 data = " << h1->Integral() << endl;
//cout << "2022 data = " << h1_2->Integral() << endl;
//cout << "2022 pre-EE MC = " << h2->Integral() << endl;
//cout << "2022 post-EE MC = " << h2_2->Integral() << endl;

char legname1[1024], legname2[1024];
sprintf(legname1,"AK4 %s",jetAlgo);
sprintf(legname2,"All analysis cuts");

//top right
if(strcmp(var,"FourjetMass")==0 || strcmp(var,"Maverage")==0 || strcmp(var,"pT")==0 || strcmp(var,"pTj1")==0 || strcmp(var,"pTj2")==0 || strcmp(var,"pTj3")==0 || strcmp(var,"pTj4")==0 || strcmp(var,"NHF")==0 || strcmp(var,"METoverHT")==0 || strcmp(var,"NM")==0 || strcmp(var,"CEMF")==0) 
{
	TLegend *leg = new TLegend(0.51,0.58,0.76,0.88,"");
	//TLegend *leg = new TLegend(0.48,0.58,0.73,0.88,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.05);
	leg->AddEntry((TObject*)0,legname1,"");
	leg->AddEntry((TObject*)0,legname2,"");
	leg->AddEntry(h1,"2023 Data (27.14 fb^{-1})","PE");
	leg->AddEntry(h1_2,"2022 Data (35.08 fb^{-1})","PE");
	//leg->AddEntry(h1_2,"2022FG Data (21.13 fb^{-1})","PE");
	leg->AddEntry(h2,"Summer22 QCD MC","L");
	leg->AddEntry(h2_2,"Summer22EE QCD MC","L");
	leg->Draw();
}

//bottom right
if(strcmp(var,"DeltaEtaJJ")==0 || strcmp(var,"DeltaR1")==0 || strcmp(var,"DeltaR2")==0)
{
	TLegend *leg = new TLegend(0.52,0.07,0.72,0.37,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.05);
	leg->AddEntry((TObject*)0,legname1,"");
	leg->AddEntry((TObject*)0,legname2,"");
	leg->AddEntry(h1,"2023 Data (27.14 fb^{-1})","PE");
	leg->AddEntry(h1_2,"2022 Data (35.08 fb^{-1})","PE");
	//leg->AddEntry(h1_2,"2022FG Data (21.13 fb^{-1})","PE");
	leg->AddEntry(h2,"Summer22 QCD MC","L");
	leg->AddEntry(h2_2,"Summer22EE QCD MC","L");
	leg->Draw();
}

//bottom left
if(strcmp(var,"DeltaPhiJJ")==0 || strcmp(var,"NEMF")==0 || strcmp(var,"CM")==0)
{
	TLegend *leg = new TLegend(0.18,0.07,0.48,0.37,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.05);
	leg->AddEntry((TObject*)0,legname1,"");
	leg->AddEntry((TObject*)0,legname2,"");
	leg->AddEntry(h1,"2023 Data (27.14 fb^{-1})","PE");
	leg->AddEntry(h1_2,"2022 Data (35.08 fb^{-1})","PE");
	//leg->AddEntry(h1_2,"2022FG Data (21.13 fb^{-1})","PE");
	leg->AddEntry(h2,"Summer22 QCD MC","L");
	leg->AddEntry(h2_2,"Summer22EE QCD MC","L");
	leg->Draw();
}

//bottom middle
if(strcmp(var,"alpha")==0 || strcmp(var,"Masymmetry")==0 || strcmp(var,"eta")==0 || strcmp(var,"etaj1")==0 || strcmp(var,"etaj2")==0 || strcmp(var,"etaj3")==0 || strcmp(var,"etaj4")==0 || strcmp(var,"phi")==0 || strcmp(var,"phij1")==0 || strcmp(var,"phij2")==0 || strcmp(var,"phij3")==0 || strcmp(var,"phij4")==0 || strcmp(var,"CHF")==0)
{
	TLegend *leg = new TLegend(0.35,0.07,0.55,0.37,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.05);
	leg->AddEntry((TObject*)0,legname1,"");
	leg->AddEntry((TObject*)0,legname2,"");
	leg->AddEntry(h1,"2023 Data (27.14 fb^{-1})","PE");
	leg->AddEntry(h1_2,"2022 Data (35.08 fb^{-1})","PE");
	//leg->AddEntry(h1_2,"2022FG Data (21.13 fb^{-1})","PE");
	leg->AddEntry(h2,"Summer22 QCD MC","L");
	leg->AddEntry(h2_2,"Summer22EE QCD MC","L");
	leg->Draw();
}


if(strcmp(var,"nVtx")==0)
{
	TLegend *leg = new TLegend(0.23,0.07,0.43,0.37,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.05);
	leg->AddEntry((TObject*)0,legname1,"");
	leg->AddEntry((TObject*)0,legname2,"");
	leg->AddEntry(h1,"2023 Data (27.14 fb^{-1})","PE");
	leg->AddEntry(h1_2,"2022 Data (35.08 fb^{-1})","PE");
	leg->AddEntry(h2,"Summer22 QCD MC","L");
	leg->AddEntry(h2_2,"Summer22EE QCD MC","L");
	leg->Draw();
}

cms->Draw();

if(strcmp(run1,"2023BCD")==0 && strcmp(run2,"2022CDEFG")==0)
{
	TPaveText *lumileg = new TPaveText(0.675,0.95,0.945,0.99,"NDC");
	lumileg->SetFillColor(0);
	lumileg->SetBorderSize(0);
	lumileg->AddText("62.22 fb^{-1} (13.6 TeV)");
	lumileg->SetTextFont(42);
	lumileg->SetTextSize(0.05);
	lumileg->Draw();
}

if(strcmp(run1,"2023BCD")==0 && strcmp(run2,"2022FG")==0)
{
	TPaveText *lumileg = new TPaveText(0.68,0.95,0.95,0.99,"NDC");
	lumileg->SetFillColor(0);
	lumileg->SetBorderSize(0);
	lumileg->AddText("48.27 fb^{-1} (13.6 TeV)");
	lumileg->SetTextFont(42);
	lumileg->SetTextSize(0.05);
	lumileg->Draw();
}

c->cd();
TPad *pad2r = new TPad("pad2r", "pad2r", 0, 0., 1, 0.35);
pad2r->SetLeftMargin(0.13);
pad2r->SetBottomMargin(0.25);
pad2r->SetRightMargin(0.05);
pad2r->SetTopMargin(0.01);
pad2r->Draw();
pad2r->cd(); 
pad2r->SetTickx(1);
pad2r->SetTicky(1);

TH1D *h_ratio = (TH1D*)h1->Clone();
h_ratio->Divide(h2);

TH1D *h_ratio_2 = (TH1D*)h1->Clone();
h_ratio_2->Divide(h1_2);

h_ratio->SetStats(0);
h_ratio->SetMarkerStyle(8);
h_ratio->SetMarkerColor(kBlack);
h_ratio->SetLineColor(kBlack);
h_ratio->SetMarkerSize(0.8);
h_ratio->GetXaxis()->SetRangeUser(xmin, xmax);
h_ratio->GetYaxis()->SetRangeUser(0.01, 1.99);
h_ratio->GetYaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelOffset(0.03);
h_ratio->GetXaxis()->SetTitle(xaxistitle);
h_ratio->GetXaxis()->SetTitleSize(0.09);//0.12
h_ratio->GetXaxis()->SetTitleOffset(1.2);//0.95
h_ratio->GetYaxis()->SetTitle("Ratio");
h_ratio->GetYaxis()->CenterTitle(1);
h_ratio->GetYaxis()->SetTitleSize(0.12);
h_ratio->GetYaxis()->SetTitleOffset(0.5);
h_ratio->GetYaxis()->SetNdivisions(210);
h_ratio->SetLineWidth(3);
h_ratio->Draw("PE1");

h_ratio_2->SetStats(0);
h_ratio_2->SetMarkerStyle(8);
h_ratio_2->SetMarkerColor(kMagenta);
h_ratio_2->SetLineColor(kMagenta);
h_ratio_2->SetMarkerSize(0.8);
h_ratio_2->SetLineWidth(3);
h_ratio_2->Draw("PE1 same");


TLine *line = new TLine(xmin,1,xmax,1);
line->SetLineWidth(2);
line->SetLineStyle(kDashed);
line->Draw("same");

//TLegend *leg_ratio = new TLegend(0.54,0.75,0.79,0.95,""); //top right
//TLegend *leg_ratio = new TLegend(0.58,0.75,0.83,0.95,""); //top right
//TLegend *leg_ratio = new TLegend(0.16,0.3,0.31,0.5,""); //bottom left
//TLegend *leg_ratio = new TLegend(0.58,0.3,0.83,0.5,""); //bottom right
TLegend *leg_ratio = new TLegend(0.54,0.3,0.79,0.5,""); //bottom right
//TLegend *leg_ratio = new TLegend(0.16,0.75,0.31,0.95,""); //top left
leg_ratio->SetBorderSize(0);
leg_ratio->SetTextSize(0.075);
leg_ratio->AddEntry(h_ratio,"2023 data / 2022 MC","PE");
leg_ratio->AddEntry(h_ratio_2,"2023 data / 2022 data","PE");
//leg_ratio->AddEntry(h_ratio_2,"2023 data / 2022FG data","PE");
leg_ratio->Draw();


char cname_1[1024], cname_2[1024];

sprintf(cname_1,"plots/2023BC_27p11fb-1_Winter23Prompt23_RunC_V2_DATA/DataRuns%s_VS_DataRuns%s_VS_Summer22_VS_Summer22EE_AK4%s_%s.png",run1,run2,jetAlgo,var);
sprintf(cname_2,"plots/2023BC_27p11fb-1_Winter23Prompt23_RunC_V2_DATA/DataRuns%s_VS_DataRuns%s_VS_Summer22_VS_Summer22EE_AK4%s_%s.pdf",run1,run2,jetAlgo,var);

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
