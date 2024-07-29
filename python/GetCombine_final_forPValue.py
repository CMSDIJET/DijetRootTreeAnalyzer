from optparse import OptionParser
import ROOT as rt
import sys
from rootTools.RootIterator import RootIterator
from rootTools import Utils
from framework import Config
import glob
from math import *
import os
from array import *
import numpy as np

def getFileName(hybridLimit, massPoint, chiPoint, box, model, lumi,  directory, method, t,alphap, width_name):
    if method == "AsymptoticLimits" or t>0:
        #fileName = "%s/%s_%s_lumi-%.3f_%s.%s.mH120.root"%(directory,hybridLimit,massPoint,lumi,box,method)
        fileName = "%s/%s_alpha0p%.0f_W-%s_%s_%s.%s.mH120.root"%(directory,hybridLimit,alphap,width_name,massPoint,chiPoint,method)
    else:
        #fileName = "%s/%s%s_%s_lumi-%.3f_%s.%s.mH120.root"%(directory,hybridLimit,model,massPoint,lumi,box,method)
        #fileName = "%s/%s_%s_%s.%s.mH120.root"%(directory,hybridLimit,massPoint,chiPoint,method)
        fileName = "%s/%s_alpha0p%.0f_W-%s_%s_%s.%s.mH120.root"%(directory,hybridLimit,alphap,width_name,massPoint,chiPoint,method)
    return fileName

def writeXsecTree(box, model, directory, massPoint,chiPoint,alphap, width_name, xsecULObs, xsecULExpPlus2, xsecULExpPlus, xsecULExp, xsecULExpMinus, xsecULExpMinus2):
    outputFileName = "%s/xsecUL_%s_W-%s_%s_%s.root" %(directory, model, width_name, massPoint, box)
    print ("INFO: xsec UL values being written to %s"%outputFileName)
    fileOut = rt.TFile.Open(outputFileName, "recreate")   
    xsecTree = rt.TTree("xsecTree", "xsecTree")
    myStructCmd = "struct MyStruct{Double_t mass;"
    ixsecUL = 0
    myStructCmd+= "Double_t xsecUL%i;"%(ixsecUL+0)
    myStructCmd+= "Double_t xsecUL%i;"%(ixsecUL+1)
    myStructCmd+= "Double_t xsecUL%i;"%(ixsecUL+2)
    myStructCmd+= "Double_t xsecUL%i;"%(ixsecUL+3)
    myStructCmd+= "Double_t xsecUL%i;"%(ixsecUL+4)
    myStructCmd+= "Double_t xsecUL%i;"%(ixsecUL+5)
    ixsecUL+=6
    myStructCmd += "}"
    rt.gROOT.ProcessLine(myStructCmd)
    from ROOT import MyStruct

    s = MyStruct()
    xsecTree.Branch('mass', rt.addressof(s,'mass'),'mass/D')
    
    
    s.mass = float(massPoint)
    
    ixsecUL = 0
    xsecTree.Branch("xsecULObs_%s"%box, rt.addressof(s,"xsecUL%i"%(ixsecUL+0)),'xsecUL%i/D'%(ixsecUL+0))
    xsecTree.Branch("xsecULExpPlus2_%s"%box, rt.addressof(s,"xsecUL%i"%(ixsecUL+1)),'xsecUL%i/D'%(ixsecUL+1))
    xsecTree.Branch("xsecULExpPlus_%s"%box, rt.addressof(s,"xsecUL%i"%(ixsecUL+2)),'xsecUL%i/D'%(ixsecUL+2))
    xsecTree.Branch("xsecULExp_%s"%box, rt.addressof(s,"xsecUL%i"%(ixsecUL+3)),'xsecUL%i/D'%(ixsecUL+3))
    xsecTree.Branch("xsecULExpMinus_%s"%box, rt.addressof(s,"xsecUL%i"%(ixsecUL+4)),'xsecUL%i/D'%(ixsecUL+4))
    xsecTree.Branch("xsecULExpMinus2_%s"%box, rt.addressof(s,"xsecUL%i"%(ixsecUL+5)),'xsecUL%i/D'%(ixsecUL+5))
    exec ('s.xsecUL%i = xsecULObs[ixsecUL]'%(ixsecUL+0))
    exec ('s.xsecUL%i = xsecULExpPlus2[ixsecUL]'%(ixsecUL+1))
    exec ('s.xsecUL%i = xsecULExpPlus[ixsecUL]'%(ixsecUL+2))
    exec ('s.xsecUL%i = xsecULExp[ixsecUL]'%(ixsecUL+3))
    exec ('s.xsecUL%i = xsecULExpMinus[ixsecUL]'%(ixsecUL+4))
    exec ('s.xsecUL%i = xsecULExpMinus2[ixsecUL]'%(ixsecUL+5))
    ixsecUL += 4

    xsecTree.Fill()

    fileOut.cd()
    xsecTree.Write()
    
    fileOut.Close()
    
    return outputFileName

