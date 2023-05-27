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

void Plot_Data(){

char fname[1024];
sprintf(fname,"Histos_4jets_2022Data_Athens.root");

TPaveText *cms = new TPaveText(0.17,0.92,0.32,0.96,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TFile *f = new TFile(fname,"READ");
cout << "File used: " << fname << endl;


/*TH1D *hall = (TH1D*)f->Get("h_FourjetMass_AllData");
TH1D *hB = (TH1D*)f->Get("h_FourjetMass_eraB");
TH1D *hC = (TH1D*)f->Get("h_FourjetMass_eraC");
TH1D *hD = (TH1D*)f->Get("h_FourjetMass_eraD");
TH1D *hE = (TH1D*)f->Get("h_FourjetMass_eraE");
TH1D *hF = (TH1D*)f->Get("h_FourjetMass_eraF");
TH1D *hG = (TH1D*)f->Get("h_FourjetMass_eraG");
*/

TH1D *hall = (TH1D*)f->Get("h_AverageDijetMass_AllData");
TH1D *hB = (TH1D*)f->Get("h_AverageDijetMass_eraB");
TH1D *hC = (TH1D*)f->Get("h_AverageDijetMass_eraC");
TH1D *hD = (TH1D*)f->Get("h_AverageDijetMass_eraD");
TH1D *hE = (TH1D*)f->Get("h_AverageDijetMass_eraE");
TH1D *hF = (TH1D*)f->Get("h_AverageDijetMass_eraF");
TH1D *hG = (TH1D*)f->Get("h_AverageDijetMass_eraG");


TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetTickx(1);
c->SetTicky(1);
c->SetLogy(1);

hall->SetTitle("");
hall->SetStats(0);
//hall->GetXaxis()->SetRangeUser(1607, 9067);
hall->GetXaxis()->SetRangeUser(1, 3019);
hall->GetYaxis()->SetTitle("Entries");
//hall->GetXaxis()->SetTitle("Four-jet mass [GeV]");
hall->GetXaxis()->SetTitle("Average dijet mass [GeV]");
hall->GetYaxis()->SetTitleSize(0.055);
hall->GetXaxis()->SetTitleSize(0.055);
hall->GetYaxis()->SetTitleOffset(0.85);
hall->GetXaxis()->SetTitleOffset(0.85);
hall->SetMarkerColor(kBlack);
hall->SetMarkerStyle(8);
hall->SetLineColor(kBlack);
hall->GetYaxis()->SetLabelSize(0.04);
hall->SetMinimum(0.5);
//h1->SetMaximum(100000);

hB->SetMarkerColor(kGreen+2);
hB->SetMarkerStyle(8);
hB->SetLineColor(kGreen+2);

hC->SetMarkerColor(2);
hC->SetMarkerStyle(8);
hC->SetLineColor(2);

hD->SetMarkerColor(4);
hD->SetMarkerStyle(8);
hD->SetLineColor(4);

hE->SetMarkerColor(kYellow+2);
hE->SetMarkerStyle(8);
hE->SetLineColor(kYellow+2);

hF->SetMarkerColor(6);
hF->SetMarkerStyle(8);
hF->SetLineColor(6);

hG->SetMarkerColor(36);
hG->SetMarkerStyle(8);
hG->SetLineColor(36);

hall->Draw("PE1");
hB->Draw("PE1 same");
hC->Draw("PE1 same");
hD->Draw("PE1 same");
hE->Draw("PE1 same");
hF->Draw("PE1 same");
hG->Draw("PE1 same");
hall->Draw("PE1 same");

char legname[1024];
sprintf(legname,"All analysis cuts");

TLegend *leg = new TLegend(0.55,0.45,0.8,0.85,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.05);
leg->SetHeader(legname);
leg->AddEntry(hall,"All data","PE");
leg->AddEntry(hB,"era B","PE");
leg->AddEntry(hC,"era C","PE");
leg->AddEntry(hD,"era D","PE");
leg->AddEntry(hE,"era E","PE");
leg->AddEntry(hF,"era F","PE");
leg->AddEntry(hG,"era G","PE");
leg->Draw();

cms->Draw();

TPaveText *lumileg = new TPaveText(0.605,0.92,0.875,0.96,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->AddText("34.7 fb^{-1} (13.6 TeV)");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);
lumileg->Draw();

char cname_1[1024], cname_2[1024];

//sprintf(cname_1,"FourjetMass_AllData.png");
//sprintf(cname_2,"FourjetMass_AllData.pdf");

sprintf(cname_1,"AverageDijetMass_AllData.png");
sprintf(cname_2,"AverageDijetMass_AllData.pdf");

c->SaveAs(cname_1);
c->SaveAs(cname_2);

}
