from ROOT import *
import ROOT,sys,os,math
from math import *
import numpy as np
#Run
#python wide_plot_gq.py

#from mass_plot import *

gROOT.ForceStyle()
gStyle.SetLegendBorderSize(0)
gStyle.SetPadTickX(1)
gStyle.SetPadTickY(0)
gStyle.SetPadLeftMargin(0.10)
gStyle.SetPadBottomMargin(0.12)
gStyle.SetPadTopMargin(0.075)
gStyle.SetPadRightMargin(0.12)

def SetCurveStyle(gr,color,lineStyle,lineWidth,markerSize):
    gr.SetMarkerColor(color)
    gr.SetMarkerSize(markerSize)
    gr.SetLineColor(color)
    gr.SetLineWidth(lineWidth)
    gr.SetFillStyle(lineStyle)
    gr.SetFillColor(color)
    return 

def g_q_res(gq):
    #return gq*math.pow(0.5+math.pow(0.25+1/(18*(gq**2)),0.5),0.5)
    return math.pow(3*gq**2+math.pow(gq**2*(9*gq**2+2),0.5),0.5)/math.pow(6,0.5)

def medWidth(gq):
  return 6*gq**2/(4*3.141592653)+1/(12*3.141592653)

def medWidth_res(gq):
    return 6*gq**2/(4*3.141592653)

if __name__=="__main__":

    isGQ=False  ### Should always be false. If true, plot gq instead of gq_prime. ###

    isLogx=False   

    doBoundary=False  ### plot full boundaries for the exclusion limits, not useful now, should always be false ###

    file_wide=TFile("../../EXO_19-012/Wide_resonances/limits/grFinal_PFDMV-g_q-limit_137p5fb.root")

    if isGQ:
        med_min=600
        med_max=3700
    else:
        med_min=1800
        med_max=5100
    med_step=10
    
    exp_wide=file_wide.Get("graph_expected")
    obs_wide=file_wide.Get("graph_observed")    
    wide_All=file_wide.Get("graph_All")
    wide_All_leg=file_wide.Get("My_leg")
    
    ### dijet wide resonance search ###

 #   new_exp_wide=TGraph(0)
