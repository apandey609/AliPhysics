//_________________________________________________________________________
//  Utility Class for transverse energy studies
//  Base class for MC analysis
//  - MC output
//  implementation file
//
//*-- Authors: Oystein Djuvsland (Bergen), David Silvermyr (ORNL)
//_________________________________________________________________________

#include "AliAnalysisEtMonteCarlo.h"
#include "AliAnalysisEtCuts.h"
#include "AliAnalysisEtSelector.h"
#include "AliAnalysisEtSelector.h"
#include "AliESDtrack.h"
#include "AliStack.h"
#include "AliVEvent.h"
#include "AliMCEvent.h"
#include "AliESDEvent.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TParticle.h"
#include "AliGenHijingEventHeader.h"
#include "AliGenPythiaEventHeader.h"
#include "TList.h"
#include "AliESDCaloCluster.h"
#include "AliLog.h"
#include <iostream>
#include <AliCentrality.h>
#include "AliPHOSGeoUtils.h"
#include "AliPHOSGeometry.h"
#include "TFile.h"
using namespace std;

ClassImp(AliAnalysisEtMonteCarlo);


// ctor
AliAnalysisEtMonteCarlo::AliAnalysisEtMonteCarlo():AliAnalysisEt()
    ,fImpactParameter(0)
    ,fNcoll(0)
    ,fNpart(0)
    ,fPrimaryTree(0)
    ,fTotEtWithSecondaryRemoved(0)
    ,fTotEtSecondaryFromEmEtPrimary(0)
    ,fTotEtSecondary(0)
    ,fPrimaryCode(0)
    ,fPrimaryCharge(0)
    ,fPrimaryE(0)
    ,fPrimaryEt(0)
    ,fPrimaryPx(0)
    ,fPrimaryPy(0)
    ,fPrimaryPz(0)
    ,fPrimaryVx(0)
    ,fPrimaryVy(0)
    ,fPrimaryVz(0)
    ,fPrimaryAccepted(0)
    ,fPrimaryMatched(0)
    ,fDepositedCode(0)
    ,fDepositedE(0)
    ,fDepositedEt(0)
    ,fDepositedCharge(0)
    ,fDepositedVx(0)
    ,fDepositedVy(0)
    ,fDepositedVz(0)
    ,fSecondary(kFALSE)
    ,fReconstructedE(0)
    ,fReconstructedEt(0)
    ,fTotPx(0)
    ,fTotPy(0)
    ,fTotPz(0)
    ,fClusterMult(0)
    ,fHistDecayVertexNonRemovedCharged(0)
    ,fHistDecayVertexRemovedCharged(0)
    ,fHistDecayVertexNonRemovedNeutral(0)
    ,fHistDecayVertexRemovedNeutral(0)

    ,fHistRemovedOrNot(0)
    ,fHistEtNonRemovedProtons(0)
    ,fHistEtNonRemovedAntiProtons(0)
    ,fHistEtNonRemovedPiPlus(0)
    ,fHistEtNonRemovedPiMinus(0)
    ,fHistEtNonRemovedKaonPlus(0)
    ,fHistEtNonRemovedKaonMinus(0)
    ,fHistEtNonRemovedK0s(0)
    ,fHistEtNonRemovedK0L(0)
    ,fHistEtNonRemovedLambdas(0)
    ,fHistEtNonRemovedElectrons(0)
    ,fHistEtNonRemovedPositrons(0)
    ,fHistEtNonRemovedMuPlus(0)
    ,fHistEtNonRemovedMuMinus(0)
    ,fHistEtNonRemovedNeutrons(0)
    ,fHistEtNonRemovedAntiNeutrons(0)
    ,fHistEtNonRemovedGammas(0)
    ,fHistEtNonRemovedGammasFromPi0(0)
    ,fHistEtRemovedGammas(0)
    ,fHistEtRemovedNeutrons(0)
    ,fHistEtRemovedAntiNeutrons(0)
    ,fHistEtRemovedCharged(0)
    ,fHistEtRemovedNeutrals(0)
    ,fHistEtNonRemovedCharged(0)
    ,fHistEtNonRemovedNeutrals(0)
    ,fHistMultNonRemovedProtons(0)
    ,fHistMultNonRemovedAntiProtons(0)
    ,fHistMultNonRemovedPiPlus(0)
    ,fHistMultNonRemovedPiMinus(0)
    ,fHistMultNonRemovedKaonPlus(0)
    ,fHistMultNonRemovedKaonMinus(0)
    ,fHistMultNonRemovedK0s(0)
    ,fHistMultNonRemovedK0L(0)
    ,fHistMultNonRemovedLambdas(0)
    ,fHistMultNonRemovedElectrons(0)
    ,fHistMultNonRemovedPositrons(0)
    ,fHistMultNonRemovedMuPlus(0)
    ,fHistMultNonRemovedMuMinus(0)
    ,fHistMultNonRemovedNeutrons(0)
    ,fHistMultNonRemovedAntiNeutrons(0)
    ,fHistMultNonRemovedGammas(0)
    ,fHistMultRemovedGammas(0)
    ,fHistMultRemovedNeutrons(0)
    ,fHistMultRemovedAntiNeutrons(0)
    ,fHistMultRemovedCharged(0)
    ,fHistMultRemovedNeutrals(0)
    ,fHistMultNonRemovedCharged(0)
    ,fHistMultNonRemovedNeutrals(0)
    ,fHistTrackMultvsNonRemovedCharged(0)
    ,fHistTrackMultvsNonRemovedNeutral(0)
    ,fHistTrackMultvsRemovedGamma(0)
    ,fHistClusterMultvsNonRemovedCharged(0)
    ,fHistClusterMultvsNonRemovedNeutral(0)
    ,fHistClusterMultvsRemovedGamma(0)
    ,fHistMultvsNonRemovedChargedE(0)
    ,fHistMultvsNonRemovedNeutralE(0)
    ,fHistMultvsRemovedGammaE(0)
    ,fEtNonRemovedProtons(0)
    ,fEtNonRemovedAntiProtons(0)
    ,fEtNonRemovedPiPlus(0)
    ,fEtNonRemovedPiMinus(0)
    ,fEtNonRemovedKaonPlus(0)
    ,fEtNonRemovedKaonMinus(0)
    ,fEtNonRemovedK0S(0)
    ,fEtNonRemovedK0L(0)
    ,fEtNonRemovedLambdas(0)
    ,fEtNonRemovedElectrons(0)
    ,fEtNonRemovedPositrons(0)
    ,fEtNonRemovedMuMinus(0)
    ,fEtNonRemovedMuPlus(0)
    ,fEtNonRemovedGammas(0)
    ,fEtNonRemovedGammasFromPi0(0)
    ,fEtNonRemovedNeutrons(0)
    ,fEtNonRemovedAntiNeutrons(0)
    ,fEtRemovedProtons(0)
    ,fEtRemovedAntiProtons(0)
    ,fEtRemovedPiPlus(0)
    ,fEtRemovedPiMinus(0)
    ,fEtRemovedKaonPlus(0)
    ,fEtRemovedKaonMinus(0)
    ,fEtRemovedK0s(0)
    ,fEtRemovedK0L(0)
    ,fEtRemovedLambdas(0)
    ,fEtRemovedElectrons(0)
    ,fEtRemovedPositrons(0)
    ,fEtRemovedMuMinus(0)
    ,fEtRemovedMuPlus(0)
    ,fEtRemovedGammasFromPi0(0)
    ,fEtRemovedGammas(0)
    ,fEtRemovedNeutrons(0)
    ,fEtRemovedAntiNeutrons(0)
    ,fMultNonRemovedProtons(0)
    ,fMultNonRemovedAntiProtons(0)
    ,fMultNonRemovedPiPlus(0)
    ,fMultNonRemovedPiMinus(0)
    ,fMultNonRemovedKaonPlus(0)
    ,fMultNonRemovedKaonMinus(0)
    ,fMultNonRemovedK0s(0)
    ,fMultNonRemovedK0L(0)
    ,fMultNonRemovedLambdas(0)
    ,fMultNonRemovedElectrons(0)
    ,fMultNonRemovedPositrons(0)
    ,fMultNonRemovedMuMinus(0)
    ,fMultNonRemovedMuPlus(0)
    ,fMultNonRemovedGammas(0)
    ,fMultNonRemovedNeutrons(0)
    ,fMultNonRemovedAntiNeutrons(0)
    ,fMultRemovedProtons(0)
    ,fMultRemovedAntiProtons(0)
    ,fMultRemovedPiPlus(0)
    ,fMultRemovedPiMinus(0)
    ,fMultRemovedKaonPlus(0)
    ,fMultRemovedKaonMinus(0)
    ,fMultRemovedK0s(0)
    ,fMultRemovedK0L(0)
    ,fMultRemovedLambdas(0)
    ,fMultRemovedElectrons(0)
    ,fMultRemovedPositrons(0)
    ,fMultRemovedMuMinus(0)
    ,fMultRemovedMuPlus(0)
    ,fMultRemovedGammas(0)
    ,fMultRemovedNeutrons(0)
    ,fMultRemovedAntiNeutrons(0)
    ,fTrackMultInAcc(0)
    ,fHistDxDzNonRemovedCharged(0)
    ,fHistDxDzRemovedCharged(0)
    ,fHistDxDzNonRemovedNeutral(0)
    ,fHistDxDzRemovedNeutral(0)
    ,fHistPiPlusMult(0)
    ,fHistPiMinusMult(0)
    ,fHistPiZeroMult(0)
    ,fHistPiPlusMultAcc(0)
    ,fHistPiMinusMultAcc(0)
    ,fHistPiZeroMultAcc(0)
