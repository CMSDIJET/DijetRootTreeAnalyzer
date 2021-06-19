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
#include "math.h"
//#include "CMS_lumi.h"

//run 
//root -l 'FinalplotPFDijetDMV_qq_1D_limit_vs_width_Prime.C("FinalPlotDM_V")'
const double PI=3.14159265;
void Coupling_limit_vs_width_Prime()
{
	string outputDIR = "../../EXO_19-012/Wide_resonances/limits/";
	system(("mkdir -p "+outputDIR).c_str());
	gROOT->SetBatch(kTRUE);
//	setTDRStyle();

//  string outputDIR = "Final-EXO-19-012/Stiched";

  // Set the color palette
	bool useNicksPalette = true;
	int ncontours        = 999;
	gStyle->SetPalette(70);  
	gStyle->SetNumberContours(ncontours);
  
	TMultiGraph *mg = new TMultiGraph(); 
	TGraph* grXsec = new TGraph();
	TGraph* grobs = new TGraph();
	TGraph* grobsNarrowg_qPrime = new TGraph();
	TGraph* grobsNarrowg_q = new TGraph();
	TGraph* grexp = new TGraph();
	TGraph* grexp_1sigma_up   = new TGraphErrors();
	TGraph* grexp_2sigma_up   = new TGraphErrors();
	TGraph* grexp_1sigma_dw   = new TGraphErrors();
	TGraph* grexp_2sigma_dw   = new TGraphErrors();
	static bool saveOutputFile  = true;  
	int expcounter          = 0;
	int exp_up_counter_1s   = 0;
	int exp_down_counter_1s = 0;
	int exp_up_counter_2s   = 0;
	int exp_down_counter_2s = 0;
	int obscounter          = 0;
	int nn=0;
	int medMin = 1800;
	double medMax = 5100;
	double GammaOverM=0;
	double GammaOverM_prime=0;
//	const double PI=3.14159265;
	vector<int> medMassList;
	double narrowLimitg_qPrime[]={0.109,0.121,0.16,0.174,0.156,0.147,0.146,0.135,0.116,0.129,0.154,0.184,0.225,0.246,0.264,0.258,0.211,0.258,0.305,0.328,0.341,0.342,0.368};
	int narrowMass[]={1600,1700,1800,1900,2000,2100,2200,2300,2400,2500,2600,2700,2800,2900,3000,3100,3200,3300,3400,3500,3600,3700};

   
  // This is where all the plots are made

	TF1 *gPrime_func = new TF1("gPrime_func", "x*sqrt( 1 / ( 1 +  1/(18*x*x) )  )", 0, 2);


	double gPrime;

	ifstream input_1 ("coupling_output.txt");
	if (input_1.fail())
	{
		exit(1);
	}

	int zMass=0; double obs, expPlus2,expPlus,exp,expMinus,expMinus2=0;
	while (!input_1.eof()) 
	{
		input_1 >> zMass >> obs >> expPlus2 >> expPlus >> exp >> expMinus >> expMinus2;
		if (!input_1.fail())
		{
			if (zMass<medMin || zMass>medMax ) continue;

			cout << " \nExpected gq = " <<  exp << " Mass " << zMass <<endl;
			cout << " \nExpected gq' = " <<  gPrime_func->Eval(exp) << " Mass " << zMass <<endl;

			double f_right = exp * sqrt( 1 / ( 1 + 1/( 18*exp*exp ) ) );			
			grexp->SetPoint(expcounter, double(zMass), gPrime_func->Eval(exp));
			expcounter++;
		  // find max and min for frame
			medMassList.push_back(zMass);

			grobs->SetPoint(obscounter, double(zMass),gPrime_func->Eval(obs));
			obscounter++;
			GammaOverM=0;
			GammaOverM =((18*exp*exp) + 1)/(12*PI);
	//      cout <<"mass = "<<zMass<< " exp = "<<exp<< " expout ="<<exp-(ind*0.01)<<" obs = "<<obs<<" obsout = "<<obs-(ind*0.01)<< " width exp ="<<GammaOverM<<endl;
		// 1 sigma dw
			grexp_1sigma_dw->SetPoint(exp_down_counter_1s, double(zMass), gPrime_func->Eval(expMinus));
			exp_down_counter_1s++;
		// 1 sigma up
			//grexp_1sigma_up->SetPoint(exp_up_counter_1s, double(zMass),expPlus-(ind*0.01));
			grexp_1sigma_up->SetPoint(exp_up_counter_1s, double(zMass), gPrime_func->Eval(expPlus));
			exp_up_counter_1s++;
		// 2 sigma dw
			grexp_2sigma_dw->SetPoint(exp_down_counter_2s, double(zMass),gPrime_func->Eval(expMinus2));
			exp_down_counter_2s++;
		// 2 sigma up
			grexp_2sigma_up->SetPoint(exp_up_counter_2s, double(zMass),gPrime_func->Eval(expPlus2));
			exp_up_counter_2s++;
		}
	}

	// Make 1 and 2 sigma brazilian bands
	TGraphAsymmErrors* graph_1sigma_band = new TGraphAsymmErrors();
	TGraphAsymmErrors* graph_2sigma_band = new TGraphAsymmErrors();

	if(exp_up_counter_1s == exp_down_counter_1s && exp_down_counter_1s == expcounter)
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
			if(iPoint == 0)	rangeUp = (medMassList.at(iPoint+1)-medMassList.at(iPoint))/2;      
			else if(iPoint == exp_up_counter_1s-1) rangeDw = (medMassList.at(iPoint)-medMassList.at(iPoint-1))/2;
			else
			{
				rangeUp = (medMassList.at(iPoint+1)-medMassList.at(iPoint))/2;
 				rangeDw = (medMassList.at(iPoint)-medMassList.at(iPoint-1))/2;
			}
			double x_obs, y_obs;
			grobs->GetPoint(iPoint,x_obs,y_obs);
			graph_1sigma_band->SetPointError(iPoint,rangeDw,rangeUp,fabs(y_dw-y_central),fabs(y_up-y_central));      
		}
	}
	else
	{
	    cerr<<"Number of expected limits value: mediat, 1-sigma up and 1-sigma down don't match --> skip "<<endl;
	    return;
	}

	if(exp_up_counter_2s == exp_down_counter_2s && exp_down_counter_2s == expcounter)
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
 
	  //////////// All the plotting and cosmetics
	TCanvas* canvas = new TCanvas("canvas", "canvas",600,600);
	TH1* frame = canvas->DrawFrame(medMin,0.,medMax,0.755, "");
	frame->GetXaxis()->SetTitle("Z' Mass (TeV)");
	frame->GetYaxis()->SetTitleFont(12);
	frame->GetYaxis()->SetTitle("g_{q}'");
	frame->GetXaxis()->SetTitleOffset(1.15);
	frame->GetXaxis()->SetLabelOffset(10000);
	frame->GetYaxis()->SetTitleOffset(1.10);  
	frame->GetXaxis()->SetNdivisions(505);
	frame->Draw();
