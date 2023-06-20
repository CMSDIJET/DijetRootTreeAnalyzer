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


void plot_variables_vs_time_4jets_Run3(char var[1024])
{ 

   char yaxistitle[1024];
   double ymin, ymax, ymaxlab;

   if(strcmp(var,"NHF")==0) {sprintf(yaxistitle,"Mean NHF of the 4 leading jets");  ymin = 0; ymax = 0.5; ymaxlab = 0.3;}
   if(strcmp(var,"NEMF")==0) {sprintf(yaxistitle,"Mean NEMF of the 4 leading jets");  ymin = 0.15; ymax = 0.7; ymaxlab = 0.5;}
   if(strcmp(var,"CHF")==0) {sprintf(yaxistitle,"Mean CHF of the 4 leading jets");  ymin = 0.1; ymax = 1.; ymaxlab = 0.6;}
   if(strcmp(var,"CEMF")==0) {sprintf(yaxistitle,"Mean CEMF of the 4 leading jets");  ymin = 0; ymax = 1; ymaxlab = 0.3;}
   if(strcmp(var,"CM")==0) {sprintf(yaxistitle,"Mean charged multiplicity of the 4 leading jets");  ymin = 10; ymax = 50; ymaxlab = 30;}
   if(strcmp(var,"NM")==0) {sprintf(yaxistitle,"Mean neutral multiplicity of the 4 leading jets");  ymin = 5; ymax = 35; ymaxlab = 22;}


   char name[1000];

   TFile *inf; 
   inf = TFile::Open("output_4jets/Runs_2022CDEFG_2023BC_47p01fb-1_stability_cert.root");
 

   TH2D *h2d;
   TProfile *h;

   TH1F *hbig;


   // plot stability plots 
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
   lumileg->AddText("47 fb^{-1} (13.6 TeV)");
   lumileg->SetTextFont(42);
   lumileg->SetTextSize(0.045);
   lumileg->Draw();

   int RUN_NUMBERS[1000];
   double LUMI[1000];
   int NRuns(0);
      
   //Read file per trigger - luminosity per run 

   sprintf(name,"Cert_Run3_47fb-1.txt");
   ifstream txtFile;
   txtFile.open(name);
      
   while (!txtFile.eof())
   {         
   	txtFile >> RUN_NUMBERS[NRuns] >> LUMI[NRuns];           
      	cout<<NRuns<<" "<<RUN_NUMBERS[NRuns]<<" "<<LUMI[NRuns]<<endl;
     	NRuns++;
	if(NRuns>=1000) cout << "NRuns>=1000 !!!!" << endl;                
   }
   NRuns = NRuns-1; 
   cout << "NRuns: " << NRuns << endl;
                

   sprintf(name,"%s_vsRun",var);
   cout<<name<<endl;

   h2d = (TH2D*)inf->Get(name); 

   h = h2d->ProfileX();

   sprintf(name,"%s_vsRunIndex",var);
   hbig = new TH1F(name,"",NRuns,0,NRuns);
   hbig->Sumw2();
	 
   for(int i=0; i<h->GetNbinsX(); i++)// changed this
   {
   	if(h->GetBinEntries(i+1) == 0) continue;  
       	int runNo(h->GetBinCenter(i+1));
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
	  	double val = h->GetBinContent(i+1);
	     	int nent   = h->GetBinEntries(i+1);
	     	int bin    = hbig->FindBin(index);
             	cout << " val " << val << " nent " << nent << " bin " << bin << endl;
	     	// if(nent>5){
	     	hbig->SetBinContent(bin,val);
	     	if(nent>5) hbig->SetBinError(bin,h->GetBinError(i+1)); 
	     	else hbig->SetBinError(bin,val/sqrt(nent));
	     	// }
	}

   }  //end of for loop 

 
	 
   //double m,s,sm,ss;
   //WeightedMean(hbig,m,s,sm,ss,2);// 2 to fit with pol1
	 	 
   hbig->GetXaxis()->SetTitle("Run index");
   hbig->GetYaxis()->SetTitle(yaxistitle);

   hbig->GetXaxis()->SetTitleSize(0.04);
   hbig->GetYaxis()->SetTitleSize(0.04);
   hbig->GetYaxis()->SetTitleOffset(1.2);
	 
   hbig->SetStats(0);
   hbig->GetYaxis()->SetRangeUser(ymin,ymax);
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

   TLegend *leg2 = new TLegend(0.55,0.67,0.55,0.87,"");
   //TLegend *leg2 = new TLegend(0.55,0.73,0.55,0.88,"");
   leg2->SetTextSize(0.04);
   leg2->SetBorderSize(0);
   leg2->AddEntry((TObject*)0,"M_{4j} > 1607 GeV","");
   leg2->AddEntry((TObject*)0,"|#Delta#eta| < 1.1","");
   leg2->AddEntry((TObject*)0,"Mass asymmetry < 0.1","");
   leg2->AddEntry((TObject*)0,"#Delta R_{1,2} < 2","");
   leg2->AddEntry((TObject*)0,"#alpha > 0.1","");
   leg2->Draw();

   cms->Draw();
   lumileg->Draw();


   TLine *l1 = new TLine(107,ymin,107,ymaxlab); //107
   l1->SetLineWidth(3);
   l1->SetLineColor(kRed);
   l1->Draw("same");

   TLine *l2 = new TLine(152,ymin,152,ymaxlab); //152
   l2->SetLineWidth(3);
   l2->SetLineColor(kRed);
   l2->Draw("same");

   TLine *l3 = new TLine(202,ymin,202,ymaxlab); //202
   l3->SetLineWidth(3);
   l3->SetLineColor(kRed);
   l3->Draw("same");

   TLine *l4 = new TLine(320,ymin,320,ymaxlab); //320
   l4->SetLineWidth(3);
   l4->SetLineColor(kRed);
   l4->Draw("same");

   TLine *l5 = new TLine(341,ymin,341,ymaxlab*1.2); //341
   l5->SetLineWidth(3);
   l5->SetLineColor(kGreen+2);
   l5->Draw("same");

   TLine *l6 = new TLine(362,ymin,362,ymaxlab); //362
   l6->SetLineWidth(3);
   l6->SetLineColor(kRed);
   l6->Draw("same");

   TLine *l7 = new TLine(421,ymin,421,ymaxlab); //362
   l7->SetLineWidth(3);
   l7->SetLineColor(kOrange+1);
   l7->Draw("same");

   TLatex *latex1 = new TLatex();
   latex1->SetTextFont(42);
   latex1->SetTextColor(kGreen+2);
   latex1->DrawLatex(370,ymaxlab*1.1,"2023");
   latex1->DrawLatex(130,ymaxlab*1.1,"2022");

   TLatex *latex2 = new TLatex();
   latex2->SetTextFont(42);
   latex2->SetTextColor(kRed);
   latex2->SetTextSize(0.04);
   latex2->DrawLatex(45,0.9*ymaxlab,"C");
   latex2->DrawLatex(125,0.9*ymaxlab,"D");
   latex2->DrawLatex(170,0.9*ymaxlab,"E");
   latex2->DrawLatex(250,0.9*ymaxlab,"F");
   latex2->DrawLatex(325,0.9*ymaxlab,"G");
   latex2->DrawLatex(345,0.9*ymaxlab,"B");
   latex2->DrawLatex(380,0.9*ymaxlab,"C");
   latex2->SetTextSize(0.03);
   latex2->DrawLatex(370,0.8*ymaxlab,"v1v2v3");
   latex2->SetTextSize(0.04);
   latex2->DrawLatex(425,0.9*ymaxlab,"C");
   latex2->SetTextSize(0.03);
   latex2->DrawLatex(425,0.8*ymaxlab,"v4");

   char cname1[1024], cname2[1024];

   sprintf(cname1,"output_4jets/plots/4jets_%s_vs_run_2022CDEFG_2023BC_47p01fb-1.png",var);
   sprintf(cname2,"output_4jets/plots/4jets_%s_vs_run_2022CDEFG_2023BC_47p01fb-1.pdf",var);

   c->SaveAs(cname1);
   c->SaveAs(cname2);

}
