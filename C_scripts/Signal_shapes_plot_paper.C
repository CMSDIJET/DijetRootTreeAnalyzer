/*
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
*/
#include "TLatex.h"

#include "include_functions.h"
//#include "setTDRStyle_teliko.C"

/*
TH1D* truncate_the_shape(int truncation_mass, TH1D* full_shape)
{
	TH1D *truncated_shape = (TH1D*)(full_shape->Clone());
	
	int nbins = full_shape->GetNbinsX();
	double mass;
	for (int i=0; i<nbins; i++)
	{
		mass = truncated_shape->GetBinCenter(i); 
		if (mass < truncation_mass) truncated_shape->SetBinContent(i,0);
	}
	
	return truncated_shape;
}
*/

void Signal_shapes_plot_paper() 
{



	char *output_directory = "../deleteme/";     


	//int mass_to_plot = 4000 ; //this has to be a multiplicative of 100:  2100, 3000, 6800....
	char *resonance = "qq";		
	//int truncation_mass = 1530;
	int truncation_mass = 0;
	
	//int xaxis_start = truncation_mass;
	int xaxis_start = 0;
	int xaxis_end = 6100;

	double massBoundaries[104] = {1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325,
     354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607,
     1687,1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337,
     4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072,
     10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000};

	gROOT->LoadMacro("setTDRStyle_teliko.C");
	setTDRStyle_teliko();

	char root_file_path[350];
	
	char *image_name = "_30_vs_35_July19" ;


//	sprintf(root_file_path,"Debugging_higher_width_shapes/InputShapes_DMVqq_W-0p3_testing_v2.root");
	sprintf(root_file_path,"../inputs/Spin1_WideResonance_shapes//ResonanceShapes_qq_13TeV_Spring16_W-0p01.root");
	TFile *f_01= new TFile(root_file_path);

	sprintf(root_file_path,"../inputs/Spin1_WideResonance_shapes//ResonanceShapes_qq_13TeV_Spring16_W-0p1.root");
	TFile *f_10= new TFile(root_file_path);

	sprintf(root_file_path,"../inputs/Spin1_WideResonance_shapes//ResonanceShapes_qq_13TeV_Spring16_W-0p2.root");
	TFile *f_20= new TFile(root_file_path);

	sprintf(root_file_path,"../inputs/Spin1_WideResonance_shapes//ResonanceShapes_qq_13TeV_Spring16_W-0p4.root");
	TFile *f_40= new TFile(root_file_path);

	sprintf(root_file_path,"../inputs/Spin1_WideResonance_shapes//ResonanceShapes_qq_13TeV_Spring16_W-0p55.root");
	TFile *f_55= new TFile(root_file_path);



	char shape_name[100];
	sprintf(shape_name,"h_%s_%i",resonance,2000);   // fore interpolated shapes

	TH1D *shape_3TeV_01 = (TH1D*)(f_01->Get(shape_name));
	TH1D *shape_3TeV_10 = (TH1D*)(f_10->Get(shape_name));
	TH1D *shape_3TeV_20 = (TH1D*)(f_20->Get(shape_name));
	TH1D *shape_3TeV_40 = (TH1D*)(f_40->Get(shape_name));
	TH1D *shape_3TeV_55 = (TH1D*)(f_55->Get(shape_name));


	sprintf(shape_name,"h_%s_%i",resonance,5000);   // fore interpolated shapes

	TH1D *shape_6TeV_01 = (TH1D*)(f_01->Get(shape_name));
	TH1D *shape_6TeV_10 = (TH1D*)(f_10->Get(shape_name));
	TH1D *shape_6TeV_20 = (TH1D*)(f_20->Get(shape_name));
	TH1D *shape_6TeV_40 = (TH1D*)(f_40->Get(shape_name));
	TH1D *shape_6TeV_55 = (TH1D*)(f_55->Get(shape_name));


	TH1D *shape_binned_3TeV_01 	      = new TH1D("shape_binned_3TeV_01","shape_binned_3TeV_01",103,massBoundaries);  
	TH1D *shape_binned_3TeV_10 	      = new TH1D("shape_binned_3TeV_10","shape_binned_3TeV_10",103,massBoundaries);  
	TH1D *shape_binned_3TeV_20 	      = new TH1D("shape_binned_3TeV_20","shape_binned_3TeV_20",103,massBoundaries);  
	TH1D *shape_binned_3TeV_40 	      = new TH1D("shape_binned_3TeV_40","shape_binned_3TeV_40",103,massBoundaries);  
	TH1D *shape_binned_3TeV_55 	      = new TH1D("shape_binned_3TeV_55","shape_binned_3TeV_55",103,massBoundaries);  

	TH1D *shape_binned_6TeV_01 	      = new TH1D("shape_binned_6TeV_01","shape_binned_6TeV_01",103,massBoundaries);
	TH1D *shape_binned_6TeV_10 	      = new TH1D("shape_binned_6TeV_10","shape_binned_3TeV_10",103,massBoundaries);    
	TH1D *shape_binned_6TeV_20 	      = new TH1D("shape_binned_6TeV_20","shape_binned_6TeV_20",103,massBoundaries);  
	TH1D *shape_binned_6TeV_40 	      = new TH1D("shape_binned_6TeV_40","shape_binned_6TeV_40",103,massBoundaries);  
	TH1D *shape_binned_6TeV_55 	      = new TH1D("shape_binned_6TeV_55","shape_binned_6TeV_55",103,massBoundaries);  


	for(int i=0; i<shape_3TeV_01->GetNbinsX(); i++)
	{
		double val  = shape_3TeV_01->GetBinContent(i);
		double xval  = shape_3TeV_01->GetBinCenter(i);
		shape_binned_3TeV_01->Fill(xval,val);		
	}

	for(int i=0; i<shape_3TeV_10->GetNbinsX(); i++)
	{
		double val  = shape_3TeV_10->GetBinContent(i);
		double xval  = shape_3TeV_10->GetBinCenter(i);
		shape_binned_3TeV_10->Fill(xval,val);		
	}

	for(int i=0; i<shape_3TeV_20->GetNbinsX(); i++)
	{
		double val  = shape_3TeV_20->GetBinContent(i);
		double xval  = shape_3TeV_20->GetBinCenter(i);
		shape_binned_3TeV_20->Fill(xval,val);		
	}

	for(int i=0; i<shape_3TeV_40->GetNbinsX(); i++)
	{
		double val  = shape_3TeV_40->GetBinContent(i);
		double xval  = shape_3TeV_40->GetBinCenter(i);
		shape_binned_3TeV_40->Fill(xval,val);		
	}

	for(int i=0; i<shape_3TeV_55->GetNbinsX(); i++)
	{
		double val  = shape_3TeV_55->GetBinContent(i);
		double xval  = shape_3TeV_55->GetBinCenter(i);
		shape_binned_3TeV_55->Fill(xval,val);		
	}



		for(int i=0; i<shape_6TeV_01->GetNbinsX(); i++)
	{
		double val  = shape_6TeV_01->GetBinContent(i);
		double xval  = shape_6TeV_01->GetBinCenter(i);
		shape_binned_6TeV_01->Fill(xval,val);		
	}

	for(int i=0; i<shape_6TeV_10->GetNbinsX(); i++)
	{
		double val  = shape_6TeV_10->GetBinContent(i);
		double xval  = shape_6TeV_10->GetBinCenter(i);
		shape_binned_6TeV_10->Fill(xval,val);		
	}

	for(int i=0; i<shape_6TeV_20->GetNbinsX(); i++)
	{
		double val  = shape_6TeV_20->GetBinContent(i);
		double xval  = shape_6TeV_20->GetBinCenter(i);
		shape_binned_6TeV_20->Fill(xval,val);		
	}

	for(int i=0; i<shape_6TeV_40->GetNbinsX(); i++)
	{
		double val  = shape_6TeV_40->GetBinContent(i);
		double xval  = shape_6TeV_40->GetBinCenter(i);
		shape_binned_6TeV_40->Fill(xval,val);		
	}

	for(int i=0; i<shape_6TeV_55->GetNbinsX(); i++)
	{
		double val  = shape_6TeV_55->GetBinContent(i);
		double xval  = shape_6TeV_55->GetBinCenter(i);
		shape_binned_6TeV_55->Fill(xval,val);		
	}

	for(int i=0; i<shape_binned_3TeV_01->GetNbinsX(); i++)
	 {
		//cout <<" mass = " << Standard_Fit->GetBinCenter(i) << " Fit = " << Standard_Fit->GetBinContent(i)<< "  Data = "<< signal_data->GetBinContent(i) <<endl;
		shape_binned_3TeV_01->SetBinContent(i,shape_binned_3TeV_01->GetBinContent(i)/((shape_binned_3TeV_01->GetBinLowEdge(i+1)-shape_binned_3TeV_01->GetBinLowEdge(i))));
		shape_binned_3TeV_10->SetBinContent(i,shape_binned_3TeV_10->GetBinContent(i)/((shape_binned_3TeV_10->GetBinLowEdge(i+1)-shape_binned_3TeV_10->GetBinLowEdge(i))));
		shape_binned_3TeV_20->SetBinContent(i,shape_binned_3TeV_20->GetBinContent(i)/((shape_binned_3TeV_20->GetBinLowEdge(i+1)-shape_binned_3TeV_20->GetBinLowEdge(i))));
		shape_binned_3TeV_40->SetBinContent(i,shape_binned_3TeV_40->GetBinContent(i)/((shape_binned_3TeV_40->GetBinLowEdge(i+1)-shape_binned_3TeV_40->GetBinLowEdge(i))));
		shape_binned_3TeV_55->SetBinContent(i,shape_binned_3TeV_55->GetBinContent(i)/((shape_binned_3TeV_55->GetBinLowEdge(i+1)-shape_binned_3TeV_55->GetBinLowEdge(i))));

		shape_binned_6TeV_01->SetBinContent(i,shape_binned_6TeV_01->GetBinContent(i)/((shape_binned_6TeV_01->GetBinLowEdge(i+1)-shape_binned_6TeV_01->GetBinLowEdge(i))));
		shape_binned_6TeV_10->SetBinContent(i,shape_binned_6TeV_10->GetBinContent(i)/((shape_binned_6TeV_10->GetBinLowEdge(i+1)-shape_binned_6TeV_10->GetBinLowEdge(i))));
		shape_binned_6TeV_20->SetBinContent(i,shape_binned_6TeV_20->GetBinContent(i)/((shape_binned_6TeV_20->GetBinLowEdge(i+1)-shape_binned_6TeV_20->GetBinLowEdge(i))));
		shape_binned_6TeV_40->SetBinContent(i,shape_binned_6TeV_40->GetBinContent(i)/((shape_binned_6TeV_40->GetBinLowEdge(i+1)-shape_binned_6TeV_40->GetBinLowEdge(i))));
		shape_binned_6TeV_55->SetBinContent(i,shape_binned_6TeV_55->GetBinContent(i)/((shape_binned_6TeV_55->GetBinLowEdge(i+1)-shape_binned_6TeV_55->GetBinLowEdge(i))));

	}

/*
	TPaveText *paveCMS2 = new TPaveText(200,0.0025,1500,0.0027);
//	TPaveText *paveCMS2 = new TPaveText(200,0.0025,1800,0.0027);
	paveCMS2->AddText("quark-quark");
	paveCMS2->SetFillColor(0);
	paveCMS2->SetBorderSize(0);
//	paveCMS2->SetTextSize(0.04);
	paveCMS2->SetTextSize(0.03);

//	TPaveText *paveCMS3 = new TPaveText(200,0.0023,1000,0.0025);
	TPaveText *paveCMS3 = new TPaveText(200,0.0023,880,0.0025);
	paveCMS3->AddText("Spin 1");
	paveCMS3->SetFillColor(0);
	paveCMS3->SetBorderSize(0);
//	paveCMS3->SetTextSize(0.04);
	paveCMS3->SetTextSize(0.03);

	TPaveText *paveCMS1 = new TPaveText(200,0.0027,2400,0.0029);
//	TPaveText *paveCMS1 = new TPaveText(200,0.0027,2250,0.0029);
//	TPaveText *paveCMS1 = new TPaveText(0.25,0.87,0.45,0.9,"NDC");
//	TPaveText *paveCMS1 = new TPaveText(0.65,0.87,0.85,0.9,"NDC");
	paveCMS1->AddText("CMS #it{Simulation} ");
//	paveCMS1->AddText("quark-quark");
//	paveCMS1->AddText("Spin 1");
	paveCMS1->SetFillColor(0);
	paveCMS1->SetBorderSize(0);
	paveCMS1->SetTextSize(0.04);
*/

	TLatex *xLab = new TLatex();
//	xLab->SetTextAlign(22);
	xLab->SetTextFont(42);
	xLab->SetTextSize(0.04);         
//	xLab->DrawLatex(200, 0.027, "CMS #it{Simulation}");

	TLatex *xLab1 = new TLatex();
//	xLab1->SetTextAlign(22);
	xLab1->SetTextFont(42);
	xLab1->SetTextSize(0.042);  
	


	TPaveText *paveCMS = new TPaveText(0.81,0.965,0.93,0.975,"NDC");
	paveCMS->AddText("(13 TeV)");
	paveCMS->SetFillColor(0);
	paveCMS->SetBorderSize(0);
	paveCMS->SetTextSize(0.04);
	paveCMS->SetTextFont(42);


	shape_binned_3TeV_01->SetLineColor(kBlack);
	shape_binned_3TeV_01->SetLineWidth(2);
	shape_binned_3TeV_01->SetLabelOffset(1000);
	shape_binned_6TeV_01->SetLineColor(kBlack);
	shape_binned_6TeV_01->SetLineWidth(2);
	shape_binned_6TeV_01->SetLineStyle(2);

//	shape_binned_3TeV_10->SetLineColor(kMagenta);
	shape_binned_3TeV_10->SetLineColor(kRed);
	shape_binned_3TeV_10->SetLineWidth(2);
//	shape_binned_6TeV_10->SetLineColor(kMagenta);
	shape_binned_6TeV_10->SetLineColor(kRed);
	shape_binned_6TeV_10->SetLineWidth(2);
	shape_binned_6TeV_10->SetLineStyle(2);

	shape_binned_3TeV_20->SetLineColor(kBlue);
	shape_binned_3TeV_20->SetLineWidth(2);
	shape_binned_6TeV_20->SetLineColor(kBlue);
	shape_binned_6TeV_20->SetLineWidth(2);
	shape_binned_6TeV_20->SetLineStyle(2);

	shape_binned_3TeV_40->SetLineColor(kRed);
	shape_binned_3TeV_40->SetLineWidth(2);
	shape_binned_6TeV_40->SetLineColor(kRed);
	shape_binned_6TeV_40->SetLineWidth(2);
	shape_binned_6TeV_40->SetLineStyle(2);

	shape_binned_3TeV_55->SetLineColor(kGreen+2);
	shape_binned_3TeV_55->SetLineWidth(2);
	shape_binned_6TeV_55->SetLineColor(kGreen+2);
	shape_binned_6TeV_55->SetLineWidth(2);
	shape_binned_6TeV_55->SetLineStyle(2);



	TCanvas *c1 = new TCanvas("c1","Superimposed Resonance Shapes",700,700);


	c1->cd();
//	c1->SetLogy(1);

	shape_binned_3TeV_01->GetYaxis()->SetRangeUser(0.0,0.003);
	shape_binned_3TeV_01->GetYaxis()->SetTitle("Normalized Yield / GeV");
	shape_binned_3TeV_01->GetYaxis()->SetLabelSize(0.03);
	shape_binned_3TeV_01->GetXaxis()->SetLabelSize(0.035);
	shape_binned_3TeV_01->GetXaxis()->SetTitle("Dijet mass [TeV]");
	shape_binned_3TeV_01->GetXaxis()->SetRangeUser(xaxis_start,xaxis_end);
	shape_binned_3TeV_01->Draw("hist");

	shape_binned_3TeV_10->Draw("hist same");
	shape_binned_3TeV_20->Draw("hist same");
//	shape_binned_3TeV_40->Draw("hist same");
	shape_binned_3TeV_55->Draw("hist same");

	shape_binned_6TeV_01->Draw("hist same");
	shape_binned_6TeV_10->Draw("hist same");
	shape_binned_6TeV_20->Draw("hist same");
//	shape_binned_6TeV_40->Draw("hist same");
	shape_binned_6TeV_55->Draw("hist same");

	TLatex *xLab2 = new TLatex();
	xLab2->SetTextAlign(22);
	xLab2->SetTextFont(42);
	xLab2->SetTextSize(0.05);    
	xLab2->DrawLatex(0, -0.0001, "0");
	xLab2->DrawLatex(1000, -0.0001, "1");     
	xLab2->DrawLatex(2000, -0.0001, "2");
	xLab2->DrawLatex(3000, -0.0001, "3");
	xLab2->DrawLatex(4000, -0.0001, "4");
	xLab2->DrawLatex(5000, -0.0001, "5");
	xLab2->DrawLatex(6000, -0.0001, "6");




	TLegend *leg;
	leg = new TLegend(0.65,0.6,0.95,0.92,NULL,"brNDC");
	//if( mass_to_plot > 0.5*(xaxis_end+xaxis_start))leg = new TLegend(0.20,0.55,0.45,0.86,NULL,"brNDC");
	//else leg = new TLegend(0.65,0.55,0.95,0.86,NULL,"brNDC");
	//leg->AddEntry(truncated_shape_1,"#Gamma/M = 30%","PL");
	//leg->AddEntry(truncated_shape_1,"#Gamma/M = 30%","PL");
	leg->AddEntry(shape_binned_3TeV_01,"2 TeV","L");
	leg->AddEntry(shape_binned_6TeV_01,"5 TeV","L");

	leg->AddEntry(shape_binned_3TeV_01,"#Gamma/M = 1%","L");
	leg->AddEntry(shape_binned_3TeV_10,"#Gamma/M = 10%","L");
	leg->AddEntry(shape_binned_3TeV_20,"#Gamma/M = 20%","L");
//	leg->AddEntry(shape_binned_3TeV_40,"#Gamma/M = 40%","L");
	leg->AddEntry(shape_binned_3TeV_55,"#Gamma/M = 55%","L");


/*
	TLegend *leg2;
	leg2 = new TLegend(0.25,0.65,0.45,0.86,NULL,"brNDC");
	leg2->AddEntry(shape_binned_3TeV_01,"2 TeV","L");
	leg2->AddEntry(shape_binned_6TeV_01,"5 TeV","L");
*/



	leg->SetFillColor(0);
	leg->SetTextSize(0.035);
	leg->SetFillStyle(0);
	leg->SetBorderSize(0);
	leg->Draw("SAME");
	paveCMS->Draw("same");
	
	xLab->DrawLatex(200, 0.0027, "#bf{CMS #it{Simulation}}");       
	xLab1->DrawLatex(200, 0.00245, "quark-quark");
	xLab1->DrawLatex(200, 0.0022, "Spin 1");
//	paveCMS1->Draw("same");
//	paveCMS2->Draw("same");
//	paveCMS3->Draw("same");
	//leg2->Draw("same");


	char png_name[450];
//	sprintf(png_name,"%s/Comparison_%s_wide_0p3_spin1_shape_%iGeV_truncate_%i.png",output_directory,resonance,mass_to_plot,truncation_mass);
//	sprintf(png_name,"%s/Comparison_shape_%iGeV_%s.png",output_directory,mass_to_plot,image_name);

//	sprintf(png_name,"Signal_shape_Paper_Plot.png");
//	sprintf(png_name,"Signal_shape_Paper_Plot.pdf");
//	cout << png_name << endl;
	c1->SaveAs("Signal_shape_Paper_Plot_10included_v3.pdf");
	c1->SaveAs("Signal_shape_Paper_Plot_10included_v3.png");
//	c1->SaveAs("test.png");









}
