#!/usr/bin/env python3
# sWeight-match the 24b8 (MagUp) calibration tuples and cache a slim threshold-region
# slice to /tmp. Method: u6_PIDCalib2/notebooks/sweight_calib_matching.ipynb.
#
#   new L0 = L0_2024_block8-MagUp-P   (4 pT trees)
#   Lc     = Lc_2024_block8-MagUp-P   (1 tree)
# branches p_P, p_ETA, p_PID_P, p_PID_K ; fiducial 9300 <= p_P <= 17700.
# Run:  cd ~/u6_PIDCalib2 && lb-conda pidcalib python3 <this>

import json
from pathlib import Path

import pandas as pd
import ROOT
from apd import AnalysisData

SAMPLES = "/home/lins/u6_PIDCalib2/src/pidcalib2/data/samples.json"
OUTDIR = Path("/data/lhcb/users/lins/u3_PIDQuantify/threshold")
OUTDIR.mkdir(parents=True, exist_ok=True)
BRANCHES = ["p_P", "p_ETA", "p_PID_P", "p_PID_K"]
PLO, PHI = 9300.0, 17700.0

TREES = {
    "L0_2024_block8-MagUp-P": ["L0ToPPi_LL_VeryHighPT", "L0ToPPi_LL_HighPT",
                               "L0ToPPi_LL_MidPT", "L0ToPPi_LL_LowPT"],
    "Lc_2024_block8-MagUp-P": ["LcToPKPi"],
}


def match_sweights(tree, tuple_file, sweight_file, branches, ordering_variables):
    cols = list(dict.fromkeys([*branches, *ordering_variables]))
    tup = pd.DataFrame(ROOT.RDataFrame(tree, tuple_file).AsNumpy(cols))
    tup = tup.sort_values(ordering_variables).reset_index(drop=True)
    sw = pd.DataFrame(ROOT.RDataFrame(tree, sweight_file).AsNumpy(["sweight", "order_index"]))
    sw = sw.sort_values("order_index").reset_index(drop=True)
    tup["sWeight"] = sw["sweight"]
    return tup


def cache_sample(key, out):
    info = json.load(open(SAMPLES))[key]
    ordering = info["ordering_variables"]
    sweight_dir = info["sweight_dir"]
    cf = info["calib_files"].copy()
    files = AnalysisData("pid", cf.pop("analysis"))(**cf)
    print(f"[{key}] {len(files)} calib files, trees={TREES[key]}", flush=True)

    pieces = []
    for i, tuple_file in enumerate(files):
        sweight_file = f"{sweight_dir}{Path(tuple_file).stem}_sweights.root"
        for t in TREES[key]:
            tree = f"{t}/DecayTree"
            df = match_sweights(tree, tuple_file, sweight_file, BRANCHES, ordering)
            df = df[(df.p_P >= PLO) & (df.p_P <= PHI)]
            pieces.append(df[[*BRANCHES, "sWeight"]])
        print(f"  file {i+1}/{len(files)} done, rows so far {sum(len(p) for p in pieces)}", flush=True)

    full = pd.concat(pieces, ignore_index=True)
    ROOT.RDF.FromNumpy({c: full[c].to_numpy() for c in full.columns}).Snapshot("DecayTree", str(out))
    print(f"[{key}] wrote {len(full)} rows -> {out}", flush=True)


cache_sample("L0_2024_block8-MagUp-P", OUTDIR / "L0.root")
cache_sample("Lc_2024_block8-MagUp-P", OUTDIR / "Lc.root")
print("DONE", flush=True)
