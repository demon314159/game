
#include <QtWidgets>

#include "hexominos.h"
#include "puzzle_book.h"
#include "full_set.h"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    app.setApplicationName("Hexominos");

    FullSet* full_set = new(FullSet);
    PuzzleBook*puzzle_book = new PuzzleBook(PUZZLE_BOOK_FILE_NAME);
    Hexominos game(full_set, puzzle_book);
    game.show();

    int res = app.exec();
    puzzle_book->save(PUZZLE_BOOK_FILE_NAME);
    delete(puzzle_book);
    delete(full_set);
    return res;
}
