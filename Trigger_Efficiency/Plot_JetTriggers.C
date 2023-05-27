#include <iostream>
#include <fstream>

void Plot_JetTriggers(char era[1024]){

TPaveText *cms = new TPaveText(0.165,0.94,0.315,0.98,"NDC");
cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
cms->SetTextFont(42);
cms->SetTextSize(0.05);
cms->SetBorderSize(0);
cms->SetFillColor(0);

char eraleg[1024];
//sprintf(eraleg,"Run2022%s, 8 fb^{-1} (13.6 TeV)",era);
sprintf(eraleg,"Run2022%s, 27 fb^{-1} (13.6 TeV)",era);

//TPaveText *lumi = new TPaveText(0.644,0.94,0.834,0.98,"NDC");
TPaveText *lumi = new TPaveText(0.627,0.94,0.827,0.98,"NDC");
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
leg2->AddText("#alpha > 0.1");

char fname0[1024], fname1[1024], fname2[1024], fname3[1024], fname4[1024];
sprintf(fname0,"2022_PromptReco_new/rootfiles/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1.root",era);
sprintf(fname1,"2022_PromptReco_new/rootfiles/seperateJetTriggers/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1_PFJet550.root",era);
sprintf(fname2,"2022_PromptReco_new/rootfiles/seperateJetTriggers/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1_AK8PFJet550.root",era);
sprintf(fname3,"2022_PromptReco_new/rootfiles/seperateJetTriggers/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1_CaloJet550.root",era);
sprintf(fname4,"2022_PromptReco_new/rootfiles/seperateJetTriggers/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1_PFHT1050.root",era);

TFile *f0 = new TFile(fname0,"READ");
TFile *f1 = new TFile(fname1,"READ");
TFile *f2 = new TFile(fname2,"READ");
TFile *f3 = new TFile(fname3,"READ");
TFile *f4 = new TFile(fname4,"READ");

TGraphAsymmErrors *gEff0 = (TGraphAsymmErrors*)f0->Get("Graph");
TGraphAsymmErrors *gEff1 = (TGraphAsymmErrors*)f1->Get("Graph");
TGraphAsymmErrors *gEff2 = (TGraphAsymmErrors*)f2->Get("Graph");
TGraphAsymmErrors *gEff3 = (TGraphAsymmErrors*)f3->Get("Graph");
TGraphAsymmErrors *gEff4 = (TGraphAsymmErrors*)f4->Get("Graph");

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

gEff0->SetLineColor(kRed+1);  
gEff0->SetMarkerColor(kRed+1);
gEff0->SetMarkerSize(1.5);
gEff0->SetLineWidth(4);

gEff1->SetLineColor(kBlue+1);  
gEff1->SetMarkerColor(kBlue+1);
gEff1->SetMarkerSize(1.5);
gEff1->SetLineWidth(2);

gEff2->SetLineColor(kMagenta+1);  
gEff2->SetMarkerColor(kMagenta+1);
gEff2->SetMarkerSize(1.5);
gEff2->SetLineWidth(2);

gEff3->SetLineColor(kOrange+1);  
gEff3->SetMarkerColor(kOrange+1);
gEff3->SetMarkerSize(1.5);
gEff3->SetLineWidth(2);

gEff4->SetLineColor(kGreen+1);  
gEff4->SetMarkerColor(kGreen+1);
gEff4->SetMarkerSize(1.5);
gEff4->SetLineWidth(2);

gEff0->Draw("same e");
gEff1->Draw("same e");
gEff2->Draw("same e");
gEff3->Draw("same e");
gEff4->Draw("same e");

cms->Draw();
lumi->Draw();
leg1->Draw();
leg2->Draw();

TCanvas *c2 = new TCanvas("c2","",1200,600);
c2->cd();
TLegend *legend = new TLegend(0.01,0.01,0.99,0.99,"");
legend->SetBorderSize(0);
legend->SetTextSize(0.04);
legend->SetHeader("Trigger efficiency = ");
legend->AddEntry(gEff0,"#frac{PassMu50 && (PassPFJet550 || PassAK8PFJet550 || PassCaloJet550 || PassPFHT1050)}{PassMu50}","PE2");
legend->AddEntry(gEff1,"#frac{PassMu50 && PassPFJet550}{PassMu50}","PE2");
legend->AddEntry(gEff2,"#frac{PassMu50 && PassAK8PFJet550}{PassMu50}","PE2");
legend->AddEntry(gEff3,"#frac{PassMu50 && PassCaloJet550}{PassMu50}","PE2");
legend->AddEntry(gEff4,"#frac{PassMu50 && PassPFHT1050}{PassMu50}","PE2");
legend->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"2022_PromptReco_new/plots/seperateJetTriggers/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1.png",era);
sprintf(cname2,"2022_PromptReco_new/plots/seperateJetTriggers/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1.pdf",era);

c->SaveAs(cname1);
c->SaveAs(cname2);

c2->SaveAs("2022_PromptReco_new/plots/seperateJetTriggers/legend_canvas.png");
c2->SaveAs("2022_PromptReco_new/plots/seperateJetTriggers/legend_canvas.pdf");


}
