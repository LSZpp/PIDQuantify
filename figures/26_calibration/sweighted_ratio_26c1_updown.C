// Polarity comparison of the 2026_c1 sWeighted calibration yields.
//
// For each probe sample the "total" TH2D (sum of sWeights per (P, ETA) bin) is
// taken for both polarities, each normalised to unit integral so the maps are
// shape-only, and the fractional difference
//
//     ( MagDown - MagUp ) / MagUp        [ shown in % ]
//
// is drawn with kThermometer, zero centred, clamped to +-5%.
//
// Follows the two-layer recipe of
// figures/final_calibration/2d_differences/perf_finals_2d.C:
//   * a colour layer whose values are clamped into [-5, +5], so bins beyond the
//     range show the floor / ceiling colour instead of being whited by ROOT;
//   * a text layer carrying the true values, so an out-of-range bin still
//     prints its real number;
//   * bins with fewer than MINEVT sWeighted candidates in either polarity are
//     set to exactly 0 in both layers, which "COL1" paints white and "TEXT"
//     leaves unlabelled.
//
// Samples: proton from Lambda^0 and from Lambda_c^+, plus the dedicated K and
// Pi calibration samples. The proton MagUp 2d jobs were killed on the memory
// limit, so that polarity is read from the 3d (P, ETA, nLongTracks) histograms
// and marginalised over the full nLongTracks range. That is safe: where both
// exist (Lc MagDown) the marginalised 3d total reproduces the 2d total to
// 2e-5 overall and better than 0.5% in every filled bin.
//
// The "total" histogram is cut-independent, so any cut file carries the same
// one.
//
// Run headless with:
//   root -l -b -q sweighted_ratio_26c1_updown.C

const double MINEVT = 10.0;   // sWeighted candidates needed to keep a bin
const double VMIN   = -5.0;   // colour range, %
const double VMAX   = +5.0;

// Fetch the (P, ETA) total, marginalising over nLongTracks for a 3d input.
TH2D *get_total(const char *path, bool is_3d, const char *clone_name){
    TFile *file = TFile::Open(path, "READ");
    if (!file || file->IsZombie()){
        printf("Failed to open %s\n", path);
        return nullptr;
    }
    TH2D *total = nullptr;
    if (is_3d){
        TH3D *total_3d = dynamic_cast<TH3D*>(file->Get("total"));
        if (!total_3d){ printf("No 3d 'total' in %s\n", path); file->Close(); return nullptr; }
        total = dynamic_cast<TH2D*>(total_3d->Project3D("yx"));
    } else {
        total = dynamic_cast<TH2D*>(file->Get("total"));
    }
    if (!total){ printf("No 'total' in %s\n", path); file->Close(); return nullptr; }
    TH2D *copy = dynamic_cast<TH2D*>(total->Clone(clone_name));
    copy->SetDirectory(nullptr);
    file->Close();
    return copy;
}

void style(TH2D *hist){
    hist->SetTitle("");
    hist->GetXaxis()->SetTitle("Momentum (MeV/#it{c})");
    hist->GetYaxis()->SetTitle("Pseudorapidity");
    hist->GetZaxis()->SetTitle("( MagDown #minus MagUp ) / MagUp  [%]");
    hist->GetXaxis()->SetTitleSize(.042);
    hist->GetYaxis()->SetTitleSize(.042);
    hist->GetZaxis()->SetTitleSize(.042);
    hist->GetXaxis()->SetLabelSize(.042);
    hist->GetYaxis()->SetLabelSize(.042);
    hist->GetZaxis()->SetLabelSize(.042);
    hist->GetZaxis()->SetTitleOffset(1.25);
    hist->SetMarkerSize(.32);   // 20 x 33 bins: scales the overlaid text
    hist->SetContour(256);
}

