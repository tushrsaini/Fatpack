#include "Console.h"

namespace Console
{
  Console::Console()
  {
  }

  Console::~Console()
  {
  }

  void Console::WriteLine(const wchar_t* text)
  {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleHandle == INVALID_HANDLE_VALUE) return;

    DWORD written = 0;
    WriteConsoleW(consoleHandle, text, (DWORD)wcslen(text), &written, NULL);
    WriteConsoleW(consoleHandle, L"\n", 1, &written, NULL);
  }
}