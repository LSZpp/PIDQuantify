// Combined 2D proton-ID efficiency maps (P vs ETA) at DLLp-DLLK>5.
// Combination is done on the histograms: sum(total), sum(passing), then divide.
// Four groups (one subdirectory each, under combined/):
//   24        : 2024 blocks 1,2,3,5,6,7,8
//   25c1      : 25c1 down + up
//   24_25c1   : 24 + 25c1
//   25c234    : 25c2, 25c3, 25c4 up + down
// Values shown as PERCENT (x100, 1 dp). Bins with <1000 events killed (white).
// 256 contours, no title (file name is the label), p axis in GeV/c.
//
// Run:  root -l -b -q perf_finals_2d_combined.C

#include <vector>
#include <cmath>

const TString DIR    = "/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/2d";
const TString OUT    = "/home/lins/u3_PIDQuantify/figures/final_calibration/2d_differences/combined";
const TString CUT    = "DLLp-DLLK>5.0";
const double  MINEVT = 100.0;

struct DS { TString tag, newL0, oldL0, lc, pol; };
std::vector<DS> kData = {
    {"24b1", "L0_2024_block1","2024_WithUT_block1_v2","Lc_2024_block1","up"  },
    {"24b2", "L0_2024_block2","2024_WithUT_block2_v2","Lc_2024_block2","up"  },
    {"24b3", "L0_2024_block3","2024_WithUT_block3_v2","Lc_2024_block3","up"  },
    {"24b5", "L0_2024_block5","2024_WithUT_block5_v2","Lc_2024_block5","up"  },
    {"24b6", "L0_2024_block6","2024_WithUT_block6_v2","Lc_2024_block6","down"},
    {"24b7", "L0_2024_block7","2024_WithUT_block7_v2","Lc_2024_block7","down"},
    {"24b8", "L0_2024_block8","2024_WithUT_block8_v2","Lc_2024_block8","up"  },
    {"25c1d","L0_2025_c1",    "2025_c1_v0",           "Lc_2025_c1",    "down"},
    {"25c1u","L0_2025_c1",    "2025_c1_v0",           "Lc_2025_c1",    "up"  },
    {"25c2", "L0_2025_c2",    "2025_c2_v0",           "Lc_2025_c2",    "down"},
    {"25c3", "L0_2025_c3",    "2025_c3_v0",           "Lc_2025_c3",    "up"  },
    {"25c4u","L0_2025_c4",    "2025_c4_v0",           "Lc_2025_c4",    "up"  },
    {"25c4d","L0_2025_c4",    "2025_c4_v0",           "Lc_2025_c4",    "down"},
};

TString ds_for(const DS &e, const TString &set){
    if (set=="oldL0") return e.oldL0;
    if (set=="newL0") return e.newL0;
    return e.lc;
}
std::vector<DS> group(std::vector<TString> tags){
    std::vector<DS> g;
    for (auto &e : kData) for (auto &t : tags) if (e.tag==t) g.push_back(e);
    return g;
}

// Combine total+passing over the entries, then divide -> efficiency in %.
TH2D *combine(const std::vector<DS> &ents, const TString &set, const TString &uname, TH2D **totOut){
    TH2D *tot=nullptr,*pas=nullptr;
    for (auto &e : ents){
        TString path=Form("%s/%s/effhists-%s-%s-P-%s-P.ETA.root",
                          DIR.Data(),set.Data(),ds_for(e,set).Data(),e.pol.Data(),CUT.Data());
        TFile *f=TFile::Open(path);
        if (!f||f->IsZombie()){ printf("  [skip] %s\n",path.Data()); if(f) delete f; continue; }
        TH2D *t=(TH2D*)f->Get("total"), *p=(TH2D*)f->Get(Form("passing_%s",CUT.Data()));
        if (!t||!p){ f->Close(); delete f; continue; }
        if (!tot){ tot=(TH2D*)t->Clone(uname+"_tot"); tot->SetDirectory(0);
                   pas=(TH2D*)p->Clone(uname+"_pas"); pas->SetDirectory(0); }
        else     { tot->Add(t); pas->Add(p); }
        f->Close(); delete f;
    }
    if (!tot){ *totOut=nullptr; return nullptr; }
    TH2D *eff=(TH2D*)pas->Clone(uname+"_eff"); eff->SetDirectory(0);
    eff->Divide(pas,tot,1.,1.,"B"); eff->Scale(100.0);
    *totOut=tot; return eff;
}

