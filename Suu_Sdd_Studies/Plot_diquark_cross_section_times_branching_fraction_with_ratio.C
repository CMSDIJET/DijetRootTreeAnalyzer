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

void Plot_diquark_cross_section_times_branching_fraction_with_ratio(double width){

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

double mass[11] = {2, 3, 4, 5, 6, 7, 8, 8.4, 8.6, 9, 10};
//double mass[10] = {2, 3, 4, 5, 6, 7, 8, 8.4, 9, 10};

double sigmaB_Suu[11], sigmaB_Sdd[11], sigmaB_ratio[11];
//double sigmaB_Suu[10], sigmaB_Sdd[10], sigmaB_ratio[10];

if(width==0.0043)
{
    double tempSuu[] = {2.6948609, 0.48931885, 0.10194526, 0.021128, 0.0040150260, 6.601e-04, 8.727e-05, 3.55e-05, 8.410e-06, 5.147e-07};
    double tempSdd[] = {0.4605, 0.05611, 0.007906, 0.001088, 0.0001392, 1.713e-05, 2.163e-06, 9.525e-07, 2.841e-07, 4.271e-08};
    std::copy(std::begin(tempSuu), std::end(tempSuu), sigmaB_Suu);
    std::copy(std::begin(tempSdd), std::end(tempSdd), sigmaB_Sdd);
}
else if(width==0.015)
{
    double tempSuu[] = {6.803, 1.184, 0.2343, 0.04637, 0.008618, 0.001472, 0.0002256, 0.0001053, 7.299e-05, 3.425e-05, 6.057e-06};
    double tempSdd[] = {1.593, 0.1939, 0.0274, 0.003854, 0.0005202, 6.897e-05, 1.025e-05, 4.905e-06, 3.413e-06, 1.706e-06, 3.269e-07};
    std::copy(std::begin(tempSuu), std::end(tempSuu), sigmaB_Suu);
    std::copy(std::begin(tempSdd), std::end(tempSdd), sigmaB_Sdd);
}
else if(width==0.05)
{
    double tempSuu[] = {21.95, 3.824, 0.7692, 0.1584, 0.03136, 0.00598, 0.00113, 0.0005934, 0.0004323, 0.0002316, 5.584e-05};
    double tempSdd[] = {5.143, 0.6367, 0.09294, 0.01389, 0.002099, 0.0003344, 6.092e-05, 3.207e-05, 2.337e-05, 1.267e-05, 2.97e-06};
    std::copy(std::begin(tempSuu), std::end(tempSuu), sigmaB_Suu);
    std::copy(std::begin(tempSdd), std::end(tempSdd), sigmaB_Sdd);
}
else if(width==0.1)
{
    double tempSuu[] = {42.2, 7.396, 1.506, 0.3228, 0.06893, 0.01449, 0.003184, 0.001785, 0.001345, 0.0007704, 0.000207};
    double tempSdd[] = {9.918, 1.238, 0.1886, 0.03042, 0.005028, 0.0009225, 0.0001918, 0.0001044, 7.817e-05, 4.426e-05, 1.089e-05};
    std::copy(std::begin(tempSuu), std::end(tempSuu), sigmaB_Suu);
    std::copy(std::begin(tempSdd), std::end(tempSdd), sigmaB_Sdd);
}


for(int i=0; i<11; i++)
//for(int i=0; i<10; i++)
{
    sigmaB_ratio[i] = sigmaB_Suu[i]/sigmaB_Sdd[i];
}  


TGraph *gr_sigmaB_Suu = new TGraph(11, mass, sigmaB_Suu);
TGraph *gr_sigmaB_Sdd = new TGraph(11, mass, sigmaB_Sdd);
//TGraph *gr_sigmaB_Suu = new TGraph(10, mass, sigmaB_Suu);
//TGraph *gr_sigmaB_Sdd = new TGraph(10, mass, sigmaB_Sdd);


gr_sigmaB_Suu->SetLineColor(kRed+1);
gr_sigmaB_Sdd->SetLineColor(kGreen+2);

gr_sigmaB_Suu->SetMarkerColor(kRed+1);
gr_sigmaB_Sdd->SetMarkerColor(kGreen+2);

gr_sigmaB_Suu->SetLineWidth(3);
gr_sigmaB_Sdd->SetLineWidth(3);

gr_sigmaB_Suu->SetLineStyle(1);
gr_sigmaB_Sdd->SetLineStyle(1);

gr_sigmaB_Suu->SetMarkerStyle(8);
gr_sigmaB_Sdd->SetMarkerStyle(8);



TGraph *gr_sigmaB_ratio = new TGraph(11, mass, sigmaB_ratio);
//TGraph *gr_sigmaB_ratio = new TGraph(10, mass, sigmaB_ratio);

gr_sigmaB_ratio->SetLineColor(kBlack);
gr_sigmaB_ratio->SetMarkerColor(kBlack);
gr_sigmaB_ratio->SetLineWidth(3);
gr_sigmaB_ratio->SetLineStyle(1);
gr_sigmaB_ratio->SetMarkerStyle(8);



TPaveText *cms1 = new TPaveText(0.227,0.95,0.527,0.98,"NDC"); 
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}"); 
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.065);

