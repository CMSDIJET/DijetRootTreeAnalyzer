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
#include "TLatex.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TH1.h"
#include "setTDRStyle.C"

void Plot_SignalShapes(){

setTDRStyle();

char name[500];

double FourjetMass, Maverage, Masymmetry, DeltaEtaJJAK4, DeltaRAK4_First, DeltaRAK4_Second, alpha;

const int nMassBins = 103;
   
//double massBoundaries[nMassBins+1] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
//     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
//     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 
//     4509,
//     4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
//     10430,
//     10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

double massBoundaries[nMassBins+1] = {1/1000., 3/1000., 6/1000., 10/1000., 16/1000., 23/1000., 31/1000., 40/1000., 50/1000., 61/1000., 74/1000., 88/1000., 103/1000., 119/1000., 137/1000., 156/1000., 176/1000., 197/1000., 220/1000., 244/1000., 270/1000., 296/1000., 325/1000.,
     354/1000., 386/1000., 419/1000., 453/1000., 489/1000., 526/1000., 565/1000., 606/1000., 649/1000., 693/1000., 740/1000., 788/1000., 838/1000., 890/1000., 944/1000., 1000/1000., 1058/1000., 1118/1000., 1181/1000., 1246/1000., 1313/1000., 1383/1000., 1455/1000., 1530/1000., 1607/1000.,
     1687/1000.,1770/1000., 1856/1000., 1945/1000., 2037/1000., 2132/1000., 2231/1000., 2332/1000., 2438/1000., 2546/1000., 2659/1000., 2775/1000., 2895/1000., 3019/1000., 3147/1000., 3279/1000., 3416/1000., 3558/1000., 3704/1000., 3854/1000., 4010/1000., 4171/1000., 4337/1000., 
     4509/1000.,
     4686/1000., 4869/1000., 5058/1000., 5253/1000., 5455/1000., 5663/1000., 5877/1000., 6099/1000., 6328/1000., 6564/1000., 6808/1000., 7060/1000., 7320/1000., 7589/1000., 7866/1000., 8152/1000., 8447/1000., 8752/1000., 9067/1000., 9391/1000., 9726/1000., 10072/1000.,
     10430/1000.,
     10798/1000., 11179/1000., 11571/1000., 11977/1000., 12395/1000., 12827/1000., 13272/1000., 13732/1000., 14000/1000.};

//TPaveText *cms1 = new TPaveText(0.22,0.81,0.47,0.86,"NDC"); //for PAS - ilias
TPaveText *cms1 = new TPaveText(0.17,0.795,0.4,0.845,"NDC"); //for PAPER - ilias
//cms1->AddText("CMS #scale[0.9]{#it{#bf{Simulation Preliminary}}}"); //for PAS - ilias
cms1->AddText("#splitline{CMS}{#scale[0.7]{#it{#bf{Simulation}}}}"); //for PAPER - ilias
cms1->SetBorderSize(0);
cms1->SetFillColor(0);
cms1->SetTextSize(0.06); //0.04 w/o Preliminary

TPaveText *cms2 = new TPaveText(0.82,0.915,0.97,0.965,"NDC"); //0.8,0.92,0.95,0.97
cms2->AddText("#bf{13 TeV}");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.04);

TPaveText *cms3 = new TPaveText(0.56,0.81,0.78,0.86,"NDC"); //0.6,0.81,0.82,0.86,"NDC"
cms3->AddText("Diquark: S #rightarrow #chi#chi #rightarrow (ug)(ug)");
cms3->SetTextFont(42);
cms3->SetBorderSize(0);
cms3->SetFillColor(0);
cms3->SetTextSize(0.04);

char hist_name[1024];
char legentry[1024];

TCanvas *c = new TCanvas();
c->cd();

TLegend *l = new TLegend(0.45, 0.55, 0.7, 0.8); //0.55, 0.55, 0.75, 0.8
l->SetBorderSize(0);
l->SetTextSize(0.04);
//l->SetHeader("S_{uu} #rightarrow #chi#chi #rightarrow (ug)(ug)");


TPaveText *t = new TPaveText(0.62,0.42,0.72,0.52,"NDC"); //0.67,0.42,0.77,0.52,"NDC"
t->AddText("0.24 < #alpha < 0.26");
t->SetTextFont(42);
t->SetBorderSize(0);
t->SetFillColor(0);
t->SetTextSize(0.04);

int color = 0;