void draw_ratio(const char *path_down, bool down_3d,
                const char *path_up,   bool up_3d,
                const char *tag, const char *annotation){
    TH2D *down = get_total(path_down, down_3d, Form("down_%s", tag));
    TH2D *up   = get_total(path_up,   up_3d,   Form("up_%s",   tag));
    if (!down || !up) return;

    // Keep the raw yields: the MINEVT test is on candidates, not on the
    // normalised shapes.
    TH2D *down_raw = dynamic_cast<TH2D*>(down->Clone(Form("downraw_%s", tag)));
    TH2D *up_raw   = dynamic_cast<TH2D*>(up  ->Clone(Form("upraw_%s",   tag)));
    down_raw->SetDirectory(nullptr);
    up_raw  ->SetDirectory(nullptr);

    // Shape-only comparison: normalise each polarity to unit integral first, so
    // the ratio reflects the kinematic distribution and not the sample size.
    down->Scale(1. / down->Integral());
    up  ->Scale(1. / up  ->Integral());

    TH2D *ratio = dynamic_cast<TH2D*>(down->Clone(Form("ratio_%s", tag)));
    ratio->SetDirectory(nullptr);
    ratio->Add(up, -1.);        // MagDown - MagUp
    ratio->Divide(up);          // / MagUp
    ratio->Scale(100.);         // as a percentage

    // Kill the sparse bins in both layers: exactly 0 is what COL1 whites out.
    int killed = 0;
    for (int i = 1; i <= ratio->GetNbinsX(); i++)
    for (int j = 1; j <= ratio->GetNbinsY(); j++){
        if (down_raw->GetBinContent(i, j) < MINEVT ||
            up_raw  ->GetBinContent(i, j) < MINEVT){
            ratio->SetBinContent(i, j, 0.);
            ratio->SetBinError  (i, j, 0.);
            killed++;
        }
    }

    TH2D *text_layer   = dynamic_cast<TH2D*>(ratio->Clone(Form("txt_%s", tag)));
    TH2D *colour_layer = dynamic_cast<TH2D*>(ratio->Clone(Form("col_%s", tag)));
    text_layer  ->SetDirectory(nullptr);
    colour_layer->SetDirectory(nullptr);
    style(text_layer);
    style(colour_layer);

    // Clamp the colour layer into the window so out-of-range bins take the
    // floor / ceiling colour rather than being dropped, and nudge anything that
    // lands on exactly 0 so it is not mistaken for a killed bin.
    const double eps = (VMAX - VMIN) * 1.e-4;
    for (int i = 1; i <= colour_layer->GetNbinsX(); i++)
    for (int j = 1; j <= colour_layer->GetNbinsY(); j++){
        if (down_raw->GetBinContent(i, j) < MINEVT ||
            up_raw  ->GetBinContent(i, j) < MINEVT) continue;   // killed: stays 0 -> white
        double value = colour_layer->GetBinContent(i, j);
        if      (value <= VMIN)             value = VMIN + eps;
        else if (value >= VMAX)             value = VMAX;
        else if (std::fabs(value) < eps)    value = eps;
        colour_layer->SetBinContent(i, j, value);
    }
    colour_layer->SetMinimum(VMIN);
    colour_layer->SetMaximum(VMAX);

    gStyle->SetPalette(kThermometer);

    TString canvas_name = TString("canvas_sweighted_ratio_26c1_") + tag;
    TCanvas *canvas = new TCanvas(canvas_name, canvas_name, 820, 720);
    canvas->cd();
    gPad->SetTopMargin(.14);    // annotations live above the frame, not on the bins
    gPad->SetRightMargin(.19);  // room for the palette

    colour_layer->Draw("COL1 Z");
    text_layer  ->Draw("TEXT SAME");

    TLatex lhcb;
    lhcb.SetNDC();
    lhcb.SetTextSize(.05);
    lhcb.DrawLatex(.12, .935, "LHCb #scale[0.8]{Work in Progress}");
    TLatex note;
    note.SetNDC();
    note.SetTextSize(.040);
    note.DrawLatex(.12, .885, annotation);

    canvas->Update();

    printf("%-6s  %d bins blanked (< %.0f sWeighted candidates in a polarity)\n",
           tag, killed, MINEVT);

    TString stub = TString("sweighted_ratio_26c1_") + tag;
    canvas->SaveAs("macro_"      + stub + ".C"  );
    canvas->SaveAs("pdf_figure_" + stub + ".pdf");
    canvas->SaveAs(               stub + ".png");
}

void sweighted_ratio_26c1_updown(){
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetNumberContours(256);
    gStyle->SetPaintTextFormat("4.1f");   // percentages, one digit

    const TString d2 = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/";
    const TString d3 = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/";

    // Proton from Lambda^0: MagDown 2d, MagUp 3d.
    draw_ratio(d2 + "newL0/effhists-2026_c1_v0-down-P-DLLp-DLLK>5.0-P.ETA.root", false,
               d3 + "newL0/effhists-2026_c1_v0-up-P-DLLp-DLLK>5.0-P.ETA.nLongTracks.root", true,
               "L0_p", "#it{p} from #it{#Lambda}^{0} #rightarrow #it{p #pi},  2026 c1");

    // Proton from Lambda_c^+: MagDown 2d, MagUp 3d.
    draw_ratio(d2 + "Lc/effhists-2026_c1_v0-down-P_Lc-DLLp-DLLK>5.0-P.ETA.root", false,
               d3 + "Lc/effhists-2026_c1_v0-up-P_Lc-DLLp-DLLK>5.0-P.ETA.nLongTracks.root", true,
               "Lc_p", "#it{p} from #it{#Lambda}_{c}^{+} #rightarrow #it{p K #pi},  2026 c1");

    // K and Pi calibration samples: both polarities in 2d.
    draw_ratio(d2 + "K/effhists-2026_s26c1_beta_fixed-down-K-DLLK>5.0-P.ETA.root", false,
               d2 + "K/effhists-2026_s26c1_beta_fixed-up-K-DLLK>5.0-P.ETA.root",   false,
               "K", "#it{K} calibration sample,  2026 c1");

    draw_ratio(d2 + "Pi/effhists-2026_s26c1_beta_fixed-down-Pi-DLLK>5.0-P.ETA.root", false,
               d2 + "Pi/effhists-2026_s26c1_beta_fixed-up-Pi-DLLK>5.0-P.ETA.root",   false,
               "Pi", "#it{#pi} calibration sample,  2026 c1");
}
