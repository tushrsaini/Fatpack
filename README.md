# Fatpack  

A Windows PE packer (x64) with LZMA compression and with full TLS (Thread Local Storage) support.  

Keywords: PE packer, PE loader, manual mapping, manual mapper, portable executable, LZMA, UPX, EXE

## Motivation

A practical application of my PE loader: https://github.com/Fatmike-GH/PELoader  

## Usage

``Fatpack.exe inputfile.exe outputfile.exe``  

## Features

### Functional Features  

- Support for native Console- and Windows executables (x64 only, no .NET support)  
- LZMA compression  
- Full TLS (Thread Local Storage) support  
  - Therefore supports Rust- and Delphi exectuables for example  
- No CRT usage in Fatpack.exe and Stubs (WinAPI only) and therefore no C/C++ redistributables are required  
- Icon extraction
- Manifest extraction (required if specfic module versions of the target executable are specified)

### Technical Features  

- Relocations
- Imports
- Delay Imports
- Exception Handlers
- Proper Memory Section Protection
- Full TLS (Thread Local Storage) support
  - TLS Callbacks
    - DLL_PROCESS_ATTACH  
    - DLL_THREAD_ATTACH  
    - DLL_THREAD_DETACH  
    - DLL_PROCESS_DETACH  
  - TLS Data

## Solution Overview

To do

## Third Party Software  

### EasyLZMA  

https://github.com/lloyd/easylzma  

### TinyZZZ  

https://github.com/WangXuan95/TinyZZZ  

### Fatmike's PE Loader  

https://github.com/Fatmike-GH/PELoader



