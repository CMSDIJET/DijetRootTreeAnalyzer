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

#ifndef CALCULATE_PSEUDOSIGNIFICANCE_H
#define CALCULATE_PSEUDOSIGNIFICANCE_H

double Calculate_pseudosignificance(double width, double alpha_true, double Suu){

const int nMassBins = 103;
   
double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
     4509,
     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430,
     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};
     
TH1D *h_ZL = new TH1D("h_ZL","",nMassBins,massBoundaries);     
     
double events_normal;
if(Suu==2000) events_normal = 8000;
if(Suu==3000) events_normal = 2200;
if(Suu==3600) events_normal = 1500;
if(Suu==4000) events_normal = 800;
if(Suu==5000) events_normal = 350;
if(Suu==6000) events_normal = 150;
if(Suu==7000) events_normal = 70;
if(Suu==8000) events_normal = 50;
if(Suu==8400) events_normal = 60;
if(Suu==8600) events_normal = 60;
if(Suu==9000) events_normal = 40;
if(Suu==10000) events_normal = 5; //.0.1

char fnameBkg[1024], fnameSig[1024];

char width_name[1024];
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

//cout << "M(S) = " << Suu << " GeV, M(chi) = " << alpha_true*Suu << " GeV" << endl;
//cout << "Width = " << width*100. << "%" << endl;
//cout << "" << endl;

sprintf(fnameBkg,"rootfiles/QCD_RunIIFall17_DeltaEta_1p1_Masym_0p10_DR_2p0.root");
sprintf(fnameSig,"rootfiles/Suu-Diquark_W-%s_S-%.0f_chi-%.0f.root",width_name,Suu,alpha_true*Suu);

TFile *fBkg = new TFile(fnameBkg,"READ");
TFile *fSig = new TFile(fnameSig,"READ");

//cout << "File for Bkg used: " << fnameBkg << endl;
//cout << "File for Signal used: " << fnameSig << endl;
//cout << "" << endl;



TH1D *hBkg = (TH1D*)fBkg->Get("h_FourjetMass_alphagt0p1");
TH1D *hSig = (TH1D*)fSig->Get("h_FourjetMass_alphagt0p1");


char freducedname[1024];
sprintf(freducedname,"/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/JEC_Summer20UL18_MC_NOMINAL/RunIISummer20UL18_Suu-Diquark_W-%s_S-%.0f_chi-%.0f__AK4CHS_reduced_skim.root",width_name,Suu,Suu*alpha_true);
TFile *freduced = new TFile(freducedname, "read");
TTree *t = (TTree*)freduced->Get("rootTupleTree/tree");
int entries_total = t->GetEntries();

double weight_signal = (1.*events_normal)/entries_total;

//cout << "Signal weight = " << weight_signal <<endl;
 
//cout << "" << endl;

//cout << "Integral of bkg = " << hBkg->Integral() << endl;

//cout << "Integral of signal = " << hSig->Integral() << endl;




//cout << "Calculating significance ..." << endl;

double sum_chi2 = 0;

for(int massbin=1; massbin<=hBkg->GetNbinsX(); massbin++)
{
    double nBkg = hBkg->GetBinContent(massbin);
    double nSig = hSig->GetBinContent(massbin)*weight_signal;

    if(nBkg!=0)
    {
        double chi2 = -2.*nSig + 2.*(nBkg+nSig)*TMath::Log(1.+(1.*nSig/nBkg));
        sum_chi2 += chi2;
        
        h_ZL->SetBinContent(massbin, chi2);

        //cout << "Mass = [" << hBkg->GetBinLowEdge(massbin) << ", " << hBkg->GetBinLowEdge(massbin+1) << "]   , nBkg = " << nBkg << "   , nSig = " << nSig << "   , chi2 = " << chi2 << endl;

    }
    else
    {
        h_ZL->SetBinContent(massbin, 0.);
    }
}
	
double Signif = TMath::Sqrt(sum_chi2);

//cout << "" << endl;

//cout << "Pseudo significance = " << "sqrt(" << sum_chi2 << ") = " << Signif << endl;
	

 




//************************************* Plot *************************************


//cout << "" << endl;
//cout << "" << endl;
//cout << "" << endl;

//cout << "Plotting starts now ..." << endl;

//cout << "" << endl;

TPaveText *cms = new TPaveText(0.26,0.92,0.41,0.96,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.06);
cms->SetBorderSize(0);
cms->SetFillColor(0);

