/**
 * @file definitions.h
 *
 * Function pointer typedefs for undocumented and documented NT APIs
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

// Function pointer typedef for LdrLoadDll
typedef NTSTATUS(NTAPI* pLdrLoadDll)(
    IN PWCHAR PathToFile OPTIONAL,
    IN ULONG Flags OPTIONAL,
    IN PUNICODE_STRING ModuleFileName,
    OUT PHANDLE ModuleHandle
    );

// Function pointer typedef for RtlInitUnicodeString
typedef VOID(NTAPI* pRtlInitUnicodeString)(
    PUNICODE_STRING DestinationString,
    PCWSTR SourceString
    );

// Function pointer typedef for ZwAllocateVirtualMemory
typedef NTSTATUS(NTAPI* pZwAllocateVirtualMemory)(
    IN HANDLE ProcessHandle,
    IN OUT PVOID* BaseAddress,
    IN ULONG_PTR ZeroBits,
    IN OUT PSIZE_T RegionSize,
    IN ULONG AllocationType,
    IN ULONG Protect
    );

// Function pointer typedef for ZwProtectVirtualMemory
typedef NTSTATUS(NTAPI* pZwProtectVirtualMemory)(
    IN HANDLE ProcessHandle,
    IN OUT PVOID* BaseAddress,
    IN OUT PSIZE_T RegionSize,
    IN ULONG NewProtect,
    OUT PULONG OldProtect
    );

// Function pointer typedef for RtlInsertInvertedFunctionTable
typedef NTSTATUS(NTAPI* pRtlInsertInvertedFunctionTable)(
    IN PVOID ImageBase,
    IN DWORD SizeOfImage
    );

// Function pointer typedef for RtlAddFunctionTable (x64 only)
#ifdef _WIN64
typedef BOOLEAN(NTAPI* pRtlAddFunctionTable)(
    IN PRUNTIME_FUNCTION FunctionTable,
    IN DWORD EntryCount,
    IN DWORD64 BaseAddress
    );
#endif

#endif // DEFINITIONS_H
