#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>
#include "TRandom.h"

	analysisClass::analysisClass(string * inputList, string * cutFile, string * treeName, string * outputFileName, string * cutEfficFile)
  	:baseClass(inputList, cutFile, treeName, outputFileName, cutEfficFile)
 	 {
	  std::cout << "analysisClass::analysisClass(): begins " << std::endl;

	  // For JECs
		if( int(getPreCutValue1("useJECs"))==1 ) //it's not implemented
		 {
			std::string L1Path = "data/Spring16_25nsV2_MC/Spring16_25nsV2_MC_L1FastJet_AK4PFchs.txt";
			std::string L2Path = "data/Spring16_25nsV2_MC/Spring16_25nsV2_MC_L2Relative_AK4PFchs.txt"; 
			std::string L3Path = "data/Spring16_25nsV2_MC/Spring16_25nsV2_MC_L3Absolute_AK4PFchs.txt";
			std::string L1DATAPath = "data/Spring16_25nsV2_DATA/Spring16_25nsV2_DATA_L1FastJet_AK4PFchs.txt";
			std::string L2DATAPath = "data/Spring16_25nsV2_DATA/Spring16_25nsV2_DATA_L2Relative_AK4PFchs.txt"; 
			std::string L3DATAPath = "data/Spring16_25nsV2_DATA/Spring16_25nsV2_DATA_L3Absolute_AK4PFchs.txt";
			std::string L2L3ResidualPath = "data/Spring16_25nsV2_DATA/Spring16_25nsV2_DATA_L2Residual_AK4PFchs.txt";

			L1Par = new JetCorrectorParameters(L1Path);
			L2Par = new JetCorrectorParameters(L2Path);
			L3Par = new JetCorrectorParameters(L3Path);
			L1DATAPar = new JetCorrectorParameters(L1DATAPath);
			L2DATAPar = new JetCorrectorParameters(L2DATAPath);
			L3DATAPar = new JetCorrectorParameters(L3DATAPath);
			L2L3Residual = new JetCorrectorParameters(L2L3ResidualPath);

			std::vector<JetCorrectorParameters> vPar;
			std::vector<JetCorrectorParameters> vPar_data;
			vPar.push_back(*L1Par);
			vPar.push_back(*L2Par);
			vPar.push_back(*L3Par);
			   
				//residuals are applied only to data
			vPar_data.push_back(*L1DATAPar);
			vPar_data.push_back(*L2DATAPar);
			vPar_data.push_back(*L3DATAPar);
			vPar_data.push_back(*L2L3Residual);

			JetCorrector = new FactorizedJetCorrector(vPar); assert(JetCorrector);
			JetCorrector_data = new FactorizedJetCorrector(vPar_data); assert(JetCorrector_data);

				//uncertainty
			unc = new JetCorrectionUncertainty("data/Spring16_25nsV2_DATA/Spring16_25nsV2_DATA_Uncertainty_AK4PFchs.txt");
		 }
	  
	  std::cout << "analysisClass::analysisClass(): ends " << std::endl;
 	}

	analysisClass::~analysisClass()
	 {
		std::cout << "analysisClass::~analysisClass(): begins " << std::endl;
		std::cout << "analysisClass::~analysisClass(): ends " << std::endl;
	 }