//     ,fPiPlusMult(0)
//     ,fPiMinusMult(0)
    ,fPiZeroMult(0)
    ,fPiPlusMultAcc(0)
    ,fPiMinusMultAcc(0)
    ,fPiZeroMultAcc(0)
    ,fNeutralRemoved(0)
    ,fChargedRemoved(0)
    ,fChargedNotRemoved(0)
    ,fNeutralNotRemoved(0)
    ,fGammaRemoved(0)
    ,fSecondaryNotRemoved(0)
    ,fEnergyNeutralRemoved(0)
    ,fEnergyChargedRemoved(0)
    ,fEnergyChargedNotRemoved(0)
    ,fEnergyNeutralNotRemoved(0)
    ,fEnergyGammaRemoved(0)
    ,fNClusters(0)
    ,fTotNeutralEtAfterMinEnergyCut(0)
    ,fHistGammasFound(0)
    ,fHistGammasGenerated(0)
{
}

// dtor
AliAnalysisEtMonteCarlo::~AliAnalysisEtMonteCarlo()
{   //Destructor

  if(fPrimaryTree){
    fPrimaryTree->Clear();
    delete fPrimaryTree;
  }
    delete fHistDecayVertexNonRemovedCharged; // Decay vertex for non-removed charged particles
    delete fHistDecayVertexRemovedCharged; // Decay vertex for non-removed charged particles
    delete fHistDecayVertexNonRemovedNeutral; // Decay vertex for non-removed charged particles
    delete fHistDecayVertexRemovedNeutral; // Decay vertex for non-removed charged particles

    delete fHistRemovedOrNot; // If charged/neutral particles were removed or not

    delete fHistEtNonRemovedProtons; // enter comment here
    delete fHistEtNonRemovedAntiProtons; // enter comment here
    delete fHistEtNonRemovedPiPlus; // enter comment here
    delete fHistEtNonRemovedPiMinus; // enter comment here
    delete fHistEtNonRemovedKaonPlus; // enter comment here
    delete fHistEtNonRemovedKaonMinus; // enter comment here
    delete fHistEtNonRemovedK0s; // enter comment here
    delete fHistEtNonRemovedK0L; // enter comment here
    delete fHistEtNonRemovedLambdas; // enter comment here
    delete fHistEtNonRemovedElectrons; // enter comment here
    delete fHistEtNonRemovedPositrons; // enter comment here
    delete fHistEtNonRemovedMuPlus; // enter comment here
    delete fHistEtNonRemovedMuMinus; // enter comment here
    delete fHistEtNonRemovedNeutrons; // enter comment here
    delete fHistEtNonRemovedAntiNeutrons; // enter comment here
    delete fHistEtNonRemovedGammas; // enter comment here
    delete fHistEtNonRemovedGammasFromPi0; // enter comment here

    delete fHistEtRemovedGammas; // enter comment here
    delete fHistEtRemovedNeutrons; // enter comment here
    delete fHistEtRemovedAntiNeutrons; // enter comment here


    delete fHistMultNonRemovedProtons; // enter comment here
    delete fHistMultNonRemovedAntiProtons; // enter comment here
    delete fHistMultNonRemovedPiPlus; // enter comment here
    delete fHistMultNonRemovedPiMinus; // enter comment here
    delete fHistMultNonRemovedKaonPlus; // enter comment here
    delete fHistMultNonRemovedKaonMinus; // enter comment here
    delete fHistMultNonRemovedK0s; // enter comment here
    delete fHistMultNonRemovedK0L; // enter comment here
    delete fHistMultNonRemovedLambdas; // enter comment here
    delete fHistMultNonRemovedElectrons; // enter comment here
    delete fHistMultNonRemovedPositrons; // enter comment here
    delete fHistMultNonRemovedMuPlus; // enter comment here
    delete fHistMultNonRemovedMuMinus; // enter comment here
    delete fHistMultNonRemovedNeutrons; // enter comment here
    delete fHistMultNonRemovedAntiNeutrons; // enter comment here
    delete fHistMultNonRemovedGammas; // enter comment here

    delete fHistMultRemovedGammas; // enter comment here
    delete fHistMultRemovedNeutrons; // enter comment here
    delete fHistMultRemovedAntiNeutrons; // enter comment here

    delete fHistTrackMultvsNonRemovedCharged; // enter comment here
    delete fHistTrackMultvsNonRemovedNeutral; // enter comment here
    delete fHistTrackMultvsRemovedGamma; // enter comment here

    delete fHistClusterMultvsNonRemovedCharged; // enter comment here
    delete fHistClusterMultvsNonRemovedNeutral; // enter comment here
    delete fHistClusterMultvsRemovedGamma; // enter comment here

    delete fHistMultvsNonRemovedChargedE; // enter comment here
    delete fHistMultvsNonRemovedNeutralE; // enter comment here
    delete fHistMultvsRemovedGammaE; // enter comment here
    delete fHistDxDzNonRemovedCharged; // enter comment here
    delete fHistDxDzRemovedCharged; // enter comment here
    delete fHistDxDzNonRemovedNeutral; // enter comment here
    delete fHistDxDzRemovedNeutral; // enter comment here

    delete fHistPiPlusMult; // enter comment here
    delete fHistPiMinusMult; // enter comment here
    delete fHistPiZeroMult; // enter comment here

    delete fHistPiPlusMultAcc; // enter comment here
    delete fHistPiMinusMultAcc; // enter comment here
    delete fHistPiZeroMultAcc; // enter comment here
}

