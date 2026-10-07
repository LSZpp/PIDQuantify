#ifdef __CLING__
#pragma cling optimize(0)
#endif
void fit_parameters_24b4_alpha_r()
{
//=========Macro generated from canvas: canvas_fit_parameters_24b4_alpha_r/
//=========  (Mon Oct  5 14:16:54 2026) by ROOT version 6.36.04
   TCanvas *canvas_fit_parameters_24b4_alpha_r = new TCanvas("canvas_fit_parameters_24b4_alpha_r", "", 0, 0, 1500, 700);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(1);
   TColor::SetPalette(57, nullptr);
   canvas_fit_parameters_24b4_alpha_r->Range(-3.968208,-0.07321602,30.71387,2.336388);
   canvas_fit_parameters_24b4_alpha_r->SetFillColor(0);
   canvas_fit_parameters_24b4_alpha_r->SetBorderMode(0);
   canvas_fit_parameters_24b4_alpha_r->SetBorderSize(2);
   canvas_fit_parameters_24b4_alpha_r->SetRightMargin(0.035);
   canvas_fit_parameters_24b4_alpha_r->SetTopMargin(0.075);
   canvas_fit_parameters_24b4_alpha_r->SetBottomMargin(0.19);
   canvas_fit_parameters_24b4_alpha_r->SetFrameBorderMode(0);
   canvas_fit_parameters_24b4_alpha_r->SetFrameBorderMode(0);
   
   TH1D *frame_fit_parameters_24b4_alpha_r__6 = new TH1D("frame_fit_parameters_24b4_alpha_r__6", "", 30, -0.5, 29.5);
   frame_fit_parameters_24b4_alpha_r__6->SetMinimum(0.3846087407077355);
   frame_fit_parameters_24b4_alpha_r__6->SetMaximum(2.155667756988812);
   frame_fit_parameters_24b4_alpha_r__6->SetStats(0);
   frame_fit_parameters_24b4_alpha_r__6->SetLineColor(TColor::GetColor("#000099"));
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetTitle("Fit bin");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(1, "vh0");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(2, "vh1");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(3, "vh2");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(4, "vh3");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(5, "h0");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(6, "h1");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(7, "h2");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(8, "h3");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(9, "h4");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(10, "h5");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(11, "h6");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(12, "h7");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(13, "h8");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(14, "h9");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(15, "m0");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(16, "m1");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(17, "m2");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(18, "m3");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(19, "m4");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(20, "m5");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(21, "m6");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(22, "m7");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(23, "m8");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(24, "m9");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(25, "l0");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(26, "l1");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(27, "l2");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(28, "l3");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(29, "l4");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetBinLabel(30, "l5");
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetLabelSize(0.03200000151991844);
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetTitleSize(0.04699999839067459);
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetTitleOffset(1.549999952316284);
   frame_fit_parameters_24b4_alpha_r__6->GetXaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_alpha_r__6->GetYaxis()->SetTitle("Right tail #alpha");
   frame_fit_parameters_24b4_alpha_r__6->GetYaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_alpha_r__6->GetYaxis()->SetLabelSize(0.0430000014603138);
   frame_fit_parameters_24b4_alpha_r__6->GetYaxis()->SetTitleSize(0.05000000074505806);
   frame_fit_parameters_24b4_alpha_r__6->GetYaxis()->SetTitleOffset(0.8999999761581421);
   frame_fit_parameters_24b4_alpha_r__6->GetYaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_alpha_r__6->GetZaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_alpha_r__6->GetZaxis()->SetTitleOffset(1);
   frame_fit_parameters_24b4_alpha_r__6->GetZaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_alpha_r__6->Draw();
   TLine *line = new TLine(0.5, 0.384609, 0.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(1.5, 0.384609, 1.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(2.5, 0.384609, 2.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(3.5, 0.384609, 3.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(4.5, 0.384609, 4.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(5.5, 0.384609, 5.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(6.5, 0.384609, 6.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(7.5, 0.384609, 7.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(8.5, 0.384609, 8.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(9.5, 0.384609, 9.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(10.5, 0.384609, 10.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(11.5, 0.384609, 11.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(12.5, 0.384609, 12.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(13.5, 0.384609, 13.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(14.5, 0.384609, 14.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(15.5, 0.384609, 15.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(16.5, 0.384609, 16.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(17.5, 0.384609, 17.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(18.5, 0.384609, 18.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(19.5, 0.384609, 19.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(20.5, 0.384609, 20.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(21.5, 0.384609, 21.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(22.5, 0.384609, 22.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(23.5, 0.384609, 23.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(24.5, 0.384609, 24.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(25.5, 0.384609, 25.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(26.5, 0.384609, 26.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(27.5, 0.384609, 27.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(28.5, 0.384609, 28.5, 2.15567);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   
   std::vector<Double_t> gre_fx_vect60{
      -0.22, 0.78, 1.78, 2.78, 3.78, 4.78, 5.78, 6.78, 7.78, 8.779999999999999,
      9.779999999999999, 10.78, 11.78, 12.78, 13.78, 14.78, 15.78, 16.78, 17.78, 18.78,
      19.78, 20.78, 21.78, 22.78, 23.78, 24.78, 25.78, 26.78, 27.78, 28.78
   };
   std::vector<Double_t> gre_fy_vect61{
      0.5231727263546947, 1.906412582824286, 0.5231727263546947, 1.906412582824286, 1.769383835395533, 1.319683438412462, 1.901842880056595, 1.653696000164343, 0.8185955421064595, 1.750300000072765,
      1.273284508573253, 1.873210005324263, 1.654910475895214, 0.6829626332472759, 1.739801531412307, 1.592439746269647, 1.481245390168762, 1.138136639478388, 1.417727867400841, 1.708374931468509,
      1.499616280065405, 1.412090496011273, 1.154392986860529, 1.417727867400841, 1.830284090969641, 1.595325810600565, 1.343408556457347, 1.805972235623442, 1.554352672552292, 1.324785061316113
   };
   std::vector<Double_t> gre_fex_vect62{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect63{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   TGraphErrors *gre = new TGraphErrors(30, gre_fx_vect60.data(), gre_fy_vect61.data(), gre_fex_vect62.data(), gre_fey_vect63.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#999999"));
   gre->SetMarkerColor(TColor::GetColor("#999999"));
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram16 = new TH1F("Graph_histogram16", "Graph", 100, -3.120000000000001, 31.68);
   Graph_histogram16->SetMinimum(0.3846087407077355);
   Graph_histogram16->SetMaximum(2.044976568471245);
   Graph_histogram16->SetDirectory(nullptr);
   Graph_histogram16->SetStats(0);
   Graph_histogram16->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram16->GetXaxis()->SetLabelFont(42);
   Graph_histogram16->GetXaxis()->SetTitleOffset(1);
   Graph_histogram16->GetXaxis()->SetTitleFont(42);
   Graph_histogram16->GetYaxis()->SetLabelFont(42);
   Graph_histogram16->GetYaxis()->SetTitleFont(42);
   Graph_histogram16->GetZaxis()->SetLabelFont(42);
   Graph_histogram16->GetZaxis()->SetTitleOffset(1);
   Graph_histogram16->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram16);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect64{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29
   };
   std::vector<Double_t> gre_fy_vect65{
      0.5231727263546947, 1.906412582824286, 0.5231727263546947, 1.906412582824286, 1.725368044269037, 1.246063086763347, 1.864179007136358, 1.649993166750026, 0.769670681824005, 1.813203383550296,
      1.323246112722235, 1.851246800159058, 1.612188764723184, 0.7694239391298355, 1.674451563136304, 1.513203035699518, 1.427740696412815, 1.122147556404455, 1.417727867400841, 1.693332867974811,
      1.452310148218775, 1.409369390136447, 1.085007486672132, 1.417727867400841, 1.780381584300335, 1.556070842128421, 1.314434430911482, 1.69992948911915, 1.49431826872262, 1.235104943717205
   };
   std::vector<Double_t> gre_fex_vect66{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect67{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect64.data(), gre_fy_vect65.data(), gre_fex_vect66.data(), gre_fey_vect67.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#990000"));
   gre->SetMarkerColor(TColor::GetColor("#990000"));
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram17 = new TH1F("Graph_histogram17", "Graph", 100, 0, 31.9);
   Graph_histogram17->SetMinimum(0.3846087407077355);
   Graph_histogram17->SetMaximum(2.044976568471245);
   Graph_histogram17->SetDirectory(nullptr);
   Graph_histogram17->SetStats(0);
   Graph_histogram17->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram17->GetXaxis()->SetLabelFont(42);
   Graph_histogram17->GetXaxis()->SetTitleOffset(1);
   Graph_histogram17->GetXaxis()->SetTitleFont(42);
   Graph_histogram17->GetYaxis()->SetLabelFont(42);
   Graph_histogram17->GetYaxis()->SetTitleFont(42);
   Graph_histogram17->GetZaxis()->SetLabelFont(42);
   Graph_histogram17->GetZaxis()->SetTitleOffset(1);
   Graph_histogram17->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram17);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect68{
      0.22, 1.22, 2.22, 3.22, 4.22, 5.22, 6.22, 7.22, 8.220000000000001, 9.220000000000001,
      10.22, 11.22, 12.22, 13.22, 14.22, 15.22, 16.22, 17.22, 18.22, 19.22,
      20.22, 21.22, 22.22, 23.22, 24.22, 25.22, 26.22, 27.22, 28.22, 29.22
   };
   std::vector<Double_t> gre_fy_vect69{
      0.5231727263546947, 1.906412582824286, 0.5231727263546947, 1.906412582824286, 1.754309845756011, 1.294097774528682, 1.886953705466027, 1.649769980694965, 0.8538967176630057, 1.769436830061767,
      1.293409328930797, 1.866723129946547, 1.640543507213282, 0.7540483331932245, 1.716752354477203, 1.559927019143779, 1.457483671138867, 1.131856917060625, 1.417727867400841, 1.704724717961468,
      1.481733323452569, 1.404191977802401, 1.129734493159126, 1.417727867400841, 1.811430796201472, 1.581383782800783, 1.330559122242913, 1.764500986289048, 1.530837671463153, 1.291043794177494
   };
   std::vector<Double_t> gre_fex_vect70{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect71{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect68.data(), gre_fy_vect69.data(), gre_fex_vect70.data(), gre_fey_vect71.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#003366"));
   gre->SetMarkerColor(TColor::GetColor("#003366"));
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram18 = new TH1F("Graph_histogram18", "Graph", 100, 0, 32.12);
   Graph_histogram18->SetMinimum(0.3846087407077355);
   Graph_histogram18->SetMaximum(2.044976568471245);
   Graph_histogram18->SetDirectory(nullptr);
   Graph_histogram18->SetStats(0);
   Graph_histogram18->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram18->GetXaxis()->SetLabelFont(42);
   Graph_histogram18->GetXaxis()->SetTitleOffset(1);
   Graph_histogram18->GetXaxis()->SetTitleFont(42);
   Graph_histogram18->GetYaxis()->SetLabelFont(42);
   Graph_histogram18->GetYaxis()->SetTitleFont(42);
   Graph_histogram18->GetZaxis()->SetLabelFont(42);
   Graph_histogram18->GetZaxis()->SetTitleOffset(1);
   Graph_histogram18->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram18);
   
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
   canvas_fit_parameters_24b4_alpha_r->Modified();
   canvas_fit_parameters_24b4_alpha_r->SetSelected(canvas_fit_parameters_24b4_alpha_r);
}