//	CMS_lumi(canvas,"137",false,true,false,0.0,0.0);
	graph_2sigma_band->SetMinimum(0);
	graph_2sigma_band->SetMaximum(0.755);
	graph_2sigma_band->SetFillColor(kOrange);
	graph_1sigma_band->SetFillColor(kGreen+1);
	graph_2sigma_band->SetLineColor(kOrange);
	graph_1sigma_band->SetLineColor(kGreen+1);


	TLatex *xLab = new TLatex();
	xLab->SetTextAlign(22);
	xLab->SetTextFont(42);
	xLab->SetTextSize(0.05);         
	xLab->DrawLatex(2000, -0.03, "2");
	xLab->DrawLatex(3000, -0.03, "3");
	xLab->DrawLatex(4000, -0.03, "4");
//	xLab->DrawLatex(5000, -0.04, "5");
//	xLab->DrawLatex(6000, -0.04, "6");
//	xLab->DrawLatex(7000, -0.04, "7");
//	xLab->DrawLatex(8000, -0.04, "8");
	  
	graph_2sigma_band->Draw("3same");
	graph_1sigma_band->Draw("3same");
	mg->Add(graph_2sigma_band);
	mg->Add(graph_1sigma_band);

	grexp->SetLineColor(kBlack);
	grexp->SetLineStyle(2);
	grexp->SetLineWidth(2);
	grexp->Draw("Lsame");
	mg->Add(grexp);

	grobs->SetLineColor(kBlack);
	grobs->SetLineWidth(2);
	grobs->Draw("Lsame");
	mg->Add(grobs);
	grobsNarrowg_qPrime->SetLineColor(kBlue);
	grobsNarrowg_qPrime->SetLineWidth(2);
	 // grobsNarrowg_qPrime->Draw("Lsame");
	 // mg->Add(grobsNarrowg_qPrime);

	grobsNarrowg_q->SetLineColor(kBlue);
	grobsNarrowg_q->SetLineWidth(2);
	  //grobsNarrowg_q->Draw("Lsame");
	  
	TF1* line = new TF1 ("line","1",medMin,medMax);
	line->SetLineColor(kBlue);
	line->SetLineWidth(2);
	//  line->Draw("L same");

	TLegend *leg = new TLegend(0.180,0.5,0.57,0.77);  
	leg->SetTextSize(0.03);
	leg->AddEntry(grobs,"#bf{Observed}","L");
	leg->AddEntry(grexp,"#bf{Expected}","L");
	leg->AddEntry(graph_1sigma_band,"#pm #bf{1 std. deviation}","F"); // #pm 1 s.d.
	leg->AddEntry(graph_2sigma_band,"#pm #bf{2 std. deviation}","F"); // #pm 2 s.d.
	//  leg->AddEntry(grobsNarrowg_q,"Observed (narrow, spin 2)","L");
	leg->SetFillColor(0);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw("SAME");
	  
	TLatex * tex = new TLatex();
	tex->SetNDC();
	tex->SetTextColor(kBlack);
	tex->SetTextFont(42);
	tex->SetLineWidth(2);
	tex->SetTextSize(0.035);
	tex->Draw();
	tex->DrawLatex(0.185,0.87,("#bf{ 95% CL Limits}")); 
	tex->SetTextColor(kBlue);
	//tex->DrawLatex(0.475,0.80,("#bf{ Observed (narrow, spin 2)}"));
	tex = new TLatex(0.04013378,0.7417103,"Coupling");
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetTextSize(0.035);
	tex->SetTextAngle(90);
	tex->SetLineWidth(2);
	tex->Draw();
	TLatex *   tex2 = new TLatex();
	tex2->SetNDC();
	tex2->SetTextFont(42);
	tex2->SetLineWidth(2);
	tex2->SetTextSize(0.042);
	tex2->SetTextAngle(90);

	gPad->RedrawAxis();
	gPad->Modified(); 
	gPad->Update();
