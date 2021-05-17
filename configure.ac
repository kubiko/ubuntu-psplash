AC_PREREQ(2.53)
AC_INIT(psplash, 0.1, [http://bugzilla.o-hand.com/enter_bug.cgi?product=psplash])
AM_INIT_AUTOMAKE()
AC_CONFIG_SRCDIR(psplash.c)
AM_CONFIG_HEADER(config.h)

AC_ISC_POSIX
AC_PROG_CC
AC_STDC_HEADERS

if test "x$GCC" = "xyes"; then
        GCC_FLAGS="-g -Wall -Wextra"
fi

AC_ARG_WITH([systemd], AS_HELP_STRING([--with-systemd], [Build with systemd
	     support]))

AS_IF([test "x$with_systemd" = "xyes"], [
   PKG_CHECK_MODULES(SYSTEMD, libsystemd >= 221)
])

AM_CONDITIONAL([HAVE_SYSTEMD], [test "x$with_systemd" = "xyes"])

AC_ARG_WITH([infinite-progress], AS_HELP_STRING([--with-infinite-progress], [Build with infinite progress support]))

AM_CONDITIONAL([HAVE_INFINITE_PROGRESS], [test "x$with_infinite_progress" = "xyes"])

AC_ARG_VAR([PROGRESS_INCREMENTS], [Increments of the infinit progress in %(default is '20')])
AS_IF([test x$PROGRESS_INCREMENTS != x],[
    EXTRA_GCC_FLAGS="$EXTRA_GCC_FLAGS -DPROGRESS_INCREMENTS=$PROGRESS_INCREMENTS"
])

AC_ARG_VAR([PROGRESS_REFRESH], [Infinite Progress Refresh rate in milliseconds %(default is '500')])
AS_IF([test x$PROGRESS_REFRESH != x],[
    EXTRA_GCC_FLAGS="$EXTRA_GCC_FLAGS -DPROGRESS_REFRESH=$PROGRESS_REFRESH"
])

AC_SUBST(GCC_FLAGS)

AC_ARG_WITH([font],
    AS_HELP_STRING([--with-font], [Set font to use (default is 'radeon')]),
    [FONT_NAME=$withval],
    [FONT_NAME=radeon])
AC_SUBST([FONT_NAME])

AC_ARG_ENABLE([startup-msg],
    AS_HELP_STRING([--disable-startup-msg], [Disable text banner output on startup]),
    [disable_startup_msg=true],
    [disable_startup_msg=false])
AS_IF([test x$disable_startup_msg = xtrue], [
    EXTRA_GCC_FLAGS="$EXTRA_GCC_FLAGS -DPSPLASH_DISABLE_STARTUP_MSG"
])

AC_ARG_ENABLE([img-fullscreen],
    AS_HELP_STRING([--enable-img-fullscreen], [Enable the logo image in fullscreen mode)]),
    [img_fullscreen=true],
    [img_fullscreen=false])
AS_IF([test x$img_fullscreen = xtrue], [
    EXTRA_GCC_FLAGS="$EXTRA_GCC_FLAGS -DPSPLASH_IMG_FULLSCREEN=1"
])

AC_SUBST(EXTRA_GCC_FLAGS)

AC_OUTPUT([
Makefile
])
