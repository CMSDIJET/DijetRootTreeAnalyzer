#include <iostream>
#include <fstream>

//////////////////////////////////////////////////////////////////////////////

void plot_stability_cert_4jets_Run3()
{
   // plothistos_stability();
   plot_xsec();
   // plothistos_stability_2jets();
  //  plothistos_stability_vsNvtx();
}


void plothistos_stability()
{
   gROOT->LoadMacro("setTDRStyle.C");
   setTDRStyle();

   TString jettype[2] = {"pf","calo"};
   int hlt[2] = {800,650}; 
   char name[1000],dirname[1000];

   TFile *inf[2]; 
   inf[0] = TFile::Open("Run2015B_lumi40_sum_17Jul_and25Jul_final_tight_stability_cert.root");

   
//    TString histoname = "Mass_vsRun";double yaxismin(0.),yaxismax(3000.);TString titly="Dijet Mass (GeV)";TString titlx="run index";
//  TString histoname = "METovSUMET_vsRun2";double yaxismin(0.),yaxismax(10.);TString titly="MET/#sqrt{SumET}";TString titlx="run index";
//   TString histoname = "METovSUMET_vsRun";double yaxismin(0.),yaxismax(0.1);TString titly="MET/SumET";TString titlx="run index";
//  TString histoname = "DeltaPhi_vsRun";double yaxismin(2.5),yaxismax(3.5);TString titly="#Delta#phi (rad)";TString titlx="run index"; 
//   TString histoname = "CosThetaStar_vsRun";double yaxismin(-2.),yaxismax(2.);TString titly="cos(#theta^{*})";TString titlx="run index";  

//   TString histoname = "PtcorJet1_vsRun";double yaxismin(200.),yaxismax(1500.);TString titly="Leading Jet Corrected p_{T} (GeV)";TString titlx="run index";   
//   TString histoname = "PhiJet1_vsRun";double yaxismin(-3.),yaxismax(3.);TString titly="Leading Jet #phi (rad)";TString titlx="run index";  
//   TString histoname = "EtaJet1_vsRun";double yaxismin(-20.5),yaxismax(20.5);TString titly="Leading Jet #eta";TString titlx="run index";  
//   TString histoname = "CHFJet1_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Leading Jet Charged Hadron Fraction";TString titlx="run index";  
//   TString histoname = "NHFJet1_vsRun";double yaxismin(0.),yaxismax(.3);TString titly="Leading Jet Neutral Hadron Fraction";TString titlx="run index";  
//   TString histoname = "CEMFJet1_vsRun";double yaxismin(0),yaxismax(0.1);TString titly="Leading Jet Charged EM Fraction";TString titlx="run index";
//   TString histoname = "NEMFJet1_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Leading Jet Neutral EM Fraction";TString titlx="run index";

//   TString histoname = "PtcorJet2_vsRun";double yaxismin(800.),yaxismax(2000.);TString titly="Second Jet Corrected p_{T} (GeV)";TString titlx="run index";   
//   TString histoname = "PhiJet2_vsRun";double yaxismin(-3.),yaxismax(3.);TString titly="Second Jet #phi (rad)";TString titlx="run index";  
//   TString histoname = "EtaJet2_vsRun";double yaxismin(-2.5),yaxismax(2.5);TString titly="Second Jet #eta";TString titlx="run index";  
//   TString histoname = "CHFJet2_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Second Jet Charged Hadron Fraction";TString titlx="run index";  
//   TString histoname = "NHFJet2_vsRun";double yaxismin(0.),yaxismax(.5);TString titly="Second Jet Neutral Hadron Fraction";TString titlx="run index";  
//   TString histoname = "CEMFJet2_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Second Jet Charged EM Fraction";TString titlx="run index";
//   TString histoname = "NEMFJet2_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Second Jet Neutral EM Fraction";TString titlx="run index";

   TH2D *h2d[2];
   TProfile *h[2];

   //itr ibiny
   double masson_pf[5][5] = {244, 296, 453, 740,1246,
                             386, 489, 740,1118,1945,
                             526, 693,1058,1770,3019,
                             649, 838,1383,2037,3558,
                             788,1058,1687,2546,3704};
   TH1F *hbig[2];// big runs only


   // plot stability plots 
   ///////////////////////////////////////////////////////////////////////////
   
  for(int itr=0;itr<1;itr++)  //trigger loop
   {  
      //sprintf(name,"%s_hlt%d",histoname.Data(),hlt[itr]);
      sprintf(name,"%s",histoname.Data());
      TCanvas *c = new TCanvas(name,name);
//      c->Divide(3,2);

      int RUN_NUMBERS[1000];
      double LUMI[1000];
      int NRuns(0);
      
      //Read file per trigger - luminosity per run 

      sprintf(name,"../Run2015D_big_cert.txt");
      ifstream txtFile;
      txtFile.open(name);
      
      while (!txtFile.eof())
      {         
      	 txtFile >> RUN_NUMBERS[NRuns] >> LUMI[NRuns];           
         //cout<<NRuns<<" "<<RUN_NUMBERS[NRuns]<<" "<<LUMI[NRuns]<<endl;
      	 NRuns++;
	 if(NRuns>=1000) cout << "NRuns>=1000 !!!!" << endl;                
      }
      NRuns = NRuns-1; 
      cout << "NRuns: " << NRuns << endl;
                
      for(int ibiny=0;ibiny<5;ibiny++)
      {
      	 sprintf(name,"%s_Ybin%d_hlt%d",histoname.Data(),ibiny,itr);
         cout<<name<<endl;

         h2d[0]= (TH2D*)inf[0]->Get(name); 
         if(ibiny==0) TH2D *h2dall[0] = (TH2D*) h2d[0]->Clone(); 
         else h2dall[0]->Add(h2d[0]);
      }

      h[0] = h2dall[0]->ProfileX();
      h[0]->SetTitle("");
      h[0]->GetXaxis()->SetTitle(titlx);
      h[0]->GetYaxis()->SetTitle(titly);

      sprintf(name,"%s_hlt%d","BigRuns",histoname.Data(),hlt[itr]);
      hbig[itr] = new TH1F(name,"",NRuns,0,NRuns);
      hbig[itr]->Sumw2();
	 
      for(int i=0;i<h[0]->GetNbinsX();i++)// changed this
      {
          //cout << " here " << h[0]->GetBinContent(i+1) << endl;
          if(h[0]->GetBinEntries(i+1) == 0) continue;  
          int runNo(h[0]->GetBinCenter(i+1));
          int index(-1);        
          for(int j=0;j<NRuns;j++) // edw
          {
             //cout<<i<<"  "<<j<<"   "<<runNo <<"  "<< RUN_NUMBERS[j]<<endl;
             if(runNo == RUN_NUMBERS[j])
             { 
               // cout << " FOUND IT  " << runNo << " index " << j << endl; 
                index = j;  
                continue;  
              }
          }
      	  if(index > -1)
	  {
	     double val = h[0]->GetBinContent(i+1);
	     int nent   = h[0]->GetBinEntries(i+1);
	     int bin    = hbig[itr]->FindBin(index);
             cout << " val " << val << " nent " << nent << " bin " << bin << endl;
	     // if(nent>5){
	     hbig[itr]->SetBinContent(bin,val);
	     if(nent>5) hbig[itr]->SetBinError(bin,h[0]->GetBinError(i+1)); 
	     else hbig[itr]->SetBinError(bin,val/sqrt(nent));
	     // }
	  }

      }  //end of for loop 

      TLegend *leg = new TLegend(0.9,0.9,0.3,0.8);
      leg->SetTextSize(.031);

      //move hist to the left in oder not to hide the y title
      TPad* pad = (TPad*)c->GetPad(0);
      pad->SetLeftMargin(0.15); 

      h[0]->Draw("");
	 
      double m,s,sm,ss;
      WeightedMean(hbig[itr],m,s,sm,ss,2);// 2 to fit with pol1
	 	 
      sprintf(name,"(HLT_HT%d)",hlt[itr]);
      hbig[itr]->GetXaxis()->SetTitle(titlx);
      hbig[itr]->GetYaxis()->SetTitle(titly);
      hbig[itr]->GetYaxis()->SetRangeUser(yaxismin,yaxismax);

      hbig[itr]->Draw("pe");

      TPaveText *pave = new TPaveText(0.2,0.75,0.85,0.85,"NDC");
      //sprintf(name,"mean = %3.2f #pm %3.2f, slope = %2.1e #pm %5.4f",m,s,sm,ss);
      sprintf(name,"mean = %3.2f #pm %3.2f",m,s);
      pave->AddText(name);
      sprintf(name,"slope = %2.0e #pm %2.0e",sm,ss);
      pave->AddText(name);
  
      pave->SetFillColor(0);
      pave->SetBorderSize(0);
      pave->SetTextFont(42);
      pave->SetTextAlign(12);
      pave->SetTextSize(0.04);

      c->Print(TString(c->GetName())+TString("_cert.png"));
      c->Print(TString(c->GetName())+TString("_cert.pdf"));

   } //end of trigger loop

}
//////////////////////////////////////////////////////////////////////////////
void plot_xsec()
{
 //TPaveText *paveCMS = new TPaveText(0.32,0.96,0.52,0.99,"NDC");
 TPaveText *paveCMS = new TPaveText(0.12,0.96,0.96,0.99,"NDC");
 paveCMS->AddText("CMS Preliminary  #sqrt{s} = 13 TeV    L = 546 pb^{-1}");
 paveCMS->SetFillColor(0);
 paveCMS->SetBorderSize(0);
 paveCMS->SetTextSize(0.04);

 TPaveText *paveCMS2 = new TPaveText(0.24,0.75,0.45,0.9,"NDC");
 paveCMS2->AddText("|#eta|<2.5" );
 paveCMS2->AddText("|#Delta #eta|>1.3");
 paveCMS2->AddText("M_{jj} > 1.2 TeV"); // 1.2 ALLAKSE
 paveCMS2->SetFillColor(0);
 paveCMS2->SetBorderSize(0);
 paveCMS2->SetTextSize(0.04);


  gROOT->LoadMacro("setTDRStyle.C");
  setTDRStyle();

   TString jettype[2] = {"pf","calo"};
   int hlt[2] = {800,650}; //????800 and PFHT650_WideJetMjj900 
   char name[1000],dirname[1000];

   TFile *inf[2]; 
   inf[0] = TFile::Open("Run2015B_lumi40_sum_17Jul_and25Jul_final_tight_stability_cert.root");

   TString histoname = "Run"; double yaxismin(0.),yaxismax(1000.); TString titly="Cross Section (pb)";TString titlx="Run index";

   TH1F *h[2], *h_all[2];
   double masson_pf[5][5] = {244, 296, 453, 740,1246,
                             386, 489, 740,1118,1945,
                             526, 693,1058,1770,3019,
                             649, 838,1383,2037,3558,   
                             788,1058,1687,2546,3704};  

   TH1F *hbig[2];// big runs only

   // plot 
   ///////////////////////////////////////////////////////////////////////////
   
   for(int itr=0;itr<1;itr++)
   {  
      sprintf(name,"%s_hlt%d",histoname.Data(),itr);
      TCanvas *c = new TCanvas(name,name);
      //c->Divide(3,2);

      int RUN_NUMBERS[1000];
      double LUMI[1000];
      int NRuns(0);
      
      //Read file per trigger - luminosity per run 

      sprintf(name,"../Run2015D_big_cert.txt");
      ifstream txtFile;
      txtFile.open(name);
      double lumi;
      int run;

      while (!txtFile.eof())
      {
         txtFile >> run >> lumi;
         //if(lumi>10){  
          LUMI[NRuns]=lumi;
          RUN_NUMBERS[NRuns] = run;
      	  cout<<NRuns<<" "<<RUN_NUMBERS[NRuns]<<" "<<LUMI[NRuns]<<endl;
      	  NRuns++;
	  if(NRuns>=1000) cout << "NRuns>=1000 !!!!" << endl;                
         //}
      }
      NRuns = NRuns-1; 
      cout << "NRuns: " << NRuns << endl;
      
                
      for(int ibiny=0;ibiny<5;ibiny++)
      {
      	 sprintf(name,"%s_Ybin%d_hlt%d",histoname.Data(),ibiny,itr);
         cout << " name is " << name << endl;
      
      	 h[0] = (TH1F*)inf[0]->Get(name);
         if(ibiny==0) TH1F *h_all[0] = (TH1F*) h[0]->Clone(); 
         else h_all[0]->Add(h[0]);
      } //end of eta bins


         h_all[0]->SetTitle("");
      	 h_all[0]->GetXaxis()->SetTitle(titlx);
      	 h_all[0]->GetYaxis()->SetTitle(titly);
	 
	 sprintf(name,"%s","BigRuns",histoname.Data());
      	 hbig[itr] = new TH1F(name,"",NRuns,0,NRuns);
      	 hbig[itr]->Sumw2();
	 
	 for(int i=0;i<h_all[0]->GetNbinsX();i++)
      	 {
//cout<<"    "<<h_all[0]->GetBinContent(i+1)<<endl;
      	    if(h_all[0]->GetBinContent(i+1) == 0) continue;  
      	    int runNo(h_all[0]->GetBinCenter(i+1));  cout<<"runNo  "<<runNo<<endl;
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
	       double valN = h_all[0]->GetBinContent(i+1);
	       double y = valN/LUMI[index];  cout<<valN<<"  "<<LUMI[index]<<"  "<<y<<endl;
	       double e = y*sqrt(1./valN);
	       
	       int bin = hbig[itr]->FindBin(index);  
	       
	       //if(valN>5){
	         hbig[itr]->SetBinContent(bin,y);
                 //cout << " NUMBER OF EVENTS " << valN  << " XSEC " << y << " RUN " << runNo << " Lumi " << LUMI[index] << " index " << index <<  endl;
	         hbig[itr]->SetBinError(bin,e);
	       //}
	    }
      	 }  //end of for loop 

      	 //gPad->SetLogy();

         //move hist to the left in oder not to hide the y title
         TPad* pad = (TPad*)c->GetPad(0);
         pad->SetLeftMargin(0.15); 

      	 TLegend *leg = new TLegend(0.6,0.6,0.8,0.8);
      	 leg->SetTextSize(.031);

      	 h_all[0]->Draw("");
         paveCMS->Draw("Same");
         paveCMS2->Draw("Same");

	 double m,s,sm,ss;
         //FOR FITTING
	 WeightedMean(hbig[itr],m,s,sm,ss,1);// 2 to fit with pol1	 

         for(Int_t jj=1;jj<hbig[itr]->GetNbinsX();jj++){
          double value = hbig[itr]->GetBinContent(jj);
          double diff = TMath::Abs(value-m);
          if((diff/m)>0.05) cout << " % change " << diff/m << " jj " << jj <<  " run " << RUN_NUMBERS[jj] << endl;
          }

	 
	 sprintf(name,"HLT_Jet%d",hlt[itr]);
	 hbig[itr]->GetXaxis()->SetTitle(titlx);
      	 hbig[itr]->GetYaxis()->SetTitle(titly);
	 
      	 hbig[itr]->GetYaxis()->SetRangeUser(0.,2.*m+2.*s); // 5
         hbig[itr]->Draw("pe");

         paveCMS->Draw("Same");
         paveCMS2->Draw("Same");

      	 TPaveText *pave = new TPaveText(0.2,0.75,0.85,0.85,"NDC");
      	 sprintf(name,"mean = %4.3f #pm %4.3f",m,s);
	 pave->AddText(name);
	 sprintf(name,"slope = %2.0e #pm %2.0e",sm,ss);
	 pave->AddText(name);
  
      	 pave->SetFillColor(0);
      	 pave->SetBorderSize(0);
      	 pave->SetTextFont(42);
      	 pave->SetTextSize(0.04);
      	 //pave->Draw("same");

      	 //leg->Draw();
       
      c->Print(TString(c->GetName())+TString("_cert.png"));
      c->Print(TString(c->GetName())+TString("_cert.pdf"));

   } //end of trigger loop

}

