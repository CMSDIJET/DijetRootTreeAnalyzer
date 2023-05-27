void create_input_forStabilityPlots(Int_t doJSON)
{

  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1);
 
  TH2F *METovSUMET_vsRun2[5][2],METovSUMET_vsNvtx2[5][2];
  TH2F *Mass_vsRun[5][2], *METovSUMET_vsRun[5][2], *CosThetaStar_vsRun[5][2], *DeltaPhi_vsRun[5][2], *DeltaEta_vsRun[5][2];
  TH2F *PtcorJet1_vsRun[5][2], *PhiJet1_vsRun[5][2], *EtaJet1_vsRun[5][2], *CHFJet1_vsRun[5][2], *NHFJet1_vsRun[5][2], *CEMFJet1_vsRun[5][2], *NEMFJet1_vsRun[5][2]; 
  //TH2F *PtcorJet2_vsRun[5][2], *PhiJet2_vsRun[5][2], *EtaJet2_vsRun[5][2], *CHFJet2_vsRun[5][2], *NHFJet2_vsRun[5][2], *CEMFJet2_vsRun[5][2], *NEMFJet2_vsRun[5][2]; 
  TH1F *Run[5][2];

  TH2F *Mass_vsNvtx[5][2], *METovSUMET_vsNvtx[5][2], *CosThetaStar_vsNvtx[5][2], *DeltaPhi_vsNvtx[5][2], *DeltaEta_vsNvtx[5][2];
  TH2F *PtcorJet1_vsNvtx[5][2], *PhiJet1_vsNvtx[5][2], *EtaJet1_vsNvtx[5][2], *CHFJet1_vsNvtx[5][2], *NHFJet1_vsNvtx[5][2], *CEMFJet1_vsNvtx[5][2], *NEMFJet1_vsNvtx[5][2]; 
  //TH2F *PtcorJet2_vsNvtx[5][2], *PhiJet2_vsNvtx[5][2], *EtaJet2_vsNvtx[5][2], *CHFJet2_vsNvtx[5][2], *NHFJet2_vsNvtx[5][2], *CEMFJet2_vsNvtx[5][2], *NEMFJet2_vsNvtx[5][2]; 
  TH2F *JetJec_vsPt_Jet1[5][2], *PFPt_CaloPt_vsPt_Jet1[5][2]; 
  TH2F *JetJec_vsPt_Jet2[5][2], *PFPt_CaloPt_vsPt_Jet2[5][2]; 
  char name[100]; 

  ////////We will have the triggers ????800 and PFHT650_WideJetMjj900 
  for(int itr=0; itr<1; itr++){ //trigger loop

    for(Int_t h=0; h<5;h++){ //for the 5 eta bins

  int run_start = 256620;
  int run_end   = 258160;

  int nbins     = run_end-run_start;

      sprintf(name,"Run_Ybin%i_hlt%i",h,itr);
      Run[h][itr] = new TH1F (name,"",nbins, run_start, run_end);
      Run[h][itr]->Sumw2();
      sprintf(name,"Mass_vsRun_Ybin%i_hlt%i",h,itr);
      Mass_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 800,0,8000);
      Mass_vsRun[h][itr]->Sumw2();

      sprintf(name,"METovSUMET_vsRun_Ybin%i_hlt%i",h,itr);
      METovSUMET_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end,100,0,1);
      METovSUMET_vsRun[h][itr]->Sumw2();

      sprintf(name,"METovSUMET_vsRun2_Ybin%i_hlt%i",h,itr);
      METovSUMET_vsRun2[h][itr] = new TH2F (name,"",nbins, run_start, run_end,100,0,10);
      METovSUMET_vsRun2[h][itr]->Sumw2();

      sprintf(name,"CosThetaStar_vsRun_Ybin%i_hlt%i",h,itr);
      CosThetaStar_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end,40,-2,2);
      CosThetaStar_vsRun[h][itr]->Sumw2();

      sprintf(name,"DeltaPhi_vsRun_Ybin%i_hlt%i",h,itr);
      DeltaPhi_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end,60,0,6);
      DeltaPhi_vsRun[h][itr]->Sumw2();
      sprintf(name,"DeltaEta_vsRun_Ybin%i_hlt%i",h,itr);
      DeltaEta_vsRun[h][itr] = new TH2F (name,"",50, 0, 50,60,0,6);
      DeltaEta_vsRun[h][itr]->Sumw2();

      sprintf(name,"PtcorJet1_vsRun_Ybin%i_hlt%i",h,itr);
      PtcorJet1_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end,100,0,3000);
      PtcorJet1_vsRun[h][itr]->Sumw2();
      sprintf(name,"PhiJet1_vsRun_Ybin%i_hlt%i",h,itr);
      PhiJet1_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end,60,-3, 3);
      PhiJet1_vsRun[h][itr]->Sumw2();
      sprintf(name,"EtaJet1_vsRun_Ybin%i_hlt%i",h,itr);
      EtaJet1_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 5,-2.5,2.5);
      EtaJet1_vsRun[h][itr]->Sumw2();
      sprintf(name,"CHFJet1_vsRun_Ybin%i_hlt%i",h,itr);
      CHFJet1_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 100, 0, 1);
      CHFJet1_vsRun[h][itr]->Sumw2();
      sprintf(name,"NHFJet1_vsRun_Ybin%i_hlt%i",h,itr);
      NHFJet1_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 100, 0, 1);
      NHFJet1_vsRun[h][itr]->Sumw2();
      sprintf(name,"CEMFJet1_vsRun_Ybin%i_hlt%i",h,itr);
      CEMFJet1_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 100, 0, 1);
      CEMFJet1_vsRun[h][itr]->Sumw2();
      sprintf(name,"NEMFJet1_vsRun_Ybin%i_hlt%i",h,itr);
      NEMFJet1_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 100, 0, 1);
      NEMFJet1_vsRun[h][itr]->Sumw2();
