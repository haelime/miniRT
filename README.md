# miniRT

A simple ray tracer implemented in C using MiniLibX. This project simulates light rays to render 3D scenes with basic geometric objects, featuring Phong reflection model and camera controls.

[Portfolio walkthrough (Korean)](https://haelime.github.io/posts/minirt/)

## Code entry points

- [Scene.c](srcs/Control/Scene.c): camera rays, closest-hit selection and recursive reflection
- [Ray.c](srcs/Graphics/Ray.c): object intersection and blending local shading with reflected color
- [Phong.c](srcs/Graphics/Phong.c): per-light diffuse, specular and shadow calculations
- [Matrix.c](srcs/Graphics/Matrix.c): SIMD matrix operations used for coordinate transforms
- [Parse.c](srcs/Parse/Parse.c): loading the `.rt` scene description

# Features
- **Supported Objects**:
  - Sphere
  - Plane
  - Cylinder
  - Circle
  - Triangle
- **Lighting**:
  - Ambient lighting
  - Diffuse and Specular reflection (Phong model)
  - Shadows
- **Camera**:
  - Real-time movement and rotation
- **File Parsing**:
  - Custom `.rt` scene file format

# Getting Started

### Prerequisites
- x86-64 macOS with AVX2 support: the current Makefile uses `-mavx2` and links the OpenGL and AppKit frameworks.
- GCC or Clang
- MiniLibX dependencies (OpenGL, AppKit on macOS)

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/haelime/miniRT.git
   cd miniRT
   ```
2. Build the project:
   ```bash
   make
   ```

### Usage
Run the program with a scene file:
```bash
./miniRT scenes/sample.rt
```

# Controls
| Key | Action |
| --- | --- |
| `W`, `S` | Move Forward / Backward |
| `A`, `D` | Move Left / Right |
| `Space`, `Shift` | Move Up / Down |
| `↑`, `↓`, `←`, `→` | Rotate Camera (X, Y axis) |
| `Q`, `E` | Rotate Camera (Z axis) |
| `R` | Toggle Debug Mode |
| `ESC` | Exit |

# Scene File Format
The `.rt` files define the scene using the following elements:
- `A` (Ambient): `ratio [0.0,1.0]`, `color [R,G,B]`
- `C` (Camera): `pos [x,y,z]`, `orientation [x,y,z]`, `FOV [0,180]`
- `L` (Light): `pos [x,y,z]`, `brightness [0.0,1.0]`, `color [R,G,B]`
- `sp` (Sphere): `center [x,y,z]`, `diameter`, `color [R,G,B]`
- `pl` (Plane): `point [x,y,z]`, `normal [x,y,z]`, `color [R,G,B]`
- `cy` (Cylinder): `center [x,y,z]`, `axis [x,y,z]`, `diameter`, `height`, `color [R,G,B]`

# Preview
https://github.com/haelime/miniRT/assets/44316628/79bc9f9b-31ef-4c7c-b86b-896cfc80f11e

![image](https://github.com/haelime/miniRT/assets/44316628/7534170c-7e96-4fe6-9670-e4bfe3f3a04b)

# SIMD profiling

The standalone benchmark compares scalar math with the SSE/AVX2 functions used
by miniRT. It checks result equivalence before measuring dot products,
matrix-vector transforms, and matrix concatenation.

```bash
make profile PROFILE_ITERATIONS=5000000
```

The CSV output reports elapsed time, nanoseconds per call, throughput, and
speedup. `math_flops_per_call` is identical between scalar and SIMD rows because
SIMD packs the same arithmetic into wider instructions rather than changing the
algorithmic operation count.
