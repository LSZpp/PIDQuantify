#ifdef __CLING__
#pragma cling optimize(0)
#endif
void fit_parameters_24b4_alpha_l()
{
//=========Macro generated from canvas: canvas_fit_parameters_24b4_alpha_l/
//=========  (Mon Oct  5 14:16:54 2026) by ROOT version 6.36.04
   TCanvas *canvas_fit_parameters_24b4_alpha_l = new TCanvas("canvas_fit_parameters_24b4_alpha_l", "", 0, 0, 1500, 700);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(1);
   TColor::SetPalette(57, nullptr);
   canvas_fit_parameters_24b4_alpha_l->Range(-3.968208,0.3388003,30.71387,4.002741);
   canvas_fit_parameters_24b4_alpha_l->SetFillColor(0);
   canvas_fit_parameters_24b4_alpha_l->SetBorderMode(0);
   canvas_fit_parameters_24b4_alpha_l->SetBorderSize(2);
   canvas_fit_parameters_24b4_alpha_l->SetRightMargin(0.035);
   canvas_fit_parameters_24b4_alpha_l->SetTopMargin(0.075);
   canvas_fit_parameters_24b4_alpha_l->SetBottomMargin(0.19);
   canvas_fit_parameters_24b4_alpha_l->SetFrameBorderMode(0);
   canvas_fit_parameters_24b4_alpha_l->SetFrameBorderMode(0);
   
   TH1D *frame_fit_parameters_24b4_alpha_l__5 = new TH1D("frame_fit_parameters_24b4_alpha_l__5", "", 30, -0.5, 29.5);
   frame_fit_parameters_24b4_alpha_l__5->SetMinimum(1.034949019823902);
   frame_fit_parameters_24b4_alpha_l__5->SetMaximum(3.7279454736588);
   frame_fit_parameters_24b4_alpha_l__5->SetStats(0);
   frame_fit_parameters_24b4_alpha_l__5->SetLineColor(TColor::GetColor("#000099"));
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetTitle("Fit bin");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(1, "vh0");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(2, "vh1");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(3, "vh2");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(4, "vh3");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(5, "h0");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(6, "h1");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(7, "h2");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(8, "h3");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(9, "h4");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(10, "h5");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(11, "h6");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(12, "h7");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(13, "h8");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(14, "h9");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(15, "m0");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(16, "m1");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(17, "m2");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(18, "m3");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(19, "m4");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(20, "m5");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(21, "m6");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(22, "m7");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(23, "m8");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(24, "m9");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(25, "l0");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(26, "l1");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(27, "l2");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(28, "l3");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(29, "l4");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetBinLabel(30, "l5");
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetLabelSize(0.03200000151991844);
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetTitleSize(0.04699999839067459);
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetTitleOffset(1.549999952316284);
   frame_fit_parameters_24b4_alpha_l__5->GetXaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_alpha_l__5->GetYaxis()->SetTitle("Left tail #alpha");
   frame_fit_parameters_24b4_alpha_l__5->GetYaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_alpha_l__5->GetYaxis()->SetLabelSize(0.0430000014603138);
   frame_fit_parameters_24b4_alpha_l__5->GetYaxis()->SetTitleSize(0.05000000074505806);
   frame_fit_parameters_24b4_alpha_l__5->GetYaxis()->SetTitleOffset(0.8999999761581421);
   frame_fit_parameters_24b4_alpha_l__5->GetYaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_alpha_l__5->GetZaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_alpha_l__5->GetZaxis()->SetTitleOffset(1);
   frame_fit_parameters_24b4_alpha_l__5->GetZaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_alpha_l__5->Draw();
   TLine *line = new TLine(0.5, 1.03495, 0.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(1.5, 1.03495, 1.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(2.5, 1.03495, 2.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(3.5, 1.03495, 3.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(4.5, 1.03495, 4.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(5.5, 1.03495, 5.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(6.5, 1.03495, 6.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(7.5, 1.03495, 7.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(8.5, 1.03495, 8.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(9.5, 1.03495, 9.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(10.5, 1.03495, 10.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(11.5, 1.03495, 11.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(12.5, 1.03495, 12.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(13.5, 1.03495, 13.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(14.5, 1.03495, 14.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(15.5, 1.03495, 15.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(16.5, 1.03495, 16.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(17.5, 1.03495, 17.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(18.5, 1.03495, 18.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(19.5, 1.03495, 19.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(20.5, 1.03495, 20.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(21.5, 1.03495, 21.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(22.5, 1.03495, 22.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(23.5, 1.03495, 23.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(24.5, 1.03495, 24.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(25.5, 1.03495, 25.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(26.5, 1.03495, 26.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(27.5, 1.03495, 27.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(28.5, 1.03495, 28.5, 3.72795);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   
   std::vector<Double_t> gre_fx_vect48{
      -0.22, 0.78, 1.78, 2.78, 3.78, 4.78, 5.78, 6.78, 7.78, 8.779999999999999,
      9.779999999999999, 10.78, 11.78, 12.78, 13.78, 14.78, 15.78, 16.78, 17.78, 18.78,
      19.78, 20.78, 21.78, 22.78, 23.78, 24.78, 25.78, 26.78, 27.78, 28.78
   };
   std::vector<Double_t> gre_fy_vect49{
      1.40805144088973, 3.349042847338268, 1.40805144088973, 3.349042847338268, 2.191244628823417, 1.593224953416561, 2.108356569472234, 1.686490999323799, 1.251413002495217, 2.191244628823417,
      1.615374087021982, 2.11010419047892, 1.668090719614734, 1.279581545117486, 1.728155616120561, 1.899984400534144, 1.675285943075185, 1.53719697713227, 2.6827907907139, 1.746445195128591,
      1.895788685678601, 1.678243151058923, 1.563716272966447, 2.6827907907139, 1.481798618774411, 1.487036690837751, 1.375630252626444, 1.484197253388643, 1.479422952320132, 1.368506401643367
   };
   std::vector<Double_t> gre_fex_vect50{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect51{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   TGraphErrors *gre = new TGraphErrors(30, gre_fx_vect48.data(), gre_fy_vect49.data(), gre_fex_vect50.data(), gre_fey_vect51.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#999999"));
   gre->SetMarkerColor(TColor::GetColor("#999999"));
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram13 = new TH1F("Graph_histogram13", "Graph", 100, -3.120000000000001, 31.68);
   Graph_histogram13->SetMinimum(1.041410018010911);
   Graph_histogram13->SetMaximum(3.559045831822573);
   Graph_histogram13->SetDirectory(nullptr);
   Graph_histogram13->SetStats(0);
   Graph_histogram13->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram13->GetXaxis()->SetLabelFont(42);
   Graph_histogram13->GetXaxis()->SetTitleOffset(1);
   Graph_histogram13->GetXaxis()->SetTitleFont(42);
   Graph_histogram13->GetYaxis()->SetLabelFont(42);
   Graph_histogram13->GetYaxis()->SetTitleFont(42);
   Graph_histogram13->GetZaxis()->SetLabelFont(42);
   Graph_histogram13->GetZaxis()->SetTitleOffset(1);
   Graph_histogram13->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram13);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect52{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29
   };
   std::vector<Double_t> gre_fy_vect53{
      1.40805144088973, 3.349042847338268, 1.40805144088973, 3.349042847338268, 2.191244628823417, 1.5983183653506, 2.090947655636403, 1.664383213191946, 1.329986743212488, 2.191244628823417,
      1.564577360103683, 2.055505325493482, 1.624723959462032, 1.245539367779754, 1.704981588533036, 1.872375060307947, 1.626320218480242, 1.480034233629799, 2.6827907907139, 1.70858849056571,
      1.835366776412628, 1.65446313315235, 1.520240299396177, 2.6827907907139, 1.463522612586598, 1.479402869406446, 1.344318273171646, 1.410810045866645, 1.429715470248628, 1.281604664839205
   };
   std::vector<Double_t> gre_fex_vect54{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect55{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect52.data(), gre_fy_vect53.data(), gre_fex_vect54.data(), gre_fey_vect55.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#990000"));
   gre->SetMarkerColor(TColor::GetColor("#990000"));
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram14 = new TH1F("Graph_histogram14", "Graph", 100, 0, 31.9);
   Graph_histogram14->SetMinimum(1.034949019823902);
   Graph_histogram14->SetMaximum(3.559633195294119);
   Graph_histogram14->SetDirectory(nullptr);
   Graph_histogram14->SetStats(0);
   Graph_histogram14->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram14->GetXaxis()->SetLabelFont(42);
   Graph_histogram14->GetXaxis()->SetTitleOffset(1);
   Graph_histogram14->GetXaxis()->SetTitleFont(42);
   Graph_histogram14->GetYaxis()->SetLabelFont(42);
   Graph_histogram14->GetYaxis()->SetTitleFont(42);
   Graph_histogram14->GetZaxis()->SetLabelFont(42);
   Graph_histogram14->GetZaxis()->SetTitleOffset(1);
   Graph_histogram14->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram14);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect56{
      0.22, 1.22, 2.22, 3.22, 4.22, 5.22, 6.22, 7.22, 8.220000000000001, 9.220000000000001,
      10.22, 11.22, 12.22, 13.22, 14.22, 15.22, 16.22, 17.22, 18.22, 19.22,
      20.22, 21.22, 22.22, 23.22, 24.22, 25.22, 26.22, 27.22, 28.22, 29.22
   };
   std::vector<Double_t> gre_fy_vect57{
      1.40805144088973, 3.349042847338268, 1.40805144088973, 3.349042847338268, 2.191244628823417, 1.59422255867696, 2.102977197158549, 1.680175108659102, 1.304684106582983, 2.191244628823417,
      1.598607270824227, 2.09123845306779, 1.654067918241247, 1.310556879900513, 1.719853743164698, 1.885346855802953, 1.654294859634805, 1.525532957686477, 2.6827907907139, 1.735390643242225,
      1.874343797812916, 1.666902004248623, 1.548293090056316, 2.6827907907139, 1.47531415138727, 1.484139763926724, 1.367222742273078, 1.455115927739462, 1.460365961795207, 1.335864311231195
   };
   std::vector<Double_t> gre_fex_vect58{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect59{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect56.data(), gre_fy_vect57.data(), gre_fex_vect58.data(), gre_fey_vect59.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#003366"));
   gre->SetMarkerColor(TColor::GetColor("#003366"));
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram15 = new TH1F("Graph_histogram15", "Graph", 100, 0, 32.12);
   Graph_histogram15->SetMinimum(1.100008232507454);
   Graph_histogram15->SetMaximum(3.553718721413796);
   Graph_histogram15->SetDirectory(nullptr);
   Graph_histogram15->SetStats(0);
   Graph_histogram15->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram15->GetXaxis()->SetLabelFont(42);
   Graph_histogram15->GetXaxis()->SetTitleOffset(1);
   Graph_histogram15->GetXaxis()->SetTitleFont(42);
   Graph_histogram15->GetYaxis()->SetLabelFont(42);
   Graph_histogram15->GetYaxis()->SetTitleFont(42);
   Graph_histogram15->GetZaxis()->SetLabelFont(42);
   Graph_histogram15->GetZaxis()->SetTitleOffset(1);
   Graph_histogram15->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram15);
   
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
   canvas_fit_parameters_24b4_alpha_l->Modified();
   canvas_fit_parameters_24b4_alpha_l->SetSelected(canvas_fit_parameters_24b4_alpha_l);
}
