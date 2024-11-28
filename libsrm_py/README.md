# Python Implementation

The implementation, just like all others is based on the [original paper](https://ieeexplore.ieee.org/document/1335450).
<br>

---

# Setup

1) Create the `virtual environment` to avoid clashes with the previously installed `libopencv-dev` used by other programming languages

```bash
python -m venv computer-vision
```

2) Download all the dependencies

```bash
python -m pip install -r requirements.txt
```

# Execution

To use run the algorithm on a test image:

```bash
python srm.py ./imgs/Sample-Image.jpeg 32 15 0.001
```

And the program will output, within the same directory, a file `Segmented_Sample-Image.jpeg`

---

# Performance


The `runtime` for the algorithm on the reference image is:

- Synthetic runtime

```bash
22.61user 0.17system 0:22.81elapsed 99%CPU (0avgtext+0avgdata 489488maxresident)k
10168inputs+416outputs (64major+108791minor)pagefaults 0swaps
```

- Verbose runtime

```bash
Command being timed: "python srm.py ./imgs/Sample-Image.jpeg 32 15 0.001"
User time (seconds): 23.40
System time (seconds): 0.16
Percent of CPU this job got: 99%
Elapsed (wall clock) time (h:mm:ss or m:ss): 0:23.60
Average shared text size (kbytes): 0
Average unshared data size (kbytes): 0
Average stack size (kbytes): 0
Average total size (kbytes): 0
Maximum resident set size (kbytes): 489416
Average resident set size (kbytes): 0
Major (requiring I/O) page faults: 0
Minor (reclaiming a frame) page faults: 110894
Voluntary context switches: 5
Involuntary context switches: 1267
Swaps: 0
File system inputs: 0
File system outputs: 416
Socket messages sent: 0
Socket messages received: 0
Signals delivered: 0
Page size (bytes): 4096
Exit status: 0
```

---

# Algorithm in Action

### Reference Image
![Reference Image](../assets/images/reference-image.jpeg)

### Segmented Image
![Python Segmented Image](../assets/images/python-srm-output.jpeg)

---
