CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

OUT_DIR := out
TARGETS := 1 2 3 4 5

.PHONY: $(TARGETS) all clean

all: $(addprefix $(OUT_DIR)/,$(TARGETS))

$(TARGETS):
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT_DIR)/$@ _$@/main.cpp
	@echo "Running $(OUT_DIR)/$@..."
	@./$(OUT_DIR)/$@

$(OUT_DIR)/%: _%/main.cpp
	@mkdir -p $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(OUT_DIR)
