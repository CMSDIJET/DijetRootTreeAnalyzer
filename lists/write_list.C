void write_list(){

ofstream Input_list_1("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_1of10.txt");
ofstream Input_list_2("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_2of10.txt");
ofstream Input_list_3("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_3of10.txt");
ofstream Input_list_4("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_4of10.txt");
ofstream Input_list_5("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_5of10.txt");
ofstream Input_list_6("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_6of10.txt");
ofstream Input_list_7("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_7of10.txt");
ofstream Input_list_8("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_8of10.txt");
ofstream Input_list_9("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_9of10.txt");
ofstream Input_list_10("2022_promptreco/list_JetMET_Run2022G-PromptReco-v1_10of10.txt");

char name[1024];

int n1 = 16;
int n2 = n1*2;
int n3 = n1*3; 
int n4 = n1*4;
int n5 = n1*5;
int n6 = n1*6;
int n7 = n1*7;
int n8 = n1*8;
int n9 = n1*9;
int n10 = 162;

for(int i=1; i<=n10; i++)
{
	sprintf(name, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run3/big_trees/data/promptReco/JetMET/crab_JetMET__Run2022G-PromptReco-v1__MINIAOD/230220_160742/0000/JetMET__Run2022G-PromptReco-v1__MINIAOD_%d.root",i);

	if(i>=1   && i<=n1)  Input_list_1 << name << endl;
	if(i>=n1+1  && i<=n2)  Input_list_2 << name << endl;
	if(i>=n2+1  && i<=n3) Input_list_3 << name << endl;
	if(i>=n3+1  && i<=n4) Input_list_4 << name << endl;
	if(i>=n4+1 && i<=n5) Input_list_5 << name << endl;
	if(i>=n5+1 && i<=n6) Input_list_6 << name << endl;
	if(i>=n6+1 && i<=n7) Input_list_7 << name << endl;
	if(i>=n7+1 && i<=n8) Input_list_8 << name << endl;
	if(i>=n8+1 && i<=n9) Input_list_9 << name << endl;
	if(i>=n9+1 && i<=n10) Input_list_10 << name << endl;
}


Input_list_1.close();
Input_list_2.close();
Input_list_3.close();
Input_list_4.close();
Input_list_5.close();
Input_list_6.close();
Input_list_7.close();
Input_list_8.close();
Input_list_9.close();
Input_list_10.close();

}
