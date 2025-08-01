#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void correct_Sdd_with_parton_level_acc_and_create_new_txt(double width, double alpha_true){
    
char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char alpha_true_name[1024];
if (alpha_true==0.11) sprintf(alpha_true_name,"0p11");
if (alpha_true==0.13) sprintf(alpha_true_name,"0p13");
if (alpha_true==0.15) sprintf(alpha_true_name,"0p15");
if (alpha_true==0.17) sprintf(alpha_true_name,"0p17");
if (alpha_true==0.19) sprintf(alpha_true_name,"0p19");
if (alpha_true==0.21) sprintf(alpha_true_name,"0p21");
if (alpha_true==0.23) sprintf(alpha_true_name,"0p23");
if (alpha_true==0.25) sprintf(alpha_true_name,"0p25");
if (alpha_true==0.27) sprintf(alpha_true_name,"0p27");
if (alpha_true==0.29) sprintf(alpha_true_name,"0p29");
if (alpha_true==0.31) sprintf(alpha_true_name,"0p31");
if (alpha_true==0.33) sprintf(alpha_true_name,"0p33");
if (alpha_true==0.42) sprintf(alpha_true_name,"0p42");    
  
char input_name[1024], output_name[1024];
sprintf(input_name, "../TheoryXSECs/DiquarkSdd_W-%s_%s.txt", width_name, alpha_true_name);
sprintf(output_name, "../TheoryXSECs/DiquarkSddCorrWithPartonLevelAcc_W-%s_%s.txt", width_name, alpha_true_name);  
    
std::ifstream infile(input_name);
std::ofstream outfile(output_name);

std::string line;
int line_count = 0;
    
while(std::getline(infile, line))
{
    line_count++;
        
    if(line_count == 1)
    { 
        outfile << line << std::endl;
    }    
        
    if(line_count == 2)
    {
        outfile << "Mass DiquarkSddCorrWithPartonLevelAcc" << std::endl;
    }
        
    if(line_count > 2) //2
    {     
        std::istringstream iss(line);
        double diquark_mass, value;
        if (iss >> diquark_mass >> value) 
        {
        
            char hnameSuu[1024], hnameSdd[1024];
            sprintf(hnameSuu, "/afs/cern.ch/work/i/izisopou/public/PlotFromLHEfilesV2/CMSSW_10_2_13/src/Suu_vs_Sdd_Studies/root_files_for_acceptance/HISTOS_Suu_Diquark_13TeV_W-%s_S%.0f_chi%.0f.root", width_name, diquark_mass, diquark_mass*alpha_true);
            sprintf(hnameSdd, "/afs/cern.ch/work/i/izisopou/public/PlotFromLHEfilesV2/CMSSW_10_2_13/src/Suu_vs_Sdd_Studies/root_files_for_acceptance/HISTOS_Sdd_Diquark_13TeV_W-%s_S%.0f_omega%.0f.root", width_name, diquark_mass, diquark_mass*alpha_true);
            
            TFile *fSuu = new TFile(hnameSuu, "READ");
            TFile *fSdd = new TFile(hnameSdd, "READ");
            
            TH1D *hSuu_before = (TH1D*)fSuu->Get("h_fourparton_mass");
            TH1D *hSuu_after = (TH1D*)fSuu->Get("h_fourparton_mass_withDeltaEtaDR");
            
            TH1D *hSdd_before = (TH1D*)fSdd->Get("h_fourparton_mass");
            TH1D *hSdd_after = (TH1D*)fSdd->Get("h_fourparton_mass_withDeltaEtaDR");
            
            double accSuu = double(hSuu_after->Integral())/hSuu_before->Integral();
            double accSdd = double(hSdd_after->Integral())/hSdd_before->Integral();
        
            double scale = double(accSdd)/accSuu;
            
            cout << "Mass = " << diquark_mass << " , scale = " << scale << endl;
        
            value *= scale;
            if (value >= 1e-4)
            {
                outfile << std::fixed << std::setprecision(1) << diquark_mass << "    " << std::fixed << std::setprecision(8) << value << std::endl;
            } 
            else
            {
                outfile << std::fixed << std::setprecision(1) << diquark_mass << "    " << std::scientific << std::setprecision(6) << value << std::endl;
            }
        }
    }
}    
    
infile.close();
outfile.close();
    
}