// Clone with the X (momentum) axis converted from MeV to GeV.
TH2D *to_gev(TH2D *h, const TString &name){
    TAxis *ax=h->GetXaxis(); int nx=ax->GetNbins();
    std::vector<double> xe(nx+1);
    for (int i=1;i<=nx;i++) xe[i-1]=ax->GetBinLowEdge(i)/1000.;
    xe[nx]=ax->GetBinUpEdge(nx)/1000.;
    TAxis *ay=h->GetYaxis(); int ny=ay->GetNbins();
    std::vector<double> ye(ny+1);
    for (int j=1;j<=ny;j++) ye[j-1]=ay->GetBinLowEdge(j);
    ye[ny]=ay->GetBinUpEdge(ny);
    TH2D *g=new TH2D(name,"",nx,xe.data(),ny,ye.data()); g->SetDirectory(0);
    for (int i=1;i<=nx;i++) for (int j=1;j<=ny;j++){
        g->SetBinContent(i,j,h->GetBinContent(i,j));
        g->SetBinError  (i,j,h->GetBinError  (i,j));
    }
    return g;
}

void style(TH2D *h){
    h->SetTitle("");
    h->GetXaxis()->SetTitle("#it{p} [GeV/#it{c}]");
    h->GetYaxis()->SetTitle("#it{#eta}");
    h->GetYaxis()->SetTitleOffset(0.6);
    h->SetMarkerSize(0.55);
    h->SetContour(256);
}

void draw_save(TH2D *h, const TString &dir, const TString &name){
    TCanvas *c=new TCanvas(name,name,1200,800);
    c->SetTopMargin(0.05); c->SetRightMargin(0.12);
    c->SetLeftMargin(0.06); c->SetBottomMargin(0.10);
    h->Draw("COL1 Z TEXT");
    c->SaveAs(dir+"/"+name+".pdf");
    delete c;
}

// Absolute efficiency: colour scale fixed to 50-100 (kRainbow). ROOT whites out
// bins BELOW the minimum, so to keep the text for sub-50 bins we draw two layers:
// a colour layer clamped to [50,100] and a text layer with the true values.
void draw_eff(TH2D *eff, TH2D *tot, const TString &dir, const TString &name, const TString &uname){
    if(!eff) return;
    TH2D *h=(TH2D*)eff->Clone(uname+"_e"); h->SetDirectory(0);
    for (int i=1;i<=h->GetNbinsX();i++) for (int j=1;j<=h->GetNbinsY();j++)
        if (tot->GetBinContent(i,j)<MINEVT){ h->SetBinContent(i,j,0.); h->SetBinError(i,j,0.); }
    TH2D *gtxt=to_gev(h,uname+"_et"); style(gtxt);          // true values (killed=0 -> no text)
    TH2D *gcol=to_gev(h,uname+"_eg"); style(gcol);          // clamped colour layer
    double eps=(100.-50.)*1e-4;
    for (int i=1;i<=gcol->GetNbinsX();i++) for (int j=1;j<=gcol->GetNbinsY();j++){
        if (tot->GetBinContent(i,j)<MINEVT) continue;       // killed -> stays 0 (white)
        double v=gcol->GetBinContent(i,j);
        if      (v<=50.)  v=50.+eps;                         // below 50% -> minimum colour
        else if (v>=100.) v=100.;                            // above 100% -> ceiling
        gcol->SetBinContent(i,j,v);
    }
    gcol->SetMinimum(50); gcol->SetMaximum(100);
    gStyle->SetPalette(kRainbow);
    TCanvas *c=new TCanvas(name,name,1200,800);
    c->SetTopMargin(0.05); c->SetRightMargin(0.12); c->SetLeftMargin(0.06); c->SetBottomMargin(0.10);
    gcol->Draw("COL1 Z");   // COL1 whites the killed (exact-0) bins; <50 bins now sit at the floor colour
    gtxt->Draw("TEXT SAME");
    c->SaveAs(dir+"/"+name+".pdf");
    delete c;
}

