/****************************************************************
 *
 * Copyright (C) 2013 Alessandro Pignotti <alessandro@leaningtech.com>
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 ***************************************************************/

#include <cheerp/client.h>
#include <cheerp/clientlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/time.h>
#include "clientbridge.h"

[[cheerp::genericjs]]
void println(const char* line, size_t len)
{
	client::String* jsline = client::String::fromUtf8(line, len);
	if (line[len-1] == '\n')
	{
		//As far as output is line buffered we can remove
		//the newline, as JS print adds it anyway
		jsline = jsline->substr(0, len-1);
	}
	client::console.log(jsline);
}

_READ_WRITE_RETURN_TYPE
_DEFUN(__cheerpwrite, (fd, buf, n),
       int fd _AND
       const char *buf _AND
       int n)
{
	println(buf, n);
	return n;
}


extern "C" {

int gettimeofday (timeval* tv, void* tz_)
{
	timezone *tz = (timezone*)tz_;
	if(tv)
	{
		// 'now' is in milliseconds
		double now = cheerp::date_now();
		tv->tv_sec = now / 1000;
		tv->tv_usec = (now-(tv->tv_sec*1000.0))*1000.0;
	}
	if(tz)
	{
		// The man page says this is an obsolete feature
		tz->tz_minuteswest = 0;
		tz->tz_dsttime = 0;
	}
	return 0;
}

}
