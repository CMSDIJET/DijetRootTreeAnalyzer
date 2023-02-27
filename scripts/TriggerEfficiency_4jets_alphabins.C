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

void TriggerEfficiency_4jets_alphabins(char era[1024], int alphabin)
{  
   double scale = 1.0; //makes sense only for the unprescaled trigger

   char txtname[1024];
   sprintf(txtname,"2022_PromptReco/textfiles/trig_2022_PromptReco_era%s_alpha%d.txt",era,alphabin);
   ofstream textfile(txtname);

  
   TH1F *h_Muon[2];
   TH1F *h_JetMET;


   char fnameJetMET[1024], fnameMuon[1024];
   sprintf(fnameJetMET,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/trigger_efficiency/2022_PromptReco/JetMET_Run2022%s-PromptReco.root",era);
   sprintf(fnameMuon,"root://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/trigger_efficiency/2022_PromptReco/Muon_Run2022%s-PromptReco.root",era);

   TFile *fJetMET = TFile::Open(fnameJetMET,"READ");
   TFile *fMuon = TFile::Open(fnameMuon,"READ");

 
   char hname[1024];

   sprintf(hname,"h_mjj_HLTpass_alpha%d_Mu50",alphabin);
   h_Muon[0] = (TH1F*)fMuon->Get(hname);     	

   sprintf(hname,"h_mjj_HLTpass_alpha%d_Mu50_AllJet",alphabin);
   h_Muon[1] = (TH1F*)fMuon->Get(hname);

   sprintf(hname,"h_mjj_HLTpass_alpha%d_AllJet",alphabin);
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
   sprintf(eraleg,"Run2022%s (13.6 TeV)",era);

   TPaveText *lumi = new TPaveText(0.705,0.94,0.895,0.98,"NDC");
   lumi->SetFillColor(0);
   lumi->SetBorderSize(0);
   lumi->SetTextFont(42);
   lumi->SetTextSize(0.04); 
   lumi->AddText(eraleg);

   char alphaleg[1024];
   if(alphabin==1)  sprintf(alphaleg,"0.10 < #alpha < 0.12");
   if(alphabin==2)  sprintf(alphaleg,"0.12 < #alpha < 0.14");
   if(alphabin==3)  sprintf(alphaleg,"0.14 < #alpha < 0.16");
   if(alphabin==4)  sprintf(alphaleg,"0.16 < #alpha < 0.18");
   if(alphabin==5)  sprintf(alphaleg,"0.18 < #alpha < 0.20");
   if(alphabin==6)  sprintf(alphaleg,"0.20 < #alpha < 0.22");
   if(alphabin==7)  sprintf(alphaleg,"0.22 < #alpha < 0.24");
   if(alphabin==8)  sprintf(alphaleg,"0.24 < #alpha < 0.26");
   if(alphabin==9)  sprintf(alphaleg,"0.26 < #alpha < 0.28");
   if(alphabin==10) sprintf(alphaleg,"0.28 < #alpha < 0.30");
   if(alphabin==11) sprintf(alphaleg,"0.30 < #alpha < 0.32");
   if(alphabin==12) sprintf(alphaleg,"0.32 < #alpha < 0.34");
   if(alphabin==13) sprintf(alphaleg,"#alpha > 0.34");

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
   leg2->AddText(alphaleg);


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
   leg3->AddText(alphaleg);
 
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

   TLegend *legend = new TLegend(0.6,0.35,0.9,0.5,"");
   legend->SetBorderSize(0);
   legend->SetTextSize(0.04);
   legend->AddEntry(h_Muon[1],"Numerator","L");
   legend->AddEntry(h_Muon[0],"Denominator","L");
   legend->Draw();


   char cname1[1024], cname2[1024];
   sprintf(cname1,"2022_PromptReco/plots/Numerator_vs_Denominator_2022_PromptReco_era%s_alpha%d.png",era,alphabin);
   sprintf(cname2,"2022_PromptReco/plots/Numerator_vs_Denominator_2022_PromptReco_era%s_alpha%d.pdf",era,alphabin);

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

   auto frame = c2->DrawFrame(701,0.4,5000,1.2);
   frame->GetXaxis()->SetTitleSize(0.05);
   frame->GetXaxis()->SetTitleOffset(0.95);
   frame->GetXaxis()->SetTitle("Four-jet mass [GeV]");
   frame->GetYaxis()->SetTitleSize(0.05);
   frame->GetYaxis()->SetTitleOffset(1.2);
   frame->GetYaxis()->SetTitle("Trigger efficiency");

   gEff->SetLineColor(kRed+1);  
   gEff->SetMarkerColor(kRed+1);
   gEff->SetMarkerSize(1.5);
   gEff->SetLineWidth(2);

   gEff->Draw("same e");
  
   cms->Draw();
   lumi->Draw();
   leg1->Draw();
   leg2->Draw();

   sprintf(cname1,"2022_PromptReco/plots/TriggerEfficiency_2022_PromptReco_era%s_alpha%d.png",era,alphabin);
   sprintf(cname2,"2022_PromptReco/plots/TriggerEfficiency_2022_PromptReco_era%s_alpha%d.pdf",era,alphabin);

   c2->SaveAs(cname1);
   c2->SaveAs(cname2);
 
  
   char foutname[1023];
   sprintf(foutname,"2022_PromptReco/rootfiles/TriggerEfficiency_2022_PromptReco_era%s_alpha%d.root",era,alphabin);
   TFile *fout = new TFile(foutname,"RECREATE");
   fout->cd(); 
   h_Muon[0]->Write();
   h_Muon[1]->Write();
   h_JetMET->Write();
   gEff->Write();
   fout->Close();
  
   textfile.close();
}

