#include <TH2D.h>
#include <TFile.h>
#include <iostream>
#include <fstream>
#include <iomanip>

void Create_YAML_M4JvsM2J_QCDMC()
{

    TFile *f = new TFile("inputs/M4JvsM2J_QCDMC.root", "READ");
    TH2D* h = (TH2D*)f->Get("h_M4J_vs_M2J");
    
    char yamlFileName[1024];
    sprintf(yamlFileName, "outputs/Figure_002-c_M4JvsM2J_QCDMC.yaml");

    std::ofstream fout(yamlFileName);


    // Apply bounds
    const double xMin = 1.607, xMax = 10.072;
    const double yMax = 2.546;

    // Pre-select valid bin indices
    std::vector<std::pair<int, int>> validBins;

    for (int ix = 1; ix <= h->GetNbinsX(); ++ix) {
        double xcenter = h->GetXaxis()->GetBinCenter(ix);
        if (xcenter <= xMin || xcenter >= xMax) continue;

        for (int iy = 1; iy <= h->GetNbinsY(); ++iy) {
            double ycenter = h->GetYaxis()->GetBinCenter(iy);
            if (ycenter >= yMax) continue;

            validBins.emplace_back(ix, iy);
        }
    }

    // Write dependent variable
    fout << "dependent_variables:\n";
    fout << "  - header: {name: Events/bin, units: events}\n";
    fout << "    values:\n";
    for (const auto& bin : validBins) {
        double val = h->GetBinContent(bin.first, bin.second);
        fout << "      - value: " << std::fixed << std::setprecision(8) << val << "\n";
    }

    // Write independent variables
    fout << "independent_variables:\n";

    // X axis
    fout << "  - header: {name: Four-jet mass, units: TeV}\n";
    fout << "    values:\n";
    for (const auto& bin : validBins) {
        int ix = bin.first;
        double low = h->GetXaxis()->GetBinLowEdge(ix);
        double high = h->GetXaxis()->GetBinLowEdge(ix+1);
        fout << std::fixed << std::setprecision(3) << "      - {low: " << low << ", high: " << high << "}\n";
    }

    // Y axis
    fout << "  - header: {name: Average dijet mass, units: TeV}\n";
    fout << "    values:\n";
    for (const auto& bin : validBins) {
        int iy = bin.second;
        double low = h->GetYaxis()->GetBinLowEdge(iy);
        double high = h->GetYaxis()->GetBinLowEdge(iy+1);
        fout << std::fixed << std::setprecision(3) << "      - {low: " << low << ", high: " << high << "}\n";
    }

    fout.close();
}

