SRCDIR		= $(shell pwd)
DESTDIR		= /usr/local/bin

CC		= gcc
CFLAGS		= -g -ggdb -D __DEBUG
LDFLAGS		=
SHELL		= /bin/sh
#CFLAGS		= -O2 -fomit-frame-pointer

PROJECT_NAME	= greth
PROJECT_VERSION = 0.1

BINARY_NAME	= $(PROJECT_NAME)

SOURCE_FILES	= greth.c connect.c edcl_protocol.c gr_run.c gr_debug.c

OBJECT_FILES	= $(SOURCE_FILES:.c=.o)
