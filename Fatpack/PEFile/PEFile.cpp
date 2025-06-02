#include "PEFile.h"

namespace PEFile
{
	PEFile::PEFile()
	{
		_buffer = nullptr;
		_bufferSize = 0;
		_PIMAGE_DOS_HEADER = nullptr;
		_PIMAGE_NT_HEADERS = nullptr;
		_PIMAGE_SECTION_HEADER = nullptr;
	}

	PEFile::~PEFile()
	{
		DeleteBuffer();
	}

	bool PEFile::LoadFromBuffer(BYTE* fileBuffer, DWORD size)
	{
		DeleteBuffer();
		_bufferSize = size;
		_buffer = new BYTE[_bufferSize];
		memcpy(_buffer, fileBuffer, _bufferSize);

		_PIMAGE_DOS_HEADER = (PIMAGE_DOS_HEADER)_buffer;
		_PIMAGE_NT_HEADERS = (PIMAGE_NT_HEADERS)(_buffer + _PIMAGE_DOS_HEADER->e_lfanew);
		_PIMAGE_SECTION_HEADER = IMAGE_FIRST_SECTION(_PIMAGE_NT_HEADERS);

		return true;
	}

	bool PEFile::IsConsole()
	{
		if (_buffer == nullptr || _bufferSize == 0) return false;

	  return (_PIMAGE_NT_HEADERS->OptionalHeader.Subsystem == IMAGE_SUBSYSTEM_WINDOWS_CUI);
	}

	void PEFile::DeleteBuffer()
	{
		if (_buffer != nullptr)
		{
			delete[] _buffer;
			_buffer = nullptr;
		}
	}
}