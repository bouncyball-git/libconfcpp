#
# Compiler flags
#
CXX      = g++
CXXFLAGS = -Wall -Werror -Wextra

#
# Project files
#
SRCS = libconfc_test.cpp libconfc.cpp
OBJS = $(SRCS:.cpp=.o)
EXE  = libconfc_test

#
# Debug build settings
#
DBGDIR = debug
DBGEXE = $(DBGDIR)/$(EXE)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGCXXFLAGS = -g -O0 -DDEBUG

#
# Release build settings
#
RELDIR = release
RELEXE = $(RELDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCXXFLAGS = -O3 -DNDEBUG

.PHONY: all clean debug prep release remake

# Default build
all: prep release debug

#
# Debug rules
#
debug: $(DBGEXE)
$(DBGEXE): $(DBGOBJS)
	$(CXX) -o $(DBGEXE) $^
$(DBGDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(DBGCXXFLAGS) -o $@ $<

#
# Release rules
#
release: $(RELEXE)
	strip $(RELEXE)
$(RELEXE): $(RELOBJS)
	$(CXX) -o $(RELEXE) $^
$(RELDIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(RELCXXFLAGS) -o $@ $<

#
# Other rules
#
prep:
	@mkdir -p $(DBGDIR) $(RELDIR)

remake: clean all

clean:
	rm -f $(RELEXE) $(RELOBJS) $(DBGEXE) $(DBGOBJS) $(RELDIR)/modded.conf $(DBGDIR)/modded.conf
