# BSDS500 Benchmark

The present directory contains a `jupyter notebook` with the statistics of a benchmark performed on a sample of the mentioned dataset.

The dataset has been selectively extracted and pre-processed, but only in terms of its structure, not its contents.

## Dataset Preprocessing

To obtain the dataset, obtain the `BSR_bsds500.tgz` file from [here](https://www2.eecs.berkeley.edu/Research/Projects/CS/vision/grouping/BSR/).

1) From the `extracted` dataset, move to the `BSDS500-Benchmark` directory only the `BSR/BSDS500/data/images` directory

2) Move all the `.jpg` files from the `train`, `test` and `val` directories into the `images` directory

```bash
cd ./train/ && mv *.jpg .. && cd ../test && mv *.jpg .. && cd ../val && mv *.jpg .. && cd .. && rm -r train && rm -r test && rm -r val
```

3) Apply the renaming `bash` script on the `images` directory

```bash
cd ..
bash rename_files.sh
```

---

## Jupyter Notebook Requirements

Afeter satisfying the `python` and `pip` requirements listed [before](../README.md#requirements):

1) Install all of the required `Python` dependencies

```bash
python -m pip install -r requirements.txt
```

2) Create a new `virtual environment` for the `benchmark`

```bash
python -m venv bsds500-benchmark
source bsds500-benchmark/bin/activate
```

3) Launch the `jupyter notebook`

```bash
jupyter-notebook BSDS500-Benchmark-Notebook.ipynb
```

And feel free to re-run the notebook on the downloaded data

---