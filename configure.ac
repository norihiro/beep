
AC_INIT([beep],[1.3.2],[norihiro@nagater.net])
AC_CONFIG_SRCDIR([config.hin])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_HEADER([config.h:config.hin])
AM_INIT_AUTOMAKE

AC_ARG_ENABLE(inspcspkr, [  --enable-inspcspkr turn on to check pscpkr is installed, if not install it],,enable_inspcspkr=yes)
if test x$enable_inspcspkr = xyes; then
	AC_DEFINE(ENABLE_INSPCSPKR, , pcspkr)
fi

AC_PROG_CC

AC_OUTPUT([Makefile])

