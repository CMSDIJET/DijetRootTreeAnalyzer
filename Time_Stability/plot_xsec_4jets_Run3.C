//////////////////////////////////////////////////////////////////////////////
void WeightedMean(TH1F *h, double &m, double &s, double &sm, double &ss, int mode)
{
   double w[1000],x[1000],e[1000];
   double sumx(0.0),sumx2(0.0),sumw(0.0); 
   int N(0);
  
   TF1  *fit0;
   if(mode==1) fit0 = new TF1("fit0","pol0");
   if(mode==2) fit0 = new TF1("fit0","pol1");

 //     fit0->SetLineStyle(2);
      fit0->SetLineStyle(kDashed);
      fit0->SetLineWidth(3);   
      
   for(int i=0;i<h->GetNbinsX();i++)
   {
      double y = h->GetBinContent(i+1);
      if (y>0)
      {
         x[i] = y;
         e[i] = h->GetBinError(i+1); 
         w[i] = 1/(e[i]*e[i]);
         N++;
      }
   } 
   for(int i=0;i<N;i++)
   {
      sumx  += w[i]*x[i];
      sumx2 += w[i]*x[i]*x[i];
      sumw  += w[i];
   }
   m  = sumx/sumw;
   s  = sqrt(sumx2/sumw-m*m);
   sm = 0.;
   ss = 0.; 
        
   if(mode==1 || mode==2)
   {
      h->Fit(fit0,"");//h->Fit(fit0,"NO");

//      fit0->SetLineStyle(2);
      fit0->SetLineStyle(kDashed);
      fit0->SetLineWidth(3);

      m      = fit0->GetParameter(0);
      s      = fit0->GetParError(0);
      sm     = fit0->GetParameter(1);
      ss     = fit0->GetParError(1);
  
      double prob1 = TMath::Prob(fit0->GetChisquare(),fit0->GetNDF());
      cout << " prob1  " << prob1 << " chisq " << fit0->GetChisquare() << " ndf " << fit0->GetNDF() <<  endl;
   }
}


