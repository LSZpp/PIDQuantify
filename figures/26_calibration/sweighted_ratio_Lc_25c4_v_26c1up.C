// Kinematic comparison of the Lambda_c^+ -> p K pi sWeighted calibration yields
// between 25c4 MagDown and 26c1 MagUp:
//
//     ( 25c4 MagDown - 26c1 MagUp ) / 26c1 MagUp        [ shown in % ]
//
// with each "total" TH2D (sum of sWeights per (P, ETA) bin) normalised to unit
// integral first, so the map is shape-only. Same presentation as
// sweighted_ratio_26c1_updown.C: kThermometer, zero centred, clamped to +-5%,
// values overlaid to one digit, and bins with fewer than MINEVT sWeighted
// candidates in either dataset painted white. The colour window is +-15% here
// rather than the +-5% used for the polarity maps, because this batch-to-batch
// difference is large enough that +-5% saturated nearly everywhere.
//
// ETA BINNING. The two datasets disagree on one internal edge:
//     25c4 :  1.50, 1.90, 2.08, 2.17, 2.24, ...
//     26c1 :  1.50, 1.90, 2.00, 2.17, 2.24, ...
// Both split [1.90, 2.17] in two, but at a different place, so those bins are
// not comparable one-to-one. They are merged back into a single [1.90, 2.17]
// bin in both histograms, which makes the axes identical (33 bins -> 32) and
// every remaining edge already agrees. Contents are summed and errors added in
// quadrature.
//
// The momentum axes need no such treatment: both datasets use the same 20-bin
// grid 9300 ... 150000.
//
// 26c1 MagUp has no 2d histograms (those jobs were killed on the memory limit),
// so it is read from the 3d (P, ETA, nLongTracks) file and marginalised over
// the full nLongTracks range. Where both exist the marginalised 3d total
// reproduces the 2d total to 2e-5, so this does not bias the comparison.
//
// Run headless with:
//   root -l -b -q sweighted_ratio_Lc_25c4_v_26c1up.C

const double MINEVT = 10.0;   // sWeighted candidates needed to keep a bin
// Wider window than the polarity maps (which use +-5): the batch difference is
// genuinely large, and +-5 saturated over most of the plot.
const double VMIN   = -15.0;  // colour range, %
const double VMAX   = +15.0;

