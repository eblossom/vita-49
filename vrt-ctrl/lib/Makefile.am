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

AM_CPPFLAGS = -I$(top_srcdir)/lib-asn1c -I.
AM_LDFLAGS = -Wl,-Map -Wl,$@.map


lib_LTLIBRARIES = libvrtc.la

libvrtc_la_SOURCES = \
	vrtc_expr.c \
	vrtc_expr_host.c

libvrtc_la_INCLUDES = \
	vrtc_expr.h \
	vrt-ctrl-protocol-consts.h

libvrtc_la_LIBADD = \
	../lib-asn1c/libasn1c.la

noinst_PROGRAMS = encode_Expr

encode_Expr_SOURCES = encode_Expr.c
encode_Expr_LDADD = libvrtc.la

