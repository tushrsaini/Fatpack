#pragma once
#include <Windows.h>

namespace CommandLine
{
  class CommandLine
  {
  public:
    CommandLine();
    ~CommandLine();

    LPWSTR GetCommandLine();
    LPWSTR* CommandLineToArgv(LPWSTR commandLine, int& argc);
  };
}