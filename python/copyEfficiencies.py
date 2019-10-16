"""
Grab the efficiency files from Hale's output root file
to make a consolidated single file with all needed
efficiency ingredients:
    TGraph used for the fit (not used for applying trigger efficiencies/SFs)
    TF1 from resulting fit to TGraph
    TH1 containing error band from fit
"""
import argparse

import ROOT
from TauAnalysisTools.TauTriggerSFs.helpers import getHist, getGraph, getFit, getHistFromGraph

parser = argparse.ArgumentParser()
parser.add_argument("input", type=str,
                    help="Input root file.")
parser.add_argument("output", type=str,
                    help="Output root file.")
parser.add_argument("-s", "--samples", type=str, nargs="+",
                    default=["MC", "DATA", "EMB"],
                    help="Sample types to be processed.")
args = parser.parse_args()

print "Making initial SF file"

iFile = ROOT.TFile(args.input, "read")
oFile = ROOT.TFile(args.output, "recreate")

# Supporting 2017 MVAv2 only
# for trigger in ['ditau', 'mutau', 'etau']:
for trigger in ["etau"]:
    for wp in ['vloose', 'loose', 'medium', 'tight', 'vtight', 'vvtight']: # No VVLoose
        for dm in ['dm0', 'dm1', 'dm10']:
            for sample in args.samples:
                # iName2017 = trigger+'_XXX_'+dm+'_'+wp+'TauMVA_'+sample
                # iName2018 = trigger+'_XXX_'+wp+'TauMVA_'+dm+'_'+sample
                iName = trigger+'_XXX_'+wp+'TauMVA_'+dm+'_'+sample
                iNameSF = trigger+'_XXX_'+wp+'TauMVA_'+dm
                saveName = trigger+'_'+wp+'MVAv2_'+dm+'_'+sample
                saveNameSF = trigger+'_'+wp+'MVAv2_'+dm
                g = getGraph( iFile, iName.replace('XXX','gEffi'), saveName+'_graph' )
                #hFit = getHist( iFile, iName.replace('XXX','hEffiFit'), saveName+'_Fithisto' )
                #hCoarse = getHist( iFile, iName.replace('XXX','hEffiCoarse'), saveName+'_CoarseBinhisto' )
                f = getFit( iFile, iName.replace('XXX','fit'), saveName+'_fit' )
                h = getHist( iFile, iName.replace('XXX','herrband'), saveName+'_errorBand' )
                hSF = getHist( iFile, iNameSF.replace('XXX','ScaleFactor'), saveNameSF+'_CoarseBinSF' )
                oFile.cd()
                g.Write()
                f.Write()
                h.Write()
                hSF.Write()

oFile.Close()
