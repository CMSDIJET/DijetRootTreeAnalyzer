#include <iostream>
#include <fstream>

void Plot_TriggerEfficiency_Superimposed(){

TPaveText *cms = new TPaveText(0.165,0.94,0.315,0.98,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.05);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char eraleg[1024];
sprintf(eraleg,"62.22 fb^{-1} (13.6 TeV)");

TPaveText *lumi = new TPaveText(0.71,0.94,0.91,0.98,"NDC");
lumi->SetFillColor(0);
lumi->SetBorderSize(0);
lumi->SetTextFont(42);
lumi->SetTextSize(0.04); 
lumi->AddText(eraleg);

TPaveText *leg1 = new TPaveText(0.2,0.75,0.5,0.9,"NDC");
leg1->SetFillColor(0);
leg1->SetBorderSize(0);
leg1->SetTextFont(42);
leg1->SetTextSize(0.04); 
leg1->AddText("AK4 PUPPI");
leg1->AddText("p_{T} > 80 GeV, |#eta| < 2.5");

TPaveText *leg2 = new TPaveText(0.61,0.73,0.91,0.9,"NDC");
leg2->SetFillColor(0);
leg2->SetBorderSize(0);
leg2->SetTextFont(42);
leg2->SetTextSize(0.04); 
leg2->AddText("|#Delta#eta| < 1.1");
leg2->AddText("Mass asymmetry < 0.1");  
leg2->AddText("#DeltaR_{1} < 2, #DeltaR_{2} < 2");
leg2->AddText("#alpha > 0.34");

char fname1[1024], fname2[1024];
sprintf(fname1,"2022_PromptReco/JEC_Winter22Run3_RunCD_V2_DATA_and_Summer22EEPrompt22_RunFG_V1_DATA/rootfiles/TriggerEfficiency_Run2022CDEFG_PromptReco_alpha13.root");
sprintf(fname2,"2023_PromptReco/JEC_Winter23Prompt23_RunC_V2_DATA/rootfiles/TriggerEfficiency_Run2023BCD_PromptReco_alpha13.root");

TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");

TGraphAsymmErrors *gEff1 = (TGraphAsymmErrors*)f1->Get("Graph");
TGraphAsymmErrors *gEff2 = (TGraphAsymmErrors*)f2->Get("Graph");

TCanvas *c = new TCanvas("c","",800,700);
c->cd();
c->SetLogy(0);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.05);
c->SetTopMargin(0.07);
c->SetLeftMargin(0.12);

auto frame = c->DrawFrame(701,0.4,5400,1.2);
frame->GetXaxis()->SetTitleSize(0.05);
frame->GetXaxis()->SetTitleOffset(0.95);
frame->GetXaxis()->SetTitle("Four-jet mass [GeV]");
frame->GetYaxis()->SetTitleSize(0.05);
frame->GetYaxis()->SetTitleOffset(1.2);
frame->GetYaxis()->SetTitle("Trigger efficiency");

gEff1->SetLineColor(kBlue+1);  
gEff1->SetMarkerColor(kBlue+1);
gEff1->SetMarkerSize(1.5);
gEff1->SetLineWidth(2);

gEff2->SetLineColor(kOrange+1);  
gEff2->SetMarkerColor(kOrange+1);
gEff2->SetMarkerSize(1.5);
gEff2->SetLineWidth(2);

gEff1->Draw("same e");
gEff2->Draw("same e");

cms->Draw();
lumi->Draw();
leg1->Draw();
leg2->Draw();

//TLegend *legend = new TLegend(0.3,0.15,0.5,0.3,"");
TLegend *legend = new TLegend(0.78,0.15,0.91,0.3,"");
legend->SetBorderSize(0);
legend->SetTextSize(0.04);
legend->AddEntry(gEff1,"2022","LPE");
legend->AddEntry(gEff2,"2023","LPE");
legend->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"2022_vs_2023_PromptReco/TriggerEfficiency_2022_vs_2023_PromptReco_alpha13.png");
sprintf(cname2,"2022_vs_2023_PromptReco/TriggerEfficiency_2022_vs_2023_PromptReco_alpha13.pdf");

c->SaveAs(cname1);
c->SaveAs(cname2);


}
