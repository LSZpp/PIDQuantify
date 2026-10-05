// Profiled kinematics for Lambda_c^+ -> p K pi, 25c4 MagDown v 26c1 MagUp,
// from the sWeighted "total" histograms. Companion to the 2d map in
// sweighted_ratio_Lc_25c4_v_26c1up.C: the same two datasets, projected.
//
// Produces
//   * pdf_figure_kinematics_Lc_25c4_v_26c1up_eta   - the eta distribution
//   * pdf_figure_kinematics_Lc_25c4_v_26c1up_p     - the momentum distribution
//   * <OUTDIR>/p_dist_etabin_NN_<lo>_<hi>.pdf      - the momentum distribution
//                                                    in each eta bin separately
//
// Each figure carries a lower pad with ( 25c4 - 26c1 ) / 26c1 in %.
//
// NORMALISATION. The two marginal figures are bin fractions of the whole
// sample, so they answer "does the sample sit at different kinematics". The
// per-eta-bin figures are normalised WITHIN their eta slice, so they answer the
// narrower question "given an eta, is the momentum spectrum shaped
// differently" - the slice-to-slice population difference is already the
// content of the eta figure, and leaving it in would swamp the shape.
// Unequal bin widths are divided out against a reference width, per house
// style, so bin height is comparable across the axis.
//
// ETA BINNING. 25c4 splits [1.90, 2.17] at 2.08 and 26c1 at 2.00, so those two
// bins are merged into one in both datasets (33 bins -> 32) before anything
// else. Every other edge already agrees, as does the whole momentum axis.
//
// 26c1 MagUp exists only as 3d histograms; it is marginalised over the full
// nLongTracks range, which reproduces the 2d total to 2e-5 where both exist.
//
// Run headless with:
//   root -l -b -q kinematics_profiles_Lc_25c4_v_26c1up.C

const char *OUTDIR = "kinematics_by_eta_Lc_25c4_v_26c1up";

const Color_t COL_A = kGray + 1;    // 25c4 MagDown, as on the performance figures
const Color_t COL_B = kAzure + 3;   // 26c1 MagUp

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

// Merge eta bins 2 and 3, dropping the edge the two datasets disagree on.
TH2D *merge_eta_bins_2_3(const TH2D *hist, const char *name){
    const TAxis *ax = hist->GetXaxis();
    const TAxis *ay = hist->GetYaxis();
    const int nx = ax->GetNbins(), ny = ay->GetNbins();
    std::vector<double> xe(nx + 1);
    for (int i = 1; i <= nx + 1; i++) xe[i - 1] = ax->GetBinLowEdge(i);
    std::vector<double> ye;
    for (int j = 1; j <= ny + 1; j++){ if (j == 3) continue; ye.push_back(ay->GetBinLowEdge(j)); }

    TH2D *merged = new TH2D(name, "", nx, xe.data(), (int)ye.size() - 1, ye.data());
    merged->SetDirectory(nullptr);
    for (int i = 1; i <= nx; i++){
        merged->SetBinContent(i, 1, hist->GetBinContent(i, 1));
        merged->SetBinError  (i, 1, hist->GetBinError  (i, 1));
        merged->SetBinContent(i, 2, hist->GetBinContent(i, 2) + hist->GetBinContent(i, 3));
        merged->SetBinError  (i, 2, std::sqrt(hist->GetBinError(i, 2) * hist->GetBinError(i, 2) +
                                              hist->GetBinError(i, 3) * hist->GetBinError(i, 3)));
        for (int j = 4; j <= ny; j++){
            merged->SetBinContent(i, j - 1, hist->GetBinContent(i, j));
            merged->SetBinError  (i, j - 1, hist->GetBinError  (i, j));
        }
    }
    return merged;
}

// Bin fraction, then divide out the bin width against a reference width so that
// unequal bins are comparable by height.
void to_density(TH1D *hist, double reference_width){
    const double integral = hist->Integral();
    if (integral <= 0.) return;
    hist->Scale(1. / integral);
    for (int i = 1; i <= hist->GetNbinsX(); i++){
        const double weight = reference_width / hist->GetBinWidth(i);
        hist->SetBinContent(i, hist->GetBinContent(i) * weight);
        hist->SetBinError  (i, hist->GetBinError  (i) * weight);
    }
}

TGraphErrors *to_graph(const TH1D *hist, Color_t colour, Size_t size){
    TGraphErrors *graph = new TGraphErrors();
    for (int i = 1; i <= hist->GetNbinsX(); i++){
        graph->SetPoint     (i - 1, hist->GetBinCenter(i),      hist->GetBinContent(i));
        graph->SetPointError(i - 1, .5 * hist->GetBinWidth(i),  hist->GetBinError(i));
    }
    graph->SetLineWidth(2);
    graph->SetLineColor(colour);
    graph->SetMarkerColor(colour);
    graph->SetMarkerStyle(24);
    graph->SetMarkerSize(size);
    graph->SetTitle("");
    return graph;
}

