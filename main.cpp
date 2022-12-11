
#include <QtWidgets>

#include "hexominos.h"
#include "puzzle_book.h"
#include "shape_set.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Hexominos");

    ShapeSet* shape_set = new ShapeSet;
    PuzzleBook*puzzle_book = new PuzzleBook(PUZZLE_BOOK_FILE_NAME);
    Hexominos game(shape_set, puzzle_book);
    game.show();

    int res = app.exec();
    puzzle_book->save(PUZZLE_BOOK_FILE_NAME);
    delete puzzle_book;
    delete shape_set ;
    return res;
}
