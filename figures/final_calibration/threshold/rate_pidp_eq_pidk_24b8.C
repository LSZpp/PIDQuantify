// 2D sWeighted rate of (p_PID_P == p_PID_K) for 24b8 new L0, zoomed into the L0
// turn-on bin [9300,17700] MeV split into 4. COL1 Z, kRainbow; bins with <100 raw
// entries whitened. Run:  root -l -b -q rate_pidp_eq_pidk_24b8.C

void rate_pidp_eq_pidk_24b8(){
    gStyle->SetOptStat(0);
    gStyle->SetPalette(kRainbow);
    gStyle->SetNumberContours(256);

    double pe[] = {9.3, 11.7, 13.7, 15.7, 17.7};                                  // GeV/c
    double ee[] = {1.5,1.9,2.08,2.17,2.24,2.31,2.38,2.45,2.52,2.59,2.66,2.73,2.79,
                   2.85,2.91,2.97,3.04,3.11,3.18,3.27,3.36,3.45,3.54,3.63,3.72,3.81,
                   3.9,4.0,4.1,4.25,4.4,4.55,4.75,5.0};
    int nP = 4, nE = 33;

    ROOT::RDataFrame df("DecayTree", "/data/lhcb/users/lins/u3_PIDQuantify/threshold/L0.root");
    auto d = df.Filter("sWeight == sWeight")                       // drop NaN sWeight (failed-fit events)
               .Define("pGeV", "p_P/1000.0")
               .Define("wEq",  "p_PID_P == p_PID_K ? sWeight : 0.0");
    auto num = d.Histo2D(ROOT::RDF::TH2DModel("num","",nP,pe,nE,ee), "pGeV","p_ETA","wEq");
    auto den = d.Histo2D(ROOT::RDF::TH2DModel("den","",nP,pe,nE,ee), "pGeV","p_ETA","sWeight");
    auto cnt = d.Histo2D(ROOT::RDF::TH2DModel("cnt","",nP,pe,nE,ee), "pGeV","p_ETA");

    TH2D *rate = (TH2D*)num->Clone("rate");
    rate->Divide(den.GetPtr());
    for (int i=1;i<=nP;i++) for (int j=1;j<=nE;j++)
        if (cnt->GetBinContent(i,j) < 100) rate->SetBinContent(i,j,0.);   // whiten low-stat

    rate->SetTitle("");
    rate->GetXaxis()->SetTitle("#it{p} [GeV/#it{c}]");
    rate->GetYaxis()->SetTitle("#it{#eta}");
    rate->GetYaxis()->SetTitleOffset(0.7);
    rate->SetMinimum(0.); rate->SetContour(256);   // max auto-ranges to reveal structure

    TCanvas *c = new TCanvas("c","c",900,950);
    c->SetRightMargin(0.14); c->SetLeftMargin(0.10);
    rate->Draw("COL1 Z");
    c->SaveAs("/home/lins/u3_PIDQuantify/figures/final_calibration/threshold/rate_pidp_eq_pidk_24b8.pdf");
}
