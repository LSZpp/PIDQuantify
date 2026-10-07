#ifdef __CLING__
#pragma cling optimize(0)
#endif
void fit_parameters_24b4_mean()
{
//=========Macro generated from canvas: canvas_fit_parameters_24b4_mean/
//=========  (Mon Oct  5 14:16:53 2026) by ROOT version 6.36.04
   TCanvas *canvas_fit_parameters_24b4_mean = new TCanvas("canvas_fit_parameters_24b4_mean", "", 0, 0, 1500, 700);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(1);
   TColor::SetPalette(57, nullptr);
   canvas_fit_parameters_24b4_mean->Range(-3.968208,1115.2,30.71387,1116.283);
   canvas_fit_parameters_24b4_mean->SetFillColor(0);
   canvas_fit_parameters_24b4_mean->SetBorderMode(0);
   canvas_fit_parameters_24b4_mean->SetBorderSize(2);
   canvas_fit_parameters_24b4_mean->SetRightMargin(0.035);
   canvas_fit_parameters_24b4_mean->SetTopMargin(0.075);
   canvas_fit_parameters_24b4_mean->SetBottomMargin(0.19);
   canvas_fit_parameters_24b4_mean->SetFrameBorderMode(0);
   canvas_fit_parameters_24b4_mean->SetFrameBorderMode(0);
   
   TH1D *frame_fit_parameters_24b4_mean__1 = new TH1D("frame_fit_parameters_24b4_mean__1", "", 30, -0.5, 29.5);
   frame_fit_parameters_24b4_mean__1->SetMinimum(1115.405926344611);
   frame_fit_parameters_24b4_mean__1->SetMaximum(1116.201427655683);
   frame_fit_parameters_24b4_mean__1->SetStats(0);
   frame_fit_parameters_24b4_mean__1->SetLineColor(TColor::GetColor("#000099"));
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetTitle("Fit bin");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(1, "vh0");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(2, "vh1");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(3, "vh2");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(4, "vh3");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(5, "h0");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(6, "h1");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(7, "h2");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(8, "h3");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(9, "h4");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(10, "h5");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(11, "h6");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(12, "h7");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(13, "h8");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(14, "h9");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(15, "m0");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(16, "m1");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(17, "m2");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(18, "m3");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(19, "m4");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(20, "m5");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(21, "m6");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(22, "m7");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(23, "m8");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(24, "m9");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(25, "l0");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(26, "l1");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(27, "l2");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(28, "l3");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(29, "l4");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetBinLabel(30, "l5");
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetLabelSize(0.03200000151991844);
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetTitleSize(0.04699999839067459);
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetTitleOffset(1.549999952316284);
   frame_fit_parameters_24b4_mean__1->GetXaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_mean__1->GetYaxis()->SetTitle("Signal mean [MeV/#it{c}^{2}]");
   frame_fit_parameters_24b4_mean__1->GetYaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_mean__1->GetYaxis()->SetLabelSize(0.0430000014603138);
   frame_fit_parameters_24b4_mean__1->GetYaxis()->SetTitleSize(0.05000000074505806);
   frame_fit_parameters_24b4_mean__1->GetYaxis()->SetTitleOffset(0.8999999761581421);
   frame_fit_parameters_24b4_mean__1->GetYaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_mean__1->GetZaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_mean__1->GetZaxis()->SetTitleOffset(1);
   frame_fit_parameters_24b4_mean__1->GetZaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_mean__1->Draw();
   TLine *line = new TLine(0.5, 1115.41, 0.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(1.5, 1115.41, 1.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(2.5, 1115.41, 2.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(3.5, 1115.41, 3.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(4.5, 1115.41, 4.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(5.5, 1115.41, 5.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(6.5, 1115.41, 6.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(7.5, 1115.41, 7.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(8.5, 1115.41, 8.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(9.5, 1115.41, 9.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(10.5, 1115.41, 10.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(11.5, 1115.41, 11.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(12.5, 1115.41, 12.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(13.5, 1115.41, 13.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(14.5, 1115.41, 14.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(15.5, 1115.41, 15.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(16.5, 1115.41, 16.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(17.5, 1115.41, 17.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(18.5, 1115.41, 18.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(19.5, 1115.41, 19.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(20.5, 1115.41, 20.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(21.5, 1115.41, 21.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(22.5, 1115.41, 22.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(23.5, 1115.41, 23.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(24.5, 1115.41, 24.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(25.5, 1115.41, 25.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(26.5, 1115.41, 26.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(27.5, 1115.41, 27.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(28.5, 1115.41, 28.5, 1116.2);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   
   std::vector<Double_t> gre_fx_vect0{
      -0.22, 0.78, 1.78, 2.78, 3.78, 4.78, 5.78, 6.78, 7.78, 8.779999999999999,
      9.779999999999999, 10.78, 11.78, 12.78, 13.78, 14.78, 15.78, 16.78, 17.78, 18.78,
      19.78, 20.78, 21.78, 22.78, 23.78, 24.78, 25.78, 26.78, 27.78, 28.78
   };
   std::vector<Double_t> gre_fy_vect1{
      1115.887385013646, 1115.818215370316, 1115.872719446542, 1115.790545642499, 1115.716471207125, 1115.706680696388, 1115.709163311035, 1115.720602910566, 1115.926887106605, 1115.659994227073,
      1115.673834771665, 1115.646793514332, 1115.690255066565, 1115.918542244669, 1115.693664076472, 1115.701632359867, 1115.706017772002, 1115.657989289443, 1115.538087509102, 1115.630272735777,
      1115.635229453102, 1115.672794135444, 1115.631007821998, 1115.468274884539, 1115.784312208927, 1115.726341203294, 1115.686415602047, 1115.74116572018, 1115.663486767077, 1115.648958319619
   };
   std::vector<Double_t> gre_fex_vect2{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect3{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   TGraphErrors *gre = new TGraphErrors(30, gre_fx_vect0.data(), gre_fy_vect1.data(), gre_fex_vect2.data(), gre_fey_vect3.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#999999"));
   gre->SetMarkerColor(TColor::GetColor("#999999"));
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram1 = new TH1F("Graph_histogram1", "Graph", 100, -3.120000000000001, 31.68);
   Graph_histogram1->SetMinimum(1115.422173662332);
   Graph_histogram1->SetMaximum(1115.972988328811);
   Graph_histogram1->SetDirectory(nullptr);
   Graph_histogram1->SetStats(0);
   Graph_histogram1->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram1->GetXaxis()->SetLabelFont(42);
   Graph_histogram1->GetXaxis()->SetTitleOffset(1);
   Graph_histogram1->GetXaxis()->SetTitleFont(42);
   Graph_histogram1->GetYaxis()->SetLabelFont(42);
   Graph_histogram1->GetYaxis()->SetTitleFont(42);
   Graph_histogram1->GetZaxis()->SetLabelFont(42);
   Graph_histogram1->GetZaxis()->SetTitleOffset(1);
   Graph_histogram1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram1);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect4{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29
   };
   std::vector<Double_t> gre_fy_vect5{
      1115.936917357459, 1116.006727107956, 1115.938637321384, 1115.897648206911, 1115.764370490745, 1115.761721438115, 1115.767847524986, 1115.816697612013, 1116.089360283814, 1115.824134076369,
      1115.757755354428, 1115.753128096729, 1115.78678046851, 1115.987896132527, 1115.739901534183, 1115.78526344426, 1115.805905498127, 1115.758110603131, 1115.908243849649, 1115.738463425936,
      1115.728388186857, 1115.760073798781, 1115.7466311489, 1115.780165466485, 1115.826863446599, 1115.801565808695, 1115.802878373176, 1115.739976650116, 1115.694701341346, 1115.711758414117
   };
   std::vector<Double_t> gre_fex_vect6{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect7{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect4.data(), gre_fy_vect5.data(), gre_fex_vect6.data(), gre_fey_vect7.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#990000"));
   gre->SetMarkerColor(TColor::GetColor("#990000"));
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram2 = new TH1F("Graph_histogram2", "Graph", 100, 0, 31.9);
   Graph_histogram2->SetMinimum(1115.654995447099);
   Graph_histogram2->SetMaximum(1116.12906617806);
   Graph_histogram2->SetDirectory(nullptr);
   Graph_histogram2->SetStats(0);
   Graph_histogram2->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram2->GetXaxis()->SetLabelFont(42);
   Graph_histogram2->GetXaxis()->SetTitleOffset(1);
   Graph_histogram2->GetXaxis()->SetTitleFont(42);
   Graph_histogram2->GetYaxis()->SetLabelFont(42);
   Graph_histogram2->GetYaxis()->SetTitleFont(42);
   Graph_histogram2->GetZaxis()->SetLabelFont(42);
   Graph_histogram2->GetZaxis()->SetTitleOffset(1);
   Graph_histogram2->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram2);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect8{
      0.22, 1.22, 2.22, 3.22, 4.22, 5.22, 6.22, 7.22, 8.220000000000001, 9.220000000000001,
      10.22, 11.22, 12.22, 13.22, 14.22, 15.22, 16.22, 17.22, 18.22, 19.22,
      20.22, 21.22, 22.22, 23.22, 24.22, 25.22, 26.22, 27.22, 28.22, 29.22
   };
   std::vector<Double_t> gre_fy_vect9{
      1115.905050090166, 1115.879705863932, 1115.894067587767, 1115.82222758725, 1115.733329316748, 1115.725192993121, 1115.729388273122, 1115.754681535082, 1115.974512697726, 1115.715649864379,
      1115.701057864972, 1115.681555627607, 1115.722123783559, 1115.937795813092, 1115.709453899414, 1115.729790169222, 1115.741335136078, 1115.696148764791, 1115.67970638173, 1115.668404750664,
      1115.668617548806, 1115.705529660484, 1115.671180705411, 1115.573193532629, 1115.799600498546, 1115.75352416998, 1115.729543862904, 1115.740347882288, 1115.675066531763, 1115.672133338134
   };
   std::vector<Double_t> gre_fex_vect10{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect11{
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002,
      0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002, 0.0002
   };
   gre = new TGraphErrors(30, gre_fx_vect8.data(), gre_fy_vect9.data(), gre_fex_vect10.data(), gre_fey_vect11.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#003366"));
   gre->SetMarkerColor(TColor::GetColor("#003366"));
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram3 = new TH1F("Graph_histogram3", "Graph", 100, 0, 32.12);
   Graph_histogram3->SetMinimum(1115.53282161612);
   Graph_histogram3->SetMaximum(1116.014884614236);
   Graph_histogram3->SetDirectory(nullptr);
   Graph_histogram3->SetStats(0);
   Graph_histogram3->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram3->GetXaxis()->SetLabelFont(42);
   Graph_histogram3->GetXaxis()->SetTitleOffset(1);
   Graph_histogram3->GetXaxis()->SetTitleFont(42);
   Graph_histogram3->GetYaxis()->SetLabelFont(42);
   Graph_histogram3->GetYaxis()->SetTitleFont(42);
   Graph_histogram3->GetZaxis()->SetLabelFont(42);
   Graph_histogram3->GetZaxis()->SetTitleOffset(1);
   Graph_histogram3->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram3);
   
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
   canvas_fit_parameters_24b4_mean->Modified();
   canvas_fit_parameters_24b4_mean->SetSelected(canvas_fit_parameters_24b4_mean);
}
