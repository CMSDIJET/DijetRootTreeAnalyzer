
void create_yaml_forHEPData_spectrum_incl(){


TFile *f = new TFile("/eos/user/i/izisopou/4jets/CMSSW_10_2_13/src/CMSDIJET/DijetRootTreeAnalyzer/Fig14_forHEPData.root","READ");

TGraphAsymmErrors *g = (TGraphAsymmErrors*)f->Get("Graph_from_h_FourjetMass");

ofstream yaml_file;
yaml_file.open("m4j_spectrum_incl.yaml");

yaml_file << "dependent_variables:" << endl;
yaml_file << "- header:" << endl;
yaml_file << "    name: Event yield" << endl;
yaml_file << "  values:" << endl;


for(int i=46; i<=89; i++)
{
	double x,y;
	g->GetPoint(i,x,y);
	double m4j_low = x - g->GetErrorXlow(i);
	double m4j_high = x + g->GetErrorXhigh(i);

	double err_high = g->GetErrorYhigh(i);
	double err_low = g->GetErrorYlow(i);

	double cont = y*((m4j_high-m4j_low)*137000)/1000.;

	yaml_file << "  - value: " << cont << ".0" << endl;
}


yaml_file << "- header:" << endl;
yaml_file << "    name: Cross-section" << endl;
yaml_file << "    units: pb/TeV" << endl;
yaml_file << "  values:" << endl;

for(int i=46; i<=89; i++)
{
	double x,y;
	g->GetPoint(i,x,y);
	double m4j_low = x - g->GetErrorXlow(i);
	double m4j_high = x + g->GetErrorXhigh(i);

	double err_high = g->GetErrorYhigh(i);
	double err_low = g->GetErrorYlow(i);

	yaml_file << "  - errors:" << endl;
	yaml_file << "    - asymerror:" << endl;
	yaml_file << "        minus: -" << err_low << endl;
	yaml_file << "        plus: " << err_high << endl;
	yaml_file << "      label: Total" << endl;
	yaml_file << "    value: " << y << endl;
}

yaml_file << "independent_variables:" << endl;
yaml_file << "- header:" << endl;
yaml_file << "    name: Four-jet mass" << endl;
yaml_file << "    units: GeV" << endl;
yaml_file << "  values:" << endl;

for(int i=46; i<=89; i++)
{
	double x,y;
	g->GetPoint(i,x,y);
	double m4j_low = x - g->GetErrorXlow(i);
	double m4j_high = x + g->GetErrorXhigh(i);

	double err_high = g->GetErrorYhigh(i);
	double err_low = g->GetErrorYlow(i);

	yaml_file << "  - high: " << m4j_high << ".0" << endl;
	yaml_file << "    low: " << m4j_low << ".0" << endl;
}

}
