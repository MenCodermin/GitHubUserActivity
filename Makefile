########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall -Isrc/include
LDFLAGS = -lcurl

# Makefile settings - Can be customized.
APPNAME = myapp
EXT = .cpp
SRCDIR = src
OBJDIR = obj

############## Do not change anything from here downwards! #############
SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

.PHONY: all clean cleandep cleanw cleandepw

# Build the application
all: $(APPNAME)

# Link the final application
$(APPNAME): $(OBJ)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Ensure the obj directory exists
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# Create dependency rules
%.d: $(SRCDIR)/%$(EXT)
	@$(CC) $(CXXFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Include dependencies
-include $(DEP)

# Build object files
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT) | $(OBJDIR)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
clean:
	rm -f $(OBJ) $(DEP) $(APPNAME)

# Cleans only dependency files
cleandep:
	rm -f $(DEP)

#################### Cleaning rules for Windows OS #####################
# Cleans complete project
cleanw:
	del $(OBJ) $(DEP) $(APPNAME).exe

# Cleans only dependency files
cleandepw:
	del $(DEP)
