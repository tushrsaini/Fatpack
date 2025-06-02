#include "CommandLine.h"

namespace CommandLine
{
  CommandLine::CommandLine()
  {
  }

  CommandLine::~CommandLine()
  {
  }

  LPWSTR CommandLine::GetCommandLine()
  {
    return ::GetCommandLineW();
  }

  LPWSTR* CommandLine::CommandLineToArgv(LPWSTR commandLine, int& argc)
  {
    return ::CommandLineToArgvW(commandLine, &argc);
  }
}