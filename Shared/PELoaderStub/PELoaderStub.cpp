#include "PELoaderStub.h"
#include "..\ResourceLoader\ResourceLoader.h"
#include "..\Decompressor\Decompressor.h"
#include "..\PELoader\PELoader\PELoader.h"
#include "..\PELoader\PELoader\PEImage.h"
#include "..\PELoader\PELoader\TlsResolver.h"

namespace PELoaderStub
{
  PELoaderStub::PELoaderStub()
  {
  }

  PELoaderStub::~PELoaderStub()
  {
  }

  PELoader::PEImage* PELoaderStub::Load(PELoader::TlsResolver* tlsResolver)
  {
    // Load packed target from resource
    DWORD targetSize = 0;
    ResourceLoader::ResourceLoader resourceLoader;
    BYTE* targetBuffer = resourceLoader.LoadResource(L"PACKED", RT_RCDATA, targetSize);
    if (targetBuffer == nullptr || targetSize == 0) return 0;

    // Decompress target
    size_t decompressedSize = 0;
    BYTE* decompressed = NULL;
    Decompressor::Decompressor decompressor;
    decompressor.Decompress(targetBuffer, targetSize, &decompressed, &decompressedSize);
    resourceLoader.Free(targetBuffer);

    // Load target
    PELoader::PELoader peLoader;
    LPVOID imageBase = peLoader.LoadPE(tlsResolver, (LPVOID)decompressed);
    decompressor.Free(decompressed);

    return new PELoader::PEImage(imageBase);
  }
}