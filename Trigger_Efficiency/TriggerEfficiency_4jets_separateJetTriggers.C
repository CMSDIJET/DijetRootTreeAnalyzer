#include <iostream>
#include <fstream>

double BetaInverse(double x,double p, double q)
{
  double result(0.0);
  double dy = 0.001;
  double eMin = 100;
  for(int i=0;i<1000;i++)
    {
      double y = i*dy;
      double e = fabs(TMath::BetaIncomplete(y,p,q)-x);
      if (e<eMin)
        {
          eMin = e;
          result = y;
        }
    }
  return result; 
}

void TriggerEfficiency_4jets_separateJetTriggers(char era[1024], char trig[1024])
{  
   double scale = 1.0; //makes sense only for the unprescaled trigger

   char txtname[1024];
   sprintf(txtname,"2022_PromptReco_new/textfiles/seperateJetTriggers/trig_2022_PromptReco_era%s_alphagt0p1_%s.txt",era,trig);
   ofstream textfile(txtname);

  
   TH1F *h_Muon[2];
   TH1F *h_JetMET;


   char fnameJetMET[1024], fnameMuon[1024];
   sprintf(fnameJetMET,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/trigger_efficiency/2022_PromptReco/JetMET_Run2022%s-PromptReco.root",era);
   sprintf(fnameMuon,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/trigger_efficiency/2022_PromptReco/new/Muon_Run2022%s-PromptReco.root",era);

   TFile *fJetMET = TFile::Open(fnameJetMET,"READ");
   TFile *fMuon = TFile::Open(fnameMuon,"READ");

 
   char hname[1024];

   sprintf(hname,"h_mjj_HLTpass_Mu50");
   h_Muon[0] = (TH1F*)fMuon->Get(hname);     	

   sprintf(hname,"h_mjj_HLTpass_%s",trig);
   h_Muon[1] = (TH1F*)fMuon->Get(hname);

   sprintf(hname,"h_mjj_HLTpass_%s",trig);
   h_JetMET = (TH1F*)fJetMET->Get(hname);



   double a  = 0.3173;
   double vx[1000], vy[1000], vexl[1000], vexh[1000], veyl[1000], veyh[1000];

   for(int i=0; i<h_Muon[0]->GetNbinsX(); i++)
   {
       double N1 = h_Muon[0]->GetBinContent(i+1);
       double N2 = h_Muon[1]->GetBinContent(i+1);
       double p  = 0;
       double eU = 0;
       double eL = 0;
       double aeff = (1-a)/2;
       double n,w;
 
       if(N1 > 0)
       { 
           p = N2/N1;
           //n = N1+N2;
           //w = N2/n;
               
           if (N1*p>100 || N1*(1-p)>100)
           { 
               eU = sqrt(p*(1-p)/N1);
               eL = sqrt(p*(1-p)/N1);
           }
           else
           {   
               eU = (1-BetaInverse(aeff,N1-N2,N2+1))-p;
               eL = p-(1-BetaInverse(1-aeff,N1-N2+1,N2));  
           }         
       }


       textfile << "Mass =  [" << h_Muon[0]->GetXaxis()->GetBinLowEdge(i+1) << " - " << h_Muon[0]->GetXaxis()->GetBinLowEdge(i+2) << "] , Numerator = " << N2 << " , Denominator = " << N1 << " , Trig. Efficiency = " << p << " , errorL = " << eL << " , errorU = " << eU << " , Inefficiency = " << 1-p << endl;


       vx[i] = h_Muon[0]->GetBinCenter(i+1);
       vy[i] = p*scale;
       vexl[i] = h_Muon[0]->GetBinWidth(i+1)/2;
       vexh[i] = h_Muon[0]->GetBinWidth(i+1)/2;      
       veyl[i] = eL*scale;
       veyh[i] = eU*scale;     
   }


   textfile << "For JetMET dataset: " << endl;

   for(int i=0; i<h_JetMET->GetNbinsX(); i++)
   {  
       double Number_of_events = h_JetMET->GetBinContent(i+1);
       if(Number_of_events>0)
       {
             textfile << "Mass = [" << h_JetMET->GetXaxis()->GetBinLowEdge(i+1) << " - " << h_JetMET->GetXaxis()->GetBinLowEdge(i+2) << "] , N = " << Number_of_events << " , 1/sqrt(N) = " << 1./sqrt(Number_of_events) << endl;
       }
       else
       {
             textfile << "Mass = [" << h_JetMET->GetXaxis()->GetBinLowEdge(i+1) << " - " << h_JetMET->GetXaxis()->GetBinLowEdge(i+2) << "] , N = " << Number_of_events << " , 1/sqrt(N) = 0" << endl;
       }
   }
    


   //Plots


   TPaveText *cms = new TPaveText(0.165,0.94,0.315,0.98,"NDC");
   cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
   cms->SetTextFont(42);
   cms->SetTextSize(0.05);
   cms->SetBorderSize(0);
   cms->SetFillColor(0);

   char eraleg[1024];
   sprintf(eraleg,"Run2022%s, 8 fb^{-1} (13.6 TeV)",era);
   //sprintf(eraleg,"Run2022%s, 27 fb^{-1} (13.6 TeV)",era);

   TPaveText *lumi = new TPaveText(0.644,0.94,0.834,0.98,"NDC");
   //TPaveText *lumi = new TPaveText(0.627,0.94,0.827,0.98,"NDC");
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


   TPaveText *leg3 = new TPaveText(0.6,0.55,0.9,0.9,"NDC");
   leg3->SetFillColor(0);
   leg3->SetBorderSize(0);
   leg3->SetTextFont(42);
   leg3->SetTextSize(0.04); 
   leg3->AddText("AK4 PUPPI");
   leg3->AddText("p_{T} > 80 GeV, |#eta| < 2.5");
   leg3->AddText("");
   leg3->AddText("|#Delta#eta| < 1.1");
   leg3->AddText("Mass asymmetry < 0.1");  
   leg3->AddText("#DeltaR_{1} < 2, #DeltaR_{2} < 2");
   leg3->AddText("#alpha > 0.1");
 
   TCanvas *c1 = new TCanvas("c1","",800,700);
   c1->cd();
   c1->SetLogy(1);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetRightMargin(0.05);
   c1->SetTopMargin(0.07);
   c1->SetLeftMargin(0.12);
  
   h_Muon[0]->GetXaxis()->SetTitle("Four-jet mass [GeV]");
   h_Muon[0]->GetYaxis()->SetTitle("Events");
   h_Muon[0]->GetXaxis()->SetRangeUser(1.,8152.);
   h_Muon[0]->SetLineColor(kBlack);
   h_Muon[0]->SetLineWidth(2);
   h_Muon[1]->SetLineColor(kRed);
   h_Muon[1]->SetLineWidth(2);
   h_Muon[0]->SetStats(0);
   h_Muon[0]->GetXaxis()->SetTitleSize(0.05);
   h_Muon[0]->GetXaxis()->SetTitleOffset(0.95);
   h_Muon[0]->GetYaxis()->SetTitleSize(0.05);
   h_Muon[0]->GetYaxis()->SetTitleOffset(1.2);
   h_Muon[0]->Draw("hist");
   h_Muon[1]->Draw("hist same");

   cms->Draw();
   lumi->Draw();
   leg3->Draw();

   char trigleg[1024];
   sprintf(trigleg,"#splitline{PassMu50 &&}{%s}",trig);

   TLegend *legend = new TLegend(0.6,0.25,0.85,0.5,"");
   legend->SetBorderSize(0);
   legend->SetTextSize(0.04);
   legend->AddEntry(h_Muon[1],trigleg,"L");
   legend->AddEntry(h_Muon[0],"PassMu50","L");
   legend->Draw();


   char cname1[1024], cname2[1024];
   sprintf(cname1,"2022_PromptReco_new/plots/seperateJetTriggers/Numerator_vs_Denominator_2022_PromptReco_era%s_alphagt0p1_%s.png",era,trig);
   sprintf(cname2,"2022_PromptReco_new/plots/seperateJetTriggers/Numerator_vs_Denominator_2022_PromptReco_era%s_alphagt0p1_%s.pdf",era,trig);

   c1->SaveAs(cname1);
   c1->SaveAs(cname2);


   TGraphAsymmErrors *gEff = new TGraphAsymmErrors(h_Muon[0]->GetNbinsX(),vx,vy,vexl,vexh,veyl,veyh);


   TCanvas *c2 = new TCanvas("c2","",800,700);
   c2->cd();
   c2->SetLogy(0);
   c2->SetTickx(1);
   c2->SetTicky(1);
   c2->SetRightMargin(0.05);
   c2->SetTopMargin(0.07);
   c2->SetLeftMargin(0.12);

   char trigtitle[1024];
   sprintf(trigtitle,"Trigger efficiency of %s",trig);

   auto frame = c2->DrawFrame(701,0.4,5400,1.2);
   frame->GetXaxis()->SetTitleSize(0.05);
   frame->GetXaxis()->SetTitleOffset(0.95);
   frame->GetXaxis()->SetTitle("Four-jet mass [GeV]");
   frame->GetYaxis()->SetTitleSize(0.05);
   frame->GetYaxis()->SetTitleOffset(1.2);
   frame->GetYaxis()->SetTitle(trigtitle);

   gEff->SetLineColor(kRed+1);  
   gEff->SetMarkerColor(kRed+1);
   gEff->SetMarkerSize(1.5);
   gEff->SetLineWidth(2);

   gEff->Draw("same e");
  
   cms->Draw();
   lumi->Draw();
   leg1->Draw();
   leg2->Draw();

   sprintf(cname1,"2022_PromptReco_new/plots/seperateJetTriggers/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1_%s.png",era,trig);
   sprintf(cname2,"2022_PromptReco_new/plots/seperateJetTriggers/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1_%s.pdf",era,trig);

   c2->SaveAs(cname1);
   c2->SaveAs(cname2);
 
  
   char foutname[1023];
   sprintf(foutname,"2022_PromptReco_new/rootfiles/seperateJetTriggers/TriggerEfficiency_2022_PromptReco_era%s_alphagt0p1_%s.root",era,trig);
   TFile *fout = new TFile(foutname,"RECREATE");
   fout->cd(); 
   h_Muon[0]->Write();
   h_Muon[1]->Write();
   h_JetMET->Write();
   gEff->Write();
   fout->Close();
  
   textfile.close();
}

