/**
 * @file definitions.h
 *
 * Type definitions for Windows NT API function pointers
 *
 * Description is available at https://github.com/Alon-Alush/AlushPacker
 *
 * E-mail: alonalush5@gmail.com
 *
 * LICENSE:
 *
 * Copyright (c) 2025 Alon Alush
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <windows.h>
#include <winternl.h>

// Function pointer type definitions for Windows NT API functions

// RtlInitUnicodeString - Initializes a UNICODE_STRING structure
typedef VOID(NTAPI* pRtlInitUnicodeString)(
    PUNICODE_STRING DestinationString,
    PCWSTR SourceString
);

// LdrLoadDll - Loads a DLL into the process address space
typedef NTSTATUS(NTAPI* pLdrLoadDll)(
    PWSTR SearchPath,
    PULONG DllCharacteristics,
    PUNICODE_STRING DllName,
    PVOID* BaseAddress
);

// ZwAllocateVirtualMemory - Allocates virtual memory in a process
typedef NTSTATUS(NTAPI* pZwAllocateVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    ULONG_PTR ZeroBits,
    PSIZE_T RegionSize,
    ULONG AllocationType,
    ULONG Protect
);

// ZwProtectVirtualMemory - Changes protection on a region of committed pages
typedef NTSTATUS(NTAPI* pZwProtectVirtualMemory)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PSIZE_T RegionSize,
    ULONG NewProtect,
    PULONG OldProtect
);

// RtlInsertInvertedFunctionTable - Inserts function table for exception handling
typedef NTSTATUS(NTAPI* pRtlInsertInvertedFunctionTable)(
    PVOID ImageBase,
    ULONG SizeOfImage
);

// RtlAddFunctionTable - Adds function table for 64-bit exception handling
typedef BOOLEAN(NTAPI* pRtlAddFunctionTable)(
    PRUNTIME_FUNCTION FunctionTable,
    DWORD EntryCount,
    DWORD64 BaseAddress
);

#endif // DEFINITIONS_H
