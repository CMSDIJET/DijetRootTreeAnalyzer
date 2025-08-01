#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void extract_cross_section(double width, double alpha_true, double S) {

char width_name[1024];
if (width==0.0043) sprintf(width_name,"0p0043");
if (width==0.015) sprintf(width_name,"0p015");
if (width==0.05) sprintf(width_name,"0p05");
if (width==0.1) sprintf(width_name,"0p1");

char fname[1024];
//sprintf(fname, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/gridpacks/Suu_Diquark/Wide_Resonances_13TeV/full_grid/log/Suu_Diquark_13TeV_W-%s_S%.0f_chi%.0f.log", width_name, S, alpha_true*S);
sprintf(fname, "/eos/cms/store/group/phys_exotica/dijet/Dijet13TeV/ilias/gridpacks/Sdd_Diquark/13TeV/log/Sdd_Diquark_13TeV_W-%s_S%.0f_omega%.0f.log", width_name, S, alpha_true*S);

ifstream file(fname);

string line;
bool found = false; // Flag to check if the block is found

while (getline(file, line))
{
    // Look for the specific block identifier
    if (line.find("=== Results Summary for run: pilotrun tag: tag_1 ===") != string::npos)
    {
        found = true; // Mark that the block has been found
        break;
    }
}

if (found)
{
    // Read lines until the cross-section value is found
    while (getline(file, line))
    {
        if (line.find("Cross-section") != string::npos)
        {
            double cross_section;
            size_t pos = line.find(":");
            if (pos != string::npos)
            {
                string value_part = line.substr(pos + 1);
                istringstream iss(value_part);
                if (iss >> cross_section)
                {
                    cout << "Extracted Cross-section: " << cross_section << " pb" << endl;
                }
                else
                {
                    cerr << "Error: Could not parse cross-section value." << endl;
                }
            }
            break;
        }
    }
}
else
{
    cerr << "Error: Specified block not found in the log file." << endl;
}

file.close();



}
