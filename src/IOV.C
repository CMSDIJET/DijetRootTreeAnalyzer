#include "IOV.h"

namespace jec{

void IOV::add(string id, int runmin, int runmax, bool isdata) {

    // sanity checks to avoid IOV overlaps
    assert(runmax>=runmin);
    assert(jecs.find(runmin)==jecs.end());
    for (IOVmap::const_iterator it = jecs.begin(); it != jecs.end(); ++it) {
      if (it->first < runmin) assert(it->second.first < runmin);
      if (it->first > runmin) assert(it->first > runmax);
    }
    
    char *s;
    const char *dir = "data/Fall17_17Nov2017_V6_DATA/";
    const char *tag = "Fall17_17Nov2017";
    const char *dtype = "_V6_DATA";
    /* const char *dir = "data/Summer16_23Sep2016V3_DATA/";
    const char *tag = "Summer16_23Sep2016";
    const char *dtype = "V3_DATA";*/
    const char *a = _algo.c_str();

    sprintf(s,"%s%s%s%s_L1FastJet_%s.txt",dir,tag,id.c_str(),dtype,a); cout<<s<<endl<<flush;
    JetCorrectorParameters *par_l1 = new JetCorrectorParameters(s);
    sprintf(s,"%s%s%s%s_L2Relative_%s.txt",dir,tag,id.c_str(),dtype,a); cout<<s<<endl<<flush;
    JetCorrectorParameters *par_l2 = new JetCorrectorParameters(s);
    sprintf(s,"%s%s%s%s_L3Absolute_%s.txt",dir,tag,id.c_str(),dtype,a); cout<<s<<endl<<flush;
    JetCorrectorParameters *par_l3 = new JetCorrectorParameters(s);
    sprintf(s,"%s%s%s%s_L2L3Residual_%s.txt",dir,tag,id.c_str(),dtype,a); cout<<s<<endl<<flush;
    JetCorrectorParameters *par_l2l3res = new JetCorrectorParameters(s);
    vector<JetCorrectorParameters> vpar;
    vpar.push_back(*par_l1);
    vpar.push_back(*par_l2);
    vpar.push_back(*par_l3);
    if (isdata) vpar.push_back(*par_l2l3res);
    FactorizedJetCorrector *jec = new FactorizedJetCorrector(vpar);
    
    jecs[runmin] = pair<int, FactorizedJetCorrector*>(runmax, jec);
  } // add
  
  FactorizedJetCorrector *IOV::get(int run) {
    assert(jecs.size()!=0);
    for (IOVmap::const_iterator it = jecs.begin(); it != jecs.end(); ++it) {
      if (it->first <= run && run <= it->second.first)
        return it->second.second;
    }
    cout << "Fatal error: IOV for run " << run << " not found!!" << endl << flush;
    assert(false);
    return 0;
  } // get

} //namespace jec
