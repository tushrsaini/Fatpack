#pragma once
#include <Windows.h>

namespace BinaryFileWriter
{
  class BinaryFileWriter
  {
  public:
    BinaryFileWriter();
    ~BinaryFileWriter();

    bool WriteFile(LPCWSTR fileName, BYTE* buffer, DWORD bufferSize);
  };
}


