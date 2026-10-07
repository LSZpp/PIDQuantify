#ifdef __CLING__
#pragma cling optimize(0)
#endif
void fit_parameters_24b4_gauss_frac()
{
//=========Macro generated from canvas: canvas_fit_parameters_24b4_gauss_frac/
//=========  (Mon Oct  5 14:16:54 2026) by ROOT version 6.36.04
   TCanvas *canvas_fit_parameters_24b4_gauss_frac = new TCanvas("canvas_fit_parameters_24b4_gauss_frac", "", 0, 0, 1500, 700);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(1);
   TColor::SetPalette(57, nullptr);
   canvas_fit_parameters_24b4_gauss_frac->Range(-3.968208,0.1144836,30.71387,0.7934722);
   canvas_fit_parameters_24b4_gauss_frac->SetFillColor(0);
   canvas_fit_parameters_24b4_gauss_frac->SetBorderMode(0);
   canvas_fit_parameters_24b4_gauss_frac->SetBorderSize(2);
   canvas_fit_parameters_24b4_gauss_frac->SetRightMargin(0.035);
   canvas_fit_parameters_24b4_gauss_frac->SetTopMargin(0.075);
   canvas_fit_parameters_24b4_gauss_frac->SetBottomMargin(0.19);
   canvas_fit_parameters_24b4_gauss_frac->SetFrameBorderMode(0);
   canvas_fit_parameters_24b4_gauss_frac->SetFrameBorderMode(0);
   
   TH1D *frame_fit_parameters_24b4_gauss_frac__9 = new TH1D("frame_fit_parameters_24b4_gauss_frac__9", "", 30, -0.5, 29.5);
   frame_fit_parameters_24b4_gauss_frac__9->SetMinimum(0.2434913909866996);
   frame_fit_parameters_24b4_gauss_frac__9->SetMaximum(0.7425480523732076);
   frame_fit_parameters_24b4_gauss_frac__9->SetStats(0);
   frame_fit_parameters_24b4_gauss_frac__9->SetLineColor(TColor::GetColor("#000099"));
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetTitle("Fit bin");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(1, "vh0");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(2, "vh1");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(3, "vh2");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(4, "vh3");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(5, "h0");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(6, "h1");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(7, "h2");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(8, "h3");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(9, "h4");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(10, "h5");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(11, "h6");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(12, "h7");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(13, "h8");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(14, "h9");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(15, "m0");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(16, "m1");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(17, "m2");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(18, "m3");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(19, "m4");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(20, "m5");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(21, "m6");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(22, "m7");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(23, "m8");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(24, "m9");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(25, "l0");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(26, "l1");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(27, "l2");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(28, "l3");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(29, "l4");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetBinLabel(30, "l5");
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetLabelSize(0.03200000151991844);
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetTitleSize(0.04699999839067459);
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetTitleOffset(1.549999952316284);
   frame_fit_parameters_24b4_gauss_frac__9->GetXaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_gauss_frac__9->GetYaxis()->SetTitle("Gaussian fraction");
   frame_fit_parameters_24b4_gauss_frac__9->GetYaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_gauss_frac__9->GetYaxis()->SetLabelSize(0.0430000014603138);
   frame_fit_parameters_24b4_gauss_frac__9->GetYaxis()->SetTitleSize(0.05000000074505806);
   frame_fit_parameters_24b4_gauss_frac__9->GetYaxis()->SetTitleOffset(0.8999999761581421);
   frame_fit_parameters_24b4_gauss_frac__9->GetYaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_gauss_frac__9->GetZaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_gauss_frac__9->GetZaxis()->SetTitleOffset(1);
   frame_fit_parameters_24b4_gauss_frac__9->GetZaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_gauss_frac__9->Draw();
   TLine *line = new TLine(0.5, 0.243491, 0.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(1.5, 0.243491, 1.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(2.5, 0.243491, 2.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(3.5, 0.243491, 3.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(4.5, 0.243491, 4.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(5.5, 0.243491, 5.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(6.5, 0.243491, 6.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(7.5, 0.243491, 7.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(8.5, 0.243491, 8.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(9.5, 0.243491, 9.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(10.5, 0.243491, 10.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(11.5, 0.243491, 11.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(12.5, 0.243491, 12.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(13.5, 0.243491, 13.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(14.5, 0.243491, 14.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(15.5, 0.243491, 15.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(16.5, 0.243491, 16.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(17.5, 0.243491, 17.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(18.5, 0.243491, 18.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(19.5, 0.243491, 19.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(20.5, 0.243491, 20.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(21.5, 0.243491, 21.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(22.5, 0.243491, 22.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(23.5, 0.243491, 23.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(24.5, 0.243491, 24.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(25.5, 0.243491, 25.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(26.5, 0.243491, 26.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(27.5, 0.243491, 27.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(28.5, 0.243491, 28.5, 0.742548);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   
   std::vector<Double_t> gre_fx_vect96{
      -0.22, 0.78, 1.78, 2.78, 3.78, 4.78, 5.78, 6.78, 7.78, 8.779999999999999,
      9.779999999999999, 10.78, 11.78, 12.78, 13.78, 14.78, 15.78, 16.78, 17.78, 18.78,
      19.78, 20.78, 21.78, 22.78, 23.78, 24.78, 25.78, 26.78, 27.78, 28.78
   };
   std::vector<Double_t> gre_fy_vect97{
      0.6713682093657299, 0.3683098085878758, 0.6644281358088429, 0.3507835155953369, 0.3522889679357249, 0.4671437166546778, 0.2987345090120216, 0.2834801926575205, 0.585471110949119, 0.3522889679357249,
      0.4671437166546778, 0.2987345090120216, 0.2834801926575205, 0.5614589654001692, 0.3713962533743405, 0.3769084979438388, 0.415695350674059, 0.437705392721669, 0.4916831475568847, 0.3713962533743405,
      0.3920691992476815, 0.4142377448071701, 0.4095534603728236, 0.5316495354244286, 0.34050126485655, 0.3145622601017606, 0.3116841672060827, 0.3406939472297829, 0.3145622601017606, 0.3116841672060827
   };
   std::vector<Double_t> gre_fex_vect98{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect99{
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001
   };
   TGraphErrors *gre = new TGraphErrors(30, gre_fx_vect96.data(), gre_fy_vect97.data(), gre_fex_vect98.data(), gre_fey_vect99.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#999999"));
   gre->SetMarkerColor(TColor::GetColor("#999999"));
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram25 = new TH1F("Graph_histogram25", "Graph", 100, -3.120000000000001, 31.68);
   Graph_histogram25->SetMinimum(0.2434913909866996);
   Graph_histogram25->SetMaximum(0.7113570110365509);
   Graph_histogram25->SetDirectory(nullptr);
   Graph_histogram25->SetStats(0);
   Graph_histogram25->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram25->GetXaxis()->SetLabelFont(42);
   Graph_histogram25->GetXaxis()->SetTitleOffset(1);
   Graph_histogram25->GetXaxis()->SetTitleFont(42);
   Graph_histogram25->GetYaxis()->SetLabelFont(42);
   Graph_histogram25->GetYaxis()->SetTitleFont(42);
   Graph_histogram25->GetZaxis()->SetLabelFont(42);
   Graph_histogram25->GetZaxis()->SetTitleOffset(1);
   Graph_histogram25->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram25);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect100{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29
   };
   std::vector<Double_t> gre_fy_vect101{
      0.6391509617580224, 0.3275593218543356, 0.6638411501671326, 0.374198203820428, 0.3522889679357249, 0.4671437166546778, 0.2987345090120216, 0.2834801926575205, 0.6387688441662787, 0.3522889679357249,
      0.4671437166546778, 0.2987345090120216, 0.2834801926575205, 0.5781656078497166, 0.3713962533743405, 0.3885491506288066, 0.425656862156136, 0.4620477189792777, 0.4539167758179096, 0.3713962533743405,
      0.3900445270741533, 0.3862931691554087, 0.3938073070717136, 0.3634462054602687, 0.3418719882419139, 0.3145622601017606, 0.3116841672060827, 0.3671192392663934, 0.3145622601017606, 0.3116841672060827
   };
   std::vector<Double_t> gre_fex_vect102{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect103{
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001
   };
   gre = new TGraphErrors(30, gre_fx_vect100.data(), gre_fy_vect101.data(), gre_fex_vect102.data(), gre_fey_vect103.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#990000"));
   gre->SetMarkerColor(TColor::GetColor("#990000"));
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram26 = new TH1F("Graph_histogram26", "Graph", 100, 0, 31.9);
   Graph_histogram26->SetMinimum(0.2442440969065593);
   Graph_histogram26->SetMaximum(0.7030772459180938);
   Graph_histogram26->SetDirectory(nullptr);
   Graph_histogram26->SetStats(0);
   Graph_histogram26->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram26->GetXaxis()->SetLabelFont(42);
   Graph_histogram26->GetXaxis()->SetTitleOffset(1);
   Graph_histogram26->GetXaxis()->SetTitleFont(42);
   Graph_histogram26->GetYaxis()->SetLabelFont(42);
   Graph_histogram26->GetYaxis()->SetTitleFont(42);
   Graph_histogram26->GetZaxis()->SetLabelFont(42);
   Graph_histogram26->GetZaxis()->SetTitleOffset(1);
   Graph_histogram26->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram26);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect104{
      0.22, 1.22, 2.22, 3.22, 4.22, 5.22, 6.22, 7.22, 8.220000000000001, 9.220000000000001,
      10.22, 11.22, 12.22, 13.22, 14.22, 15.22, 16.22, 17.22, 18.22, 19.22,
      20.22, 21.22, 22.22, 23.22, 24.22, 25.22, 26.22, 27.22, 28.22, 29.22
   };
   std::vector<Double_t> gre_fy_vect105{
      0.6595194879493428, 0.343313410961888, 0.6639093060768588, 0.3553795666460511, 0.3522889679357249, 0.4671437166546778, 0.2987345090120216, 0.2834801926575205, 0.5867869316869392, 0.3522889679357249,
      0.4671437166546778, 0.2987345090120216, 0.2834801926575205, 0.5548348811533249, 0.3713962533743405, 0.3843575293244057, 0.4220351192758688, 0.443435912578508, 0.4587478507340682, 0.3713962533743405,
      0.3921715945900941, 0.407985687988774, 0.404663293517276, 0.4639552260542438, 0.3409388004115056, 0.3145622601017606, 0.3116841672060827, 0.3509201071820698, 0.3145622601017606, 0.3116841672060827
   };
   std::vector<Double_t> gre_fex_vect106{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect107{
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001
   };
   gre = new TGraphErrors(30, gre_fx_vect104.data(), gre_fy_vect105.data(), gre_fex_vect106.data(), gre_fey_vect107.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#003366"));
   gre->SetMarkerColor(TColor::GetColor("#003366"));
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram27 = new TH1F("Graph_histogram27", "Graph", 100, 0, 32.12);
   Graph_histogram27->SetMinimum(0.2442372813155867);
   Graph_histogram27->SetMaximum(0.7031522174187926);
   Graph_histogram27->SetDirectory(nullptr);
   Graph_histogram27->SetStats(0);
   Graph_histogram27->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram27->GetXaxis()->SetLabelFont(42);
   Graph_histogram27->GetXaxis()->SetTitleOffset(1);
   Graph_histogram27->GetXaxis()->SetTitleFont(42);
   Graph_histogram27->GetYaxis()->SetLabelFont(42);
   Graph_histogram27->GetYaxis()->SetTitleFont(42);
   Graph_histogram27->GetZaxis()->SetLabelFont(42);
   Graph_histogram27->GetZaxis()->SetTitleOffset(1);
   Graph_histogram27->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram27);
   
   gre->Draw("pz ");
   
   TLegend *leg = new TLegend(0.7, 0.76, 0.96, 0.92, nullptr, "brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.034);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *legentry = leg->AddEntry("Graph","Block 4 partition 2","P");
   legentry->SetMarkerColor(TColor::GetColor("#999999"));
   legentry->SetMarkerStyle(20);
   legentry->SetMarkerSize(0.85);
   legentry->SetTextFont(42);
   legentry = leg->AddEntry("Graph","Block 4 partition 3","P");
   legentry->SetMarkerColor(TColor::GetColor("#990000"));
   legentry->SetMarkerSize(0.85);
   legentry->SetTextFont(42);
   legentry = leg->AddEntry("Graph","Block 4 combined","P");
   legentry->SetMarkerColor(TColor::GetColor("#003366"));
   legentry->SetMarkerStyle(24);
   legentry->SetMarkerSize(0.85);
   legentry->SetTextFont(42);
   leg->Draw();
   canvas_fit_parameters_24b4_gauss_frac->Modified();
   canvas_fit_parameters_24b4_gauss_frac->SetSelected(canvas_fit_parameters_24b4_gauss_frac);
}
