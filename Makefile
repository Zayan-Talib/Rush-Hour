CXXFLAGS =	-g3 -fmessage-length=0 -Wno-narrowing #-Wall -Werror

SRCS = game.cpp \
       utility/util.cpp \
       world/board.cpp \
       world/game_state.cpp \
       ui/menu.cpp \
       entities/entity.cpp \
       entities/actor.cpp \
       entities/player_car.cpp

OBJS = $(SRCS:.cpp=.o)

LIBS = 		-L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGLU -lGL -lX11 -lfreeimage -pthread

TARGET =	rush_hour

$(TARGET):	$(OBJS) 
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
