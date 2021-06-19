//IT NEEDS 'cmsenv' TO READ SOME DIJET WORSPACES!!!

#include "RooGlobalFunc.h"
//#include "RooDijetBinPdf.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TFile.h"
#include "TH1.h"
using namespace RooFit ;


void Make_Histo_of_Standard_Fit() {

//int nMassBins=103;

	double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};





// R e a d   w o r k s p a c e   f r o m   f i l e
  // -----------------------------------------------

  // Open input file with workspace 
//  TFile *f = new TFile("../Final_Results_EXO-19-012/Standard_Fit/DijetFitResults_PFDijet2017.root") ;    //2016+2017 file
  TFile *f = new TFile("../Final_Results_EXO-19-012/2016_paper_tests/DijetFitResults_PFDijet2016.root") ;    //2016 paper file, 36fb^-1
  //TFile *f = new TFile("../Standard_Fit_Wide_Resonances_2017/DijetFitResults_PFDijet2017.root ") ;	                //2017 file
  //TFile *f = new TFile("../Re-reco_Limits_2017/2017/DijetFitResults_PFDijet2017_mjj1530_JEC2017_41p85FB.root");          //2017 file  new JEC
  //TFile *f = new TFile("../Standard_Fit_2016_data_Final/DijetFitResults_PFDijet2016.root ") ;				//2016 file


  // Retrieve workspace from file
  RooWorkspace* w = (RooWorkspace*) f->Get("wPFDijet2016") ;     //loads the workspace from file


  w->Print();

  //https://root.cern.ch/root/html/tutorials/roofit/rf503_wspaceread.C.html
  // R e t r i e v e   p d f ,   d a t a   f r o m   w o r k s p a c e
  // -----------------------------------------------------------------

  //TObject* BkgFit = (TObject*) f->Get("nll_extDijetPdf_data_obs"); 

   //RooDataHist* da = (RooDataHist*) w->data("data_obs") ;    //Gets the RooDataHist from the workspace -this can be ploted on a frame or converted to TH1
    //TH1 *h_da = da->createHistogram("th1x",31);                 //converts RooDataHist to TH1 histogram with 31 bins 

   RooAbsPdf* Bkg_binned = w->pdf("PFDijet2016_bkg") ;           //gets the p.d.f. binned
   RooAbsPdf* Bkg_unbinned = w->pdf("PFDijet2016_bkg_unbin") ;   //gets the p.d.f. unbinned

   RooRealVar* th1x = w->var("th1x") ;                           //gets the variable
   RooRealVar* mjj = w->var("mjj") ;
   //RooRealVar* p0_PFDijet2016 = w->var("p0_PFDijet2016") ;
   //RooRealVar* p1_PFDijet2016 = w->var("p1_PFDijet2016") ;
   //RooRealVar* p2_PFDijet2016 = w->var("p2_PFDijet2016") ;
   //RooRealVar* p3_PFDijet2016 = w->var("p3_PFDijet2016") ;


   RooPlot* th1x_frame = th1x->frame(Title("Binned bkg-only standard fit")) ;  //creates a RooPlot (like Canvas) corresponding to th1x variable
   RooPlot* mjj_frame = mjj->frame(Title("Unbinned bkg-only standard fit")) ;
  
   //BkgFit->plotOn(th1x_frame);
   Bkg_binned->plotOn(th1x_frame);                                            //Draws the pdf on the RooPlot
   Bkg_unbinned->plotOn(mjj_frame);  

   //th1x_frame->Draw();
   //mjj_frame->Draw();

   TH1 *unbinned = Bkg_unbinned->createHistogram("mjj",10000000);              //6697 is the number of total bins (1GeV bin) from 1455 to 8152
   //TH1 *binned = Bkg_unbinned->createHistogram("th1x",31);

////////////////////GET THE INTEGRAL FROM THE STANDARD BINNED HISTOGRAM OF DATA!!!!!!!!! /////////////////////////////////////////////////////////////

   //unbinned->Scale(3685313);     //Scale the histogram to the data: 6485460 for 2016 & 3110740 for 2017 , 4754350 for 2016 + 2017, 2641904 (for 2017 data with new JEC starting from 1530 GeV)
									// 1324440 for ABC 18
									//1503910  for D 18
									//2828350  for both
									//5009750  16+17+ABC18
 //  unbinned->Scale(6557850.);
   unbinned->Scale(6485470.);            //36fb 2016 paper, 1246-8752  
   unbinned->Print();

   

   TH1D *Bkg_fit_binned = new TH1D("Bkg_fit_binned","Binned bkg-only standard fit",103,massBoundaries);  
   TH1D *Bkg_fit_unbinned = new TH1D("Bkg_fit_unbinned","Unbinned bkg-only standard fit",14000,0,14000);  


  for(int i=0; i<10000000; i++)
  {
	double val  = unbinned->GetBinContent(i);
	double xval  = unbinned->GetBinCenter(i);
	Bkg_fit_unbinned->Fill(xval,val);
	Bkg_fit_binned->Fill(xval,val);
  }

//TH1D *Binned_CR_fit_ = (TH1D*) Bkg_fit_binned->Clone();
//TH1D *Smoothed_CR_fit = (TH1D*) Bkg_fit_unbinned->Clone();
//Smoothed_CR_fit_scaled->Scale(389656);

 Bkg_fit_unbinned->Draw();

//TFile *fout= new TFile("../Final_Results_EXO-19-012/Standard_Fit/DijetFitResult_16AugV11_17v6_18v10.root","RECREATE");
TFile *fout= new TFile("../Final_Results_EXO-19-012/2016_paper_tests/DijetFitResult_16paper_36fb.root","RECREATE");
fout->cd();
Bkg_fit_unbinned->Write();
Bkg_fit_binned->Write();
//Smoothed_CR_fit_scaled->SetName("Smoothed_SR_fit_scaled");
//Smoothed_CR_fit_scaled->Write();


}
