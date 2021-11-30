TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        global.cxx \
        main.cpp \
        tournament/tournament.cpp \
        tournament/games/chess.cpp \
        tournament/games/connect4.cpp \
        tournament/games/memory.cpp \
        tournament/games/priceisright.cpp \
        tournament/games/rockpaperscissors.cpp \
        tournament/games/tictactoe.cpp

HEADERS += \
    global.h

DISTFILES += \
    readme.md 
