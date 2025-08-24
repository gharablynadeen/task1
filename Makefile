CXX      = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -I.
#LDFLAGS  = -lgtest -lgtest_main -pthread  

.PHONY: all run clean

all: a.exe

a.exe: main1.o FileManager.o
	$(CXX) $(CXXFLAGS) -o a.exe main1.o FileManager.o $(LDFLAGS)   

main1.o: main1.cpp FileManager.h
	$(CXX) $(CXXFLAGS) -c main1.cpp

FileManager.o: FileManager.cpp FileManager.h
	$(CXX) $(CXXFLAGS) -c FileManager.cpp

#test: unitTesting.o FileManager.o
#	$(CXX) $(CXXFLAGS) -o test.exe unitTesting.o FileManager.o $(LDFLAGS)

#unitTesting.o: unitTesting.cpp FileManager.h
#	$(CXX) $(CXXFLAGS) -c unitTesting.cpp

run: a.exe
	./a.exe

clean:
	- if exist a.exe del /Q a.exe
	- if exist *.o del /Q *.o
    #- if exist test.exe del /Q test.exe    

GTEST_DIR := third_party/googletest/googletest
GTEST_INC := $(GTEST_DIR)/include
GTEST_SRC := $(GTEST_DIR)/src/gtest-all.cc   # NOTE: no gtest_main.cc (you provide main1.cpp)

# keep your earlier CXX/CXXFLAGS lines; just add the include for gtest
CXXFLAGS += -I$(GTEST_INC)
# If MinGW warns about -pthread, just delete the next line:
LDFLAGS  += -pthread

# --- OS-specific helpers ---
ifeq ($(OS),Windows_NT)
  EXE := .exe
  # Create directory (cmd.exe style) - convert forward slashes to backslashes and quote it
  MKDIR_P = if not exist "$(subst /,\,$(1))" mkdir "$(subst /,\,$(1))"
  RUN = "$(1)"
else
  EXE :=
  MKDIR_P = mkdir -p "$(1)"
  RUN = ./$(1)
endif

TEST_BIN  := build/bin/unit_tests$(EXE)
# Make sure the file name matches your test file exactly:
TEST_SRCS := unitTesting_.cpp main1.cpp FileManager.cpp

$(TEST_BIN): $(TEST_SRCS) $(GTEST_SRC)
	@$(call MKDIR_P,$(@D))
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

.PHONY: tests test
tests: $(TEST_BIN)

test: $(TEST_BIN)
	@$(call RUN,$(TEST_BIN))

# Optional clean
.PHONY: clean-tests
clean-tests:
	- if exist "$(TEST_BIN)" del /Q "$(TEST_BIN)"