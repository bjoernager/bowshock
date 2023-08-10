![BOWSHOCK](https://mandelbrot.dk/logo/bowshock.svg)

# CHANGELOG

Read: `CHANGELOG.md`

# COMPILATION

Bowshock uses CMake as its build system. The standard option `CMAKE_BUILD_TYPE` may be set to either `Release` or `Debug`, depending on the build type.

The main program is written in C++20, and a conforming compiler is therefore required. OpenGL 3.2 is used for rendering, and the shaders are therefore written in GLSL 1.5.

Before compilation, an appropriate *GLAD* loader must be downloaded from a web instance. I use the one on `dav1d.de`, with the following settings:

<https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.2&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on>

The script `extractGlad.sh` will extract `glad.zip` (or any other archive – if specified) to `glad`. It also copies a CMake lists file to the directory.

```
./extractGlad.sh <archive>
```

Before running – however – the data directory must be installed. This can be done via the installation script `install.sh`:

```
./install.sh data [data directory]
```

# DEVELOPMENT

To initialise the environment, I use the following commands:

```
rm -fr build && \
rm -fr bindir && \
rm -fr datdir && \
./extractGlad.sh && \
cmake -Bbuild -DBOW_DATA_DIRECTORY="${PWD}/datdir" -DCMAKE_BUILD_TYPE=Debug . && \
./install.sh data "${PWD}/datdir"
```

… and from there just use the following to build the project:

```
clear && \
./validateShaders.py && \
cmake --build build && \
build/bowshock/bowshock --skip
```

## SHADER VALIDATION

The shaders at bowshock/shader may be validated using the Python script `validateShaders.py`. If the shaders contain errors, and these are not fixed before installation, the program will fail to compile them during run‐time.

# INSTALLATION

The script `install.sh` will install the executable, the assets, the shaders, etc. to the specified directories:

```
./install.sh [build directory] [binary directory] [data directory]
```

# MIRRORS

mandelbrot.dk (main): <https://mandelbrot.dk/bowshock>

GitLab: <https://gitlab.com/bjoernager/bowshock.git>

GitHub: <https://github.com/bjoernager/bowshock.git>

# CREDITS

Read: `CREDITS.txt`