/*
      sprintf(name,"PtcorJet2_vsRun_Ybin%i_hlt%i",h,itr);
      PtcorJet2_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end,100,0,3000);
      PtcorJet2_vsRun[h][itr]->Sumw2();
      sprintf(name,"PhiJet2_vsRun_Ybin%i_hlt%i",h,itr);
      PhiJet2_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end,60,-3, 3);
      PhiJet2_vsRun[h][itr]->Sumw2();
      sprintf(name,"EtaJet2_vsRun_Ybin%i_hlt%i",h,itr);
      EtaJet2_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end,5,-2.5,2.5);
      EtaJet2_vsRun[h][itr]->Sumw2();
      sprintf(name,"CHFJet2_vsRun_Ybin%i_hlt%i",h,itr);
      CHFJet2_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 100, 0, 1);
      CHFJet2_vsRun[h][itr]->Sumw2();
      sprintf(name,"NHFJet2_vsRun_Ybin%i_hlt%i",h,itr);
      NHFJet2_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 100, 0, 1);
      NHFJet2_vsRun[h][itr]->Sumw2();
      sprintf(name,"CEMFJet2_vsRun_Ybin%i_hlt%i",h,itr);
      CEMFJet2_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 100, 0, 1);
      CEMFJet2_vsRun[h][itr]->Sumw2();
      sprintf(name,"NEMFJet2_vsRun_Ybin%i_hlt%i",h,itr);
      NEMFJet2_vsRun[h][itr] = new TH2F (name,"",nbins, run_start, run_end, 100, 0, 1);
      NEMFJet2_vsRun[h][itr]->Sumw2();
*/

    
      sprintf(name,"Mass_vsNvtx_Ybin%i_hlt%i",h,itr);
      Mass_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 800,0,8000);
      Mass_vsNvtx[h][itr]->Sumw2();

      sprintf(name,"METovSUMET_vsNvtx_Ybin%i_hlt%i",h,itr);
      METovSUMET_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50,100,0,1);
      METovSUMET_vsNvtx[h][itr]->Sumw2();

      sprintf(name,"METovSUMET_vsNvtx2_Ybin%i_hlt%i",h,itr);
      METovSUMET_vsNvtx2[h][itr] = new TH2F (name,"",50, 0, 50,100,0,10);
      METovSUMET_vsNvtx2[h][itr]->Sumw2();

      sprintf(name,"CosThetaStar_vsNvtx_Ybin%i_hlt%i",h,itr);
      CosThetaStar_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50,40,-2,2);
      CosThetaStar_vsNvtx[h][itr]->Sumw2();

      sprintf(name,"DeltaPhi_vsNvtx_Ybin%i_hlt%i",h,itr);
      DeltaPhi_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50,60,0,6);
      DeltaPhi_vsNvtx[h][itr]->Sumw2();

      sprintf(name,"DeltaEta_vsNvtx_Ybin%i_hlt%i",h,itr);
      DeltaEta_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50,60,0,6);
      DeltaEta_vsNvtx[h][itr]->Sumw2(); 

      sprintf(name,"PtcorJet1_vsNvtx_Ybin%i_hlt%i",h,itr);
      PtcorJet1_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50,100,0,3000);
      PtcorJet1_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"PhiJet1_vsNvtx_Ybin%i_hlt%i",h,itr);
      PhiJet1_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50,60,-3, 3);
      PhiJet1_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"EtaJet1_vsNvtx_Ybin%i_hlt%i",h,itr);
      EtaJet1_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 5,-2.5,2.5);
      EtaJet1_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"CHFJet1_vsNvtx_Ybin%i_hlt%i",h,itr);
      CHFJet1_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 100, 0, 1);
      CHFJet1_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"NHFJet1_vsNvtx_Ybin%i_hlt%i",h,itr);
      NHFJet1_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 100, 0, 1);
      NHFJet1_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"CEMFJet1_vsNvtx_Ybin%i_hlt%i",h,itr);
      CEMFJet1_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 100, 0, 1);
      CEMFJet1_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"NEMFJet1_vsNvtx_Ybin%i_hlt%i",h,itr);
      NEMFJet1_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 100, 0, 1);
      NEMFJet1_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"JetJec_vsPt_Jet1_Ybin%i_hlt%i",h,itr);
      JetJec_vsPt_Jet1[h][itr] = new TH2F (name,"", 100,0,3000, 100, 1.0, 1.5);
      JetJec_vsPt_Jet1[h][itr]->Sumw2();
      sprintf(name,"PFPt_CaloPt_vsPt_Jet1_Ybin%i_hlt%i",h,itr);
      PFPt_CaloPt_vsPt_Jet1[h][itr] = new TH2F (name,"", 100,0,3000, 100, 0, 1);
      PFPt_CaloPt_vsPt_Jet1[h][itr]->Sumw2();
