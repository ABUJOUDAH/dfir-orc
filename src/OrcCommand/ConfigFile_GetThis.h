//
// SPDX-License-Identifier: LGPL-2.1-or-later
//
// Copyright © 2011-2019 ANSSI. All Rights Reserved.
//
// Author(s): Jean Gautier (ANSSI)
//

#include "OrcLib.h"

#include "ConfigFile.h"

#include "ConfigFile_Common.h"

#pragma managed(push, off)

constexpr auto GETTHIS_OUTPUT = 0L;
constexpr auto GETTHIS_LOCATION = 1L;
constexpr auto GETTHIS_KNOWNLOCATIONS = 2L;
constexpr auto GETTHIS_SAMPLES = 3L;
constexpr auto GETTHIS_LOGGING = 4L;
constexpr auto GETTHIS_FLUSHREGISTRY = 5L;
constexpr auto GETTHIS_NOLIMITS = 6L;
constexpr auto GETTHIS_REPORTALL = 7L;
constexpr auto GETTHIS_HASH = 8L;
constexpr auto GETTHIS_FUZZYHASH = 9L;
constexpr auto GETTHIS_YARA = 10L;

constexpr auto GETTHIS_GETTHIS = 0L;

namespace Orc::Config::GetThis {
ORCLIB_API HRESULT root(ConfigItem& item);
}