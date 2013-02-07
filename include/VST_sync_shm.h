/*
 * VST_sync_shm.h - type declarations needed for VST to lmms host sync
 *
 * Copyright (c) 2004-2013 Tobias Doerffel <tobydox/at/users.sourceforge.net>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#ifndef _VST_SYNC_SHM_H
#define _VST_SYNC_SHM_H

// VST sync frequency (in ms), how often will be VST plugin synced
// keep it power of two if possible (not used by now)
//#define VST_SNC_TIMER 1

// When defined, latency should be subtracted from song PPQ position
//#define VST_SNC_LATENCY

// define file for ftok as shared memory shmget key
#define VST_SNC_SHM_KEY_FILE "/dev/null"
//#define VST_SNC_SHM_RND_KEY 3561653564469

struct sncVST
{
	bool isPlayin;
	double ppqPos;
	int timeSigNumer;
	int timeSigDenom;
	bool isCycle;
	bool hasSHM;
	double cycleStart;
	double cycleEnd;
	int m_bufferSize;
	int m_sampleRate;
	int m_bpm;

#ifdef VST_SNC_LATENCY
	double m_latency;
#endif
} ;

#endif
