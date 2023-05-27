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
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TLatex.h"
#include "setTDRStyle_teliko.C"
#include "TH1.h"

void Fit_BkgOnly(){

  double lumi 	     = 137000.;    //35900 for 2016, 41850 for 2017, 77750 for 2016+2017
  double startit     = 1607; //1530.;
  double endit	     = 9067.;
  gROOT->LoadMacro("setTDRStyle.C");
  setTDRStyle();

  const int nMassBins = 103;
  const int nMassBins_V2=32.;
  
  double qq_A_obs_limit = 0.0014*0.01; //bin8
  double r = 0.0008; //from simult. fit
  cout<<"Scaling = "<<qq_A_obs_limit<<"  "<<qq_A_obs_limit*lumi<<endl;

  ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls( 100000000);   //set the number of parameter searches for convergence
  
  TFile *f_SIGNAL = new TFile("ResonanceShapes_Suu8400_Chi2100_SR_alphabin8.root","READ"); //1 GeV bin
  TFile *f_HISTO = new TFile("HISTOS_4J_Alldata_SR_alphabin8.root","READ"); //1 GeV bin
 
  double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325, //22
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530., 1607, //47
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, //70
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395,12827, 13272, 13732, 14000};

  double massBoundaries_V2[nMassBins_V2+1] = {  325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530., 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231};

  TH1D *signal_data_1GeV      = (TH1D*)(f_HISTO->Get("h_FourjetMass_1GeV"));
  TH1D *signal_data           = new TH1D("signal_data","signal_data",nMassBins,massBoundaries);  
  TH1D *Fit                   = new TH1D("Fit","Fit",nMassBins,massBoundaries);

  TH1D *FitC                  = new TH1D("FitC","FitC",nMassBins_V2,massBoundaries_V2);
  TH1D *FitB                  = new TH1D("FitB","FitB",nMassBins_V2,massBoundaries_V2);
  TH1D *FitA                  = new TH1D("FitA","FitA",nMassBins,massBoundaries); //nMassBins_V2,massBoundaries_V2);
  TH1D *FitR                  = new TH1D("FitR","FitR",nMassBins,massBoundaries);
  TH1D *shape_qq_A            = (TH1D*)(f_SIGNAL->Get("h_FourjetMass1GeV")); //h_FourjetMass"));
  TH1D *Fit2                  = new TH1D("Fit2","Fit2",nMassBins,massBoundaries);
  TH1D *Blank       	      = (TH1D*)(signal_data ->Clone());
  TH1D *pullFit               = (TH1D*)(signal_data->Clone());
  TH1D *shape_qq_binned        = new TH1D("shape_qq_binned","shape_qq_binned",nMassBins,massBoundaries);  

  signal_data->SetMarkerStyle(8);
  signal_data->SetLineColor(1);
  signal_data->SetMarkerColor(1);
  signal_data->GetXaxis()->SetRangeUser(startit,endit);
  signal_data->GetYaxis()->SetRangeUser(0.0000001,10.);
  Blank->SetMarkerColor(0); 
  Blank->SetLineColor(0);

  double chi_square_SF=0;
  int NDF_SF=0;

  shape_qq_A->Scale(qq_A_obs_limit*lumi);
  
  for(int i=0; i<shape_qq_A->GetNbinsX(); i++){
	double val  = shape_qq_A->GetBinContent(i); //if(val>0) cout<<i<<"  "<<val<<endl;
	double xval  = shape_qq_A->GetBinCenter(i);
	shape_qq_binned->Fill(xval,val);		
  }

  for(int i=0; i<signal_data_1GeV->GetNbinsX(); i++){
	 double val  = signal_data_1GeV->GetBinContent(i);
	 double xval  = signal_data_1GeV->GetBinCenter(i);
	 signal_data->Fill(xval,val);		
  }

 //cout<<signal_data->Integral()<<" "<<shape_qq_binned->Integral()<<"  "<<shape_qq_A->Integral()<<endl;
