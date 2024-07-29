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

void Plot_SignalShapes_vsMassAndWidth(double alpha_true, double Suu1, double Suu2, double Suu3, int alphabin){

double ymax, yoffset, line_ymin, line_ymax;

if(alphabin==0) {ymax=3.09; yoffset=-0.1; line_ymin=1.358; line_ymax=2.558;}
if(alphabin!=0) {ymax=4.29; yoffset=-0.15; line_ymin=1.945; line_ymax=3.55;}

double Suu[3] = {Suu1, Suu2, Suu3};

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,  //<--48th bin
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, //<--71st bin
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,  //<-94th bin
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};


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

char alphabin_name[1024], alphaleg[1024];
if (alphabin==1) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.10 < #alpha < 0.12");}
if (alphabin==2) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.12 < #alpha < 0.14");}
if (alphabin==3) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.14 < #alpha < 0.16");}
if (alphabin==4) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.16 < #alpha < 0.18");}
if (alphabin==5) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.18 < #alpha < 0.20");}
if (alphabin==6) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.20 < #alpha < 0.22");}
if (alphabin==7) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.22 < #alpha < 0.24");}
if (alphabin==8) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.24 < #alpha < 0.26");}
if (alphabin==9) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.26 < #alpha < 0.28");}
if (alphabin==10) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.28 < #alpha < 0.30");}
if (alphabin==11) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.30 < #alpha < 0.32");}
if (alphabin==12) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.32 < #alpha < 0.34");}
if (alphabin==13) {sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#alpha > 0.34");}
if (alphabin==0) {sprintf(alphabin_name,"alphagt0p1"); sprintf(alphaleg,"#alpha > 0.1");}


char fname1[3][1024], fname2[3][1024], fname3[3][1024], fname4[3][1024];
TFile *f1[3], *f2[3], *f3[3], *f4[3];
TH1D *h1[3], *h2[3], *h3[3], *h4[3];
TH1D *h1_1GeV[3];

for(int i=0; i<3; i++)
{

    if(Suu[i]!=10000 && Suu[i]!=11000)
    {
        if(alphabin==0)
        {
            sprintf(fname1[i], "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/ResonanceShapes_Suu%.0f_Chi%.0f_SR_noslices.root", alpha_true_name, Suu[i], Suu[i]*alpha_true);
        }
        else
        {
            sprintf(fname1[i], "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/ResonanceShapes_Suu%.0f_Chi%.0f_SR_%s.root", alpha_true_name, Suu[i], Suu[i]*alpha_true, alphabin_name);
        }
    }
    else
    {
        sprintf(fname1[i], "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Narrow_Resonance_Search/signals_13bins/alpha%s/nominal/ResonanceShapes_Summer20UL18_Suu-Diquark_S-%.0f_chi-%.0f_%s.root", alpha_true_name, Suu[i], Suu[i]*alpha_true, alphabin_name);
    }

    sprintf(fname2[i], "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p015_S-%.0f_chi-%.0f_%s.root", alpha_true_name, Suu[i], Suu[i]*alpha_true, alphabin_name);
    sprintf(fname3[i], "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p05_S-%.0f_chi-%.0f_%s.root", alpha_true_name, Suu[i], Suu[i]*alpha_true, alphabin_name);
    sprintf(fname4[i], "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/signal_histos/alpha%s/ResonanceShapes_NOMINAL_Suu-Diquark_W-0p1_S-%.0f_chi-%.0f_%s.root", alpha_true_name, Suu[i], Suu[i]*alpha_true, alphabin_name);


    f1[i] = new TFile(fname1[i],"read");
    f2[i] = new TFile(fname2[i],"read");
    f3[i] = new TFile(fname3[i],"read");
    f4[i] = new TFile(fname4[i],"read");
   
    cout << "Suu = " << Suu[i] << " GeV: File 1 = " << fname1[i] << endl;
    cout << "Suu = " << Suu[i] << " GeV: File 2 = " << fname2[i] << endl;
    cout << "Suu = " << Suu[i] << " GeV: File 3 = " << fname3[i] << endl;
    cout << "Suu = " << Suu[i] << " GeV: File 4 = " << fname4[i] << endl;


    if(Suu[i]!=10000 && Suu[i]!=11000)
    {
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
    }
    else
    {
        h1[i] = (TH1D*)f1[i]->Get("h_FourjetMass");
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
    
    cout << "Suu = " << Suu[i] << " GeV, h1 CONT integral = " << h1[i]->Integral() << endl;
    cout << "Suu = " << Suu[i] << " GeV, h1 MATH integral = " << h1[i]->Integral("width") << endl;
    
    cout << "Suu = " << Suu[i] << " GeV, h2 CONT integral = " << h2[i]->Integral() << endl;
    cout << "Suu = " << Suu[i] << " GeV, h2 MATH integral = " << h2[i]->Integral("width") << endl;
    
    cout << "Suu = " << Suu[i] << " GeV, h3 CONT integral = " << h3[i]->Integral() << endl;
    cout << "Suu = " << Suu[i] << " GeV, h3 MATH integral = " << h3[i]->Integral("width") << endl;
    
    cout << "Suu = " << Suu[i] << " GeV, h4 CONT integral = " << h4[i]->Integral() << endl;
    cout << "Suu = " << Suu[i] << " GeV, h4 MATH integral = " << h4[i]->Integral("width") << endl;

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
frame->GetXaxis()->SetTitleSize(0.07);
frame->GetXaxis()->SetTitleOffset(0.8);
frame->GetXaxis()->SetTitle("Four-jet mass [TeV]");
frame->GetYaxis()->SetTitleSize(0.058);
frame->GetYaxis()->SetTitleOffset(1.15);
frame->GetYaxis()->SetTitle("Normalized yield/TeV");
frame->GetXaxis()->SetLabelSize(0.05);
frame->GetYaxis()->SetLabelSize(0.045);
frame->GetYaxis()->SetLabelOffset(0.012);
frame->GetXaxis()->SetLabelOffset(1000);

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
        h1[i]->SetLineStyle(1);
        h2[i]->SetLineStyle(1);
        h3[i]->SetLineStyle(1);
        h4[i]->SetLineStyle(1);
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
        h1[i]->SetLineStyle(7);
        h2[i]->SetLineStyle(7);
        h3[i]->SetLineStyle(7);
        h4[i]->SetLineStyle(7);    
    }
    
    h1[i]->Draw("hist same");
    h2[i]->Draw("hist same");
    h3[i]->Draw("hist same");
    h4[i]->Draw("hist same");
}



TPaveText *cms1 = new TPaveText(0.22,0.915,0.47,0.965,"NDC"); 
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}"); 
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.055);
cms1->Draw();

