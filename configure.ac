
AC_INIT(libvirt-glib, 0.0.1)
AC_CONFIG_SRCDIR(libvirt-glib/libvirt-glib-main.c)
AC_CONFIG_AUX_DIR([build-aux])
AM_CONFIG_HEADER(config.h)
AC_CONFIG_MACRO_DIR([m4])
dnl Make automake keep quiet about wildcards & other GNUmake-isms
AM_INIT_AUTOMAKE([-Wno-portability])
AC_CANONICAL_HOST

AM_SILENT_RULES([yes])

LIBVIRT_REQUIRED=0.5.0
GLIB2_REQUIRED=2.10.0
GOBJECT2_REQUIRED=2.10.0
GIO_REQUIRED=2.10.0
GOBJECT_INTROSPECTION_REQUIRED=0.10.8
LIBXML2_REQUIRED=2.0.0

LIBVIRT_GLIB_MAJOR_VERSION=`echo $VERSION | awk -F. '{print $1}'`
LIBVIRT_GLIB_MINOR_VERSION=`echo $VERSION | awk -F. '{print $2}'`
LIBVIRT_GLIB_MICRO_VERSION=`echo $VERSION | awk -F. '{print $3}'`
LIBVIRT_GLIB_VERSION=$LIBVIRT_GLIB_MAJOR_VERSION.$LIBVIRT_GLIB_MINOR_VERSION.$LIBVIRT_GLIB_MICRO_VERSION$LIBVIRT_GLIB_MICRO_VERSION_SUFFIX
LIBVIRT_GLIB_VERSION_INFO=`expr $LIBVIRT_GLIB_MAJOR_VERSION + $LIBVIRT_GLIB_MINOR_VERSION`:$LIBVIRT_GLIB_MICRO_VERSION:$LIBVIRT_GLIB_MINOR_VERSION
LIBVIRT_GLIB_VERSION_NUMBER=`expr $LIBVIRT_GLIB_MAJOR_VERSION \* 1000000 + $LIBVIRT_GLIB_MINOR_VERSION \* 1000 + $LIBVIRT_GLIB_MICRO_VERSION`

AC_SUBST([LIBVIRT_GLIB_MAJOR_VERSION])
AC_SUBST([LIBVIRT_GLIB_MINOR_VERSION])
AC_SUBST([LIBVIRT_GLIB_MICRO_VERSION])
AC_SUBST([LIBVIRT_GLIB_VERSION])
AC_SUBST([LIBVIRT_GLIB_VERSION_INFO])
AC_SUBST([LIBVIRT_GLIB_VERSION_NUMBER])

AC_PROG_CC
AM_PROG_CC_C_O

AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

dnl AC_CONFIG_LIBOBJ_DIR([src])

AC_DEFINE([_GNU_SOURCE], [], [Enable GNU extensions])

LIBVIRT_GLIB_COMPILE_WARNINGS([maximum])

PKG_CHECK_MODULES(LIBVIRT, libvirt >= $LIBVIRT_REQUIRED)
PKG_CHECK_MODULES(GLIB2, glib-2.0 >= $GLIB2_REQUIRED)
PKG_CHECK_MODULES(GTHREAD2, gthread-2.0 >= $GLIB2_REQUIRED)
PKG_CHECK_MODULES(GOBJECT2, gobject-2.0 >= $GLIB2_REQUIRED)
PKG_CHECK_MODULES(GIO2, gio-2.0 >= $GLIB2_REQUIRED)
PKG_CHECK_MODULES(LIBXML2, libxml-2.0 >= $LIBXML2_REQUIRED)

dnl Extra link-time flags for Cygwin.
dnl Copied from libxml2 configure.in, but I removed mingw changes
dnl for now since I'm not supporting mingw at present.  - RWMJ
CYGWIN_EXTRA_LDFLAGS=
CYGWIN_EXTRA_LIBADD=
CYGWIN_EXTRA_PYTHON_LIBADD=
MINGW_EXTRA_LDFLAGS=
case "$host" in
  *-*-cygwin*)
    CYGWIN_EXTRA_LDFLAGS="-no-undefined"
    CYGWIN_EXTRA_LIBADD="${INTLLIBS}"
    if test "x$PYTHON_VERSION" != "x"; then
      CYGWIN_EXTRA_PYTHON_LIBADD="-L/usr/lib/python${PYTHON_VERSION}/config -lpython${PYTHON_VERSION}"
    fi
    ;;
  *-*-mingw*)
    MINGW_EXTRA_LDFLAGS="-no-undefined"
    ;;
esac
AC_SUBST([CYGWIN_EXTRA_LDFLAGS])
AC_SUBST([CYGWIN_EXTRA_LIBADD])
AC_SUBST([CYGWIN_EXTRA_PYTHON_LIBADD])
AC_SUBST([MINGW_EXTRA_LDFLAGS])


AC_ARG_ENABLE([test-coverage],
[  --enable-test-coverage  turn on code coverage instrumentation],
[case "${enableval}" in
   yes|no) ;;
   *)      AC_MSG_ERROR([bad value ${enableval} for test-coverage option]) ;;
 esac],
              [enableval=no])
enable_coverage=$enableval