// Fetch the (P, ETA) total, marginalising over nLongTracks for a 3d input.
TH2D *get_total(const char *path, bool is_3d, const char *clone_name){
    TFile *file = TFile::Open(path, "READ");
    if (!file || file->IsZombie()){ printf("Failed to open %s\n", path); return nullptr; }
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

// Merge eta bins 2 and 3 into one, dropping the internal edge the two datasets
// disagree on. Everything else is copied through untouched.
TH2D *merge_eta_bins_2_3(const TH2D *hist, const char *name){
    const TAxis *ax = hist->GetXaxis();
    const TAxis *ay = hist->GetYaxis();
    const int nx = ax->GetNbins();
    const int ny = ay->GetNbins();
    if (ny < 3){ printf("Too few eta bins to merge\n"); return nullptr; }

    std::vector<double> xe(nx + 1);
    for (int i = 1; i <= nx + 1; i++) xe[i - 1] = ax->GetBinLowEdge(i);

    // New eta edges: all the old ones except the boundary between bins 2 and 3.
    std::vector<double> ye;
    for (int j = 1; j <= ny + 1; j++){
        if (j == 3) continue;                  // the disputed edge (2.08 or 2.00)
        ye.push_back(ay->GetBinLowEdge(j));
    }

    TH2D *merged = new TH2D(name, "", nx, xe.data(), (int)ye.size() - 1, ye.data());
    merged->SetDirectory(nullptr);
    for (int i = 1; i <= nx; i++){
        // eta bin 1 is unchanged
        merged->SetBinContent(i, 1, hist->GetBinContent(i, 1));
        merged->SetBinError  (i, 1, hist->GetBinError  (i, 1));
        // old bins 2 and 3 become new bin 2
        const double content = hist->GetBinContent(i, 2) + hist->GetBinContent(i, 3);
        const double error   = std::sqrt(hist->GetBinError(i, 2) * hist->GetBinError(i, 2) +
                                         hist->GetBinError(i, 3) * hist->GetBinError(i, 3));
        merged->SetBinContent(i, 2, content);
        merged->SetBinError  (i, 2, error);
        // the rest shift down by one
        for (int j = 4; j <= ny; j++){
            merged->SetBinContent(i, j - 1, hist->GetBinContent(i, j));
            merged->SetBinError  (i, j - 1, hist->GetBinError  (i, j));
        }
    }
    return merged;
}

bool axes_match(const TH2D *a, const TH2D *b){
    if (a->GetNbinsX() != b->GetNbinsX() || a->GetNbinsY() != b->GetNbinsY()) return false;
    for (int i = 1; i <= a->GetNbinsX() + 1; i++)
        if (std::fabs(a->GetXaxis()->GetBinLowEdge(i) - b->GetXaxis()->GetBinLowEdge(i)) > 1e-6) return false;
    for (int j = 1; j <= a->GetNbinsY() + 1; j++)
        if (std::fabs(a->GetYaxis()->GetBinLowEdge(j) - b->GetYaxis()->GetBinLowEdge(j)) > 1e-6) return false;
    return true;
}

void style(TH2D *hist){
    hist->SetTitle("");
    hist->GetXaxis()->SetTitle("Momentum (MeV/#it{c})");
    hist->GetYaxis()->SetTitle("Pseudorapidity");
    hist->GetZaxis()->SetTitle("( 25c4 MagDown #minus 26c1 MagUp ) / 26c1 MagUp  [%]");
    hist->GetXaxis()->SetTitleSize(.042);
    hist->GetYaxis()->SetTitleSize(.042);
    hist->GetZaxis()->SetTitleSize(.036);
    hist->GetXaxis()->SetLabelSize(.042);
    hist->GetYaxis()->SetLabelSize(.042);
    hist->GetZaxis()->SetLabelSize(.042);
    hist->GetZaxis()->SetTitleOffset(1.35);
    hist->SetMarkerSize(.32);
    hist->SetContour(256);
}

void sweighted_ratio_Lc_25c4_v_26c1up(){
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetNumberContours(256);
    gStyle->SetPaintTextFormat("4.1f");   // percentages, one digit

    const TString d2 = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/Lc/";
    const TString d3 = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/Lc/";

    TH2D *a_raw = get_total(d2 + "effhists-Lc_2025_c4-down-P-DLLp-DLLK>5.0-P.ETA.root",
                            false, "a_raw");
    TH2D *b_raw = get_total(d3 + "effhists-2026_c1_v0-up-P_Lc-DLLp-DLLK>5.0-P.ETA.nLongTracks.root",
                            true,  "b_raw");
    if (!a_raw || !b_raw) return;

    printf("before merge:  25c4 eta edges 2-4 = %.2f %.2f %.2f   |   26c1 eta edges 2-4 = %.2f %.2f %.2f\n",
           a_raw->GetYaxis()->GetBinLowEdge(2), a_raw->GetYaxis()->GetBinLowEdge(3), a_raw->GetYaxis()->GetBinLowEdge(4),
           b_raw->GetYaxis()->GetBinLowEdge(2), b_raw->GetYaxis()->GetBinLowEdge(3), b_raw->GetYaxis()->GetBinLowEdge(4));

    TH2D *a = merge_eta_bins_2_3(a_raw, "a_merged");
    TH2D *b = merge_eta_bins_2_3(b_raw, "b_merged");
    if (!a || !b) return;

    printf("after  merge:  25c4 eta edges 2-4 = %.2f %.2f %.2f   |   26c1 eta edges 2-4 = %.2f %.2f %.2f\n",
           a->GetYaxis()->GetBinLowEdge(2), a->GetYaxis()->GetBinLowEdge(3), a->GetYaxis()->GetBinLowEdge(4),
           b->GetYaxis()->GetBinLowEdge(2), b->GetYaxis()->GetBinLowEdge(3), b->GetYaxis()->GetBinLowEdge(4));
    printf("axes match after merge: %s   (%d x %d bins)\n",
           axes_match(a, b) ? "YES" : "NO", a->GetNbinsX(), a->GetNbinsY());
    if (!axes_match(a, b)) return;

    // Raw yields are kept for the MINEVT test; the shapes are normalised.
    TH2D *a_counts = dynamic_cast<TH2D*>(a->Clone("a_counts")); a_counts->SetDirectory(nullptr);
    TH2D *b_counts = dynamic_cast<TH2D*>(b->Clone("b_counts")); b_counts->SetDirectory(nullptr);
    a->Scale(1. / a->Integral());
    b->Scale(1. / b->Integral());

    TH2D *ratio = dynamic_cast<TH2D*>(a->Clone("ratio"));
    ratio->SetDirectory(nullptr);
    ratio->Add(b, -1.);     // 25c4 MagDown - 26c1 MagUp
    ratio->Divide(b);       // / 26c1 MagUp
    ratio->Scale(100.);     // as a percentage

    int killed = 0;
    for (int i = 1; i <= ratio->GetNbinsX(); i++)
    for (int j = 1; j <= ratio->GetNbinsY(); j++){
        if (a_counts->GetBinContent(i, j) < MINEVT ||
            b_counts->GetBinContent(i, j) < MINEVT){
            ratio->SetBinContent(i, j, 0.);
            ratio->SetBinError  (i, j, 0.);
            killed++;
        }
    }
    printf("%d bins blanked (< %.0f sWeighted candidates in a dataset)\n", killed, MINEVT);

    TH2D *text_layer   = dynamic_cast<TH2D*>(ratio->Clone("txt")); text_layer  ->SetDirectory(nullptr);
    TH2D *colour_layer = dynamic_cast<TH2D*>(ratio->Clone("col")); colour_layer->SetDirectory(nullptr);
    style(text_layer);
    style(colour_layer);

    const double eps = (VMAX - VMIN) * 1.e-4;
    for (int i = 1; i <= colour_layer->GetNbinsX(); i++)
    for (int j = 1; j <= colour_layer->GetNbinsY(); j++){
        if (a_counts->GetBinContent(i, j) < MINEVT ||
            b_counts->GetBinContent(i, j) < MINEVT) continue;   // killed: stays 0 -> white
        double value = colour_layer->GetBinContent(i, j);
        if      (value <= VMIN)          value = VMIN + eps;
        else if (value >= VMAX)          value = VMAX;
        else if (std::fabs(value) < eps) value = eps;
        colour_layer->SetBinContent(i, j, value);
    }
    colour_layer->SetMinimum(VMIN);
    colour_layer->SetMaximum(VMAX);

    gStyle->SetPalette(kThermometer);

    TCanvas *canvas = new TCanvas("canvas_sweighted_ratio_Lc_25c4_v_26c1up",
                                  "canvas_sweighted_ratio_Lc_25c4_v_26c1up", 820, 720);
    canvas->cd();
    gPad->SetTopMargin(.14);
    gPad->SetRightMargin(.20);

    colour_layer->Draw("COL1 Z");
    text_layer  ->Draw("TEXT SAME");

    TLatex lhcb;
    lhcb.SetNDC();
    lhcb.SetTextSize(.05);
    lhcb.DrawLatex(.12, .935, "LHCb #scale[0.8]{Work in Progress}");
    TLatex note;
    note.SetNDC();
    note.SetTextSize(.040);
    note.DrawLatex(.12, .885,
                   "#it{#Lambda}_{c}^{+} #rightarrow #it{p K #pi},  "
                   "25c4 MagDown v 26c1 MagUp");

    canvas->Update();
    canvas->SaveAs("macro_sweighted_ratio_Lc_25c4_v_26c1up.C"  );
    canvas->SaveAs("pdf_figure_sweighted_ratio_Lc_25c4_v_26c1up.pdf");
    canvas->SaveAs("sweighted_ratio_Lc_25c4_v_26c1up.png");
}
