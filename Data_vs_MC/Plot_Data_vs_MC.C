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

void Plot_Data_vs_MC(char jetAlgo[1024], char run[1024], char var[1024]){

char fname[1024];
sprintf(fname,"AllRuns_35p2fb-1/Histos_DataAllRuns2022_VS_QCDFlatMC_AllSelCrit_PUReweight_AK4%s.root",jetAlgo);

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
if(strcmp(var,"pT")==0) {sprintf(xaxistitle,"p_{T} of the 4 leading jets [GeV]"); xmin=0; xmax=4000;}
if(strcmp(var,"pTj1")==0) {sprintf(xaxistitle,"p_{T} of leading jet [GeV]"); xmin=0; xmax=7000;}
if(strcmp(var,"pTj2")==0) {sprintf(xaxistitle,"p_{T} of sub-leading jet [GeV]"); xmin=0; xmax=7000;}
if(strcmp(var,"pTj3")==0) {sprintf(xaxistitle,"p_{T} of third jet [GeV]"); xmin=0; xmax=7000;}
if(strcmp(var,"pTj4")==0) {sprintf(xaxistitle,"p_{T} of fourth jet [GeV]"); xmin=0; xmax=7000;}
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
if(strcmp(var,"NHF")==0) {sprintf(xaxistitle,"NHF of the 4 leading jets");  xmin = 0; xmax = 1.2;}
if(strcmp(var,"NEMF")==0) {sprintf(xaxistitle,"NEMF of the 4 leading jets");  xmin = 0; xmax = 1.2;}
if(strcmp(var,"CM")==0) {sprintf(xaxistitle,"Charged multiplicity of the 4 leading jets");  xmin = 0; xmax = 70;}
if(strcmp(var,"NM")==0) {sprintf(xaxistitle,"Neutral multiplicity of the 4 leading jets");  xmin = 0; xmax = 70;}
if(strcmp(var,"METoverHT")==0) {sprintf(xaxistitle,"MET / H_{T}");  xmin = 0; xmax = 1;}
if(strcmp(var,"nVtx")==0) {sprintf(xaxistitle,"Number of vertices");  xmin = 0; xmax = 70;}

TPaveText *cms = new TPaveText(0.17,0.95,0.32,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TFile *f = new TFile(fname,"READ");
cout << "File used: " << fname << endl;

char hname_data[1024], hname_mc[1024];
char hvar[1024];

sprintf(hvar,"%s",var);
if(strcmp(var,"DeltaR1")==0) sprintf(hvar,"DeltaR_First");
if(strcmp(var,"DeltaR2")==0) sprintf(hvar,"DeltaR_Second");
if(strcmp(var,"CHF")==0) sprintf(hvar,"chargedHadEnFrac");
if(strcmp(var,"CHF")==0) sprintf(hvar,"chargedHadEnFrac");
if(strcmp(var,"NHF")==0) sprintf(hvar,"neutrHadEnFrac");
if(strcmp(var,"NEMF")==0) sprintf(hvar,"neutrElectromFrac");
if(strcmp(var,"CM")==0) sprintf(hvar,"chargedMult");
if(strcmp(var,"NM")==0) sprintf(hvar,"neutrMult");

sprintf(hname_data,"h_%s_data",hvar);
sprintf(hname_mc,"h_%s_mc",hvar);

TH1D *h1 = (TH1D*)f->Get(hname_data);
TH1D *h2 = (TH1D*)f->Get(hname_mc);


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
h1->GetYaxis()->SetTitle("Entries");
h1->GetYaxis()->SetTitleSize(0.07);
h1->GetYaxis()->SetTitleOffset(0.9);
h1->SetMarkerColor(kBlack);
h1->SetMarkerStyle(8);
h1->SetMarkerSize(0.8);
h1->SetLineColor(kBlack);
h1->GetXaxis()->SetLabelOffset(1000);
h1->GetYaxis()->SetLabelSize(0.04);
h1->SetMinimum(0.5);
//h1->SetMaximum(100000);

h2->SetLineColor(kRed);
h2->SetLineWidth(3);

h1->Draw("PE1");
h2->Scale(h1->Integral()/h2->Integral());
h2->Draw("hist same");
h1->Draw("PE1 same");

char legname[1024];
sprintf(legname,"#splitline{AK4 %s}{All analysis cuts applied}",jetAlgo);

//top right
if(strcmp(var,"FourjetMass")==0 || strcmp(var,"Maverage")==0 || strcmp(var,"pT")==0 || strcmp(var,"pTj1")==0 || strcmp(var,"pTj2")==0 || strcmp(var,"pTj3")==0 || strcmp(var,"pTj4")==0 || strcmp(var,"NHF")==0 || strcmp(var,"METoverHT")==0 || strcmp(var,"NM")==0) 
{
	TLegend *leg = new TLegend(0.55,0.6,0.8,0.9,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.05);
	leg->SetHeader(legname);
	leg->AddEntry(h1,"Data","PE");
	leg->AddEntry(h2,"QCD MC","L");
	leg->Draw();
}

//bottom right
if(strcmp(var,"DeltaEtaJJ")==0 || strcmp(var,"DeltaR1")==0 || strcmp(var,"DeltaR2")==0)
{
	TLegend *leg = new TLegend(0.55,0.07,0.75,0.37,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.05);
	leg->SetHeader(legname);
	leg->AddEntry(h1,"Data","PE");
	leg->AddEntry(h2,"QCD MC","L");
	leg->Draw();
}

//bottom left
if(strcmp(var,"DeltaPhiJJ")==0 || strcmp(var,"NEMF")==0)
{
	TLegend *leg = new TLegend(0.2,0.07,0.5,0.37,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.05);
	leg->SetHeader(legname);
	leg->AddEntry(h1,"Data","PE");
	leg->AddEntry(h2,"QCD MC","L");
	leg->Draw();
}

//bottom middle
if(strcmp(var,"nVtx")==0 || strcmp(var,"alpha")==0 || strcmp(var,"Masymmetry")==0 || strcmp(var,"eta")==0 || strcmp(var,"etaj1")==0 || strcmp(var,"etaj2")==0 || strcmp(var,"etaj3")==0 || strcmp(var,"etaj4")==0 || strcmp(var,"phi")==0 || strcmp(var,"phij1")==0 || strcmp(var,"phij2")==0 || strcmp(var,"phij3")==0 || strcmp(var,"phij4")==0 || strcmp(var,"CHF")==0 || strcmp(var,"CM")==0)
{
	TLegend *leg = new TLegend(0.35,0.07,0.55,0.37,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.05);
	leg->SetHeader(legname);
	leg->AddEntry(h1,"Data","PE");
	leg->AddEntry(h2,"QCD MC","L");
	leg->Draw();
}

cms->Draw();

if(strcmp(run,"B")==0 || strcmp(run,"C")==0 || strcmp(run,"D")==0 || strcmp(run,"E")==0 || strcmp(run,"F")==0)
{
	TPaveText *lumileg = new TPaveText(0.554,0.95,0.884,0.99,"NDC");
	lumileg->SetFillColor(0);
	lumileg->SetBorderSize(0);
	if(strcmp(run,"B")==0) lumileg->AddText("2022 RunB, 0.1 fb^{-1} (13.6 TeV)");
	if(strcmp(run,"C")==0) lumileg->AddText("2022 RunC, 4.9 fb^{-1} (13.6 TeV)");
	if(strcmp(run,"D")==0) lumileg->AddText("2022 RunD, 2.7 fb^{-1} (13.6 TeV)");
	if(strcmp(run,"E")==0) lumileg->AddText("2022 RunE, 5.7 fb^{-1} (13.6 TeV)");
	if(strcmp(run,"F")==0) lumileg->AddText("2022 RunF, 13.6 fb^{-1} (13.6 TeV)");
	lumileg->SetTextFont(42);
	lumileg->SetTextSize(0.05);
	lumileg->Draw();
}
else if(strcmp(run,"BCDEFG")==0)
{
	//TPaveText *lumileg = new TPaveText(0.51,0.95,0.84,0.99,"NDC");
	TPaveText *lumileg = new TPaveText(0.68,0.95,0.95,0.99,"NDC");
	lumileg->SetFillColor(0);
	lumileg->SetBorderSize(0);
	//lumileg->AddText("2022 RunsBCDEF, 29.8 fb^{-1} (13.6 TeV)");
	lumileg->AddText("35.2 fb^{-1} (13.6 TeV)");
	lumileg->SetTextFont(42);
	lumileg->SetTextSize(0.05);
	lumileg->Draw();
}
else if(strcmp(run,"BCDEF")==0)
{
	//TPaveText *lumileg = new TPaveText(0.51,0.95,0.84,0.99,"NDC");
	TPaveText *lumileg = new TPaveText(0.685,0.95,0.955,0.99,"NDC");
	lumileg->SetFillColor(0);
	lumileg->SetBorderSize(0);
	//lumileg->AddText("2022 RunsBCDEF, 29.8 fb^{-1} (13.6 TeV)");
	lumileg->AddText("30 fb^{-1} (13.6 TeV)");
	lumileg->SetTextFont(42);
	lumileg->SetTextSize(0.05);
	lumileg->Draw();
}
else if(strcmp(run,"BCD")==0)
{
	TPaveText *lumileg = new TPaveText(0.54,0.95,0.87,0.99,"NDC");
	lumileg->SetFillColor(0);
	lumileg->SetBorderSize(0);
	lumileg->AddText("2022 RunsBCD, 7.7 fb^{-1} (13.6 TeV)");
	lumileg->SetTextFont(42);
	lumileg->SetTextSize(0.05);
	lumileg->Draw();
}
else if(strcmp(run,"BCDE")==0)
{
	TPaveText *lumileg = new TPaveText(0.53,0.95,0.86,0.99,"NDC");
	lumileg->SetFillColor(0);
	lumileg->SetBorderSize(0);
	lumileg->AddText("2022 RunsBCDE, 13.4 fb^{-1} (13.6 TeV)");
	lumileg->SetTextFont(42);
	lumileg->SetTextSize(0.045);
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

h_ratio->SetStats(0);
h_ratio->SetMarkerStyle(8);
h_ratio->SetMarkerColor(kBlack);
h_ratio->SetLineColor(kBlack);
h_ratio->SetMarkerSize(0.8);
h_ratio->GetXaxis()->SetRangeUser(xmin, xmax);
h_ratio->GetYaxis()->SetRangeUser(0.01, 2.99);
h_ratio->GetYaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelSize(0.08);
h_ratio->GetXaxis()->SetLabelOffset(0.03);
h_ratio->GetXaxis()->SetTitle(xaxistitle);
h_ratio->GetXaxis()->SetTitleSize(0.09);//0.12
h_ratio->GetXaxis()->SetTitleOffset(1.2);//0.95
h_ratio->GetYaxis()->SetTitle("Data / MC");
h_ratio->GetYaxis()->CenterTitle(1);
h_ratio->GetYaxis()->SetTitleSize(0.12);
h_ratio->GetYaxis()->SetTitleOffset(0.5);
h_ratio->GetYaxis()->SetNdivisions(210);
h_ratio->SetLineWidth(3);
h_ratio->Draw("PE1");

TLine *line = new TLine(xmin,1,xmax,1);
line->SetLineWidth(2);
line->SetLineStyle(kDashed);
line->Draw("same");

char cname_1[1024], cname_2[1024];

sprintf(cname_1,"AllRuns_35p2fb-1/plots/%s_AllCuts_DataRuns2022%s_VS_MC_%s_.png",var,run,jetAlgo);
sprintf(cname_2,"AllRuns_35p2fb-1/plots/%s_AllCuts_DataRuns2022%s_VS_MC_%s_.pdf",var,run,jetAlgo);

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
