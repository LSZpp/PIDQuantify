#ifdef __CLING__
#pragma cling optimize(0)
#endif
void fit_parameters_24b4_gauss_sigma()
{
//=========Macro generated from canvas: canvas_fit_parameters_24b4_gauss_sigma/
//=========  (Mon Oct  5 14:16:53 2026) by ROOT version 6.36.04
   TCanvas *canvas_fit_parameters_24b4_gauss_sigma = new TCanvas("canvas_fit_parameters_24b4_gauss_sigma", "", 0, 0, 1500, 700);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(1);
   TColor::SetPalette(57, nullptr);
   canvas_fit_parameters_24b4_gauss_sigma->Range(-3.968208,0.07121872,30.71387,4.158498);
   canvas_fit_parameters_24b4_gauss_sigma->SetFillColor(0);
   canvas_fit_parameters_24b4_gauss_sigma->SetBorderMode(0);
   canvas_fit_parameters_24b4_gauss_sigma->SetBorderSize(2);
   canvas_fit_parameters_24b4_gauss_sigma->SetRightMargin(0.035);
   canvas_fit_parameters_24b4_gauss_sigma->SetTopMargin(0.075);
   canvas_fit_parameters_24b4_gauss_sigma->SetBottomMargin(0.19);
   canvas_fit_parameters_24b4_gauss_sigma->SetFrameBorderMode(0);
   canvas_fit_parameters_24b4_gauss_sigma->SetFrameBorderMode(0);
   
   TH1D *frame_fit_parameters_24b4_gauss_sigma__2 = new TH1D("frame_fit_parameters_24b4_gauss_sigma__2", "", 30, -0.5, 29.5);
   frame_fit_parameters_24b4_gauss_sigma__2->SetMinimum(0.8478018326321948);
   frame_fit_parameters_24b4_gauss_sigma__2->SetMaximum(3.851952393949609);
   frame_fit_parameters_24b4_gauss_sigma__2->SetStats(0);
   frame_fit_parameters_24b4_gauss_sigma__2->SetLineColor(TColor::GetColor("#000099"));
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetTitle("Fit bin");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(1, "vh0");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(2, "vh1");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(3, "vh2");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(4, "vh3");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(5, "h0");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(6, "h1");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(7, "h2");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(8, "h3");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(9, "h4");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(10, "h5");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(11, "h6");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(12, "h7");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(13, "h8");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(14, "h9");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(15, "m0");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(16, "m1");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(17, "m2");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(18, "m3");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(19, "m4");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(20, "m5");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(21, "m6");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(22, "m7");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(23, "m8");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(24, "m9");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(25, "l0");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(26, "l1");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(27, "l2");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(28, "l3");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(29, "l4");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetBinLabel(30, "l5");
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetLabelSize(0.03200000151991844);
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetTitleSize(0.04699999839067459);
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetTitleOffset(1.549999952316284);
   frame_fit_parameters_24b4_gauss_sigma__2->GetXaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_gauss_sigma__2->GetYaxis()->SetTitle("Gaussian width [MeV/#it{c}^{2}]");
   frame_fit_parameters_24b4_gauss_sigma__2->GetYaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_gauss_sigma__2->GetYaxis()->SetLabelSize(0.0430000014603138);
   frame_fit_parameters_24b4_gauss_sigma__2->GetYaxis()->SetTitleSize(0.05000000074505806);
   frame_fit_parameters_24b4_gauss_sigma__2->GetYaxis()->SetTitleOffset(0.8999999761581421);
   frame_fit_parameters_24b4_gauss_sigma__2->GetYaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_gauss_sigma__2->GetZaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_gauss_sigma__2->GetZaxis()->SetTitleOffset(1);
   frame_fit_parameters_24b4_gauss_sigma__2->GetZaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_gauss_sigma__2->Draw();
   TLine *line = new TLine(0.5, 0.847802, 0.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(1.5, 0.847802, 1.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(2.5, 0.847802, 2.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(3.5, 0.847802, 3.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(4.5, 0.847802, 4.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(5.5, 0.847802, 5.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(6.5, 0.847802, 6.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(7.5, 0.847802, 7.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(8.5, 0.847802, 8.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(9.5, 0.847802, 9.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(10.5, 0.847802, 10.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(11.5, 0.847802, 11.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(12.5, 0.847802, 12.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(13.5, 0.847802, 13.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(14.5, 0.847802, 14.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(15.5, 0.847802, 15.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(16.5, 0.847802, 16.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(17.5, 0.847802, 17.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(18.5, 0.847802, 18.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(19.5, 0.847802, 19.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(20.5, 0.847802, 20.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(21.5, 0.847802, 21.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(22.5, 0.847802, 22.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(23.5, 0.847802, 23.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(24.5, 0.847802, 24.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(25.5, 0.847802, 25.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(26.5, 0.847802, 26.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(27.5, 0.847802, 27.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(28.5, 0.847802, 28.5, 3.85195);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   
   std::vector<Double_t> gre_fx_vect12{
      -0.22, 0.78, 1.78, 2.78, 3.78, 4.78, 5.78, 6.78, 7.78, 8.779999999999999,
      9.779999999999999, 10.78, 11.78, 12.78, 13.78, 14.78, 15.78, 16.78, 17.78, 18.78,
      19.78, 20.78, 21.78, 22.78, 23.78, 24.78, 25.78, 26.78, 27.78, 28.78
   };
   std::vector<Double_t> gre_fy_vect13{
      1.581092382838228, 2.441312656666799, 1.585308339305564, 2.424087506004849, 1.472929153035191, 1.390240376224845, 1.778635733905406, 1.781274343959386, 2.044550672107272, 1.446773835924345,
      1.383677938712735, 1.75761139811769, 1.760701503670878, 2.167978335809981, 1.244487425444434, 1.470443228174749, 1.492397362846166, 1.617746857344739, 2.815489436736821, 1.217952577399741,
      1.432323860166981, 1.470888899786301, 1.616240828740991, 2.727416064945042, 1.12636896129435, 1.304874689437947, 1.510095892482975, 1.112201916763317, 1.288555632379993, 1.499959869334741
   };
   std::vector<Double_t> gre_fex_vect14{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect15{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   TGraphErrors *gre = new TGraphErrors(30, gre_fx_vect12.data(), gre_fy_vect13.data(), gre_fex_vect14.data(), gre_fey_vect15.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#999999"));
   gre->SetMarkerColor(TColor::GetColor("#999999"));
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram4 = new TH1F("Graph_histogram4", "Graph", 100, -3.120000000000001, 31.68);
   Graph_histogram4->SetMinimum(0.9416331647659671);
   Graph_histogram4->SetMaximum(2.986058188734171);
   Graph_histogram4->SetDirectory(nullptr);
   Graph_histogram4->SetStats(0);
   Graph_histogram4->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram4->GetXaxis()->SetLabelFont(42);
   Graph_histogram4->GetXaxis()->SetTitleOffset(1);
   Graph_histogram4->GetXaxis()->SetTitleFont(42);
   Graph_histogram4->GetYaxis()->SetLabelFont(42);
   Graph_histogram4->GetYaxis()->SetTitleFont(42);
   Graph_histogram4->GetZaxis()->SetLabelFont(42);
   Graph_histogram4->GetZaxis()->SetTitleOffset(1);
   Graph_histogram4->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram4);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect16{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29
   };
   std::vector<Double_t> gre_fy_vect17{
      1.589385191918274, 2.563311497732686, 1.608970799587938, 2.440563997252503, 1.469451084168402, 1.390936907390901, 1.788207553166738, 1.818480339996347, 2.274341081512829, 1.482970835873151,
      1.376336008887957, 1.754904843062263, 1.767056104058866, 2.176396051638769, 1.232258736096023, 1.459234043605968, 1.48829687994382, 1.672099128244257, 3.14131024509209, 1.217688649077824,
      1.419424991471704, 1.477295552995524, 1.586183814979679, 3.429293721264348, 1.128836388422372, 1.318411123649816, 1.553555581893699, 1.082701095235118, 1.279124318061033, 1.430515325955383
   };
   std::vector<Double_t> gre_fex_vect18{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect19{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect16.data(), gre_fy_vect17.data(), gre_fex_vect18.data(), gre_fey_vect19.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#990000"));
   gre->SetMarkerColor(TColor::GetColor("#990000"));
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram5 = new TH1F("Graph_histogram5", "Graph", 100, 0, 31.9);
   Graph_histogram5->SetMinimum(0.8478018326321948);
   Graph_histogram5->SetMaximum(3.664192983867271);
   Graph_histogram5->SetDirectory(nullptr);
   Graph_histogram5->SetStats(0);
   Graph_histogram5->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram5->GetXaxis()->SetLabelFont(42);
   Graph_histogram5->GetXaxis()->SetTitleOffset(1);
   Graph_histogram5->GetXaxis()->SetTitleFont(42);
   Graph_histogram5->GetYaxis()->SetLabelFont(42);
   Graph_histogram5->GetYaxis()->SetTitleFont(42);
   Graph_histogram5->GetZaxis()->SetLabelFont(42);
   Graph_histogram5->GetZaxis()->SetTitleOffset(1);
   Graph_histogram5->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram5);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect20{
      0.22, 1.22, 2.22, 3.22, 4.22, 5.22, 6.22, 7.22, 8.220000000000001, 9.220000000000001,
      10.22, 11.22, 12.22, 13.22, 14.22, 15.22, 16.22, 17.22, 18.22, 19.22,
      20.22, 21.22, 22.22, 23.22, 24.22, 25.22, 26.22, 27.22, 28.22, 29.22
   };
   std::vector<Double_t> gre_fy_vect21{
      1.584329986715362, 2.505158048103695, 1.593604563149505, 2.432487906395269, 1.472135451243169, 1.390528678199404, 1.783503110650894, 1.798066812501501, 2.14518111985538, 1.45780202764904,
      1.381707340133693, 1.756508256860137, 1.762588794910788, 2.180906659966506, 1.240827759745586, 1.464314982570117, 1.490086690559315, 1.641496263885358, 2.981356885809821, 1.21857463050308,
      1.427774045224099, 1.471639789687078, 1.607490266357472, 2.924311813551856, 1.127831261861273, 1.311321559817161, 1.527555975219524, 1.100046562942487, 1.285167031135319, 1.476615143116939
   };
   std::vector<Double_t> gre_fex_vect22{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect23{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect20.data(), gre_fy_vect21.data(), gre_fex_vect22.data(), gre_fey_vect23.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#003366"));
   gre->SetMarkerColor(TColor::GetColor("#003366"));
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram6 = new TH1F("Graph_histogram6", "Graph", 100, 0, 32.12);
   Graph_histogram6->SetMinimum(0.9116755306557538);
   Graph_histogram6->SetMaximum(3.169727918096555);
   Graph_histogram6->SetDirectory(nullptr);
   Graph_histogram6->SetStats(0);
   Graph_histogram6->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram6->GetXaxis()->SetLabelFont(42);
   Graph_histogram6->GetXaxis()->SetTitleOffset(1);
   Graph_histogram6->GetXaxis()->SetTitleFont(42);
   Graph_histogram6->GetYaxis()->SetLabelFont(42);
   Graph_histogram6->GetYaxis()->SetTitleFont(42);
   Graph_histogram6->GetZaxis()->SetLabelFont(42);
   Graph_histogram6->GetZaxis()->SetTitleOffset(1);
   Graph_histogram6->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram6);
   
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
   canvas_fit_parameters_24b4_gauss_sigma->Modified();
   canvas_fit_parameters_24b4_gauss_sigma->SetSelected(canvas_fit_parameters_24b4_gauss_sigma);
}