if __name__ == '__main__':

    
    parser = OptionParser()
    parser.add_option('-b','--box',dest="box", default="CaloDijet",type="string",
                  help="box name")
    parser.add_option('-m','--model',dest="model", default="gg",type="string",
                  help="signal model name")
    parser.add_option('-l','--lumi',dest="lumi", default=1.981,type="float",
                  help="lumi in fb^-1, e.g.: 0.210")
    parser.add_option('--mass',dest="mass", default='750',type="string",
                  help="mass of resonance")
    parser.add_option('--chi',dest="chi", default='750',type="string",
                  help="chi of resonance")
    parser.add_option('-d','--dir',dest="outDir",default="./",type="string",
                  help="Input/Output directory to store output")
    parser.add_option('--signif',dest="doSignificance",default=False,action='store_true',
                  help="for significance instead of limit")
    parser.add_option('--bayes',dest="bayes",default=False,action='store_true',
                  help="for bayesian limits")
    parser.add_option('--toys',dest="doHybridNew",default=False,action='store_true',
                  help="for toys instead of asymptotic")
    parser.add_option('--xsec',dest="xsec",default=1,type="float",
                  help="reference xsec")
    parser.add_option('--asymp_plus_HybridNew',dest="asymp_plus_HybridNew",default=0.,type="float",
                  help="for limits run with asymptotics at high statistics and hybridnew at low statistics") 
    parser.add_option('--alpha_true',dest="alpha_true",default=0.,type="float",
                  help="alpha true value of signals for 1D limit plot")
    parser.add_option('--width',dest="width",default=0.015,type="float",
                  help="diquark width")              

    (options,args) = parser.parse_args()

    boxInput = options.box
    model = options.model
    lumi = options.lumi
    directory = options.outDir
    doHybridNew = options.doHybridNew
    doSignificance = options.doSignificance
    bayes = options.bayes
    refXsec = options.xsec
    alphatrue=options.alpha_true
    alphap=100*alphatrue
    width = options.width
    
    if abs(width - 0.015) < 1e-6:
        width_name = '0p015'
    elif abs(width - 0.05) < 1e-6:
        width_name = '0p05'
    elif abs(width - 0.1) < 1e-6:
        width_name = '0p1'
    elif abs(width - 0.0043) < 1e-6:
        width_name = '0p0043'    
    else:
        width_name = 'unknown'

    boxes = boxInput.split('_')

    box = boxInput       

    haddOutputs = []

    print ("===>>>",options.mass)
    print ("len(options.mass.split(','))", len(options.mass.split(',')))
    print ("list(eval(options.mass))", list(eval(options.mass)))

    print ("===>>>",options.chi)
    print ("len(options.chi.split(','))", len(options.chi.split(',')))
    print ("list(eval(options.chi))", list(eval(options.chi)))

    if len(options.mass.split(','))==1:
        massIterable = [options.mass]
    else:
        massIterable = list(eval(options.mass))
     
    if len(options.chi.split(','))==1:
        chiIterable = [options.chi]
    else:
        chiIterable = list(eval(options.chi))     
        
        
    for massPoint in massIterable:
      for chiPoint in  chiIterable: 
       if chiPoint-alphatrue*massPoint < 0.01:

        
        
        #print ("MASSPOINT", massPoint)
        #print ("chiPoint", chiPoint)

        
        if massPoint >= options.asymp_plus_HybridNew :
        
         if doSignificance and doHybridNew:
            if not glob.glob(getFileName("higgsCombineSignif",massPoint,chiPoint,boxInput,model,lumi,directory,"HybridNew",0,alphap,width_name)): continue
            print ("INFO: opening %s"%(getFileName("higgsCombineSignif",massPoint,chiPoint,boxInput,model,lumi,directory,"HybridNew",0,alphap,width_name)))
            tFile = rt.TFile.Open(getFileName("higgsCombineSignif",massPoint,chiPoint,boxInput,model,lumi,directory,"HybridNew",0,alphap,width_name))
         elif doHybridNew: 
            #if not glob.glob(getFileName("higgsCombineToys",massPoint,chiPoint,boxInput,model,lumi,directory,"HybridNew",0)): continue
            #print ("INFO: opening %s"%(getFileName("higgsCombineToys",massPoint,chiPoint,boxInput,model,lumi,directory,"HybridNew",0)))
            #tFile = rt.TFile.Open(getFileName("higgsCombineToys",massPoint,chiPoint,boxInput,model,lumi,directory,"HybridNew",0))
            if not glob.glob(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"HybridNew",0,alphap,width_name)): continue
            print ("INFO: opening %s"%(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"HybridNew",0,alphap,width_name)))
            tFile = rt.TFile.Open(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"HybridNew",0,alphap,width_name))
         elif doSignificance: 
            if not glob.glob(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"Significance",0,alphap,width_name)): continue
            print ("INFO: opening %s"%(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"Significance",0,alphap,width_name)))
            tFile = rt.TFile.Open(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"Significance",0,alphap,width_name))
         elif bayes:
            if not glob.glob(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"MarkovChainMC",0,alphap,width_name)): continue
            print ("INFO: opening %s"%(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"MarkovChainMC",0,alphap,width_name)))
            tFile = rt.TFile.Open(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"MarkovChainMC",0,alphap,width_name))
         else:
            if not glob.glob(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"AsymptoticLimits",0,alphap,width_name)): continue
            print ("INFO: opening %s"%(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"AsymptoticLimits",0,alphap,width_name)))
            tFile = rt.TFile.Open(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"AsymptoticLimits",0,alphap,width_name))


        else:
        
          if doSignificance: 
            if not glob.glob(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"Significance",0,alphap,width_name)): continue
            print ("INFO: opening %s"%(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"Significance",0,alphap,width_name)))
            tFile = rt.TFile.Open(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"Significance",0,alphap,width_name))
          elif bayes:
            if not glob.glob(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"MarkovChainMC",0,alphap,width_name)): continue
            print ("INFO: opening %s"%(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"MarkovChainMC",0,alphap,width_name)))
            tFile = rt.TFile.Open(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"MarkovChainMC",0,alphap,width_name))
          else:
            if not glob.glob(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"AsymptoticLimits",0,alphap,width_name)): continue
            print ("INFO: opening %s"%(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"AsymptoticLimits",0,alphap,width_name)))
            tFile = rt.TFile.Open(getFileName("higgsCombine",massPoint,chiPoint,boxInput,model,lumi,directory,"AsymptoticLimits",0,alphap,width_name))       








        try:
            if tFile.InheritsFrom("TFile") is False:
                print ('tFile.InheritsFrom("TFile") is False')
                continue
        except:
            print ('EXCEPTION')
            continue

        limit = tFile.Get("limit")
        try:
            if limit.InheritsFrom("TTree") is False: 
                print ('limit.InheritsFrom("TTree") is False')
                tFile.cd()
                tFile.Close()
                continue
        except:
            print ('EXCEPTION')
            tFile.cd()
            tFile.Close()
            continue
        if (doSignificance or bayes) and limit.GetEntries() < 1: 
            tFile.cd()
            tFile.Close()
            continue
        if not (doSignificance or bayes) and limit.GetEntries() < 5: 
            print ('limit.GetEntries() < 5')
            tFile.cd()
            tFile.Close()
            continue
        limit.Draw('>>elist','','entrylist')
        elist = rt.gDirectory.Get('elist')
        entry = elist.Next()
        limit.GetEntry(entry)
        limits = []

        while True:
            if entry == -1: 
                print ('entry == -1')
                break
            limit.GetEntry(entry)
                
            if doSignificance:
                pvalue = rt.RooStats.SignificanceToPValue(limit.limit)	#convert signif to pvalue
                limits.append(min(0.5,pvalue))
                #limits.append(max(0.0,limit.limit))
            elif bayes:
                limits.append(refXsec*limit.limit)
            else:                    
                limits.append(refXsec*limit.limit)
            entry = elist.Next()
        tFile.cd()
        tFile.Close()

        # no observed limit
        if len(limits)==5:
            limits.append(0)

        # no expected limits
        if len(limits)==1 and bayes:
            if glob.glob(getFileName("higgsCombine",massPoint,boxInput,model,lumi,directory,"MarkovChainMC","*")):
                os.system("rm -rf %s"%(getFileName("higgsCombine",massPoint,boxInput,model,lumi,directory,"MarkovChainMC",123456)))
                os.system("hadd -f %s %s"%(getFileName("higgsCombine",massPoint,boxInput,model,lumi,directory,"MarkovChainMC",123456),getFileName("higgsCombine",massPoint,boxInput,model,lumi,directory,"MarkovChainMC","*")))              
            if not glob.glob(getFileName("higgsCombine",massPoint,boxInput,model,lumi,directory,"MarkovChainMC",123456)):
                print ("expected limit file not found")
                limits.reverse()
                limits.extend([0,0,0,0,0])
                limits.reverse()
            else:
                quants = [0.975, 0.84, 0.5, 0.16, 0.025]
                print ("INFO: opening %s"%(getFileName("higgsCombine",massPoint,boxInput,model,lumi,directory,"MarkovChainMC",123456)))
                tFileExp = rt.TFile.Open(getFileName("higgsCombine",massPoint,boxInput,model,lumi,directory,"MarkovChainMC",123456))
                explimit = tFileExp.Get("limit")         
                explimit.Draw('>>elist','','entrylist')
                elist = rt.gDirectory.Get('elist')
                entry = elist.Next()
                explimit.GetEntry(entry)
                explimits = []                
                while True:
                    if entry == -1: break
                    explimit.GetEntry(entry)
                    #if explimit.limitErr/explimit.limit<0.5:              
                    #    explimits.append(refXsec*explimit.limit)      
                    explimits.append(refXsec*explimit.limit)
                    entry = elist.Next()
                #print (explimits)
                tFileExp.cd()
                tFileExp.Close()
                limits.reverse()
                limits.extend([np.percentile(explimits,100*q) for q in quants])
                limits.reverse()
        
        elif len(limits)==1 and doSignificance:
            limits.reverse()
            limits.extend([0,0,0,0,0])
            limits.reverse()
            
        limits.reverse()
        print (massPoint)
        print (limits)
        
        haddOutput = writeXsecTree(boxInput, model, directory, massPoint,chiPoint,alphap,width_name,[limits[0]],[limits[1]],[limits[2]],[limits[3]],[limits[4]],[limits[5]])
        haddOutputs.append(haddOutput)


    if doHybridNew:
        os.system("hadd -f %s/xsecUL_HybridNew_%s_alpha0p%.0f_W-%s_%s.root %s"%(directory,model,alphap,width_name,boxInput," ".join(haddOutputs))) 
    elif doSignificance:
        os.system("hadd -f %s/xsecUL_ProfileLikelihood_%s_alpha0p%.0f_W-%s_%s.root %s"%(directory,model,alphap,width_name,boxInput," ".join(haddOutputs)))
    else:
        if bayes:
            os.system("hadd -f %s/xsecUL_MarkovChainMC_%s_%s.root %s"%(directory,model,boxInput," ".join(haddOutputs)))
        else:
            os.system("hadd -f %s/xsecUL_Asymptotic_%s_%s.root %s"%(directory,model,boxInput," ".join(haddOutputs)))
