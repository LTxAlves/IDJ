# Trabalho 1 - Introdução ao Desenvolvimeto de Jogos

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

For this project to run, you will need the following:

```
g++ 4.7 or superior
SDL2
SDL2_image
SDL2_mixer
SDL2_ttf
```

### Installing

#### Installing prerequisites in a Linux based OS (using terminal):

* g++:
    ```
    sudo apt-get install build-essencial
    ```

* SDL2:
    ```
    sudo apt-get install libsdl2-devlibsdl2-image-dev libsdl2-mixer-dev libsdl-ttf
    ```

#### Installing prerequisites in a Windows based OS:

* Firstly, a terminal-like program is needed.
    * TDM-GCC is recommended: 
    [TDM-GCC](http://tdm-gcc.tdragon.net/download)
        * while installing, add it to PATH
        * TDM-GCC comes with C and C++ compilers

* SDL2 and its packages:
    * Download SDL2-devel-2.x.x-mingw.tar.gz (or SDL2-devel-2.x.x-VC.zip if you use Visual Code) from the [link](http://libsdl.org/download-2.0.php)
    * Extract the downloaded file and copy the folders
    ```
    bin
    include
    lib
    ```
    to
    ```
    C:\SDL-2.x.x
    ```
* SDL2 image, mixer and ttf packages:

    * use the links:
        * [SDL_image](http://www.libsdl.org/projects/SDL_image/)
        * [SDL_mixer](http://www.libsdl.org/projects/SDL_mixer/)
        * [SDL_ttf](http://www.libsdl.org/projects/SDL_ttf/)

    * from these pages, dowload the files with names ending with [...]-devel-2.x.x-mingw.zip
    * as with SDL2, extract each file and move the folders

    ```
    bin
    include
    lib
    ```
    to
    ```
    C:\SDL-2.x.x
    ```
    * merging with previously included folders
    * open the "lib" directory and copy all DLL files to
    ```
    C:\SDL-2.x.x\bin
    ```
    * copy these DLL files to the .exe file location

## Running the code

Just open the installation directory with MinGW and run
```
make
```

## Built with
* [SDL2](https://wiki.libsdl.org/)

## Author
* **Leonardo Alves** - *16/0012007* - [LTxAlves](https://github.com/LTxAlves/IDJ)

## Acknowledgemets
* Billie Thompson's README template - found [here](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2#file-readme-template-md)
