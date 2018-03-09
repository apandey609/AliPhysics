

#ifndef ALIANALYSISTASKMLTREEMAKEREff_H
#define ALIANALYSISTASKMLTREEMAKEREff_H
class TH1F;
class TList;
class TH2D;
class TH3D;
class AliESDtrackCuts;


#include "AliAnalysisTaskSE.h"
#ifndef ALIANALYSISTASKSE_H
#endif

// Authors: Sebastian Lehner (SMI Vienna) - selehner@cern.ch


class AliAnalysisTaskMLTreeMakerEff : public AliAnalysisTaskSE {
 public:
  AliAnalysisTaskMLTreeMakerEff(const char *name);
  AliAnalysisTaskMLTreeMakerEff();
  virtual ~AliAnalysisTaskMLTreeMakerEff(){} 
   
  
  virtual void   UserCreateOutputObjects();
  virtual void   UserExec(Option_t *option);
  virtual void   FinishTaskOutput();
  virtual void   Terminate(Option_t *);
  
  void SetupTrackCuts();
  void SetupEventCuts();
  
  AliDielectronEventCuts* eventCuts;
  AliDielectronVarCuts *eventplaneCuts;
  AliAnalysisFilter* evfilter;
  
  AliDielectronVarCuts* trcuts;
  AliDielectronTrackCuts *trfilter;
  AliDielectronPID *pidcuts;
  AliDielectronCutGroup* cuts;
  AliAnalysisFilter* filter; 
  
    AliDielectronVarManager* varManager;
  
//  void SetCentralityPercentileRange(Double_t min, Double_t max){
//    fCentralityPercentileMin = min;
//    fCentralityPercentileMax = max;
//
//    Printf("Thresholds Set");
//    Printf("pT = %f - %f",fPtMin,fPtMax);
//    Printf("eta = %f - %f",fEtaMin,fEtaMax);
//    Printf("cent = %f - %f",fCentralityPercentileMin,fCentralityPercentileMax);
//  }
//
//  void SetPtRange(Double_t min, Double_t max){
//    fPtMin = min;
//    fPtMax = max;
//
//    Printf("Thresholds Set");
//    Printf("pT = %f - %f",fPtMin,fPtMax);
//    Printf("eta = %f - %f",fEtaMin,fEtaMax);
//    Printf("cent = %f - %f",fCentralityPercentileMin,fCentralityPercentileMax);
//  }
//
//  void SetEtaRange(Double_t min, Double_t max){
//    fEtaMin = min;
//    fEtaMax = max;
//
//    Printf("Thresholds Set");
//    Printf("pT = %f - %f",fPtMin,fPtMax);
//    Printf("eta = %f - %f",fEtaMin,fEtaMax);
//    Printf("cent = %f - %f",fCentralityPercentileMin,fCentralityPercentileMax);
//  }

  void SetFilterBit(Int_t filterBit){
    fFilterBit = filterBit;
  }
//  
//    void SetLoCuts(Bool_t x){       //use loose cuts?
//    loCuts = x;
//  }

 private:
 
  AliPIDResponse *fPIDResponse;     //! PID response object


  std::vector<Float_t> NCrossedRowsTPC;
  std::vector<Int_t> NClustersTPC;
  std::vector<Int_t> HasSPDfirstHit; 
  std::vector<Double_t> RatioCrossedRowsFindableClusters;  
  std::vector<Int_t> NTPCSignal;    
  


  Int_t fFilterBit;// track cut bit from track selection (default = 96)

//  AliESDtrackCuts* fESDTrackCuts;
  
  std::vector<Double_t> EsigTPC;
  std::vector<Double_t> EsigTOF;
  std::vector<Double_t> EsigITS;
  
  std::vector<Double_t> PsigTPC;
  std::vector<Double_t> PsigTOF;
  std::vector<Double_t> PsigITS;

  std::vector<Double_t> KsigTPC;
  std::vector<Double_t> KsigTOF;
  std::vector<Double_t> KsigITS;
  
  std::vector<Int_t> nITS;
  std::vector<Double_t> nITSshared;
  
  std::vector<Int_t> ITS1S;
  std::vector<Int_t> ITS2S;
  std::vector<Int_t> ITS3S;
  std::vector<Int_t> ITS4S;
  std::vector<Int_t> ITS5S;
  std::vector<Int_t> ITS6S;
  
  std::vector<Double_t> chi2ITS;
//  std::vector<Double_t> chi2TPC;
  std::vector<Double_t> chi2GlobalPerNDF;
  std::vector<Double_t> chi2GlobalvsTPC;
  Int_t	fCutMaxChi2TPCConstrainedVsGlobalVertexType;
  
  
  
  std::vector<Double_t> ProdVx;
  std::vector<Double_t> ProdVy;
  std::vector<Double_t> ProdVz;
  
  std::vector<Float_t> dcar;    //DCA
  std::vector<Float_t> dcaz;
  
  Int_t runn;
  Int_t n;
  Double_t cent;
  
  Double_t IsEventAccepted(AliESDEvent *event);
  Int_t GetAcceptedTracks(AliVEvent *event, Double_t gCentrality);
  
  AliAnalysisTaskMLTreeMakerEff(const AliAnalysisTaskMLTreeMakerEff&); // not implemented

  AliAnalysisTaskMLTreeMakerEff& operator=(const AliAnalysisTaskMLTreeMakerEff&); // not implemented

  TList *fList;//output list for QA histograms

//  Double_t fCentralityPercentileMin;// minimum centrality threshold (default = 0)
//  Double_t fCentralityPercentileMax;// maximum centrality threshold (default = 80)
//
//  Double_t fPtMin;// minimum pT threshold (default = 0)
//  Double_t fPtMax;// maximum pT threshold (default = 1000)
//  Double_t fEtaMin;// minimum eta threshold (default = -10)
//  Double_t fEtaMax;// maximum eta threshold (default = 10)
  
  Double_t fPtMinMC;// minimum pT threshold (default = 0)
  Double_t fPtMaxMC;// maximum pT threshold (default = 1000)
  Double_t fEtaMinMC;// minimum eta threshold (default = -10)
  Double_t fEtaMaxMC;// maximum eta threshold (default = 10)
  
//  Int_t gMultiplicity;
  Int_t mcTrackIndex;
  AliMCEvent* fMcArray; 
 
  std::vector<Double_t> MCpt;
  std::vector<Double_t> MCeta;
  std::vector<Double_t> MCphi;
  
  std::vector<Double_t> MCvertx;
  std::vector<Double_t> MCverty;
  std::vector<Double_t> MCvertz;
  
  std::vector<Double_t> pt;
  std::vector<Double_t> eta;
  std::vector<Double_t> phi;
  std::vector<Int_t> charge;
  std::vector<Int_t> enh;  
  
  Double_t vertx;
  Double_t verty;
  Double_t vertz; 
 
  Bool_t hasMC;
  Bool_t Rej;
  
  std::vector<Int_t> pdg;
  std::vector<Int_t> pdgmother;
  std::vector<Int_t> hasmother;
  std::vector<Int_t> motherlabel;
  std::vector<Int_t> enh;  
  std::vector<Int_t> charge;
  std::vector<Int_t> IsRec;
  std::vector<Int_t> pass;
  std::vector<Int_t> IsPrim;
  Bool_t Rej;

  
  TTree* fTree;
  TH1F* fQAHist;

  ClassDef(AliAnalysisTaskMLTreeMakerEff, 1); //

};



#endif

