#
# Copyright 2010 Free Software Foundation, Inc.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

include $(top_srcdir)/Makefile.common

AM_CPPFLAGS = -I$(top_srcdir)/include
#AM_LDFLAGS = -Wl,-Map -Wl,$@.map


lib_LTLIBRARIES = libvrtc-device.la

libvrtc_device_la_SOURCES = \
	handle_op.c \
	vrtcd_handle_incoming_datagram.c

libvrtc_device_la_LIBADD = \
	../../common/lib/libvrtc-common.la

