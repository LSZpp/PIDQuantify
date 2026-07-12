// Fraction of new-L0 events in the L0 turn-on momentum bin [9300,17700] for the
// three combined data-period groups, from the sWeighted "total" histograms:
//   frac = Integral(P bin 1) / Integral(all).
// One point per group (colours match the ROC; distinct markers). Run with
//   root -l -b -q threshold_fraction.C

void threshold_fraction(){
    gStyle->SetOptStat(0);
    const char *DIR = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/newL0";
    const char *CUT = "DLLp-DLLK>5.0";   // any cut: "total" is cut-independent

    std::vector<std::string> names = {"24b7/8", "25c1", "25c2/3/4"};
    std::vector<std::vector<std::string>> groups = {
        {"L0_2024_block7-down", "L0_2024_block8-up"},
        {"L0_2025_c1-down", "L0_2025_c1-up"},
        {"L0_2025_c2-down", "L0_2025_c3-up", "L0_2025_c4-up", "L0_2025_c4-down"}};
    Color_t col[] = {kP8Blue, kP8Blue + 1, kP8Blue + 2};
    Style_t mrk[] = {21, 21, 25};

    double frac[3];
    for (int g = 0; g < 3; g++){
        TH2D *tot = nullptr;
        for (auto &d : groups[g]){
            TFile *f = TFile::Open(Form("%s/effhists-%s-P-%s-P.ETA.root", DIR, d.c_str(), CUT));
            TH2D *h = (TH2D*)f->Get("total");
            if (!tot){ tot = (TH2D*)h->Clone(Form("tot%d", g)); tot->SetDirectory(0); }
            else tot->Add(h);
            f->Close();
        }
        double thr = tot->Integral(1, 1, 1, tot->GetNbinsY());   // P bin 1 = [9300,17700]
        frac[g] = thr / tot->Integral();
        printf("%-9s threshold=%.1f  total=%.1f  frac=%.4f\n", names[g].c_str(), thr, tot->Integral(), frac[g]);
    }

    double ymax = std::max({frac[0], frac[1], frac[2]});
    TH1F *fr = new TH1F("fr", "", 3, 0.5, 3.5);
    for (int i = 0; i < 3; i++) fr->GetXaxis()->SetBinLabel(i + 1, names[i].c_str());
    fr->SetMinimum(0); fr->SetMaximum(ymax * 1.3);
    fr->GetXaxis()->SetLabelSize(0.06);
    fr->GetYaxis()->SetTitle("s#it{W}eighted fraction with 9.3 GeV/#it{c} < #it{p} < 17.7 GeV/#it{c}");
    fr->GetYaxis()->SetTitleOffset(1.3);

    TCanvas *c = new TCanvas("c", "c", 800, 600);
    c->SetLeftMargin(0.14);
    fr->Draw();
    for (int g = 0; g < 3; g++){
        TGraph *gr = new TGraph(1);
        gr->SetPoint(0, g + 1, frac[g]);
        gr->SetMarkerColor(col[g]); gr->SetMarkerStyle(mrk[g]); gr->SetMarkerSize(2.2);
        gr->Draw("P SAME");
    }
    c->SaveAs("/home/lins/u3_PIDQuantify/figures/final_calibration/threshold/threshold_fraction.pdf");
}
