#ifdef __CLING__
#pragma cling optimize(0)
#endif
void fit_parameters_24b4_sigma_l_scale()
{
//=========Macro generated from canvas: canvas_fit_parameters_24b4_sigma_l_scale/
//=========  (Mon Oct  5 14:16:53 2026) by ROOT version 6.36.04
   TCanvas *canvas_fit_parameters_24b4_sigma_l_scale = new TCanvas("canvas_fit_parameters_24b4_sigma_l_scale", "", 0, 0, 1500, 700);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(1);
   TColor::SetPalette(57, nullptr);
   canvas_fit_parameters_24b4_sigma_l_scale->Range(-3.968208,0.300955,30.71387,1.121828);
   canvas_fit_parameters_24b4_sigma_l_scale->SetFillColor(0);
   canvas_fit_parameters_24b4_sigma_l_scale->SetBorderMode(0);
   canvas_fit_parameters_24b4_sigma_l_scale->SetBorderSize(2);
   canvas_fit_parameters_24b4_sigma_l_scale->SetRightMargin(0.035);
   canvas_fit_parameters_24b4_sigma_l_scale->SetTopMargin(0.075);
   canvas_fit_parameters_24b4_sigma_l_scale->SetBottomMargin(0.19);
   canvas_fit_parameters_24b4_sigma_l_scale->SetFrameBorderMode(0);
   canvas_fit_parameters_24b4_sigma_l_scale->SetFrameBorderMode(0);
   
   TH1D *frame_fit_parameters_24b4_sigma_l_scale__3 = new TH1D("frame_fit_parameters_24b4_sigma_l_scale__3", "", 30, -0.5, 29.5);
   frame_fit_parameters_24b4_sigma_l_scale__3->SetMinimum(0.4569207449849249);
   frame_fit_parameters_24b4_sigma_l_scale__3->SetMaximum(1.060262092994263);
   frame_fit_parameters_24b4_sigma_l_scale__3->SetStats(0);
   frame_fit_parameters_24b4_sigma_l_scale__3->SetLineColor(TColor::GetColor("#000099"));
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetTitle("Fit bin");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(1, "vh0");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(2, "vh1");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(3, "vh2");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(4, "vh3");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(5, "h0");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(6, "h1");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(7, "h2");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(8, "h3");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(9, "h4");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(10, "h5");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(11, "h6");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(12, "h7");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(13, "h8");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(14, "h9");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(15, "m0");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(16, "m1");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(17, "m2");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(18, "m3");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(19, "m4");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(20, "m5");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(21, "m6");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(22, "m7");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(23, "m8");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(24, "m9");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(25, "l0");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(26, "l1");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(27, "l2");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(28, "l3");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(29, "l4");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetBinLabel(30, "l5");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetLabelSize(0.03200000151991844);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetTitleSize(0.04699999839067459);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetTitleOffset(1.549999952316284);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetXaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetYaxis()->SetTitle("Left width scale");
   frame_fit_parameters_24b4_sigma_l_scale__3->GetYaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetYaxis()->SetLabelSize(0.0430000014603138);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetYaxis()->SetTitleSize(0.05000000074505806);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetYaxis()->SetTitleOffset(0.8999999761581421);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetYaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetZaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetZaxis()->SetTitleOffset(1);
   frame_fit_parameters_24b4_sigma_l_scale__3->GetZaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_sigma_l_scale__3->Draw();
   TLine *line = new TLine(0.5, 0.456921, 0.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(1.5, 0.456921, 1.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(2.5, 0.456921, 2.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(3.5, 0.456921, 3.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(4.5, 0.456921, 4.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(5.5, 0.456921, 5.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(6.5, 0.456921, 6.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(7.5, 0.456921, 7.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(8.5, 0.456921, 8.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(9.5, 0.456921, 9.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(10.5, 0.456921, 10.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(11.5, 0.456921, 11.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(12.5, 0.456921, 12.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(13.5, 0.456921, 13.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(14.5, 0.456921, 14.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(15.5, 0.456921, 15.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(16.5, 0.456921, 16.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(17.5, 0.456921, 17.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(18.5, 0.456921, 18.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(19.5, 0.456921, 19.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(20.5, 0.456921, 20.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(21.5, 0.456921, 21.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(22.5, 0.456921, 22.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(23.5, 0.456921, 23.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(24.5, 0.456921, 24.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(25.5, 0.456921, 25.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(26.5, 0.456921, 26.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(27.5, 0.456921, 27.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(28.5, 0.456921, 28.5, 1.06026);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   
   std::vector<Double_t> gre_fx_vect24{
      -0.22, 0.78, 1.78, 2.78, 3.78, 4.78, 5.78, 6.78, 7.78, 8.779999999999999,
      9.779999999999999, 10.78, 11.78, 12.78, 13.78, 14.78, 15.78, 16.78, 17.78, 18.78,
      19.78, 20.78, 21.78, 22.78, 23.78, 24.78, 25.78, 26.78, 27.78, 28.78
   };
   std::vector<Double_t> gre_fy_vect25{
      0.9128970285820951, 0.617836488341587, 0.9377902181339762, 0.5982025771466215, 0.6812793694528955, 0.8001373858272249, 0.681698762516956, 0.7615207591135439, 0.9122016856519019, 0.6967039552363532,
      0.8036376120995052, 0.6651948789564602, 0.7316848424351369, 0.8169563233525232, 0.6985635057767767, 0.6879141282364741, 0.7293525561864546, 0.7462832572635836, 0.5509927249105078, 0.7029055553204083,
      0.6795431164213608, 0.7227269898274289, 0.7336117981466883, 0.5447276560302576, 0.6974943089281037, 0.7088569688086394, 0.7380079005101629, 0.7030736591794317, 0.6989144049348514, 0.7330008395617906
   };
   std::vector<Double_t> gre_fex_vect26{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect27{
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001
   };
   TGraphErrors *gre = new TGraphErrors(30, gre_fx_vect24.data(), gre_fy_vect25.data(), gre_fex_vect26.data(), gre_fey_vect27.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#999999"));
   gre->SetMarkerColor(TColor::GetColor("#999999"));
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram7 = new TH1F("Graph_histogram7", "Graph", 100, -3.120000000000001, 31.68);
   Graph_histogram7->SetMinimum(0.5042213998198858);
   Graph_histogram7->SetMaximum(0.9782964743443481);
   Graph_histogram7->SetDirectory(nullptr);
   Graph_histogram7->SetStats(0);
   Graph_histogram7->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram7->GetXaxis()->SetLabelFont(42);
   Graph_histogram7->GetXaxis()->SetTitleOffset(1);
   Graph_histogram7->GetXaxis()->SetTitleFont(42);
   Graph_histogram7->GetYaxis()->SetLabelFont(42);
   Graph_histogram7->GetYaxis()->SetTitleFont(42);
   Graph_histogram7->GetZaxis()->SetLabelFont(42);
   Graph_histogram7->GetZaxis()->SetTitleOffset(1);
   Graph_histogram7->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram7);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect28{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29
   };
   std::vector<Double_t> gre_fy_vect29{
      0.8892464250258789, 0.612355040597379, 0.9744172159304503, 0.6287140748633302, 0.6795132745727639, 0.8093443177167857, 0.6754765814322422, 0.7493651528712636, 0.8863544559057461, 0.7005444671969769,
      0.8134298328441685, 0.6833369681357562, 0.7449781708895681, 0.833621743003243, 0.6948647065444158, 0.6902547410657758, 0.730600937030095, 0.7252672638133676, 0.5657211219365582, 0.7063993034795761,
      0.6849125566605583, 0.7088697368065614, 0.7394484283226838, 0.5050567877981544, 0.7002453440590588, 0.6974073088796756, 0.7286908577751596, 0.7166609977576877, 0.6884967135325517, 0.7299725680896252
   };
   std::vector<Double_t> gre_fex_vect30{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect31{
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001
   };
   gre = new TGraphErrors(30, gre_fx_vect28.data(), gre_fy_vect29.data(), gre_fex_vect30.data(), gre_fey_vect31.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#990000"));
   gre->SetMarkerColor(TColor::GetColor("#990000"));
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram8 = new TH1F("Graph_histogram8", "Graph", 100, 0, 31.9);
   Graph_histogram8->SetMinimum(0.4569207449849249);
   Graph_histogram8->SetMaximum(1.02255325874368);
   Graph_histogram8->SetDirectory(nullptr);
   Graph_histogram8->SetStats(0);
   Graph_histogram8->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram8->GetXaxis()->SetLabelFont(42);
   Graph_histogram8->GetXaxis()->SetTitleOffset(1);
   Graph_histogram8->GetXaxis()->SetTitleFont(42);
   Graph_histogram8->GetYaxis()->SetLabelFont(42);
   Graph_histogram8->GetYaxis()->SetTitleFont(42);
   Graph_histogram8->GetZaxis()->SetLabelFont(42);
   Graph_histogram8->GetZaxis()->SetTitleOffset(1);
   Graph_histogram8->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram8);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect32{
      0.22, 1.22, 2.22, 3.22, 4.22, 5.22, 6.22, 7.22, 8.220000000000001, 9.220000000000001,
      10.22, 11.22, 12.22, 13.22, 14.22, 15.22, 16.22, 17.22, 18.22, 19.22,
      20.22, 21.22, 22.22, 23.22, 24.22, 25.22, 26.22, 27.22, 28.22, 29.22
   };
   std::vector<Double_t> gre_fy_vect33{
      0.903427463082739, 0.6125948808144805, 0.9484553339249193, 0.6070549400005798, 0.6807233732641013, 0.8029637892146435, 0.6789731823916136, 0.7556421744341355, 0.8839791009426069, 0.7011538239070551,
      0.806997030057493, 0.6715238928994478, 0.736716187150487, 0.8270281725241774, 0.6970128029277317, 0.6882282794973881, 0.7296948077444259, 0.7403935511707457, 0.5583084219585567, 0.7058955390088978,
      0.6826437853826227, 0.7195484865558303, 0.7356815936629209, 0.5465143904869862, 0.6981645028227553, 0.7037346562823746, 0.7356428877056255, 0.7083626396041675, 0.6950396551661965, 0.7312856741095739
   };
   std::vector<Double_t> gre_fex_vect34{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect35{
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001
   };
   gre = new TGraphErrors(30, gre_fx_vect32.data(), gre_fy_vect33.data(), gre_fex_vect34.data(), gre_fey_vect35.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#003366"));
   gre->SetMarkerColor(TColor::GetColor("#003366"));
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram9 = new TH1F("Graph_histogram9", "Graph", 100, 0, 32.12);
   Graph_histogram9->SetMinimum(0.505120296143193);
   Graph_histogram9->SetMaximum(0.9898494282687126);
   Graph_histogram9->SetDirectory(nullptr);
   Graph_histogram9->SetStats(0);
   Graph_histogram9->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram9->GetXaxis()->SetLabelFont(42);
   Graph_histogram9->GetXaxis()->SetTitleOffset(1);
   Graph_histogram9->GetXaxis()->SetTitleFont(42);
   Graph_histogram9->GetYaxis()->SetLabelFont(42);
   Graph_histogram9->GetYaxis()->SetTitleFont(42);
   Graph_histogram9->GetZaxis()->SetLabelFont(42);
   Graph_histogram9->GetZaxis()->SetTitleOffset(1);
   Graph_histogram9->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram9);
   
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
   canvas_fit_parameters_24b4_sigma_l_scale->Modified();
   canvas_fit_parameters_24b4_sigma_l_scale->SetSelected(canvas_fit_parameters_24b4_sigma_l_scale);
}
