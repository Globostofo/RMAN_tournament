TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        tournament/games/dames.cpp \
        tournament/games/echecs.cpp \
        tournament/games/memory.cpp \
        tournament/games/morpion.cpp \
        tournament/games/p4.cpp \
        tournament/tournament.cpp

HEADERS += \
    tournament/global.hpp \
    tournament/structs.h

DISTFILES += \
    readme.md \
    tournament/NOTAMOAMEM.md \
    tournament/students.txt
