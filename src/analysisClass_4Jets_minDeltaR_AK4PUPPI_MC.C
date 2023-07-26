#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>

//ATTENTION: In the big trees we save AK4 PUPPI jets as "AK8". Here whichever variable has the name AK8 it means AK4PUPPI

analysisClass::analysisClass(string * inputList, string * cutFile, string * treeName, string * outputFileName, string * cutEfficFile)
  :baseClass(inputList, cutFile, treeName, outputFileName, cutEfficFile)
{
  std::cout << "analysisClass::analysisClass(): begins " << std::endl;

  // For JECs
  if( int(getPreCutValue1("useJECs"))==1 )
  {
    std::cout << "Reapplying JECs on the fly" << std::endl;
    std::cout << "Using IOV implementation for periodic JEC..." << std::endl;
    
    // Using IOV JEC now. Now that's 2016. See include/IOV.h for changing versions.
    // Note that the IOV implementation can be used with just one JEC if wanted. Juska.
    
    /*
   Ranges for 2016 run periods from DAS as of 4 Nov 16.
   Periods with no certified luminosity are omitted.
   B-v2: 273150 - 275376
   C-v2: 276282 - 276279
   D-v2: 276315 - 276653
   E-v2: 276824 - 277420
   F-v1: 277816 - 278808
   G-v1: 278816 - 280385
   H-v2: 282807 - 283885
   List obtained with commands like this:
   [juska@lxplus069 workdir]$ das_client.py --query='run dataset=/JetHT/Run2016H-PromptReco-v2/MINIAOD' --limit 0
    */

    
    // IOV's updated for Summer16_V3 JEC intervals
  /*  iov = new jec::IOV("AK4PFchs");
    iov->add("BCD",1,276811,true);
    iov->add("EF",276831,278801,true);
    iov->add("G",278802,280385,true);
    iov->add("H",280919,999999,true);*/

/* iov = new jec::IOV("AK4PFchs");
    iov->add("B",297046,299329,true);
    iov->add("C",299368,302029,true);
    iov->add("D",302030,303434,true);
    iov->add("E",303824,304797,true);
    iov->add("F",305040,999999,true);*/

 /*iov = new jec::IOV("AK4PFchs");
    iov->add("B",297046,299329,true);
    iov->add("C",299368,302029,true);
    iov->add("DE",302030,304797,true);
    iov->add("F",305040,999999,true);
*/


/*    
    JetCorrector_data = new FactorizedJetCorrector(); // Will be filled later

           
    std::string L1Path = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L1FastJet_AK4PFPuppi.txt";
    std::string L2Path = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L2Relative_AK4PFPuppi.txt";
    std::string L3Path = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L3Absolute_AK4PFPuppi.txt";

    std::string L1DATAPath = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L1FastJet_AK4PFPuppi.txt";
    std::string L2DATAPath = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L2Relative_AK4PFPuppi.txt"; 
    std::string L3DATAPath = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L3Absolute_AK4PFPuppi.txt";
    //std::string L2L3ResidualPath = "data/Winter23Prompt23_V1_MC/Winter23Prompt23_V1_MC_L2L3Residual_AK4PFPuppi.txt";

    unc = new JetCorrectionUncertainty("data/Winter23Prompt23_V1_MC/Winter23Prompt23_V1_MC_Uncertainty_AK4PFPuppi.txt");
*/


    std::string L1Path = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L1FastJet_AK4PFPuppi.txt";
    std::string L2Path = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L2Relative_AK4PFPuppi.txt";
    std::string L3Path = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L3Absolute_AK4PFPuppi.txt";

    std::string L1DATAPath = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L1FastJet_AK4PFPuppi.txt";
    std::string L2DATAPath = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L2Relative_AK4PFPuppi.txt"; 
    std::string L3DATAPath = "data/Summer22Run3_V1_MC/Summer22Run3_V1_MC_L3Absolute_AK4PFPuppi.txt";
    //std::string L2L3ResidualPath = "data/Winter22Run3/Winter22Run3_RunC_V2_DATA_L2Residual_AK4PFPuppi.txt";

    unc = new JetCorrectionUncertainty("data/Winter22Run3/Winter22Run3_V1_Uncertainty_AK4PFPuppi.txt");



 
    L1Par = new JetCorrectorParameters(L1Path);
    L2Par = new JetCorrectorParameters(L2Path);
    L3Par = new JetCorrectorParameters(L3Path);
    
    L1DATAPar = new JetCorrectorParameters(L1DATAPath);
    L2DATAPar = new JetCorrectorParameters(L2DATAPath);
    L3DATAPar = new JetCorrectorParameters(L3DATAPath);
    //L2L3Residual = new JetCorrectorParameters(L2L3ResidualPath);
    

    std::vector<JetCorrectorParameters> vPar;
    vPar.push_back(*L1Par);
    vPar.push_back(*L2Par);
    vPar.push_back(*L3Par);

      
    //residuals are applied only to data
    std::vector<JetCorrectorParameters> vPar_data;
    vPar_data.push_back(*L1DATAPar);
    vPar_data.push_back(*L2DATAPar);
    vPar_data.push_back(*L3DATAPar);
    //vPar_data.push_back(*L2L3Residual);
    

   JetCorrector = new FactorizedJetCorrector(vPar); assert(JetCorrector);
   JetCorrector_data = new FactorizedJetCorrector(vPar_data); assert(JetCorrector_data);
    
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

   /////////initialize variables

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << "analysisClass::Loop(): nentries = " << nentries << std::endl;   

   ////// The following ~7 lines have been taken from rootNtupleClass->Loop() /////
   ////// If the root version is updated and rootNtupleClass regenerated,     /////
   ////// these lines may need to be updated.                                 /////    
   Long64_t nbytes = 0, nb = 0;
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) { //event loop
   //for (Long64_t jentry=0; jentry<10;jentry++) {
   //for (Long64_t jentry=0; jentry<nentries;jentry=jentry+10) {   //takes every 10th en
   
     Long64_t ientry = LoadTree(jentry);

     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     if(jentry < 10 || jentry%500000 == 0) std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
     // if (Cut(ientry) < 0) continue;

     ////////////////////// User's code starts here ///////////////////////

     ///Stuff to be done for every event

     size_t no_jets_ak8=jetPtAK8->size();

     vector<TLorentzVector> AK8jets;    
     TLorentzVector ak8j1, ak8j2, ak8j3, ak8j4; 
     TLorentzVector ak8dijet1_[3][1],  ak8dijet2_[3][1], ak8fourjet;  
     TLorentzVector b, c, d;

     resetCuts();

     //find intime BX
     int idx_InTimeBX=-1;
     for(size_t j=0; j<PileupOriginBX->size(); ++j)
       {
	 //cout << PileupOriginBX->at(j) << endl;	 
	 if(PileupOriginBX->at(j)==0)
	   {
	     idx_InTimeBX = j;
	     //cout << "idx_InTimeBX: " << idx_InTimeBX << endl; 
	   }
       }

     std::vector<double> jecFactors;
     std::vector<double> jecUncertainty;
     // new JECs could change the jet pT ordering. the vector below
     // holds sorted jet indices after the new JECs had been applied
     std::vector<unsigned> sortedJetIdx;
     bool isData = 0;

     if(idx_InTimeBX > -1 ) isData = 0;
     else isData = 1;
 
     if( int(getPreCutValue1("useJECs"))==1 )
     {
	 // sort jets by increasing pT
	 std::multimap<double, unsigned> sortedJets;
	 for(size_t j=0; j<no_jets_ak8; ++j)
	 {
	     JetCorrector->setJetEta(jetEtaAK8->at(j));
	     JetCorrector->setJetPt(jetPtAK8->at(j)/jetJecAK8->at(j)); //pTraw
	     JetCorrector->setJetA(jetAreaAK8->at(j));
	     JetCorrector->setRho(rho);
	     
  	     //JetCorrector_data = iov->get(runNo); // Get IOV dependent JEC

        
  	     JetCorrector_data->setJetEta(jetEtaAK8->at(j));
	     JetCorrector_data->setJetPt(jetPtAK8->at(j)/jetJecAK8->at(j)); //pTraw
	     JetCorrector_data->setJetA(jetAreaAK8->at(j));
	     JetCorrector_data->setRho(rho);


  	     //nominal value of JECs
	     double correction;//, old_correction, nominal_correction;
	     //if( int(getPreCutValue1("shiftJECs"))==0 ){
	     if (isData == 1) correction = JetCorrector_data->getCorrection();                             
	     else correction = JetCorrector->getCorrection();
	
	     //nominal_correction=correction;
	     //old_correction = jetJecAK8->at(j);
	     //}
	     //JEC uncertainties
	     unc->setJetEta(jetEtaAK8->at(j));
	     unc->setJetPt(jetPtAK8->at(j)/jetJecAK8->at(j)*correction);
	     double uncertainty = unc->getUncertainty(true);
	     jecUncertainty.push_back(uncertainty); 

	     //use "shifted" JECs for study of systematic uncertainties 
	     if( int(getPreCutValue1("shiftJECs"))==1 ){
	       //flat shift
	       //if (isData == 1) correction = JetCorrector_data->getCorrection() * getPreCutValue2("shiftJECs");
	       //else correction = JetCorrector->getCorrection() * getPreCutValue2("shiftJECs");
	       //shift of the corresponding unc
	       correction = correction + getPreCutValue2("shiftJECs")*uncertainty*correction;	       
	     }

	     jecFactors.push_back(correction);
	     sortedJets.insert(std::make_pair((jetPtAK8->at(j)/jetJecAK8->at(j))*correction, j));

       }
       // get jet indices in decreasing pT order
       for(std::multimap<double, unsigned>::const_reverse_iterator it = sortedJets.rbegin(); it != sortedJets.rend(); ++it)
	 sortedJetIdx.push_back(it->second);
     
     }
     else if( int(getPreCutValue1("noJECs"))==1  )
     {
	 // sort jets by increasing pT
	 std::multimap<double, unsigned> sortedJets;
	 for(size_t j=0; j<no_jets_ak8; ++j) //same ordering of original root trees
	   {
	     jecUncertainty.push_back(0.); 
	     jecFactors.push_back(1.);
	     sortedJets.insert(std::make_pair((jetPtAK8->at(j)/jetJecAK8->at(j)), j)); //raw
	   }       
	 // get jet indices in decreasing pT order
	 for(std::multimap<double, unsigned>::const_reverse_iterator it = sortedJets.rbegin(); it != sortedJets.rend(); ++it)
	   sortedJetIdx.push_back(it->second);
     }
     else
     {
	 for(size_t j=0; j<no_jets_ak8; ++j) //same ordering of original root trees
	   {
	     jecFactors.push_back(jetJecAK8->at(j));
	     jecUncertainty.push_back(0.); 
	     sortedJetIdx.push_back(j);
	   }
     }



    // Create JetID vector for every jet in the event (do not use the existing jetID vector from the big trees)
     std::vector<int> *JetID = 0;

     for(size_t ijet=0; ijet<no_jets_ak8; ++ijet)
     {
	 int passJetID = ( jetNhfAK8->at(ijet)<0.99 && jetNemfAK8->at(ijet)<0.9 && chMultAK8->at(ijet)+neMultAK8->at(ijet)>1 && jetMufAK8->at(ijet)<0.8 && jetChfAK8->at(ijet)>0.01 && chMultAK8->at(ijet)>0 && jetCemfAK8->at(ijet)<0.8 );

         JetID.push_back(passJetID);
     }



     //#############################################################
     //########## NOTE: from now on sortedJetIdx[ijet] should be used
     //#############################################################


     //count ak8 jets passing eta, pt threshold and id criteria
     int Nak8 = 0;
     double HTak8 = 0;
     for(size_t ijet=0; ijet<no_jets_ak8; ++ijet)
     {
	  //cout << "ijet=" << ijet << " , sortedJetIdx[ijet]=" << sortedJetIdx[ijet] 
	  //     << " , raw pT=" << jetPtAK8->at(sortedJetIdx[ijet])/jetJecAK8->at(sortedJetIdx[ijet]) 
	  //     << " , final corrected pT - old =" << jetPtAK8->at(sortedJetIdx[ijet] ) 
	  //     << " , final corrected pT - new =" << (jecFactors[sortedJetIdx[ijet]]/jetJecAK8->at(sortedJetIdx[ijet]))*jetPtAK8->at(sortedJetIdx[ijet])
	  //     << endl;

	 //////////////cout << "id Tight jet" << sortedJetIdx[1] << " = " << idTAK8->at(sortedJetIdx[1]) << endl;
	 if(fabs(jetEtaAK8->at(sortedJetIdx[ijet])) < getPreCutValue1("jetFidRegion") && JetID->at(sortedJetIdx[ijet]) == getPreCutValue1("tightJetID") && (jecFactors[sortedJetIdx[ijet]]/jetJecAK8->at(sortedJetIdx[ijet]))*jetPtAK8->at(sortedJetIdx[ijet]) > getPreCutValue1("ptCut"))
	 {
	     Nak8 += 1;
	     HTak8 += (jecFactors[sortedJetIdx[ijet]]/jetJecAK8->at(sortedJetIdx[ijet]))*jetPtAK8->at(sortedJetIdx[ijet]);
	 }
     }


     //AK8 jets
     if(no_jets_ak8>=4){

	 if(fabs(jetEtaAK8->at(sortedJetIdx[0])) < getPreCutValue1("jetFidRegion") && JetID->at(sortedJetIdx[0]) == getPreCutValue1("tightJetID") && (jecFactors[sortedJetIdx[0]]/jetJecAK8->at(sortedJetIdx[0]))*jetPtAK8->at(sortedJetIdx[0]) > getPreCutValue1("pt0Cut")){

	     if(fabs(jetEtaAK8->at(sortedJetIdx[1])) < getPreCutValue1("jetFidRegion") && JetID->at(sortedJetIdx[1]) == getPreCutValue1("tightJetID") && (jecFactors[sortedJetIdx[1]]/jetJecAK8->at(sortedJetIdx[1]))*jetPtAK8->at(sortedJetIdx[1]) > getPreCutValue1("pt1Cut")){

 		 if(fabs(jetEtaAK8->at(sortedJetIdx[2])) < getPreCutValue1("jetFidRegion") && JetID->at(sortedJetIdx[2]) == getPreCutValue1("tightJetID") && (jecFactors[sortedJetIdx[2]]/jetJecAK8->at(sortedJetIdx[2]))*jetPtAK8->at(sortedJetIdx[2]) > getPreCutValue1("pt2Cut")){

 		    if(fabs(jetEtaAK8->at(sortedJetIdx[3])) < getPreCutValue1("jetFidRegion") && JetID->at(sortedJetIdx[3]) == getPreCutValue1("tightJetID") && (jecFactors[sortedJetIdx[3]]/jetJecAK8->at(sortedJetIdx[3]))*jetPtAK8->at(sortedJetIdx[3]) > getPreCutValue1("pt3Cut")){
 			
		 	  ak8j1.SetPtEtaPhiM( (jecFactors[sortedJetIdx[0]]/jetJecAK8->at(sortedJetIdx[0])) *jetPtAK8->at(sortedJetIdx[0])
				     ,jetEtaAK8->at(sortedJetIdx[0])
				     ,jetPhiAK8->at(sortedJetIdx[0])
				     , (jecFactors[sortedJetIdx[0]]/jetJecAK8->at(sortedJetIdx[0])) *jetMassAK8->at(sortedJetIdx[0]));
			  ak8j2.SetPtEtaPhiM( (jecFactors[sortedJetIdx[1]]/jetJecAK8->at(sortedJetIdx[1])) *jetPtAK8->at(sortedJetIdx[1])
				     ,jetEtaAK8->at(sortedJetIdx[1])
				     ,jetPhiAK8->at(sortedJetIdx[1])
				     , (jecFactors[sortedJetIdx[1]]/jetJecAK8->at(sortedJetIdx[1])) *jetMassAK8->at(sortedJetIdx[1]));

                 	  ak8j3.SetPtEtaPhiM( (jecFactors[sortedJetIdx[2]]/jetJecAK8->at(sortedJetIdx[2])) *jetPtAK8->at(sortedJetIdx[2])
				     ,jetEtaAK8->at(sortedJetIdx[2])
				     ,jetPhiAK8->at(sortedJetIdx[2])
				     , (jecFactors[sortedJetIdx[2]]/jetJecAK8->at(sortedJetIdx[2])) *jetMassAK8->at(sortedJetIdx[2]));
                 	  ak8j4.SetPtEtaPhiM( (jecFactors[sortedJetIdx[3]]/jetJecAK8->at(sortedJetIdx[3])) *jetPtAK8->at(sortedJetIdx[3])
				     ,jetEtaAK8->at(sortedJetIdx[3])
				     ,jetPhiAK8->at(sortedJetIdx[3])
				     , (jecFactors[sortedJetIdx[3]]/jetJecAK8->at(sortedJetIdx[3])) *jetMassAK8->at(sortedJetIdx[3]));
		   
	            }
	         }
            } 
         }
     }  //end of 4jets 

     double MJJAK8 = 0; 
     double MJJAK8_1_[3][1]={0}; double MJJAK8_2_[3][1]={0};
     double MJJAK8_1=0; double MJJAK8_2=0;      
     
     double M4J_AK8=0; double Maverage=0;
     double Masymmetry=0; double Masymmetry_[3][1]={0}; 
     double DDR=0; double DDR_[3][1]={0};
     double DeltaR=0; double DeltaR_[3][1]={0}; double Delta_1=0; double Delta_2=0;  
          
     double PT_firstcomb_1=0; double PT_firstcomb_2=0; double PT_secondcomb_1=0; double PT_secondcomb_2=0;

     double DeltaPhiJJAK8=0; double DeltaEtaJJAK8=0;   
     double ETA_1=0; double ETA_2=0;
      
     double Rapidity_1=0; double Rapidity_2=0; double DeltaRapidity=0;
     double DeltaRAK8_First=0; double DeltaRAK8_Second=0; double DeltaRAK8_1_[3][1]={0}; double DeltaRAK8_2_[3][1]={0};
  
   if( ak8j1.Pt()>0 && ak8j2.Pt()>0  && ak8j3.Pt()>0 && ak8j4.Pt()>0){ // Create 4jet system, create 3 combinations
   //cout<<ak8j1.Pt()<<" "<<ak8j2.Pt()<<" "<<ak8j3.Pt()<<" "<<ak8j4.Pt()<<endl;  

     for(int comb=0; comb<3; comb++){ //for 5jets loop: loop over 4 combinations: 1->2, 1->3, 1->4, 1->5

       for(int ijet=0; ijet<1; ijet++){//for 5jets loop: loop over 3 cases: i.e. for 1->2 combinations the cases are 3->4, 3->5, 4->5
     
         if(comb==0){
	   b=ak8j2;
	   if(ijet==0){c=ak8j3;d=ak8j4;}
           //if(ijet==1){c=ak8j3;d=ak8j5;}
           //if(ijet==2){c=ak8j4;d=ak8j5;}
         }if(comb==1){
	   b=ak8j3;
	   if(ijet==0){c=ak8j2;d=ak8j4;}
           //if(ijet==1){c=ak8j2;d=ak8j5;}
           //if(ijet==2){c=ak8j4;d=ak8j5;}
         }if(comb==2){
           b=ak8j4;
	   if(ijet==0){c=ak8j2;d=ak8j3;}
           //if(ijet==1){c=ak8j2;d=ak8j5;}
           //if(ijet==2){c=ak8j3;d=ak8j5;}
         }
/*	if(comb==3){
	   b=ak8j5;
 	   if(ijet==0){c=ak8j2;d=ak8j3;}
           if(ijet==1){c=ak8j2;d=ak8j4;}
           if(ijet==2){c=ak8j3;d=ak8j4;}
         }      
*/
       ak8dijet1_[comb][ijet] = ak8j1 + b;
       ak8dijet2_[comb][ijet]=  c + d;  
 
       MJJAK8_1_[comb][ijet] = ak8dijet1_[comb][ijet].M();
       MJJAK8_2_[comb][ijet] = ak8dijet2_[comb][ijet].M();
       Masymmetry_[comb][ijet]=fabs((MJJAK8_1_[comb][ijet]-MJJAK8_2_[comb][ijet])/(MJJAK8_1_[comb][ijet]+MJJAK8_2_[comb][ijet]));  
       
       DeltaRAK8_1_[comb][ijet]=ak8j1.DeltaR(b);//here DeltaR between jets of the 1st pair
       DeltaRAK8_2_[comb][ijet]=c.DeltaR(d);//here DeltaR between jets of the 2nd pair
       //cout<<DeltaRAK8_1_[comb][ijet]<<" "<<DeltaRAK8_2_[comb][ijet]<<endl; 
       DDR_[comb][ijet] = fabs(DeltaRAK8_1_[comb][ijet]-DeltaRAK8_2_[comb][ijet]);
       DeltaR_[comb][ijet] = fabs(DeltaRAK8_1_[comb][ijet]-0.8) + fabs(DeltaRAK8_2_[comb][ijet]-0.8);
     
       }//end of ijet loop:  different cases for the 1st combination

     } //end of combination loop

     double DDR_minimum=1000.0; double Masymmetry_minimum=1000; double DeltaR_minimum=1000; int comb_min,ijet_min, comb_min_Mas, ijet_min_Mas, comb_min_DR, ijet_min_DR;
     for(int comb=0; comb<3; comb++){ //for 5jets loop:  loop over 4 combinations: 1->2, 1->3, 1->4, 1->5
       for(int ijet=0; ijet<1; ijet++){//for 5jets loop:  loop over 3 cases: i.e. for 1->2 combinations the cases are 3->4, 3->5, 4->5
     
	 if(DDR_[comb][ijet] < DDR_minimum) {
           DDR_minimum = DDR_[comb][ijet];
	   comb_min=comb; ijet_min=ijet;
         }
         if(Masymmetry_[comb][ijet] < Masymmetry_minimum) {
           Masymmetry_minimum = Masymmetry_[comb][ijet];
	   comb_min_Mas=comb; ijet_min_Mas=ijet;
         }
         if(DeltaR_[comb][ijet] < DeltaR_minimum){
	   DeltaR_minimum = DeltaR_[comb][ijet];
	   comb_min_DR=comb; ijet_min_DR=ijet;
	 }
         
       }//end of ijet loop:  different cases for the 1st combination
     } //end of combination loop
     //cout << comb_min<<" "<<ijet_min<<" "<<DDR_minimum << endl;

     for(int comb=0; comb<3; comb++){ //for 5jets loop: loop over 4 combinations: 1->2, 1->3, 1->4, 1->5
       for(int ijet=0; ijet<1; ijet++){//for 5jets loop: loop over 3 cases: i.e. for 1->2 combinations the cases are 3->4, 3->5, 4->5
    
         if(comb==comb_min_DR && ijet==ijet_min_DR){

           if(comb==0){
	     b=ak8j2;
	     if(ijet==0){c=ak8j3;d=ak8j4;}
             //if(ijet==1){c=ak8j3;d=ak8j5;}
             //if(ijet==2){c=ak8j4;d=ak8j5;}
           }if(comb==1){
	     b=ak8j3;
	     if(ijet==0){c=ak8j2;d=ak8j4;}
             //if(ijet==1){c=ak8j2;d=ak8j5;}
             //if(ijet==2){c=ak8j4;d=ak8j5;}
           }if(comb==2){
             b=ak8j4;
	     if(ijet==0){c=ak8j2;d=ak8j3;}
             //if(ijet==1){c=ak8j2;d=ak8j5;}
             //if(ijet==2){c=ak8j3;d=ak8j5;}
           }
/*	if(comb==3){
	     b=ak8j5;
 	     if(ijet==0){c=ak8j2;d=ak8j3;}
             if(ijet==1){c=ak8j2;d=ak8j4;}
             if(ijet==2){c=ak8j3;d=ak8j4;}
           }  
*/
     	   MJJAK8_1=MJJAK8_1_[comb][ijet]; 
    	   MJJAK8_2=MJJAK8_2_[comb][ijet];
           ak8fourjet=ak8j1+b+c+d;  
   	   M4J_AK8=ak8fourjet.M();

    	   Maverage=(MJJAK8_1_[comb][ijet]+MJJAK8_2_[comb][ijet])/2.;
    	   Masymmetry=Masymmetry_[comb][ijet];
    	   DDR=DDR_[comb_min][ijet]; 
    	   DeltaEtaJJAK8=fabs(ak8dijet1_[comb][ijet].Eta()-ak8dijet2_[comb][ijet].Eta());// edw Delta ETA metaxy zevgwn
    	   DeltaPhiJJAK8 = fabs(ak8dijet1_[comb][ijet].DeltaPhi(ak8dijet2_[comb][ijet]));

    	   PT_firstcomb_1=ak8j1.Pt();
    	   PT_firstcomb_2=b.Pt();
    	   PT_secondcomb_1=c.Pt();
     	   PT_secondcomb_2=d.Pt();

    	   ETA_1=ak8dijet1_[comb][ijet].Eta();
     	   ETA_2=ak8dijet2_[comb][ijet].Eta();

     	   Rapidity_1=ak8dijet1_[comb][ijet].Rapidity();
     	   Rapidity_2=ak8dijet2_[comb][ijet].Rapidity();
     	   DeltaRapidity=fabs(ak8dijet1_[comb][ijet].Rapidity()-ak8dijet2_[comb][ijet].Rapidity());

     	   DeltaRAK8_First=DeltaRAK8_1_[comb][ijet];
     	   DeltaRAK8_Second=DeltaRAK8_2_[comb][ijet];
	   DeltaR=DeltaR_[comb][ijet]; 


	   //=============== EXO-17-021 ===============
       	   Delta_1=PT_firstcomb_1+PT_firstcomb_2-Maverage;
           Delta_2=PT_secondcomb_1+PT_secondcomb_2-Maverage;

       	   // Put in the container
           AK8jets.push_back(ak8j1);
           AK8jets.push_back(ak8j2);
           AK8jets.push_back(ak8j3);
           AK8jets.push_back(ak8j4);

	 }//end of if min
       }//end of ijet	
     }//end of comb
   }//end of 5jet system with pt>0
   

     //== Fill Variables ==

     fillVariableWithValue("run",runNo);     
     fillVariableWithValue("event",evtNo);     
     fillVariableWithValue("lumi",lumi);     
     fillVariableWithValue("nVtx",nvtx);     
     fillVariableWithValue("metSig",metSig);
     fillVariableWithValue("Nak4puppi",Nak8);
     fillVariableWithValue ("PassJSON", passJSON (runNo, lumi, isData));


     if( AK8jets.size() >=4 ){//4-jets analysis 

       fillVariableWithValue("IdTightAK4PUPPI_j1",JetID->at(sortedJetIdx[0]));
       fillVariableWithValue("pTAK4PUPPI_j1", AK8jets[0].Pt());
       fillVariableWithValue("etaAK4PUPPI_j1", AK8jets[0].Eta());
       fillVariableWithValue("phiAK4PUPPI_j1", AK8jets[0].Phi());
       fillVariableWithValue("jetJecAK4PUPPI_j1", jecFactors[sortedJetIdx[0]] );
       fillVariableWithValue("jetJecUncAK4PUPPI_j1", jecUncertainty[sortedJetIdx[0]]);   
       fillVariableWithValue("neutrHadEnFracAK4PUPPI_j1", jetNhfAK8->at(sortedJetIdx[0]));
       fillVariableWithValue("chargedHadEnFracAK4PUPPI_j1", jetChfAK8->at(sortedJetIdx[0]));
       fillVariableWithValue("photonEnFracAK4PUPPI_j1", jetPhfAK8->at(sortedJetIdx[0]));
       fillVariableWithValue("eleEnFractAK4PUPPI_j1", jetElfAK8->at(sortedJetIdx[0]));
       fillVariableWithValue("muEnFractAK4PUPPI_j1", jetMufAK8->at(sortedJetIdx[0]));
       fillVariableWithValue("neutrElectromFracAK4PUPPI_j1", jetNemfAK8->at(sortedJetIdx[0]));
       fillVariableWithValue("chargedElectromFracAK4PUPPI_j1", jetCemfAK8->at(sortedJetIdx[0]));
       fillVariableWithValue("chargedMultAK4PUPPI_j1", chMultAK8->at(sortedJetIdx[0]));
       fillVariableWithValue("neutrMultAK4PUPPI_j1", neMultAK8->at(sortedJetIdx[0]));
       fillVariableWithValue("photonMultAK4PUPPI_j1", phoMultAK8->at(sortedJetIdx[0]));
     
       fillVariableWithValue("IdTightAK4PUPPI_j2",JetID->at(sortedJetIdx[1]));
       fillVariableWithValue("pTAK4PUPPI_j2", AK8jets[1].Pt() );
       fillVariableWithValue("etaAK4PUPPI_j2", AK8jets[1].Eta());
       fillVariableWithValue("phiAK4PUPPI_j2", AK8jets[1].Phi());
       fillVariableWithValue("jetJecAK4PUPPI_j2", jecFactors[sortedJetIdx[1]]); 
       fillVariableWithValue("jetJecUncAK4PUPPI_j2", jecUncertainty[sortedJetIdx[1]] );
       fillVariableWithValue("neutrHadEnFracAK4PUPPI_j2", jetNhfAK8->at(sortedJetIdx[1]));
       fillVariableWithValue("chargedHadEnFracAK4PUPPI_j2", jetChfAK8->at(sortedJetIdx[1]));
       fillVariableWithValue("photonEnFracAK4PUPPI_j2", jetPhfAK8->at(sortedJetIdx[1]));
       fillVariableWithValue("eleEnFractAK4PUPPI_j2", jetElfAK8->at(sortedJetIdx[1]));
       fillVariableWithValue("muEnFractAK4PUPPI_j2", jetMufAK8->at(sortedJetIdx[1]));
       fillVariableWithValue("neutrElectromFracAK4PUPPI_j2", jetNemfAK8->at(sortedJetIdx[1]));
       fillVariableWithValue("chargedElectromFracAK4PUPPI_j2", jetCemfAK8->at(sortedJetIdx[1]));
       fillVariableWithValue("chargedMultAK4PUPPI_j2", chMultAK8->at(sortedJetIdx[1]));
       fillVariableWithValue("neutrMultAK4PUPPI_j2", neMultAK8->at(sortedJetIdx[1]));
       fillVariableWithValue("photonMultAK4PUPPI_j2", phoMultAK8->at(sortedJetIdx[1]));

       fillVariableWithValue("IdTightAK4PUPPI_j3",JetID->at(sortedJetIdx[2]));
       fillVariableWithValue("pTAK4PUPPI_j3", AK8jets[2].Pt() );
       fillVariableWithValue("etaAK4PUPPI_j3", AK8jets[2].Eta());
       fillVariableWithValue("phiAK4PUPPI_j3", AK8jets[2].Phi());
       fillVariableWithValue("jetJecAK4PUPPI_j3", jecFactors[sortedJetIdx[2]]); 
       fillVariableWithValue("jetJecUncAK4PUPPI_j3", jecUncertainty[sortedJetIdx[2]] );
       fillVariableWithValue("neutrHadEnFracAK4PUPPI_j3", jetNhfAK8->at(sortedJetIdx[2]));
       fillVariableWithValue("chargedHadEnFracAK4PUPPI_j3", jetChfAK8->at(sortedJetIdx[2]));
       fillVariableWithValue("photonEnFracAK4PUPPI_j3", jetPhfAK8->at(sortedJetIdx[2]));
       fillVariableWithValue("eleEnFractAK4PUPPI_j3", jetElfAK8->at(sortedJetIdx[2]));
       fillVariableWithValue("muEnFractAK4PUPPI_j3", jetMufAK8->at(sortedJetIdx[2]));
       fillVariableWithValue("neutrElectromFracAK4PUPPI_j3", jetNemfAK8->at(sortedJetIdx[2]));
       fillVariableWithValue("chargedElectromFracAK4PUPPI_j3", jetCemfAK8->at(sortedJetIdx[2]));
       fillVariableWithValue("chargedMultAK4PUPPI_j3", chMultAK8->at(sortedJetIdx[2]));
       fillVariableWithValue("neutrMultAK4PUPPI_j3", neMultAK8->at(sortedJetIdx[2]));
       fillVariableWithValue("photonMultAK4PUPPI_j3", phoMultAK8->at(sortedJetIdx[2]));
            
       fillVariableWithValue("IdTightAK4PUPPI_j4",JetID->at(sortedJetIdx[3]));
       fillVariableWithValue("pTAK4PUPPI_j4", AK8jets[3].Pt() );
       fillVariableWithValue("etaAK4PUPPI_j4", AK8jets[3].Eta());
       fillVariableWithValue("phiAK4PUPPI_j4", AK8jets[3].Phi());
       fillVariableWithValue("jetJecAK4PUPPI_j4", jecFactors[sortedJetIdx[3]]); 
       fillVariableWithValue("jetJecUncAK4PUPPI_j4", jecUncertainty[sortedJetIdx[3]] );
       fillVariableWithValue("neutrHadEnFracAK4PUPPI_j4", jetNhfAK8->at(sortedJetIdx[3]));
       fillVariableWithValue("chargedHadEnFracAK4PUPPI_j4", jetChfAK8->at(sortedJetIdx[3]));
       fillVariableWithValue("photonEnFracAK4PUPPI_j4", jetPhfAK8->at(sortedJetIdx[3]));
       fillVariableWithValue("eleEnFractAK4PUPPI_j4", jetElfAK8->at(sortedJetIdx[3]));
       fillVariableWithValue("muEnFractAK4PUPPI_j4", jetMufAK8->at(sortedJetIdx[3]));
       fillVariableWithValue("neutrElectromFracAK4PUPPI_j4", jetNemfAK8->at(sortedJetIdx[3]));
       fillVariableWithValue("chargedElectromFracAK4PUPPI_j4", jetCemfAK8->at(sortedJetIdx[3]));
       fillVariableWithValue("chargedMultAK4PUPPI_j4", chMultAK8->at(sortedJetIdx[3]));
       fillVariableWithValue("neutrMultAK4PUPPI_j4", neMultAK8->at(sortedJetIdx[3]));
       fillVariableWithValue("photonMultAK4PUPPI_j4", phoMultAK8->at(sortedJetIdx[3]));
      
       fillVariableWithValue("Dijet_MassAK4PUPPI_1", MJJAK8_1) ;
       fillVariableWithValue("Dijet_MassAK4PUPPI_2", MJJAK8_2) ;  
       fillVariableWithValue("FourjetMassAK4PUPPI", M4J_AK8) ; 
       fillVariableWithValue("MasymmetryAK4PUPPI" ,Masymmetry);
       fillVariableWithValue("MaverageAK4PUPPI", Maverage);
       fillVariableWithValue("DeltaEtaJJAK4PUPPI", DeltaEtaJJAK8);
       fillVariableWithValue("DeltaRAK4PUPPI_First",DeltaRAK8_First);
       fillVariableWithValue("DeltaRAK4PUPPI_Second",DeltaRAK8_Second);
       fillVariableWithValue("DeltaPhiJJAK4PUPPI",DeltaPhiJJAK8);
       fillVariableWithValue("ETA_AK4PUPPI_1",ETA_1);
       fillVariableWithValue("ETA_AK4PUPPI_2",ETA_2);
       fillVariableWithValue("RapidityAK4PUPPI_1",Rapidity_1);
       fillVariableWithValue("RapidityAK4PUPPI_2",Rapidity_2);
       fillVariableWithValue("DeltaRapidityAK4PUPPI",DeltaRapidity);
       fillVariableWithValue("PTAK4PUPPI_firstcomb_1",PT_firstcomb_1);
       fillVariableWithValue("PTAK4PUPPI_firstcomb_2",PT_firstcomb_2);
       fillVariableWithValue("PTAK4PUPPI_secondcomb_1",PT_secondcomb_1);
       fillVariableWithValue("PTAK4PUPPI_secondcomb_2",PT_secondcomb_2);
       fillVariableWithValue("DDR_AK4PUPPI",DDR);
       fillVariableWithValue("DeltaR_AK4PUPPI",DeltaR);
       fillVariableWithValue("DeltaAK4PUPPI_1", Delta_1);
       fillVariableWithValue("DeltaAK4PUPPI_2", Delta_2);
          
     }//end of 4-jets 


     //no cuts on these variables, just to store in output
     if(!isData)
       fillVariableWithValue("trueVtx",PileupInteractions->at(idx_InTimeBX));
     else if(isData)
       fillVariableWithValue("trueVtx",999);     

     fillVariableWithValue("MET",met);
     double METoverHTAK8=double(met/HTak8);
     fillVariableWithValue("METoverHTAK4PUPPI",METoverHTAK8);
     fillVariableWithValue("HTAK4PUPPI",HTak8);
     fillVariableWithValue("ptHat",ptHat);
     //fillVariableWithValue("weight",weight);

     //triggers
     for(unsigned int i=0; i<triggerName->size(); i++){
	if( triggerName->at(i).compare(0,13,"HLT_PFHT780_v")==0 ) fillVariableWithValue("passHLT_PFHT780",triggerResult->at(i));
	if( triggerName->at(i).compare(0,13,"HLT_PFHT890_v")==0 ) fillVariableWithValue("passHLT_PFHT890",triggerResult->at(i));
	if( triggerName->at(i).compare(0,14,"HLT_PFHT1050_v")==0 ) fillVariableWithValue("passHLT_PFHT1050",triggerResult->at(i));
	if( triggerName->at(i).compare(0,14,"HLT_PFJet400_v")==0 ) fillVariableWithValue("passHLT_PFJet400",triggerResult->at(i));
	if( triggerName->at(i).compare(0,14,"HLT_PFJet450_v")==0 ) fillVariableWithValue("passHLT_PFJet450",triggerResult->at(i));
	if( triggerName->at(i).compare(0,14,"HLT_PFJet500_v")==0 ) fillVariableWithValue("passHLT_PFJet500",triggerResult->at(i));
	if( triggerName->at(i).compare(0,14,"HLT_PFJet550_v")==0 ) fillVariableWithValue("passHLT_PFJet550",triggerResult->at(i));
	if( triggerName->at(i).compare(0,10,"HLT_Mu50_v")==0 ) fillVariableWithValue("passHLT_Mu50",triggerResult->at(i));
	if( triggerName->at(i).compare(0,17,"HLT_AK8PFJet320_v")==0 ) fillVariableWithValue("passHLT_AK8PFJet320",triggerResult->at(i));
	if( triggerName->at(i).compare(0,17,"HLT_AK8PFJet400_v")==0 ) fillVariableWithValue("passHLT_AK8PFJet400",triggerResult->at(i));
	if( triggerName->at(i).compare(0,17,"HLT_AK8PFJet450_v")==0 ) fillVariableWithValue("passHLT_AK8PFJet450",triggerResult->at(i));
	if( triggerName->at(i).compare(0,17,"HLT_AK8PFJet500_v")==0 ) fillVariableWithValue("passHLT_AK8PFJet500",triggerResult->at(i));
	if( triggerName->at(i).compare(0,17,"HLT_AK8PFJet550_v")==0 ) fillVariableWithValue("passHLT_AK8PFJet550",triggerResult->at(i));
	if( triggerName->at(i).compare(0,24,"HLT_CaloJet500_NoJetID_v")==0 ) fillVariableWithValue("passHLT_CaloJet500_NoJetID",triggerResult->at(i));
	if( triggerName->at(i).compare(0,24,"HLT_CaloJet550_NoJetID_v")==0 ) fillVariableWithValue("passHLT_CaloJet550_NoJetID",triggerResult->at(i));

     }


     //Noise filters
     fillVariableWithValue("passFilter_goodVertices",passFilter_goodVertices);
     fillVariableWithValue("passFilter_globalSuperTightHalo2016",passFilter_globalSuperTightHalo2016);
     fillVariableWithValue("passFilter_HBHENoise",passFilter_HBHENoise);
     fillVariableWithValue("passFilter_HBHENoiseIso",passFilter_HBHENoiseIso);
     fillVariableWithValue("passFilter_EcalDeadCellTriggerPrimitive",passFilter_EcalDeadCellTriggerPrimitive);
     fillVariableWithValue("passFilter_BadPFMuon",passFilter_BadPFMuon);
     fillVariableWithValue("passFilter_BadPFMuonDz",passFilter_BadPFMuonDz);
     fillVariableWithValue("passFilter_BadChargedCandidate",passFilter_BadChargedCandidate);
     fillVariableWithValue("passFilter_eeBadSc",passFilter_eeBadSc);
     fillVariableWithValue("passFilter_ecalBadCalib",passFilter_ecalBadCalib);
     fillVariableWithValue("passFilter_hfNoisyHits",passFilter_hfNoisyHits);


     //Evaluate cuts (but do not apply them)
     evaluateCuts();
     

     fillReducedSkimTree();

   } // End loop over events


   std::cout << "analysisClass::Loop() ends" <<std::endl;   
}