#    for mmed in np.linspace(med_min,med_max,num=int((med_max-med_min)/med_step+1)):
#        new_exp_wide.SetPoint(new_exp_wide.GetN(),mmed,g_q_res(exp_wide.Eval(mmed)))
##    SetCurveStyle(exp_wide,kBlack,2,402,0.1)
 #   SetCurveStyle(new_exp_wide,kBlack,2,402,0.1)

 #   new_obs_wide=TGraph(0)
 #   for mmed in np.linspace(med_min,med_max,num=int((med_max-med_min)/med_step+1)):
 #       new_obs_wide.SetPoint(new_obs_wide.GetN(),mmed,g_q_res(obs_wide.Eval(mmed)))
 #   SetCurveStyle(obs_wide,kRed,1,402,0.1)
 #   SetCurveStyle(new_obs_wide,kRed,1,402,0.1)

    ### Plotting ###
    
    canvas=TCanvas("myCanvas","myCanvas",0,0,640,610)
    xmin=med_min
    xmax=med_max
    if isLogx:
        canvas.SetLogx()
        xmin=40
        xmax=8000

    mg=TMultiGraph()

    if isGQ:
        mg.Add(new_exp_wide,"l")
        mg.Add(new_obs_wide,"l")
    else:
        mg.Add(exp_wide,"l")
        mg.Add(obs_wide,"l")

    ymin=0.
    if isGQ:
        ymax=1.42788
    else:
        ymax=1.04
    
    #mg.Draw("apl")
    #mg.GetYaxis().SetRangeUser(ymin,ymax)
    wide_All.Draw("3Lsame")
    wide_All_leg.Draw("same")
    wide_All.GetYaxis().SetRangeUser(ymin,ymax) 
    if isGQ:
        mg.GetYaxis().SetTitle("g_{q}")
    else:
        wide_All.GetYaxis().SetTitle("g_{q}")
    wide_All.GetYaxis().SetTitleOffset(0.8)
    wide_All.GetYaxis().SetTitleSize(0.05)
    wide_All.GetYaxis().SetLabelSize(0.04)
    
    wide_All.GetXaxis().SetLimits(xmin,xmax)
    wide_All.GetXaxis().SetTitle("M_{Med} [TeV]")
    wide_All.GetXaxis().SetTitleOffset(1.)
    wide_All.GetXaxis().SetLabelOffset(1000.)
    wide_All.GetXaxis().SetTitleSize(0.05)
    wide_All.GetXaxis().SetLabelSize(0.042)

    xLab = TLatex()
    xLab.SetTextAlign(22)
    xLab.SetTextSize(0.05)
    xLab.SetTextFont(42)
    for i in range(1,10):
            if i*1000>=med_min and i*1000<=med_max:
                xLab.DrawLatex(i*1000, -0.03, "%g"%i)

    if isLogx:
        #mg.GetXaxis().SetNdivisions(10)
        mg.GetXaxis().SetMoreLogLabels()
        mg.GetXaxis().SetMoreLogLabels()
        #mg.GetXaxis().GetLabels().ChangeLabel(7000,"7000")
        leglabel=TLatex(6900,-0.066,"8000")
        leglabel.SetTextSize(0.04)
        leglabel.SetTextFont(42)
        leglabel.Draw()
        mg.GetXaxis().SetNdivisions(10)
        mg.GetXaxis().SetNoExponent(True); 
    
    minwidth=medWidth(ymin)
    maxwidth=medWidth(ymax)
    print minwidth,
    myFunc=TF1("myFunc"," sqrt( (x-1/(12*3.141592653))*(4*3.141592653)/6)",minwidth,maxwidth)
    y2=TGaxis(xmax, ymin, xmax, ymax,"myFunc",510, "+L")
    y2.SetTitle("#Gamma/M_{Med}")
    y2.SetLabelSize(0.042)
    y2.SetTextFont(42)
    y2.SetLabelFont(42)
    y2.SetTitleSize(0.04)
    y2.SetTitleOffset(1.3)
    y2.Draw()
    canvas.RedrawAxis();
    canvas.Modified();
    canvas.Update();
    ### plot full boundaries for the exclusion limits, not useful now ###

    if doBoundary:
    
        upper_exp_wide=TGraph(0)
        upper_exp_wide.SetPoint(upper_exp_wide.GetN(),600,exp_wide.Eval(600))
        upper_exp_wide.SetPoint(upper_exp_wide.GetN(),600,0.5)
        upper_exp_wide.SetPoint(upper_exp_wide.GetN(),3700,0.5)
        #upper_exp_wide.SetPoint(upper_exp_wide.GetN(),3700,exp_wide.Eval(3700))
        #SetCurveStyle(upper_exp_wide,kRed-10,3004,-402,0.1)
        upper_exp_wide.Draw()

        upper_obs_wide=TGraph(0)
        upper_obs_wide.SetPoint(upper_obs_wide.GetN(),600,obs_wide.Eval(600))
        upper_obs_wide.SetPoint(upper_obs_wide.GetN(),600,0.5)
        upper_obs_wide.SetPoint(upper_obs_wide.GetN(),3700,0.5)
        #upper_obs_wide.SetPoint(upper_obs_wide.GetN(),3700,obs_wide.Eval(3700))
        #SetCurveStyle(upper_obs_wide,kRed+2,3004,-402,0.1)
        upper_obs_wide.Draw("same")

    if isLogx:
        position=0.12
    else:
        position=0.84
        
    if isGQ:
        l0p5=TLine(xmin,0.3,xmax,0.3)
        l0p5.SetLineColor(kGray+1)
        l0p5.SetLineStyle(kDashed)
        l0p5.Draw("same")
        l0p5T=TLatex((xmax-xmin)*position+xmin,0.5+0.05,"g_{q}=0.5, #Gamma/M_{Med}=15%")
        l0p5T.SetTextSize(0.035)
        l0p5T.SetTextColor(kGray+1)
        l0p5T.Draw("same")
    else:
        l0p5=TLine(xmin,0.4,xmax,0.4)
        l0p5.SetLineColor(kGray+1)
        l0p5.SetLineStyle(kDashed)
        #l0p5.Draw("same")
        l0p5T=TLatex((xmax-xmin)*position+xmin,0.4+0.03," #Gamma/M_{Med}=10%")
        l0p5T.SetTextSize(0.035)
        l0p5T.SetTextColor(kGray+1)
        #l0p5T.Draw("same")


    l1p0=TLine(xmin,0.77,xmax,0.77)
    l1p0.SetLineColor(kGray+1)
    l1p0.SetLineStyle(kDotted)
    #l1p0.Draw("same")
    if isGQ:
        l1p0T=TLatex((xmax-xmin)*position+xmin,1+0.05,"g_{q}=1.0, #Gamma/M_{Med}=50%")
    else:
        l1p0T=TLatex((xmax-xmin)*position+xmin,0.77+0.03," #Gamma/M_{Med}=30%")
    l1p0T.SetTextSize(0.035)
    l1p0T.SetTextColor(kGray+1)
    #l1p0T.Draw("same")

  #  leg=TLegend(0.11,0.43,0.5,0.78,"CMS 95% CL Upper Limits")
    leg=TLegend(0.18,0.73,0.57,0.87," 95% CL Upper Limits")
    leg.SetFillStyle(0)
    leg.SetTextSize(0.03)
    leg.Draw()

