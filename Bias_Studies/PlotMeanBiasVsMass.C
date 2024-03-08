#include <TFile.h>
#include <TDirectoryFile.h>
#include <TMath.h>
#include "setTDRStyle_teliko.C"

void biasVSmass(){

  gROOT->LoadMacro("setTDRStyle_teliko.C");
  setTDRStyle_teliko();
/*
//===========Signal = Expected================
//=== Dijet ====
	mean		error
2: -7.24591e-02   3.64795e-02
3: 5.31263e-02   4.28896e-02
4: 6.68303e-03   3.23145e-02
6:  -9.49660e-02   3.93104e-02
7:  -1.20345e-01   4.01363e-02
8:  1.66280e-01   3.53013e-02
9:  1.87614e-01   3.86760e-02

//==ATLAS===
2: 1.04509e-01   4.06977e-02
3: -6.02051e-02   4.10766e-02
4: 1.17518e-02   3.32471e-02
6: 7.77814e-02   3.74066e-02
7: -2.64737e-02   3.87989e-02
8: 1.45566e-01   3.42474e-02
9: 1.22474e-01   3.80605e-02
//=== ModDijet ====
2: 6.20381e-02   4.49512e-02
3: -6.14169e-02   3.85009e-02
4: 5.62505e-02   3.43562e-02
6:  -6.83044e-02   3.72636e-02
7:  -4.87674e-02   4.07920e-02
8: 1.05899e-01   3.54211e-02
9: 1.76073e-01   3.73574e-02

//===========Signal = 5sigma================
//== Dijet===
2: -2.89812e-01   3.66786e-02
3: -4.44218e-01   4.29693e-02 
4: 1.33805e-02   4.00130e-02
5:
6: -1.96454e-01   3.89907e-02
7: -1.16684e-01   4.12598e-02
8: 6.95868e-04   3.84393e-02
9: -5.09269e-02   4.29869e-02

//== ATLAS===
2: -3.37329e-01   4.38796e-02
3:  -5.04228e-01   4.05784e-02
4: -6.10668e-02   4.07235e-02
5:
6:  -4.49036e-02   4.01689e-02
7: 2.99264e-02   3.62177e-02
8:  8.52775e-02   3.73964e-02
9: -1.28471e-02   3.95953e-02 

//== ModDijet===
2: -1.97933e-01   3.76902e-02
3: -4.56478e-01   4.00725e-02
4:  9.12221e-02   3.89243e-02
5:
6: -5.70206e-02   3.86181e-02
7: -6.14596e-02   4.28179e-02
8: 6.97391e-04   3.90856e-02
9: -3.85149e-02   4.06031e-02



//===========Signal = 0================
//== Dijet===
2: -5.87049e-02   3.14755e-02
3: 5.30405e-02   4.02809e-02
4:  3.65981e-02   4.41993e-02
5:
6:
7:

//== ATLAS===
2: 7.17292e-03   2.70080e-02
3: -2.87334e-02   4.66409e-02
4: 2.35789e-02   4.55295e-02
5:
6:
7:
8:
9:
//== ModDijet===
2: 4.52522e-02   2.63822e-02 
3: -8.83563e-03   4.20193e-02
4:  2.69351e-02   3.84175e-02
5:
6:
7:
8:
9:
*/

//===alpha 0.42 ===
//===============signal=expected======
//===Dijet===
//2:  -8.67121e-02   4.02553e-02
//8: -7.69602e-02   3.34031e-02
//==ATLAS===
//2:  3.60421e-02   3.74807e-02
//8: 1.48504e-01   3.85368e-02
//===ModDijet===
//2: 7.93648e-02   4.05976e-02
//8: -8.29139e-02   3.80962e-02
//===============signal=5s======
//===Dijet===
//2:  -3.38361e-01   3.50980e-02
//8: -1.44791e-01   3.99169e-02
//==ATLAS===
//2: -2.29490e-01   3.57271e-02
//8: 8.93963e-02   4.22590e-02
//===ModDijet===
//2: -2.26048e-01   3.71656e-02
//8: -1.36699e-01   4.03652e-02
//===============signal=0======
//===Dijet===
//2:
//8: 
//==ATLAS===
//2:
//8:
//===ModDijet===
//2:
//8:

 //===alpha 0.11 ===
//===============signal=expected======
//===Dijet===
//2: -5.68442e-02   3.88134e-02
//8: 3.81928e-02   3.82049e-02
//==ATLAS===
//2:  -1.55824e-02   3.96809e-02 
//8:
//===ModDijet===
//2: -3.98287e-02   4.30086e-02
//8:
//===============signal=5s======
//===Dijet===
//2:  -4.54371e-01   4.58170e-02
//8: -1.42660e-01   3.53822e-02
//==ATLAS===
//2: -3.20499e-01   3.89712e-02
//8:
//===ModDijet===
//2: -3.34903e-01   4.17552e-02
//8:
//===============signal=0======
//===Dijet===
//2:  -9.52190e-02   3.88241e-02
//8: 
//==ATLAS===
//2: 5.46699e-02   3.88186e-02  
//8:
//===ModDijet===
//2: 3.19459e-02   4.11246e-02
//8:
 
 /*

//==Dijet===
//alpha= 0.25
double bias[7]={ -7.24591e-02, 5.31263e-02,6.68303e-03, -9.49660e-02, -1.20345e-01, 1.66280e-01, 1.87614e-01};
double bias_error[7]={3.64795e-02, 4.28896e-02,3.23145e-02,3.93104e-02, 4.01363e-02, 3.53013e-02, 3.86760e-02};
double bias0[3]={-5.87049e-02, 5.30405e-02,3.65981e-02};
double bias0_error[3]={3.14755e-02,4.02809e-02,4.41993e-02};
double bias5s[7]={-2.89812e-01,-4.44218e-01, 1.33805e-02,-1.96454e-01,-1.16684e-01,6.95868e-04,-5.09269e-02};
double bias5s_error[7]={3.66786e-02, 4.29693e-02,4.00130e-02,3.89907e-02,4.12598e-02,3.84393e-02,4.29869e-02};
//alpha= 0.11
double bias1[1]={-5.68442e-02, };
double bias1_error[1]={3.88134e-02};
double bias10[1]={-9.52190e-02};
double bias10_error[1]={ 3.88241e-02};
double bias15s[1]={-4.54371e-01};
double bias15s_error[1]={ 4.58170e-02};
//alpha= 0.42
double bias2[2]={ -8.67121e-02,-7.69602e-02};
double bias2_error[2]={4.02553e-02,3.34031e-02};
double bias20[2]={};
double bias20_error[2]={};
double bias25s[2]={-3.38361e-01,-1.44791e-01};
double bias25s_error[2]={ 3.50980e-02,3.99169e-02};



//===ATLAS===
//alpha= 0.25
double bias[7]={1.04509e-01,-5.67698e-02,-6.10668e-02,7.77814e-02,-2.64737e-02, 1.45566e-01,1.22474e-01};
double bias_error[7]={4.06977e-02,3.84103e-02, 4.07235e-02,3.74066e-02,3.87989e-02,3.42474e-02 ,3.80605e-02};
double bias0[3]={7.17292e-03,-2.87334e-02,2.35789e-02};
double bias0_error[3]={2.70080e-02,4.66409e-02,4.55295e-02};
double bias5s[7]={-3.37329e-01,-5.04228e-01,-6.10668e-02,-4.49036e-02,2.99264e-02,8.52775e-02,-1.28471e-02};
double bias5s_error[7]={4.38796e-02,4.05784e-02,4.07235e-02,4.01689e-02,3.62177e-02,3.73964e-02,3.95953e-02};
//alpha= 0.11
double bias1[1]={-1.55824e-02};
double bias1_error[1]={3.96809e-02 };
double bias10[1]={5.46699e-02};
double bias10_error[1]={3.88186e-02};
double bias15s[1]={-3.20499e-01};
double bias15s_error[1]={3.89712e-02};
//alpha= 0.42
double bias2[2]={ 3.60421e-02,1.48504e-01 };
double bias2_error[2]={ 3.74807e-02,3.85368e-02};
double bias20[2]={};
double bias20_error[2]={};
double bias25s[2]={ -2.29490e-01,8.93963e-02};
double bias25s_error[2]={3.57271e-02,4.22590e-02};

*/

//==ModDijet===
//alpha= 0.25
double bias[7]={6.20381e-02,-5.72110e-02, 9.12221e-02, -6.83044e-02,-4.87674e-02,1.05899e-01 ,1.76073e-01};
double bias_error[7]={4.49512e-02,4.00797e-02,3.89243e-02,3.72636e-02,4.07920e-02,3.54211e-02,3.73574e-02};
double bias0[3]={4.52522e-02,-8.83563e-03,2.69351e-02};
double bias0_error[3]={ 2.63822e-02, 4.20193e-02, 3.84175e-02};
double bias5s[7]={-1.97933e-01,-4.56478e-01, 9.12221e-02,-5.70206e-02,-6.14596e-02,6.97391e-04,-3.85149e-02};
double bias5s_error[7]={3.76902e-02,4.00725e-02,3.89243e-02,3.86181e-02,4.28179e-02,3.90856e-02,4.06031e-02};
//alpha= 0.11
double bias1[1]={-3.98287e-02};
double bias1_error[1]={4.30086e-02};
double bias10[1]={3.19459e-02};
double bias10_error[1]={4.11246e-02};
double bias15s[1]={-3.34903e-01};
double bias15s_error[1]={4.17552e-02};
//alpha= 0.42
double bias2[2]={7.93648e-02,-8.29139e-02 };
double bias2_error[2]={4.05976e-02,3.80962e-02};
double bias20[2]={};
double bias20_error[2]={};
double bias25s[2]={-2.26048e-01, -1.36699e-01};  
double bias25s_error[2]={3.71656e-02,4.03652e-02};

 

double mass[7]={2, 3, 4, 6, 7, 8, 9};
double mass1[1]={2};
double mass2[2]={2,8};
 
auto cv = new TCanvas("cv","cv",800,600);//800,600);
TGraph *gr_bias = new TGraphErrors(7, mass, bias, 0, bias_error);
gr_bias->GetXaxis()->SetTitle("S_{uu} mass [TeV]");
gr_bias->GetYaxis()->SetTitleOffset(0.95);
gr_bias->GetYaxis()->SetTitle("mean bias"); 
gr_bias->SetMarkerColor(2);
gr_bias->GetYaxis()->SetRangeUser(-0.8,0.8);
gr_bias->GetXaxis()->SetRangeUser(1.5,9.2);
gr_bias->Draw("AP"); // RX P*"); //A RX RY P*");
//pave_M4J->Draw("same");

TGraph *gr_bias0 = new TGraphErrors(3, mass, bias0, 0, bias0_error);
gr_bias0->SetMarkerColor(4);
gr_bias0->Draw("P same");

TGraph *gr_bias5s = new TGraphErrors(7, mass, bias5s, 0, bias5s_error);
gr_bias5s->SetMarkerColor(3);
gr_bias5s->Draw("P same");

//=== alpha=0.11 ===
TGraph *gr_bias1 = new TGraphErrors(1, mass1, bias1, 0, bias1_error);
gr_bias1->SetMarkerColor(2);
gr_bias1->SetMarkerStyle(33);
gr_bias1->Draw("P same");

TGraph *gr_bias10 = new TGraphErrors(1, mass1, bias10, 0, bias10_error);
gr_bias10->SetMarkerColor(4);
gr_bias10->SetMarkerStyle(33);
gr_bias10->Draw("P same");

TGraph *gr_bias15s = new TGraphErrors(1, mass1, bias15s, 0, bias15s_error);
gr_bias15s->SetMarkerColor(3);
gr_bias15s->SetMarkerStyle(33);
gr_bias15s->Draw("P same");

//=== alpha=0.42 ===
TGraph *gr_bias2 = new TGraphErrors(2, mass2, bias2, 0, bias25s_error);
gr_bias2->SetMarkerColor(2);
gr_bias2->SetMarkerStyle(22);
gr_bias2->Draw("P same");

TGraph *gr_bias20 = new TGraphErrors(2, mass1, bias20, 0, bias20_error);  
gr_bias20->SetMarkerColor(4);
gr_bias20->SetMarkerStyle(22);
//gr_bias20->Draw("P same");

TGraph *gr_bias25s = new TGraphErrors(2, mass2, bias25s, 0, bias25s_error);
gr_bias25s->SetMarkerColor(3);
gr_bias25s->SetMarkerStyle(22);
gr_bias25s->Draw("P same");


TLine *line = new TLine(1.5,0,9.2,0); 
line->SetLineWidth(2);
line->Draw("same");

TLine *line1 = new TLine(1.5,.50,9.2,0.5); 
line1->SetLineColor(2);
line1->SetLineStyle(2);
line1->Draw("same");

TLine *line2 = new TLine(1.5,-0.5,9.2,-0.5); 
line2->SetLineColor(2);
line2->SetLineStyle(2);
line2->Draw("same");


 TLegend *leg1 =new TLegend(.90, .75, .60, .93); //.55, .85, .65, .93);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.035);
  leg1->SetHeader("#alpha_{True}=0.25");
  leg1->AddEntry(gr_bias0, "r = 0", "P");
  leg1->AddEntry(gr_bias, "r = expected ", "P");
  leg1->AddEntry(gr_bias5s, "r = 5#sigma ", "P");
  leg1->Draw("same");

TLegend *leg2 =new TLegend(.90, .75, .60, .93); //.55, .85, .65, .93);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetHeader("#alpha_{True}=0.11");
  leg2->AddEntry(gr_bias10, "r = 0", "P");
  leg2->AddEntry(gr_bias1, "r = expected ", "P");
  leg2->AddEntry(gr_bias15s, "r = 5#sigma ", "P");
  leg2->Draw("same");

TLegend *leg3 =new TLegend(.90, .75, .60, .93); //.55, .85, .65, .93);
  leg3->SetFillColor(0);
  leg3->SetBorderSize(0);
  leg3->SetTextSize(0.035);
  leg3->SetHeader("#alpha_{True}=0.42");
  leg3->AddEntry(gr_bias20, "r = 0", "P");
  leg3->AddEntry(gr_bias2, "r = expected ", "P");
  leg3->AddEntry(gr_bias25s, "r = 5#sigma ", "P");
  leg3->Draw("same");




TPaveText *pave_Sig_low_xsec = new TPaveText(0.1,0.96,0.97,0.99,"NDC");//(0.15,0.82,0.45,0.87,"NDC");
pave_Sig_low_xsec->AddText("  Generated with ModDijet function ");
pave_Sig_low_xsec->SetBorderSize(0);
pave_Sig_low_xsec->SetFillColor(0);
pave_Sig_low_xsec->SetTextSize(0.04);
pave_Sig_low_xsec->Draw();

//cv->SaveAs("bias_plotsAN/biasVSmass_GenDijet.png"); 
//cv->SaveAs("bias_plotsAN/biasVSmass_GenAtlas.png"); 
cv->SaveAs("bias_plotsAN/biasVSmass_GenModDijet.png"); 


}



