INC = -I$(GAIAGL) -I$(GAIAGL)/GaiaGL/vendor -I$(IMGUI)
LIB = -L$(GAIAGL)/GaiaGL -lGL -lGLEW -lglfw -lgaiagl

SAT: source.cpp $(GAIAGL)/GaiaGL/libgaiagl.a Collider.o
	g++ $^ -o $@ $(INC) $(LIB)

Collider.o: Collider.cpp Collider.hpp
	g++ $< -c -o $@ $(LIB) $(INC)