//Plot generated/simulated shapes at 2,4,6,8 TeV
for (int mass=2000; mass<=8000; mass=mass+2000)
{
	color++;
	double chi = mass*0.25;

	sprintf(name,"root:://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/eirini/4jets/Signal/MC2017/newGeneratedSignals/MC2017_Suu_Diquark_S%d_chi%.0f_reduced_skim.root", mass, chi);
	//sprintf(name,"MC2017_Suu_Diquark_S%d_chi%.0f_reduced_skim.root", mass, chi);

	cout << "Root file : " << name << endl;

	TFile *f = new TFile(name,"READ");

	TH1D *h_mass1, *h_mass2, *h_mass3, *h_mass4, *h_mass5, *h_mass6, *h_mass7, *h_mass8, *h_mass9, *h_mass10, *h_mass11, *h_mass12, *h_mass13, *h_mass_noslices; 

	if (f->IsOpen())
	{
		h_mass1 = new TH1D("h_mass1","",nMassBins,massBoundaries);
		h_mass2 = new TH1D("h_mass2","",nMassBins,massBoundaries);
		h_mass3 = new TH1D("h_mass3","",nMassBins,massBoundaries);
		h_mass4 = new TH1D("h_mass4","",nMassBins,massBoundaries);
		h_mass5 = new TH1D("h_mass5","",nMassBins,massBoundaries);
		h_mass6 = new TH1D("h_mass6","",nMassBins,massBoundaries);
		h_mass7 = new TH1D("h_mass7","",nMassBins,massBoundaries);
		h_mass8 = new TH1D("h_mass8","",nMassBins,massBoundaries);
		h_mass9 = new TH1D("h_mass9","",nMassBins,massBoundaries);
		h_mass10 = new TH1D("h_mass10","",nMassBins,massBoundaries);
		h_mass11 = new TH1D("h_mass11","",nMassBins,massBoundaries);
		h_mass12 = new TH1D("h_mass12","",nMassBins,massBoundaries);
		h_mass13 = new TH1D("h_mass13","",nMassBins,massBoundaries);
		h_mass_noslices = new TH1D("h_mass_noslices","",nMassBins,massBoundaries);

		h_mass1->Sumw2();
		h_mass2->Sumw2();
		h_mass3->Sumw2();
		h_mass4->Sumw2();
		h_mass5->Sumw2();
		h_mass6->Sumw2();
		h_mass7->Sumw2();
		h_mass8->Sumw2();
		h_mass9->Sumw2();
		h_mass10->Sumw2();
		h_mass11->Sumw2();
		h_mass12->Sumw2();
		h_mass13->Sumw2();
		h_mass_noslices->Sumw2();

		TTree *tree = (TTree*)(f->Get("rootTupleTree/tree"));

		tree->SetBranchAddress("FourjetMass",&FourjetMass);
  		tree->SetBranchAddress("Maverage",&Maverage);
  		tree->SetBranchAddress("Masymmetry",&Masymmetry);
  		tree->SetBranchAddress("DeltaEtaJJAK4",&DeltaEtaJJAK4);
  		tree->SetBranchAddress("DeltaRAK4_First",&DeltaRAK4_First);
  		tree->SetBranchAddress("DeltaRAK4_Second",&DeltaRAK4_Second);
	   
		int nentries=(Int_t)tree->GetEntries(); 
		std::cout<<"Number of entries =  "<<nentries<<std::endl;
		for (int i=0; i<nentries; i++)    //event loop
		{     
			tree->GetEntry(i);

			if(Masymmetry<0.1 && DeltaEtaJJAK4<1.1 && DeltaRAK4_First<2.0 && DeltaRAK4_Second<2.0) 
			{
				alpha=Maverage/FourjetMass; 
				if (alpha>0.10 && alpha<0.12) h_mass1->Fill(FourjetMass/1000.);
				if (alpha>0.12 && alpha<0.14) h_mass2->Fill(FourjetMass/1000.);
				if (alpha>0.14 && alpha<0.16) h_mass3->Fill(FourjetMass/1000.);
				if (alpha>0.16 && alpha<0.18) h_mass4->Fill(FourjetMass/1000.);
				if (alpha>0.18 && alpha<0.20) h_mass5->Fill(FourjetMass/1000.);
				if (alpha>0.20 && alpha<0.22) h_mass6->Fill(FourjetMass/1000.);
				if (alpha>0.22 && alpha<0.24) h_mass7->Fill(FourjetMass/1000.);
				if (alpha>0.24 && alpha<0.26) h_mass8->Fill(FourjetMass/1000.);
				if (alpha>0.26 && alpha<0.28) h_mass9->Fill(FourjetMass/1000.);
				if (alpha>0.28 && alpha<0.30) h_mass10->Fill(FourjetMass/1000.);
				if (alpha>0.30 && alpha<0.32) h_mass11->Fill(FourjetMass/1000.);
				if (alpha>0.32 && alpha<0.34) h_mass12->Fill(FourjetMass/1000.);
				if (alpha>0.34) h_mass13->Fill(FourjetMass/1000.);

				if (alpha>0.10) h_mass_noslices->Fill(FourjetMass/1000.);
			}
		}
	
	}

	h_mass1->Scale(1./h_mass1->Integral());	
	h_mass2->Scale(1./h_mass2->Integral());
	h_mass3->Scale(1./h_mass3->Integral());
	h_mass4->Scale(1./h_mass4->Integral());
	h_mass5->Scale(1./h_mass5->Integral());
	h_mass6->Scale(1./h_mass6->Integral());
	h_mass7->Scale(1./h_mass7->Integral());
	//h_mass8->Scale(1./h_mass8->Integral());
	h_mass9->Scale(1./h_mass9->Integral());
	h_mass10->Scale(1./h_mass10->Integral());
	h_mass11->Scale(1./h_mass11->Integral());
	h_mass12->Scale(1./h_mass12->Integral());
	h_mass13->Scale(1./h_mass13->Integral());
	h_mass_noslices->Scale(1./h_mass_noslices->Integral());	

	TH1D *histo = new TH1D("histo","",nMassBins,massBoundaries);

	//Central slice for signals with alpha=0.25
	histo = (TH1D*)h_mass8->Clone();

	for(int i=1; i<=histo->GetNbinsX(); i++)
	{
		double val = histo->GetBinContent(i);
		//cout << "Bin Cont = " << val << endl;
		//cout << "Bin edges = [" << histo->GetBinLowEdge(i) << " , " << histo->GetBinLowEdge(i+1) << " ]" << endl;
		val = val/(histo->GetBinLowEdge(i+1)-histo->GetBinLowEdge(i));
		histo->SetBinContent(i,val);
	}

	histo->Scale(1./histo->Integral(),"width");
	cout << "Cont int = " << histo->Integral() << endl;
	cout << "Math int = " << histo->Integral("width") << endl;

	/*double sum=0.;
	for(int i=1; i<=histo->GetNbinsX(); i++)
	{
		cout << histo->GetBinContent(i)*(histo->GetBinLowEdge(i+1)-histo->GetBinLowEdge(i)) << endl;
		sum+=histo->GetBinContent(i)*(histo->GetBinLowEdge(i+1)-histo->GetBinLowEdge(i));
	}

	cout << "Sum = " << sum << endl;
	*/
	histo->SetLineWidth(2);

	histo->SetLineColor(color);

	histo->SetTitle("");
	histo->GetXaxis()->SetRangeUser(0.,11.);
	histo->GetYaxis()->SetRangeUser(0.,4.5);
	histo->GetXaxis()->SetTitle("Four-jet mass [TeV]");
	histo->GetXaxis()->SetTitleSize(0.06);
	histo->GetXaxis()->SetTitleOffset(0.82);
	histo->GetYaxis()->SetTitle("Normalized yield/TeV");
	histo->GetYaxis()->SetTitleSize(0.06);
	histo->GetYaxis()->SetTitleOffset(1.);
	histo->GetXaxis()->SetNdivisions(512,"kTRUE");
	histo->Draw("same hist");
	if(mass==2000 || mass==6000) 
	{
		sprintf(legentry, "#font[42]{M(S) = %.0f, M(#chi) = %.1f TeV}", mass/1000., chi/1000.);
	}
	else
	{
		sprintf(legentry, "#font[42]{M(S) = %.0f, M(#chi) = %.0f TeV}", mass/1000., chi/1000.);
	}
	l->AddEntry(histo, legentry, "L");
}

