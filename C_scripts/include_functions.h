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
#include "TLegendEntry.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include "TLine.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TGraph.h"
#include "setTDRStyle_teliko.C"
#include <algorithm>
#include <string>
#include <stdarg.h>

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


TH1D* truncate_the_shape_high_end(int truncation_mass, TH1D* full_shape)
{
	TH1D *truncated_shape = (TH1D*)(full_shape->Clone());
	
	int nbins = full_shape->GetNbinsX();
	double mass;
	for (int i=0; i<nbins; i++)
	{
		mass = truncated_shape->GetBinCenter(i); 
		if (mass > truncation_mass) truncated_shape->SetBinContent(i,0);
	}
	
	return truncated_shape;
}


char *stitch_the_string(int No_of_string_parts, ...)
{
    va_list string_parts;
    int j;
    char final_string[300];
    va_start(string_parts, No_of_string_parts); //Requires the last fixed parameter (to get the address)
    for(j=0; j<No_of_string_parts; j++)
	{
		if ( j==0 ) strcpy(	final_string,va_arg(string_parts, char*)); 
		else strcat( final_string,va_arg(string_parts, char*)); 
	//	tot+=va_arg(string_parts, char); //Requires the type to cast to. Increments ap to the next argument.
	}
    va_end(string_parts);
    return final_string;
}

double Find_intersection_of_two_graphs(TGraph* first_graph, TGraph* second_graph, int range_start , int range_end )
{
	double current_point_x = 0, first_graph_value=0, second_graph_value=0;
	long double distance=0 ,distance_initial=0, distance_final =0;
	double x_point_of_min_distance = 0, value_of_min_distance = 0;
	long double d_min=100 ;

	for (int i=0; i<10*(range_end-range_start); i++)
	{
		current_point_x = range_start + 0.1*(i+1)/(range_end - range_start)*(range_end-range_start) ;
		first_graph_value  =  first_graph->Eval(current_point_x,0,"");        //interpolated y coordinate of 1st graph
		second_graph_value = second_graph->Eval(current_point_x,0,"");       //interpolated y coordinate of 2nd graph
		distance = sqrt ( (second_graph_value-first_graph_value)*(second_graph_value-first_graph_value) );
		if(i==0) distance_initial = distance;
		if(i==10*(range_end-range_start) -1) distance_final = distance;
		//cout << " x = "<<x_1 <<" y1exp= "<<y1<<" y2exp= "<<y2<<" d = "<< d<< endl;
		if (distance < d_min)
		{ 
			d_min = distance;
			x_point_of_min_distance = current_point_x;
			value_of_min_distance = first_graph_value;   
			   //cout << " dmin = " << d_min<<endl ;         
		}
	} 

	if(d_min!=distance_initial && d_min!=distance_final && d_min<0.0000001) return x_point_of_min_distance;
	else return -1;
}
