all:
	clang++ main.cc -I . -lsqlite3 -lboost_system -lboost_filesystem -std=c++11
