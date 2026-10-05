#!/usr/bin/env python3
"""Create the small APD manifest consumed by build_sweighted_probnn_hists.cc.

The APD lookup is intentionally isolated here: the expensive part of the
study is opening the ROOT files, which is handled by the compiled worker.
"""

import argparse
import json
from pathlib import Path

from apd import AnalysisData


SAMPLES_FILE = Path("/home/lins/u6_PIDCalib2/src/pidcalib2/data/samples.json")
SAMPLE_KEYS = ("2025_c4_v0-MagUp-P_Lc", "2025_c4_v0-MagUp-K", "2025_c4_v0-MagUp-Pi")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    samples = json.loads(SAMPLES_FILE.read_text())
    rows = []
    for key in SAMPLE_KEYS:
        config = samples[key]
        particle = key.rsplit("-", 1)[1]
        calib_files = config["calib_files"]
        files = AnalysisData("pid", calib_files["analysis"])(
            polarity=calib_files["polarity"],
            eventtype=calib_files["eventtype"],
            datatype=calib_files["datatype"],
            name=calib_files["name"],
            version=calib_files["version"],
        )
        for tuple_file in sorted(files):
            stem = Path(tuple_file).stem
            sweight_file = f"{config['sweight_dir']}{stem}_sweights.root"
            rows.append((particle, tuple_file, sweight_file))

    args.output.parent.mkdir(parents=True, exist_ok=True)
    with args.output.open("w") as output:
        output.write("# particle\ttuple_file\tsweight_file\n")
        for row in rows:
            output.write("\t".join(row) + "\n")
    print(f"Wrote {len(rows)} APD records to {args.output}")


if __name__ == "__main__":
    main()
