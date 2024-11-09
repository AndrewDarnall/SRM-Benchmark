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

# Algorithm in Action

### The Reference Image
![Reference-Image](../assets/images/reference-image.jpeg)


### Segmented Image
![Segmented-Image-C++](../assets/images/cpp-srm-output.jpeg)

---