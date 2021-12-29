![raytracer_banner](https://user-images.githubusercontent.com/42053774/147417284-32dd7185-d07b-4b95-8d41-e81429c4df5f.png)

# Simple raytracer
Simple ray tracing project in C to learn both C and explore algorithms and math for ray tracing.
## Subject
Algoritmos y Programacion 1 - 95.11 (FIUBA)
## Compiling
In order to compile the project gcc is used together with GNU Make.

```bash
make
```

**Note**: The flags used for the compilation are -Wall -Werror -std=c99 -pedantic -g -lm. It is important to mention that the flag -g is used only in the development phase of the project to debug it.

## Execution
Execution example. The program is capable to generate two different output image format, ppm and bmp.
```bash
make run_ppm
```
```bash
make run_bmp
```
**Note:** The example image resolution is VGA. Recursion depth is 10 and the output image format is bmp. All of these parameters could be changed from the Makefile.

```Makefile
PROGRAM_IMG_DIMENSIONS = 640 480
RECURSION_DEPTH = 5
PROGRAM_OUTPUT_IMAGE_PPM = foo.ppm
PROGRAM_OUTPUT_IMAGE_BMP = bar.bmp
```

## Contact me
guerodriguez@fi.uba.ar
<br/><br/>Saludos, Guido 😉.
