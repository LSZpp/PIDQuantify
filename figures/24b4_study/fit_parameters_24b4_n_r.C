#ifdef __CLING__
#pragma cling optimize(0)
#endif
void fit_parameters_24b4_n_r()
{
//=========Macro generated from canvas: canvas_fit_parameters_24b4_n_r/
//=========  (Mon Oct  5 14:16:54 2026) by ROOT version 6.36.04
   TCanvas *canvas_fit_parameters_24b4_n_r = new TCanvas("canvas_fit_parameters_24b4_n_r", "", 0, 0, 1500, 700);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(1);
   TColor::SetPalette(57, nullptr);
   canvas_fit_parameters_24b4_n_r->Range(-3.968208,-1.996382,30.71387,13.80028);
   canvas_fit_parameters_24b4_n_r->SetFillColor(0);
   canvas_fit_parameters_24b4_n_r->SetBorderMode(0);
   canvas_fit_parameters_24b4_n_r->SetBorderSize(2);
   canvas_fit_parameters_24b4_n_r->SetRightMargin(0.035);
   canvas_fit_parameters_24b4_n_r->SetTopMargin(0.075);
   canvas_fit_parameters_24b4_n_r->SetBottomMargin(0.19);
   canvas_fit_parameters_24b4_n_r->SetFrameBorderMode(0);
   canvas_fit_parameters_24b4_n_r->SetFrameBorderMode(0);
   
   TH1D *frame_fit_parameters_24b4_n_r__8 = new TH1D("frame_fit_parameters_24b4_n_r__8", "", 30, -0.5, 29.5);
   frame_fit_parameters_24b4_n_r__8->SetMinimum(1.004983562330706);
   frame_fit_parameters_24b4_n_r__8->SetMaximum(12.61552948537368);
   frame_fit_parameters_24b4_n_r__8->SetStats(0);
   frame_fit_parameters_24b4_n_r__8->SetLineColor(TColor::GetColor("#000099"));
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetTitle("Fit bin");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(1, "vh0");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(2, "vh1");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(3, "vh2");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(4, "vh3");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(5, "h0");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(6, "h1");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(7, "h2");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(8, "h3");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(9, "h4");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(10, "h5");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(11, "h6");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(12, "h7");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(13, "h8");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(14, "h9");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(15, "m0");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(16, "m1");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(17, "m2");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(18, "m3");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(19, "m4");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(20, "m5");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(21, "m6");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(22, "m7");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(23, "m8");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(24, "m9");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(25, "l0");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(26, "l1");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(27, "l2");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(28, "l3");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(29, "l4");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetBinLabel(30, "l5");
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetLabelSize(0.03200000151991844);
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetTitleSize(0.04699999839067459);
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetTitleOffset(1.549999952316284);
   frame_fit_parameters_24b4_n_r__8->GetXaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_n_r__8->GetYaxis()->SetTitle("Right tail #it{n}");
   frame_fit_parameters_24b4_n_r__8->GetYaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_n_r__8->GetYaxis()->SetLabelSize(0.0430000014603138);
   frame_fit_parameters_24b4_n_r__8->GetYaxis()->SetTitleSize(0.05000000074505806);
   frame_fit_parameters_24b4_n_r__8->GetYaxis()->SetTitleOffset(0.8999999761581421);
   frame_fit_parameters_24b4_n_r__8->GetYaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_n_r__8->GetZaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_n_r__8->GetZaxis()->SetTitleOffset(1);
   frame_fit_parameters_24b4_n_r__8->GetZaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_n_r__8->Draw();
   TLine *line = new TLine(0.5, 1.00498, 0.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(1.5, 1.00498, 1.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(2.5, 1.00498, 2.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(3.5, 1.00498, 3.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(4.5, 1.00498, 4.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(5.5, 1.00498, 5.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(6.5, 1.00498, 6.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(7.5, 1.00498, 7.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(8.5, 1.00498, 8.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(9.5, 1.00498, 9.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(10.5, 1.00498, 10.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(11.5, 1.00498, 11.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(12.5, 1.00498, 12.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(13.5, 1.00498, 13.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(14.5, 1.00498, 14.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(15.5, 1.00498, 15.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(16.5, 1.00498, 16.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(17.5, 1.00498, 17.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(18.5, 1.00498, 18.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(19.5, 1.00498, 19.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(20.5, 1.00498, 20.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(21.5, 1.00498, 21.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(22.5, 1.00498, 22.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(23.5, 1.00498, 23.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(24.5, 1.00498, 24.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(25.5, 1.00498, 25.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(26.5, 1.00498, 26.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(27.5, 1.00498, 27.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(28.5, 1.00498, 28.5, 12.6155);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   
   std::vector<Double_t> gre_fx_vect84{
      -0.22, 0.78, 1.78, 2.78, 3.78, 4.78, 5.78, 6.78, 7.78, 8.779999999999999,
      9.779999999999999, 10.78, 11.78, 12.78, 13.78, 14.78, 15.78, 16.78, 17.78, 18.78,
      19.78, 20.78, 21.78, 22.78, 23.78, 24.78, 25.78, 26.78, 27.78, 28.78
   };
   std::vector<Double_t> gre_fy_vect85{
      10.98259646494577, 3.130487460686332, 10.98259646494577, 3.130487460686332, 3.559970276334715, 5.198534456870306, 2.333961955698134, 3.227502154932302, 6.898952214495393, 3.559970276334715,
      5.198534456870306, 2.333961955698134, 3.227502154932302, 6.898952214495393, 3.146026745033174, 3.233841908282534, 3.085812427382334, 5.338288999981544, 1.912257462568439, 3.146026745033174,
      3.233841908282534, 3.085812427382334, 5.338288999981544, 1.912257462568439, 2.42235026954516, 3.186462936080003, 3.654318712449072, 2.42235026954516, 3.186462936080003, 3.654318712449072
   };
   std::vector<Double_t> gre_fex_vect86{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect87{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   TGraphErrors *gre = new TGraphErrors(30, gre_fx_vect84.data(), gre_fy_vect85.data(), gre_fex_vect86.data(), gre_fey_vect87.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#999999"));
   gre->SetMarkerColor(TColor::GetColor("#999999"));
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram22 = new TH1F("Graph_histogram22", "Graph", 100, -3.120000000000001, 31.68);
   Graph_histogram22->SetMinimum(1.004983562330706);
   Graph_histogram22->SetMaximum(11.8898703651835);
   Graph_histogram22->SetDirectory(nullptr);
   Graph_histogram22->SetStats(0);
   Graph_histogram22->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram22->GetXaxis()->SetLabelFont(42);
   Graph_histogram22->GetXaxis()->SetTitleOffset(1);
   Graph_histogram22->GetXaxis()->SetTitleFont(42);
   Graph_histogram22->GetYaxis()->SetLabelFont(42);
   Graph_histogram22->GetYaxis()->SetTitleFont(42);
   Graph_histogram22->GetZaxis()->SetLabelFont(42);
   Graph_histogram22->GetZaxis()->SetTitleOffset(1);
   Graph_histogram22->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram22);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect88{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29
   };
   std::vector<Double_t> gre_fy_vect89{
      10.98259646494577, 3.130487460686332, 10.98259646494577, 3.130487460686332, 3.559970276334715, 5.198534456870306, 2.333961955698134, 3.227502154932302, 6.898952214495393, 3.559970276334715,
      5.198534456870306, 2.333961955698134, 3.227502154932302, 6.898952214495393, 3.146026745033174, 3.233841908282534, 3.085812427382334, 5.338288999981544, 1.912257462568439, 3.146026745033174,
      3.233841908282534, 3.085812427382334, 5.338288999981544, 1.912257462568439, 2.42235026954516, 3.186462936080003, 3.654318712449072, 2.42235026954516, 3.186462936080003, 3.654318712449072
   };
   std::vector<Double_t> gre_fex_vect90{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect91{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect88.data(), gre_fy_vect89.data(), gre_fex_vect90.data(), gre_fey_vect91.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#990000"));
   gre->SetMarkerColor(TColor::GetColor("#990000"));
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram23 = new TH1F("Graph_histogram23", "Graph", 100, 0, 31.9);
   Graph_histogram23->SetMinimum(1.004983562330706);
   Graph_histogram23->SetMaximum(11.8898703651835);
   Graph_histogram23->SetDirectory(nullptr);
   Graph_histogram23->SetStats(0);
   Graph_histogram23->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram23->GetXaxis()->SetLabelFont(42);
   Graph_histogram23->GetXaxis()->SetTitleOffset(1);
   Graph_histogram23->GetXaxis()->SetTitleFont(42);
   Graph_histogram23->GetYaxis()->SetLabelFont(42);
   Graph_histogram23->GetYaxis()->SetTitleFont(42);
   Graph_histogram23->GetZaxis()->SetLabelFont(42);
   Graph_histogram23->GetZaxis()->SetTitleOffset(1);
   Graph_histogram23->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram23);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect92{
      0.22, 1.22, 2.22, 3.22, 4.22, 5.22, 6.22, 7.22, 8.220000000000001, 9.220000000000001,
      10.22, 11.22, 12.22, 13.22, 14.22, 15.22, 16.22, 17.22, 18.22, 19.22,
      20.22, 21.22, 22.22, 23.22, 24.22, 25.22, 26.22, 27.22, 28.22, 29.22
   };
   std::vector<Double_t> gre_fy_vect93{
      10.98259646494577, 3.130487460686332, 10.98259646494577, 3.130487460686332, 3.559970276334715, 5.198534456870306, 2.333961955698134, 3.227502154932302, 6.898952214495393, 3.559970276334715,
      5.198534456870306, 2.333961955698134, 3.227502154932302, 6.898952214495393, 3.146026745033174, 3.233841908282534, 3.085812427382334, 5.338288999981544, 1.912257462568439, 3.146026745033174,
      3.233841908282534, 3.085812427382334, 5.338288999981544, 1.912257462568439, 2.42235026954516, 3.186462936080003, 3.654318712449072, 2.42235026954516, 3.186462936080003, 3.654318712449072
   };
   std::vector<Double_t> gre_fex_vect94{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect95{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect92.data(), gre_fy_vect93.data(), gre_fex_vect94.data(), gre_fey_vect95.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#003366"));
   gre->SetMarkerColor(TColor::GetColor("#003366"));
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram24 = new TH1F("Graph_histogram24", "Graph", 100, 0, 32.12);
   Graph_histogram24->SetMinimum(1.004983562330706);
   Graph_histogram24->SetMaximum(11.8898703651835);
   Graph_histogram24->SetDirectory(nullptr);
   Graph_histogram24->SetStats(0);
   Graph_histogram24->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram24->GetXaxis()->SetLabelFont(42);
   Graph_histogram24->GetXaxis()->SetTitleOffset(1);
   Graph_histogram24->GetXaxis()->SetTitleFont(42);
   Graph_histogram24->GetYaxis()->SetLabelFont(42);
   Graph_histogram24->GetYaxis()->SetTitleFont(42);
   Graph_histogram24->GetZaxis()->SetLabelFont(42);
   Graph_histogram24->GetZaxis()->SetTitleOffset(1);
   Graph_histogram24->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram24);
   
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
   canvas_fit_parameters_24b4_n_r->Modified();
   canvas_fit_parameters_24b4_n_r->SetSelected(canvas_fit_parameters_24b4_n_r);
}
