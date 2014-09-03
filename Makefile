.PHONY: clean, mrproper

PATHOFOBJ = obj/
CXX = g++
EXE = JVTerm.exe
CFLAGS = -std=c++11 -Wall -Wextra -pedantic
LIBFLAG = -lncursesw -lcurlpp -lcurl -lboost_regex
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
PATHOBJ = $(addprefix $(PATHOFOBJ), $(OBJ))

all: $(EXE)

$(EXE): $(PATHOBJ)
	$(CXX) $^ -o $@ $(CFLAGS) $(LIBFLAG) -L/home/werck/lib/curlpp/lib/

$(PATHOFOBJ)%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS) -I/home/werck/lib/curlpp/include/

clean:
	rm -f $(PATHOFOBJ)*.o

mrproper: clean
	rm -f $(EXE)
