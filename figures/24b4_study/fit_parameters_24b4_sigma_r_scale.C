#ifdef __CLING__
#pragma cling optimize(0)
#endif
void fit_parameters_24b4_sigma_r_scale()
{
//=========Macro generated from canvas: canvas_fit_parameters_24b4_sigma_r_scale/
//=========  (Mon Oct  5 14:16:53 2026) by ROOT version 6.36.04
   TCanvas *canvas_fit_parameters_24b4_sigma_r_scale = new TCanvas("canvas_fit_parameters_24b4_sigma_r_scale", "", 0, 0, 1500, 700);
   gStyle->SetOptFit(0);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(1);
   TColor::SetPalette(57, nullptr);
   canvas_fit_parameters_24b4_sigma_r_scale->Range(-3.968208,0.3918057,30.71387,0.9520306);
   canvas_fit_parameters_24b4_sigma_r_scale->SetFillColor(0);
   canvas_fit_parameters_24b4_sigma_r_scale->SetBorderMode(0);
   canvas_fit_parameters_24b4_sigma_r_scale->SetBorderSize(2);
   canvas_fit_parameters_24b4_sigma_r_scale->SetRightMargin(0.035);
   canvas_fit_parameters_24b4_sigma_r_scale->SetTopMargin(0.075);
   canvas_fit_parameters_24b4_sigma_r_scale->SetBottomMargin(0.19);
   canvas_fit_parameters_24b4_sigma_r_scale->SetFrameBorderMode(0);
   canvas_fit_parameters_24b4_sigma_r_scale->SetFrameBorderMode(0);
   
   TH1D *frame_fit_parameters_24b4_sigma_r_scale__4 = new TH1D("frame_fit_parameters_24b4_sigma_r_scale__4", "", 30, -0.5, 29.5);
   frame_fit_parameters_24b4_sigma_r_scale__4->SetMinimum(0.4982484059175372);
   frame_fit_parameters_24b4_sigma_r_scale__4->SetMaximum(0.9100136952882726);
   frame_fit_parameters_24b4_sigma_r_scale__4->SetStats(0);
   frame_fit_parameters_24b4_sigma_r_scale__4->SetLineColor(TColor::GetColor("#000099"));
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetTitle("Fit bin");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(1, "vh0");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(2, "vh1");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(3, "vh2");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(4, "vh3");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(5, "h0");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(6, "h1");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(7, "h2");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(8, "h3");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(9, "h4");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(10, "h5");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(11, "h6");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(12, "h7");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(13, "h8");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(14, "h9");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(15, "m0");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(16, "m1");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(17, "m2");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(18, "m3");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(19, "m4");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(20, "m5");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(21, "m6");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(22, "m7");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(23, "m8");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(24, "m9");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(25, "l0");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(26, "l1");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(27, "l2");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(28, "l3");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(29, "l4");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetBinLabel(30, "l5");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetLabelSize(0.03200000151991844);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetTitleSize(0.04699999839067459);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetTitleOffset(1.549999952316284);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetXaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetYaxis()->SetTitle("Right width scale");
   frame_fit_parameters_24b4_sigma_r_scale__4->GetYaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetYaxis()->SetLabelSize(0.0430000014603138);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetYaxis()->SetTitleSize(0.05000000074505806);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetYaxis()->SetTitleOffset(0.8999999761581421);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetYaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetZaxis()->SetLabelFont(42);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetZaxis()->SetTitleOffset(1);
   frame_fit_parameters_24b4_sigma_r_scale__4->GetZaxis()->SetTitleFont(42);
   frame_fit_parameters_24b4_sigma_r_scale__4->Draw();
   TLine *line = new TLine(0.5, 0.498248, 0.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(1.5, 0.498248, 1.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(2.5, 0.498248, 2.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(3.5, 0.498248, 3.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(4.5, 0.498248, 4.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(5.5, 0.498248, 5.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(6.5, 0.498248, 6.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(7.5, 0.498248, 7.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(8.5, 0.498248, 8.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(9.5, 0.498248, 9.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(10.5, 0.498248, 10.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(11.5, 0.498248, 11.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(12.5, 0.498248, 12.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(13.5, 0.498248, 13.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(14.5, 0.498248, 14.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(15.5, 0.498248, 15.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(16.5, 0.498248, 16.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(17.5, 0.498248, 17.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(18.5, 0.498248, 18.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(19.5, 0.498248, 19.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(20.5, 0.498248, 20.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(21.5, 0.498248, 21.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(22.5, 0.498248, 22.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(23.5, 0.498248, 23.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(24.5, 0.498248, 24.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(25.5, 0.498248, 25.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(26.5, 0.498248, 26.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(27.5, 0.498248, 27.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   line = new TLine(28.5, 0.498248, 28.5, 0.910014);
   line->SetLineColor(TColor::GetColor("#999999"));
   line->SetLineStyle(3);
   line->Draw();
   
   std::vector<Double_t> gre_fx_vect36{
      -0.22, 0.78, 1.78, 2.78, 3.78, 4.78, 5.78, 6.78, 7.78, 8.779999999999999,
      9.779999999999999, 10.78, 11.78, 12.78, 13.78, 14.78, 15.78, 16.78, 17.78, 18.78,
      19.78, 20.78, 21.78, 22.78, 23.78, 24.78, 25.78, 26.78, 27.78, 28.78
   };
   std::vector<Double_t> gre_fy_vect37{
      0.5333330476074666, 0.7004396268145165, 0.5434233928023682, 0.7501320185724542, 0.6784003657644582, 0.8036775251308715, 0.7104171474540952, 0.8013483395774854, 0.752791073162857, 0.6987350086563103,
      0.7996552009479913, 0.7498491425101492, 0.8511092014705129, 0.5537697212868027, 0.6836983192861095, 0.6790331746408265, 0.7071356447269375, 0.7820454639955798, 0.6293548050705127, 0.6999387855526517,
      0.6930375646741435, 0.7013781517015668, 0.7837554538505158, 0.6818924360863788, 0.6640196666418637, 0.6867126657293158, 0.7161457064653447, 0.6693855127380697, 0.6943176973750018, 0.7179128635994074
   };
   std::vector<Double_t> gre_fex_vect38{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect39{
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001
   };
   TGraphErrors *gre = new TGraphErrors(30, gre_fx_vect36.data(), gre_fy_vect37.data(), gre_fex_vect38.data(), gre_fey_vect39.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#999999"));
   gre->SetMarkerColor(TColor::GetColor("#999999"));
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram10 = new TH1F("Graph_histogram10", "Graph", 100, -3.120000000000001, 31.68);
   Graph_histogram10->SetMinimum(0.500355432221162);
   Graph_histogram10->SetMaximum(0.8840868168568176);
   Graph_histogram10->SetDirectory(nullptr);
   Graph_histogram10->SetStats(0);
   Graph_histogram10->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram10->GetXaxis()->SetLabelFont(42);
   Graph_histogram10->GetXaxis()->SetTitleOffset(1);
   Graph_histogram10->GetXaxis()->SetTitleFont(42);
   Graph_histogram10->GetYaxis()->SetLabelFont(42);
   Graph_histogram10->GetYaxis()->SetTitleFont(42);
   Graph_histogram10->GetZaxis()->SetLabelFont(42);
   Graph_histogram10->GetZaxis()->SetTitleOffset(1);
   Graph_histogram10->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram10);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect40{
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
      10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29
   };
   std::vector<Double_t> gre_fy_vect41{
      0.5314175691496259, 0.7158362508147507, 0.5421761991557704, 0.7270633626507074, 0.6621667624142649, 0.7867735173995555, 0.7307479656056026, 0.8247432489163444, 0.6682661534743405, 0.6594416724859687,
      0.8429641390488988, 0.742553630213477, 0.836878848486821, 0.6657392341565922, 0.6894331607659959, 0.6799718034164284, 0.7141269265547212, 0.7830926193634473, 0.6667090698881618, 0.6891474529264756,
      0.6975961065748857, 0.7112035721331393, 0.7766645743566016, 0.6176769273605635, 0.6706322189702428, 0.6794898918448607, 0.7083365681480036, 0.6873772330573162, 0.703301423085918, 0.7423623926535289
   };
   std::vector<Double_t> gre_fex_vect42{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect43{
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001
   };
   gre = new TGraphErrors(30, gre_fx_vect40.data(), gre_fy_vect41.data(), gre_fex_vect42.data(), gre_fey_vect43.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#990000"));
   gre->SetMarkerColor(TColor::GetColor("#990000"));
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram11 = new TH1F("Graph_histogram11", "Graph", 100, 0, 31.9);
   Graph_histogram11->SetMinimum(0.4990629121596986);
   Graph_histogram11->SetMaximum(0.875318796038826);
   Graph_histogram11->SetDirectory(nullptr);
   Graph_histogram11->SetStats(0);
   Graph_histogram11->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram11->GetXaxis()->SetLabelFont(42);
   Graph_histogram11->GetXaxis()->SetTitleOffset(1);
   Graph_histogram11->GetXaxis()->SetTitleFont(42);
   Graph_histogram11->GetYaxis()->SetLabelFont(42);
   Graph_histogram11->GetYaxis()->SetTitleFont(42);
   Graph_histogram11->GetZaxis()->SetLabelFont(42);
   Graph_histogram11->GetZaxis()->SetTitleOffset(1);
   Graph_histogram11->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram11);
   
   gre->Draw("pz ");
   
   std::vector<Double_t> gre_fx_vect44{
      0.22, 1.22, 2.22, 3.22, 4.22, 5.22, 6.22, 7.22, 8.220000000000001, 9.220000000000001,
      10.22, 11.22, 12.22, 13.22, 14.22, 15.22, 16.22, 17.22, 18.22, 19.22,
      20.22, 21.22, 22.22, 23.22, 24.22, 25.22, 26.22, 27.22, 28.22, 29.22
   };
   std::vector<Double_t> gre_fy_vect45{
      0.5324284876464178, 0.7053956422442018, 0.542610208240342, 0.7429020612101791, 0.6725391893825284, 0.7986751820080472, 0.7168792093606774, 0.8086594907894972, 0.7435542008387217, 0.6879703161615549,
      0.8167539894652884, 0.7486214463283719, 0.8469228347432931, 0.6087080016843649, 0.6856079565227557, 0.6806075566502167, 0.7097883651210647, 0.7791727154031772, 0.63967780532195, 0.6971105512895145,
      0.6949417571439026, 0.7031063535775585, 0.7808901068958923, 0.6554944023201323, 0.6664517326890614, 0.6841081013421147, 0.7127870992305491, 0.6770642897436785, 0.6977595771725834, 0.7254590698140039
   };
   std::vector<Double_t> gre_fex_vect46{
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
   };
   std::vector<Double_t> gre_fey_vect47{
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001,
      0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001
   };
   gre = new TGraphErrors(30, gre_fx_vect44.data(), gre_fy_vect45.data(), gre_fex_vect46.data(), gre_fey_vect47.data());
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);
   gre->SetLineColor(TColor::GetColor("#003366"));
   gre->SetMarkerColor(TColor::GetColor("#003366"));
   gre->SetMarkerStyle(24);
   gre->SetMarkerSize(0.85);
   
   TH1F *Graph_histogram12 = new TH1F("Graph_histogram12", "Graph", 100, 0, 32.12);
   Graph_histogram12->SetMinimum(0.4997790529367303);
   Graph_histogram12->SetMaximum(0.8795722694529806);
   Graph_histogram12->SetDirectory(nullptr);
   Graph_histogram12->SetStats(0);
   Graph_histogram12->SetLineColor(TColor::GetColor("#000099"));
   Graph_histogram12->GetXaxis()->SetLabelFont(42);
   Graph_histogram12->GetXaxis()->SetTitleOffset(1);
   Graph_histogram12->GetXaxis()->SetTitleFont(42);
   Graph_histogram12->GetYaxis()->SetLabelFont(42);
   Graph_histogram12->GetYaxis()->SetTitleFont(42);
   Graph_histogram12->GetZaxis()->SetLabelFont(42);
   Graph_histogram12->GetZaxis()->SetTitleOffset(1);
   Graph_histogram12->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_histogram12);
   
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
   canvas_fit_parameters_24b4_sigma_r_scale->Modified();
   canvas_fit_parameters_24b4_sigma_r_scale->SetSelected(canvas_fit_parameters_24b4_sigma_r_scale);
}
