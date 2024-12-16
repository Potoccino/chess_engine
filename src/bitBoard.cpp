#include <cstdint>

struct BitBoard{
    uint64_t black_pieces;
    uint64_t white_pieces;
    uint64_t black_pawn;
    uint64_t black_rook;
    uint64_t black_knight;
    uint64_t black_bishop;
    uint64_t black_queen;
    uint64_t black_king;
    uint64_t white_pawn;
    uint64_t white_rook;
    uint64_t white_knight;
    uint64_t white_bishop;
    uint64_t white_queen;
    uint64_t white_king;

    BitBoard(){
        for(short i = 48 ; i < 56 ; i += 1){
            black_pawn |= 1LL << i;
            white_pawn |= 1LL << (i - 40);
        }

        white_rook = 1 | (1 << 7);
        black_rook = (1LL << 56)  | (1LL << 63);

        white_knight = (1 << 1) || (1 << 6);
        black_knight = (1LL << 57)  | (1LL << 62);

        white_bishop = (1 << 2) | (1 << 5);
        black_bishop = (1LL << 58) | (1LL << 61);

        white_queen = 1 << 3;
        black_queen = 1LL << 59;

        white_king = 1 << 4;
        black_king = 1LL << 60;

        black_pieces = black_bishop | black_king | black_knight | black_rook | black_queen | black_pawn;
        white_pieces = white_bishop | white_king | white_knight | white_rook | white_queen | white_pawn;
    }

};