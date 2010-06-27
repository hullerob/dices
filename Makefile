# dices - a game

include config.mk

SRC = game.c
HEAD = game.h
OBJ = ${SRC:.c=.o}

all: options dices

options:
	@echo dices build options
	@echo "CFLAGS  = ${CFLAGS}"
	@echo "LDFLAGS = ${LDFLAGS}"
	@echo "CC      = ${CC}"
	@echo "LD      = ${LD}"

%.o: %.c
	@echo CC $<
	@${CC} ${CFLAGS} -c $<

dices: ${OBJ}
	@echo LD $@
	@${LD} ${LDFLAGS} -o $@ ${OBJ}

${OBJ}: config.mk ${HEAD}

clean:
	@echo cleaning
	@rm -f dices ${OBJ} dices-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir dices-${VERSION}
	@cp LICENSE Makefile config.mk ${SRC} ${HEAD} dices-${VERSION}
	@tar cf dices-${VERSION}.tar dices-${VERSION}
	@gzip dices-${VERSION}.tar
	@rm -r dices-${VERSION}

install: all
	@echo installing executable file to ${EXECPREFIX}
	@mkdir -p ${DESTDIR}${EXECPREFIX}
	@cp -f dices ${DESTDIR}${EXECPREFIX}
	@chmod 755 ${DESTDIR}${EXECPREFIX}/dices

uninstall:
	@echo removing executable file from ${DESTDIR}${EXECPREFIX}
	@rm -f ${DESTDIR}${EXECPREFIX}/dices

.PHONY: all options clean dist install uninstall
