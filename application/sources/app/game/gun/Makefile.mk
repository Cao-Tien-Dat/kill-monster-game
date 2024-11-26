CFLAGS		+= -I./sources/app/game/gun
CPPFLAGS	+= -I./sources/app/game/gun

VPATH += sources/app/game/gun

# CPP source files 
# Archery game 
SOURCES_CPP += sources/app/game/gun/game_gun.cpp
SOURCES_CPP += sources/app/game/gun/bullet.cpp
SOURCES_CPP += sources/app/game/gun/bang.cpp
SOURCES_CPP += sources/app/game/gun/game_border.cpp
SOURCES_CPP += sources/app/game/gun/monster.cpp