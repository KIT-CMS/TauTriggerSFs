#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFsSingleTau.h"
#include "TauAnalysisTools/TauTriggerSFs/interface/TauTriggerSFs2017.h"

#include <TString.h> // Form

#include <iostream> // std::cerr, std::endl
#include <iomanip> 
#include <assert.h> // assert
#include <cmath> // std::sqrt
#include <regex> // std::regex_replace

double ptCheckST(double pt)
{
  if (pt > 1000)  pt = 1000;
  else if (pt < 80) pt = 80;
  return pt;
}

TauTriggerSFsSingleTau::TauTriggerSFsSingleTau(const std::string& inputFileName, const std::string& year, const std::string& tauWP, const std::string& wpType)
  : inputFileName_(inputFileName),
    year_(year),
    tauWP_(tauWP),
    wpType_(wpType)
{
  inputFile_ = new TFile(inputFileName_.data());
  if ( !inputFile_ ) {
    std::cerr << "Failed to open input file = '" << inputFileName_ << "' !!" << std::endl;
    assert(0);
  }

  // Load the TGraphAssymErrors containing the single tau trigger efficiencies.
  // This is done per decay mode: 0, 1, 10, 11
  std::vector<int> DMs = {0, 1, 10, 11};
  for (auto dm: DMs)
  {
      effSTMCMap_ [dm] = loadTH1(inputFile_, Form("singletau_%s%s_dm%i_MC", tauWP_.data(), wpType_.data(), dm));
      effSTDataMap_ [dm] = loadTH1(inputFile_, Form("singletau_%s%s_dm%i_DATA", tauWP_.data(), wpType_.data(), dm));
      effSTDataUncUpMap_ [dm] = loadTH1(inputFile_, Form("singletau_%s%s_dm%i_DATA_Up", tauWP_.data(), wpType_.data(), dm));
      effSTDataUncDownMap_ [dm] = loadTH1(inputFile_, Form("singletau_%s%s_dm%i_DATA_Down", tauWP_.data(), wpType_.data(), dm));
  }
}


TauTriggerSFsSingleTau::~TauTriggerSFsSingleTau()
{
  delete inputFile_;
}


double getSingleTauTriggerEfficiency(double pt, const TH1* effHist)
{
  double pt_checked = ptCheckST( pt );
  double eff = effHist->GetBinContent( (const_cast<TH1*>(effHist))->FindBin(pt_checked));

  return eff;
}

double TauTriggerSFsSingleTau::getSingleTauTriggerEfficiencyMC(double pt, int dm) const
{
  int dm_checked = dmCheck( dm );
  if ( (dm_checked!=0) && (dm_checked!=1) && (dm_checked!=10) && (dm_checked!=11) )
  {
    std::cerr << Form("Efficiencies only provided for DMs 0, 1, 10, 11.  You provided DM %i", dm_checked) << std::endl;
    assert(0);
  }
  return getSingleTauTriggerEfficiency(pt, effSTMCMap_.at(dm_checked));
}

double TauTriggerSFsSingleTau::getSingleTauTriggerEfficiencyData(double pt, int dm) const
{
  int dm_checked = dmCheck( dm );
  if ( (dm_checked!=0) && (dm_checked!=1) && (dm_checked!=10) && (dm_checked!=11) )
  {
    std::cerr << Form("Efficiencies only provided for DMs 0, 1, 10, 11.  You provided DM %i", dm_checked) << std::endl;
    assert(0);
  }
  return getSingleTauTriggerEfficiency(pt, effSTDataMap_.at(dm_checked));
}

double TauTriggerSFsSingleTau::getSingleTauTriggerEfficiencyDataUncertUp(double pt, int dm) const
{
  int dm_checked = dmCheck( dm );
  if ( (dm_checked!=0) && (dm_checked!=1) && (dm_checked!=10) && (dm_checked!=11) )
  {
    std::cerr << Form("Efficiencies only provided for DMs 0, 1, 10, 11.  You provided DM %i", dm_checked) << std::endl;
    assert(0);
  }
  return getSingleTauTriggerEfficiency(pt, effSTDataUncUpMap_.at(dm_checked));
}

double TauTriggerSFsSingleTau::getSingleTauTriggerEfficiencyDataUncertDown(double pt, int dm) const
{
  int dm_checked = dmCheck( dm );
  if ( (dm_checked!=0) && (dm_checked!=1) && (dm_checked!=10) && (dm_checked!=11) )
  {
    std::cerr << Form("Efficiencies only provided for DMs 0, 1, 10, 11.  You provided DM %i", dm_checked) << std::endl;
    assert(0);
  }
  return getSingleTauTriggerEfficiency(pt, effSTDataUncDownMap_.at(dm_checked));
}
