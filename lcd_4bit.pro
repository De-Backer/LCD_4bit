TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

NAME = lcd_4bit

HEADERS =   lcd_4bit.h 

SOURCES = lcd_4bit.c

# Add any library paths needed to build your project

INCLUDEPATH =/opt/cross/avr/avr/include/

DISTFILES += README.md
