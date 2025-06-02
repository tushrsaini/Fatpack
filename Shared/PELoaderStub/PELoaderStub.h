#pragma once
#include <windows.h>

namespace PELoader
{
  class PEImage;
  class TlsResolver;
  
}

namespace PELoaderStub
{
  class PELoaderStub
  {
  public:
    PELoaderStub();
    ~PELoaderStub();

    PELoader::PEImage* Load(PELoader::TlsResolver* tlsResolver);
  };
}