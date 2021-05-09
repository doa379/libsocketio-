LOCAL = ..
LIBSPATH = -L ${LOCAL}/libsocketio++ -Wl,-R$(LOCAL)/libsocketio++ '-Wl,-R$$ORIGIN'
INCS = -I /usr/local/include -I ${LOCAL}/
LIBS = -l socket++

SRC_LIBSOCKETIO = socketio.cpp
OBJ_LIBSOCKETIO = ${SRC_LIBSOCKETIO:.cpp=.o}
SRC_TEST0 = client_example.cpp
OBJ_TEST0 = ${SRC_TEST0:.cpp=.o}

CC = c++
CFLAGS = -std=c++14 -c -Wall -fPIE -fPIC -pedantic -O3 ${INCS}
LDFLAGS += ${LIBSPATH}

all: libsocketio++.so \
  client_example

.cpp.o:
	@echo CC $<
	@${CC} ${CFLAGS} $<

libsocketio++.so: ${OBJ_LIBSOCKETIO}
	@echo CC -o $@
	@${CC} -shared -o $@ ${OBJ_LIBSOCKETIO} ${LDFLAGS} ${LIBS}

client_example: ${OBJ_TEST0}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ_TEST0} ${LDFLAGS} -l socketio++

clean:
	@echo Cleaning
	@rm -f ${OBJ_LIBSOCKETIO} ${OBJ_TEST0}
	@rm -f *example
