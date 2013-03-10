# Compiler to use
CC     = gcc
CPPC   = g++
LEX    = flex
YACC   = bison -y
LINKER = g++

# Directories to store stuff (relative to makefile) 
SRCDIR = src
GENDIR = obj
OBJDIR = obj
BINDIR = bin
TESTDIR = test
LIBDIR = lib
INCLUDEDIR = include
LIBRARIES = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lGL

CFLAGS   = -O3 -Wall -I$(INCLUDEDIR) -I$(GENDIR) -I$(SRCDIR)
CPPFLAGS = -O3 -g -Wall -I$(INCLUDEDIR) -I$(GENDIR) -I$(SRCDIR)
LFLAGS   = 
YFLAGS   = -d
LDFLAGS  = -O3 -lm -g -L$(LIBDIR) $(LIBRARIES)

# To allow linking of multiple projects we assume files matching *_main.* are main project files.
# Files sharing the same prefix (before _main.*) are considered part of the same project.
# Everything else is a dependency of all projects (unless ignored separately).
# All projects are compiled with the same options
MAINS_LIST = $(wildcard $(SRCDIR)/*_main.*)
PROJECTS = $(patsubst %_main,%,$(basename $(notdir $(MAINS_LIST))))
PROJECT_TARGETS = $(addprefix $(BINDIR)/, $(PROJECTS))
PROJECT_SOURCES = $(foreach PROJECT,$(PROJECTS),$(wildcard $(SRCDIR)/$(PROJECT)*))

PROJECT_C_SOURCES = $(filter %.c, $(PROJECT_SOURCES))
PROJECT_CPP_SOURCES = $(filter %.cpp, $(PROJECT_SOURCES))
PROJECT_LEX_SOURCES = $(filter %.l, $(PROJECT_SOURCES))
PROJECT_YACC_SOURCES = $(filter %.y, $(PROJECT_SOURCES))

PROJECT_OBJECTS =  $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(notdir $(PROJECT_C_SOURCES))))
PROJECT_OBJECTS += $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o,$(notdir $(PROJECT_CPP_SOURCES))))
PROJECT_OBJECTS += $(addprefix $(OBJDIR)/, $(patsubst %.l,%.o,$(notdir $(PROJECT_LEX_SOURCES))))
PROJECT_OBJECTS += $(addprefix $(OBJDIR)/, $(patsubst %.y,%.o,$(notdir $(PROJECT_YACC_SOURCES))))

# Files in source directory to not compile
IGNORE_LIST = 
IGNORE = $(addprefix $(SRCDIR)/, $(IGNORE_LIST)) $(PROJECT_SOURCES)

ALL_C_SOURCES = $(wildcard $(SRCDIR)/*.c)
C_SOURCES = $(filter-out $(IGNORE), $(ALL_C_SOURCES))

ALL_CPP_SOURCES = $(wildcard $(SRCDIR)/*.cpp)
CPP_SOURCES = $(filter-out $(IGNORE), $(ALL_CPP_SOURCES))

ALL_LEX_SOURCES = $(wildcard $(SRCDIR)/*.l)
LEX_SOURCES = $(filter-out $(IGNORE), $(ALL_LEX_SOURCES))

ALL_YACC_SOURCES = $(wildcard $(SRCDIR)/*.y)
YACC_SOURCES = $(filter-out $(IGNORE), $(ALL_YACC_SOURCES))
YACC_GENERATED = $(addprefix $(GENDIR)/, $(subst .y,.c, $(notdir $(YACC_SOURCES)))) 

OBJECTS =  $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(notdir $(C_SOURCES))))
OBJECTS += $(addprefix $(OBJDIR)/, $(patsubst %.cpp,%.o,$(notdir $(CPP_SOURCES))))
OBJECTS += $(addprefix $(OBJDIR)/, $(patsubst %.l,%.o,$(notdir $(LEX_SOURCES))))
OBJECTS += $(addprefix $(OBJDIR)/, $(patsubst %.y,%.o,$(notdir $(YACC_SOURCES))))


# Targets to make 
all : $(PROJECT_TARGETS)

$(OBJDIR)/%.o : $(GENDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(GENDIR)/%.cpp
	$(CPPC) $(CPPFLAGS) -c $< -o $@

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CPPC) $(CPPFLAGS) -c $< -o $@

# By depending on yacc generated files, we know that the header files have been created
$(GENDIR)/%.c : $(SRCDIR)/%.l $(YACC_GENERATED)
	$(LEX) -t $(LFLAGS) $< > $@

$(GENDIR)/%.c : $(SRCDIR)/%.y
	$(YACC) $(YFLAGS) $< && mv -f y.tab.c $@ && mv -f y.tab.h $(@:.c=.h)

# Can't find a cleaner way to do this, I'd need to run a function on the 
# '%' in the prerequisite list, but functions get expanded before that % takes on a value.
define define_project_rules
$(BINDIR)/$(1) : $(filter $(OBJDIR)/$(1)%, $(PROJECT_OBJECTS)) $(OBJECTS)
	$$(LINKER) $$(LDFLAGS) -o $$@ $$^
endef

$(foreach project,$(PROJECTS),$(eval $(call define_project_rules,$(project))))

# Runs test script
.PHONY : test
test :
	$(TESTDIR)/run_tests.sh

# Deletes binary and object files
.PHONY : clean
clean :
	\rm -f $(OBJDIR)/*.o $(PROJECT_TARGETS)