TPaveText *cms2 = new TPaveText(0.815,0.95,0.925,0.98,"NDC"); 
cms2->AddText("(13 TeV)");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.06);
cms2->SetTextFont(42);


TPaveText *pave1 = new TPaveText(0.5, 0.82, 0.93, 0.86,"NDC");
pave1->SetTextAlign(31);
pave1->AddText("LO (MadGraph)");
pave1->SetFillColor(0);
pave1->SetBorderSize(0);
pave1->SetTextSize(0.04);
pave1->SetTextFont(42);

TPaveText *pave2 = new TPaveText(0.55, 0.63, 0.93, 0.78,"NDC");
pave2->SetTextAlign(31);
pave2->AddText("lhapdf = 325300");
pave2->AddText("NNPDF 3.1 NNLO PDF");
pave2->AddText("with #alpha_{S} = 0.118");
pave2->SetFillColor(0);
pave2->SetBorderSize(0);
pave2->SetTextSize(0.04);
pave2->SetTextFont(42);


/*
TPaveText *pave1 = new TPaveText(0.5, 0.72, 0.93, 0.86,"NDC");
pave1->SetTextAlign(31);
pave1->AddText("For S_{uu} model:");
pave1->AddText("NLO for M_{S} #geq 6 TeV");
pave1->AddText("LO (lhapdf = 315000) #times 1.47 for M_{S} < 6 TeV");
pave1->SetFillColor(0);
pave1->SetBorderSize(0);
pave1->SetTextSize(0.04);
pave1->SetTextFont(42);

TPaveText *pave2 = new TPaveText(0.55, 0.52, 0.93, 0.67,"NDC");
pave2->SetTextAlign(31);
pave2->AddText("For S_{dd} model:");
pave2->AddText("LO (MadGraph)");
pave2->AddText("lhapdf = 325300");
pave2->SetFillColor(0);
pave2->SetBorderSize(0);
pave2->SetTextSize(0.04);
pave2->SetTextFont(42);
*/

TCanvas *c1 = new TCanvas("c1","c1",700,800);
c1->cd();
c1->Draw();

TPad *main_panel = new TPad("main_panel", "main_panel", 0, 0.27, 1, 1);
main_panel->SetTickx(1);
main_panel->SetTicky(1);
main_panel->SetLogy(1);
main_panel->SetRightMargin(0.05);
main_panel->SetLeftMargin(0.15);
main_panel->SetTopMargin(0.08);
main_panel->SetBottomMargin(0.001);
main_panel->Draw();

TPad *ratio_panel = new TPad("ratio_panel", "ratio_panel", 0, 0, 1, 0.25);
ratio_panel->SetTickx(1);
ratio_panel->SetTicky(1);
ratio_panel->SetGridy(1);
ratio_panel->SetRightMargin(0.05);
ratio_panel->SetLeftMargin(0.15);
ratio_panel->SetTopMargin(0.);
ratio_panel->SetBottomMargin(0.3);
ratio_panel->Draw();

main_panel->cd();

auto frame1 = main_panel->DrawFrame(1.5,5e-10,10.5,1000);
frame1->GetYaxis()->SetTitleSize(0.07);
frame1->GetYaxis()->SetLabelSize(0.05);
frame1->GetYaxis()->SetTitleOffset(1.);
frame1->GetYaxis()->SetTitle("#sigma #times B [pb]");