TPaveText *cms2 = new TPaveText(0.825,0.915,0.975,0.965,"NDC"); 
cms2->AddText("13 TeV");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.055);
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

TLegend *leg1 = new TLegend(0.3,0.48,0.62,0.68);
leg1->SetFillColor(0);
leg1->SetBorderSize(0);
leg1->SetTextSize(0.04);
leg1->SetMargin(0.5);
leg1->AddEntry(h1[0], " ", "L");
leg1->AddEntry(h2[0], " ", "L");
leg1->AddEntry(h3[0], " ", "L");
leg1->AddEntry(h4[0], " ", "L");
leg1->Draw();

TLegend *leg2 = new TLegend(0.44,0.48,0.76,0.68);
leg2->SetFillColor(0);
leg2->SetBorderSize(0);
leg2->SetTextSize(0.04);
leg2->SetMargin(0.5);
leg2->AddEntry(h1[1], " ", "L");
leg2->AddEntry(h2[1], " ", "L");
leg2->AddEntry(h3[1], " ", "L");
leg2->AddEntry(h4[1], " ", "L");
leg2->Draw();

TLegend *leg3 = new TLegend(0.57,0.48,0.89,0.68);
leg3->SetFillColor(0);
leg3->SetBorderSize(0);
leg3->SetTextSize(0.035);
leg3->SetMargin(0.5);
leg3->AddEntry(h1[2], "#Gamma / M_{S} = 0.43 %", "L");
leg3->AddEntry(h2[2], "#Gamma / M_{S} = 1.5 %", "L");
leg3->AddEntry(h3[2], "#Gamma / M_{S} = 5 %", "L");
leg3->AddEntry(h4[2], "#Gamma / M_{S} = 10 %", "L");
leg3->Draw();


