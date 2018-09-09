TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    command_interpreter.c \
    constants.c \
    dictionary.c \
    stack.c \
    run.c

HEADERS += \
    command_interpreter.h \
    constants.h \
    dictionary.h \
    stack.h \
    run.h
