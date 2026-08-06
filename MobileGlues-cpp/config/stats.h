// MobileGlues - config/stats.h
// Copyright (c) 2025-2026 MobileGL-Dev
// Licensed under the GNU Lesser General Public License v2.1:
//   https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
// SPDX-License-Identifier: LGPL-2.1-only
// End of Source File Header
#ifndef _MOBILEGLUES_STATS_H_
#define _MOBILEGLUES_STATS_H_

#ifdef __cplusplus
extern "C"
{
#endif

    // MG/stats.json: numbers this renderer accumulates about itself, kept apart
    // from config.json so that hand-editing settings can never disturb them and a
    // damaged counter can never be mistaken for a damaged configuration.
    //
    // Counting happens here rather than in the plugin app because this library is
    // what a game actually loads: one dlopen of libMobileGlues.so is one launch,
    // whereas opening the settings app is not.
    extern char* stats_file_path;

    // Read the current count, add one, write it back. Called once per process,
    // from init_config(), before anything else can fail.
    //
    // Does nothing when MG_SKIP_LAUNCH_COUNT is set: the plugin app loads this
    // library itself to read GL information, and that is not a launch either.
    void bump_launch_count();

#ifdef __cplusplus
}
#endif

#endif // _MOBILEGLUES_STATS_H_
