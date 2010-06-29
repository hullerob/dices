# dices version
VERSION = 1

# Customize below to fit your system

# paths
PREFIX = /usr/local
EXECPREFIX = ${PREFIX}/bin
MANPREFIX = ${PREFIX}/share/man

INCS = -I. -I/usr/include
LIBS =

# options
# colors
OPTS += -DWITH_COLOR

# flags
CFLAGS  = -std=c99 -pedantic -Wall -Wextra -Werror -O0 -g ${INCS}
CFLAGS += -DVERSION=\"${VERSION}\"
CFLAGS += ${OPTS}
LDFLAGS = ${LIBS} -static

# compiler and linker
CC = clang
LD = ${CC}
