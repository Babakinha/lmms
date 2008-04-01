/*
 * export.h - header which is needed for song-export
 *
 * Copyright (c) 2004-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
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

#ifndef _EXPORT_H
#define _EXPORT_H

#include <QtCore/QString>

#include "types.h"


class audioFileDevice;
class mixer;


typedef audioFileDevice * ( * getDeviceInst)( const sample_rate_t _sample_rate,
						const ch_cnt_t _channels,
						bool & _success_ful,
						const QString & _file,
						const bool _use_vbr,
						const bitrate_t _nom_bitrate,
						const bitrate_t _min_bitrate,
						const bitrate_t _max_bitrate,
						mixer * _mixer );


enum ExportFileTypes
{
	WaveFile,
	OggFile,
	NullFile = 0xFF
} ;



struct fileEncodeDevice
{
	ExportFileTypes m_fileType;
	const char * m_description;
	const char * m_extension;
	getDeviceInst m_getDevInst;
} ;


extern fileEncodeDevice fileEncodeDevices[];


#endif
