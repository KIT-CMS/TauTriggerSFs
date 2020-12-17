#ifndef TauTriggerSFsSingleTau_h
#define TauTriggerSFsSingleTau_h

/** \class TauTriggerSFsSingleTau
 *
 * Class to access information on tau trigger efficiencies in data and MC and related data/MC scale-factors.
 * The trigger efficiencies are parametrized as function of pT, eta, and phi of the offline reconstructed tau,
 * cf. https://indico.cern.ch/event/700928/contributions/2883477/attachments/1596523/2529036/Ruggles_TauTriggers_TauPOG_20180207_v4.pdf 
 *
 * \authors Tyler Ruggles, Wisconsin; Christian Veelken, Tallin
 *
 * \updated February2019 Francesco Brivio, Milano-Bicocca; Chiara Amendola, LLR
 * cf. https://indico.cern.ch/event/799374/contributions/3323191/attachments/1797874/2931826/TauTrigger2017SFv3_TauID_hsert.pdf
 *
 */

#include <TFile.h> // TFile
#include <TH1.h> // TH1
#include <TH2.h> // TH2
#include <TF1.h> // TF1

#include <string> // std::string
#include <map>    // std::map

class TauTriggerSFsSingleTau
{
public:

  TauTriggerSFsSingleTau(const std::string& inputFileName, const std::string& year, const std::string& tauWP = "medium", const std::string& wpType = "DeepTau");
  ~TauTriggerSFsSingleTau();

  // Return the data efficiency or the +/- 1 sigma uncertainty shifted efficiency
  double getSingleTauTriggerEfficiencyData(double pt, int dm) const;
  double getSingleTauTriggerEfficiencyDataUncertUp(double pt, int dm) const;
  double getSingleTauTriggerEfficiencyDataUncertDown(double pt, int dm) const;

  // Return the mc efficiency
  double getSingleTauTriggerEfficiencyMC(double pt, int dm) const;

protected:
  std::string inputFileName_;
  TFile* inputFile_;

  std::string trigger_;
  std::string year_;
  std::string tauWP_;
  std::string wpType_;

  // Maps for the single tau trigger
  std::map<int, TH1*> effSTDataMap_;
  std::map<int, TH1*> effSTMCMap_;
  std::map<int, TH1*> effSTDataUncUpMap_;
  std::map<int, TH1*> effSTDataUncDownMap_;
};

#endif // TauTriggerSFsSingleTau_h

