#include "Console\Console.h"
#include "CommandLine\CommandLine.h"
#include "PEFile\PEFile.h"
#include "..\Shared\BinaryFileReader\BinaryFileReader.h"
#include "BinaryFileWriter\BinaryFileWriter.h"
#include "IconExtractor\IconExtractor.h"
#include "ManifestExtractor\ManifestExtractor.h"
#include "..\Shared\ResourceLoader\ResourceLoader.h"
#include "Compessor\Compressor.h"

int main()
{
  Console::Console console;
  CommandLine::CommandLine commandLine;

  auto args = commandLine.GetCommandLine();

  int argc = 0;
  auto argv = commandLine.CommandLineToArgv(args, argc);
  if (argc != 3)
  {
    console.WriteLine(L"\n..::[Fatmike 2025]::..\n");
    console.WriteLine(L"Version: Fatpack v1.0.0");
    console.WriteLine(L"Usage:\t fatpack.exe inputfile.exe outputfile.exe");
    return 0;
  }

  LPWSTR inputFile = argv[1];
  LPWSTR outputFile = argv[2];

  if (wcscmp(inputFile, outputFile) == 0)
  {
    console.WriteLine(L"inputfile may not be the same as outputfile");
    return 0;
  }

  // Read input file
  BinaryFileReader::BinaryFileReader binaryFileReader(inputFile);
  if (binaryFileReader.GetBufferSize() == 0 || binaryFileReader.GetBuffer() == nullptr)
  {
    console.WriteLine(L"Failed to read inputfile.");
    return 0;
  }

  PEFile::PEFile inputPEFile;
  inputPEFile.LoadFromBuffer(binaryFileReader.GetBuffer(), binaryFileReader.GetBufferSize());
  
  // Load PE Loader from resource (PE Loader is added as resource in postbuild event of ResourceAdder)
  DWORD resourceSize = 0;
  ResourceLoader::ResourceLoader resourceLoader;
  BYTE* resourceData = nullptr;
  if (inputPEFile.IsConsole())
  {
    console.WriteLine(L"Using console loader stub.");
    resourceData = resourceLoader.LoadResource(MAKEINTRESOURCE(1000), RT_RCDATA, resourceSize); // 1000 : Loader_Console
  }
  else
  {
    console.WriteLine(L"Using windows loader stub.");
    resourceData = resourceLoader.LoadResource(MAKEINTRESOURCE(1001), RT_RCDATA, resourceSize); // 1001 : Loader_Windows
  }
  
  if (resourceData == nullptr || resourceSize == 0)
  {
    console.WriteLine(L"Failed to load loader stub.");
    return 0;
  }
  
  // Write loader from resource to disk (Loader is added as resource in postbuild event of ResourceAdder)
  BinaryFileWriter::BinaryFileWriter binaryFileWriter;
  if (!binaryFileWriter.WriteFile(outputFile, resourceData, resourceSize))
  {
    console.WriteLine(L"Failed save loader stub to disk.");
    return 0;
  }

  // Extract icon from inputFile if available and add it to outputFile
  IconExtractor::IconExtractor iconExtractor;
  iconExtractor.ExtractAndSetIconWithCustomIds(inputFile, outputFile);

  // Extract manifest from inputFile if available and add it to outputFile
  // This is required cause the manifest can contain important data for loading the pe file.
  // For example a specific version of a dll to be loaded (Example: Version 6.0.0.0 of comctl32.dll since TaskDialogIndirect is only avaliable in this version)
  ManifestExtractor::ManifestExtractor manifestExtractor;
  if (manifestExtractor.ExtractManifestResources(inputFile))
  {
    console.WriteLine(L"Manifest found. Adding manifest...");
    if (!manifestExtractor.AddManifestResourcesToTarget(outputFile))
    {
      console.WriteLine(L"Adding manifest failed.");
    }
    else
    {
      console.WriteLine(L"Manifest added.");
    }
  }
  
  // Compress input file
  BYTE* compressed = nullptr;
  size_t compressedSize = 0;
  Compressor::Compressor compressor;  
  compressor.Compress(inputPEFile.GetBuffer(), inputPEFile.GetBufferSize(), &compressed, &compressedSize);

  // Add packet target (inputFile) as resource to loader (ouputfile)
  HANDLE updateHandle = BeginUpdateResourceW(outputFile, FALSE);
  UpdateResource(updateHandle, RT_RCDATA, L"PACKED", MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), compressed, (DWORD)compressedSize);
  EndUpdateResource(updateHandle, FALSE);
  free(compressed);

  return 0;
}
