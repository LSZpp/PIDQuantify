// sWeighted calibration yields for the Lambda_c^+ -> p K pi proton sample:
// the "total" TH2D of the PIDCalib2 effhists, i.e. the sum of sWeights per
// (P, ETA) bin, for 2026_c1 MagDown and 2026_c2 MagUp.
//
// The "total" histogram is the cut-independent denominator of every efficiency,
// so any cut file carries the same one; DLLp-DLLK>5.0 is used simply because it
// is the working point of the performance figures.
//
// Drawn with "COL1 Z" and the bin contents overlaid as white text.
//
// Run headless with:
//   root -l -b -q sweighted_total_Lc_26.C

void draw_one(const char *path, const char *tag, const char *annotation){
    TFile *file = TFile::Open(path, "READ");
    if (!file || file->IsZombie()){
        printf("Failed to open %s\n", path);
        return;
    }
    TH2D *total = dynamic_cast<TH2D*>(file->Get("total"));
    if (!total){
        printf("No 'total' histogram in %s\n", path);
        return;
    }
    total->SetDirectory(nullptr);   // survive the file being closed
    file->Close();

    TString canvas_name = TString("canvas_sweighted_total_Lc_") + tag;
    TCanvas *canvas = new TCanvas(canvas_name, canvas_name, 820, 720);
    canvas->cd();
    gPad->SetTopMargin(.14);        // the map fills the frame, so the annotations
                                    // go in the margin above it rather than on top
                                    // of the bins
    gPad->SetRightMargin(.19);      // room for the palette

    total->SetTitle("");
    total->GetXaxis()->SetTitle("Momentum (MeV/#it{c})");
    total->GetYaxis()->SetTitle("Pseudorapidity");
    total->GetZaxis()->SetTitle("sWeighted candidates");
    total->GetXaxis()->SetTitleSize(.042);
    total->GetYaxis()->SetTitleSize(.042);
    total->GetZaxis()->SetTitleSize(.042);
    total->GetXaxis()->SetLabelSize(.042);
    total->GetYaxis()->SetLabelSize(.042);
    total->GetZaxis()->SetLabelSize(.042);
    total->GetZaxis()->SetTitleOffset(1.25);

    // The bin contents are painted with the histogram's marker attributes, so
    // the marker colour is what makes the text white and the marker size is
    // what keeps 20 x 33 numbers from overlapping.
    total->SetMarkerColor(kWhite);
    total->SetMarkerSize(.32);      // 20 x 33 bins: anything larger and the
                                    // low-momentum columns run into each other

    total->Draw("COL1 Z");
    total->Draw("TEXT SAME");

    TLatex lhcb;
    lhcb.SetNDC();
    lhcb.SetTextSize(.05);
    lhcb.DrawLatex(.12, .935, "LHCb #scale[0.8]{Work in Progress}");
    TLatex note;
    note.SetNDC();
    note.SetTextSize(.040);
    note.DrawLatex(.12, .885,
                   TString("#it{#Lambda}_{c}^{+} #rightarrow #it{p K #pi},  ")
                   + annotation);

    canvas->Update();

    TString stub = TString("sweighted_total_Lc_") + tag;
    canvas->SaveAs("macro_"      + stub + ".C"  );
    canvas->SaveAs("pdf_figure_" + stub + ".pdf");
    canvas->SaveAs(               stub + ".png");
}

void sweighted_total_Lc_26(){
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPalette(kRainbow);
    gStyle->SetNumberContours(256);
    gStyle->SetPaintTextFormat(".3g");   // keep the overlaid numbers short

    const TString dir = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d/Lc/";

    draw_one(dir + "effhists-2026_c1_v0-down-P_Lc-DLLp-DLLK>5.0-P.ETA.root",
             "26c1_MagDown", "2026 c1 MagDown");
    draw_one(dir + "effhists-2026_c2_v0-up-P_Lc-DLLp-DLLK>5.0-P.ETA.root",
             "26c2_MagUp",   "2026 c2 MagUp");
}