if test "${enable_coverage}" = yes; then
  gl_COMPILER_FLAGS(-fprofile-arcs)
  gl_COMPILER_FLAGS(-ftest-coverage)
  AC_SUBST([COVERAGE_CFLAGS], [$COMPILER_FLAGS])
  AC_SUBST([COVERAGE_LDFLAGS], [$COMPILER_FLAGS])
  COMPILER_FLAGS=
fi

dnl
dnl check for python
dnl
AC_ARG_WITH([python],
  AC_HELP_STRING([--with-python], [Build python bindings @<:@default=yes@:>@]),[],[with_python=yes])

PYTHON_VERSION=
PYTHON_INCLUDES=
PYTHON_SITE_PACKAGES=
PYTHON_TESTS=
pythondir=
if test "$with_python" != "no" ; then
    if test "$with_python" = "yes" ; then
       with_python=""
    fi
    if test -x "$with_python/bin/python"
    then
        echo Found python in $with_python/bin/python
        PYTHON="$with_python/bin/python"
    else
	if test -x "$with_python"
	then
	    echo Found python in $with_python
	    PYTHON="$with_python"
	else
	    if test -x "$PYTHON"
	    then
	        echo Found python in environment PYTHON=$PYTHON
		with_python=`$PYTHON -c "import sys; print sys.exec_prefix"`
	    else
		AC_PATH_PROG([PYTHON], [python python2.6 python2.5 python2.4 python2.3 python2.2 python2.1 python2.0 python1.6 python1.5])
	    fi
	fi
    fi
    if test "$PYTHON" != ""
    then
        PYTHON_VERSION=`$PYTHON -c "import sys; print sys.version[[0:3]]"`
	echo Found Python version $PYTHON_VERSION
    fi
    if test "$PYTHON_VERSION" != ""
    then
	if test -r $with_python/include/python$PYTHON_VERSION/Python.h -a \
	   -d $with_python/lib/python$PYTHON_VERSION/site-packages
	then
	    PYTHON_INCLUDES=$with_python/include/python$PYTHON_VERSION
	    PYTHON_SITE_PACKAGES=$libdir/python$PYTHON_VERSION/site-packages
	else
	    if test -r $prefix/include/python$PYTHON_VERSION/Python.h
	    then
	        PYTHON_INCLUDES=$prefix/include/python$PYTHON_VERSION
	        PYTHON_SITE_PACKAGES=$libdir/python$PYTHON_VERSION/site-packages
	    else
		if test -r /usr/include/python$PYTHON_VERSION/Python.h
		then
		    PYTHON_INCLUDES=/usr/include/python$PYTHON_VERSION
	            PYTHON_SITE_PACKAGES=$libdir/python$PYTHON_VERSION/site-packages
		else
		    echo could not find python$PYTHON_VERSION/Python.h
		fi
	    fi
	    if test ! -d "$PYTHON_SITE_PACKAGES"
	    then
		    PYTHON_SITE_PACKAGES=`$PYTHON -c "from distutils import sysconfig; print sysconfig.get_python_lib()"`
	    fi
	fi
    fi
    if test "$with_python" != ""
    then
        pythondir='$(PYTHON_SITE_PACKAGES)'
    else
        pythondir='$(libdir)/python$(PYTHON_VERSION)/site-packages'
    fi
else
    PYTHON=
fi
AM_CONDITIONAL([WITH_PYTHON], test "$PYTHON_INCLUDES" != "")
AC_SUBST([pythondir])
AC_SUBST([PYTHON_VERSION])
AC_SUBST([PYTHON_INCLUDES])
AC_SUBST([PYTHON_SITE_PACKAGES])

AC_ARG_ENABLE([introspection],
        AS_HELP_STRING([--enable-introspection], [enable GObject introspection]),
        [], [enable_introspection=check])

if test "x$enable_introspection" != "xno" ; then
        PKG_CHECK_MODULES([GOBJECT_INTROSPECTION],
                          [gobject-introspection-1.0 >= $GOBJECT_INTROSPECTION_REQUIRED],
                          [enable_introspection=yes],
                          [
                             if test "x$enable_introspection" = "xcheck"; then
                               enable_introspection=no
                             else
                               AC_MSG_ERROR([gobject-introspection is not available])
                             fi
                          ])
        if test "x$enable_introspection" = "xyes" ; then
          AC_DEFINE([WITH_GOBJECT_INTROSPECTION], [1], [enable GObject introspection support])
          AC_SUBST(GOBJECT_INTROSPECTION_CFLAGS)
          AC_SUBST(GOBJECT_INTROSPECTION_LIBS)
          AC_SUBST([G_IR_SCANNER], [$($PKG_CONFIG --variable=g_ir_scanner gobject-introspection-1.0)])
          AC_SUBST([G_IR_COMPILER], [$($PKG_CONFIG --variable=g_ir_compiler gobject-introspection-1.0)])
        fi
fi
AM_CONDITIONAL([WITH_GOBJECT_INTROSPECTION], [test "x$enable_introspection" = "xyes"])

AC_OUTPUT(Makefile
          libvirt-glib/Makefile
          libvirt-gconfig/Makefile
          libvirt-gobject/Makefile
          examples/Makefile
          python/Makefile
          libvirt-glib-1.0.pc
          libvirt-gconfig-1.0.pc
          libvirt-gobject-1.0.pc
          libvirt-glib.spec
          mingw32-libvirt-glib.spec)