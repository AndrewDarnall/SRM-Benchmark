# C++ Implementation

The implementation is based on the `Python` implementation as it is the simplest way to implement the algorithm,
even when compared with the official `ImageJ` [implementation](https://wsr.imagej.net/plugins/SRM_.java) or
compared to the `Java Applet` made by the creators of the algorithm, [here](https://www.lix.polytechnique.fr/~nielsen/Srmjava.java)

---

# Usage

1) Change into the build directory

```bash
cd ~/SRM-Benchmark/libsrm_cpp/build
```

2) Run `CMake` to create the appropriate `Makefile`

```bash
cmake ..
```

3) Build the project's executable with `Make`

```bash
make
```

4) Run on a sample image

```bash
./Executables/main_exec ../imgs/Sample-Image.jpeg 32 15 0.001
```

And the program will output a `Segmented-Sample-Image.jpeg`

---

# Performance

The `runtime` for the algorithm on the reference image is:

- Synthetic Runtime

```bash
30.46user 0.53system 0:30.10elapsed 102%CPU (0avgtext+0avgdata 113224maxresident)k
0inputs+408outputs (1major+25287minor)pagefaults 0swaps
```

- Verbose Runtime

```bash
Command being timed: "./Executables/main_exec ../imgs/Sample-Image.jpeg 32 15 0.001"
User time (seconds): 29.60
System time (seconds): 0.49
Percent of CPU this job got: 102%
Elapsed (wall clock) time (h:mm:ss or m:ss): 0:29.24
Average shared text size (kbytes): 0
Average unshared data size (kbytes): 0
Average stack size (kbytes): 0
Average total size (kbytes): 0
Maximum resident set size (kbytes): 113316
Average resident set size (kbytes): 0
Major (requiring I/O) page faults: 452
Minor (reclaiming a frame) page faults: 26579
Voluntary context switches: 363
Involuntary context switches: 316
Swaps: 0
File system inputs: 82408
File system outputs: 408
Socket messages sent: 0
Socket messages received: 0
Signals delivered: 0
Page size (bytes): 4096
Exit status: 0
```

# Algorithm in Action

### The Reference Image
![Reference-Image](../assets/images/reference-image.jpeg)


### Segmented Image
![Segmented-Image-C++](../assets/images/cpp-srm-output.jpeg)

---