gr_sigmaB_Suu->Draw("lp same");
gr_sigmaB_Sdd->Draw("lp same");

cms1->Draw();
cms2->Draw();
pave1->Draw();
pave2->Draw();

TLegend *leg = new TLegend(0.17,0.04,0.53,0.4);
leg->SetFillColor(0);
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->AddEntry((TObject*)0,"#alpha_{true} = 0.25","");
if(width==0.0043) leg->AddEntry((TObject*)0,"y_{uu} = y_{dd} = 0.4", "");
if(width==0.015) leg->AddEntry((TObject*)0,"y_{uu} = y_{dd} = 0.746", "");
if(width==0.05) leg->AddEntry((TObject*)0, "y_{uu} = y_{dd} = 1.364", "");
if(width==0.1) leg->AddEntry((TObject*)0, "y_{uu} = y_{dd} = 1.928", "");
if(width==0.0043) leg->AddEntry((TObject*)0, "y_{#chi} = y_{#omega} = 0.6","");
if(width==0.015) leg->AddEntry((TObject*)0, "y_{#chi} = y_{#omega} = 1.120","");
if(width==0.05) leg->AddEntry((TObject*)0, "y_{#chi} = y_{#omega} = 2.044","");
if(width==0.1) leg->AddEntry((TObject*)0, "y_{#chi} = y_{#omega} = 2.892","");
if(width==0.0043) leg->AddEntry((TObject*)0, "#Gamma / M(S_{uu}) = #Gamma / M(S_{dd}) = 0.43%","");
if(width==0.015) leg->AddEntry((TObject*)0, "#Gamma / M(S_{uu}) = #Gamma / M(S_{dd}) = 1.5%","");
if(width==0.05) leg->AddEntry((TObject*)0, "#Gamma / M(S_{uu}) = #Gamma / M(S_{dd}) = 5%","");
if(width==0.1) leg->AddEntry((TObject*)0, "#Gamma / M(S_{uu}) = #Gamma / M(S_{dd}) = 10%","");
leg->AddEntry(gr_sigmaB_Suu, "uu #rightarrow S_{uu} #rightarrow #chi#chi #rightarrow (ug)(ug)", "L");
leg->AddEntry(gr_sigmaB_Sdd, "dd #rightarrow S_{dd} #rightarrow #omega#omega #rightarrow (dg)(dg)", "L");
leg->Draw();


ratio_panel->cd();

auto frame2 = ratio_panel->DrawFrame(1.5,0.1,10.5,29.9);
frame2->GetYaxis()->SetTitleSize(0.18);
frame2->GetYaxis()->CenterTitle(1);
frame2->GetYaxis()->SetTitleOffset(0.4);
frame2->GetYaxis()->SetTitle("S_{uu} / S_{dd}");
frame2->GetXaxis()->SetLabelSize(0.12);
frame2->GetYaxis()->SetLabelSize(0.12);
frame2->GetYaxis()->SetLabelOffset(0.015);
frame2->GetXaxis()->SetTitleSize(0.095);
frame2->GetXaxis()->SetTitleOffset(0.73);
frame2->GetXaxis()->SetTitleSize(0.18);
frame2->GetYaxis()->SetNdivisions(208); //210
frame2->GetXaxis()->SetTitle("Diquark mass [TeV]");
frame2->GetXaxis()->SetTickSize(0.10);
frame2->GetYaxis()->SetTickSize(0.02);

gr_sigmaB_ratio->Draw("lp same");


char cname1[1024], cname2[1024];
sprintf(cname1, "../output/Wide_Resonances_Run2_Final/plots/Suu_Sdd_Studies/CrossSectionTimesBranchingFraction_Suu_vs_Sdd_alpha0p25_W-%s.png", width_name);
sprintf(cname2, "../output/Wide_Resonances_Run2_Final/plots/Suu_Sdd_Studies/CrossSectionTimesBranchingFraction_Suu_vs_Sdd_alpha0p25_W-%s.pdf", width_name);

c1->SaveAs(cname1);
c1->SaveAs(cname2);

}
