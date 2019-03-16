# requires boost to be installed
#
# on debian: apt install afl afl-clang libboost-system-dev clang-6.0
SRC:=bdecode.cpp
SRCDEPS:=bdecode.hpp
CLANG:=clang++-6.0
LIBS:=-lboost_system
CXXFLAGS:=-std=c++14 -g -O3 # -Wall -Wextra # slideware doesn't like warnings

.PHONY: all
all: reproducer_sanitizer reproducer_plain libfuzzer_plain libfuzzer_w_sanitizers afl_fast afl_plain
	@which afl-fuzz>/dev/null && echo "afl-fuzz found, all good!"

#reproducer
reproducer_sanitizer: reproducer.cpp $(SRC) $(SRCDEPS) 
	$(CXX) $(CXXFLAGS) -fsanitize=address $< $(SRC) $(LIBS) -o $@
reproducer_plain: reproducer.cpp $(SRC) $(SRCDEPS) 
	$(CXX) $(CXXFLAGS) $< $(SRC) $(LIBS) -o $@

#fuzzer target for llvm fuzzer (libfuzzer)
libfuzzer_plain : entrypoint_libfuzzer.cpp $(SRC) $(SRCDEPS) 
	$(CLANG) $(CXXFLAGS) -fsanitize=fuzzer $< $(SRC) $(LIBS) -o $@

.PHONY: run-libfuzzer-plain output-libfuzzer-plain
run-libfuzzer-plain: libfuzzer_plain output-libfuzzer-plain
	 ./libfuzzer_plain output-libfuzzer-plain

#fuzzer target for llvm fuzzer (libfuzzer), with sanitizers enabled
libfuzzer_w_sanitizers: entrypoint_libfuzzer.cpp $(SRC) $(SRCDEPS) 
	 $(CLANG) $(CXXFLAGS) -fsanitize=fuzzer,address,undefined $< $(SRC) $(LIBS) -o $@

.PHONY: run-libfuzzer-sanitizer
run-libfuzzer-sanitizer: libfuzzer_w_sanitizers output-libfuzzer-sanitizer
	 ./libfuzzer_w_sanitizers output-libfuzzer-sanitizer

#afl fast
afl_fast: entrypoint_afl_fast.cpp  $(SRC) $(SRCDEPS) 
	afl-clang-fast++ $(CXXFLAGS) $< $(SRC) $(LIBS) -o $@

#makes an empty corpus (afl refuses to start otherwise)
corpus:
	mkdir -p corpus
	echo "" > corpus/empty
output:
	mkdir -p $@
output-afl-fast:
	mkdir -p $@
output-afl-plain:
	mkdir -p $@
output-libfuzzer-plain:
	mkdir -p $@
output-libfuzzer-sanitizer:
	mkdir -p $@
.PHONY: run-afl-fast
run-afl-fast: afl_fast corpus output-afl-fast
	afl-fuzz -i corpus/ -o output-afl-fast -- ./afl_fast

#afl plain
afl_plain: entrypoint_afl_plain.cpp  $(SRC) $(SRCDEPS) 
	afl-g++ $(CXXFLAGS) $< $(SRC) $(LIBS) -o $@

.PHONY: run-afl-plain
run-afl-plain: afl_plain corpus output-afl-plain
	afl-fuzz -i corpus/ -o output-afl-plain -- ./afl_plain @@

.PHONY: clean
clean:
	rm -f afl_plain afl_fast libfuzzer_w_sanitizers libfuzzer_plain reproducer_sanitizer reproducer_plain


package.tar:
	tar cvf $@ *.cpp *.hpp makefile

