# Statistical Region Merging Benchmark

The following reposiroty contains a benchmark which compares different implementations of the [Statistical Region Merging](https://ieeexplore.ieee.org/document/1335450) algorithm.
<
<br>
<br>
Given that many image processing and computer vision algorithms are frequently utilized in their 'Pythonic' form, which introduces a notable performance overhead, implementing the algorithm in a highly efficient and fast programming language like `C++` was an obvious choice. However, considering the well-known challenges associated with memory management in `C++`, implementing the algorithm in the `Rust` programming language presents a compelling alternative, as it offers both high performance and strong memory safety guarantees.
<br>
<br>
The implementations are benchmarked against the [Berkely Image Segmentation Dataset 500 (BSDS500)](https://www.kaggle.com/datasets/balraj98/berkeley-segmentation-dataset-500-bsds500), a widely used dataset for image segmentation (even if for Deep Learning and Computer Vision models),
and then I measure the resource consumption of each implementation.

---

## Requirements

| Component | Version |
|-----------|---------|
| OpenCV    | `4.5.1` |
| C++       | `10.2.1`|
| Rust      | `1.81.0`|
| Python    | `3.12.4`|
| pip       | `24.2`  |
| CMake     | `3.18.4`|
| Make      | `4.3`   |

---

## Project Structure

---

## Usage

---