void plothistos_stability_2jets()
{
   gROOT->Reset();   
   gROOT->ForceStyle();
   LoadStyle();

   TString jettype[2] = {"pf","calo"};
   int hlt[5] = {80,140,200,260,320};

   char name[1000],dirname[1000];

   TFile *inf[2]; 
   inf[0] = TFile::Open("./MassEventJetHistos_9200invpb_5Nov2012_uncsrc.root");

//   TString histoname1="PtcorJet1_vsRun";TString histoname2="PtcorJet2_vsRun";double yaxismin(0.),yaxismax(1000.);TString titly="Corrected p_{T} (GeV)";TString titlx="run index";   
//   TString histoname1="PhiJet1_vsRun";TString histoname2="PhiJet2_vsRun";double yaxismin(-3.),yaxismax(3.);TString titly="#phi (rad)";TString titlx="run index";  
//   TString histoname1="EtaJet1_vsRun";TString histoname2="EtaJet2_vsRun";double yaxismin(-2.5),yaxismax(2.5);TString titly="#eta";TString titlx="run index";  
//   TString histoname1="CHFJet1_vsRun";TString histoname2="CHFJet2_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Charged Hadron Fraction";TString titlx="run index";  
//   TString histoname1="NHFJet1_vsRun";TString histoname2="NHFJet2_vsRun";double yaxismin(0.),yaxismax(.5);TString titly="Neutral Hadron Fraction";TString titlx="run index";  
//   TString histoname1="CEMFJet1_vsRun";TString histoname2="CEMFJet2_vsRun";double yaxismin(-0.1),yaxismax(0.1);TString titly="Charged EM Fraction";TString titlx="run index";
//   TString histoname1="NEMFJet1_vsRun";TString histoname2="NEMFJet2_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Neutral EM Fraction";TString titlx="run index";




   TProfile *h[2];

   TString ytitl[5] = {"|y|_{max}<0.5", "0.5<|y|_{max}<1.0", "1.0<|y|_{max}<1.5", "1.5<|y|_{max}<2.0", "2.0<|y|_{max}<2.5"};
   //itr ibiny
   double masson_pf[5][5] = {244, 296, 453, 740,1246,
                             386, 489, 740,1118,1945,
                             526, 693,1058,1770,3019,
                             649, 838,1383,2037,3558,   
                             788,1058,1687,2546,3704};  

   TH1F *hbig1[5][5];// big runs only
   TH1F *hbig2[5][5];

   // plot stability plots 
   ///////////////////////////////////////////////////////////////////////////
   

   //for(int itr=0;itr<5;itr++)
   for(int itr=1;itr<5;itr++)
   {  
      sprintf(name,"canv_%s_%s_hlt%d",histoname1.Data(),histoname2.Data(),hlt[itr]);
      TCanvas *c = new TCanvas(name,name);
      c->Divide(3,2);

      int RUN_NUMBERS[1000];
      double LUMI[1000];
      int NRuns(0);
      
      //Read file per trigger - luminosity per run 

      sprintf(name,"./RunsJet%dBig.txt",hlt[itr]);
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
      
                
      for(int ibiny=0;ibiny<5;ibiny++)
      {
      	 sprintf(dirname,"efficiency/ak7%s",jettype[0].Data()); 
      	 sprintf(name,"%s/%s_Ybin%d_hlt%d",dirname,histoname1.Data(),ibiny,hlt[itr]);

      	 h[0] = (TProfile*)inf[0]->Get(name);
         h[0]->SetTitle("");
      	 h[0]->GetXaxis()->SetTitle(titlx);
      	 h[0]->GetYaxis()->SetTitle(titly);
	 
      	 sprintf(name,"%s/%s_Ybin%d_hlt%d",dirname,histoname2.Data(),ibiny,hlt[itr]);

      	 h[1] = (TProfile*)inf[0]->Get(name);
         h[1]->SetTitle("");
      	 h[1]->GetXaxis()->SetTitle(titlx);
      	 h[1]->GetYaxis()->SetTitle(titly);
	 
	 
	 
	 sprintf(name,"%s_%s_Ybin%d_hlt%d","BigRuns",histoname1.Data(),ibiny,hlt[itr]);
      	 hbig1[itr] = new TH1F(name,name,NRuns,0,NRuns);
      	 hbig1[itr]->Sumw2();
	 
	 sprintf(name,"%s_%s_Ybin%d_hlt%d","BigRuns",histoname2.Data(),ibiny,hlt[itr]);
      	 hbig2[itr] = new TH1F(name,name,NRuns,0,NRuns);
      	 hbig2[itr]->Sumw2();
	 
	 
	 
	 for(int i=0;i<h[0]->GetNbinsX();i++)
      	 {
      	    if(h[0]->GetBinContent(i+1) == 0) continue;  
      	    int runNo(h[0]->GetBinCenter(i+1));
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
	       double val = h[0]->GetBinContent(i+1);
	       int nent = h[0]->GetBinEntries(i+1);
	       int bin = hbig1[itr]->FindBin(index);
	       
	       if(nent>10){
	       hbig1[itr]->SetBinContent(bin,val);
	       if(nent>5) hbig1[itr]->SetBinError(bin,h[0]->GetBinError(i+1)); 
	       else hbig1[itr]->SetBinError(bin,val/sqrt(nent));
	       }
	       
	       cout << bin << " " << val <<  endl;
	    }
      	 }
	 
	 for(int i=0;i<h[1]->GetNbinsX();i++)
      	 {
      	    if(h[1]->GetBinContent(i+1) == 0) continue;  
      	    int runNo(h[1]->GetBinCenter(i+1));
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
	       double val = h[1]->GetBinContent(i+1);
	       int nent = h[1]->GetBinEntries(i+1);
	       int bin = hbig2[itr]->FindBin(index);
	       
	       if(nent>10){
	       hbig2[itr]->SetBinContent(bin,val);
	       if(nent>5) hbig2[itr]->SetBinError(bin,h[1]->GetBinError(i+1)); 
	       else hbig2[itr]->SetBinError(bin,val/sqrt(nent));
	       }
	       
	       cout << bin << " " << val <<  endl;
	    }
      	 }
	  

      	 c->cd(ibiny+1);
      	 //gPad->SetLogy();

      	 TLegend *leg = new TLegend(0.6,0.6,0.8,0.8);
      	 leg->SetTextSize(.031);

      	 h[0]->Draw("");
      	 h[0]->Draw("same");

	 
	 double m1,s1,sm1,ss1;
	 WeightedMean(hbig1[itr],m1,s1,sm1,ss1,2);// 2 to fit with pol1
	 
	 double m2,s2,sm2,ss2;
	 WeightedMean(hbig2[itr],m2,s2,sm2,ss2,2);// 2 to fit with pol1
	 
	 
	 sprintf(name,"%s (HLT_Jet%d, M_{jj} > %d GeV)",ytitl[ibiny].Data(),hlt[itr],masson_pf[itr]);
	 
	 hbig1[itr]->SetTitle(name);
	 hbig1[itr]->GetXaxis()->SetTitle(titlx);
      	 hbig1[itr]->GetYaxis()->SetTitle(titly);
	 
      	 //hbig1[itr]->GetYaxis()->SetRangeUser(m-0.5*m,m+0.5*m);
	 hbig1[itr]->GetYaxis()->SetRangeUser(yaxismin,yaxismax);
	 hbig1[itr]->Draw("pe");

	 hbig2[itr]->SetTitle(name);
	 hbig2[itr]->GetXaxis()->SetTitle(titlx);
      	 hbig2[itr]->GetYaxis()->SetTitle(titly);
	 
      	 //hbig2[itr]->GetYaxis()->SetRangeUser(m-0.5*m,m+0.5*m);
	 hbig2[itr]->GetYaxis()->SetRangeUser(yaxismin,yaxismax);
	 hbig2[itr]->SetLineColor(kRed);
	 hbig2[itr]->Draw("pesame");

      	 TPaveText *pave = new TPaveText(0.15,0.75,0.85,0.85,"NDC");
	 //sprintf(name,"mean = %3.2f #pm %3.2f, slope = %2.1e #pm %5.4f",m,s,sm,ss);
	 sprintf(name,"leading jet, mean = %3.2f #pm %3.2f",m1,s1);
	 pave->AddText(name);
	 sprintf(name,"slope = %2.0e #pm %2.0e",sm1,ss1);
	 pave->AddText(name);
	 
	 //sprintf(name,"mean = %3.2f #pm %3.2f, slope = %2.1e #pm %5.4f",m,s,sm,ss);
	 sprintf(name,"second jet, mean = %3.2f #pm %3.2f",m2,s2);
	 pave->AddText(name);
	 sprintf(name,"slope = %2.0e #pm %2.0e",sm2,ss2);
	 pave->AddText(name);
	 
      	 pave->SetFillColor(0);
      	 pave->SetBorderSize(0);
      	 pave->SetTextFont(42);
	 pave->SetTextAlign(32);
      	 pave->SetTextSize(0.04);
      	 pave->Draw("same");

      	 //leg->Draw();

      	 TMarker *mk1 = new TMarker(.2,.84,20);
	 mk1->SetNDC();
	 mk1->SetMarkerColor(1);
	 mk1->SetMarkerSize(.4);
	 mk1->Draw("same"); 
	 
      	 TMarker *mk2 = new TMarker(.2,.78,21);
	 mk2->SetNDC();
	 mk2->SetMarkerColor(2);
	 mk2->SetMarkerSize(.4);
	 mk2->Draw("same"); 
	


      }
      c->Print(TString(c->GetName())+TString("_cert.gif"));
      c->Print(TString(c->GetName())+TString("_cert.eps"));
      c->Print(TString(c->GetName())+TString("_cert.pdf"));
   }
}
//////////////////////////////////////////////////////////////////////////////
void plothistos_stability_vsNvtx()
{

  gROOT->LoadMacro("setTDRStyle.C");
  setTDRStyle();

   TString jettype[2] = {"pf","calo"};
   int hlt[2] = {800,650}; //????800 and PFHT650_WideJetMjj900 
   char name[1000],dirname[1000];

   TFile *inf[2]; 
   inf[0] = TFile::Open("Run2015B_lumi40_sum_17Jul_and25Jul_final_tight_stability_cert.root");
 
//   TString histoname = "Mass_vsNvtx";double yaxismin(0.),yaxismax(2000.);TString titly="Dijet Mass (GeV)";TString titlx="Number of vertices";
//  TString histoname = "METovSUMET_vsNvtx";double yaxismin(0.),yaxismax(1.);TString titly="MET/SumET";TString titlx="Number of vertices";
//    TString histoname = "METovSUMET_vsNvtx2";double yaxismin(0.),yaxismax(10.);TString titly="MET/#sqrt{SumET}";TString titlx="Number of vertices";
//  TString histoname = "DeltaPhi_vsNvtx";double yaxismin(2.5),yaxismax(3.5);TString titly="#Delta#phi (rad)";TString titlx="Number of vertices"; 
// TString histoname = "CosThetaStar_vsNvtx";double yaxismin(-2.),yaxismax(2.);TString titly="cos(#theta^{*})";TString titlx="Number of vertices";  

//TString histoname = "PtcorJet1_vsNvtx";double yaxismin(200.),yaxismax(500.);TString titly="Leading Jet Corrected p_{T} (GeV)";TString titlx="Number of vertices";   
//TString histoname = "PhiJet1_vsNvtx";double yaxismin(-3.),yaxismax(3.);TString titly="Leading Jet #phi (rad)";TString titlx="Number of vertices";  
//TString histoname = "EtaJet1_vsNvtx";double yaxismin(-2.5),yaxismax(2.5);TString titly="Leading Jet #eta";TString titlx="Number of vertices";  
//TString histoname = "CHFJet1_vsNvtx";double yaxismin(0.),yaxismax(1.);TString titly="Leading Jet Charged Hadron Fraction";TString titlx="Number of vertices";  
//TString histoname = "NHFJet1_vsNvtx";double yaxismin(0.),yaxismax(1.);TString titly="Leading Jet Neutral Hadron Fraction";TString titlx="Number of vertices";  
//TString histoname = "CEMFJet1_vsNvtx";double yaxismin(0),yaxismax(1.);TString titly="Leading Jet Charged EM Fraction";TString titlx="Number of vertices";
TString histoname = "NEMFJet1_vsNvtx";double yaxismin(0.),yaxismax(1.);TString titly="Leading Jet Neutral EM Fraction";TString titlx="Number of vertices";

//   TString histoname = "PtcorJet2_vsNvtx";double yaxismin(800.),yaxismax(2000.);TString titly="Second Jet Corrected p_{T} (GeV)";TString titlx="Number of vertices";   
//   TString histoname = "PhiJet2_vsNvtx";double yaxismin(-3.),yaxismax(3.);TString titly="Second Jet #phi (rad)";TString titlx="Number of vertices";  
//   TString histoname = "EtaJet2_vsNvtx";double yaxismin(-2.5),yaxismax(2.5);TString titly="Second Jet #eta";TString titlx="Number of vertices";  
//   TString histoname = "CHFJet2_vsNvtx";double yaxismin(0.),yaxismax(1.);TString titly="Second Jet Charged Hadron Fraction";TString titlx="Number of vertices";  
//   TString histoname = "NHFJet2_vsNvtx";double yaxismin(0.),yaxismax(.5);TString titly="Second Jet Neutral Hadron Fraction";TString titlx="Number of vertices";  
//   TString histoname = "CEMFJet2_vsNvtx";double yaxismin(0.),yaxismax(1.);TString titly="Second Jet Charged EM Fraction";TString titlx="Number of vertices";
//   TString histoname = "NEMFJet2_vsNvtx";double yaxismin(0.),yaxismax(1.);TString titly="Second Jet Neutral EM Fraction";TString titlx="Number of vertices";

    // TString histoname = "JetJec_vsPt_Jet1";double yaxismin(0.),yaxismax(3000.);TString titly="JetJecAK4";TString titlx="PF Pt AK4 (GeV)";
    // TString histoname = "PFPt_CaloPt_vsPt_Jet1";double yaxismin(0.),yaxismax(1500.);TString titly="(PF Pt - Calo Pt)/ PF Pt";TString titlx="PF Pt AK4 (GeV)";

  //TString histoname = "Mass_vsRun";double yaxismin(0.),yaxismax(1000.);TString titly="Dijet Mass (GeV)";TString titlx="Run number";
  // TString histoname = "METovSUMET_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="MET/SumET";TString titlx="Run number";
//   TString histoname = "DeltaPhi_vsRun";double yaxismin(2.5),yaxismax(3.5);TString titly="#Delta#phi (rad)";TString titlx="Run number"; 
//   TString histoname = "CosThetaStar_vsRun";double yaxismin(-2.),yaxismax(2.);TString titly="cos(#theta^{*})";TString titlx="Run number";  

//   TString histoname = "PtcorJet1_vsRun";double yaxismin(200.),yaxismax(500.);TString titly="Leading Jet Corrected p_{T} (GeV)";TString titlx="Run number";   
//   TString histoname = "PhiJet1_vsRun";double yaxismin(-3.),yaxismax(3.);TString titly="Leading Jet #phi (rad)";TString titlx="Run number";  
//   TString histoname = "EtaJet1_vsRun";double yaxismin(-2.5),yaxismax(2.5);TString titly="Leading Jet #eta";TString titlx="Run number";  
//   TString histoname = "CHFJet1_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Leading Jet Charged Hadron Fraction";TString titlx="Run number";  
//   TString histoname = "NHFJet1_vsRun";double yaxismin(0.),yaxismax(.3);TString titly="Leading Jet Neutral Hadron Fraction";TString titlx="Run number";  
//  TString histoname = "CEMFJet1_vsRun";double yaxismin(-0.1),yaxismax(0.1);TString titly="Leading Jet Charged EM Fraction";TString titlx="Run number";
//   TString histoname = "NEMFJet1_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Leading Jet Neutral EM Fraction";TString titlx="Run number";

//   TString histoname = "PtcorJet2_vsRun";double yaxismin(800.),yaxismax(2000.);TString titly="Second Jet Corrected p_{T} (GeV)";TString titlx="Run number";   
//   TString histoname = "PhiJet2_vsRun";double yaxismin(-3.),yaxismax(3.);TString titly="Second Jet #phi (rad)";TString titlx="Run number";  
//   TString histoname = "EtaJet2_vsRun";double yaxismin(-2.5),yaxismax(2.5);TString titly="Second Jet #eta";TString titlx="Run number";  
//   TString histoname = "CHFJet2_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Second Jet Charged Hadron Fraction";TString titlx="Run number";  
//   TString histoname = "NHFJet2_vsRun";double yaxismin(0.),yaxismax(.5);TString titly="Second Jet Neutral Hadron Fraction";TString titlx="Run number";  
//   TString histoname = "CEMFJet2_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Second Jet Charged EM Fraction";TString titlx="Run number";
//   TString histoname = "NEMFJet2_vsRun";double yaxismin(0.),yaxismax(1.);TString titly="Second Jet Neutral EM Fraction";TString titlx="Run number";

   TH2D *h2d[2];
   TProfile *h[2];
  

   //itr ibiny
   double masson_pf[5][5] = {244, 296, 453, 740,1246,
                             386, 489, 740,1118,1945,
                             526, 693,1058,1770,3019,
                             649, 838,1383,2037,3558,
                             788,1058,1687,2546,3704};
   //TH1F *hbig[2];// big runs only


   // plot stability plots 
   ///////////////////////////////////////////////////////////////////////////
   
  for(int itr=0;itr<1;itr++)  //trigger loop
   {  
      //sprintf(name,"canv_%s_hlt%d",histoname.Data(),hlt[itr]);
      sprintf(name,"%s",histoname.Data());
      TCanvas *c = new TCanvas(name,name);
             
      for(int ibiny=0;ibiny<5;ibiny++)
      {
      	 //sprintf(dirname,"efficiency/ak7%s",jettype[0].Data()); 
      	 sprintf(name,"%s_Ybin%d_hlt%d",histoname.Data(),ibiny,itr);

         //h[0] = (TProfile*)inf[0]->Get(name); // it doesn't create the profile
         h2d[0]= (TH2D*)inf[0]->Get(name); 
         if(ibiny==0) TH2D *h2dall[0] = (TH2D*) h2d[0]->Clone(); 
         else h2dall[0]->Add(h2d[0]);
       } //end of ybin
       h[0] = h2dall[0]->ProfileX();
       h[0]->SetTitle("");
       h[0]->GetXaxis()->SetTitle(titlx);
       h[0]->GetYaxis()->SetTitle(titly);

         //move hist to the left in oder not to hide the y title
         TPad* pad = (TPad*)c->GetPad(0);
         pad->SetLeftMargin(0.18); //0.15  

         //c->cd(ibiny+1);
       h[0]->Draw();
       double m,s,sm,ss;
       TH1D *htest=h[0]->ProjectionX();
       htest->GetXaxis()->SetRangeUser(4.,20.);
       double max = htest->GetMinimum();
       htest->SetMinimum(1.5*max);
       if(max<0) htest->SetMinimum(2.5*max);
 
       WeightedMeanD(htest,m,s,sm,ss,2);// 2 to fit with pol1

      //} //end of ybin

       c->Print(TString(c->GetName())+TString("_cert.png"));
      //c->Print(TString(c->GetName())+TString("_cert.eps"));
      c->Print(TString(c->GetName())+TString("_cert.pdf"));
   } //end of trigger loop

}

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
      fit0->SetLineWidth(1);   
      
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
      fit0->SetLineWidth(1);

      m      = fit0->GetParameter(0);
      s      = fit0->GetParError(0);
      sm     = fit0->GetParameter(1);
      ss     = fit0->GetParError(1);
  
      prob1 = TMath::Prob(fit0->GetChisquare(),fit0->GetNDF());
      cout << " prob1  " << prob1 << " chisq " << fit0->GetChisquare() << " ndf " << fit0->GetNDF() <<  endl;
   }
}