for(int i=0; i<103; i++){
 cout<<i+1<<"  "<<signal_data->GetBinContent(i)<<" "<<shape_qq_binned->GetBinContent(i)<<endl;
}


  //dijet function

  TF1 *func2 = new TF1("func2","([0])*(1-x/13000.)**([1])/( (x/13000.)**([2]+[3]*log(x/13000.)+[4]*log(x/13000.)**2.)   )",1607.,8447.);

  func2->SetParameter(0.,3e-11); // 2.63225e-03);//-06
  func2->SetParameter(1., 3.5821e+00 );
  func2->SetParameter(2, 1.1758e+01);  
  func2->FixParameter(3, 0.0e+00);
  func2->FixParameter(4, 0.0e+00);
  func2->FixParameter(5, 0.0e+00);

  for(Int_t i=1;i<=signal_data->GetNbinsX();i++){

       if (signal_data->GetBinContent(i) < 30) signal_data->SetBinError(i, 0.5 + sqrt( signal_data->GetBinContent(i) + 0.25 ) ); 
       signal_data->SetBinContent(i,1000*signal_data->GetBinContent(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));
       signal_data->SetBinError(i,1000*signal_data->GetBinError(i)/((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi));
  }


TGraphAsymmErrors * signal_datag = new TGraphAsymmErrors(signal_data);

 for(Int_t i=1;i<=signal_data->GetNbinsX();i++) {

      double edata_signal   = signal_data->GetBinError(i); 
      double alpha = 1-0.6827;
      double cont = signal_data->GetBinContent(i)*((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi)/1000.;
      double errl,errh,sqr;

      if(cont<=0) errl = 0;
      if(cont<=0) errh = 1.8;

      if(cont>0 && cont < 20){
       	  errl = cont - ROOT::Math::gamma_quantile(alpha/2,cont,1.);
      	  errh = ROOT::Math::gamma_quantile_c(alpha/2,cont+1,1.)-cont;
      }
      if(cont>0 && cont >= 20){
           errl = sqrt(cont); 
           errh = sqrt(cont);
      }

        sqr=sqrt(cont)*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);
        errl = errl*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);
        errh = errh*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);

        /*std::cout<<"i = "<<i<<std::endl;
        std::cout<<"errl = "<<errl<<std::endl;
        std::cout<<"errh = "<<errh<<std::endl;
        std::cout<<"sqr = "<<sqr<<std::endl;
        std::cout<<"cont = "<<cont<<std::endl;*/

       double edata_signal2 = ( errl + errh )/2.;
     
	signal_datag->SetPointEYlow(i-1, errl); 
        signal_datag->SetPointEYhigh(i-1, errh);