Int_t AliAnalysisEtMonteCarlo::AnalyseEvent(AliVEvent* ev)
{   // analyse MC event
    ResetEventValues();

    
    fPiPlusMult = 0;
    fPiMinusMult = 0;
    fPiZeroMult = 0;
    if (fCentrality)
    {
        fCentClass = fCentrality->GetCentralityClass10(fCentralityMethod);

    }

    // Get us an mc event
    if (!ev) {
        AliFatal("ERROR: Event does not exist");
        return 0;
    }
    AliMCEvent *event = dynamic_cast<AliMCEvent*>(ev);
    if (!event) {
        AliFatal("ERROR: MC Event does not exist");
        return 0;
    }

    Double_t protonMass =fgProtonMass;

    // Hijing header
    AliGenEventHeader* genHeader = event->GenEventHeader();
    if (!genHeader) {
        Printf("ERROR: Event generation header does not exist");
        return 0;
    }
    AliGenHijingEventHeader* hijingGenHeader = dynamic_cast<AliGenHijingEventHeader*>(genHeader);
    if (hijingGenHeader) {
        fImpactParameter = hijingGenHeader->ImpactParameter();
        fNcoll = hijingGenHeader->HardScatters(); // or should this be some combination of NN() NNw() NwN() NwNw() ?
        fNpart = hijingGenHeader->ProjectileParticipants() + hijingGenHeader->TargetParticipants();
    }

    // Let's play with the stack!
    AliStack *stack = event->Stack();

    Int_t nPrim = stack->GetNtrack();

    Int_t partCount = 0;
    for (Int_t iPart = 0; iPart < nPrim; iPart++)
    {

        TParticle *part = stack->Particle(iPart);
	
	

        if (!part)
        {
            Printf("ERROR: Could not get particle %d", iPart);
            continue;
        }
        TParticlePDG *pdg = part->GetPDG(0);

        if (!pdg)
        {
            Printf("ERROR: Could not get particle PDG %d", iPart);
            continue;
        }

        Double_t particleMassPart = 0; //The mass part in the Et calculation for this particle
        Int_t code = pdg->PdgCode();
	
	if(stack->IsPhysicalPrimary(iPart))
	{
	  fTotPx += part->Px();
	  fTotPy += part->Py();
	  fTotPz += part->Pz();
	}
	
        // Check for reasonable (for now neutral and singly charged) charge on the particle
        if (fSelector->CutNeutralMcParticle(iPart,*stack,*pdg))
        {

            fMultiplicity++;
//             PrintFamilyTree(iPart, stack);
//
            if (TMath::Abs(part->Eta()) < fCuts->GetCommonEtaCut())
            {
                //Printf("Particle with eta: %f, pid: %d", part->Eta(), code);
                // calculate E_T
                if (
                    TMath::Abs(code) == fgProtonCode ||
                    TMath::Abs(code) == fgNeutronCode ||
                    TMath::Abs(code) == fgLambdaCode ||
                    TMath::Abs(code) == fgXiCode ||
                    TMath::Abs(code) == fgXi0Code ||
                    TMath::Abs(code) == fgOmegaCode
                )
                {
                    if (code > 0) {
                        particleMassPart = - protonMass;
                    }
                    if (code < 0) {
                        particleMassPart = protonMass;
                    }
                }
                Double_t et = part->Energy() * TMath::Sin(part->Theta()) + particleMassPart;


                // Fill up total E_T counters for each particle species
                if (code == fgProtonCode || code == fgAntiProtonCode)
                {
                }
                if (code == fgPiPlusCode || code == fgPiMinusCode)
                {
                    if (code == fgPiPlusCode)
                    {
                    }
                    else
                    {
                    }
                }
                if (code == fgGammaCode)
                {
                }
                if (code == fgKPlusCode)
                {
                }
                if(code == fgKMinusCode)
                {
                }
                if (code == fgMuPlusCode || code == fgMuMinusCode)
                {
                }
                if (code == fgEPlusCode || code == fgEMinusCode)
                {
                }
                // some neutrals also
                if (code == fgNeutronCode)
                {
                }
                if (code == fgAntiNeutronCode)
                {
                }
                if (code == fgGammaCode)
                {
                }

                // Neutral particles
                //if (TMath::Abs(pdg->Charge() - fCuts->GetMonteCarloNeutralParticle()) <1e-3 )

                if(code == fgGammaCode || code == fgPi0Code || code == fgEtaCode)
                {
		//  PrintFamilyTree(iPart,stack);
                    //Printf("Gamma, phi: %f, eta: %f, phi cut min: %f, phi cut max: %f, eta cut: %f", part->Phi(), part->Eta(), fPhiMinCutAcc, fPhiMaxCutAcc, fEtaCutAcc);
                    //if (et > fCuts->GetCommonClusterEnergyCut()) fTotNeutralEt += et;

                    // inside EMCal acceptance

                    //if (TMath::Abs(part->Eta()) < fEtaCutAcc && part->Phi() < fPhiMaxCutAcc && part->Phi() > fPhiMinCutAcc)

                    if(fSelector->CutGeometricalAcceptance(*part) )
                    {
                        fNeutralMultiplicity++;
                        fTotNeutralEt += et;
                        if(fSelector->CutMinEnergy(*part))
                        {
                            fTotNeutralEtAfterMinEnergyCut += et;
                        }
                        if (part->Energy() > 0.05) partCount++;
                    }
                }
                //Charged particles
                else if (TMath::Abs( pdg->Charge() - fCuts->GetMonteCarloNeutralParticle())>1e-3 )
                {

                    // inside EMCal acceptance
                    if (fSelector->CutGeometricalAcceptance(*part))
                    {

                        fChargedMultiplicity++;

                        fTotChargedEt += et;

                        if (code == fgProtonCode || code == fgAntiProtonCode)
                        {
                        }
                        if (code == fgPiPlusCode || code == fgPiMinusCode)
                        {
                        }
                        if (code == fgKPlusCode || code == fgKMinusCode)
                        {
                        }
                        if (code == fgMuPlusCode || code == fgMuMinusCode)
                        {
                        }

                        if (code == fgEPlusCode || code == fgEMinusCode)
                        {
                            fTotNeutralEt += et; // calling electrons neutral
                            fTotChargedEt -= et;
                        }
                    } // inside EMCal acceptance

                    if (TrackHitsCalorimeter(part)) // magnetic field info not filled?
                    {
                        if (pdg->Charge() > 0) fHistPhivsPtPos->Fill(part->Phi(),part->Pt());
                        else fHistPhivsPtNeg->Fill(part->Phi(), part->Pt());
                    }
                }
            }

        }
    }
   // std::cout << "Total: p_x = " << fTotPx << ", p_y = " << fTotPy << ", p_z = " << fTotPz << std::endl;
    fTotEt = fTotChargedEt + fTotNeutralEt;
    //fTotEtAcc = fTotChargedEtAcc + fTotNeutralEtAcc;//
    //std::cout << "Event done! # of particles: " << partCount << std::endl;
    return 0;
}
//Int_t AliAnalysisEtMonteCarlo::AnalyseEvent(AliMCEvent* mcEvent,AliESDEvent* realEvent)
Int_t AliAnalysisEtMonteCarlo::AnalyseEvent(AliVEvent* ev,AliVEvent* ev2)
{   // analyse MC and real event info
    //if(!mcEvent || !realEvent){
    if (!ev || !ev2) {
        AliFatal("ERROR: Event does not exist");
        return 0;
    }
    AliAnalysisEt::AnalyseEvent(ev);
    AliMCEvent *mcEvent = dynamic_cast<AliMCEvent*>(ev);
    AliESDEvent *realEvent = dynamic_cast<AliESDEvent*>(ev2);
    if (!mcEvent || !realEvent) {
        AliFatal("ERROR: mcEvent or realEvent does not exist");
       
    }

    std::vector<Int_t> foundGammas;
    
    fSelector->SetEvent(realEvent);

    AnalyseEvent(ev);

    AliStack *stack = mcEvent->Stack();

    // get all detector clusters
    //  TRefArray* caloClusters = new TRefArray();

//    if (fDetector == fCuts->GetDetectorEmcal()) realEvent->GetEMCALClusters( caloClusters );
    //else if (fDetector == fCuts->GetDetectorPhos()) realEvent->GetPHOSClusters( caloClusters );
    //else {
    //AliFatal("Detector ID has not been specified");
    //return -1;
//    }

    TRefArray *caloClusters = fSelector->GetClusters();

    Int_t nCluster = caloClusters->GetEntries();
    fClusterMult = nCluster;
    fNClusters = 0;
    // loop the clusters
    for (int iCluster = 0; iCluster < nCluster; iCluster++ )
    {
        Int_t cf = 0;
        AliESDCaloCluster* caloCluster = ( AliESDCaloCluster* )caloClusters->At( iCluster );
        //Float_t caloE = caloCluster->E();

        fNClusters++;
        const UInt_t iPart = (UInt_t)TMath::Abs(caloCluster->GetLabel());
        TParticle *part  =  stack->Particle(iPart);

        if (!part)
        {
            Printf("No MC particle %d", iCluster);
            continue;
        }

        int primIdx = iPart;
        if (!stack->IsPhysicalPrimary(iPart)) // check whether particle is primary. we keep secondary electron and gamma for testing.
        {
            primIdx = GetPrimMother(iPart, stack);
	    if(primIdx != stack->GetPrimary(iPart))
	    {
	      //std::cout << primIdx << " = " << stack->GetPrimary(iPart) << std::endl;
	      //PrintFamilyTree(iPart, stack);
	    }
	     
            if(primIdx < 0)
            {
                std::cout << "What!? No primary?" << std::endl;
                continue;
            }

        } // end of primary particle check
        
        const int primCode = stack->Particle(primIdx)->GetPdgCode();
        TParticlePDG *pdg = part->GetPDG();
        if (!pdg)
        {
            Printf("ERROR: Could not get particle PDG %d", iPart);
            continue;
        }

        Int_t code = pdg->PdgCode();
	if(primCode == fgGammaCode) 
	{
	  
	 
	  if(fSelector->CutDistanceToBadChannel(*caloCluster))//&&fSelector->CutGeometricalAcceptance(*(stack->Particle(primIdx))))
	  {
//	    std::cout << "Gamma primary: " << primIdx << std::endl;
	    foundGammas.push_back(primIdx); 
	  }
	  
	}
        fCutFlow->Fill(cf++);
        if(!fSelector->CutDistanceToBadChannel(*caloCluster)) continue;
        Double_t clEt = CalculateTransverseEnergy(*caloCluster);
//	if(code == fgK0SCode) std::cout << "K0 energy: " << caloCluster->E() << std::endl;
        if(!fSelector->CutMinEnergy(*caloCluster)) continue;
        fCutFlow->Fill(cf++);
        Float_t pos[3];
	//PrintFamilyTree(
        caloCluster->GetPosition(pos);
        TVector3 cp(pos);

        TParticle *primPart = stack->Particle(primIdx);
        fPrimaryCode = primPart->GetPdgCode();
        fPrimaryCharge = primPart->GetPDG()->Charge();

        fPrimaryE = primPart->Energy();
        fPrimaryEt = primPart->Energy()*TMath::Sin(primPart->Theta());

        fPrimaryPx = primPart->Px();
        fPrimaryPy = primPart->Py();
        fPrimaryPz = primPart->Pz();

        fPrimaryVx = primPart->Vx();
        fPrimaryVy = primPart->Vy();
        fPrimaryVz = primPart->Vz();

        fPrimaryAccepted = false;
        fPrimaryMatched = false;

        fDepositedCode = part->GetPdgCode();
	fDepositedE = part->Energy();
        fDepositedEt = part->Energy()*TMath::Sin(part->Theta());
        fDepositedCharge = part->GetPDG()->Charge();

        fDepositedVx = part->Vx();
        fDepositedVy = part->Vy();
        fDepositedVz = part->Vz();

	//fSecondary = fSelector->FromSecondaryInteraction(*primPart, *stack);
	fSecondary =fSelector->FromSecondaryInteraction(*part, *stack);
	if(fSecondary) 
	{
	  //std::cout << "Have secondary!" << std::endl;
	  //PrintFamilyTree(iPart, stack);
	}
	fReconstructedE = caloCluster->E();
	fReconstructedEt = caloCluster->E()*TMath::Sin(cp.Theta());
        //if(caloCluster->GetEmcCpvDistance() < fTrackDistanceCut)
	
	pdg = primPart->GetPDG(0);
	code = primPart->GetPdgCode();
        //if (TMath::Abs(caloCluster->GetTrackDx()) < 5 && TMath::Abs(caloCluster->GetTrackDz()) < 5)
        if(!fSelector->CutTrackMatching(*caloCluster))
        {
	    fPrimaryMatched = true;
            if (pdg->Charge() != 0)
            {
                fChargedRemoved++;
                fEnergyChargedRemoved += clEt;
                fHistRemovedOrNot->Fill(0.0, fCentClass);
                fHistDxDzRemovedCharged->Fill(caloCluster->GetTrackDx(), caloCluster->GetTrackDz());
             
            }
            else
            {
		if(code==fgGammaCode)
		{
		  fGammaRemoved++;
		  fGammaRemovedEt+=clEt; 
		 
		}
		else
		{
		  fNeutralRemoved++;
		  fEnergyNeutralRemoved += clEt;
		  fHistRemovedOrNot->Fill(1.0, fCentClass);
		  fHistDxDzRemovedNeutral->Fill(caloCluster->GetTrackDx(), caloCluster->GetTrackDz());
		}
            }
        }
        else
        {
            fPrimaryAccepted = true;
	    fPrimaryMatched = false;
            fCutFlow->Fill(cf++);
            if (pdg->Charge() != 0)
            {

		if(fSecondary)
		{
		  fSecondaryNotRemoved++;
		}
		else
		{
		  fChargedNotRemoved++;
		  fEnergyChargedNotRemoved += clEt;
		  fHistRemovedOrNot->Fill(2.0, fCentClass);
		  fHistDxDzNonRemovedCharged->Fill(caloCluster->GetTrackDx(), caloCluster->GetTrackDz());
		  PrintFamilyTree(iPart, stack);
		}
            }
            else
            {
                if(!fSecondary)
		{
		  fNeutralNotRemoved++;
		  fEnergyNeutralNotRemoved += clEt;
		  fHistRemovedOrNot->Fill(3.0, fCentClass);
		  fHistDxDzNonRemovedNeutral->Fill(caloCluster->GetTrackDx(), caloCluster->GetTrackDz());
		}
		else
		{
//  		  PrintFamilyTree(iPart, stack);
		}
               // if(TMath::Abs(part->Vx()) < 1.0 && TMath::Abs(part->Vy()) < 1.0 && TMath::Abs(part->Vz()) < 20 && fSelector->IsEmEtParticle(primCode))
		if(fSecondary && fSelector->IsEmEtParticle(primCode))
                {
                    fTotEtSecondaryFromEmEtPrimary += clEt;
		    fSecondaryNotRemoved++;
                }
                else if(fSelector->IsEmEtParticle(primCode))
                {
                    fTotEtWithSecondaryRemoved += clEt;
// 		    PrintFamilyTree(iPart, stack);
		    
                }
                else		
		{
                    //fTotEtSecondary += clEt;
// 		    PrintFamilyTree(iPart,stack);
                }
                //code = stack->Particle(primIdx)->GetPdgCode();
                if (code == fgGammaCode && !fSecondary)
                {
                    fEtNonRemovedGammas += clEt;
                    fMultNonRemovedGammas++;
		    fNeutralNotRemoved--;
		    fEnergyNeutralNotRemoved -= clEt;
		    //PrintFamilyTree(iPart, stack);
//                    if (pdgMom)
                    //                  {
                    //                    if (TMath::Abs(pdgMom->PdgCode()) == fgPi0Code || TMath::Abs(pdgMom->PdgCode()) == fgEtaCode || TMath::Abs(pdgMom->PdgCode()) == 331)
                    //                  {
//			std::cout << "Mother of gamma: " << pdgMom->PdgCode() << " " << pdgMom->GetName() <<  ", E: " << part->Energy() << std::endl;
                    //                    fEtNonRemovedGammasFromPi0 += clEt;
                    //              }
                    //        }
                }
            }
        }
        fPrimaryTree->Fill();
    } // end of loop over clusters


    std::sort(foundGammas.begin(), foundGammas.end());
    for (Int_t iPart = 0; iPart < stack->GetNtrack(); iPart++)
    {

	if(!stack->IsPhysicalPrimary(iPart)) continue;
	
	TParticle *part = stack->Particle(iPart);

        if (!part)
        {
            Printf("ERROR: Could not get particle %d", iPart);
            continue;
        }
        TParticlePDG *pdg = part->GetPDG(0);

        if (!pdg)
        {
            Printf("ERROR: Could not get particle PDG %d", iPart);
            continue;
        }
        
        if(pdg->PdgCode()==fgGammaCode && fSelector->CutGeometricalAcceptance(*part))// TMath::Abs(part->Eta()) < 0.12)
	{
	  fHistGammasGenerated->Fill(part->Energy());
//	  std::cout << "Searching for gammas..." << std::endl;
	  if(std::binary_search(foundGammas.begin(),foundGammas.end(),iPart))
	  {
	    fHistGammasFound->Fill(part->Energy());
	  }
// 	  for(int i = 0; i < foundGammas.size(); i++)
// 	  {
// //	    std::cout << iPart << std::endl;
// 	    if(foundGammas[i] == iPart)
// 	    {
// 	      fHistGammasFound->Fill(part->Energy());
// 	      std::cout << "Match!" << std::endl;
// 	      break;
// 	    }
//	  }
	}
        
    }
    //std::cout << "Distance cut: " << fTrackDistanceCut << std::endl;
    //std::cout << "Number of removed neutrals: " << fNeutralRemoved << std::endl;
    //std::cout << "Number of removed charged: " << fChargedRemoved << std::endl;
    //std::cout << "Number of non-removed charged: " << fChargedNotRemoved << std::endl;
    //std::cout << "Number of non-removed neutral: " << fNeutralNotRemoved << std::endl;

//  std::cout << "Energy of removed neutrals: " << fEnergyNeutralRemoved << std::endl;
//  std::cout << "Energy of removed charged: " << fEnergyChargedRemoved << std::endl;
//  std::cout << "Energy of non-removed charged: " << fEnergyChargedNotRemoved << std::endl;
//  std::cout << "Energy of non-removed neutral: " << fEnergyNeutralNotRemoved << std::endl;

    FillHistograms();
    return 0;
}

