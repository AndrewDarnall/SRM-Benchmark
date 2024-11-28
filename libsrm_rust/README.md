# Rust Implementation

The Rust implementation is derived from the C++ version, with Rust selected for its strong guarantees regarding memory safety and other inherent advantages, such as zero-cost abstractions.

Although the OpenCV bindings for Rust are not as widely supported as those for Python, they still provide a familiar interface and functionality consistent with the OpenCV experience in other programming languages.

---

# Usage

1. Change into the build directory

```bash
cd ~/SRM-Benchmark/libsrm_rust/
```

2. Use `cargo` to `build` the project

```bash
cargo build
```

3. Use `cargo` to `run` the project

```bash
cargo run ./imgs/Sample-Image.jpeg 32 15 0.001
```

And the program will output the `Segmented-Sample-Image.jpeg`

---

# Performance

The `runtime` of the algorithm on the reference image is:

- Synthetic Runtime

```bash
3.65user 0.52system 0:03.28elapsed 127%CPU (0avgtext+0avgdata 123676maxresident)k
0inputs+616outputs (0major+16126minor)pagefaults 0swaps
```

- Verbose Runtime

```bash
Command being timed: "cargo run ./imgs/Sample-Image.jpeg 32 15 0.001"
User time (seconds): 3.80
System time (seconds): 0.46
Percent of CPU this job got: 126%
Elapsed (wall clock) time (h:mm:ss or m:ss): 0:03.38
Average shared text size (kbytes): 0
Average unshared data size (kbytes): 0
Average stack size (kbytes): 0
Average total size (kbytes): 0
Maximum resident set size (kbytes): 127440
Average resident set size (kbytes): 0
Major (requiring I/O) page faults: 0
Minor (reclaiming a frame) page faults: 29388
Voluntary context switches: 17
Involuntary context switches: 467
Swaps: 0
File system inputs: 0
File system outputs: 616
Socket messages sent: 0
Socket messages received: 0
Signals delivered: 0
Page size (bytes): 4096
Exit status: 0
```

---

# Algorithm in Action

#### The Reference Image

![Reference Image](../assets/images/reference-image.jpeg)

#### Segmented Image

![Rust Segmented Image](../assets/images/rust-srm-output.jpeg)

---