void analysisClass::Loop()
 {
	std::cout << "analysisClass::Loop() begins" <<std::endl;      
	if (fChain == 0) return;
	   
	   //////////book histos here

	   /////////initialize variables

	Long64_t nentries = fChain->GetEntriesFast();
	std::cout << "analysisClass::Loop(): nentries = " << nentries << std::endl;   

	////// The following ~7 lines have been taken from rootNtupleClass->Loop() /////
	////// If the root version is updated and rootNtupleClass regenerated,     /////
	////// these lines may need to be updated.                                 /////    
	Long64_t nbytes = 0, nb = 0;


//	for (Long64_t jentry=0; jentry<nentries;jentry++)
	for (Long64_t jentry=0; jentry<500000; jentry++)
	 {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   
		nbytes += nb;
		if(jentry < 10 || jentry%1000000 == 0) std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
		// if (Cut(ientry) < 0) continue;
		////////////////////// User's code starts here ///////////////////////

		///Stuff to be done for every event
		size_t no_jets_AK8 = jetPtAK8->size();
		resetCuts(); 


		//== Fill Variables for AK8 ==
		if(no_jets_AK8 >=2)
		 {

			bool cut1 = (jetPtAK8->at(0) > getPreCutValue1("pt0Cut"));
			bool cut2 = (jetPtAK8->at(1) > getPreCutValue1("pt1Cut"));            
			if(cut1 && cut2)
			{

				if(passJSON (runNo, lumi, int(getPreCutValue1("IsData"))==1 )==1   ||  int(getPreCutValue1("IsData"))==0 )  //if it's golden data or MC
				{  

					if(dPhijjAK8 > getPreCutValue1("deltaPhijj")  )   //back-to-back
					{ 

					//	if (neMultAK8->at(0)>0)cout << neMultAK8->at(0) << endl;
						fillVariableWithValue("nJet", no_jets_AK8);
						fillVariableWithValue("met",met);
						fillVariableWithValue("metSig",metSig);
						fillVariableWithValue("passFilterGoodVtx",passFilterGoodVtx);
						fillVariableWithValue("passFilterHBHE",passFilterHBHE);
						fillVariableWithValue("passFilterHBHEIso",passFilterHBHEIso);
						fillVariableWithValue("passFilterglobalSuperTightHalo",passFilterglobalSuperTightHalo2016);
						fillVariableWithValue("passFilterECALDeadCell",passFilterECALDeadCell);
						fillVariableWithValue("passFilterEEBadSc",passFilterEEBadSc);
						fillVariableWithValue("passFilterBadChargedCandidate",passFilterBadChargedCandidate);
						fillVariableWithValue("passFilterBadPFMuon",passFilterBadPFMuon);
						fillVariableWithValue("run",runNo); 
						fillVariableWithValue("event",evtNo); 
						fillVariableWithValue("lumi",lumi); 
						fillVariableWithValue("nVtx",nvtx); 
						fillVariableWithValue("DijetMassAK4",mjjAK8);
						fillVariableWithValue( "deltaPhi", dPhijjAK8);
						fillVariableWithValue( "pT_j1", jetPtAK8->at(0));
						fillVariableWithValue( "eta_j1", jetEtaAK8->at(0));
						fillVariableWithValue( "phi_j1", jetPhiAK8->at(0));
						fillVariableWithValue( "neutrHadEnFrac_j1", jetNhfAK8->at(0));
						fillVariableWithValue( "chargedHadEnFrac_j1", jetChfAK8->at(0));
						fillVariableWithValue( "photonEnFrac_j1", jetPhfAK8->at(0));
						fillVariableWithValue( "eleEnFract_j1", jetElfAK8->at(0));
						fillVariableWithValue( "muEnFract_j1", jetMufAK8->at(0));
					 	fillVariableWithValue( "neutrElectromFrac_j1", jetNemfAK8->at(0));
					 	fillVariableWithValue( "chargedElectromFrac_j1", jetCemfAK8->at(0));
						fillVariableWithValue( "chargedMult_j1", chMultAK8->at(0));
					   	fillVariableWithValue( "neutrMult_j1", neMultAK8->at(0));
						fillVariableWithValue( "photonMult_j1", phoMultAK8->at(0));	
						fillVariableWithValue( "pT_j2", jetPtAK8->at(1));
						fillVariableWithValue( "eta_j2", jetEtaAK8->at(1));
						fillVariableWithValue( "phi_j2", jetPhiAK8->at(1));	
						fillVariableWithValue( "neutrHadEnFrac_j2", jetNhfAK8->at(1));
						fillVariableWithValue( "chargedHadEnFrac_j2", jetChfAK8->at(1));
						fillVariableWithValue( "photonEnFrac_j2", jetPhfAK8->at(1));
						fillVariableWithValue( "eleEnFract_j2", jetElfAK8->at(1));
						fillVariableWithValue( "muEnFract_j2", jetMufAK8->at(1));
					 	fillVariableWithValue( "neutrElectromFrac_j2", jetNemfAK8->at(1));
					 	fillVariableWithValue( "chargedElectromFrac_j2", jetCemfAK8->at(1));
						fillVariableWithValue( "chargedMult_j2", chMultAK8->at(1));
					   	fillVariableWithValue( "neutrMult_j2", neMultAK8->at(1));
					 	fillVariableWithValue( "photonMult_j2", phoMultAK8->at(1));

						fillVariableWithValue("passHLT", triggerResult->at(0));// HLT_PFHT780_v* 
						fillVariableWithValue("passHLT1",triggerResult->at(1));// HLT_PFHT890_v* 
						fillVariableWithValue("passHLT2",triggerResult->at(2));// HLT_PFHT1050_v* 
						fillVariableWithValue("passHLT3",triggerResult->at(3));// HLT_PFJet200_v*
						fillVariableWithValue("passHLT4",triggerResult->at(4));// HLT_PFJet455_v* 
						fillVariableWithValue("passHLT5",triggerResult->at(5));// HLT_PFJet500_v* 
						fillVariableWithValue("passHLT6",triggerResult->at(6));// HLT_PFJet550_v* 


					 
						bool JetID_j1_2016, JetID_j1_2017, JetID_j1_2018,  JetIDlepVeto_j1_2016, JetIDlepVeto_j1_2017, JetIDlepVeto_j1_2018;
						bool JetID_j2_2016, JetID_j2_2017, JetID_j2_2018,  JetIDlepVeto_j2_2016, JetIDlepVeto_j2_2017, JetIDlepVeto_j2_2018;

							

						double eta_j1, cm_j1, nm_j1, nemf_j1, cemf_j1, nhf_j1, chf_j1, muf_j1; 
						double eta_j2, cm_j2, nm_j2, nemf_j2, cemf_j2, nhf_j2, chf_j2, muf_j2; 

						eta_j1  = jetEtaAK8->at(0);		eta_j2  = jetEtaAK8->at(1);
						cm_j1   = chMultAK8->at(0);		cm_j2   = chMultAK8->at(1);
						nm_j1   = neMultAK8->at(0);		nm_j2   = neMultAK8->at(1);
						nemf_j1 = jetNemfAK8->at(0);	nemf_j2 = jetNemfAK8->at(1);
						cemf_j1 = jetCemfAK8->at(0);	cemf_j2 = jetCemfAK8->at(1);
						chf_j1  = jetChfAK8->at(0);		chf_j2  = jetChfAK8->at(1);
						nhf_j1  = jetNhfAK8->at(0);		nhf_j2  = jetNhfAK8->at(1);
						muf_j1  = jetMufAK8->at(0);		muf_j2  = jetMufAK8->at(1);


////////////////////////////////////////////JetID for 2016 chs////////////////////////////////////////////




						JetID_j1_2016 = getJetID(2016,false, eta_j1, cm_j1, nm_j1, nemf_j1, cemf_j1, nhf_j1, chf_j1, muf_j1);
						JetIDlepVeto_j1_2016 = getJetID(2016,true, eta_j1, cm_j1, nm_j1, nemf_j1, cemf_j1, nhf_j1, chf_j1, muf_j1);

						JetID_j2_2016 = getJetID(2016,false, eta_j2, cm_j2, nm_j2, nemf_j2, cemf_j2, nhf_j2, chf_j2, muf_j2);
						JetIDlepVeto_j2_2016 = getJetID(2016,true, eta_j2, cm_j2, nm_j2, nemf_j2, cemf_j2, nhf_j2, chf_j2, muf_j2);
						


						if(JetID_j1_2016) 					fillVariableWithValue("JetID_2016_j1",1);
						else								fillVariableWithValue("JetID_2016_j1",0);
						if(JetIDlepVeto_j1_2016)			fillVariableWithValue("JetIDlepVeto_2016_j1",1);
						else 								fillVariableWithValue("JetIDlepVeto_2016_j1",0);

						if(JetID_j2_2016) 					fillVariableWithValue("JetID_2016_j2",1);
						else								fillVariableWithValue("JetID_2016_j2",0);
						if(JetIDlepVeto_j2_2016)			fillVariableWithValue("JetIDlepVeto_2016_j2",1);
						else 								fillVariableWithValue("JetIDlepVeto_2016_j2",0);


////////////////////////////////////////////JetID for 2017 puppi////////////////////////////////////////////

						JetID_j1_2017 = getJetID(2017,false, eta_j1, cm_j1, nm_j1, nemf_j1, cemf_j1, nhf_j1, chf_j1, muf_j1);
						JetIDlepVeto_j1_2017 = getJetID(2017,true, eta_j1, cm_j1, nm_j1, nemf_j1, cemf_j1, nhf_j1, chf_j1, muf_j1);

						JetID_j2_2017 = getJetID(2017,false, eta_j2, cm_j2, nm_j2, nemf_j2, cemf_j2, nhf_j2, chf_j2, muf_j2);
						JetIDlepVeto_j2_2017 = getJetID(2017,true, eta_j2, cm_j2, nm_j2, nemf_j2, cemf_j2, nhf_j2, chf_j2, muf_j2);



						if(JetID_j1_2017) 					fillVariableWithValue("JetID_2017_j1",1);
						else								fillVariableWithValue("JetID_2017_j1",0);
						if(JetIDlepVeto_j1_2017)			fillVariableWithValue("JetIDlepVeto_2017_j1",1);
						else 								fillVariableWithValue("JetIDlepVeto_2017_j1",0);

						if(JetID_j2_2017) 					fillVariableWithValue("JetID_2017_j2",1);
						else								fillVariableWithValue("JetID_2017_j2",0);
						if(JetIDlepVeto_j2_2017)			fillVariableWithValue("JetIDlepVeto_2017_j2",1);
						else 								fillVariableWithValue("JetIDlepVeto_2017_j2",0);



////////////////////////////////////////////JetID for 2018 puppi////////////////////////////////////////////

						JetID_j1_2018 = getJetID(2018, false, eta_j1, cm_j1, nm_j1, nemf_j1, cemf_j1, nhf_j1, chf_j1, muf_j1);
						JetIDlepVeto_j1_2018 = getJetID(2018, true, eta_j1, cm_j1, nm_j1, nemf_j1, cemf_j1, nhf_j1, chf_j1, muf_j1);

						JetID_j2_2018 = getJetID(2018, false, eta_j2, cm_j2, nm_j2, nemf_j2, cemf_j2, nhf_j2, chf_j2, muf_j2);
						JetIDlepVeto_j2_2018 = getJetID(2018, true, eta_j2, cm_j2, nm_j2, nemf_j2, cemf_j2, nhf_j2, chf_j2, muf_j2);


						if(JetID_j1_2018) 					fillVariableWithValue("JetID_2018_j1",1);
						else								fillVariableWithValue("JetID_2018_j1",0);
						if(JetIDlepVeto_j1_2018)			fillVariableWithValue("JetIDlepVeto_2018_j1",1);
						else 								fillVariableWithValue("JetIDlepVeto_2018_j1",0);

						if(JetID_j2_2018) 					fillVariableWithValue("JetID_2018_j2",1);
						else								fillVariableWithValue("JetID_2018_j2",0);
						if(JetIDlepVeto_j2_2018)			fillVariableWithValue("JetIDlepVeto_2018_j2",1);
						else 								fillVariableWithValue("JetIDlepVeto_2018_j2",0);


			 			// Evaluate cuts (but do not apply them)
						evaluateCuts();     
						fillReducedSkimTree();

					} //end of deltPhi cut
				} //end of  PassJSON cut 
			 } //end of pt cut
		 } //end of dijets  
		 ////////////////////// User's code ends here ///////////////////////
	 } // End loop over events
	  
	std::cout << "analysisClass::Loop() ends" <<std::endl;   
}

