# 0.C.0

*0.C.0-12*

* Update readme
* Improve commenting

*0.C.0-11*

* Fix readme

*0.C.0-10*

* Update readme
* Add dependencies subsection to readme
* Add function for logging

*0.C.0-F*

* Fix and update readme
* Update and fix installation script
* Put version number in readme

*0.C.0-E*

* Update readme
* Add function for getting the hull mass of a ship type
* Update commenting
* Don't define object-kind type types inside their appropriate class
* Rename ware_mass to ware_density
* Add ship type 'canis'

*0.C.0-D*

* Update readme

*0.C.0-C*

* Update readme (add logo)

*0.C.0-B*

* Update readme
* Update changelog style

*0.C.0-A*

* Update readme (eg. use non-ASCII characters)

*0.C.0-9*

* Fix CMake not complaining about data directory not being specified
* Find packages in CMake
* Update exception specifiers
* Add terminal parameter for specifying the port number
* Update help screen
* Rename terminal paramaeter 'name' to 'save'
* Add server configuration structure
* Clean up code
* Improve commenting
* Update ware list
* Add linked-list class for object roots
* Fix gravitate in the case of overlaping objects
* Add our own terminate functions for unrecoverable errors
* Improve error handling
* Add new header for network formats
* Fix save path
* Make readme Markdown
* Make changelog Markdown
* Rename home_directory to base_directory

*0.C.0-8*

* Fix shader validation script
* Fix shader

*0.C.0-7*

* Update readme
* Split program into client-side and server-side
* Use inheritance for objects (instead of using unions) and rework them
* Rework application structure
* Remove 'random' facilities
* Improve commenting
* Update and fix quotes
* Use OpenGL 3.2
* Allow sixteen characters in commander names (was 14).
* Update save format (bump format version)
* Update default name: Caelum => Corneille
* Create app-specific directory (save files in a subdirectory here)
* Rework save path setting
* Rework terminal parameters
* Update help print
* Add copyright symbol to startup notice
* Bump version specified in CMake

*0.C.0-6*

* Check I/O results
* Fix credits print
* Add structure for wares
* Disable language extensions
* Don't overwrite save by default
* Load save file before start sequence
* Fix quotes
* Fix logs
* Fix save loader

*0.C.0-5*

* Update readme
* Fix version constant

*0.C.0-4*

* Drop zp in favour of the standard library
* Drop ly in favour of the standard library
* Update code style
* Update naming convention
* Use libfmt
* Remove abort function
* Add background to main logo
* Update readme
* Print shader errors at run-time
* Update help screen
* Fix objects not being deleted

*0.C.0-3*

* Enable more warnings

*0.C.0-2*

* Enforce new naming convention
* Use fixed-width floating-point types
* Update shader validation script
* Rename bs module to bas
* Register SIGTERM handler
* Make cmpshd static
* Rename crd to prcrd

*0.C.0-1*

* Update naming convention
* Use trailing return types
* Use C++20
* Don't use minimum-width types
* Update some typings
* Rename intro to start sequence

*0.C.0-0*

* Migrate from Zap to zp
* Migrate from Flux to ly
* Tag development versions
* Use minimum-width types

# 0.B.2

* Fix data directory not being set correctly by CMake

# 0.B.1

* Fortify sources
* Use Flux more

# 0.B.0

* Use generator expressions in CMake
* Use OpenGL 4.1
* Migrate to C++
* Implement main program as a class
* Use exceptions
* Use references
* Update readme
* Add more quotes
* Fix launch options not being listed on the help print

# 0.A.0

* Remove satellite object type
* Fix viewport size being too small on some devices
* Update mass unit
* Add macros for branch prediction
* Add new modules 'init' and 'run'
* Remove module 'gfx'
* Add more ship types
* Use OpenGL 4.0
* Use GLAD
* Specify OpenGL profile
* Update code style
* Update gitignore
* Update naming convention
* Add more station types
* Create script for validating shaders
* Add install script
* Add script for extracting glad
* Add launch option 'credits'
* Make code more modular
* Add readme
* Update credits
* Switch back to CMake
* Add minimal MSVC support
* Specify underlying type for enumerations
* Add more quotes
* Rename launch option 'restart' to 'new'
* Add assumption macro
* Improve precision of gravitational constant

# 0.9.0

* Fix compilation warning
* Optimise mechanical functions
* Add system generation routine
* Remove 'info' module
* Add intro
* Add terminal parameters
* Update units
* Make window fullscreen
* Resume time
* Update gitignore
* Make code more modular

# 0.8.1

* Update renderer
* Add canister to simulation
* Update mechanical functions

# 0.8.0

* Make code more modular
* Don't use global variables
* Add more launch options
* Fix memory leak
* Add abort routine
* Add copyright notices to source files
* Add patch version to version number
* Enable more warnings
* Draw simulation in window

# 0.7

* Make window fullscreen
* Update object data (store both positional and rotational velocity)
* Update save format
* Add credits file
* Add more quotes
* Standardise and optimise save format
* Perform checks on save file
* Fix bad module name
* Use 'pragma once'
* (Temporarily) define some constants as macros instead of as compile-time variables
* Create object system

# 0.6

* Update versioning: Use major.minor
* Update save format
* Fix invalid symbol
* Add quotes
* Save simulation result to image

# 5

* Update save data format
* Add continue routine
* Read command line parameters
* Set SIGINT handler
* Print quote on start
* Add log function for errors
* Update flux usage
* Optimise grav

# 4

* Add simple save routine
* Add logo
* Add clean and purge targets to makefile

# 3

* Fix incorrect symbol names
* Add basic graphics instancing

# 2

* Rename project to Bowshock (from Procyon)
* Rewrite project
* Add gravity engine

# 1

* Move save handlers into their own module 'sav'
* Add new module 'evt'
* Move shipnm into new module 'info'
* Update save format
* Add jump function
* Rename ship to shipid
* Add ship structure
* Store ship information in player data
* Add function for getting the length to a system
* Add function for determining the jump range of a ship
* Add desktop entry

# 0

* Initial
