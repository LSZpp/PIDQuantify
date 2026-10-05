// Fraction of Lambda_c^+ -> p K pi sWeighted candidates falling in the momentum
// turn-on bin [9300, 17700] MeV/c, for the five datasets drawn on the Lc
// performance figures:
//
//     frac = Integral(P bin 1) / Integral(all)
//
// taken from the sWeighted "total" histograms ("total" is cut-independent, so
// any cut file carries the same one). Same idea as
// figures/final_calibration/threshold/threshold_fraction.C, but per dataset
// rather than per combined period group, and for the Lc sample.
//
// All five datasets share the 20-bin momentum grid 9300 ... 150000, so bin 1 is
// the same physical interval everywhere and the fractions are comparable.
//
// The 26c1 MagUp 2d jobs were killed on the memory limit, so that series is read
// from the 3d (P, ETA, nLongTracks) histogram and marginalised over the full
// nLongTracks range. Where both exist the marginalised 3d total reproduces the
// 2d total to 2e-5, so this does not bias the fraction.
//
// Run headless with:
//   root -l -b -q threshold_fraction_Lc_26.C

void threshold_fraction_Lc_26(){
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    const TString D2 = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/Lc/";
    const TString D3 = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/Lc/";

    const int N = 5;
    const char *names[N]  = {"25c4 MagDown", "26c1 MagDown", "26c1 MagUp",
                             "26c2 MagDown", "26c2 MagUp"};
    // Axis labels: short, so five of them fit without overlapping.
    const char *labels[N] = {"25c4 #downarrow", "26c1 #downarrow", "26c1 #uparrow",
                             "26c2 #downarrow", "26c2 #uparrow"};
    const TString paths[N] = {
        D2 + "effhists-Lc_2025_c4-down-P-DLLp-DLLK>5.0-P.ETA.root",
        D2 + "effhists-2026_c1_v0-down-P_Lc-DLLp-DLLK>5.0-P.ETA.root",
        D3 + "effhists-2026_c1_v0-up-P_Lc-DLLp-DLLK>5.0-P.ETA.nLongTracks.root",
        D2 + "effhists-2026_c2_v0-down-P_Lc-DLLp-DLLK>5.0-P.ETA.root",
        D2 + "effhists-2026_c2_v0-up-P_Lc-DLLp-DLLK>5.0-P.ETA.root"
    };
    const bool is_3d[N] = {false, false, true, false, false};

    // House series palette, matching perf_L0_Lc_26.cc and the ROC figures.
    const Color_t colours[N] = {kGray + 1, kRed + 2, kAzure + 3, kTeal - 8, kViolet + 2};

    double frac[N];
    for (int i = 0; i < N; i++){
        TFile *file = TFile::Open(paths[i], "READ");
        if (!file || file->IsZombie()){ printf("Failed to open %s\n", paths[i].Data()); return; }

        TH2D *total = nullptr;
        if (is_3d[i]){
            TH3D *total_3d = dynamic_cast<TH3D*>(file->Get("total"));
            if (!total_3d){ printf("No 3d 'total' in %s\n", paths[i].Data()); return; }
            total = dynamic_cast<TH2D*>(total_3d->Project3D("yx"));
        } else {
            total = dynamic_cast<TH2D*>(file->Get("total"));
        }
        if (!total){ printf("No 'total' in %s\n", paths[i].Data()); return; }

        const double threshold = total->Integral(1, 1, 1, total->GetNbinsY());
        const double all       = total->Integral();
        frac[i] = threshold / all;
        printf("%-14s  P bin 1 = [%.0f, %.0f]  threshold=%12.1f  total=%12.1f  frac=%.4f\n",
               names[i], total->GetXaxis()->GetBinLowEdge(1), total->GetXaxis()->GetBinLowEdge(2),
               threshold, all, frac[i]);
        file->Close();
    }

    double ymax = 0.;
    for (int i = 0; i < N; i++) if (frac[i] > ymax) ymax = frac[i];

    TH1F *frame = new TH1F("frame", "", N, .5, N + .5);
    for (int i = 0; i < N; i++) frame->GetXaxis()->SetBinLabel(i + 1, labels[i]);
    frame->SetMinimum(0.);
    frame->SetMaximum(ymax * 1.45);   // headroom for the annotations
    frame->GetXaxis()->SetLabelSize(.055);
    frame->GetYaxis()->SetTitle("s#it{W}eighted fraction with 9.3 GeV/#it{c} < #it{p} < 17.7 GeV/#it{c}");
    frame->GetYaxis()->SetTitleSize(.040);
    frame->GetYaxis()->SetLabelSize(.040);
    frame->GetYaxis()->SetTitleOffset(1.5);

    TCanvas *canvas = new TCanvas("canvas_threshold_fraction_Lc_26",
                                  "canvas_threshold_fraction_Lc_26", 800, 600);
    canvas->cd();
    canvas->SetLeftMargin(.15);
    gPad->SetTopMargin(.05);
    frame->Draw();

    for (int i = 0; i < N; i++){
        TGraph *point = new TGraph(1);
        point->SetPoint(0, i + 1, frac[i]);
        point->SetMarkerColor(colours[i]);
        point->SetMarkerStyle(24);      // open circle, as on the performance figures
        point->SetMarkerSize(2.2);
        point->SetLineColor(colours[i]);
        point->Draw("P SAME");
    }

    TLatex lhcb;
    lhcb.SetNDC();
    lhcb.SetTextSize(.05);
    lhcb.DrawLatex(.20, .88, "LHCb #scale[0.8]{Work in Progress}");
    TLatex note;
    note.SetNDC();
    note.SetTextSize(.040);
    note.DrawLatex(.20, .82, "#it{#Lambda}_{c}^{+} #rightarrow #it{p K #pi}");

    canvas->Update();
    canvas->SaveAs("macro_threshold_fraction_Lc_26.C"  );
    canvas->SaveAs("pdf_figure_threshold_fraction_Lc_26.pdf");
    canvas->SaveAs("threshold_fraction_Lc_26.png");
}