/*
      sprintf(name,"PtcorJet2_vsNvtx_Ybin%i_hlt%i",h,itr);
      PtcorJet2_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50,100,0,3000);
      PtcorJet2_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"PhiJet2_vsNvtx_Ybin%i_hlt%i",h,itr);
      PhiJet2_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50,60,-3, 3);
      PhiJet2_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"EtaJet2_vsNvtx_Ybin%i_hlt%i",h,itr);
      EtaJet2_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50,5,-2.5,2.5);
      EtaJet2_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"CHFJet2_vsNvtx_Ybin%i_hlt%i",h,itr);
      CHFJet2_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 100, 0, 1);
      CHFJet2_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"NHFJet2_vsNvtx_Ybin%i_hlt%i",h,itr);
      NHFJet2_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 100, 0, 1);
      NHFJet2_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"CEMFJet2_vsNvtx_Ybin%i_hlt%i",h,itr);
      CEMFJet2_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 100, 0, 1);
      CEMFJet2_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"NEMFJet2_vsNvtx_Ybin%i_hlt%i",h,itr);
      NEMFJet2_vsNvtx[h][itr] = new TH2F (name,"",50, 0, 50, 100, 0, 1);
      NEMFJet2_vsNvtx[h][itr]->Sumw2();
      sprintf(name,"JetJec_vsPt_Jet2_Ybin%i_hlt%i",h,itr);
      JetJec_vsPt_Jet2[h][itr] = new TH2F (name,"", 100,0,3000, 100, 1.0, 1.5);
      JetJec_vsPt_Jet2[h][itr]->Sumw2();
      sprintf(name,"PFPt_CaloPt_vsPt_Jet2_Ybin%i_hlt%i",h,itr);
      PFPt_CaloPt_vsPt_Jet2[h][itr] = new TH2F (name,"", 100,0,3000, 100, 0, 1);
      PFPt_CaloPt_vsPt_Jet2[h][itr]->Sumw2();
*/
    } //end of eta bins loop 
  }// end of trigger loop

   /////////initialize variables

   double run, nvtx, metSig, mjj, deltaETAjj, deltaPHIjj,MET;  
   double chf_j1, nhf_j1, cemf_j1, nemf_j1, muf_j1, cm_j1, nm_j1, pTWJ_j1, etaWJ_j1, phiWJ_j1, jetJecAK4_j1, jetPtAK4matchCaloJet_j1, pTAK4_j1;
   double chf_j2, nhf_j2, cemf_j2, nemf_j2, muf_j2, cm_j2, nm_j2, pTWJ_j2, etaWJ_j2, phiWJ_j2, jetJecAK4_j2, jetPtAK4matchCaloJet_j2, pTAK4_j2;
   double ymax;
   double yBnd[]={0.0,0.5,1.0,1.5,2.0,2.5};
     float deta_cut=1.3;
     float mjj_cut=1181; 
     float mjj_cuth=14000;