// One comparison figure: two distributions on top, their relative difference
// below. a_in / b_in are consumed (normalised in place).
void draw_pair(TH1D *a_in, TH1D *b_in, const char *x_title, const char *y_title,
               double reference_width, const char *annotation, const char *out_path,
               double x_lo, double x_hi){
    TH1D *a = dynamic_cast<TH1D*>(a_in->Clone(Form("%s_a", out_path)));
    TH1D *b = dynamic_cast<TH1D*>(b_in->Clone(Form("%s_b", out_path)));
    a->SetDirectory(nullptr); b->SetDirectory(nullptr);

    // Relative difference from the bin fractions, before the width weighting
    // (which cancels in a ratio anyway).
    TH1D *fa = dynamic_cast<TH1D*>(a->Clone(Form("%s_fa", out_path))); fa->SetDirectory(nullptr);
    TH1D *fb = dynamic_cast<TH1D*>(b->Clone(Form("%s_fb", out_path))); fb->SetDirectory(nullptr);
    if (fa->Integral() > 0.) fa->Scale(1. / fa->Integral());
    if (fb->Integral() > 0.) fb->Scale(1. / fb->Integral());
    TH1D *rel = dynamic_cast<TH1D*>(fa->Clone(Form("%s_rel", out_path))); rel->SetDirectory(nullptr);
    rel->Add(fb, -1.);
    rel->Divide(fb);
    rel->Scale(100.);
    for (int i = 1; i <= rel->GetNbinsX(); i++)
        if (fb->GetBinContent(i) <= 0.){ rel->SetBinContent(i, 0.); rel->SetBinError(i, 0.); }

    to_density(a, reference_width);
    to_density(b, reference_width);

    TGraphErrors *ga = to_graph(a, COL_A, 1.3);
    TGraphErrors *gb = to_graph(b, COL_B, 1.1);
    TGraphErrors *gr = to_graph(rel, kBlack, 1.0);

    TCanvas *canvas = new TCanvas(Form("c_%s", out_path), out_path, 800, 750);

    TPad *top = new TPad("top", "top", 0, .32, 1, 1);
    top->SetBottomMargin(.02); top->SetLeftMargin(.15); top->SetTopMargin(.06);
    top->Draw(); top->cd();
    double ymax = 0.;
    for (int i = 1; i <= a->GetNbinsX(); i++){
        ymax = std::max(ymax, a->GetBinContent(i) + a->GetBinError(i));
        ymax = std::max(ymax, b->GetBinContent(i) + b->GetBinError(i));
    }
    ga->Draw("APE");
    ga->GetXaxis()->SetLimits(x_lo, x_hi);
    ga->GetXaxis()->SetLabelSize(0.);
    ga->GetYaxis()->SetTitle(y_title);
    ga->GetYaxis()->SetTitleSize(.055);
    ga->GetYaxis()->SetLabelSize(.050);
    ga->GetYaxis()->SetTitleOffset(1.25);
    ga->SetMinimum(0.);
    ga->SetMaximum(ymax * 1.55);
    gb->Draw("PE SAME");

    TLatex lhcb; lhcb.SetNDC(); lhcb.SetTextSize(.065);
    lhcb.DrawLatex(.19, .86, "LHCb #scale[0.8]{Work in Progress}");
    TLatex note; note.SetNDC(); note.SetTextSize(.052);
    note.DrawLatex(.19, .79, annotation);

    TLegend *legend = new TLegend(.60, .68, .88, .88);
    legend->SetBorderSize(0); legend->SetFillStyle(0); legend->SetTextSize(.052);
    legend->AddEntry(ga, "25c4 MagDown", "PLE");
    legend->AddEntry(gb, "26c1 MagUp",   "PLE");
    legend->Draw();

    canvas->cd();
    TPad *bottom = new TPad("bottom", "bottom", 0, 0, 1, .32);
    bottom->SetTopMargin(.03); bottom->SetBottomMargin(.34); bottom->SetLeftMargin(.15);
    bottom->Draw(); bottom->cd();
    gr->Draw("APE");
    gr->GetXaxis()->SetLimits(x_lo, x_hi);
    gr->GetXaxis()->SetTitle(x_title);
    gr->GetXaxis()->SetTitleSize(.115);
    gr->GetXaxis()->SetLabelSize(.105);
    gr->GetXaxis()->SetTitleOffset(1.25);
    gr->GetYaxis()->SetTitle("#Delta [%]");
    gr->GetYaxis()->SetTitleSize(.115);
    gr->GetYaxis()->SetLabelSize(.105);
    gr->GetYaxis()->SetTitleOffset(.58);
    gr->GetYaxis()->SetNdivisions(505);
    gr->SetMinimum(-29.); gr->SetMaximum(29.);
    TLine *zero = new TLine(x_lo, 0., x_hi, 0.);
    zero->SetLineStyle(2); zero->SetLineColor(kGray + 2); zero->Draw();
    gr->Draw("PE SAME");

    canvas->Update();
    canvas->SaveAs(out_path);
    delete canvas;
}

