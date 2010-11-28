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

AM_CPPFLAGS = -I$(top_srcdir)/include $(BOOST_CPPFLAGS)
AM_CXXFLAGS += $(BOOST_CXXFLAGS)
#AM_LDFLAGS = -Wl,-Map -Wl,$@.map


bin_PROGRAMS = vrtc-dev-sim

vrtc_dev_sim_SOURCES = \
	dev-sim-main.cc \
	resource-impl.c \
	resource-tree.c

vrtc_dev_sim_LDADD = \
	../lib/libvrtc-device.la \
	$(BOOST_LDFLAGS) $(BOOST_SYSTEM_LIB)

noinst_INCLUDES = \
	resource-impl.h


#vrtc_dev_sim_echo_raw_SOURCES = dev-sim-main.cc handle_datagram_echo_raw.c
#vrtc_dev_sim_echo_raw_LDADD = ../lib/libvrtc-device.la $(BOOST_LDFLAGS) $(BOOST_SYSTEM_LIB)
