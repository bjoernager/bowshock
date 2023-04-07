BOWSHOCK

# CHANGELOG

Read: "CHANGELOG.txt"

# COMPILATION

Bowshock uses CMake as its build system. The standard option CMAKE_-
BUILD_TYPE may be set to either "Release" or "Debug", depending on the 
build type.

The program is written in C2x, and a conforming compiler is therefore 
required. It has been tested to work with GCC 12.2 and Clang 15.0, but 
the option BOW_C2X_COMPATIBILITY may have to be set to "true" when 
invoking CMake.

Before compilation, an appropriate GLAD loader must be downloaded from 
a web instance. I use the one on dav1d.de, with the following settings:

<https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D4.0&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on>

The script "extractGlad.sh" will extract "glad.zip" (or any other ar-
chive - if specified) to "glad". It also copies a CMAKE lists file to 
the directory, and CMake will automatically include this and build  
GLAD.

Before running - however - the data directory must be installed. This 
can be done via the installation script "install.sh":

./install.sh data [data directory]

## DEVELOPMENT

The commands I use for development are:

clear && \
rm -fr build && \
rm -fr bindir && \
rm -fr datdir && \
./validateShaders.py && \
./extractGlad.sh && \
cmake -Bbuild -DBOW_DATA_DIRECTORY="${PWD}/datdir" -DCMAKE_BUILD_TYPE=Debug . && \
cmake --build build && \
./install.sh data "${PWD}/datdir" && \
build/bowshock/bowshock --skip

## SHADER VALIDATION

The shaders at bowshock/shader may be validated using the Python-
script "validateShaders.py". If the shaders contain errors, and these 
are not fixed before installation, the program will fail to compile 
them during run-time, but the errors will not be diagnosed.

## INSTALLATION

The script "install.sh" will install the executable, the assets, the 
shaders... to the specified directories:

./install.sh [build directory] [binary directory] [data directory]

# CREDITS

Read: "CREDITS.txt"
