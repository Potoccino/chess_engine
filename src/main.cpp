#include <iostream>
#include "bitBoard.h"
#include "pieces.h"
#include <regex>

const std::tuple<u_short, u_short, promotion_piece> INVALID_INPUT = {0, 0, promotion_piece::NO_PROMOTION};

std::tuple<short, short, promotion_piece> read_move()
{
    std::string move;
    std::cin >> move;

    bool match = std::regex_match(move, std::regex("[a-h][1-8][a-h][1-8][rbkq]?"));

    if (!match)
    {
        return INVALID_INPUT;
    }

    u_short source_index = 0, destination_index = 0;

    source_index = (move[1] - '1') << 3 + (move[0] - 'a');
    destination_index = (move[3] - '1') << 3 + (move[2] - 'a');

    char promotion_char = move.length() == 4 ? ' ' : move.back();
    promotion_piece promotion_piece;

    if (promotion_char == 'r')
    {
        promotion_piece = promotion_piece::ROOK;
    }
    else if (promotion_char == 'n')
    {
        promotion_piece = promotion_piece::KNIGHT;
    }
    else if(promotion_char == 'b')
    {
        promotion_char = promotion_piece::BISHOP;
    }
    else if (promotion_char == 'q')
    {
        promotion_piece = promotion_piece::QUEEN;
    }
    else
    {
        promotion_piece = promotion_piece::NO_PROMOTION;
    }
    
    return {source_index , destination_index , promotion_piece};
}

void run()
{
    // normal move detection
    // regex("[RNBKQrnbkq]?[a-h]?[1-8]?[a-h][1-8]([+#])?")

    // move with takes
    // regex("[RNBKQrnbkq]?[a-h]?[1-8]?x[a-h][1-8]([+#])?")
}

int main()
{

    BitBoard board = BitBoard();
    return 0;
}