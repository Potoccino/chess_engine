
#include "bitBoard.h"

bitBoard* getStartingBitBoard()
{
    bitBoard* board = (bitBoard *)malloc(sizeof(bitBoard));

    for(int i = 48 ; i < 56 ; i += 1)
    {
        board->black.pawns |= 1ll << i;
        board->white.pawns |= 1ll << (i - 40);
    }

    board->white.rooks = 1 | (1 << 7);
    board->black.rooks = (1LL << 56)  | (1LL << 63);

    board->white.knights = (1 << 1) | (1 << 6);
    board->black.knights = (1LL << 57)  | (1LL << 62);

    board->white.bishops = (1 << 2) | (1 << 5);
    board->black.bishops = (1LL << 58) | (1LL << 61);

    board->white.queens = 1 << 3;
    board->black.queens = 1LL << 59;

    board->white.kings = 1 << 4;
    board->black.kings = 1LL << 60;

    board->white.occupied = board->white.rooks | board->white.knights | 
                            board->white.bishops | board->white.queens | 
                            board->white.kings | board->white.pawns;

    board->black.occupied = board->black.rooks | board->black.knights | 
                            board->black.bishops | board->black.queens | 
                            board->black.kings | board->black.pawns;

    board->black.castleRooks.set(56);
    board->black.castleRooks.set(63);

    board->white.castleRooks.set(0);
    board->white.castleRooks.set(7);

    return board;
}