//  TFile *f = TFile::Open("/tmp/nsaoulid/2015c_25ns_jecv4_reduced_skim.root","READ");
//  TFile *f = TFile::Open("/tmp/nsaoulid/2015C_25ns_16pb_JEC25nsV2_reduced_skim.root","READ");
//    TFile *f = TFile::Open("/tmp/nsaoulid/Run2015D_DCSOnly_20150923_25nsV3_reduced_skim.root","READ");	
//    TFile *f = TFile::Open("/tmp/nsaoulid/rootfile_JetHT__Run2015D-PromptReco-v3__MINIAOD_Run2015D_DCSonly_390pb-1_JEC_Summer15_25nsV3_20151001_165849_reduced_skim.root","READ");
    TFile *f = TFile::Open("/tmp/nsaoulid/rootfile_JetHT__Run2015D_DCS.root","READ");
   
   double PassJSON;

  TDirectoryFile *Multijets=(TDirectoryFile*) f->Get("rootTupleTree");
  f->cd("rootTupleTree"); 

  tree->SetBranchAddress("run",&run);
  tree->SetBranchAddress("nVtx",&nvtx);
  tree->SetBranchAddress("metSig",&metSig);
  tree->SetBranchAddress("MET",&MET);
  tree->SetBranchAddress("mjj",&mjj);
  tree->SetBranchAddress("deltaPHIjj",&deltaPHIjj);
  tree->SetBranchAddress("deltaETAjj",&deltaETAjj);

  tree->SetBranchAddress("chargedHadEnFrac_j1",&chf_j1);
  tree->SetBranchAddress("neutrHadEnFrac_j1",&nhf_j1);
  tree->SetBranchAddress("eleEnFract_j1",&cemf_j1);
  tree->SetBranchAddress("neutrElectromFrac_j1",&nemf_j1);
  tree->SetBranchAddress("pTWJ_j1",&pTWJ_j1);
  tree->SetBranchAddress("etaWJ_j1",&etaWJ_j1);
  tree->SetBranchAddress("phiWJ_j1",&phiWJ_j1);
  tree->SetBranchAddress("jetJecAK4_j1",&jetJecAK4_j1);
  tree->SetBranchAddress("jetPtAK4matchCaloJet_j1",&jetPtAK4matchCaloJet_j1);
  tree->SetBranchAddress("pTAK4_j1",&pTAK4_j1);

  tree->SetBranchAddress("chargedHadEnFrac_j2",&chf_j2);
  tree->SetBranchAddress("neutrHadEnFrac_j2",&nhf_j2);
  tree->SetBranchAddress("eleEnFract_j2",&cemf_j2);
  tree->SetBranchAddress("neutrElectromFrac_j2",&nemf_j2);
  tree->SetBranchAddress("pTWJ_j2",&pTWJ_j2);
  tree->SetBranchAddress("etaWJ_j2",&etaWJ_j2);
  tree->SetBranchAddress("phiWJ_j2",&phiWJ_j2);
  tree->SetBranchAddress("jetJecAK4_j2",&jetJecAK4_j2);
  tree->SetBranchAddress("jetPtAK4matchCaloJet_j2",&jetPtAK4matchCaloJet_j2);
  tree->SetBranchAddress("pTAK4_j2",&pTAK4_j2);
  tree->SetBranchAddress("PassJSON",&PassJSON);

  Int_t nentries=(Int_t)tree->GetEntries(); 
  cout<<"Number of entries =  "<<nentries<<endl;

  for (int i=0; i<nentries; i++){    //event loop
    tree->GetEntry(i);
    for(int itr=0; itr<1; itr++){
      
      if(TMath::Abs(deltaETAjj) > deta_cut &&  TMath::Abs(deltaETAjj) <2.6 && mjj > mjj_cut && mjj< mjj_cuth && ( (doJSON==0) || (doJSON==1 &&PassJSON==1) ) ){

        int ybin = getBin(fabs(etaWJ_j1),yBnd);
        if (ybin > -1){ //fill hist's in the corresponding eta bin

          Run[ybin][itr]->Fill(run);  
          Mass_vsRun[ybin][itr]->Fill(run, mjj); 
	  METovSUMET_vsRun[ybin][itr]->Fill(run, metSig);
          METovSUMET_vsRun2[ybin][itr]->Fill(run, MET/(sqrt(MET*1./metSig)));
          CosThetaStar_vsRun[ybin][itr]->Fill(run, TMath::TanH((etaWJ_j1-etaWJ_j2)/2));
	  DeltaPhi_vsRun[ybin][itr]->Fill(run, deltaPHIjj);
	  DeltaEta_vsRun[ybin][itr]->Fill(run, TMath::Abs(deltaETAjj));

	  PtcorJet1_vsRun[ybin][itr]->Fill(run, pTWJ_j1);
          PhiJet1_vsRun[ybin][itr]->Fill(run, phiWJ_j1);
          EtaJet1_vsRun[ybin][itr]->Fill(run, etaWJ_j1);
          CHFJet1_vsRun[ybin][itr]->Fill(run, chf_j1);
          NHFJet1_vsRun[ybin][itr]->Fill(run, nhf_j1);
	  CEMFJet1_vsRun[ybin][itr]->Fill(run, cemf_j1);
          NEMFJet1_vsRun[ybin][itr]->Fill(run, nemf_j1); 
/*
          PtcorJet2_vsRun[ybin][itr]->Fill(run, pTWJ_j2);
          PhiJet2_vsRun[ybin][itr]->Fill(run, phiWJ_j2);
          EtaJet2_vsRun[ybin][itr]->Fill(run, etaWJ_j2);
          CHFJet2_vsRun[ybin][itr]->Fill(run, chf_j2);
          NHFJet2_vsRun[ybin][itr]->Fill(run, nhf_j2);
	  CEMFJet2_vsRun[ybin][itr]->Fill(run, cemf_j2);
          NEMFJet2_vsRun[ybin][itr]->Fill(run, nemf_j2); 
*/
	  Mass_vsNvtx[ybin][itr]->Fill(nvtx, mjj); 
	  METovSUMET_vsNvtx[ybin][itr]->Fill(nvtx, metSig);
          METovSUMET_vsNvtx2[ybin][itr]->Fill(nvtx, MET/(sqrt(MET*1./metSig)));
          CosThetaStar_vsNvtx[ybin][itr]->Fill(nvtx, TMath::TanH((etaWJ_j1-etaWJ_j2)/2));
	  DeltaPhi_vsNvtx[ybin][itr]->Fill(nvtx, TMath::Abs(deltaPHIjj));
	  DeltaEta_vsNvtx[ybin][itr]->Fill(nvtx, deltaETAjj);

	  PtcorJet1_vsNvtx[ybin][itr]->Fill(nvtx, pTWJ_j1);
          PhiJet1_vsNvtx[ybin][itr]->Fill(nvtx, phiWJ_j1);
          EtaJet1_vsNvtx[ybin][itr]->Fill(nvtx, etaWJ_j1);
          CHFJet1_vsNvtx[ybin][itr]->Fill(nvtx, chf_j1);
          NHFJet1_vsNvtx[ybin][itr]->Fill(nvtx, nhf_j1);
	  CEMFJet1_vsNvtx[ybin][itr]->Fill(nvtx, cemf_j1);
          NEMFJet1_vsNvtx[ybin][itr]->Fill(nvtx, nemf_j1); 
          JetJec_vsPt_Jet1[ybin][itr]->Fill(pTAK4_j1, jetJecAK4_j1);
          PFPt_CaloPt_vsPt_Jet1[ybin][itr]->Fill(pTAK4_j1, (pTAK4_j1-jetPtAK4matchCaloJet_j1)/pTAK4_j1);
/*
          PtcorJet2_vsNvtx[ybin][itr]->Fill(nvtx, pTWJ_j2);
          PhiJet2_vsNvtx[ybin][itr]->Fill(nvtx, phiWJ_j2);
          EtaJet2_vsNvtx[ybin][itr]->Fill(nvtx, etaWJ_j2);
          CHFJet2_vsNvtx[ybin][itr]->Fill(nvtx, chf_j2);
          NHFJet2_vsNvtx[ybin][itr]->Fill(nvtx, nhf_j2);
	  CEMFJet2_vsNvtx[ybin][itr]->Fill(nvtx, cemf_j2);
          NEMFJet2_vsNvtx[ybin][itr]->Fill(nvtx, nemf_j2); 
          JetJec_vsPt_Jet2[ybin][itr]->Fill(pTAK4_j2, jetJecAK4_j2);
          PFPt_CaloPt_vsPt_Jet2[ybin][itr]->Fill(pTAK4_j2, (pTAK4_j2-jetPtAK4matchCaloJet_j2)/pTAK4_j2);
*/
        } //end of if ybin 
      }//end of Deta and mjj cut
    } //end of trigger loop
  }//end of event loop 

  TFile *output;
  if(doJSON==0) output =  new TFile("Run2015B_lumi40_sum_17Jul_and25Jul_final_tight_stability.root","RECREATE");
  if(doJSON==1) output =  new TFile("Run2015B_lumi40_sum_17Jul_and25Jul_final_tight_stability_cert.root","RECREATE");

  for(int itr=0; itr<1; itr++){
    for(int h=0; h<5; h++){ 
   
      Run[h][itr]->Write();   
      Mass_vsRun[h][itr]->Write();
      METovSUMET_vsRun[h][itr]->Write();
      METovSUMET_vsRun2[h][itr]->Write();
      CosThetaStar_vsRun[h][itr]->Write();
      DeltaPhi_vsRun[h][itr]->Write();
      PtcorJet1_vsRun[h][itr]->Write();
      PhiJet1_vsRun[h][itr]->Write();
      EtaJet1_vsRun[h][itr]->Write();
      CHFJet1_vsRun[h][itr]->Write();
      NHFJet1_vsRun[h][itr]->Write();
      CEMFJet1_vsRun[h][itr]->Write();
      NEMFJet1_vsRun[h][itr]->Write();
/*
      PtcorJet2_vsRun[h][itr]->Write();
      PhiJet2_vsRun[h][itr]->Write();
      EtaJet2_vsRun[h][itr]->Write();
      CHFJet2_vsRun[h][itr]->Write();
      NHFJet2_vsRun[h][itr]->Write();
      CEMFJet2_vsRun[h][itr]->Write();
      NEMFJet2_vsRun[h][itr]->Write();
*/
      Mass_vsNvtx[h][itr]->Write();
      METovSUMET_vsNvtx[h][itr]->Write();
      METovSUMET_vsNvtx2[h][itr]->Write();
      CosThetaStar_vsNvtx[h][itr]->Write();
      DeltaPhi_vsNvtx[h][itr]->Write();
      PtcorJet1_vsNvtx[h][itr]->Write();
      PhiJet1_vsNvtx[h][itr]->Write();
      EtaJet1_vsNvtx[h][itr]->Write();
      CHFJet1_vsNvtx[h][itr]->Write();
      NHFJet1_vsNvtx[h][itr]->Write();
      CEMFJet1_vsNvtx[h][itr]->Write();
      NEMFJet1_vsNvtx[h][itr]->Write();
      JetJec_vsPt_Jet1[h][itr]->Write();
      PFPt_CaloPt_vsPt_Jet1[h][itr]->Write();
/*
      PtcorJet2_vsNvtx[h][itr]->Write();
      PhiJet2_vsNvtx[h][itr]->Write();
      EtaJet2_vsNvtx[h][itr]->Write();
      CHFJet2_vsNvtx[h][itr]->Write();
      NHFJet2_vsNvtx[h][itr]->Write();
      CEMFJet2_vsNvtx[h][itr]->Write();
      NEMFJet2_vsNvtx[h][itr]->Write();
      JetJec_vsPt_Jet2[h][itr]->Write();
      PFPt_CaloPt_vsPt_Jet2[h][itr]->Write();
*/
      }
    }

  output->Close();

}

int getBin(double x, double boundaries[]) 
{
  int i;
  int n = 5; //sizeof(boundaries)/sizeof(boundaries[0])-1;  
  if (x<boundaries[0] || x>=boundaries[n])
    return -1;
  for(i=0;i<n;i++)
   {
     if (x>=boundaries[i] && x<boundaries[i+1])
       return i;
   }
  return 0;
}