//////////////////////////////////////////////////////////////////////////////
void WeightedMeanD(TH1D *h, double &m, double &s, double &sm, double &ss, int mode)
{
   double w[1000],x[1000],e[1000];
   double sumx(0.0),sumx2(0.0),sumw(0.0);
   int N(0);
    
   TF1  *fit0;
   if(mode==1) fit0 = new TF1("fit0","pol0");
   if(mode==2) fit0 = new TF1("fit0","pol1");
 
 //     fit0->SetLineStyle(2);
      fit0->SetLineStyle(kDashed);
      fit0->SetLineWidth(1);
   
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
      fit0->SetLineWidth(1);
   
      m      = fit0->GetParameter(0);
      s      = fit0->GetParError(0);
      sm     = fit0->GetParameter(1);
      ss     = fit0->GetParError(1);
   
      prob1 = TMath::Prob(fit0->GetChisquare(),fit0->GetNDF());
      cout << " prob1  " << prob1 << " chisq " << fit0->GetChisquare() << " ndf " << fit0->GetNDF() <<  endl;
   }
}
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
void LoadStyle()
{
   //gROOT->Reset();

   gROOT->SetStyle("Plain");
   gStyle->SetPalette(1);
   gStyle->SetPaperSize(21,28);

   gStyle->SetPadColor(10);
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   gStyle->SetPadGridX(0);
   gStyle->SetPadGridY(0);
 
   gStyle->SetFillColor(10);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);
   gStyle->SetCanvasColor(10);

   //gStyle->SetHistFillColor(2);
   //gStyle->SetHistFillStyle(1001);//solid
   gStyle->SetHistFillStyle(3001);//solid
   //gStyle->SetHistFillStyle(3004);//nice hatch style
     
   //gStyle->SetFrameFillColor(10);
   gStyle->SetFrameFillColor(18);
   gStyle->SetFrameLineWidth(1.5);   

   gStyle->SetLegendBorderSize(0);   

   gStyle->SetStatColor(10);   
   gStyle->SetStatBorderSize(1);   
   //gStyle->SetOptStat(1111111);
   gStyle->SetOptStat(0);
   //gStyle->SetStatX(0.87);   
   //gStyle->SetStatY(0.87);   
   gStyle->SetStatX(0.9);   
   gStyle->SetStatY(0.985);   
   gStyle->SetStatW(0.19);   
   gStyle->SetStatH(0.1);   

   gStyle->SetTitleX(0.15);   
   gStyle->SetTitleY(0.985);   
   //gStyle->SetTitleW(0.2);   
   //gStyle->SetTitleH(0.09);   
   gStyle->SetTitleFillColor(10);
   gStyle->SetTitleBorderSize(0);
   //gStyle->SetOptTitle(0);

   //gStyle->SetTitleSize(0.03,"yz");
   //gStyle->SetTitleSize(0.09,"x");
   //gStyle->SetTitleOffset(0.53,"x");
   gStyle->SetTitleOffset(1.6,"y");

   //gStyle->SetLabelSize(0.06,"X");
   //gStyle->SetLabelSize(0.05,"Y");
   //gStyle->SetLabelSize(0.05,"Z");
   //gStyle->SetLabelOffset(0.01,"X");
   //gStyle->SetLabelOffset(0.01,"Y");

   gStyle->SetLabelSize(0.04,"X");
   gStyle->SetLabelSize(0.04,"Y");
   gStyle->SetLabelSize(0.03,"Z");

   gStyle->SetMarkerColor(2);
   gStyle->SetMarkerSize(3);
   gROOT->ForceStyle();   
   
   gStyle->SetLabelFont(42,"xyz");
   gStyle->SetTitleFont(42);
   gStyle->SetTitleFont(42,"xyz");
   gStyle->SetStatFont(42);
   gStyle->SetFrameFillColor(10);
   gROOT->ForceStyle();
}
//////////////////////////////////////////////////////////////////////////////

 
  
  
