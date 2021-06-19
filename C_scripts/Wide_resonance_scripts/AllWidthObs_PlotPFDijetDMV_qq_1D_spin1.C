#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TColor.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TLegend.h"
#include "TEfficiency.h"
#include "TGraphAsymmErrors.h"
#include "TGraph2D.h"
#include "TGraph.h"
#include "TPaletteAxis.h"
#include <iostream>

#include "CMS_lumi.h"

//root -l 'AllWidthObs_PlotPFDijetDMV_qq_1D_Ratio_Method_higher_widths.C("xsecUL_Asymptotic_qq_PFDijet2017MC.root","AllWidthObs_updated1DPlotDMV_qq_Ratio_Method")'
//void AllWidthObs_PlotPFDijetDMV_qq_1D_Ratio_Method_higher_widths(string inputFileName,string outputDIR) {
void AllWidthObs_PlotPFDijetDMV_qq_1D_spin1(string inputFileName = "xsecUL_Asymptotic_qq_PFDijet2017MC.root" ) {

	string outputDIR = "../../EXO_19-012/Wide_resonances/limits/";
	system(("mkdir -p "+outputDIR).c_str());
	gROOT->SetBatch(kTRUE);
	setTDRStyle();

	// Set the color palette
	bool useNicksPalette = true;
	int ncontours= 999;

	gStyle->SetNumberContours(ncontours);

	TGraph* grobsW55 = new TGraph();
	TGraph* grobsW50 = new TGraph();
	TGraph* grobsW45 = new TGraph();
	TGraph* grobsW40 = new TGraph();
	TGraph* grobsW35 = new TGraph();
	TGraph* grobsW30 = new TGraph();
	TGraph* grobsW25 = new TGraph();
	TGraph* grobsW20 = new TGraph();
	TGraph* grobsW15 = new TGraph();
	TGraph* grobsW10 = new TGraph();
	TGraph* grobsW05 = new TGraph();
	TGraph* grobsW01 = new TGraph();
	TGraph* grobsW0p001 = new TGraph();
	TGraph* grexp = new TGraph();

	TGraph* grexp_1sigma_up = new TGraphErrors();
	TGraph* grexp_2sigma_up = new TGraphErrors();
	TGraph* grexp_1sigma_dw = new TGraphErrors();
	TGraph* grexp_2sigma_dw = new TGraphErrors();

	int expcounter= 0;
	int exp_up_counter_1s = 0;
	int exp_down_counter_1s = 0;
	int exp_up_counter_2s = 0;
	int exp_down_counter_2s = 0;
	int obscounter55= 0;
	int obscounter50= 0;
	int obscounter45= 0;
	int obscounter40= 0;
	int obscounter35= 0;
	int obscounter30= 0;
	int obscounter25= 0;
	int obscounter20= 0;
	int obscounter15= 0;
	int obscounter10= 0;
	int obscounter05= 0;
	int obscounter01= 0;

	int medMin = 1750;
	int medMax = 8750;

	char *spin_txt= "Spin 1";
	char *resonance_txt= "quark-quark";

	double xsecMin = 0.00001;
	double xsecMax = 1000;

	vector<int> medMassList;

	string width[]={"0p55", "0p5","0p45","0p4","0p35","0p3","0p25","0p2","0p15","0p1","0p05","0p01"};

	for(int w=0; w<12; w++)
	{

		string inputFileName1= "../../EXO_19-012/Wide_resonances/limits/qq_"+width[w]+"/"+inputFileName;

// This is where all the plots are made
		TFile *file = TFile::Open(inputFileName1.c_str(),"READ");
		TTree *tree = (TTree*)file->Get("xsecTree");
		double mass;
		double xsecULObs_PFDijet2016;
		double xsecULExpPlus2_PFDijet2016;
		double xsecULExpPlus_PFDijet2016;
		double xsecULExp_PFDijet2016;
		double xsecULExpMinus_PFDijet2016;
		double xsecULExpMinus2_PFDijet2016;
		tree->SetBranchAddress("mass", &mass);
		tree->SetBranchAddress("xsecULObs_PFDijet2017MC", &xsecULObs_PFDijet2016);
		tree->SetBranchAddress("xsecULExpPlus2_PFDijet2017MC", &xsecULExpPlus2_PFDijet2016);
		tree->SetBranchAddress("xsecULExpPlus_PFDijet2017MC", &xsecULExpPlus_PFDijet2016);
		tree->SetBranchAddress("xsecULExp_PFDijet2017MC", &xsecULExp_PFDijet2016);
		tree->SetBranchAddress("xsecULExpMinus_PFDijet2017MC", &xsecULExpMinus_PFDijet2016);
		tree->SetBranchAddress("xsecULExpMinus2_PFDijet2017MC", &xsecULExpMinus2_PFDijet2016);

		for (int i = 0; i < tree->GetEntries(); i++)
		{
			tree->GetEntry(i);
			if(mass<medMin or mass>medMax) continue; 
			grexp->SetPoint(expcounter, double(mass), xsecULExp_PFDijet2016);
			expcounter++;
			cout << "\n\n"<< endl;
			cout << "File processed : "<< width[w] <<endl;
			cout<<"mass =" <<mass<<" xsecULExp ="<<xsecULExp_PFDijet2016<<" xsecULObs ="<<xsecULObs_PFDijet2016<<endl;
			// find max and min for frame
			medMassList.push_back(mass);

			if (width[w]=="0p55" and mass<=medMax and mass>=2100) { grobsW55->SetPoint(obscounter55, double(mass),xsecULObs_PFDijet2016 ); obscounter55++;}
			if (width[w]=="0p5" and mass<=medMax and mass>=2100) { grobsW50->SetPoint(obscounter50, double(mass),xsecULObs_PFDijet2016 ); obscounter50++;}
			if (width[w]=="0p45" and mass<=medMax and mass>=2100) { grobsW45->SetPoint(obscounter45, double(mass),xsecULObs_PFDijet2016 ); obscounter45++;}
			if (width[w]=="0p4" and mass<=medMax and mass>=2100) { grobsW40->SetPoint(obscounter40, double(mass),xsecULObs_PFDijet2016 ); obscounter40++;}
			if (width[w]=="0p35" and mass<=medMax and mass>=2100) { grobsW35->SetPoint(obscounter35, double(mass),xsecULObs_PFDijet2016 ); obscounter35++;}
			if (width[w]=="0p3" and mass<=medMax and mass>=2100) { grobsW30->SetPoint(obscounter30, double(mass),xsecULObs_PFDijet2016 ); obscounter30++;}
			if (width[w]=="0p25" and mass<=medMax) { grobsW25->SetPoint(obscounter25, double(mass),xsecULObs_PFDijet2016 ); obscounter25++;}
			if (width[w]=="0p2" and mass<=medMax) { grobsW20->SetPoint(obscounter20, double(mass),xsecULObs_PFDijet2016 ); obscounter20++;}
			if (width[w]=="0p15" and mass<=medMax) { grobsW15->SetPoint(obscounter15, double(mass),xsecULObs_PFDijet2016 ); obscounter15++;}
			if (width[w]=="0p1" and mass<=medMax) { grobsW10->SetPoint(obscounter10, double(mass),xsecULObs_PFDijet2016 ); obscounter10++;}
			if (width[w]=="0p05" and mass<=medMax) { grobsW05->SetPoint(obscounter05, double(mass),xsecULObs_PFDijet2016 ); obscounter05++;}
			if (width[w]=="0p01" and mass<=medMax) { grobsW01->SetPoint(obscounter01, double(mass),xsecULObs_PFDijet2016 ); obscounter01++;}

			// 1 sigma dw
			grexp_1sigma_dw->SetPoint(exp_down_counter_1s, double(mass),xsecULExpMinus_PFDijet2016 );
			exp_down_counter_1s++;
			// 1 sigma up
			grexp_1sigma_up->SetPoint(exp_up_counter_1s, double(mass),xsecULExpPlus_PFDijet2016 );
			exp_up_counter_1s++;

			// 2 sigma dw
			grexp_2sigma_dw->SetPoint(exp_down_counter_2s, double(mass),xsecULExpMinus2_PFDijet2016 );
			exp_down_counter_2s++;
			// 2 sigma up
			grexp_2sigma_up->SetPoint(exp_up_counter_2s, double(mass),xsecULExpPlus2_PFDijet2016 );
			exp_up_counter_2s++;
		}
	tree->ResetBranchAddresses();
	delete tree;
	delete file;
	}

 // Make 1 and 2 sigma brazilian bands
	TGraphAsymmErrors* graph_1sigma_band = new TGraphAsymmErrors();
	TGraphAsymmErrors* graph_2sigma_band = new TGraphAsymmErrors();

	if(exp_up_counter_1s == exp_down_counter_1s and exp_down_counter_1s == expcounter)
	{
		for(int iPoint = 0; iPoint < exp_up_counter_1s; iPoint++)
		{
			double x_central, y_central;
			grexp->GetPoint(iPoint,x_central,y_central);
			graph_1sigma_band->SetPoint(iPoint,x_central,y_central);
			double y_up, y_dw;
			grexp_1sigma_dw->GetPoint(iPoint,x_central,y_dw);
			grexp_1sigma_up->GetPoint(iPoint,x_central,y_up);
			float rangeDw = 0;
			float rangeUp = 0;
			if(iPoint == 0)
			{
				rangeUp = (medMassList.at(iPoint+1)-medMassList.at(iPoint))/2;
			}
			else if(iPoint == exp_up_counter_1s-1)
			{
				rangeDw = (medMassList.at(iPoint)-medMassList.at(iPoint-1))/2;
			}
			else
			{
				rangeUp = (medMassList.at(iPoint+1)-medMassList.at(iPoint))/2;
				rangeDw = (medMassList.at(iPoint)-medMassList.at(iPoint-1))/2;
			}

			double x_obs, y_obs;
			grobsW30->GetPoint(iPoint,x_obs,y_obs);
			graph_1sigma_band->SetPointError(iPoint,rangeDw,rangeUp,fabs(y_dw-y_central),fabs(y_up-y_central));
		}
	}
	else 
	{
		cerr<<"Number of expected limits value: mediat, 1-sigma up and 1-sigma down don't match --> skip "<<endl;
		return;
	}

	if(exp_up_counter_2s == exp_down_counter_2s and exp_down_counter_2s == expcounter)
	{
		for(int iPoint = 0; iPoint < exp_up_counter_2s; iPoint++)
		{
			double x_central, y_central;
			grexp->GetPoint(iPoint,x_central,y_central);
			graph_2sigma_band->SetPoint(iPoint,x_central,y_central);
			double y_up, y_dw;
			grexp_2sigma_dw->GetPoint(iPoint,x_central,y_dw);
			grexp_2sigma_up->GetPoint(iPoint,x_central,y_up);
			float rangeDw = 0;
			float rangeUp = 0;
			if(iPoint == 0)
			{
				rangeUp = (medMassList.at(iPoint+1)-medMassList.at(iPoint))/2;
			}
			else if(iPoint == exp_up_counter_1s-1)
			{
				rangeDw = (medMassList.at(iPoint)-medMassList.at(iPoint-1))/2;
			}
			else
			{
				rangeUp = (medMassList.at(iPoint+1)-medMassList.at(iPoint))/2;
				rangeDw = (medMassList.at(iPoint)-medMassList.at(iPoint-1))/2;
			}
			graph_2sigma_band->SetPointError(iPoint,rangeDw,rangeUp,fabs(y_dw-y_central),fabs(y_up-y_central));
		}
	}
	else
	{
		cerr<<"Number of expected limits value: mediat, 2-sigma up and 2-sigma down don't match --> skip "<<endl;
		return;
	}

// cout<<"graph_2sigma_band "<<graph_2sigma_band->GetN()<<endl; 
 //////////// All the plotting and cosmetics
	TCanvas* canvas = new TCanvas("canvas", "canvas",600,600);
	TH1* frame = canvas->DrawFrame(medMin,TMath::MinElement(graph_2sigma_band->GetN(),graph_2sigma_band->GetY())*0.0001, medMax,TMath::MaxElement(graph_2sigma_band->GetN(),graph_2sigma_band->GetY())*4.5, "");
 //frame->GetYaxis()->CenterTitle();
	frame->GetXaxis()->SetTitle("Resonance mass [TeV]");
// frame->GetYaxis()->SetTitle("#sigma #it{B} #it{A} [pb]");
	frame->GetYaxis()->SetTitle("#sigma#kern[0.15]{#bf{#it{#Beta}}}#kern[0.15]{#bf{#it{#Alpha}}} [pb]");
	frame->GetXaxis()->SetTitleOffset(1.15);
	frame->GetXaxis()->SetLabelOffset(1000);
	frame->GetYaxis()->SetTitleOffset(1.10);
	frame->Draw();
	//CMS_lumi(canvas,"35.9");
	CMS_lumi(canvas,"137",false,true,false,0.,0);


	TLatex *xLab = new TLatex();
	xLab->SetTextAlign(22);
	xLab->SetTextFont(42);
	xLab->SetTextSize(0.05); 
	xLab->DrawLatex(2000, 6.25e-6, "2");
	xLab->DrawLatex(3000, 6.25e-6, "3");
	xLab->DrawLatex(4000, 6.25e-6, "4");
	xLab->DrawLatex(5000, 6.25e-6, "5");
	xLab->DrawLatex(6000, 6.25e-6, "6");
	xLab->DrawLatex(7000, 6.25e-6, "7");
	xLab->DrawLatex(8000, 6.25e-6, "8");

	int lineColor[] = {kRed,kGreen,kGreen+3,kMagenta+3,kCyan-4,kPink-9,kTeal+4,kMagenta-9,kSpring-9};
	grobsW30->SetLineColor(kRed);
	grobsW30->SetLineWidth(2);
	grobsW30->Draw("Lsame* ][");
	grobsW30->SetMarkerColor(kRed);
	grobsW30->SetMarkerStyle(20);



	grobsW25->SetLineColor(kGreen+3);
	grobsW25->SetLineWidth(2);
	// grobsW25->Draw("Lsame*");
	grobsW25->SetMarkerColor(kGreen+3);
	grobsW25->SetMarkerStyle(22);

	grobsW20->SetLineColor(kGreen);
	grobsW20->SetLineWidth(2);
	grobsW20->Draw("Lsame*");
	grobsW20->SetMarkerColor(kGreen);
	grobsW20->SetMarkerStyle(21);

	grobsW15->SetLineColor(kMagenta+3);
	grobsW15->SetLineWidth(2);
	grobsW15->Draw("Lsame*");
	grobsW15->SetMarkerColor(kMagenta+3);
	grobsW15->SetMarkerStyle(24);

	grobsW10->SetLineColor(kBlue);
	grobsW10->SetLineWidth(2);
	grobsW10->Draw("Lsame*");
	grobsW10->SetMarkerColor(kBlue);
	grobsW10->SetMarkerStyle(23);

	grobsW05->SetLineColor(kPink-9);
	grobsW05->SetLineWidth(2);
	grobsW05->Draw("Lsame*");
	grobsW05->SetMarkerColor(kPink-9);
	grobsW05->SetMarkerStyle(25);

	grobsW01->SetLineColor(kBlack);
	grobsW01->SetLineWidth(2);
	grobsW01->Draw("Lsame*");
	grobsW01->SetMarkerColor(kBlack);
	grobsW01->SetMarkerStyle(26);





	grobsW35->SetLineColor(kYellow-2);
	grobsW35->SetLineWidth(2);
	// grobsW35->Draw("Lsame*");
	grobsW35->SetMarkerColor(kYellow-2);
	grobsW35->SetMarkerStyle(34);


	grobsW40->SetLineColor(kBlue-1);
	grobsW40->SetLineWidth(2);
	grobsW40->Draw("Lsame*");
	grobsW40->SetMarkerColor(kBlue-1);
	grobsW40->SetMarkerStyle(31);

	grobsW45->SetLineColor(kCyan+2);
	grobsW45->SetLineWidth(2);
	// grobsW45->Draw("Lsame*");
	grobsW45->SetMarkerColor(kCyan+2);
	grobsW45->SetMarkerStyle(29);

	grobsW50->SetLineColor(kGray+2);
	grobsW50->SetLineWidth(2);
	// grobsW50->Draw("Lsame*");
	grobsW50->SetMarkerColor(kGray+2);
	grobsW50->SetMarkerStyle(32);
	//grobsW50->SetMarkerSize(0.06);

	grobsW55->SetLineColor(kBlue-3);
	grobsW55->SetLineWidth(2);
	grobsW55->Draw("Lsame*");
	grobsW55->SetMarkerColor(kBlue-3);
	grobsW55->SetMarkerStyle(25);

	grobsW30->Print();





	grobsW0p001->SetLineColor(kMagenta-9);
	grobsW0p001->SetLineWidth(2);
	grobsW0p001->Draw("Lsame*");
	grobsW0p001->SetMarkerColor(kMagenta-9);
	grobsW0p001->SetMarkerStyle(27);

	TF1* line = new TF1 ("line","1",medMin,medMax);
	line->SetLineColor(kBlue);
	line->SetLineWidth(2);
	//line->Draw("L same");

	TLegend *leg = new TLegend(0.65,0.45,0.99,0.86,NULL,"brNDC");

	leg->AddEntry(grobsW55,"#Gamma/M = 55%","PL");
	// leg->AddEntry(grobsW50,"#Gamma/M = 50%","PL");
	// leg->AddEntry(grobsW45,"#Gamma/M = 45%","PL");
	leg->AddEntry(grobsW40,"#Gamma/M = 40%","PL");
	// leg->AddEntry(grobsW35,"#Gamma/M = 35%","PL");
	leg->AddEntry(grobsW30,"#Gamma/M = 30%","PL");
	// leg->AddEntry(grobsW25,"#Gamma/M = 25%","PL");
	leg->AddEntry(grobsW20,"#Gamma/M = 20%","PL");
	leg->AddEntry(grobsW15,"#Gamma/M = 15%","PL");
	leg->AddEntry(grobsW10,"#Gamma/M = 10%","PL");
	leg->AddEntry(grobsW05,"#Gamma/M = 5%","PL");
	leg->AddEntry(grobsW01,"#Gamma/M = 1%","PL");
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw("SAME");
	 
	TLatex * tex = new TLatex();
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetLineWidth(2);
	tex->SetTextSize(0.042);
	tex->Draw();
	tex->DrawLatex(0.17,0.80,(resonance_txt));
	tex->DrawLatex(0.17,0.75,(spin_txt));
	tex->DrawLatex(0.61,0.87,("#bf{Observed 95% CL}"));
	gPad->RedrawAxis();
	gPad->Modified(); 
	gPad->Update();

	TLine *line5 =new TLine(2950,xsecMin,2950,2);
	line5->SetLineStyle(9);
	line5->SetLineWidth(1);

	TLatex *l5 =new TLatex();
	l5->SetTextAlign(11);
	l5->SetTextSize(0.028);
	l5->SetNDC();
	l5->SetTextFont(72);
	line5->Draw("same");
	l5->DrawLatex(0.152,0.22,"Fit");
	l5->DrawLatex(0.152,0.18,"method");
	l5->DrawLatex(0.358,0.22,"Ratio");
	l5->DrawLatex(0.358,0.18,"method");


	 

	canvas->SetLogy();
	 //frame->GetYaxis()->SetRangeUser(TMath::MinElement(graph_2sigma_band->GetN(),graph_2sigma_band->GetY())*0.1,TMath::MaxElement(graph_2sigma_band->GetN(),graph_2sigma_band->GetY())*400);
	frame->GetYaxis()->SetRangeUser(xsecMin,xsecMax);
	canvas->SaveAs((outputDIR+"/DMV_qq_limit_AllWidth_Observed_UpdatedFinal_137p5fb_1D_"+to_string(int(1))+"_log_spin1_stylystic_v3.pdf").c_str(),"pdf");
	canvas->SaveAs((outputDIR+"/DMV_qq_limit_AllWidth_Observed_UpdatedFinal_137p5fb_1D_"+to_string(int(1))+"_log_spin1_stylystic_v3.png").c_str(),"pdf");
	canvas->SaveAs((outputDIR+"/DMV_qq_limit_AllWidth_Observed_UpdatedFinal_137p5fb_1D_"+to_string(int(1))+"_log_spin1_stylystic_v3.C").c_str(),"pdf");

}

