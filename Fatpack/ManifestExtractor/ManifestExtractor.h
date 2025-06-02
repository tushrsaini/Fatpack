#pragma once
#include <Windows.h>

namespace ManifestExtractor
{
#define MANIFEST_RESOURCE_TYPE RT_MANIFEST  // RT_MANIFEST = MAKEINTRESOURCE(24)
#define MAX_MANIFEST_RESOURCES 64

  struct ManifestResource
  {
    WORD id;
    WORD lang;
    DWORD size;
    LPVOID data;
  };

  class ManifestExtractor
  {
  public:
    ManifestExtractor();
    ~ManifestExtractor();

    bool ExtractManifestResources(LPWSTR srcPath);
    bool AddManifestResourcesToTarget(LPWSTR destPath);

    private:
      static BOOL CALLBACK EnumResNameProc(HMODULE moduleHandle, LPCTSTR type, LPTSTR name, LONG_PTR param);
      static BOOL CALLBACK EnumResLangProc(HMODULE moduleHandle, LPCTSTR type, LPCTSTR name, WORD language, LONG_PTR param);

  private:
    static ManifestResource* _manifestResources;
    static DWORD _manifestCount;
    HANDLE _heapHandle;
  };
}