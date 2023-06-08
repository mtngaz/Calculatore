# WWW = -Werror -Wextra -Wall -g
# # WWW = -g -Werror -Wextra -Wall -fsanitize=address
# G = gcc
# OS = $(shell uname)

# ifeq ($(OS), Linux)
# 	FLAGS = -lcheck -pthread -lrt -lm -lsubunit
# 	BD = cd build;./Smart_Calc
# 	DEL = ./Smart_Calc 
# else
# 	FLAGS = -lcheck
# 	BD = open build/Smart_Calc.app/MacOS/Smart_Calc 
# 	DEL = Smart_Calc.app
# endif


# all: uninstall clean install

# build:
# 	mkdir -p build
# 	cd build && cmake ..
# 	cd build && make


# # install: clean
# # 	cd build;qmake Smart_Calc.pro
# # 	make -C build
# # 	$(BD)

# uninstall:
# 	rm -rf build/$(DEL) moc_mainwindow.cpp moc_qcustomplot.cpp
# 	rm -rf build/moc_mainwindow.cpp
# 	rm -rf build/moc_qcustomplot.cpp
# 	rm -rf build/moc_predefs.h
# 	rm -rf build/ui_mainwindow.h

# test: clean
# 	$(G) $(WWW) Calc/*.c $(FLAGS) -o test
# 	./test

# clean: uninstall
# 	rm -rf build/*.o *.a *.gch *.gcno *.gcna *.gcda *.info *.dSYM test test_html .qmake.stash
# 	rm -rf build/Smart_Calc.pro.user build/.qmake.stash  build/Makefile

# dvi: 
# 	open index.html

# dist:
# 	tar -cf SmartCalc_v1.0.tar *.h build Calc Smart_Calc index.html

# gcov_report: clean
# 	$(G) $(WWW) -fprofile-arcs -ftest-coverage Calc/*.c $(FLAGS) -o test
# 	./test
# 	lcov -t "test_html" -o unit_test.info -c -d .
# 	genhtml -o test_html unit_test.info
# 	open test_html/index.html

# leaks:
# 	leaks -atExit -- ./test

# valgrind:
# 	valgrind --tool=memcheck --leak-check=yes ./test

# style_i:
# 	clang-format -style=google -i Calc/*.c *.h

# style_n:
# 	clang-format -style=google -n Calc/*.c *.h
WWW = -Werror -Wextra -Wall -g
# WWW = -g -Werror -Wextra -Wall -fsanitize=address
G = gcc
OS = $(shell uname)

ifeq ($(OS), Linux)
    FLAGS = -lcheck -pthread -lrt -lm -lsubunit
    BD = cd bin;./Smart_Calc
    DEL = ./Smart_Calc 
else
    FLAGS = -lcheck
    BD = open bin/Smart_Calc.app/MacOS/Smart_Calc 
    DEL = Smart_Calc.app
endif

# Новая переменная для хранения имени директории для сборки
BUILD_DIR = build

all: uninstall clean install

# Измененное правило сборки для создания директории `bin` и сборки в нее
build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make
	mkdir -p bin
	cp $(BUILD_DIR)/Smart_Calc bin/

# Измененное правило очистки
clean: uninstall
	rm -rf $(BUILD_DIR)/*.o *.a *.gch *.gcno *.gcna *.gcda *.info *.dSYM test test_html .qmake.stash
	rm -rf $(BUILD_DIR)/Smart_Calc.pro.user $(BUILD_DIR)/.qmake.stash  $(BUILD_DIR)/Makefile
	rm -rf bin/*

# Измененное правило удаления установленных файлов
uninstall:
	rm -rf $(BUILD_DIR)/$(DEL) moc_mainwindow.cpp moc_qcustomplot.cpp
	rm -rf $(BUILD_DIR)/moc_mainwindow.cpp
	rm -rf $(BUILD_DIR)/moc_qcustomplot.cpp
	rm -rf $(BUILD_DIR)/moc_predefs.h
	rm -rf $(BUILD_DIR)/ui_mainwindow.h

test: clean
	$(G) $(WWW) Calc/*.c $(FLAGS) -o test
	./test

dvi: 
	open index.html

dist:
	tar -cf SmartCalc_v1.0.tar *.h build Calc Smart_Calc index.html

gcov_report: clean
	$(G) $(WWW) -fprofile-arcs -ftest-coverage Calc/*.c $(FLAGS) -o test
	./test
	lcov -t "test_html" -o unit_test.info -c -d .
	genhtml -o test_html unit_test.info
	open test_html/index.html

leaks:
	leaks -atExit -- ./test

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./test

style_i:
	clang-format -style=google -i Calc/*.c *.h

style_n:
	clang-format -style=google -n Calc/*.c *.h
