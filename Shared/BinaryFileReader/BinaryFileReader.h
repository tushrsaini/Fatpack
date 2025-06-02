#pragma once
#include <Windows.h>

namespace BinaryFileReader
{
  class BinaryFileReader
  {
  public:
    BinaryFileReader(const wchar_t* fileName);
    ~BinaryFileReader();

    BYTE* GetBuffer() { return _buffer; }
    DWORD GetBufferSize() { return _bufferSize; }

  private:
    void Cleanup();

  private:
    BYTE* _buffer;
    DWORD _bufferSize;
  };
}


