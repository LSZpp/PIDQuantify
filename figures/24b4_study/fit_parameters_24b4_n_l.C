#ifdef __CLING__
#pragma cling optimize(0)
#endif
void fit_parameters_24b4_n_l()
{
//=========Macro generated from canvas: canvas_fit_parameters_24b4_n_l/
//=========  (Mon Oct  5 14:16:54 2026) by ROOT version 6.36.04
   TCanvas *canvas_fit_parameters_24b4_n_l = new TCanvas("canvas_fit_parameters_24b4_n_l", "", 0, 0, 1500, 700);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(1);
   TColor::SetPalette(57, nullptr);
   canvas_fit_parameters_24b4_n_l->Range(-3.968208,-2.620974,30.71387,9.238931);
   canvas_fit_parameters_24b4_n_l->SetFillColor(0);
   canvas_fit_parameters_24b4_n_l->SetBorderMode(0);
   canvas_fit_parameters_24b4_n_l->SetBorderSize(2);
   canvas_fit_parameters_24b4_n_l->SetRightMargin(0.035);
   canvas_fit_parameters_24b4_n_l->SetTopMargin(0.075);
   canvas_fit_parameters_24b4_n_l->SetBottomMargin(0.19);
   canvas_fit_parameters_24b4_n_l->SetFrameBorderMode(0);
   canvas_fit_parameters_24b4_n_l->SetFrameBorderMode(0);
   
   TH1D *frame_fit_parameters_24b4_n_l__7 = new TH1D("frame_fit_parameters_24b4_n_l__7", "", 30, -0.5, 29.5);
   frame_fit_parameters_24b4_n_l__7->SetMinimum(-0.3675919237660874);
   frame_fit_parameters_24b4_n_l__7->SetMaximum(8.34943806771453);
   frame_fit_parameters_24b4_n_l__7->SetStats(0);
   frame_fit_parameters_24b4_n_l__7->SetLineColor(TColor::GetColor("#000099"));
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetTitle("Fit bin");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(1, "vh0");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(2, "vh1");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(3, "vh2");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(4, "vh3");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(5, "h0");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(6, "h1");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(7, "h2");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(8, "h3");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(9, "h4");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(10, "h5");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(11, "h6");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(12, "h7");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(13, "h8");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(14, "h9");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(15, "m0");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(16, "m1");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(17, "m2");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(18, "m3");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(19, "m4");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(20, "m5");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(21, "m6");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(22, "m7");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(23, "m8");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(24, "m9");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(25, "l0");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(26, "l1");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(27, "l2");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(28, "l3");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(29, "l4");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetBinLabel(30, "l5");
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetLabelSize(0.03200000151991844);
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetTitleSize(0.04699999839067459);
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetTitleOffset(1.549999952316284);
   frame_fit_parameters_24b4_n_l__7->GetXaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_n_l__7->GetYaxis()->SetTitle("Left tail #it{n}");
   frame_fit_parameters_24b4_n_l__7->GetYaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_n_l__7->GetYaxis()->SetLabelSize(0.0430000014603138);
   frame_fit_parameters_24b4_n_l__7->GetYaxis()->SetTitleSize(0.05000000074505806);
   frame_fit_parameters_24b4_n_l__7->GetYaxis()->SetTitleOffset(0.8999999761581421);
   frame_fit_parameters_24b4_n_l__7->GetYaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_n_l__7->GetZaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_n_l__7->GetZaxis()->SetTitleOffset(1);
   frame_fit_parameters_24b4_n_l__7->GetZaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_n_l__7->Draw();
   TLine *line = new TLine(0.5, -0.367592, 0.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(1.5, -0.367592, 1.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(2.5, -0.367592, 2.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(3.5, -0.367592, 3.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(4.5, -0.367592, 4.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(5.5, -0.367592, 5.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(6.5, -0.367592, 6.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(7.5, -0.367592, 7.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(8.5, -0.367592, 8.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(9.5, -0.367592, 9.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(10.5, -0.367592, 10.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(11.5, -0.367592, 11.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(12.5, -0.367592, 12.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(13.5, -0.367592, 13.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(14.5, -0.367592, 14.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(15.5, -0.367592, 15.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(16.5, -0.367592, 16.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(17.5, -0.367592, 17.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(18.5, -0.367592, 18.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(19.5, -0.367592, 19.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(20.5, -0.367592, 20.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(21.5, -0.367592, 21.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(22.5, -0.367592, 22.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(23.5, -0.367592, 23.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(24.5, -0.367592, 24.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(25.5, -0.367592, 25.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(26.5, -0.367592, 26.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(27.5, -0.367592, 27.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(28.5, -0.367592, 28.5, 8.34944);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   
   std::vector<Double_t> gre_fx_vect72{
      -0.22, 0.78, 1.78, 2.78, 3.78, 4.78, 5.78, 6.78, 7.78, 8.779999999999999,
      9.779999999999999, 10.78, 11.78, 12.78, 13.78, 14.78, 15.78, 16.78, 17.78, 18.78,
      19.78, 20.78, 21.78, 22.78, 23.78, 24.78, 25.78, 26.78, 27.78, 28.78
   };
   std::vector<Double_t> gre_fy_vect73{
      2.574614530921685, 0.6088344545637712, 2.574614530921685, 0.6088344545637712, 1.419111228205216, 2.92059475675328, 1.714492165643948, 3.822673571931203, 7.123405725162568, 1.419111228205216,
      2.92059475675328, 1.714492165643948, 3.822673571931203, 7.123405725162568, 2.256234270089747, 1.773999305874642, 2.498650281294003, 2.496490314382448, 0.3136260443183359, 2.256234270089747,
      1.773999305874642, 2.498650281294003, 2.496490314382448, 0.3136260443183359, 2.839200746186634, 3.023643645348547, 3.646955770276528, 2.839200746186634, 3.023643645348547, 3.646955770276528
   };
   std::vector<Double_t> gre_fex_vect74{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect75{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   TGraphErrors *gre = new TGraphErrors(30, gre_fx_vect72.data(), gre_fy_vect73.data(), gre_fex_vect74.data(), gre_fey_vect75.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#999999"));
   gre->SetMarkerColor(TColor::GetColor("#999999"));
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram19 = new TH1F("Graph_histogram19", "Graph", 100, -3.120000000000001, 31.68);
   Graph_histogram19->SetMinimum(0.2820834398865023);
   Graph_histogram19->SetMaximum(7.804623693246992);
   Graph_histogram19->SetDirectory(nullptr);
   Graph_histogram19->SetStats(0);
   Graph_histogram19->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram19->GetXaxis()->SetLabelFont(42);
   Graph_histogram19->GetXaxis()->SetTitleOffset(1);
   Graph_histogram19->GetXaxis()->SetTitleFont(42);
   Graph_histogram19->GetYaxis()->SetLabelFont(42);
   Graph_histogram19->GetYaxis()->SetTitleFont(42);
   Graph_histogram19->GetZaxis()->SetLabelFont(42);
   Graph_histogram19->GetZaxis()->SetTitleOffset(1);
   Graph_histogram19->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram19);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect76{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29
   };
   std::vector<Double_t> gre_fy_vect77{
      2.574614530921685, 0.6088344545637712, 2.574614530921685, 0.6088344545637712, 1.419111228205216, 2.92059475675328, 1.714492165643948, 3.822673571931203, 7.123405725162568, 1.419111228205216,
      2.92059475675328, 1.714492165643948, 3.822673571931203, 7.123405725162568, 2.256234270089747, 1.773999305874642, 2.498650281294003, 2.496490314382448, 0.3136260443183359, 2.256234270089747,
      1.773999305874642, 2.498650281294003, 2.496490314382448, 0.3136260443183359, 2.839200746186634, 3.023643645348547, 3.646955770276528, 2.839200746186634, 3.023643645348547, 3.646955770276528
   };
   std::vector<Double_t> gre_fex_vect78{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect79{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect76.data(), gre_fy_vect77.data(), gre_fex_vect78.data(), gre_fey_vect79.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#990000"));
   gre->SetMarkerColor(TColor::GetColor("#990000"));
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram20 = new TH1F("Graph_histogram20", "Graph", 100, 0, 31.9);
   Graph_histogram20->SetMinimum(0.2820834398865023);
   Graph_histogram20->SetMaximum(7.804623693246992);
   Graph_histogram20->SetDirectory(nullptr);
   Graph_histogram20->SetStats(0);
   Graph_histogram20->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram20->GetXaxis()->SetLabelFont(42);
   Graph_histogram20->GetXaxis()->SetTitleOffset(1);
   Graph_histogram20->GetXaxis()->SetTitleFont(42);
   Graph_histogram20->GetYaxis()->SetLabelFont(42);
   Graph_histogram20->GetYaxis()->SetTitleFont(42);
   Graph_histogram20->GetZaxis()->SetLabelFont(42);
   Graph_histogram20->GetZaxis()->SetTitleOffset(1);
   Graph_histogram20->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram20);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect80{
      0.22, 1.22, 2.22, 3.22, 4.22, 5.22, 6.22, 7.22, 8.220000000000001, 9.220000000000001,
      10.22, 11.22, 12.22, 13.22, 14.22, 15.22, 16.22, 17.22, 18.22, 19.22,
      20.22, 21.22, 22.22, 23.22, 24.22, 25.22, 26.22, 27.22, 28.22, 29.22
   };
   std::vector<Double_t> gre_fy_vect81{
      2.574614530921685, 0.6088344545637712, 2.574614530921685, 0.6088344545637712, 1.419111228205216, 2.92059475675328, 1.714492165643948, 3.822673571931203, 7.123405725162568, 1.419111228205216,
      2.92059475675328, 1.714492165643948, 3.822673571931203, 7.123405725162568, 2.256234270089747, 1.773999305874642, 2.498650281294003, 2.496490314382448, 0.3136260443183359, 2.256234270089747,
      1.773999305874642, 2.498650281294003, 2.496490314382448, 0.3136260443183359, 2.839200746186634, 3.023643645348547, 3.646955770276528, 2.839200746186634, 3.023643645348547, 3.646955770276528
   };
   std::vector<Double_t> gre_fex_vect82{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect83{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect80.data(), gre_fy_vect81.data(), gre_fex_vect82.data(), gre_fey_vect83.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#003366"));
   gre->SetMarkerColor(TColor::GetColor("#003366"));
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram21 = new TH1F("Graph_histogram21", "Graph", 100, 0, 32.12);
   Graph_histogram21->SetMinimum(0.2820834398865023);
   Graph_histogram21->SetMaximum(7.804623693246992);
   Graph_histogram21->SetDirectory(nullptr);
   Graph_histogram21->SetStats(0);
   Graph_histogram21->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram21->GetXaxis()->SetLabelFont(42);
   Graph_histogram21->GetXaxis()->SetTitleOffset(1);
   Graph_histogram21->GetXaxis()->SetTitleFont(42);
   Graph_histogram21->GetYaxis()->SetLabelFont(42);
   Graph_histogram21->GetYaxis()->SetTitleFont(42);
   Graph_histogram21->GetZaxis()->SetLabelFont(42);
   Graph_histogram21->GetZaxis()->SetTitleOffset(1);
   Graph_histogram21->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram21);
   
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
   canvas_fit_parameters_24b4_n_l->Modified();
   canvas_fit_parameters_24b4_n_l->SetSelected(canvas_fit_parameters_24b4_n_l);
}
