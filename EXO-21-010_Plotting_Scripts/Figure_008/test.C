

void test(){

TFile *f1 = new TFile("test_pulls_alpha1.root");
//TFile *f2 = new TFile("test_pulls_alpha6_ilias.root");

TH1D *h1 = (TH1D*)f1->Get("h_FourjetMass");
//TH1D *h2 = (TH1D*)f2->Get("h_FourjetMass");

double sum=0;
//double sum_ilias=0;

for(int i=1; i<=h1->GetNbinsX(); i++)
{
	sum+=h1->GetBinContent(i)*h1->GetBinContent(i);
}

cout << "chi2 = " << sum << endl;

/*for(int i=1; i<=h2->GetNbinsX(); i++)
{
	sum_ilias+=h2->GetBinContent(i)*h2->GetBinContent(i);
}

cout << "chi2 = " << sum_ilias << endl;
*/
}
