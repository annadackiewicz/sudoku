field_test.o:	Field.hpp Field.cpp Field_test.cpp
		g++ Field.hpp Field.cpp Field_test.cpp -o field_test

board_test.o:	Field.hpp Field.cpp Board.hpp Board.cpp Board_test.cpp Utils.hpp
		g++ Field.hpp Field.cpp Board.hpp Board.cpp Board_test.cpp Utils.hpp -o board_test
