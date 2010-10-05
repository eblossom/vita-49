dnl
dnl Copyright 2010 Free Software Foundation, Inc.
dnl
dnl This program is free software: you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation, either version 3 of the License, or
dnl (at your option) any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program.  If not, see <http://www.gnu.org/licenses/>.
dnl

AC_INIT
AC_PREREQ(2.61)
AM_CONFIG_HEADER(config.h)
AC_CONFIG_SRCDIR([include/vrt/expanded_if_context_section.h])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AM_INIT_AUTOMAKE(vrt,0.0)

dnl Remember if the user explicity set CFLAGS
if test -n "${CFLAGS}"; then
  user_set_cflags=yes
fi
dnl Remember if the user explicity set CXXFLAGS
if test -n "${CXXFLAGS}"; then
  user_set_cxxflags=yes
fi


LF_CONFIGURE_CC
LF_CONFIGURE_CXX
GR_LIB64		dnl check for lib64 suffix after choosing compilers

GR_VERSION

dnl define WORDS_BIGENDIAN if needed
AC_C_BIGENDIAN


dnl The three macros above are known to override CFLAGS if the user
dnl didn't specify them.  Though I'm sure somebody thought this was
dnl a good idea, it makes it hard to use other than -g -O2 when compiling
dnl selected files.  Thus we "undo" the damage here...
dnl 
dnl If the user specified CFLAGS, we use them.
dnl See Makefile.common for the rest of the magic.
if test "$user_set_cflags" != yes; then
  autoconf_default_CFLAGS="$CFLAGS"
  CFLAGS=""
fi
AC_SUBST(autoconf_default_CFLAGS)


dnl The three macros above are known to override CXXFLAGS if the user
dnl didn't specify them.  Though I'm sure somebody thought this was
dnl a good idea, it makes it hard to use other than -g -O2 when compiling
dnl selected files.  Thus we "undo" the damage here...
dnl 
dnl If the user specified CXXFLAGS, we use them.  Otherwise when compiling
dnl the output of swig use use -O1 if we're using g++.
dnl See Makefile.common for the rest of the magic.
if test "$user_set_cxxflags" != yes; then
  autoconf_default_CXXFLAGS="$CXXFLAGS"
  CXXFLAGS=""
  if test "$GXX" = yes; then
    case "$host_cpu" in
    	powerpc*)
	   dnl "-O1" is broken on the PPC for some reason
	   dnl (at least as of g++ 4.1.1)
	   swig_CXXFLAGS="-g1 -O2 -Wno-strict-aliasing -Wno-parentheses"
	;;
    	*) 
	swig_CXXFLAGS="-g -O1 -Wno-strict-aliasing -Wno-parentheses"
	;;
    esac
  fi
fi
AC_SUBST(autoconf_default_CXXFLAGS)
AC_SUBST(swig_CXXFLAGS)


LF_SET_WARNINGS
AM_PROG_AS
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PATH_PROG([RM_PROG], [rm])

AC_LIBTOOL_WIN32_DLL
m4_ifdef([LT_INIT],[LT_INIT],[AC_PROG_LIBTOOL])

GR_NO_UNDEFINED		dnl do we need the -no-undefined linker flag


dnl We require the boost headers, thread lib and date_time lib.
dnl AX_BOOST_BASE finds the headers and the lib dir (-L<foo>)
dnl
dnl calls AC_SUBST(BOOST_CPPFLAGS), AC_SUBST(BOOST_LDFLAGS) and defines HAVE_BOOST
dnl
dnl Current Boost version requirement is >=1.35 for all platforms except Darwin,
dnl which requires >=1.37 for code in usrp host library.
case "$host_os" in
     darwin*)
        AX_BOOST_BASE([1.37])
        ;;
      *)
        AX_BOOST_BASE([1.35])
        ;;
esac

dnl calls AC_SUBST(BOOST_THREAD_LIB), AC_SUBST(BOOST_CXXFLAGS) and defines HAVE_BOOST_THREAD
dnl AX_BOOST_THREAD
dnl CXXFLAGS="$CXXFLAGS $BOOST_CXXFLAGS"       dnl often picks up a -pthread or something similar
dnl CFLAGS="$CFLAGS $BOOST_CXXFLAGS"           dnl often picks up a -pthread or something similar

dnl
dnl all the rest of these call AC_SUBST(BOOST_<foo>_LIB) and define HAVE_BOOST_<foo>
dnl
dnl AX_BOOST_DATE_TIME
dnl AX_BOOST_FILESYSTEM
dnl AX_BOOST_IOSTREAMS
AX_BOOST_PROGRAM_OPTIONS
dnl AX_BOOST_REGEX
dnl AX_BOOST_SERIALIZATION
dnl AX_BOOST_SIGNALS
AX_BOOST_SYSTEM
dnl AX_BOOST_TEST_EXEC_MONITOR
dnl AX_BOOST_UNIT_TEST_FRAMEWORK
dnl AX_BOOST_WSERIALIZATION


AC_CONFIG_FILES([\
    Makefile
    m4/Makefile
    vrt.pc
    include/Makefile
    include/vrt/Makefile
    lib/Makefile
    apps/Makefile
])

AC_OUTPUT
