SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include
BIN_DIR := .

EXE := $(BIN_DIR)/test.bin

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY : clean all test_1 test_2, test_3

# -MMD et -MP sont importants pour generer les dépendances .hpp automatiquement.
CPPFLAGS := -I $(INC_DIR) -std=c++11 -MMD -MP
CFLAGS := -Wall
CPP := g++ $(CPPFLAGS) $(CFLAGS)

all: $(EXE)
	$(EXE)
$(EXE): $(OBJ)
	$(CPP) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CPP) -c $< -o $@

# Si le dossier OBJ_DIR n'existe pas/plus, on le cree
$(OBJ_DIR):
	mkdir -p $@

clean:
	$(RM) -r $(OBJ_DIR) $(EXE)

# Tests
test: test_1 test_2 test_3
test_1:
	$(EXE) graphe
test_2:
	$(EXE) garbage_collector
test_3:
	$(EXE) kruskal

# - permet d'ignorer les erreurs
-include $(OBJ:.o=.d)
