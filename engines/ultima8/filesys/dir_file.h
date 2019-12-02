/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef ULTIMA8_FILESYS_DIRFILE_H
#define ULTIMA8_FILESYS_DIRFILE_H

#include "ultima8/filesys/named_archive_file.h"
#include "ultima8/misc/p_dynamic_cast.h"
#include "ultima8/std/string.h"

namespace Ultima8 {

class DirFile : public NamedArchiveFile {
public:
	ENABLE_RUNTIME_CLASSTYPE()

	//! create DirFile from path
	explicit DirFile(const std::string &path);
	virtual ~DirFile();

	virtual bool exists(const std::string &name);

	virtual uint8 *getObject(const std::string &name, uint32 *size = 0);

	virtual uint32 getSize(const std::string &name);

	virtual uint32 getCount() {
		return count;
	}

protected:
	bool readMetadata();

	std::string path;
	uint32 count;
};

} // End of namespace Ultima8

#endif