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


void Reading_workspace(int func, int alphabin) {

double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

char func_name[1024];
if (func==0) sprintf(func_name,"Dijet");
if (func==1) sprintf(func_name,"PowExp");
if (func==2) sprintf(func_name,"ModDijet");


char fname[1024];
sprintf(fname, "output/Wide_Resonances_Run2_4parFits/BkgFits/%s-4p/DijetFitResults_PFDijetRun2_4J_alphabin%d.root", func_name, alphabin);

TFile *f = new TFile(fname, "READ");

// Retrieve workspace from file
char wname[1024];
sprintf(wname, "wPFDijetRun2_4J_alphabin%d", alphabin);

RooWorkspace *w = (RooWorkspace*)f->Get(wname) ;     //loads the workspace from file
w->Print();

//https://root.cern.ch/root/html/tutorials/roofit/rf503_wspaceread.C.html
// R e t r i e v e   p d f ,   d a t a   f r o m   w o r k s p a c e
// -----------------------------------------------------------------

char bkg_binned_name[1024], bkg_unbinned_name[1024];
sprintf(bkg_binned_name, "PFDijetRun2_4J_alphabin%d_bkg", alphabin);
sprintf(bkg_unbinned_name, "PFDijetRun2_4J_alphabin%d_bkg_unbin", alphabin);

RooAbsPdf *Bkg_binned = w->pdf(bkg_binned_name);
RooAbsPdf *Bkg_unbinned = w->pdf(bkg_unbinned_name);

RooRealVar *th1x = w->var("th1x") ;                           
RooRealVar *mjj  = w->var("mjj") ;

RooPlot *th1x_frame = th1x->frame(Title("Binned bkg-only standard fit")) ;  //creates a RooPlot (like Canvas) corresponding to th1x variable
RooPlot *mjj_frame  = mjj->frame(Title("Unbinned bkg-only standard fit")) ;
  
Bkg_binned->plotOn(th1x_frame);                                            //Draws the pdf on the RooPlot
Bkg_unbinned->plotOn(mjj_frame);  

TH1 *unbinned = Bkg_unbinned->createHistogram("mjj",500000);   //6697 is the number of total bins (1GeV bin) from 1455 to 8152

////////////////////GET THE INTEGRAL FROM THE STANDARD BINNED HISTOGRAM OF DATA!!!!!!!!! /////////////////////////////////////////////////////////////

char fhistname[1024];
sprintf(fhistname, "Fitting/4ParFits/HISTOS_4J_AlldataRun2_SR_alphabin%d.root", alphabin);
TFile *fhist = new TFile(fhistname, "READ");
TH1D *hist = (TH1D*)fhist->Get("h_FourjetMass");
double integral_data = hist->Integral(); 

unbinned->Scale(integral_data); 
unbinned->Print();
 
TH1D *Bkg_fit_binned = new TH1D("Bkg_fit_binned","Binned bkg-only standard fit",103,massBoundaries);  
TH1D *Bkg_fit_unbinned = new TH1D("Bkg_fit_unbinned","Unbinned bkg-only standard fit",14000,0,14000);  


for(int i=0; i<500000; i++)
{
    double val  = unbinned->GetBinContent(i);
    double xval  = unbinned->GetBinCenter(i);
    Bkg_fit_unbinned->Fill(xval,val);
    Bkg_fit_binned->Fill(xval,val);
}

//Bkg_fit_unbinned->Draw();

char foutname[1024];
sprintf(foutname, "Fitting/4ParFits/DijetFitResult_PFDijetRun2_4J_alphabin%d_%s.root", alphabin, func_name);

TFile *fout= new TFile(foutname,"RECREATE");
fout->cd();
Bkg_fit_unbinned->Write();
Bkg_fit_binned->Write();


}
