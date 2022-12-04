all:
	@$(MAKE) -C ./bin/ MAKEFLAGS=

setup:
	@cmake -S src -B bin

run:
	@./bin/cmake-project
