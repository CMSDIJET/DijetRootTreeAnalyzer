#include <TFile.h>
#include <TH1.h>
#include <TKey.h>
#include <TClass.h>
#include <TIterator.h>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iostream>

std::string formatLabel(const std::string& histName) {
    std::smatch match;
    std::regex pattern("SignalShape_AlphaTrue([0-9p]+)_W-([0-9p]+)_S([0-9]+)");

    if (std::regex_match(histName, match, pattern)) {
        std::string alpha_str = match[1];
        std::string width_str = match[2];
        std::string mass_str = match[3];

        // Convert strings
        std::string alpha = alpha_str;
        std::string width_percent = width_str;
        std::string mass_TeV = std::to_string(std::stoi(mass_str) / 1000);

        // Replace 'p' with '.' in alpha and width
        std::replace(alpha.begin(), alpha.end(), 'p', '.');
        std::replace(width_percent.begin(), width_percent.end(), 'p', '.');

        double width_frac = std::stod(width_percent);
        int width_pct = static_cast<int>(width_frac * 100 + 0.5);

        return "Normalized yield/TeV for $M_{\\mathrm{S}}$ = " + mass_TeV + " TeV, $\\alpha_{\\mathrm{true}}$ = " + alpha + " and $\\Gamma/M_{\\mathrm{S}}$ = " + std::to_string(width_pct) + "\\%";
    }

    // Fallback label
    return "Normalized yield/TeV";
}

void Create_YAML_SignalShapes(const char* rootFile = "inputs/SignalShapes.root", const char* outFile = "outputs/Figure_003_SignalShapes.yaml") {
    TFile* f = TFile::Open(rootFile);
    if (!f || f->IsZombie()) {
        std::cerr << "Cannot open file: " << rootFile << std::endl;
        return;
    }

    std::map<std::string, std::vector<double>> y_map;
    std::vector<double> x_low, x_high;

    TIter next(f->GetListOfKeys());
    TKey* key;
    bool filled_x = false;

    while ((key = (TKey*)next())) {

        TH1* h = (TH1*)key->ReadObj();
        std::string name = h->GetName();
        int nbins = h->GetNbinsX();

        std::vector<double> y_vals;
        for (int i = 1; i <= nbins; ++i) {
            if (!filled_x) {
                x_low.push_back(h->GetBinLowEdge(i));
                x_high.push_back(h->GetBinLowEdge(i + 1));
            }
            y_vals.push_back(h->GetBinContent(i));
        }
        filled_x = true;
        y_map[name] = y_vals;
    }

    std::ofstream out(outFile);
    if (!out.is_open()) {
        std::cerr << "Cannot write to file: " << outFile << std::endl;
        return;
    }

    // Write independent variable (common X axis)
    out << "independent_variables:\n";
    out << "- header:\n";
    out << "    name: Four-jet mass\n";
    out << "    units: TeV\n";
    out << "  values:\n";
    for (size_t i = 0; i < x_low.size(); ++i) {
        out << "  - low: " << x_low[i]/1000. << "\n";
        out << "    high: " << x_high[i]/1000. << "\n";
    }

    // Write dependent variables
    out << "dependent_variables:\n";
    for (const auto& [histName, yvals] : y_map) {
        out << "- header:\n";
        out << "    name: " << formatLabel(histName) << "\n";
        out << "  values:\n";
        for (double val : yvals) {
            out << "  - value: " << val << "\n";
        }
    }

    out.close();
}