//Also plot extrapolated shape at 10 TeV for central slice 8
TFile *f1 = new TFile("/afs/cern.ch/work/i/izisopou/public/Interpolation_Final/output_alpha0p25/ResonanceShapes_alpha0p25_slice8_stdbin_TeV.root", "READ");
//TFile *f1 = new TFile("ResonanceShapes_alpha0p25_slice8_stdbin_TeV.root", "READ");

TH1D *h = new TH1D("h","",nMassBins,massBoundaries);

h = (TH1D*)f1->Get("h_qq_Suu10_Chi2500");
h->SetLineWidth(2);
h->SetLineColor(6);

for(int i=1; i<=h->GetNbinsX(); i++)
{
	double val = h->GetBinContent(i);
	val = val/(h->GetBinLowEdge(i+1)-h->GetBinLowEdge(i));
	h->SetBinContent(i,val);
}

h->Scale(1./h->Integral(),"width");

cout << "Cont int = " << h->Integral() << endl;
cout << "Math int = " << h->Integral("width") << endl;

/*double sum=0.;
for(int i=1; i<=h->GetNbinsX(); i++)
{
	cout << h->GetBinContent(i)*(h->GetBinLowEdge(i+1)-h->GetBinLowEdge(i)) << endl;
	sum+=h->GetBinContent(i)*(h->GetBinLowEdge(i+1)-h->GetBinLowEdge(i));
}

cout << "Sum = " << sum << endl;
*/
h->Draw("same hist");

sprintf(legentry, "#font[42]{M(S) = 10, M(#chi) = 2.5 TeV}");
l->AddEntry(h, legentry, "L");

l->Draw();
t->Draw();
cms1->Draw();
cms2->Draw();
cms3->Draw();

c->SaveAs("Figure_005-a.pdf");

}