void kinematics_profiles_Lc_25c4_v_26c1up(){
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    const TString d2 = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/Lc/";
    const TString d3 = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/3d/Lc/";

    TH2D *a_raw = get_total(d2 + "effhists-Lc_2025_c4-down-P-DLLp-DLLK>5.0-P.ETA.root", false, "a_raw");
    TH2D *b_raw = get_total(d3 + "effhists-2026_c1_v0-up-P_Lc-DLLp-DLLK>5.0-P.ETA.nLongTracks.root", true, "b_raw");
    if (!a_raw || !b_raw) return;

    TH2D *a = merge_eta_bins_2_3(a_raw, "a_merged");
    TH2D *b = merge_eta_bins_2_3(b_raw, "b_merged");
    printf("merged eta axis: %d bins; momentum axis: %d bins %.0f..%.0f\n",
           a->GetNbinsY(), a->GetNbinsX(),
           a->GetXaxis()->GetBinLowEdge(1), a->GetXaxis()->GetBinLowEdge(a->GetNbinsX() + 1));

    const double p_lo = a->GetXaxis()->GetBinLowEdge(1);
    const double p_hi = a->GetXaxis()->GetBinLowEdge(a->GetNbinsX() + 1);

    // --- marginal distributions -------------------------------------------
    TH1D *a_eta = a->ProjectionY("a_eta", 1, a->GetNbinsX(), "e");
    TH1D *b_eta = b->ProjectionY("b_eta", 1, b->GetNbinsX(), "e");
    a_eta->SetDirectory(nullptr); b_eta->SetDirectory(nullptr);
    draw_pair(a_eta, b_eta, "Pseudorapidity", "Normalised candidates / 0.1", .1,
              "#it{#Lambda}_{c}^{+} #rightarrow #it{p K #pi}",
              "pdf_figure_kinematics_Lc_25c4_v_26c1up_eta.pdf", 1.5, 5.);

    TH1D *a_p = a->ProjectionX("a_p", 1, a->GetNbinsY(), "e");
    TH1D *b_p = b->ProjectionX("b_p", 1, b->GetNbinsY(), "e");
    a_p->SetDirectory(nullptr); b_p->SetDirectory(nullptr);
    draw_pair(a_p, b_p, "Momentum (MeV/#it{c})", "Normalised candidates / (1000 MeV/#it{c})", 1000.,
              "#it{#Lambda}_{c}^{+} #rightarrow #it{p K #pi}",
              "pdf_figure_kinematics_Lc_25c4_v_26c1up_p.pdf", p_lo, p_hi);

    // --- momentum distribution in each eta bin ----------------------------
    gSystem->mkdir(OUTDIR, kTRUE);
    for (int j = 1; j <= a->GetNbinsY(); j++){
        const double eta_lo = a->GetYaxis()->GetBinLowEdge(j);
        const double eta_hi = a->GetYaxis()->GetBinUpEdge(j);

        TH1D *a_slice = a->ProjectionX(Form("a_slice_%d", j), j, j, "e");
        TH1D *b_slice = b->ProjectionX(Form("b_slice_%d", j), j, j, "e");
        a_slice->SetDirectory(nullptr); b_slice->SetDirectory(nullptr);
        if (a_slice->Integral() <= 0. || b_slice->Integral() <= 0.){
            printf("eta bin %2d [%.2f, %.2f]: empty in one dataset, skipped\n", j, eta_lo, eta_hi);
            continue;
        }
        printf("eta bin %2d [%.2f, %.2f]: 25c4 %10.1f candidates, 26c1 %10.1f\n",
               j, eta_lo, eta_hi, a_slice->Integral(), b_slice->Integral());

        draw_pair(a_slice, b_slice, "Momentum (MeV/#it{c})",
                  "Normalised candidates / (1000 MeV/#it{c})", 1000.,
                  Form("#it{#Lambda}_{c}^{+} #rightarrow #it{p K #pi},  %.2f < #eta < %.2f",
                       eta_lo, eta_hi),
                  Form("%s/p_dist_etabin_%02d_%.2f_%.2f.pdf", OUTDIR, j, eta_lo, eta_hi),
                  p_lo, p_hi);
    }
    printf("per-eta-bin figures written to %s/\n", OUTDIR);
}
