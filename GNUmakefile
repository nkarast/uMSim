# $Id: GNUmakefile,v 1.1 1999/01/07 16:05:40 gunter Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := mylar
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin


#include $(G4INSTALL)/config/architecture.gmk

#Add ROOT options for compilation
CPPFLAGS += `root-config --cflags` -stdlib=libstdc++
LDFLAGS  += `root-config --libs` -stdlib=libstdc++


#include $(G4INSTALL)/config/binmake.gmk

visclean:
        rm -f g4*.prim g4*.eps g4*.wrl
        rm -f .DAWN_*
