//
// SPDX-License-Identifier: LGPL-2.1-or-later
//
// Copyright © 2011-2019 ANSSI. All Rights Reserved.
//
// Author(s): Jean Gautier (ANSSI)
//

#include "Archive.h"

#include "7zip/Archive/IArchive.h"
#include "7zip/IPassword.h"
#include "7zip/ICoder.h"

#include <concrt.h>

#pragma managed(push, off)

namespace Orc {

class ArchiveUpdateCallback
    : public IArchiveUpdateCallback
    , public ICryptoGetTextPassword2
    , public ICompressProgressInfo
{
private:
    long m_refCount;

    logger _L_;

    Archive::ArchiveItems& m_Items;
    Archive::ArchiveIndexes& m_Indexes;

    size_t m_firstAddIndex = 0;

    UInt32 m_curIndex;
    UInt32 m_curIndexInArchive;

    bool m_bFinal = false;

    Archive::ArchiveCallback m_Callback;

    std::wstring m_Password;

    concurrency::critical_section m_cs;

    size_t DeviseNextBestAddition();

public:
    ArchiveUpdateCallback(
        logger pLog,
        Archive::ArchiveItems& items,
        Archive::ArchiveIndexes& indexes,
        bool bFinal,
        Archive::ArchiveCallback pCallback = nullptr,
        const std::wstring& pwd = L"")
        : m_refCount(0)
        , _L_(std::move(pLog))
        , m_Items(items)
        , m_curIndex(0L)
        , m_curIndexInArchive((UInt32)indexes.size())
        , m_Callback(pCallback)
        , m_Indexes(indexes)
        , m_Password(pwd)
        , m_bFinal(bFinal) {};
    virtual ~ArchiveUpdateCallback();

    STDMETHOD(QueryInterface)(REFIID iid, void** ppvObject);
    STDMETHOD_(ULONG, AddRef)();
    STDMETHOD_(ULONG, Release)();

    // IProgress
    STDMETHOD(SetTotal)(UInt64 size);
    STDMETHOD(SetCompleted)(const UInt64* completeValue);

    // IArchiveUpdateCallback
    STDMETHOD(GetUpdateItemInfo)(UInt32 index, Int32* newData, Int32* newProperties, UInt32* indexInArchive);
    STDMETHOD(GetProperty)(UInt32 index, PROPID propID, PROPVARIANT* value);
    STDMETHOD(GetStream)(UInt32 index, ISequentialInStream** inStream);
    STDMETHOD(SetOperationResult)(Int32 operationResult);

    // ICryptoGetTextPassword2
    STDMETHOD(CryptoGetTextPassword2)(Int32* passwordIsDefined, BSTR* password);

    // ICompressProgressInfo
    STDMETHOD(SetRatioInfo)(const UInt64* inSize, const UInt64* outSize);
};
}  // namespace Orc

#pragma managed(pop)