bool analysisClass::getJetID(int era, bool LepVeto, double eta, double cm, double nm, double nemf, double cemf, double nhf, double chf, double muf )
{
	bool tight, extracut_26_27, extracut_27_3, extracut_3_5, lepton_cut, JetID;

	if ( era == 2016) 
	{
		bool tight_24_27, lepton_cut_24_27, lepton_tot;

		tight = ( abs(eta)<=2.4 && cm>0 && nemf<0.9 && chf>0 && nhf < 0.9 && (cm + nm)>1 && cemf<0.99 );
		tight_24_27 = ( abs(eta)>2.4 && abs(eta)<=2.7 && nemf<0.9 && nhf < 0.9 && ( cm + nm )>1 ) ;
		extracut_27_3 = ( abs(eta)> 2.7 && abs(eta)<=3.0 && nhf <0.98 && nemf>0.01 && nm>2 );  
		extracut_3_5 =  ( abs(eta)> 3.0 && abs(eta)<=5.0 && nemf< 0.9 && nm > 10 ); 
		lepton_cut =  abs(eta)>2.7  || ( muf<0.8 && cemf < 0.9 && abs(eta)<=2.4);
		lepton_cut_24_27 =  abs(eta)>2.7 || (muf<0.8 && abs(eta)>2.4 && abs(eta )<=2.7) ;
		lepton_tot = lepton_cut || lepton_cut_24_27;



		if (LepVeto) JetID = ( tight || tight_24_27 || extracut_27_3 || extracut_3_5 ) && lepton_tot ;
		else JetID = tight || tight_24_27 || extracut_27_3 || extracut_3_5;
	}
	else if( era == 2017 )
	{

		tight = (abs(eta)<=2.7 && cm>0 && nemf<0.9 && chf>0 && nhf < 0.9 &&   (cm + nm)>1   );
		extracut_27_3 = (abs(eta)> 2.7 && abs(eta)<=3.0 && nhf<0.99);  
		extracut_3_5 = (abs(eta)> 3.0 && abs(eta)<=5.0 && nemf< 0.9 && nhf>0.02 && nm>2 && nm<15); 
		lepton_cut =  abs(eta)>2.7 || (muf<0.8 && cemf<0.8 && abs(eta)<2.7);


		if (LepVeto) JetID = ( tight ||  extracut_27_3 || extracut_3_5) && lepton_cut ;
		else  JetID =  tight ||  extracut_27_3 || extracut_3_5;
	}
	else 
	{
		if (era != 2018) cout << "\nWARNING! era "<< era <<" is not valid. Will use era 2018. Valid era's are the integers: 2016, 2017, 2018. " << endl;

		tight = ( abs(eta)<=2.6 && cm>0 && nemf<0.9 && chf>0 && nhf < 0.9 && ( cm + nm)>1   );
		extracut_26_27 = (abs(eta)> 2.6 && abs(eta)<=2.7 && nemf<0.99 && nhf<0.9 );
		extracut_27_3 = (abs(eta)> 2.7 && abs(eta)<=3.0 && nhf<0.99);  
		extracut_3_5 = (abs(eta)> 3.0 && abs(eta)<=5.0 && nemf< 0.9 && nhf>0.02 && nm>2 && nm<15); 
		lepton_cut =  abs(eta)>2.7 || ( muf<0.8 && cemf<0.8 && abs(eta)<=2.7 );

		if (LepVeto) JetID = ( tight || extracut_26_27 || extracut_27_3 || extracut_3_5) && lepton_cut;
		else JetID =  tight || extracut_26_27 || extracut_27_3 || extracut_3_5 ;
	}



return JetID;
}