//	canvas->SaveAs((outputDIR+"/Final_PFDMV-g_qPrime-limit_observed_137p5fb_final_NLO_1D_higherW_M"+to_string(int(1))+"_DK.pdf").c_str(),"pdf");
//	canvas->SaveAs((outputDIR+"/Final_PFDMV-g_qPrime-limit_observed_137p5fb_final_NLO_1D_higherW_M"+to_string(int(1))+"_DK.png").c_str(),"png");
//	canvas->SaveAs((outputDIR+"/Final_PFDMV-g_qPrime-limit_observed_137p5fb_final_NLO_1D_higherW_M"+to_string(int(1))+"_DK.C").c_str(),"pdf");
	if(saveOutputFile)
	{
		TFile* outputFile = new TFile((outputDIR+"/grFinal_PFDMV-q_qPrime-limit_137p5fb.root").c_str(),"RECREATE");
		outputFile->cd();
		grexp->Write("graph_expected");
		grobs->Write("graph_observed");
		grexp_1sigma_up->Write("graph_expected_p1s");
		grexp_2sigma_up->Write("graph_expected_p2s");
		grexp_1sigma_dw->Write("graph_expected_m1s");
		grexp_2sigma_dw->Write("graph_expected_m2s");
	//	grobsNarrowg_qPrime->Write("graph_observedNarrowg_qPrime");
		mg->Write("graph_All");
		leg->SetName("My_leg");
		leg->Write();
		outputFile->Write();
	}
	/*
	  canvas->SetLogy();
	  frame->GetYaxis()->SetRangeUser(TMath::MinElement(graph_2sigma_band->GetN(),graph_2sigma_band->GetY())*0.009,
					  TMath::MaxElement(graph_2sigma_band->GetN(),graph_2sigma_band->GetY())*1000);
	  canvas->SaveAs((outputDIR+"/Final_PFDMV_qq_limit_observed_final_1D_M"+to_string(int(1))+"_log.pdf").c_str(),"pdf");
	  canvas->SaveAs((outputDIR+"/Final_PFDMV_qq_limit_observed_final_1D_M"+to_string(int(1))+"_log.png").c_str(),"pdf");
	*/
}

