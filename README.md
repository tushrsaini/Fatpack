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

The solution consists of four projects:  

- ``Fatpack``  
  - The console application ``Fatpack.exe``, which the user employs to pack their target executable.  
  
- Loader stubs  
  - The loader stubs serve as containers for the packed target executable and are responsible for loading and executing it.  
  - ``Loader_Console``  
  - ``Loader_Windows``  
  
- ``ResourceAdder``
  - ``ResourceAdder.exe``, a helper executable that adds the loader stubs to ``Fatpack.exe`` as post-build step, using the scripts ``PostBuildStep_Debug.bat`` and ``PostBuildStep_Release.bat``.

### Loader Stubs  

Both ``Loader_Console`` and ``Loader_Windows`` serve as loader stubs. Upon startup, they retrieve the packed target executable from their embedded resources, unpack it in memory, and execute it.  
The loader logic is available at: https://github.com/Fatmike-GH/PELoader  

- ``Loader_Console``: The loader stub for loading console applications.  
- ``Loader_Windows``: The loader stub for loading windows applications.  

### ResourceAdder  

A simple console application used to embed the loader stubs into ``Fatpack.exe`` as post-build step. This integration is handled via the scripts ``PostBuildStep_Debug.bat`` and ``PostBuildStep_Release.bat``.  

>**Note:** Always use **"Rebuild Solution"** after making changes to ensure that the post-build steps execute correctly.  

### Fatpack

The console application (``Fatpack.exe``) is used by the user to package their target executable. Its main responsibilities include:  

- Determining the appropriate loader stub (Loader_Console or Loader_Windows) based on the type of the target executable, loading it from an embedded resource, and saving it to disk.  
- Extracting the icon from the target executable and embedding it into the selected loader stub.  
- Extracting and embedding the application manifest from the target executable. This step is essential, as the manifest may specify specific module versions required for correct execution.  
- Compressing the target executable using the LZMA algorithm and appending it to the loader stub.  

>**Note:** Rebasing of the loader stub is not yet implemented. If the target executable lacks a relocation table, the loader stub may fail to function properly. This is due to a potential conflict between the image base addresses of the loader stub and the target executable.  

![image](Images/Concept.PNG)

## Fatpack vs UPX  

| Target size 	| UPX     	| UPX -9  	| Fatpack 	|
|-------------	|---------	|---------	|---------	|
| 6744 kb     	| 1735 kb 	| 1669 kb 	| **1608 kb** 	|
| 2728 kb     	| 1052 kb 	| **1034 kb** 	| 1035 kb 	|
| 611 kb      	| 86 kb   	| 83 kb   	| **80 kb**   	|
| 533 kb      	| 213 kb  	| 210 kb  	| **199 kb**  	|
| 448 kb      	| -       	| -       	| **193 kb**  	|
| 233 kb      	| 89 kb   	| 89 kb   	| **85 kb**   	|
| 32 kb       	| **9 kb**    	| **9 kb**    	| 16 kb   	|
| 20 kb       	| **11 kb**   	| **11 kb**   	| 18 kb   	|
| 15 kb       	| **10 kb**  	| **10 kb**   	| 17 kb   	|  

Since the loader stubs (``Loader_Console`` and ``Loader_Windows``) are relatively large,approximately 10 KB each, the compression ratio is less favorable when packing very small target executables. However, for larger executables, the results are significantly more efficient, yielding much better overall compression ratios.

## Third Party Software  

### EasyLZMA  

https://github.com/lloyd/easylzma  

### TinyZZZ  

https://github.com/WangXuan95/TinyZZZ  

### Fatmike's PE Loader  

https://github.com/Fatmike-GH/PELoader