// a - b (both %); kill bins where totA<MINEVT or totB<MINEVT (white, no text).
// Two layers: colour layer clamped to [vmin,vmax] (so bins BELOW the floor show
// the floor colour instead of being whited by ROOT) + text layer with the true
// values (out-of-range bins keep their real number). kThermometer, zero centred.
void draw_diff(TH2D *a, TH2D *b, TH2D *tA, TH2D *tB, const TString &dir, const TString &name,
               const TString &uname, double vmin, double vmax){
    if(!a||!b) return;
    TH2D *d=(TH2D*)a->Clone(uname+"_d"); d->SetDirectory(0); d->Add(b,-1.0);
    for (int i=1;i<=d->GetNbinsX();i++) for (int j=1;j<=d->GetNbinsY();j++)
        if (tA->GetBinContent(i,j)<MINEVT || tB->GetBinContent(i,j)<MINEVT){ d->SetBinContent(i,j,0.); d->SetBinError(i,j,0.); }
    TH2D *gtxt=to_gev(d,uname+"_dt"); style(gtxt);          // true values (killed=0 -> no text)
    TH2D *gcol=to_gev(d,uname+"_dg"); style(gcol);          // clamped colour layer
    double eps=(vmax-vmin)*1e-4;
    for (int i=1;i<=gcol->GetNbinsX();i++) for (int j=1;j<=gcol->GetNbinsY();j++){
        if (tA->GetBinContent(i,j)<MINEVT || tB->GetBinContent(i,j)<MINEVT) continue;  // killed -> stays 0 (white)
        double v=gcol->GetBinContent(i,j);
        if      (v<=vmin) v=vmin+eps;             // below floor -> floor colour
        else if (v>=vmax) v=vmax;                 // above ceiling
        else if (std::fabs(v)<eps) v=eps;         // avoid exact-0 (would white out)
        gcol->SetBinContent(i,j,v);
    }
    gcol->SetMinimum(vmin); gcol->SetMaximum(vmax);
    gStyle->SetPalette(kThermometer);
    TCanvas *c=new TCanvas(name,name,1200,800);
    c->SetTopMargin(0.05); c->SetRightMargin(0.12); c->SetLeftMargin(0.06); c->SetBottomMargin(0.10);
    gcol->Draw("COL1 Z");   // COL1 whites the exact-0 (killed) bins; COL would paint them at centre
    gtxt->Draw("TEXT SAME");
    c->SaveAs(dir+"/"+name+".pdf");
    delete c;
}

void perf_finals_2d_combined(){
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetNumberContours(256);
    gStyle->SetPaintTextFormat("4.1f");

    std::vector<TString> b24={"24b1","24b2","24b3","24b5","24b6","24b7","24b8"};
    std::vector<TString> c1 ={"25c1d","25c1u"};
    std::vector<TString> c234={"25c2","25c3","25c4u","25c4d"};
    std::vector<TString> b24c1=b24; b24c1.insert(b24c1.end(),c1.begin(),c1.end());

    std::vector<std::pair<TString,std::vector<DS>>> groups={
        {"24",      group(b24)   },
        {"25c1",    group(c1)    },
        {"24_25c1", group(b24c1) },
        {"25c234",  group(c234)  },
    };

    for (auto &gr : groups){
        TString tag=gr.first; auto &ents=gr.second;
        TString sub=OUT+"/"+tag; gSystem->mkdir(sub,kTRUE);
        TH2D *oT,*nT,*lT;
        TH2D *oE=combine(ents,"oldL0",tag+"_o",&oT);
        TH2D *nE=combine(ents,"newL0",tag+"_n",&nT);
        TH2D *lE=combine(ents,"Lc",   tag+"_l",&lT);
        printf("%-8s : old=%s new=%s Lc=%s  (%d datasets)\n",
               tag.Data(), oE?"ok":"--", nE?"ok":"--", lE?"ok":"--", (int)ents.size());
        draw_eff (oE,oT,sub,"eff_oldL0",tag+"o");
        draw_eff (nE,nT,sub,"eff_newL0",tag+"n");
        draw_eff (lE,lT,sub,"eff_Lc",   tag+"l");
        draw_diff(nE,oE,nT,oT,sub,"diff_newL0_minus_oldL0",tag+"dno", -1.5, +1.5);
        draw_diff(lE,nE,lT,nT,sub,"diff_Lc_minus_newL0",   tag+"dln", -10., +10.);
    }
    printf("done.\n");
}