TPaveText *lumileg = new TPaveText(0.84,0.92,0.99,0.96,"NDC");
lumileg->SetFillColor(0);
lumileg->SetBorderSize(0);
lumileg->AddText("13 TeV");
lumileg->SetTextFont(42);
lumileg->SetTextSize(0.05);


char legname1[1024], legname2[1024], legname3[1024];
sprintf(legname1,"M_{S} = %.1f TeV",Suu/1000.);
sprintf(legname2,"M_{#chi} = %.2f TeV",alpha_true*Suu/1000.);
sprintf(legname3,"#Gamma / M_{S} = %.1f %%",width*100.);

TPaveText *sigleg = new TPaveText(0.73,0.73,0.93,0.87,"NDC");
sigleg->SetFillColor(0);
sigleg->SetBorderSize(0);
sigleg->AddText(legname1);
sigleg->AddText(legname2);
sigleg->AddText(legname3);
sigleg->SetTextFont(42);
sigleg->SetTextSize(0.04);


TCanvas *c = new TCanvas("c","",800,700);
c->cd()->SetLogy(1);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.02);

for(int massbin=1; massbin<hSig->GetNbinsX(); massbin++)
{
    double nSig = hSig->GetBinContent(massbin)*weight_signal;
    hSig->SetBinContent(massbin, nSig);
}

//cout << "Bkg histo integral = " << hBkg->Integral() << endl;
//cout << "Signal histo integral = " << hSig->Integral() << endl;

hBkg->SetTitle("");
hBkg->SetStats(0);
hBkg->GetYaxis()->SetTitle("Events");
hBkg->GetYaxis()->SetTitleSize(0.05);
hBkg->GetYaxis()->SetTitleOffset(0.9);
hBkg->GetXaxis()->SetRangeUser(1607, 11571);
hBkg->GetXaxis()->SetTitle("Four-jet mass [GeV]");
hBkg->GetXaxis()->SetTitleSize(0.05);
hBkg->GetXaxis()->SetTitleOffset(0.9);
hBkg->GetYaxis()->SetRangeUser(0.000005,100000);

hBkg->SetLineColor(kBlack);
hBkg->SetLineWidth(3);

hSig->SetLineColor(kViolet);
hSig->SetLineWidth(3);
//hSig->SetLineStyle(kDashed);
	
hBkg->Draw("hist");
hSig->Draw("hist same");


char legname4[1024], legname5[1024];
sprintf(legname4,"QCD (%.0f events)",hBkg->Integral());
sprintf(legname5,"Signal (%.2f events)",hSig->Integral());

TLegend *leg = new TLegend(0.6,0.55,0.8,0.65,"");
leg->SetBorderSize(0);
leg->SetTextSize(0.04);
leg->AddEntry(hBkg,legname4,"L");
leg->AddEntry(hSig,legname5,"L");
leg->Draw();

char legname6[1024], legname7[1024];
sprintf(legname6, "Z_{L} = \\sqrt{\\sum_{i=1}^{nMassBins}Z_{L}^{i}} =");
sprintf(legname7, "= \\sqrt{ \\sum_{i=1}^{nMassBins}(-2S_{i}+2(S_{i}+B_{i})\\ln{(1+\\frac{S_{i}}{B_{i}})}) } = %.3f", Signif);



TLatex *signifleg = new TLatex();
signifleg->SetTextFont(42);
signifleg->SetTextSize(0.035);
signifleg->DrawLatex(3000, 0.001, legname6);
signifleg->DrawLatex(2300, 0.00008, legname7);

cms->Draw();
lumileg->Draw();
sigleg->Draw();

char cname1[1024], cname2[1024];

sprintf(cname1,"../output/Wide_Resonances_Run2_Final/plots/diquark_cross_section/QCDBkg_vs_S%.0f_chi%.0f_W-%s.png",Suu,alpha_true*Suu,width_name);
sprintf(cname2,"../output/Wide_Resonances_Run2_Final/plots/diquark_cross_section/QCDBkg_vs_S%.0f_chi%.0f_W-%s.pdf",Suu,alpha_true*Suu,width_name);

//c->SaveAs(cname1);
//c->SaveAs(cname2);



//************************************* Plot *************************************


//cout << "" << endl;
//cout << "" << endl;
//cout << "" << endl;

//cout << "Plotting starts now ..." << endl;

//cout << "" << endl;

TPaveText *cms2 = new TPaveText(0.27,0.92,0.42,0.96,"NDC");
cms2->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}");
cms2->SetTextFont(42);
cms2->SetTextSize(0.06);
cms2->SetBorderSize(0);
cms2->SetFillColor(0);



