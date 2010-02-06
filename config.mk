SRCDIR		= $(shell pwd)
DESTDIR		= /usr/local/bin

CC		= gcc
#CFLAGS		= -O2 -fomit-frame-pointer
CFLAGS		= -g -ggdb -D __DEBUG
LDFLAGS		=
SHELL		= /bin/sh

PROJECT_NAME	= greth
PROJECT_VERSION = 0.1

BINARY_NAME	= $(PROJECT_NAME)

SOURCE_FILES	= greth.c connect.c edcl_protocol.c

OBJECT_FILES	= $(SOURCE_FILES:.c=.o)
