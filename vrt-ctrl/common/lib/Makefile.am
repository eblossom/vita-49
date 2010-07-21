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

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common/libasn1c -I.
AM_LDFLAGS = -Wl,-Map -Wl,$@.map


lib_LTLIBRARIES = libvrtccommon.la

libvrtccommon_la_SOURCES = \
	vrtc_expr.c \
	vrtc_host.c

libvrtccommon_la_INCLUDES = \
	vrtc_expr.h \
	vrtc_host.h


libvrtccommon_la_LIBADD = \
	../libasn1c/libasn1c.la

noinst_PROGRAMS = encode_Expr

encode_Expr_SOURCES = encode_Expr.c
encode_Expr_LDADD = libvrtccommon.la

