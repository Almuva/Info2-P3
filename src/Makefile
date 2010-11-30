HOME = ..

TARGETS = $(PRUEBA) 

OBJECTS = $(OBJPRUEBA) 


########
# Mesa #
########
#MesaIncDir = /usr/local/include/GL -DVTK_USE_OGLR
#MesaLibs = -lGL -lXext -lXt -lSM -lICE -lX11 -lm



###############################
# esto es general

CPP = g++ 

incdir1 = $(HOME)/inc
incdir2 = /usr/include/ImageMagick


SRC= $(HOME)/src
OBJ = $(HOME)/obj
bindir=$(HOME)/bin


INCLUDES = -I$(incdir2) -I$(incdir1)



CPPFLAGS = -g -pedantic -Wall

LIBS = -DHAVE_CONFIG_H -D_REENTRANT -D_FILE_OFFSET_BITS=64 -I/usr/include/ImageMagick -I/X11 -L/usr/lib -L/usr/X11R6/lib -L../lib/ -lMagick++ -ltiff -ljpeg -lpng -lz -lpthread -lm -ldl -lxml2




##########################################
# PRUEBA

PRUEBA = prueba
OBJPRUEBA = main_p3.o Imagen.o inout.o utiles.o mg.o seam_finding.o quilting.o transfer.o

installprueba: $(bindir)/$(PRUEBA)
$(bindir)/prueba: $(OBJ)/prueba
	-rm $(bindir)/prueba
	cp -p $(OBJ)/prueba $(bindir)/prueba

prueba: $(OBJ)/prueba

$(OBJ)/prueba: $(addprefix $(OBJ)/, $(OBJPRUEBA))
	$(CPP) $(INCLUDES) $(CPPFLAGS) -o $(addprefix $(OBJ)/,$(PRUEBA)) $(addprefix $(OBJ)/, $(OBJPRUEBA)) -lpthread $(LIBS) $(MesaLibs)


#########################################
# reglas generales


$(OBJ)/%.o : %.cpp
	$(CPP) -c $(INCLUDES) $(CPPFLAGS)  $< -o $@


.PHONY: prueba

all: directorios $(TARGETS)

clean:
	-rm $(TARGETS)
	-rm $(OBJ)/*.o

cleanall: clean

build: clean all

install: $(subst $(OBJ),$(bindir),$(TARGETS))

directorios:
	@if [ ! -d $(bindir) ]; then mkdir $(bindir); fi
	@if [ ! -d $(OBJ) ]; then mkdir $(OBJ); fi



