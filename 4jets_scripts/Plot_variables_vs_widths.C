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

void Plot_variables_vs_widths(int Suu, int Chi, char var[1024]){

char fname1[1024], fname2[1024], fname3[1024], fname4[1024];
sprintf(fname1,"signal_histos_NoSelectionCuts/ResonanceShapes_RunIIFall17_Suu-Diquark_W-0p0043_S-%d_chi-%d_NoSelectionCuts.root",Suu,Chi);
sprintf(fname2,"signal_histos_NoSelectionCuts/ResonanceShapes_RunIISummer20UL18_Suu-Diquark_W-0p015_S-%d_chi-%d_NoSelectionCuts.root",Suu,Chi);
sprintf(fname3,"signal_histos_NoSelectionCuts/ResonanceShapes_RunIISummer20UL18_Suu-Diquark_W-0p05_S-%d_chi-%d_NoSelectionCuts.root",Suu,Chi);
sprintf(fname4,"signal_histos_NoSelectionCuts/ResonanceShapes_RunIISummer20UL18_Suu-Diquark_W-0p1_S-%d_chi-%d_NoSelectionCuts.root",Suu,Chi);

char xaxistitle[1024];
double xmin, xmax;

if(strcmp(var,"FourjetMass")==0) {sprintf(xaxistitle,"Four-jet mass [GeV]");  xmin = 1; xmax = 12395;}
if(strcmp(var,"Maverage")==0) {sprintf(xaxistitle,"Average dijet mass [GeV]");  xmin = 1; xmax = 4337;}
if(strcmp(var,"Dijet_Mass_1")==0) {sprintf(xaxistitle,"Dijet mass of first pair [GeV]");  xmin = 1; xmax = 4337;}
if(strcmp(var,"Dijet_Mass_2")==0) {sprintf(xaxistitle,"Dijet mass of second pair [GeV]");  xmin = 1; xmax = 4337;}
if(strcmp(var,"alpha")==0) {sprintf(xaxistitle,"#alpha = Average dijet mass / Four-jet mass"); xmin=0; xmax=0.5;}
//if(strcmp(var,"DeltaEtaJJ")==0) {sprintf(xaxistitle,"|#Delta#eta| between two pairs"); xmin=0; xmax=1.1;}
if(strcmp(var,"DeltaEtaJJ")==0) {sprintf(xaxistitle,"|#Delta#eta| between two pairs"); xmin=0; xmax=6;}
if(strcmp(var,"DeltaPhiJJ")==0) {sprintf(xaxistitle,"|#Delta#phi| between two pairs"); xmin=0; xmax=3.1416;}
//if(strcmp(var,"Masymmetry")==0) {sprintf(xaxistitle,"Mass asymmetry"); xmin=0; xmax=0.1;}
if(strcmp(var,"Masymmetry")==0) {sprintf(xaxistitle,"Mass asymmetry"); xmin=0; xmax=1;}
//if(strcmp(var,"DeltaR1")==0) {sprintf(xaxistitle,"#DeltaR_{1}"); xmin=0; xmax=2;}
//if(strcmp(var,"DeltaR2")==0) {sprintf(xaxistitle,"#DeltaR_{2}"); xmin=0; xmax=2;}
if(strcmp(var,"DeltaR1")==0) {sprintf(xaxistitle,"#DeltaR_{1}"); xmin=0; xmax=6;}
if(strcmp(var,"DeltaR2")==0) {sprintf(xaxistitle,"#DeltaR_{2}"); xmin=0; xmax=6;}
if(strcmp(var,"pT")==0) {sprintf(xaxistitle,"p_{T} of the 4 leading jets [GeV]"); xmin=0; xmax=5200;}
if(strcmp(var,"pTj1")==0) {sprintf(xaxistitle,"p_{T} of leading jet [GeV]"); xmin=0; xmax=5200;}
if(strcmp(var,"pTj2")==0) {sprintf(xaxistitle,"p_{T} of sub-leading jet [GeV]"); xmin=0; xmax=5200;}
if(strcmp(var,"pTj3")==0) {sprintf(xaxistitle,"p_{T} of third jet [GeV]"); xmin=0; xmax=5200;}
if(strcmp(var,"pTj4")==0) {sprintf(xaxistitle,"p_{T} of fourth jet [GeV]"); xmin=0; xmax=5200;}
if(strcmp(var,"eta")==0) {sprintf(xaxistitle,"#eta of the 4 leading jets"); xmin=-3; xmax=3;}
if(strcmp(var,"etaj1")==0) {sprintf(xaxistitle,"#eta of leading jet"); xmin=-3; xmax=3;}
if(strcmp(var,"etaj2")==0) {sprintf(xaxistitle,"#eta of sub-leading jet"); xmin=-3; xmax=3;}
if(strcmp(var,"etaj3")==0) {sprintf(xaxistitle,"#eta of third jet"); xmin=-3; xmax=3;}
if(strcmp(var,"etaj4")==0) {sprintf(xaxistitle,"#eta of fourth jet"); xmin=-3; xmax=3;}
if(strcmp(var,"phi")==0) {sprintf(xaxistitle,"#phi of the 4 leading jets"); xmin=-3.1416; xmax=3.14;}
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

TPaveText *cms = new TPaveText(0.23,0.95,0.38,0.99,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.055);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TPaveText *lumileg = new TPaveText(0.85,0.95,0.98,0.99,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->AddText("13 TeV");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);

char legname1[1024], legname2[1024];
sprintf(legname1,"M_{S} = %.0f TeV",Suu/1000.);
sprintf(legname2,"M_{#chi} = %.2f TeV",Chi/1000.);

TPaveText *signalleg = new TPaveText(0.75,0.75,0.87,0.87,"NDC");
signalleg->SetFillColor(0);
signalleg->SetBorderSize(0);
signalleg->AddText(legname1);
signalleg->AddText(legname2);
signalleg->SetTextFont(42);
signalleg->SetTextSize(0.04);

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");
TFile *f3 = new TFile(fname3,"READ");
TFile *f4 = new TFile(fname4,"READ");
cout << "File 1 used: " << fname1 << endl;
cout << "File 2 used: " << fname2 << endl;
cout << "File 3 used: " << fname3 << endl;
cout << "File 4 used: " << fname4 << endl;

char hname[1024];
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

sprintf(hname,"h_%s",hvar);

TH1D *h1 = (TH1D*)f1->Get(hname);
TH1D *h2 = (TH1D*)f2->Get(hname);
TH1D *h3 = (TH1D*)f3->Get(hname);
TH1D *h4 = (TH1D*)f4->Get(hname);

TCanvas *c = new TCanvas("c","",800,700);
c->cd()->SetLogy(1);
c->SetTickx(1);
c->SetTicky(1);
//if(strcmp(var,"DeltaEtaJJ")==0) c->cd()->SetLogy(0);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.02);
c->SetTopMargin(0.07);

h1->SetTitle("");
h1->SetStats(0);
h1->GetXaxis()->SetRangeUser(xmin, xmax);
h2->GetXaxis()->SetRangeUser(xmin, xmax);
h3->GetXaxis()->SetRangeUser(xmin, xmax);
h4->GetXaxis()->SetRangeUser(xmin, xmax);
h1->GetYaxis()->SetTitle("Normalized events");
h1->GetYaxis()->SetTitleSize(0.06);
h1->GetYaxis()->SetTitleOffset(0.8);
h1->GetXaxis()->SetTitle(xaxistitle);
h1->GetXaxis()->SetTitleSize(0.06);
h1->GetXaxis()->SetTitleOffset(0.75);

h1->SetMinimum(0.5);
h1->SetMaximum(30000);

h1->SetLineColor(kBlack);
h2->SetLineColor(kRed+1);
h3->SetLineColor(kBlue-3);
h4->SetLineColor(kGreen+2);

h1->SetLineWidth(3);
h2->SetLineWidth(3);
h3->SetLineWidth(3);
h4->SetLineWidth(3);

h2->Scale(h1->Integral()/h2->Integral());
h3->Scale(h1->Integral()/h3->Integral());
h4->Scale(h1->Integral()/h4->Integral());

h1->Draw("hist");
h2->Draw("hist same");
h3->Draw("hist same");
h4->Draw("hist same");



//top left
if(strcmp(var,"eta")==0 || strcmp(var,"DeltaR1")==0 || strcmp(var,"DeltaR2")==0 || strcmp(var,"FourjetMass")==0 || strcmp(var,"alpha")==0) 
{
	TLegend *leg = new TLegend(0.3,0.2,0.48,0.45,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04); 
	leg->AddEntry((TObject*)0,"No selection cuts","");
	leg->AddEntry(h1,"#Gamma/M_{S} = 0.43%","L");
	leg->AddEntry(h2,"#Gamma/M_{S} = 1.5%","L");
	leg->AddEntry(h3,"#Gamma/M_{S} = 5%","L");
	leg->AddEntry(h4,"#Gamma/M_{S} = 10%","L");
	leg->Draw();
}

//top right
if(strcmp(var,"Maverage")==0 || strcmp(var,"Dijet_Mass_1")==0 || strcmp(var,"Dijet_Mass_2")==0)
{
	TLegend *leg = new TLegend(0.4,0.2,0.58,0.45,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04); 
	leg->AddEntry((TObject*)0,"No selection cuts","");
	leg->AddEntry(h1,"#Gamma/M_{S} = 0.43%","L");
	leg->AddEntry(h2,"#Gamma/M_{S} = 1.5%","L");
	leg->AddEntry(h3,"#Gamma/M_{S} = 5%","L");
	leg->AddEntry(h4,"#Gamma/M_{S} = 10%","L");
	leg->Draw();
}

//bottom left
if(strcmp(var,"DeltaEtaJJ")==0 || strcmp(var,"DeltaPhiJJ")==0 || strcmp(var,"Masymmetry")==0 || strcmp(var,"pT")==0 || strcmp(var,"phi")==0)
{
	TLegend *leg = new TLegend(0.16,0.2,0.38,0.45,"");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.04); 
	leg->AddEntry((TObject*)0,"No selection cuts","");
	leg->AddEntry(h1,"#Gamma/M_{S} = 0.43%","L");
	leg->AddEntry(h2,"#Gamma/M_{S} = 1.5%","L");
	leg->AddEntry(h3,"#Gamma/M_{S} = 5%","L");
	leg->AddEntry(h4,"#Gamma/M_{S} = 10%","L");
	leg->Draw();
}


cms->Draw();
lumileg->Draw();
signalleg->Draw();

TLine *line = new TLine(1.1,500,1.1,30000);
line->SetLineWidth(2);
line->SetLineStyle(kDashed);
line->Draw("same");

char cname_1[1024], cname_2[1024];


sprintf(cname_1,"output/Wide_Resonances_Run2_Final/plots/acceptance_degradation/Suu-Diquark_S%d_chi%d_diff_widths_NoSelectionCuts_%s.png",Suu,Chi,var);
sprintf(cname_2,"output/Wide_Resonances_Run2_Final/plots/acceptance_degradation/Suu-Diquark_S%d_chi%d_diff_widths_NoSelectionCuts_%s.pdf",Suu,Chi,var);

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