void AliAnalysisEtMonteCarlo::Init()
{   // init
    AliAnalysisEt::Init();
}

void AliAnalysisEtMonteCarlo::ResetEventValues()
{   // reset event values
    AliAnalysisEt::ResetEventValues();

    fTotEtSecondary = 0;
    fTotEtSecondaryFromEmEtPrimary = 0;
    fTotEtWithSecondaryRemoved = 0;

    // collision geometry defaults for p+p:
    fImpactParameter = 0;
    fNcoll = 1;
    fNpart = 2;

    fEtNonRemovedProtons = 0;
    fEtNonRemovedAntiProtons = 0;
    fEtNonRemovedPiPlus = 0;
    fEtNonRemovedPiMinus = 0;
    fEtNonRemovedKaonPlus = 0;
    fEtNonRemovedKaonMinus = 0;
    fEtNonRemovedK0S = 0;
    fEtNonRemovedK0L = 0;
    fEtNonRemovedLambdas = 0;
    fEtNonRemovedElectrons = 0;
    fEtNonRemovedPositrons = 0;
    fEtNonRemovedMuPlus = 0;
    fEtNonRemovedMuMinus = 0;
    fEtNonRemovedNeutrons = 0;
    fEtNonRemovedAntiNeutrons = 0;
    fEtNonRemovedGammas = 0;
    fEtNonRemovedGammasFromPi0 = 0;

    fEtRemovedProtons = 0;
    fEtRemovedAntiProtons = 0;
    fEtRemovedPiPlus = 0;
    fEtRemovedPiMinus = 0;
    fEtRemovedKaonPlus = 0;
    fEtRemovedKaonMinus = 0;
    fEtRemovedK0s = 0;
    fEtRemovedK0L = 0;
    fEtRemovedLambdas = 0;
    fEtRemovedElectrons = 0;
    fEtRemovedPositrons = 0;
    fEtRemovedMuPlus = 0;
    fEtRemovedMuMinus = 0;
    fEtRemovedNeutrons = 0;

    fEtRemovedGammasFromPi0 = 0;
    fEtRemovedGammas = 0;
    fEtRemovedNeutrons = 0;
    fEtRemovedAntiNeutrons = 0;

    fMultNonRemovedProtons = 0;
    fMultNonRemovedAntiProtons = 0;
    fMultNonRemovedPiPlus = 0;
    fMultNonRemovedPiMinus = 0;
    fMultNonRemovedKaonPlus = 0;
    fMultNonRemovedKaonMinus = 0;
    fMultNonRemovedK0s = 0;
    fMultNonRemovedK0L = 0;
    fMultNonRemovedLambdas = 0;
    fMultNonRemovedElectrons = 0;
    fMultNonRemovedPositrons = 0;
    fMultNonRemovedMuPlus = 0;
    fMultNonRemovedMuMinus = 0;
    fMultNonRemovedNeutrons = 0;
    fMultNonRemovedAntiNeutrons = 0;
    fMultNonRemovedGammas = 0;

    fMultRemovedProtons = 0;
    fMultRemovedAntiProtons = 0;
    fMultRemovedPiPlus = 0;
    fMultRemovedPiMinus = 0;
    fMultRemovedKaonPlus = 0;
    fMultRemovedKaonMinus = 0;
    fMultRemovedK0s = 0;
    fMultRemovedK0L = 0;
    fMultRemovedLambdas = 0;
    fMultRemovedElectrons = 0;
    fMultRemovedPositrons = 0;
    fMultRemovedMuPlus = 0;
    fMultRemovedMuMinus = 0;

    fMultRemovedGammas = 0;
    fMultRemovedNeutrons = 0;
    fMultRemovedAntiNeutrons = 0;

    fEnergyChargedNotRemoved = 0;
    fEnergyChargedRemoved = 0;
    fEnergyNeutralNotRemoved = 0;
    fEnergyNeutralRemoved = 0;

    fChargedNotRemoved = 0;
    fChargedRemoved = 0;
    fNeutralNotRemoved = 0;
    fNeutralRemoved = 0;
    fGammaRemoved = 0;
    fSecondaryNotRemoved = 0;

    fTrackMultInAcc = 0;

    fTotNeutralEtAfterMinEnergyCut = 0;
  
    fSecondaryNotRemoved = 0;
    
    fTotPx = 0;
    fTotPy = 0;
    fTotPz = 0;
    
    
}