#    leg_dm=TLegend(0.18,0.21,0.57,0.21,"m_{DM} = 1 GeV")
    leg_dm=TLegend(0.18,0.18,0.57,0.18,"m_{DM} = 1 GeV, g_{DM} = 1")
    leg_dm.SetFillStyle(0)
    leg_dm.SetTextSize(0.03)
    leg_dm.Draw()

 #   leg_gdm=TLegend(0.18,0.17,0.57,0.17,"g_{DM}  = 1")
 #   leg_gdm.SetFillStyle(0)
 #   leg_gdm.SetTextSize(0.03)
 #   leg_gdm.Draw()

    if isLogx:
        offset=10
    else:
        offset=200
    if isGQ:
        leg1=TLatex(xmin+offset,ymax-0.18,"#splitline{Vector/Axial-Vector Mediator}{m_{DM} = 1 GeV, g_{DM} = 1.0}")
    else:
        #leg1=TLatex(xmin+offset,ymax-0.18,"#splitline{Vector/Axial-Vector Mediator}{#Gamma_{DM} = 0}")
        leg1=TLatex(xmin+offset,ymax-0.12,"Vector/Axial-Vector Mediator")
        leg1p=TLatex(xmin+offset,ymax-0.21,"#Gamma_{DM} = 0")
        leg1p.SetTextSize(0.04)
        #leg1p.Draw("same")
    #leg1.SetTextFont(42)
    leg1.SetTextSize(0.04)
    #leg1.Draw("same")

    # CMS

    leg2=TLegend(0.173,0.83,0.57,0.89," #bf{CMS}")
 #   leg2=TLegend(0.09,0.935,0.25,0.935," #bf{CMS #it{Preliminary}}")
    leg2.SetFillStyle(0)
    leg2.SetTextSize(0.045)
    leg2.Draw()

  #  line_test =TLine(med_min,0.221729816,med_max,0.221729816) # coupling corresponding to 0.05 width, plots the line as a test
  #  line_test.SetLineStyle(9)
  #  line_test.SetLineWidth(1)
  #  line_test.SetLineColor(1)
  #  line_test.Draw("same")

#    leg2=TLatex(xmin+100,ymax-0.05,"#bf{CMS}")
 #   leg2=TLatex(0.18,0.86,"#bf{CMS}")
 #   leg2.SetNDC()
 #   leg2.SetTextFont(42)
 #   leg2.SetTextSize(0.045)

    if isLogx:
        lumioffset=5250
    else:
        lumioffset=810
    # lumi
    leg3=TLatex(xmax-240-lumioffset,ymax+0.01,"137 fb^{-1} (13 TeV)")
    leg3.SetTextFont(42)
    leg3.SetTextSize(0.04)
    leg2.Draw("same")
    leg3.Draw("same")
    
    
    if isGQ:
        if isLogx:
            canvas.SaveAs("../../EXO_19-012/Wide_resonances/limits/dijet_combined_gq_logx.pdf")
  #      else:
 #           canvas.SaveAs("Final-EXO-19-012/Stiched/Spin_1/Coupling_plot_higher_widths///dijet_combined_gq.pdf")
    else:
        if isLogx:
            canvas.SaveAs("../../EXO_19-012/Wide_resonances/limits/dijet_combined_gq_logx.pdf")
        else:
            canvas.SaveAs("../../EXO_19-012/Wide_resonances/limits/wide-g_q-withNarrow-limit_137p5fb.pdf")
            canvas.SaveAs("../../EXO_19-012/Wide_resonances/limits/wide-g_q-withNarrow-limit_137p5fb.png")

    
    
