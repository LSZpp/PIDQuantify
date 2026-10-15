# PID pipeline

Run these interpreted ROOT macros from this directory, or use their absolute paths.
They launch the existing Python programs; the mass models and processing engines
remain in `u5_sw_fit` and `u6_PIDCalib2`.

Settings and repeated tools live in `U_utils.cc`; `U_utils.hh` contains declarations.
Each stage keeps its commands and loops in its own macro. ROOT supplies the usual
C++/ROOT headers, so these launchers do not need a compilation setup.

## Select a sample

```bash
root -l -b -q 'A_cache.C("Lambda0:25c1d:b")'
root -l -b -q 'B_histogramming.C("both:24b4p2,24b4p3")'
root -l -b -q 'J_effhists.C("LambdaC:24b4p2:l:b")'
```

- Particle: `Lambda0`, `LambdaC`, `both` (also `L0` and `Lc`).
- Datasets: `24b1`–`24b8`, `25c1d`, `25c1u`, `25c2`, `25c3`, `25c4u`,
  `25c4d`, `26c1d`, `26c1u`, `26c2d`, `26c2u`, `24b4p2`, `24b4p3`.
- Commas select several datasets. L0 always processes all four pT streams.
- `:b` submits to Condor; supported only by **A, F, J**.
- `:l` selects local sWeights in **J**. Original tuple reads still need grid access.
- A second argument, `true`, prints commands without writing outputs, querying
  APD, authenticating, or submitting jobs. F shows one job template per stream;
  its actual job count is resolved from APD when it runs.

There is no `24b4p1`: it is outside this UT-included calibration workflow.
**H rejects partitions, including mixed selections. J requires `:l` for partitions.**

## Ordinary LambdaC production

Replace `24b4` with the requested dataset. Run the stages separately; wait for
each batch stage to finish before starting a dependent stage.

```bash
cd /home/lins/u3_PIDQuantify/run
root -l -b -q 'P_proxy.C()'
root -l -b -q 'A_cache.C("LambdaC:24b4:b")'
# Wait for A.
root -l -b -q 'B_histogramming.C("LambdaC:24b4")'
root -l -b -q 'D_fit_data.C("LambdaC:24b4")'
root -l -b -q 'E_fit_yields.C("LambdaC:24b4")'
root -l -b -q 'F_assign.C("LambdaC:24b4:b")'
# Wait for F. LambdaC does not need G.
root -l -b -q 'H_xrdcp.C("LambdaC:24b4")'
root -l -b -q 'J_effhists.C("LambdaC:24b4:b")'
```

For Lambda0, replace the particle selector and run
`G_merge_sweights.C("Lambda0:24b4")` after F completes and before H or local J.
For both particles, select `both`; G automatically skips Lc.

## Block 4 partition pass, both particles

The partition windows are inclusive: p2 = 9832–9883; p3 = 9896–9910.
Both reuse their respective full `24b4` cache. Existing `block4_partition*`
outputs stay where they are; new outputs use `24b4p2` and `24b4p3`.

```bash
root -l -b -q 'P_proxy.C()'
root -l -b -q 'A_cache.C("both:24b4:b")'
# Wait for A. Omit A if these caches already exist.
root -l -b -q 'B_histogramming.C("both:24b4p2,24b4p3")'
root -l -b -q 'D_fit_data.C("both:24b4p2,24b4p3")'
root -l -b -q 'E_fit_yields.C("both:24b4p2,24b4p3")'
root -l -b -q 'F_assign.C("both:24b4p2,24b4p3:b")'
# Wait for F.
root -l -b -q 'G_merge_sweights.C("both:24b4p2,24b4p3")'
root -l -b -q 'J_effhists.C("both:24b4p2,24b4p3:l:b")'
```

Do not run H for these partitions. To process full Block 4 instead, use `24b4`;
that alias supports normal EOS publication.

## Simulation preparation

C retains the small-sample combined histogram-and-fit path and existing simulation
outputs. It is separate from the data sequence and does not copy fitted parameters
into data configs automatically.

```bash
root -l -b -q 'C_fit_simulation.C("both:2024,2025c234")'
```

A data alias also selects its corresponding simulation bucket. L0 2025 c1 uses
2024 simulation; Lc 2025 uses 2025c234 simulation.

## Outputs and execution material

The data roots remain `/data/lhcb/users/lins/u1_PID_L0/<alias>` and
`/data/lhcb/users/lins/u2_PID_Lc/<alias>`. Cache, histogram, shape-fit, and yield-fit
outputs use `c`, `h`, `f`, and `y`, with L0 pT subdirectories `vh`, `h`, `m`, `l`.
E writes its generated yield config inside `y`; F reads that config and its table.

Assignment numbers the sorted original file list from `001` (Python index zero):

```text
L0: <alias>/s/<pt>/001/<input-stem>_sweights.root
Lc: <alias>/s/001/<input-stem>_sweights.root
```

Each batch directory also contains `run.sh`, `submission.txt`, `E<Cluster>.txt`,
`O<Cluster>.txt`, and `L<Cluster>.txt`. Every submission has `queue 1`.
Resubmissions retain old cluster logs; the submit description and payload are
replaced. Local runs use `E.txt`, `O.txt`, and `L.txt` beside their artifacts;
these three files describe the latest local execution.

G merges all four L0 files into `s/c/001/`. H copies only the sWeight ROOT files
into the existing flat EOS dataset directory, never scripts or logs.

J with `:l` makes physical copies into `s/local_sweights/`, containing only ROOT
files. It refreshes that directory before starting the dimension jobs. Normal J
uses EOS. Histograms and logs are grouped by dataset:

```text
/data/lhcb/users/lins/u3_PIDQuantify/finals_hists/<2d|3d>/<newL0|Lc>/<alias>/
/data/lhcb/users/lins/u3_PIDQuantify/finals_hists_local/<2d|3d>/<newL0|Lc>/<alias>/
```

The reader accepts the new dataset directories and falls back to existing flat
histograms. Rebuild the PIDQuantify library before using the updated reader.
Pass the normal or local histogram root to the plotting source as appropriate.

## Resources and authentication

A requests 128GB per job and reads its CPU count from cache JSON `num_threads`
(currently 50 per L0 stream, 8 for Lc). F requests one CPU for L0 and two for Lc,
one original file per cluster, and leaves memory at the Condor default. J requests
one CPU and 8GB per dimension/grid job. Other stages run locally.

P requests a 167:59 proxy, strips the appended DIRACX block for worker-node VOMS
compatibility, validates it, and installs `run/proxy` with mode 0600. It is ignored
by Git. A/F/J validate credentials, environments, remote access, and submit
descriptions before submitting anything. They abort on preflight failure rather
than prompting for authentication inside a batch worker.

## Efficiency settings

J defaults to 2D and 3D DLL scans: four labels, -50 to 50 in steps of 0.5.
Block 4 and its partitions retain -20 to 30 in steps of 0.1. Edit J's short
`dimensions` and `grids` lists for other scans. Optional grids are `ProbNNLog`
(exp(-15 + 0.05*i), 301 points) and `ProbNNLinear` ((0.2*i)/100, 501 points),
each with the three existing ProbNN labels and ten-decimal threshold formatting.
They use separate grid subdirectories under the dataset directory.