TPaveText *sig = new TPaveText(0.505,0.78,0.755,0.88,"NDC"); 
sig->AddText("Diquark: S #rightarrow #chi#chi #rightarrow (ug)(ug)"); 
sig->AddText("M_{#chi} / M_{S} = 0.25");
sig->SetBorderSize(0);
sig->SetTextFont(42);
sig->SetFillColor(0);
sig->SetTextSize(0.04);
sig->Draw();

TPaveText *Suu1_leg = new TPaveText(0.356,0.68,0.406,0.76,"NDC"); 
Suu1_leg->AddText("M_{S} =");
Suu1_leg->AddText("2 TeV"); 
Suu1_leg->SetBorderSize(0);
Suu1_leg->SetTextFont(42);
Suu1_leg->SetFillColor(0);
Suu1_leg->SetTextSize(0.04);
Suu1_leg->Draw();

TPaveText *Suu2_leg = new TPaveText(0.492,0.68,0.542,0.76,"NDC"); 
Suu2_leg->AddText("M_{S} =");
Suu2_leg->AddText("5 TeV"); 
Suu2_leg->SetBorderSize(0);
Suu2_leg->SetTextFont(42);
Suu2_leg->SetFillColor(0);
Suu2_leg->SetTextSize(0.04);
Suu2_leg->Draw();

TPaveText *Suu3_leg = new TPaveText(0.625,0.68,0.675,0.76,"NDC"); 
Suu3_leg->AddText("M_{S} =");
Suu3_leg->AddText("8.6 TeV"); 
Suu3_leg->SetBorderSize(0);
Suu3_leg->SetTextFont(42);
Suu3_leg->SetFillColor(0);
Suu3_leg->SetTextSize(0.04);
Suu3_leg->Draw();


TLine *line1 = new TLine(2450, line_ymin, 2450, line_ymax);
TLine *line2 = new TLine(9400, line_ymin, 9400, line_ymax);
TLine *line3 = new TLine(2450, line_ymin, 9400, line_ymin);
TLine *line4 = new TLine(2450, line_ymax, 9400, line_ymax);
line1->SetLineWidth(1);
line2->SetLineWidth(1);
line3->SetLineWidth(1);
line4->SetLineWidth(1);
line1->Draw("same");
line2->Draw("same");
line3->Draw("same");
line4->Draw("same");

TPaveText *alpha_leg = new TPaveText(0.7,0.34,0.89,0.45,"NDC"); 
if(alphabin==0)
{
    alpha_leg->AddText("All #alpha bins");
    alpha_leg->AddText("(#alpha > 0.1)");
}
else
{
    alpha_leg->AddText(alphaleg);
}
alpha_leg->SetBorderSize(0);
alpha_leg->SetTextFont(42);
alpha_leg->SetFillColor(0);
alpha_leg->SetTextSize(0.04);
alpha_leg->Draw();


char cname1[1024], cname2[1024];
sprintf(cname1,"output/Wide_Resonances_Run2_Final/plots/SignalShapesVsMassVsWidth_alpha%s_Suu_%.0f_%.0f_%.0f_%s.png",alpha_true_name,Suu1,Suu2,Suu3,alphabin_name);
sprintf(cname2,"output/Wide_Resonances_Run2_Final/plots/SignalShapesVsMassVsWidth_alpha%s_Suu_%.0f_%.0f_%.0f_%s.pdf",alpha_true_name,Suu1,Suu2,Suu3,alphabin_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}


