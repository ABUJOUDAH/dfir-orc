//
// SPDX-License-Identifier: LGPL-2.1-or-later
//
// Copyright © 2011-2019 ANSSI. All Rights Reserved.
//
// Author(s): Jean Gautier (ANSSI)
//
#pragma once

#include "CompleteVolumeReader.h"

#pragma managed(push, off)

namespace Orc {

class LogFileWriter;

class ImageReader : public CompleteVolumeReader
{
private:
    WCHAR m_szImageReader[MAX_PATH];

protected:
    virtual std::shared_ptr<VolumeReader> DuplicateReader();

public:
    ImageReader(logger pLog, const WCHAR* szImageFile);

    const WCHAR* ShortVolumeName() { return L"\\"; }

    virtual HRESULT LoadDiskProperties(void);
    virtual HANDLE GetDevice() { return INVALID_HANDLE_VALUE; }

    ~ImageReader(void);
};

}  // namespace Orc

constexpr auto REGEX_IMAGE = L"([^,]+)(,offset=([0-9]+))?(,size=([0-9]+))?(,sector=([0-9]+))?(,part=([0-9]+))?";
constexpr auto REGEX_IMAGE_SPEC = 1;
constexpr auto REGEX_IMAGE_PARTITION_SPEC = 8;
constexpr auto REGEX_IMAGE_PARTITION_NUM = 9;

constexpr auto REGEX_IMAGE_OFFSET = 3;
constexpr auto REGEX_IMAGE_SIZE = 5;
constexpr auto REGEX_IMAGE_SECTOR = 7;

#pragma managed(pop)
