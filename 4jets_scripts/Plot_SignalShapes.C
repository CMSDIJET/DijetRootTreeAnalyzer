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

void Plot_SignalShapes(double width, double alpha_true, int alphabin){

char width_name[1024];
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char alpha_true_name[1024];
if (alpha_true==0.11) sprintf(alpha_true_name,"0p11");
if (alpha_true==0.13) sprintf(alpha_true_name,"0p13");
if (alpha_true==0.15) sprintf(alpha_true_name,"0p15");
if (alpha_true==0.17) sprintf(alpha_true_name,"0p17");
if (alpha_true==0.19) sprintf(alpha_true_name,"0p19");
if (alpha_true==0.21) sprintf(alpha_true_name,"0p21");
if (alpha_true==0.23) sprintf(alpha_true_name,"0p23");
if (alpha_true==0.25) sprintf(alpha_true_name,"0p25");
if (alpha_true==0.27) sprintf(alpha_true_name,"0p27");
if (alpha_true==0.29) sprintf(alpha_true_name,"0p29");
if (alpha_true==0.31) sprintf(alpha_true_name,"0p31");
if (alpha_true==0.33) sprintf(alpha_true_name,"0p33");
if (alpha_true==0.42) sprintf(alpha_true_name,"0p42");

double alpha_low, alpha_high;
char alphabin_name[1024], alphaleg[1024];
if (alphabin==1) {alpha_low = 0.10; alpha_high = 0.12; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.10 < #alpha < 0.12");}
if (alphabin==2) {alpha_low = 0.12; alpha_high = 0.14; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.12 < #alpha < 0.14");}
if (alphabin==3) {alpha_low = 0.14; alpha_high = 0.16; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.14 < #alpha < 0.16");}
if (alphabin==4) {alpha_low = 0.16; alpha_high = 0.18; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.16 < #alpha < 0.18");}
if (alphabin==5) {alpha_low = 0.18; alpha_high = 0.20; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.18 < #alpha < 0.20");}
if (alphabin==6) {alpha_low = 0.20; alpha_high = 0.22; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.20 < #alpha < 0.22");}
if (alphabin==7) {alpha_low = 0.22; alpha_high = 0.24; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.22 < #alpha < 0.24");}
if (alphabin==8) {alpha_low = 0.24; alpha_high = 0.26; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.24 < #alpha < 0.26");}
if (alphabin==9) {alpha_low = 0.26; alpha_high = 0.28; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.26 < #alpha < 0.28");}
if (alphabin==10) {alpha_low = 0.28; alpha_high = 0.30; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.28 < #alpha < 0.30");}
if (alphabin==11) {alpha_low = 0.30; alpha_high = 0.32; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.30 < #alpha < 0.32");}
if (alphabin==12) {alpha_low = 0.32; alpha_high = 0.34; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"0.32 < #alpha < 0.34");}
if (alphabin==13) {alpha_low = 0.34; alpha_high = 100.; sprintf(alphabin_name,"alphabin%d",alphabin); sprintf(alphaleg,"#alpha > 0.34");}
if (alphabin==0) {alpha_low = 0.10; alpha_high = 100.; sprintf(alphabin_name,"alphagt0p1"); sprintf(alphaleg,"#alpha > 0.10");}


double FourjetMass, Maverage, Masymmetry, DeltaEtaJJAK4, DeltaRAK4_First, DeltaRAK4_Second, alpha;

const int nMassBins = 103;

double massBoundaries[nMassBins+1] = {1/1000., 3/1000., 6/1000., 10/1000., 16/1000., 23/1000., 31/1000., 40/1000., 50/1000., 61/1000., 74/1000., 88/1000., 103/1000., 119/1000., 137/1000., 156/1000., 176/1000., 197/1000., 220/1000., 244/1000., 270/1000., 296/1000., 325/1000.,
     354/1000., 386/1000., 419/1000., 453/1000., 489/1000., 526/1000., 565/1000., 606/1000., 649/1000., 693/1000., 740/1000., 788/1000., 838/1000., 890/1000., 944/1000., 1000/1000., 1058/1000., 1118/1000., 1181/1000., 1246/1000., 1313/1000., 1383/1000., 1455/1000., 1530/1000., 1607/1000.,
     1687/1000.,1770/1000., 1856/1000., 1945/1000., 2037/1000., 2132/1000., 2231/1000., 2332/1000., 2438/1000., 2546/1000., 2659/1000., 2775/1000., 2895/1000., 3019/1000., 3147/1000., 3279/1000., 3416/1000., 3558/1000., 3704/1000., 3854/1000., 4010/1000., 4171/1000., 4337/1000., 
     4509/1000.,
     4686/1000., 4869/1000., 5058/1000., 5253/1000., 5455/1000., 5663/1000., 5877/1000., 6099/1000., 6328/1000., 6564/1000., 6808/1000., 7060/1000., 7320/1000., 7589/1000., 7866/1000., 8152/1000., 8447/1000., 8752/1000., 9067/1000., 9391/1000., 9726/1000., 10072/1000.,
     10430/1000.,
     10798/1000., 11179/1000., 11571/1000., 11977/1000., 12395/1000., 12827/1000., 13272/1000., 13732/1000., 14000/1000.};

TPaveText *cms1 = new TPaveText(0.21,0.91,0.46,0.96,"NDC"); 
cms1->AddText("#bf{CMS} #scale[0.7]{#it{Simulation Preliminary}}"); 
cms1->SetBorderSize(0);
cms1->SetTextFont(42);
cms1->SetFillColor(0);
cms1->SetTextSize(0.06); 

TPaveText *cms2 = new TPaveText(0.825,0.91,0.975,0.96,"NDC"); 
cms2->AddText("13 TeV");
cms2->SetBorderSize(0);
cms2->SetFillColor(0);
cms2->SetTextSize(0.06);
cms2->SetTextFont(42);

TPaveText *cms3 = new TPaveText(0.59,0.81,0.81,0.86,"NDC"); //0.6,0.81,0.82,0.86,"NDC"
cms3->AddText("Diquark: S #rightarrow #chi#chi #rightarrow (ug)(ug)");
cms3->SetTextFont(42);
cms3->SetBorderSize(0);
cms3->SetFillColor(0);
cms3->SetTextSize(0.04);

char legentry[1024], legtitle[1024];

TCanvas *c = new TCanvas("c","",800,700);
c->SetTickx(1);
c->SetTicky(1);
c->SetRightMargin(0.03);
c->cd();


TLegend *l = new TLegend(0.5, 0.5, 0.75, 0.8); //0.55, 0.55, 0.75, 0.8
l->SetBorderSize(0);
l->SetTextSize(0.04);

if(width==0.015)
{
	sprintf(legtitle, "#Gamma / M_{S} = %.1f %%",width*100.);
}
else
{
	sprintf(legtitle, "#Gamma / M_{S} = %.0f %%",width*100.);
}

l->SetHeader(legtitle);


TPaveText *t = new TPaveText(0.7,0.35,0.8,0.45,"NDC"); //0.67,0.42,0.77,0.52,"NDC"
t->AddText(alphaleg);
t->SetTextFont(42);
t->SetBorderSize(0);
t->SetFillColor(0);
t->SetTextSize(0.04);

int color = 0;

for (int mass=2000; mass<=10000; mass=mass+2000)
{
	color++;
	double chi = mass*alpha_true;

	char name[1024];
	sprintf(name,"root:://eoscms//eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/reduced_trees/Suu_Diquarks/RunIISummer20UL18MiniAODv2/full_grid/RunIISummer20UL18_Suu-Diquark_W-%s_S-%d_chi-%.0f__AK4CHS_reduced_skim.root", width_name, mass, chi);

	cout << "Root file : " << name << endl;

	TFile *f = new TFile(name,"READ");

	TH1D *histo; 

	if (f->IsOpen())
	{
		histo = new TH1D("histo","",nMassBins,massBoundaries);
		histo->Sumw2();
		

		TTree *tree = (TTree*)(f->Get("rootTupleTree/tree"));

		tree->SetBranchAddress("FourjetMassAK4CHS",&FourjetMass);
  		tree->SetBranchAddress("MaverageAK4CHS",&Maverage);
  		tree->SetBranchAddress("MasymmetryAK4CHS",&Masymmetry);
  		tree->SetBranchAddress("DeltaEtaJJAK4CHS",&DeltaEtaJJAK4);
  		tree->SetBranchAddress("DeltaRAK4CHS_First",&DeltaRAK4_First);
  		tree->SetBranchAddress("DeltaRAK4CHS_Second",&DeltaRAK4_Second);
	   
		int nentries=(Int_t)tree->GetEntries(); 
		std::cout<<"Number of entries =  "<<nentries<<std::endl;
		for (int i=0; i<nentries; i++)    //event loop
		{     
			tree->GetEntry(i);

			alpha=Maverage/FourjetMass;
			if(Masymmetry<0.1 && DeltaEtaJJAK4<1.1 && DeltaRAK4_First<2.0 && DeltaRAK4_Second<2.0 && alpha>alpha_low && alpha<alpha_high) 
			{ 
				histo->Fill(FourjetMass/1000.);
			}
		}
	
	}
	

	for(int i=1; i<=histo->GetNbinsX(); i++)
	{
		double val = histo->GetBinContent(i)/(histo->GetBinLowEdge(i+1)-histo->GetBinLowEdge(i));
		histo->SetBinContent(i,val);
	}

	histo->Scale(1./histo->Integral(),"width");
	cout << "Cont int = " << histo->Integral() << endl;
	cout << "Math int = " << histo->Integral("width") << endl;

	
	histo->SetLineWidth(2);
	histo->SetStats(0);
	

	if(mass==10000) color = 6;
	histo->SetLineColor(color);

	histo->SetTitle("");
	histo->GetXaxis()->SetRangeUser(0.,11.);
	histo->GetYaxis()->SetRangeUser(0.,2.99);
	histo->GetXaxis()->SetTitle("Four-jet mass [TeV]");
	histo->GetXaxis()->SetTitleSize(0.055);
	histo->GetXaxis()->SetTitleOffset(0.82);
	histo->GetYaxis()->SetTitle("Normalized yield/TeV");
	histo->GetYaxis()->SetTitleSize(0.055);
	histo->GetYaxis()->SetTitleOffset(0.85);
	histo->GetXaxis()->SetNdivisions(512,"kTRUE");
	histo->Draw("same hist");


	if(mass==2000 || mass==6000 || mass==10000) 
	{
		sprintf(legentry, "#font[42]{M_{S} = %.0f, M_{#chi} = %.1f TeV}", mass/1000., chi/1000.);
	}
	else
	{
		sprintf(legentry, "#font[42]{M_{S} = %.0f, M_{#chi} = %.0f TeV}", mass/1000., chi/1000.);
	}
	l->AddEntry(histo, legentry, "L");
}


l->Draw();
t->Draw();
cms1->Draw();
cms2->Draw();
cms3->Draw();

char cname1[1024], cname2[1024];
sprintf(cname1,"plots/SignalShapes/SignalShapes_alpha%s_W-%s_%s.png",alpha_true_name,width_name,alphabin_name);
sprintf(cname2,"plots/SignalShapes/SignalShapes_alpha%s_W-%s_%s.pdf",alpha_true_name,width_name,alphabin_name);

c->SaveAs(cname1);
c->SaveAs(cname2);

}


