CXXFLAGS =	-g3 -fmessage-length=0 -Wno-narrowing #-Wall -Werror

SRCS = game.cpp \
       utility/util.cpp \
       world/board.cpp \
       world/game_state.cpp \
       world/audio.cpp \
       ui/ui_element.cpp \
       ui/ui.cpp \
       ui/main_menu.cpp \
       ui/mode_menu.cpp \
       ui/name_menu.cpp \
       ui/leaderboard.cpp \
       ui/game_over_menu.cpp \
       ui/hud.cpp \
       ui/button.cpp \
       entities/entity.cpp \
       entities/actor.cpp \
       entities/player_car.cpp \
       entities/npc_car.cpp \
       entities/structure.cpp \
       entities/fuel_station.cpp \
       entities/mode_station.cpp \
       entities/building.cpp \
       entities/destination.cpp \
       entities/transportable.cpp \
       entities/package.cpp \
       entities/passenger.cpp   

OBJS = $(SRCS:.cpp=.o)

LIBS = 	-L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGLU -lGL -lX11 -lfreeimage -pthread -lSDL2 -lSDL2_mixer

TARGET =	rush_hour

$(TARGET):	$(OBJS) 
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