void AliAnalysisEtMonteCarlo::CreateHistograms()
{   // histogram related additions
    AliAnalysisEt::CreateHistograms();
    if (fEventSummaryTree) {
        fEventSummaryTree->Branch("fImpactParameter",&fImpactParameter,"fImpactParameter/D");
        fEventSummaryTree->Branch("fNcoll",&fNcoll,"fNcoll/I");
        fEventSummaryTree->Branch("fNpart",&fNpart,"fNpart/I");
        fEventSummaryTree->Branch("fTotEtWithSecondaryRemoved", &fTotEtWithSecondaryRemoved, "fTotEtWithSecondaryRemoved/D");
        fEventSummaryTree->Branch("fTotEtSecondaryFromEmEtPrimary", &fTotEtSecondaryFromEmEtPrimary, "fTotEtSecondaryFromEmEtPrimary/D");
        fEventSummaryTree->Branch("fTotEtSecondary", &fTotEtSecondary, "fTotEtSecondary/D");
        fEventSummaryTree->Branch("fTotNeutralEtAfterMinEnergyCut", &fTotNeutralEtAfterMinEnergyCut, "fTotNeutralEtAfterMinEnergyCut/D");
        fEventSummaryTree->Branch("fSecondaryNotRemoved", &fSecondaryNotRemoved, "fSecondaryNotRemoved/I");
	fEventSummaryTree->Branch("fChargedNotRemoved", &fChargedNotRemoved, "fChargedNotRemoved/I");
	fEventSummaryTree->Branch("fNeutralNotRemoved", &fNeutralNotRemoved, "fNeutralNotRemoved/I");
	fEventSummaryTree->Branch("fChargedRemoved", &fChargedRemoved, "fChargedRemoved/I");
	fEventSummaryTree->Branch("fNeutralRemoved", &fNeutralRemoved, "fNeutralRemoved/I");
	fEventSummaryTree->Branch("fGammaRemoved", &fGammaRemoved, "fGammaRemoved/I");
	fEventSummaryTree->Branch("fTotPx", &fTotPx, "fTotPx/D");
	fEventSummaryTree->Branch("fTotPy", &fTotPy, "fTotPy/D");
	fEventSummaryTree->Branch("fTotPz", &fTotPz, "fTotPz/D");
// 	fEventSummaryTree->Branch("f
    }

    //fHistDecayVertexNonRemovedCharged = new TH3F("fHistDecayVertexNonRemovedCharged","fHistDecayVertexNonRemovedCharged", 500, -470, 30, 500, -300, 300, 40, -20, 20);
    //fHistDecayVertexRemovedCharged = new TH3F("fHistDecayVertexRemovedCharged","fHistDecayVertexRemovedCharged", 500, -470, 30, 500, -300, 300, 40, -20, 20);
    //fHistDecayVertexNonRemovedNeutral = new TH3F("fHistDecayVertexNonRemovedNeutral","fHistDecayVertexNonRemovedNeutral", 500, -470, 30, 500, -300, 300, 40, -20, 20);
    //fHistDecayVertexRemovedNeutral = new TH3F("fHistDecayVertexRemovedNeutral","fHistDecayVertexRemovedNeutral", 500, -470, 30, 500, -300, 300, 40, -20, 20);

    fHistRemovedOrNot = new TH2F("fHistRemovedOrNot", "fHistRemovedOrNot", 4, -0.5, 3.5, 10, -0.5, 9.5);

    fHistEtNonRemovedProtons = new TH2F("fHistEtNonRemovedProtons", "fHistEtNonRemovedProtons", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedAntiProtons = new TH2F("fHistEtNonRemovedAntiProtons", "fHistEtNonRemovedAntiProtons", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedPiPlus = new TH2F("fHistEtNonRemovedPiPlus", "fHistEtNonRemovedPiPlus", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedPiMinus = new TH2F("fHistEtNonRemovedPiMinus", "fHistEtNonRemovedPiMinus", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedKaonPlus = new TH2F("fHistEtNonRemovedKaonPlus", "fHistEtNonRemovedKaonPlus", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedKaonMinus = new TH2F("fHistEtNonRemovedKaonMinus", "fHistEtNonRemovedKaonMinus", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedK0s = new TH2F("fHistEtNonRemovedK0s", "fHistEtNonRemovedK0s", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedK0L = new TH2F("fHistEtNonRemovedK0L", "fHistEtNonRemovedK0L", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedLambdas = new TH2F("fHistEtNonRemovedLambdas", "fHistEtNonRemovedLambdas", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedElectrons = new TH2F("fHistEtNonRemovedElectrons", "fHistEtNonRemovedElectrons", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedPositrons = new TH2F("fHistEtNonRemovedPositrons", "fHistEtNonRemovedPositrons", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedMuPlus = new TH2F("fHistEtNonRemovedMuPlus", "fHistEtNonRemovedMuPlus", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedMuMinus = new TH2F("fHistEtNonRemovedMuMinus", "fHistEtNonRemovedMuMinus", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedNeutrons = new TH2F("fHistEtNonRemovedNeutrons", "fHistEtNonRemovedNeutrons", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedAntiNeutrons = new TH2F("fHistEtNonRemovedAntiNeutrons", "fHistEtNonRemovedAntiNeutrons", 1500, 0, 30, 10, -0.5, 9.5);

    fHistEtNonRemovedGammas = new  TH2F("fHistEtNonRemovedGammas", "fHistEtNonRemovedGammas", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedGammasFromPi0 = new  TH2F("fHistEtNonRemovedGammasFromPi0", "fHistEtNonRemovedGammasFromPi0", 1500, 0, 30, 10, -0.5, 9.5);

    fHistEtRemovedGammas = new  TH2F("fHistEtRemovedGammas", "fHistEtRemovedGammas", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtRemovedNeutrons = new  TH2F("fHistEtRemovedNeutrons", "fHistEtRemovedNeutrons", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtRemovedAntiNeutrons = new  TH2F("fHistEtRemovedAntiNeutrons", "fHistEtRemovedAntiNeutrons", 1500, 0, 30, 10, -0.5, 9.5);

    fHistEtRemovedCharged = new  TH2F("fHistEtRemovedCharged", "fHistEtRemovedCharged", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtRemovedNeutrals = new  TH2F("fHistEtRemovedNeutrals", "fHistEtRemovedNeutrals", 1500, 0, 30, 10, -0.5, 9.5);

    fHistEtNonRemovedCharged = new  TH2F("fHistEtNonRemovedCharged", "fHistEtNonRemovedCharged", 1500, 0, 30, 10, -0.5, 9.5);
    fHistEtNonRemovedNeutrals = new  TH2F("fHistEtNonRemovedNeutrals", "fHistEtNonRemovedNeutrals", 1500, 0, 30, 10, -0.5, 9.5);

    fHistMultNonRemovedProtons = new TH2F("fHistMultNonRemovedProtons", "fHistMultNonRemovedProtons", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedAntiProtons = new TH2F("fHistMultNonRemovedAntiProtons", "fHistMultNonRemovedAntiProtons", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedPiPlus = new TH2F("fHistMultNonRemovedPiPlus", "fHistMultNonRemovedPiPlus", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedPiMinus = new TH2F("fHistMultNonRemovedPiMinus", "fHistMultNonRemovedPiMinus", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedKaonPlus = new TH2F("fHistMultNonRemovedKaonPlus", "fHistMultNonRemovedKaonPlus", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedKaonMinus = new TH2F("fHistMultNonRemovedKaonMinus", "fHistMultNonRemovedKaonMinus", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedK0s = new TH2F("fHistMultNonRemovedK0s", "fHistMultNonRemovedK0s", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedK0L = new TH2F("fHistMultNonRemovedK0L", "fHistMultNonRemovedK0L", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedLambdas = new TH2F("fHistMultNonRemovedLambdas", "fHistMultNonRemovedLambdas", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedElectrons = new TH2F("fHistMultNonRemovedElectrons", "fHistMultNonRemovedElectrons", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedPositrons = new TH2F("fHistMultNonRemovedPositrons", "fHistMultNonRemovedPositrons", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedMuPlus = new TH2F("fHistMultNonRemovedMuPlus", "fHistMultNonRemovedMuPlus", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedMuMinus = new TH2F("fHistMultNonRemovedMuMinus", "fHistMultNonRemovedMuMinus", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedNeutrons = new TH2F("fHistMultNonRemovedNeutrons", "fHistMultNonRemovedNeutrons", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultNonRemovedAntiNeutrons = new TH2F("fHistMultNonRemovedAntiNeutrons", "fHistMultNonRemovedAntiNeutrons", 100, -0.5, 99.5, 10, -0.5, 9.5);

    fHistMultNonRemovedGammas = new  TH2F("fHistMultNonRemovedGammas", "fHistMultNonRemovedGammas", 100, -0.5, 99.5, 100, -0.5, 99.5);

    fHistMultRemovedGammas = new  TH2F("fHistMultRemovedGammas", "fHistMultRemovedGammas", 100, -0.5, 99.5, 100, -0.5, 99.5);
    fHistMultRemovedNeutrons = new  TH2F("fHistMultRemovedNeutrons", "fHistMultRemovedNeutrons", 100, -0.5, 99.5, 10, -0.5, 9.5);
    fHistMultRemovedAntiNeutrons = new  TH2F("fHistMultRemovedAntiNeutrons", "fHistMultRemovedAntiNeutrons", 100, -0.5, 99.5, 10, -0.5, 9.5);
    /*
      fHistMultRemovedCharged = new  TH2F("fHistMultRemovedCharged", "fHistMultRemovedCharged", 1500, 0, 30, 10, -0.5, 9.5);
      fHistMultRemovedNeutrals = new  TH2F("fHistMultRemovedNeutrals", "fHistMultRemovedNeutrals", 1500, 0, 30, 10, -0.5, 9.5);

      fHistMultNonRemovedCharged = new  TH2F("fHistMultNonRemovedCharged", "fHistMultNonRemovedCharged", 1500, 0, 30, 10, -0.5, 9.5);
      fHistMultNonRemovedNeutrals = new  TH2F("fHistMultNonRemovedNeutrals", "fHistMultNonRemovedNeutrals", 1500, 0, 30, 10, -0.5, 9.5);*/


    fHistMultRemovedCharged = new  TH2F("fHistMultRemovedCharged", "fHistMultRemovedCharged", 100, -0.5, 99.5, 100, -0.5, 99.5);
    fHistMultRemovedNeutrals = new  TH2F("fHistMultRemovedNeutrals", "fHistMultRemovedNeutrals", 100, -0.5, 99.5, 100, -0.5, 99.5);

    fHistMultNonRemovedCharged = new  TH2F("fHistMultNonRemovedCharged", "fHistMultNonRemovedCharged", 100, -0.5, 99.5, 100, -0.5, 99.5);
    fHistMultNonRemovedNeutrals = new  TH2F("fHistMultNonRemovedNeutrals", "fHistMultNonRemovedNeutrals", 100, -0.5, 99.5, 100, -0.5, 99.5);

    fHistTrackMultvsNonRemovedCharged = new TH2F("fHistTrackMultvsNonRemovedCharged", "fHistTrackMultvsNonRemovedCharged", 1000, -0.5, 999.5, 100, -0.5, 99.5);
    fHistTrackMultvsNonRemovedNeutral = new TH2F("fHistTrackMultvsNonRemovedNeutral", "fHistTrackMultvsNonRemovedNeutral", 1000, -0.5, 999.5, 100, -0.5, 99.5);
    fHistTrackMultvsRemovedGamma = new TH2F("fHistTrackMultvsRemovedGamma", "fHistTrackMultvsRemovedGamma", 1000, -0.5, 999.5, 100, -0.5, 99.5);

    fHistClusterMultvsNonRemovedCharged = new TH2F("fHistClusterMultvsNonRemovedCharged", "fHistClusterMultvsNonRemovedCharged", 1000, -0.5, 999.5, 100, -0.5, 99.5);
    fHistClusterMultvsNonRemovedNeutral = new TH2F("fHistClusterMultvsNonRemovedNeutral", "fHistClusterMultvsNonRemovedNeutral", 1000, -0.5, 999.5, 100, -0.5, 99.5);
    fHistClusterMultvsRemovedGamma = new TH2F("fHistClusterMultvsRemovedGamma", "fHistClusterMultvsRemovedGamma", 1000, -0.5, 999.5, 100, -0.5, 99.5);

    fHistDxDzNonRemovedCharged = new TH2F("fHistDxDzNonRemovedCharged", "fHistDxDzNonRemovedCharged", 800, -200, 200, 800, -200, 200);
    fHistDxDzRemovedCharged = new TH2F("fHistDxDzRemovedCharged", "fHistDxDzRemovedCharged", 800, -200, 200, 800, -200, 200);
    fHistDxDzNonRemovedNeutral = new TH2F("fHistDxDzNonRemovedNeutral", "fHistDxDzNonRemovedNeutral", 800, -200, 200, 800, -200, 200);
    fHistDxDzRemovedNeutral = new TH2F("fHistDxDzRemovedNeutral", "fHistDxDzRemovedNeutral", 800, -200, 200, 800, -200, 200);

    fHistPiPlusMult = new TH1F("fHistPiPlusMult", "fHistPiPlusMult", 2000, -0.5, 1999.5);
    fHistPiMinusMult = new TH1F("fHistPiMinusMult", "fHistPiMinusMult", 2000, -0.5, 1999.5);
    fHistPiZeroMult = new TH1F("fHistPiZeroMult", "fHistPiZeroMult", 2000, -0.5, 1999.5);

    fHistPiPlusMultAcc = new TH1F("fHistPiPlusMultAcc", "fHistPiPlusMultAcc", 2000, -0.5, 1999.5);
    fHistPiMinusMultAcc = new TH1F("fHistPiMinusMultAcc", "fHistPiMinusMultAcc", 2000, -0.5, 1999.5);
    fHistPiZeroMultAcc = new TH1F("fHistPiZeroMultAcc", "fHistPiZeroMultAcc", 2000, -0.5, 1999.5);

    if(fCuts->GetHistMakeTree())
    {
        TString treename = "fPrimaryTree" + fHistogramNameSuffix;
        fPrimaryTree = new TTree(treename, treename);

        fPrimaryTree->Branch("fTotEt",&fTotEt,"fTotEt/D");
        fPrimaryTree->Branch("fNeutralMultiplicity", &fNeutralMultiplicity, "fNeutralMultiplicity/I");
        fPrimaryTree->Branch("fCentClass",&fCentClass,"fCentClass/I");

        fPrimaryTree->Branch("fPrimaryCode", &fPrimaryCode, "fPrimaryCode/I");
        fPrimaryTree->Branch("fPrimaryCharge", &fPrimaryCharge, "fPrimaryCharge/I");

        fPrimaryTree->Branch("fPrimaryE", &fPrimaryE, "fPrimaryE/D");
        fPrimaryTree->Branch("fPrimaryEt", &fPrimaryEt, "fPrimaryEt/D");

        fPrimaryTree->Branch("fPrimaryPx", &fPrimaryPx, "fPrimaryPx/D");
        fPrimaryTree->Branch("fPrimaryPy", &fPrimaryPy, "fPrimaryPy/D");
        fPrimaryTree->Branch("fPrimaryPz", &fPrimaryPz, "fPrimaryPz/D");

        fPrimaryTree->Branch("fPrimaryVx", &fPrimaryVx, "fPrimaryVx/D");
        fPrimaryTree->Branch("fPrimaryVy", &fPrimaryVy, "fPrimaryVy/D");
        fPrimaryTree->Branch("fPrimaryVz", &fPrimaryVz, "fPrimaryVz/D");

        fPrimaryTree->Branch("fPrimaryAccepted", &fPrimaryAccepted, "fPrimaryAccepted/B");
        fPrimaryTree->Branch("fPrimaryMatched", &fPrimaryMatched, "fPrimaryMatched/B");


        fPrimaryTree->Branch("fDepositedCode", &fDepositedCode, "fDepositedCode/I");
        fPrimaryTree->Branch("fDepositedCharge", &fDepositedCharge, "fDepositedCharge/I");
	fPrimaryTree->Branch("fDepositedE", &fDepositedE, "fDepositedE/D");
        fPrimaryTree->Branch("fDepositedEt", &fDepositedEt, "fDepositedEt/D");

        fPrimaryTree->Branch("fDepositedVx", &fDepositedVx, "fDepositedVx/D");
        fPrimaryTree->Branch("fDepositedVy", &fDepositedVy, "fDepositedVy/D");
        fPrimaryTree->Branch("fDepositedVz", &fDepositedVz, "fDepositedVz/D");

	fPrimaryTree->Branch("fSecondary", &fSecondary, "fSecondary/I");

	
	fPrimaryTree->Branch("fReconstructedE", &fReconstructedE, "fReconstructedE/D");
        fPrimaryTree->Branch("fReconstructedEt", &fReconstructedEt, "fReconstructedEt/D");
	
	fPrimaryTree->Branch("fClusterMult", &fClusterMult,  "fClusterMult/I");
	
	
    }

    fHistGammasFound = new TH1F("fHistGammasFound", "fHistGammasFound",200, 0, 10);
    fHistGammasGenerated = new TH1F("fHistGammasGenerated", "fHistGammasGenerated",200, 0, 10);
}

void AliAnalysisEtMonteCarlo::FillOutputList(TList *list)
{   //fill the output list
    AliAnalysisEt::FillOutputList(list);

    if(fCuts->GetHistMakeTree())
    {
        list->Add(fPrimaryTree);
    }

    list->Add(fHistRemovedOrNot);

    list->Add(fHistEtNonRemovedProtons);
    list->Add(fHistEtNonRemovedAntiProtons);
    list->Add(fHistEtNonRemovedPiPlus);
    list->Add(fHistEtNonRemovedPiMinus);
    list->Add(fHistEtNonRemovedKaonPlus);
    list->Add(fHistEtNonRemovedKaonMinus);
    list->Add(fHistEtNonRemovedK0s);
    list->Add(fHistEtNonRemovedK0L);
    list->Add(fHistEtNonRemovedLambdas);
    list->Add(fHistEtNonRemovedElectrons);
    list->Add(fHistEtNonRemovedPositrons);
    list->Add(fHistEtNonRemovedMuPlus);
    list->Add(fHistEtNonRemovedMuMinus);
    list->Add(fHistEtNonRemovedNeutrons);
    list->Add(fHistEtNonRemovedAntiNeutrons);
    list->Add(fHistEtNonRemovedGammas);
    list->Add(fHistEtNonRemovedGammasFromPi0);

    list->Add(fHistEtRemovedGammas);
    list->Add(fHistEtRemovedNeutrons);
    list->Add(fHistEtRemovedAntiNeutrons);

    list->Add(fHistEtRemovedCharged);
    list->Add(fHistEtRemovedNeutrals);

    list->Add(fHistEtNonRemovedCharged);
    list->Add(fHistEtNonRemovedNeutrals);

    list->Add(fHistMultNonRemovedProtons);
    list->Add(fHistMultNonRemovedAntiProtons);
    list->Add(fHistMultNonRemovedPiPlus);
    list->Add(fHistMultNonRemovedPiMinus);
    list->Add(fHistMultNonRemovedKaonPlus);
    list->Add(fHistMultNonRemovedKaonMinus);
    list->Add(fHistMultNonRemovedK0s);
    list->Add(fHistMultNonRemovedK0L);
    list->Add(fHistMultNonRemovedLambdas);
    list->Add(fHistMultNonRemovedElectrons);
    list->Add(fHistMultNonRemovedPositrons);
    list->Add(fHistMultNonRemovedMuPlus);
    list->Add(fHistMultNonRemovedMuMinus);
    list->Add(fHistMultNonRemovedNeutrons);
    list->Add(fHistMultNonRemovedAntiNeutrons);
    list->Add(fHistMultNonRemovedGammas);

    list->Add(fHistMultRemovedGammas);
    list->Add(fHistMultRemovedNeutrons);
    list->Add(fHistMultRemovedAntiNeutrons);

    list->Add(fHistMultRemovedCharged);
    list->Add(fHistMultRemovedNeutrals);

    list->Add(fHistMultNonRemovedCharged);
    list->Add(fHistMultNonRemovedNeutrals);

    list->Add(fHistTrackMultvsNonRemovedCharged);
    list->Add(fHistTrackMultvsNonRemovedNeutral);
    list->Add(fHistTrackMultvsRemovedGamma);

    list->Add(fHistClusterMultvsNonRemovedCharged);
    list->Add(fHistClusterMultvsNonRemovedNeutral);
    list->Add(fHistClusterMultvsRemovedGamma);

    //list->Add(fHistDecayVertexNonRemovedCharged);
    //list->Add(fHistDecayVertexNonRemovedNeutral);
    //list->Add(fHistDecayVertexRemovedCharged);
    //list->Add(fHistDecayVertexRemovedNeutral);

    list->Add(fHistDxDzNonRemovedCharged);
    list->Add(fHistDxDzRemovedCharged);
    list->Add(fHistDxDzNonRemovedNeutral);
    list->Add(fHistDxDzRemovedNeutral);

    list->Add(fHistPiPlusMult);
    list->Add(fHistPiMinusMult);
    list->Add(fHistPiZeroMult);
    list->Add(fHistPiPlusMultAcc);
    list->Add(fHistPiMinusMultAcc);
    list->Add(fHistPiZeroMultAcc);
    
    list->Add(fHistGammasFound);
    list->Add(fHistGammasGenerated);

}


bool AliAnalysisEtMonteCarlo::TrackHitsCalorimeter(TParticle* part, Double_t magField)
{
    //  printf(" TrackHitsCalorimeter - magField %f\n", magField);
    AliESDtrack *esdTrack = new AliESDtrack(part);
    // Printf("MC Propagating track: eta: %f, phi: %f, pt: %f", esdTrack->Eta(), esdTrack->Phi(), esdTrack->Pt());

    Bool_t prop = esdTrack->PropagateTo(fDetectorRadius, magField);

    // if(prop) Printf("Track propagated, eta: %f, phi: %f, pt: %f", esdTrack->Eta(), esdTrack->Phi(), esdTrack->Pt());

    bool status = prop && fSelector->CutGeometricalAcceptance(*esdTrack);
    delete esdTrack;

    return status;
}

void AliAnalysisEtMonteCarlo::FillHistograms()
{   // let base class fill its histograms, and us fill the local ones
    AliAnalysisEt::FillHistograms();
    //std::cout << fEtNonRemovedPiPlus << " " << fCentClass << std::endl;

    fHistEtNonRemovedProtons->Fill(fEtNonRemovedProtons, fCentClass);
    fHistEtNonRemovedAntiProtons->Fill(fEtNonRemovedAntiProtons, fCentClass);
    fHistEtNonRemovedKaonPlus->Fill(fEtNonRemovedKaonPlus, fCentClass);
    fHistEtNonRemovedKaonMinus->Fill(fEtNonRemovedKaonMinus, fCentClass);
    fHistEtNonRemovedK0s->Fill(fEtNonRemovedK0S, fCentClass);
    fHistEtNonRemovedK0L->Fill(fEtNonRemovedK0L, fCentClass);
    fHistEtNonRemovedLambdas->Fill(fEtNonRemovedLambdas, fCentClass);
    fHistEtNonRemovedPiPlus->Fill(fEtNonRemovedPiPlus, fCentClass);
    fHistEtNonRemovedPiMinus->Fill(fEtNonRemovedPiMinus, fCentClass);
    fHistEtNonRemovedElectrons->Fill(fEtNonRemovedElectrons, fCentClass);
    fHistEtNonRemovedPositrons->Fill(fEtNonRemovedPositrons, fCentClass);
    fHistEtNonRemovedMuPlus->Fill(fEtNonRemovedMuPlus, fCentClass);
    fHistEtNonRemovedMuMinus->Fill(fEtNonRemovedMuMinus, fCentClass);
    fHistEtNonRemovedNeutrons->Fill(fEtNonRemovedNeutrons, fCentClass);
    fHistEtNonRemovedAntiNeutrons->Fill(fEtNonRemovedAntiNeutrons, fCentClass);
    fHistEtNonRemovedGammas->Fill(fEtNonRemovedGammas, fCentClass);
    fHistEtNonRemovedGammasFromPi0->Fill(fEtNonRemovedGammasFromPi0, fCentClass);

    fHistEtRemovedGammas->Fill(fEtRemovedGammas, fNClusters);
    fHistEtRemovedNeutrons->Fill(fEtRemovedNeutrons, fCentClass);
    fHistEtRemovedAntiNeutrons->Fill(fEtRemovedAntiNeutrons, fCentClass);

//     fHistEtRemovedCharged->Fill(fEtRemovedAntiProtons+fEtRemovedElectrons+fEtRemovedKaonMinus+fEtRemovedKaonPlus
//                                             +fEtRemovedMuMinus+fEtRemovedMuPlus+fEtRemovedPiMinus+fEtRemovedPiPlus+fEtRemovedPositrons
//                                             +fEtRemovedProtons.
// 				fCentClass);
//     fHistEtRemovedNeutrals->Fill(fEtRemovedNeutrons+fEtRemovedAntiNeutrons, fCentClass);
//
//     fHistEtNonRemovedCharged->Fill(fEtNonRemovedAntiProtons+fEtNonRemovedElectrons+fEtNonRemovedKaonMinus+fEtNonRemovedKaonPlus
//                                             +fEtNonRemovedMuMinus+fEtNonRemovedMuPlus+fEtNonRemovedPiMinus+fEtNonRemovedPiPlus+fEtNonRemovedPositrons
//                                             +fEtNonRemovedProtons,
// 				fCentClass);
//     fHistEtRemovedNeutrals->Fill(fEtNonRemovedNeutrons+fEtNonRemovedAntiNeutrons, fCentClass);

    fHistEtRemovedCharged->Fill(fEnergyChargedRemoved, fNClusters);
    fHistEtRemovedNeutrals->Fill(fEnergyNeutralRemoved, fNClusters);
    fHistEtNonRemovedCharged->Fill(fEnergyChargedNotRemoved, fNClusters);
    fHistEtNonRemovedNeutrals->Fill(fEnergyNeutralNotRemoved, fNClusters);

    fHistMultRemovedCharged->Fill(fChargedRemoved, fNClusters);
    fHistMultRemovedNeutrals->Fill(fNeutralRemoved, fNClusters);
    fHistMultNonRemovedCharged->Fill(fChargedNotRemoved, fNClusters);
    fHistMultNonRemovedNeutrals->Fill(fNeutralNotRemoved, fNClusters);


    fHistMultNonRemovedProtons->Fill(fMultNonRemovedProtons, fCentClass);
    fHistMultNonRemovedAntiProtons->Fill(fMultNonRemovedAntiProtons, fCentClass);
    fHistMultNonRemovedKaonPlus->Fill(fMultNonRemovedKaonPlus, fCentClass);
    fHistMultNonRemovedKaonMinus->Fill(fMultNonRemovedKaonMinus, fCentClass);
    fHistMultNonRemovedK0s->Fill(fMultNonRemovedK0s, fCentClass);
    fHistMultNonRemovedK0L->Fill(fMultNonRemovedK0L, fCentClass);
    fHistMultNonRemovedLambdas->Fill(fMultNonRemovedLambdas, fCentClass);
    fHistMultNonRemovedPiPlus->Fill(fMultNonRemovedPiPlus, fCentClass);
    fHistMultNonRemovedPiMinus->Fill(fMultNonRemovedPiMinus, fCentClass);
    fHistMultNonRemovedElectrons->Fill(fMultNonRemovedElectrons, fCentClass);
    fHistMultNonRemovedPositrons->Fill(fMultNonRemovedPositrons, fCentClass);
    fHistMultNonRemovedMuPlus->Fill(fMultNonRemovedMuPlus, fCentClass);
    fHistMultNonRemovedMuMinus->Fill(fMultNonRemovedMuMinus, fCentClass);
    fHistMultNonRemovedNeutrons->Fill(fMultNonRemovedNeutrons, fCentClass);
    fHistMultNonRemovedAntiNeutrons->Fill(fMultNonRemovedAntiNeutrons, fCentClass);
    fHistMultNonRemovedGammas->Fill(fMultNonRemovedGammas, fCentClass);

    fHistMultRemovedGammas->Fill(fMultRemovedGammas, fCentClass);
    fHistMultRemovedNeutrons->Fill(fMultRemovedNeutrons, fCentClass);
    fHistMultRemovedAntiNeutrons->Fill(fMultRemovedAntiNeutrons, fCentClass);

    fHistTrackMultvsNonRemovedCharged->Fill(fTrackMultInAcc,
                                            fMultNonRemovedAntiProtons+fMultNonRemovedElectrons+fMultNonRemovedKaonMinus+fMultNonRemovedKaonPlus
                                            +fMultNonRemovedMuMinus+fMultNonRemovedMuPlus+fMultNonRemovedPiMinus+fMultNonRemovedPiPlus+fMultNonRemovedPositrons
                                            +fMultNonRemovedProtons);

    fHistTrackMultvsNonRemovedNeutral->Fill(fTrackMultInAcc,
                                            fMultNonRemovedNeutrons+fMultNonRemovedAntiNeutrons+fMultNonRemovedK0s+fMultNonRemovedK0L+fMultNonRemovedLambdas+fK0sMult);

    fHistTrackMultvsRemovedGamma->Fill(fTrackMultInAcc,
                                       fMultRemovedGammas);

    fHistClusterMultvsNonRemovedCharged->Fill(fNClusters,
            fMultNonRemovedAntiProtons+fMultNonRemovedElectrons+fMultNonRemovedKaonMinus
            +fMultNonRemovedKaonPlus+fMultNonRemovedMuMinus+fMultNonRemovedMuPlus
            +fMultNonRemovedPiMinus+fMultNonRemovedPiPlus+fMultNonRemovedPositrons+fMultNonRemovedProtons);

    fHistClusterMultvsNonRemovedNeutral->Fill(fNClusters,
            fMultNonRemovedNeutrons+fMultNonRemovedAntiNeutrons+fMultNonRemovedK0s+fMultNonRemovedK0L+fMultNonRemovedLambdas+fK0sMult);

    fHistClusterMultvsRemovedGamma->Fill(fNClusters,
                                         fMultRemovedGammas);

}




Int_t AliAnalysisEtMonteCarlo::PrintFamilyTree(Int_t partIdx, AliStack* stack)
{ // print family tree
    TParticle *part = stack->Particle(partIdx);
//     if(part->GetPdgCode() == fgK0SCode)
    {
        std::cout << "This is index: " << partIdx << " (" << stack->Particle(partIdx)->GetName() <<") , is it primary: " << stack->IsPhysicalPrimary(partIdx)<< std::endl;
        std::cout << "PID: " << part->GetPdgCode() << "/" << part->GetName() << std::endl;
        std::cout << "Energy: " << part->Energy() << std::endl;
        std::cout << "Vertex: " << part->Vx() << ", " << part->Vy() << ", " << part->Vz() << std::endl;
    }
    return PrintMothers(partIdx, stack, 1);
}

Int_t AliAnalysisEtMonteCarlo::PrintMothers(Int_t partIdx, AliStack* stack, Int_t gen)
{ // print mothers
    char *tabs = new char[gen+1];
    for(Int_t i = 0; i < gen; ++i)
    {
        //std::cout << i << std::endl;
        tabs[i] = '\t';
    }
    tabs[gen] = '\0';
    Int_t mothIdx = stack->Particle(partIdx)->GetMother(0);
    if(mothIdx < 0)
    {
      delete [] tabs;
      return 0;
    }
    TParticle *mother = stack->Particle(mothIdx);
//     if(mother->GetPdgCode() == fgK0SCode)
    {
        //std::cout << tabs << "Mother of index: " << partIdx << " (" << stack->Particle(partIdx)->GetName() <<") is: " << mothIdx << ", is it primary: " << stack->IsPhysicalPrimary(mothIdx)<< std::endl;
        std::cout << tabs << "Index: " << mothIdx << std::endl;
        std::cout << tabs << "Primary: " << stack->IsPhysicalPrimary(mothIdx) << std::endl;
        std::cout << tabs << "PID: " << mother->GetPdgCode() << "/" << mother->GetName() << std::endl;
        std::cout << tabs << "Energy: " << mother->Energy() << std::endl;
	if(mother->GetFirstMother() >= 0)
	{
	  std::cout << tabs << "Mother(s): " << stack->Particle(mother->GetFirstMother())->GetPdgCode();
	  if(mother->GetSecondMother() >= 0) std::cout << ", " << stack->Particle(mother->GetSecondMother())->GetPdgCode();
	  std::cout << std::endl;
	}
        std::cout << tabs << "Vertex: " << mother->Vx() << ", " << mother->Vy() << ", " << mother->Vz() << std::endl;
    }
    if(mother->GetPdgCode() == fgK0SCode)
    {
//	std::cout << "K0S!!!!!!!!!!!!!11111!!!!!" << std::endl;
    }
//  std::cout << "Mother of index: " << partIdx << " (" << stack->Particle(partIdx)->GetName() <<") is: " << mothIdx << std::endl;
//  std::cout << "PID: " << mother->GetPdgCode() << "/" << mother->GetName() << std::endl;
//  std::cout << "Energy: " << mother->Energy() << std::endl;
//  std::cout << "Vertex: " << mother->Vx() << ", " << mother->Vy() << ", " << mother->Vz() << std::endl;

    delete [] tabs;
    return PrintMothers(mothIdx, stack, gen+1) + 1;
}

Int_t AliAnalysisEtMonteCarlo::GetPrimMother(Int_t partIdx, AliStack *stack)
{ // get primary mother
    if(partIdx >= 0)
    {
	//return stack->GetPrimary(partIdx);
	
        Int_t mothIdx = stack->Particle(partIdx)->GetMother(0);
        if(mothIdx < 0) return -1;
        TParticle *mother = stack->Particle(mothIdx);
        if(mother)
        {
            // if(mother->GetPdgCode() == fgK0SCode)
            //{
//	std::cout << "!!!!!!!!!!!!!!!!! K0S !!!!!!!!!!!!!!!!!!" << std::endl;
            //return mothIdx;
            //    }
            //if(mother->GetPdgCode() == fgK0SCode&& stack->IsPhysicalPrimary(mothIdx))
            //{
//	std::cout << "!!!!!!!!!!!!!!!!! Primary K0S !!!!!!!!!!!!!!!!!!" << std::endl;
            //return mothIdx;
            //      }
            if(stack->IsPhysicalPrimary(mothIdx)) return mothIdx;
            else return GetPrimMother(mothIdx, stack);
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

Int_t AliAnalysisEtMonteCarlo::GetK0InFamily(Int_t partIdx, AliStack* stack)
{ // get K0 in family
    if(partIdx >= 0)
    {
        if(stack->Particle(partIdx)->GetPdgCode() == fgPi0Code) return partIdx;
        Int_t mothIdx = stack->Particle(partIdx)->GetMother(0);
        if(mothIdx < 0) return -1;
        TParticle *mother = stack->Particle(mothIdx);
        if(mother)
        {
            if(mother->GetPdgCode() == fgPi0Code)
            {
                return mothIdx;
            }
            return GetK0InFamily(mothIdx, stack);
        }
        else
        {
            return -1;
        }
    }
    return -1;
}

