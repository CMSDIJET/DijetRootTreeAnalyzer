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
#include "TLatex.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TH1.h"

void Plot_SignalShapes_vsMassAndWidth(){

double ymax, yoffset, line_ymin, line_ymax;

ymax=3.27; 
yoffset=-0.1; 
line_ymin=1.358; 
line_ymax=2.558;

double Suu[3] = {2000, 5000, 8600};

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,  //<--48th bin
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, //<--71st bin
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,  //<-94th bin
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};


char alphabin_name[1024], alphaleg[1024];
sprintf(alphabin_name,"alphagt0p1");
sprintf(alphaleg,"#alpha > 0.1");


char fname1[3][1024], fname2[3][1024], fname3[3][1024], fname4[3][1024];
TFile *f1[3], *f2[3], *f3[3], *f4[3];
TH1D *h1[3], *h2[3], *h3[3], *h4[3];
TH1D *h1_1GeV[3];

for(int i=0; i<3; i++)
{

    sprintf(fname1[i], "files/ResonanceShapes_Suu%.0f_Chi%.0f_SR_noslices.root", Suu[i], Suu[i]*0.25);
    sprintf(fname2[i], "files/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p015_S-%.0f_chi-%.0f_alphagt0p1.root", Suu[i], Suu[i]*0.25);
    sprintf(fname3[i], "files/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p05_S-%.0f_chi-%.0f_alphagt0p1.root", Suu[i], Suu[i]*0.25);
    sprintf(fname4[i], "files/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p1_S-%.0f_chi-%.0f_alphagt0p1.root", Suu[i], Suu[i]*0.25);


    f1[i] = new TFile(fname1[i],"read");
    f2[i] = new TFile(fname2[i],"read");
    f3[i] = new TFile(fname3[i],"read");
    f4[i] = new TFile(fname4[i],"read");


    h1_1GeV[i] = (TH1D*)f1[i]->Get("h_FourjetMass1GeV");

    char tmp[1024];
    sprintf(tmp,"h1_%d",i);
        
    h1[i] = new TH1D(tmp,"",nMassBins,massBoundaries);

    double val, xval;

    for(unsigned int j=1; j<=h1_1GeV[i]->GetNbinsX(); j++)
    {
	 val  = h1_1GeV[i]->GetBinContent(j);
	 xval = h1_1GeV[i]->GetBinCenter(j);
	 h1[i]->Fill(xval,val);		
    }
        

    h2[i] = (TH1D*)f2[i]->Get("h_FourjetMass");
    h3[i] = (TH1D*)f3[i]->Get("h_FourjetMass");
    h4[i] = (TH1D*)f4[i]->Get("h_FourjetMass");

}



for(int i=0; i<3; i++)
{

    for(int bin=1; bin<=h1[i]->GetNbinsX(); bin++)
    {
        double val1 = h1[i]->GetBinContent(bin)/(h1[i]->GetBinLowEdge(bin+1)-h1[i]->GetBinLowEdge(bin));
        h1[i]->SetBinContent(bin,val1);
        
        double val2 = h2[i]->GetBinContent(bin)/(h2[i]->GetBinLowEdge(bin+1)-h2[i]->GetBinLowEdge(bin));
        h2[i]->SetBinContent(bin,val2);
        
        double val3 = h3[i]->GetBinContent(bin)/(h3[i]->GetBinLowEdge(bin+1)-h3[i]->GetBinLowEdge(bin));
        h3[i]->SetBinContent(bin,val3);
        
        double val4 = h4[i]->GetBinContent(bin)/(h4[i]->GetBinLowEdge(bin+1)-h4[i]->GetBinLowEdge(bin));
        h4[i]->SetBinContent(bin,val4);
    }

    h1[i]->Scale(1000./h1[i]->Integral(),"width");
    h2[i]->Scale(1000./h2[i]->Integral(),"width");
    h3[i]->Scale(1000./h3[i]->Integral(),"width");
    h4[i]->Scale(1000./h4[i]->Integral(),"width");
    
}


TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetLogy(0);
c->SetTickx(1);
c->SetTicky(1);
c->SetGridy(0);
c->SetRightMargin(0.03);
c->SetTopMargin(0.09);
c->SetLeftMargin(0.14);
c->SetBottomMargin(0.12);

auto frame = c->DrawFrame(526,0.0005,9726,ymax);
frame->GetXaxis()->SetTitleSize(0.06);
frame->GetXaxis()->SetTitleOffset(0.85);
frame->GetXaxis()->SetTitle("Four-jet mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.06);
frame->GetYaxis()->SetTitleOffset(1.15);
frame->GetYaxis()->SetTitle("Normalized yield/TeV");
frame->GetXaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelSize(0.045);
frame->GetYaxis()->SetLabelOffset(0.012);
frame->GetXaxis()->SetLabelOffset(1000);

h1[0]->GetXaxis()->SetRangeUser(526, 3019);
h2[0]->GetXaxis()->SetRangeUser(526, 3019);
h3[0]->GetXaxis()->SetRangeUser(526, 3019);
h4[0]->GetXaxis()->SetRangeUser(526, 3019);

h1[1]->GetXaxis()->SetRangeUser(2037, 6099);
h2[1]->GetXaxis()->SetRangeUser(2037, 6099);
h3[1]->GetXaxis()->SetRangeUser(2037, 6099);
h4[1]->GetXaxis()->SetRangeUser(2037, 6099);

h1[2]->GetXaxis()->SetRangeUser(2037, 9391);
h2[2]->GetXaxis()->SetRangeUser(2037, 9391);
h3[2]->GetXaxis()->SetRangeUser(2037, 9391);
h4[2]->GetXaxis()->SetRangeUser(2037, 9391);

for(int i=0; i<3; i++)
{
    h1[i]->SetLineWidth(3);
    h2[i]->SetLineWidth(3);
    h3[i]->SetLineWidth(3);
    h4[i]->SetLineWidth(3);
   
    
    h1[i]->SetLineColor(kBlack);
    h2[i]->SetLineColor(kRed+1);
    h3[i]->SetLineColor(kBlue-3);
    h4[i]->SetLineColor(kGreen+2);
    
    if(i==0)
    { 
        h1[i]->SetLineStyle(9);
        h2[i]->SetLineStyle(9);
        h3[i]->SetLineStyle(9);
        h4[i]->SetLineStyle(9);
    }    
    else if(i==1) 
    {
        h1[i]->SetLineStyle(2);
        h2[i]->SetLineStyle(2);
        h3[i]->SetLineStyle(2);
        h4[i]->SetLineStyle(2);
    }
    else
    {
        h1[i]->SetLineStyle(1);
        h2[i]->SetLineStyle(1);
        h3[i]->SetLineStyle(1);
        h4[i]->SetLineStyle(1);    
    }
    
    //h1[i]->Draw("hist same");
    h2[i]->Draw("hist same");
    h3[i]->Draw("hist same");
    h4[i]->Draw("hist same");
}


TPaveText *cms1 = new TPaveText(0.16,0.81,0.36,0.84,"NDC");
cms1->AddText("#splitline{#bf{CMS}}{#scale[0.7]{#it{Simulation}}}"); 
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.07);
cms1->Draw();

TPaveText *cms2 = new TPaveText(0.842,0.915,0.952,0.965,"NDC"); 
cms2->AddText("(13 TeV)");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.05);
cms2->SetTextFont(42);
cms2->Draw();


char xLab_leg[1024];
TLatex *xLab = new TLatex();
xLab->SetTextAlign(22);
xLab->SetTextSize(0.05);
xLab->SetTextFont(42);
xLab->SetTextSize(0.05);
for(int mass=1000; mass<=9000; mass=mass+1000)
{
    sprintf(xLab_leg,"%.0f",mass/1000.);
    xLab->DrawLatex(mass, yoffset, xLab_leg);
}