TCanvas *c2 = new TCanvas("c2","",800,700);
c2->cd()->SetLogy(1);
c2->SetTickx(1);
c2->SetTicky(1);
c2->SetRightMargin(0.02);
c2->SetLeftMargin(0.12);

h_ZL->SetTitle("");
h_ZL->SetStats(0);
//h_ZL->GetYaxis()->SetTitle("Z_{L}^{i} = -2S_{i}+2(S_{i}+B_{i})\\ln{(1+\\frac{S_{i}}{B_{i}})}");
h_ZL->GetYaxis()->SetTitle("Z_{L}^{i}");
h_ZL->GetYaxis()->SetTitleSize(0.045);
h_ZL->GetYaxis()->SetTitleOffset(1.1);
h_ZL->GetXaxis()->SetRangeUser(1607, 11571);
h_ZL->GetXaxis()->SetTitle("Four-jet mass [GeV]");
h_ZL->GetXaxis()->SetTitleSize(0.05);
h_ZL->GetXaxis()->SetTitleOffset(0.9);
h_ZL->GetYaxis()->SetRangeUser(0.000005,1000);

h_ZL->SetLineColor(kBlack);
h_ZL->SetLineWidth(3);
	
h_ZL->Draw("hist");

cms2->Draw();
lumileg->Draw();
sigleg->Draw();

//cout << "h_ZL integral = " << h_ZL->Integral(1, 103) << endl;

int count = 1;
double perc = TMath::Sqrt(h_ZL->Integral(count, 103))/TMath::Sqrt(h_ZL->Integral());
//cout << "count = " << count << " , perc = " << perc << endl;
while(perc>0.99)
{    
    perc = TMath::Sqrt(h_ZL->Integral(count, 103))/TMath::Sqrt(h_ZL->Integral());
    //cout << "count = " << count << " , perc = " << perc << endl;
    count++;
}

//cout << "count = " << count << endl;

TLine *line = new TLine(h_ZL->GetBinLowEdge(count-2), 0.000005, h_ZL->GetBinLowEdge(count-2), h_ZL->GetBinContent(count-2));
line->SetLineWidth(3);
line->SetLineColor(kRed);
line->Draw("same");


TBox *box;
for(int i=count-2; i<=103; i++)
{
    box = new TBox(h_ZL->GetBinLowEdge(i), 0.000005, h_ZL->GetBinLowEdge(i+1), h_ZL->GetBinContent(i));
    box->SetFillColor(kRed); 
    box->SetFillStyle(3244);     
    box->SetLineColor(kRed);
    box->Draw("same");
}


char textleg1[1024], textleg2[1024], textleg3[1024];
sprintf(textleg1, "Z_{L}^{total} = #sqrt{Total integral} = %.3f", TMath::Sqrt(h_ZL->Integral()));
sprintf(textleg2, "Z_{L}^{shaded area} = #sqrt{Shaded area integral} = %.3f", TMath::Sqrt(h_ZL->Integral(count-2, 103)));
sprintf(textleg3, "Z_{L}^{M_{4J} #geq %.0f GeV} / Z_{L}^{total} = %.3f > 99%%",h_ZL->GetBinLowEdge(count-2), TMath::Sqrt(h_ZL->Integral(count-2, 103))/TMath::Sqrt(h_ZL->Integral()));


TPaveText *text = new TPaveText(0.15,0.65,0.35,0.85,"NDC");
text->AddText(textleg1);
text->AddText(textleg2);
text->AddText(textleg3);
text->SetTextFont(42);
text->SetTextSize(0.035);
text->SetBorderSize(0);
text->SetFillColor(0);
text->SetTextAlign(11);

text->Draw();

char cname3[1024], cname4[1024];

sprintf(cname3,"../output/Wide_Resonances_Run2_Final/plots/diquark_cross_section/keep_60percent_of_signif/ZLi_vs_Mass_S%.0f_chi%.0f_W-%s.png",Suu,alpha_true*Suu,width_name);
sprintf(cname4,"../output/Wide_Resonances_Run2_Final/plots/diquark_cross_section/keep_60percent_of_signif/ZLi_vs_Mass_S%.0f_chi%.0f_W-%s.pdf",Suu,alpha_true*Suu,width_name);

//c2->SaveAs(cname3);
//c2->SaveAs(cname4);

double output_value = count-2;

//cout << output_value << endl;

return output_value;
	
}

#endif

