
void create_yaml_forHEPData_spectrum_alphabins(){


TFile *f1 = new TFile("/eos/user/i/izisopou/4jets/CMSSW_10_2_13/src/CMSDIJET/DijetRootTreeAnalyzer/Fig6_forHEPData_alpha7.root","READ");
TFile *f2 = new TFile("/eos/user/i/izisopou/4jets/CMSSW_10_2_13/src/CMSDIJET/DijetRootTreeAnalyzer/Fig6_forHEPData_alpha8.root","READ");
TFile *f3 = new TFile("/eos/user/i/izisopou/4jets/CMSSW_10_2_13/src/CMSDIJET/DijetRootTreeAnalyzer/Fig6_forHEPData_alpha9.root","READ");

TGraphAsymmErrors *g1 = (TGraphAsymmErrors*)f1->Get("Graph_from_h_FourjetMass");
TGraphAsymmErrors *g2 = (TGraphAsymmErrors*)f2->Get("Graph_from_h_FourjetMass");
TGraphAsymmErrors *g3 = (TGraphAsymmErrors*)f3->Get("Graph_from_h_FourjetMass");

ofstream yaml_file;
yaml_file.open("m4j_spectrum_alphabins.yaml");

yaml_file << "dependent_variables:" << endl;

//------------- 0.22<alpha<0.24  -------------

yaml_file << "- header:" << endl;
yaml_file << "    name: Event yield for 0.22<\\alpha<0.24" << endl;
yaml_file << "  values:" << endl;

for(int i=47; i<=89; i++)
{
	double x,y;
	g1->GetPoint(i,x,y);
	double m4j_low = x - g1->GetErrorXlow(i);
	double m4j_high = x + g1->GetErrorXhigh(i);

	double err_high = g1->GetErrorYhigh(i);
	double err_low = g1->GetErrorYlow(i);

	double cont = y*((m4j_high-m4j_low)*137000)/1000.;

	yaml_file << "  - value: " << cont << ".0" << endl;
}


yaml_file << "- header:" << endl;
yaml_file << "    name: Cross-section for 0.22<\\alpha<0.24" << endl;
yaml_file << "    units: pb/TeV" << endl;
yaml_file << "  values:" << endl;

for(int i=47; i<=89; i++)
{
	double x,y;
	g1->GetPoint(i,x,y);
	double m4j_low = x - g1->GetErrorXlow(i);
	double m4j_high = x + g1->GetErrorXhigh(i);

	double err_high = g1->GetErrorYhigh(i);
	double err_low = g1->GetErrorYlow(i);

	yaml_file << "  - errors:" << endl;
	yaml_file << "    - asymerror:" << endl;
	yaml_file << "        minus: -" << err_low << endl;
	yaml_file << "        plus: " << err_high << endl;
	yaml_file << "      label: Total" << endl;
	yaml_file << "    value: " << y << endl;
}

//------------- 0.24<alpha<0.26  -------------

yaml_file << "- header:" << endl;
yaml_file << "    name: Event yield for 0.24<\\alpha<0.26" << endl;
yaml_file << "  values:" << endl;

for(int i=47; i<=89; i++)
{
	double x,y;
	g2->GetPoint(i,x,y);
	double m4j_low = x - g2->GetErrorXlow(i);
	double m4j_high = x + g2->GetErrorXhigh(i);

	double err_high = g2->GetErrorYhigh(i);
	double err_low = g2->GetErrorYlow(i);

	double cont = y*((m4j_high-m4j_low)*137000)/1000.;

	yaml_file << "  - value: " << cont << ".0" << endl;
}


yaml_file << "- header:" << endl;
yaml_file << "    name: Cross-section for 0.24<\\alpha<0.26" << endl;
yaml_file << "    units: pb/TeV" << endl;
yaml_file << "  values:" << endl;

for(int i=47; i<=89; i++)
{
	double x,y;
	g2->GetPoint(i,x,y);
	double m4j_low = x - g2->GetErrorXlow(i);
	double m4j_high = x + g2->GetErrorXhigh(i);

	double err_high = g2->GetErrorYhigh(i);
	double err_low = g2->GetErrorYlow(i);

	yaml_file << "  - errors:" << endl;
	yaml_file << "    - asymerror:" << endl;
	yaml_file << "        minus: -" << err_low << endl;
	yaml_file << "        plus: " << err_high << endl;
	yaml_file << "      label: Total" << endl;
	yaml_file << "    value: " << y << endl;
}


//------------- 0.26<alpha<0.28  -------------

yaml_file << "- header:" << endl;
yaml_file << "    name: Event yield for 0.26<\\alpha<0.28" << endl;
yaml_file << "  values:" << endl;

for(int i=47; i<=89; i++)
{
	double x,y;
	g3->GetPoint(i,x,y);
	double m4j_low = x - g3->GetErrorXlow(i);
	double m4j_high = x + g3->GetErrorXhigh(i);

	double err_high = g3->GetErrorYhigh(i);
	double err_low = g3->GetErrorYlow(i);

	double cont = y*((m4j_high-m4j_low)*137000)/1000.;

	yaml_file << "  - value: " << cont << ".0" << endl;
}


yaml_file << "- header:" << endl;
yaml_file << "    name: Cross-section for 0.26<\\alpha<0.28" << endl;
yaml_file << "    units: pb/TeV" << endl;
yaml_file << "  values:" << endl;

for(int i=47; i<=89; i++)
{
	double x,y;
	g3->GetPoint(i,x,y);
	double m4j_low = x - g3->GetErrorXlow(i);
	double m4j_high = x + g3->GetErrorXhigh(i);

	double err_high = g3->GetErrorYhigh(i);
	double err_low = g3->GetErrorYlow(i);

	yaml_file << "  - errors:" << endl;
	yaml_file << "    - asymerror:" << endl;
	yaml_file << "        minus: -" << err_low << endl;
	yaml_file << "        plus: " << err_high << endl;
	yaml_file << "      label: Total" << endl;
	yaml_file << "    value: " << y << endl;
}

//------------- Four-jet mass  -------------

yaml_file << "independent_variables:" << endl;
yaml_file << "- header:" << endl;
yaml_file << "    name: Four-jet mass" << endl;
yaml_file << "    units: GeV" << endl;
yaml_file << "  values:" << endl;

for(int i=47; i<=89; i++)
{
	double x,y;
	g1->GetPoint(i,x,y);
	double m4j_low = x - g1->GetErrorXlow(i);
	double m4j_high = x + g1->GetErrorXhigh(i);

	double err_high = g1->GetErrorYhigh(i);
	double err_low = g1->GetErrorYlow(i);

	yaml_file << "  - high: " << m4j_high << ".0" << endl;
	yaml_file << "    low: " << m4j_low << ".0" << endl;
}

}
