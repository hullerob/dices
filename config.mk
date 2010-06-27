# dices version
VERSION = 0

# Customize below to fit your system

# paths
PREFIX = /usr/local
EXECPREFIX = ${PREFIX}/bin
MANPREFIX = ${PREFIX}/share/man

INCS = -I. -I/usr/include
LIBS =

# flags
CFLAGS  = -std=c99 -pedantic -Wall -Wextra -Werror -Os ${INCS}
CFLAGS += -DVERSION=\"${VERSION}\"
LDFLAGS = ${LIBS} -static

# compiler and linker
CC = cc
LD = ${CC}
