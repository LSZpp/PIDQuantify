// Lc vs new-L0 kinematics in the L0 turn-on bin [9300,17700] MeV, 24b8 (sWeighted).
// (1) normalised p distribution, overlaid;  (2) per-eta-bin momentum centre-of-mass
// <p> = sum(w*p)/sum(w) (a sWeighted-mean TProfile), overlaid. L0 = kRed+1, Lc = kBlue+2.
// Run:  root -l -b -q kinematics_threshold_24b8.C

void kinematics_threshold_24b8(){
    gStyle->SetOptStat(0);
    const std::string OUT = "/home/lins/u3_PIDQuantify/figures/final_calibration/threshold/";
    double ee[] = {1.5,1.9,2.08,2.17,2.24,2.31,2.38,2.45,2.52,2.59,2.66,2.73,2.79,
                   2.85,2.91,2.97,3.04,3.11,3.18,3.27,3.36,3.45,3.54,3.63,3.72,3.81,
                   3.9,4.0,4.1,4.25,4.4,4.55,4.75,5.0};
    int nE = 33;

    auto l0 = ROOT::RDataFrame("DecayTree","/data/lhcb/users/lins/u3_PIDQuantify/threshold/L0.root").Filter("sWeight==sWeight").Define("pGeV","p_P/1000.0");
    auto lc = ROOT::RDataFrame("DecayTree","/data/lhcb/users/lins/u3_PIDQuantify/threshold/Lc.root").Filter("sWeight==sWeight").Define("pGeV","p_P/1000.0");

    // (1) normalised sWeighted p distribution
    auto hp0 = l0.Histo1D(ROOT::RDF::TH1DModel("hp0","",42,9.3,17.7),"pGeV","sWeight");
    auto hp1 = lc.Histo1D(ROOT::RDF::TH1DModel("hp1","",42,9.3,17.7),"pGeV","sWeight");
    TH1D *a=(TH1D*)hp0->Clone("a"); a->Scale(1./a->Integral());
    TH1D *b=(TH1D*)hp1->Clone("b"); b->Scale(1./b->Integral());
    a->SetLineColor(kRed+1);  a->SetLineWidth(2);
    b->SetLineColor(kBlue+2); b->SetLineWidth(2);
    a->SetTitle(""); a->GetXaxis()->SetTitle("#it{p} [GeV/#it{c}]"); a->GetYaxis()->SetTitle("Normalised");
    a->SetMinimum(0.); a->SetMaximum(1.15*std::max(a->GetMaximum(),b->GetMaximum()));
    TCanvas c1("c1","c1",900,700); c1.SetLeftMargin(0.12);
    a->Draw("HIST"); b->Draw("HIST SAME");
    TLegend lg1(.65,.76,.92,.90); lg1.SetBorderSize(0); lg1.SetFillStyle(0);
    lg1.AddEntry(a,"L0","l"); lg1.AddEntry(b,"#it{#Lambda}_{#it{c}}","l"); lg1.Draw();
    c1.SaveAs((OUT+"kin_pdist_24b8.pdf").c_str());

    // (2) per-eta-bin momentum centre-of-mass (sWeighted mean p). Convert each
    // profile to a graph of only the FILLED bins, so the line stops where a sample
    // runs out of events (no spurious vertical drop into the empty bins).
    auto pr0 = l0.Profile1D(ROOT::RDF::TProfile1DModel("pr0","",nE,ee),"p_ETA","pGeV","sWeight");
    auto pr1 = lc.Profile1D(ROOT::RDF::TProfile1DModel("pr1","",nE,ee),"p_ETA","pGeV","sWeight");

    auto graph = [](TProfile *pr, Color_t c){
        TGraphErrors *g = new TGraphErrors();
        for (int b=1; b<=pr->GetNbinsX(); b++){
            if (pr->GetBinEntries(b) <= 0) continue;                  // skip empty bins
            int n = g->GetN();
            g->SetPoint(n, pr->GetBinCenter(b), pr->GetBinContent(b));
            g->SetPointError(n, pr->GetBinWidth(b)/2., pr->GetBinError(b));   // x-err = half bin width
        }
        g->SetLineColor(c); g->SetMarkerColor(c); g->SetMarkerStyle(24); g->SetLineWidth(2);
        return g;
    };
    TGraphErrors *g0 = graph(pr0.GetPtr(), kRed+1);
    TGraphErrors *g1 = graph(pr1.GetPtr(), kBlue+2);

    TH1F *fr = new TH1F("fr","",1,1.5,5.0);
    fr->SetMinimum(9.3); fr->SetMaximum(17.7);
    fr->GetXaxis()->SetTitle("#it{#eta}");
    fr->GetYaxis()->SetTitle("s#it{W}eighted first moment in  #it{p} [GeV/#it{c}]");
    fr->GetYaxis()->SetTitleOffset(1.2);
    TCanvas c2("c2","c2",900,700); c2.SetLeftMargin(0.12);
    fr->Draw();
    g0->Draw("LP SAME"); g1->Draw("LP SAME");
    TLegend lg2(.60,.10,.80,.30); lg2.SetBorderSize(0); lg2.SetFillStyle(0);
    lg2.AddEntry(g0,"#it{#Lambda}^{0} #rightarrow #it{p#pi}","lpe");
    lg2.AddEntry(g1,"#it{#Lambda}_{#it{c}} #rightarrow #it{pK#pi}","lpe"); lg2.Draw();
    c2.SaveAs((OUT+"kin_com_vs_eta_24b8.pdf").c_str());
}
