HEADERS = 	include/callbacks.h\
			include/resource.h\
			include/plot2d.h\

OBJS =		obj/winmain.o\
			obj/callbacks.o\
			obj/resource.o\
			obj/plot2d.o\

INCLUDE_DIRS = -I.\include

WARNS = -Wall

CC = gcc

LDFLAGS = -s -lcomctl32 -lGdi32 -Wl,--subsystem,windows

RC = windres

# Compile ANSI build only if CHARSET=ANSI
ifeq (${CHARSET}, ANSI)
  CFLAGS= -O3 -std=c99 -D _WIN32_IE=0x0500 -D WINVER=0x500 ${WARNS}
else
  CFLAGS= -O3 -std=c99 -D UNICODE -D _UNICODE -D _WIN32_IE=0x0500 -D WINVER=0x500 ${WARNS}
endif


all: bin/plot2d.exe

bin/plot2d.exe: ${OBJS}
	${CC} -o "$@" ${OBJS} ${LDFLAGS}

clean:
	del obj\*.o "bin/plot2d.exe"

obj/%.o: src/%.c ${HEADERS}
	${CC} ${CFLAGS} ${INCLUDE_DIRS} -c $< -o $@

obj/resource.o: res/resource.rc res/Application.manifest res/Application.ico include/resource.h
	${RC} -I.\include -I.\res -i $< -o $@