void plot_xsec_4jets_Run3()
{ 
   char name[1000],dirname[1000];

   TFile *inf; 
   inf = TFile::Open("output_4jets/Run2022BCDEF_29p8fb-1_stability_onlyMassAndDeltaEtaCut_cert.root");

   TString histoname = "Run"; double yaxismin(0.),yaxismax(1000.); TString titly="Cross Section [pb]";TString titlx="Run index";

   TH1F *h, *h_all, *hbig;  

   // plot 
   ///////////////////////////////////////////////////////////////////////////
   
   TCanvas *c = new TCanvas("Run","",800,700);
   c->SetTickx(1);
   c->SetTicky(1);
   //c->SetGridx(1);
   //c->SetGridy(1);

   TPaveText *cms = new TPaveText(0.17,0.92,0.32,0.96,"NDC");
   cms->AddText("#bf{CMS} #scale[0.7]{#it{Preliminary}}");
   cms->SetTextFont(42);
   cms->SetTextSize(0.06);
   cms->SetBorderSize(0);
   cms->SetFillColor(0);

   TPaveText *lumileg = new TPaveText(0.664,0.92,0.864,0.96,"NDC");
   lumileg->SetFillColor(0);
   lumileg->SetBorderSize(0);
   lumileg->AddText("30 fb^{-1} (13.6 TeV)");
   lumileg->SetTextFont(42);
   lumileg->SetTextSize(0.045);
   lumileg->Draw();
   

   int RUN_NUMBERS[1000];
   double LUMI[1000];
   int NRuns(0);
      

   sprintf(name,"Cert_Run3_29p8fb-1.txt");
   ifstream txtFile;
   txtFile.open(name);
   double lumi;
   int run;

   while (!txtFile.eof())
   {
       txtFile >> run >> lumi; 
       //if(lumi>=10){
       LUMI[NRuns]=lumi;
       RUN_NUMBERS[NRuns] = run;
       cout<<NRuns<<" "<<RUN_NUMBERS[NRuns]<<" "<<LUMI[NRuns]<<endl;
       NRuns++;
       if(NRuns>=1000) cout << "NRuns>=1000 !!!!" << endl; 
       //} 
   }
   NRuns = NRuns-1; 
   cout << "NRuns: " << NRuns << endl;
 
   h = (TH1F*)inf->Get("Run");
   h_all = (TH1F*)h->Clone();


   h_all->SetTitle("");
   h_all->GetXaxis()->SetTitle(titlx);
   h_all->GetYaxis()->SetTitle(titly);
	 
   hbig = new TH1F("Run","",NRuns,0,NRuns);
   hbig->Sumw2();
	 
   for(int i=0;i<h_all->GetNbinsX();i++)
   {
      	  if(h_all->GetBinContent(i+1) == 0) continue;  
      	  int runNo(h_all->GetBinCenter(i+1));  cout<<"runNo  "<<runNo<<endl;
      	  int index(-1); 
      	  for(int j=0;j<NRuns;j++)
          {
               if(runNo == RUN_NUMBERS[j])
               { 
                  index = j;
                  continue;  
               }
          }  
      	  if(index > -1)
	  {
	       double valN = h_all->GetBinContent(i+1);
	       double y = valN/LUMI[index];  cout<<valN<<"  "<<LUMI[index]<<"  "<<y<<endl;
	       double e = y*sqrt(1./valN);
	       
	       int bin = hbig->FindBin(index);  
	       
	         hbig->SetBinContent(bin,y);
	         hbig->SetBinError(bin,e);
	   }
   }  //end of for loop 



   h_all->Draw("");

   double m,s,sm,ss;

   WeightedMean(hbig,m,s,sm,ss,1);// 2 to fit with pol1	 

   for(Int_t jj=1;jj<hbig->GetNbinsX();jj++)
   {
         double value = hbig->GetBinContent(jj);
         double diff = TMath::Abs(value-m);
         if((diff/m)>0.05) cout << " % change " << diff/m << " jj " << jj <<  " run " << RUN_NUMBERS[jj] << endl;
   }

	 
   hbig->GetXaxis()->SetTitle(titlx);
   hbig->GetYaxis()->SetTitle(titly);

   hbig->GetXaxis()->SetTitleSize(0.04);
   hbig->GetYaxis()->SetTitleSize(0.04);
   hbig->GetYaxis()->SetTitleOffset(1.1);
	 
   hbig->SetStats(0);
   //hbig->GetYaxis()->SetRangeUser(0.,2.*m+2.*s); // 5
   hbig->GetYaxis()->SetRangeUser(0.,120.);
   hbig->SetMarkerStyle(8);
   hbig->SetMarkerColor(kBlack);
   hbig->SetLineColor(kBlack);
   hbig->Draw("pe1");

   TLegend *leg1 = new TLegend(0.16,0.71,0.16,0.86,"");
   leg1->SetTextSize(0.04);
   leg1->SetBorderSize(0);
   leg1->AddEntry((TObject*)0,"Paired dijet analysis","");
   leg1->AddEntry((TObject*)0,"4 leading AK4 jets","");
   leg1->AddEntry((TObject*)0,"|#eta| < 2.5, p_{T} > 80 GeV","");
   leg1->Draw();

   //TLegend *leg2 = new TLegend(0.55,0.65,0.55,0.85,"");
   TLegend *leg2 = new TLegend(0.55,0.73,0.55,0.88,"");
   leg2->SetTextSize(0.04);
   leg2->SetBorderSize(0);
   leg2->AddEntry((TObject*)0,"M_{4j} > 1607 GeV","");
   leg2->AddEntry((TObject*)0,"|#Delta#eta| < 1.1","");
   //leg2->AddEntry((TObject*)0,"Mass asymmetry < 0.1","");
   //leg2->AddEntry((TObject*)0,"#Delta R_{1,2} < 2","");
   //leg2->AddEntry((TObject*)0,"#alpha > 0.1","");
   leg2->Draw();

   cms->Draw();
   lumileg->Draw();


   TLine *l1 = new TLine(17,0,17,30);
   l1->SetLineWidth(3);
   l1->SetLineColor(kRed);
   l1->Draw("same");

   TLine *l2 = new TLine(123,0,123,30);
   l2->SetLineWidth(3);
   l2->SetLineColor(kRed);
   l2->Draw("same");

   TLine *l3 = new TLine(168,0,168,30);
   l3->SetLineWidth(3);
   l3->SetLineColor(kRed);
   l3->Draw("same");

   TLine *l4 = new TLine(216,0,216,30);
   l4->SetLineWidth(3);
   l4->SetLineColor(kRed);
   l4->Draw("same");

   TLatex *latex = new TLatex();
   latex->SetTextFont(42);
   latex->SetTextColor(kRed);
   latex->DrawLatex(3,10,"B");
   latex->DrawLatex(60,10,"C");
   latex->DrawLatex(140,10,"D");
   latex->DrawLatex(190,10,"E");
   latex->DrawLatex(270,10,"F");


   c->SaveAs("output_4jets/4jets_xsec_vs_run_onlyMassAndDeltaEtaCut.png");
   c->SaveAs("output_4jets/4jets_xsec_vs_run_onlyMassAndDeltaEtaCut.pdf");


}
