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
#include "setTDRStyle.C"

void plot_info_panel(){

TCanvas *c1 = new TCanvas("c1","Signal region Data & Prediction",1800,800);
	
c1->cd();

c1->SetTopMargin(0);
c1->SetBottomMargin(0);
c1->SetLeftMargin(0.);
c1->SetRightMargin(0);



TPaveText *pave = new TPaveText(0.1,0.0,1.,0.88,"NDC"); //0.1,0.0,1.,0.91,"NDC"
// pave->SetFillColor(0);
//pave->SetLineColor(0);

pave->SetFillColor(0);
pave->SetLineColor(1);
pave->SetBorderSize(1);
pave->SetFillStyle(4100);
pave->SetTextFont(42);
pave->SetTextSize(0.12);
//pave->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}} "); //for PAS - ilias
pave->AddText("#bf{CMS}")->SetTextSize(0.25); //for PAPER - ilias
pave->AddText("Y #rightarrow XX #rightarrow (jj) (jj)");
pave->AddText("#alpha = Average dijet mass/Four-jet mass");
//pave->AddLine(0.2,0,0.2,0.99);
//pave->SetBorderSize(2);
pave->Draw("");
     	

//TLatex *cmslatex = new TLatex(0.4, 0.8, "#font[42]{#bf{CMS}}");
//cmslatex->SetTextSize(0.2);
//cmslatex->Draw();

TLegend *leg32 = new TLegend(0.6,0.91,0.98,0.92); //0.6,0.92,0.98,0.93
leg32->SetTextFont(42);
leg32->AddEntry((TObject*)0,"#bf{#bf{138 fb^{-1} (13 TeV)}}","");
leg32->SetBorderSize(0);
leg32->SetTextSize(0.1);
//leg32->Draw("same");




TFile *fout;

//fout = new TFile("pad1_margin_V3_PAS.root","RECREATE");
fout = new TFile("new_pad1_margin_V3_PAPER_FR.root","RECREATE");

fout->cd();
c1->Write();
fout->Close();

}
