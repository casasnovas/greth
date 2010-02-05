SRCDIR		= $(shell pwd)
DESTDIR		= /usr/local/bin

CC		= gcc
CFLAGS		= -O2 -fomit-frame-pointer
LDFLAGS		=
SHELL		= /bin/sh

PROJECT_NAME	= greth
PROJECT_VERSION = 0.1

BINARY_NAME	= $(PROJECT_NAME)

SOURCE_FILES	= greth.c

OBJECT_FILES	= $(SOURCE_FILES:.c=.o)
