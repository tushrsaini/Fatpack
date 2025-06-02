#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "..\Shared\BinaryFileReader\BinaryFileReader.h"

int wmain(int argc, wchar_t* argv[])
{
  if (argc != 4)
  {
    std::cout << "Usage: ResourceAdder resourcefile targetfile.exe resource id" << std::endl;
    return 0;
  }

  std::wstring resourceFile(argv[1]);
  std::wstring targetFile(argv[2]);
  std::wstring resourceId(argv[3]);

  WORD resourceIdValue = static_cast<WORD>(std::stoi(resourceId));

  // Read resourceFile
  BinaryFileReader::BinaryFileReader binaryFileReader(resourceFile.c_str());
  if (binaryFileReader.GetBuffer() == nullptr || binaryFileReader.GetBufferSize() == 0) return 0;

  // Add resourceFile as resource to targetFile
  HANDLE updateHandle = BeginUpdateResourceW(targetFile.c_str(), FALSE);
  UpdateResource(updateHandle, RT_RCDATA, MAKEINTRESOURCE(resourceIdValue), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), binaryFileReader.GetBuffer(), binaryFileReader.GetBufferSize());
  EndUpdateResource(updateHandle, FALSE);

  return 0;
}
