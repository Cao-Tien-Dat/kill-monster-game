CFLAGS		+= -I./sources/app/game/archery_game
CPPFLAGS	+= -I./sources/app/game/archery_game

VPATH += sources/app/game/archery_game

# CPP source files 
# Archery game 
SOURCES_CPP += sources/app/game/archery_game/game_gun.cpp
SOURCES_CPP += sources/app/game/archery_game/bullet.cpp
SOURCES_CPP += sources/app/game/archery_game/bang.cpp
SOURCES_CPP += sources/app/game/archery_game/game_border.cpp
SOURCES_CPP += sources/app/game/archery_game/monster.cpp