TLegend *leg1 = new TLegend(0.3,0.445,0.62,0.645);
leg1->SetFillColor(0);
leg1->SetBorderSize(0);
leg1->SetTextSize(0.04);
leg1->SetMargin(0.5);
leg1->AddEntry(h2[0], " ", "L");
leg1->AddEntry(h3[0], " ", "L");
leg1->AddEntry(h4[0], " ", "L");
leg1->Draw();

TLegend *leg2 = new TLegend(0.44,0.445,0.76,0.645);
leg2->SetFillColor(0);
leg2->SetBorderSize(0);
leg2->SetTextSize(0.04);
leg2->SetMargin(0.5);
leg2->AddEntry(h2[1], " ", "L");
leg2->AddEntry(h3[1], " ", "L");
leg2->AddEntry(h4[1], " ", "L");
leg2->Draw();

TLegend *leg3 = new TLegend(0.57,0.445,0.89,0.645);
leg3->SetFillColor(0);
leg3->SetBorderSize(0);
leg3->SetTextSize(0.04);
leg3->SetMargin(0.5);
leg3->AddEntry(h2[2], "#Gamma / M_{S} = 1.5%", "L");
leg3->AddEntry(h3[2], "#Gamma / M_{S} = 5%", "L");
leg3->AddEntry(h4[2], "#Gamma / M_{S} = 10%", "L");
leg3->Draw();


TPaveText *sig = new TPaveText(0.505,0.76,0.755,0.88,"NDC"); 
sig->AddText("uu #rightarrow S_{uu} #rightarrow #chi#chi #rightarrow (ug)(ug)"); 
sig->AddText("M_{#chi} / M_{S} = 0.25");
sig->SetBorderSize(0);
sig->SetTextFont(42);
sig->SetFillColor(0);
sig->SetTextSize(0.04);
sig->Draw();

TPaveText *Suu1_leg = new TPaveText(0.356,0.645,0.406,0.725,"NDC"); 
Suu1_leg->AddText("M_{S} =");
Suu1_leg->AddText("2 TeV"); 
Suu1_leg->SetBorderSize(0);
Suu1_leg->SetTextFont(42);
Suu1_leg->SetFillColor(0);
Suu1_leg->SetTextSize(0.04);
Suu1_leg->Draw();

TPaveText *Suu2_leg = new TPaveText(0.492,0.645,0.542,0.725,"NDC"); 
Suu2_leg->AddText("M_{S} =");
Suu2_leg->AddText("5 TeV"); 
Suu2_leg->SetBorderSize(0);
Suu2_leg->SetTextFont(42);
Suu2_leg->SetFillColor(0);
Suu2_leg->SetTextSize(0.04);
Suu2_leg->Draw();

TPaveText *Suu3_leg = new TPaveText(0.625,0.645,0.675,0.725,"NDC"); 
Suu3_leg->AddText("M_{S} =");
Suu3_leg->AddText("8.6 TeV"); 
Suu3_leg->SetBorderSize(0);
Suu3_leg->SetTextFont(42);
Suu3_leg->SetFillColor(0);
Suu3_leg->SetTextSize(0.04);
Suu3_leg->Draw();


TPaveText *alpha_leg = new TPaveText(0.7,0.32,0.89,0.43,"NDC"); 
alpha_leg->AddText("All #alpha bins");
alpha_leg->AddText("(#alpha > 0.1)");
alpha_leg->SetBorderSize(0);
alpha_leg->SetTextFont(42);
alpha_leg->SetFillColor(0);
alpha_leg->SetTextSize(0.04);
alpha_leg->Draw();


char cname[1024];
sprintf(cname,"plots/Figure_003.pdf");

c->SaveAs(cname);

}