// TEST NS setting error of X bins to zero
        signal_datag->SetPointEXlow(i-1, 0.);
        signal_datag->SetPointEXhigh(i-1, 0.);
    }

 signal_datag->Fit("func2","","",1607., 8447.);
 cout << "func2: Chi2 = " <<  func2->GetChisquare() << " NDF = " << func2->GetNDF() << endl;

 for(Int_t i=1;i<=signal_data->GetNbinsX();i++) {

      double edata_signal   = signal_data->GetBinError(i);
      double alpha = 1-0.6827;
      double cont = signal_data->GetBinContent(i)*((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi)/1000.;
      double errl,errh,sqr;

      if(cont<=0) errl = 0;
      if(cont<=0) errh = 1.8;

      if(cont>0 && cont < 20){
          errl = cont - ROOT::Math::gamma_quantile(alpha/2,cont,1.);
          errh = ROOT::Math::gamma_quantile_c(alpha/2,cont+1,1.)-cont;
      }
      if(cont>0 && cont >= 20){
           errl = sqrt(cont);
           errh = sqrt(cont);
      }

        sqr=sqrt(cont)*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);
        errl = errl*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);
        errh = errh*1000./((signal_data->GetBinLowEdge(i+1)-signal_data->GetBinLowEdge(i))*lumi);

	shape_qq_binned->SetBinContent(i,1000*shape_qq_binned->GetBinContent(i)/((shape_qq_binned->GetBinLowEdge(i+1)-shape_qq_binned->GetBinLowEdge(i))*lumi));
		
	double data_signal    = signal_data->GetBinContent(i);
	double mjj   	      = signal_data->GetBinCenter(i);
        double Fit_A          = func2->Eval(mjj);

         FitA->SetBinContent(i,Fit_A);         
	 if(edata_signal>0 && edata_signal==edata_signal){ 

              if(data_signal>Fit_A) pullFit->SetBinContent(i,(-Fit_A+data_signal)/errl);
              if(data_signal<Fit_A) pullFit->SetBinContent(i,(-Fit_A+data_signal)/errh);  
                              
	      if(mjj>=startit && mjj<= endit && cont!= 0 ){
                  double chi_s_i = pullFit->GetBinContent(i)*pullFit->GetBinContent(i);
                  std::cout<<"Chisquare for the i-th bin is "<<chi_s_i<<std::endl;	
		  chi_square_SF = chi_square_SF + pullFit->GetBinContent(i)*pullFit->GetBinContent(i); cout<<"!!!!"<<chi_square_SF<<"  "<< pullFit->GetBinContent(i)<<endl;
		  NDF_SF        = NDF_SF + 1 ;
	      }
	 } else pullFit->SetBinContent(i,0);
  } 

  cout << " chi2 =  " << chi_square_SF << " number of bins in the fit range = " << NDF_SF << endl;

  TPaveText *paveCMS = new TPaveText(0.16,0.96,0.96,0.99,"NDC");
  paveCMS->AddText("CMS             #sqrt{s} = 13 TeV         L = 137 fb^{-1}");
  paveCMS->SetFillColor(0);
  paveCMS->SetBorderSize(0);
  paveCMS->SetTextSize(0.04);

  TPaveText *paveCMS2 = new TPaveText(0.2,0.00,0.5,0.28,"NDC");
  paveCMS2->SetFillColor(0);
  paveCMS2->SetBorderSize(0);
  paveCMS2->SetFillStyle(0);
  paveCMS2->SetTextFont(42);
  paveCMS2->SetTextSize(0.045);
  paveCMS2->SetTextAlign(11);        
  //paveCMS2->AddText("Wide PF-jets"); 
  Char_t pave[1024];
  //sprintf(pave,"m_{jj} > %3.2f TeV",startit/1000.);   
  paveCMS2->AddText(pave);
  //paveCMS2->AddText("|#eta| < 2.5, |#Delta#eta| < 1.1");
  Char_t chi_sq_SF[1024];
  //sprintf(chi_sq_SF,"#chi^{2}/NDF = %3.2f / %3.2i ",chi_square_SF, 28); 
  // sprintf(chi_sq_SF,"#chi^{2}/NDF = %3.2f / %3.2i ", func2->GetChisquare()	,func2->GetNDF()); 
  //paveCMS2->AddText(chi_sq_SF); 

  cout << "func2" << "Chi2 " <<  func2->GetChisquare() << " NDF " << func2->GetNDF() << endl;
  //cout << "func3" << "Chi2 " <<  func3->GetChisquare() << " NDF " << func3->GetNDF() << endl;
  //cout << "func4" << "Chi2 " <<  func4->GetChisquare() << " NDF " << func4->GetNDF() << endl;

  TLegend *leg = new TLegend(.70, .75, .60, .93); //0.7,0.53,0.8,0.93);
  leg->AddEntry(signal_data,   "Data ","p");
  leg->AddEntry(func2, "Dijet Function", "L");
  //leg->AddEntry(func3, "ATLAS Function", "L");
  leg->AddEntry(shape_qq_binned,"Signal","L");
  leg->SetTextSize(0.04);

  pullFit->SetLineColor(8);
  pullFit->SetMarkerColor(8);
  pullFit->GetXaxis()->SetRangeUser(startit,endit);
  pullFit->GetYaxis()->SetRangeUser(-3.5,3.5);	      	      

  TCanvas *c1 = new TCanvas("c1","Signal region Data & Prediction",600,700);
  c1->Divide(1,2,0,0,0);
        
  TVirtualPad *pad1r; 
  pad1r = c1->GetPad(1);
  pad1r->SetPad(0.01,0.37,0.99,0.98);
  pad1r->SetRightMargin(0.05);
  pad1r->SetTopMargin(0.05);
  pad1r->SetLeftMargin(0.175);
  pad1r->SetFillColor(0);
  pad1r->SetBorderMode(0);
  pad1r->SetFrameFillStyle(0);
  pad1r->SetFrameBorderMode(0);
  pad1r->Draw();
  pad1r->cd();
  pad1r->cd()->SetLogy(1);
  pad1r->cd()->SetLogx(1);
  //signal_data->GetXaxis()->SetRangeUser(0.01,35000.);

  signal_datag->GetYaxis()->SetTitle("d #sigma / dm_{4j}  [pb/TeV]");
  signal_datag->GetYaxis()->SetTitleSize(0.06);
  signal_datag->GetYaxis()->SetTitleOffset(1.2);
  signal_datag->SetMarkerStyle(8);
  signal_datag->SetLineColor(1);
  signal_datag->SetMarkerColor(1);
  signal_datag->GetXaxis()->SetRangeUser(startit,endit);
  signal_datag->GetYaxis()->SetRangeUser(0.0000001,10.);
  signal_datag->Draw("AP");
  FitA->SetLineColor(6);

  func2->SetLineColor(4);
  func2->Draw("same");
  shape_qq_binned->SetLineColor(2);
  shape_qq_binned->SetLineStyle(7);
  shape_qq_binned->Draw("same HIST");  
  TLatex *l = new TLatex();     
  l->SetTextAlign(11);
  l->SetTextSize(0.055);
  l->SetNDC();
  l->SetTextFont(62);
  l->DrawLatex(0.18,0.955,"CMS #it{Preliminary}");
  l->SetTextFont(52);
  l->SetTextFont(42);
  l->DrawLatex(0.69,0.955,"137 fb^{-1} (13 TeV)");
  leg->Draw("same");
  c1->cd();

  TVirtualPad *pad2r ;
  pad2r = c1->GetPad(2);
  pad2r->SetLeftMargin(0.175);
  pad2r->SetPad(0.01,0.02,0.99,0.37);
  pad2r->SetBottomMargin(0.35);
  pad2r->SetRightMargin(0.05);
  pad2r->Draw();
  pad2r->cd(); 
  pad2r->cd()->SetLogx(1);
  pad2r->SetGridx();
  pad2r->SetGridy();

  pullFit->GetXaxis()->SetTitle("Fourjet Mass [TeV]");
  pullFit->GetXaxis()->SetNoExponent();    
  pullFit->GetXaxis()->SetMoreLogLabels();  
  pullFit->GetXaxis()->SetTitleSize(2*0.06);
  pullFit->GetYaxis()->SetTitleSize(2*0.06);
  pullFit->GetXaxis()->SetLabelSize(2*0.07);
  pullFit->GetYaxis()->SetLabelSize(0.09);
  pullFit->GetXaxis()->SetLabelOffset(10);
  pullFit->GetXaxis()->SetTitleOffset(1.2);
  pullFit->GetYaxis()->SetTitleOffset(0.6);
  pullFit->GetYaxis()->SetNdivisions(210);
  pullFit->SetLineWidth(1);
  pullFit->SetYTitle("#frac{(Data-Prediction)}{Uncertainty}");
  TLine *sk = new TLine(startit,0.,endit,0.);
  pullFit->SetFillStyle(3244);
  pullFit->SetFillColor(8);
  pullFit->SetLineWidth(1);
  pullFit->Draw("same hist");

  TLatex *xLab = new TLatex();
  xLab->SetTextAlign(22);
  xLab->SetTextFont(40);
  xLab->SetTextSize(2*0.05);         
  xLab->DrawLatex(1530, -4.15, "1.5");
  xLab->DrawLatex(2000, -4.15, "2");
  xLab->DrawLatex(3000, -4.15, "3");
  xLab->DrawLatex(4000, -4.15, "4");
  xLab->DrawLatex(5000, -4.15, "5");
  xLab->DrawLatex(6000, -4.15, "6");
  xLab->DrawLatex(7000, -4.15, "7");
  xLab->DrawLatex(8000, -4.15, "8");

}
