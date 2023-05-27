
void create_yaml_forHEP(){

int alphap = 42;

char input_name[1024], output_name[1024];
sprintf(input_name,"GetCombine_final/limits/Limits_alpha0p%d/limits_freq_gg_pfdijet2017_alpha0p%d_red.root",alphap,alphap);
TFile *f = new TFile(input_name,"READ");

TGraph *obs = (TGraph*)f->Get("obs_gg_pfdijet2017");
TGraph *exp = (TGraph*)f->Get("exp_gg_pfdijet2017");
TGraphAsymmErrors *unc_1s = (TGraphAsymmErrors*)f->Get("exp1sigma_gg_pfdijet2017");
TGraphAsymmErrors *unc_2s = (TGraphAsymmErrors*)f->Get("exp2sigma_gg_pfdijet2017");
TGraph *diq = (TGraph*)f->Get("Diquark");

ofstream yaml_file;
sprintf(output_name,"cross_section_limits_alpha0p%d.yaml",alphap);
yaml_file.open(output_name);

yaml_file << "dependent_variables:" << endl;

//------------------- Observed -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL observed upper limits" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int point=0; point<=70; point++)
{
	double x,y;
	obs->GetPoint(point,x,y);
	yaml_file << "  - value: " << y << endl;
}

//------------------- -2 sigma expected -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL expected -2 s.d. upper limits" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int point=0; point<=70; point++)
{
	double x,y;
	unc_2s->GetPoint(point,x,y);
	double err = unc_2s->GetErrorYlow(point);
	yaml_file << "  - value: " << y-err << endl;
}

//------------------- -1 sigma expected -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL expected -1 s.d. upper limits" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int point=0; point<=70; point++)
{
	double x,y;
	unc_1s->GetPoint(point,x,y);
	double err = unc_1s->GetErrorYlow(point);
	yaml_file << "  - value: " << y-err << endl;
}

//------------------- Expected -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL expected upper limits" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int point=0; point<=70; point++)
{
	double x,y;
	exp->GetPoint(point,x,y);
	yaml_file << "  - value: " << y << endl;
}

//------------------- +1 sigma expected -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL expected +1 s.d. upper limits" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int point=0; point<=70; point++)
{
	double x,y;
	unc_1s->GetPoint(point,x,y);
	double err = unc_1s->GetErrorYhigh(point);
	yaml_file << "  - value: " << y+err << endl;
}

//------------------- +2 sigma expected -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: 95% CL expected +2 s.d. upper limits" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int point=0; point<=70; point++)
{
	double x,y;
	unc_2s->GetPoint(point,x,y);
	double err = unc_2s->GetErrorYhigh(point);
	yaml_file << "  - value: " << y+err << endl;
}

//------------------- Diquark -------------------

yaml_file << "- header:" << endl;
yaml_file << "    name: Diquark cross section" << endl;
yaml_file << "    units: pb" << endl;
yaml_file << "  values:" << endl;

for (int mass=2000; mass<=9000; mass=mass+100)
{
	double x,y;
	bool flag = false;
	for(int point=0; point<diq->GetN(); point++)
	{
		diq->GetPoint(point,x,y);
		if(x==mass) 
		{
			flag = true;
			break;
		}
	}

	if(flag==false)
	{
		yaml_file << "  - value: '-'" << endl;
	}
	else
	{
		yaml_file << "  - value: " << y << endl;
	}
}

//------------------- Resonance mass -------------------

yaml_file << "independent_variables:" << endl;

yaml_file << "- header:" << endl;
yaml_file << "    name: Resonance mass" << endl;
yaml_file << "    units: GeV" << endl;
yaml_file << "  values:" << endl;

for (int point=0; point<=70; point++)
{
	double x,y;
	exp->GetPoint(point,x,y);
	yaml_file << "  - value: " << x << ".0" << endl;
}

//-----------------------------------------------------



}
