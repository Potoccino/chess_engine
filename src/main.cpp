#include <iostream>
#include "bitBoard.h"
#include "pieces.h"
#include <regex>

const std::bitset<16> INVALID_INPUT = 0;



// a move is a 16 bit bitset
// 6 bits for the source
// 6 bits for the destination
// 3 bits for the taken piece
// 1 bit for the color
std::bitset<16> read_move(const BitBoard bitBoard, bool turn)
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
    ushort promotion_piece;

    if (promotion_char == 'r')
    {
        promotion_piece = ROOK_PROMOTED;
    }
    else if (promotion_char == 'n')
    {
        promotion_piece = KNIGHT_PROMOTED;
    }
    else if (promotion_char == 'b')
    {
        promotion_char = BISHOP_PROMOTED;
    }
    else if (promotion_char == 'q')
    {
        promotion_piece = QUEEN_PROMOTED;
    }
    else
    {
        promotion_piece = NOTHING_PROMOTED;
    }

    std::bitset<16> final_move;

    u_short taken_piece = NOTHING_TAKEN;
    const std::bitset<64> *piece_set = turn ? bitBoard.white_pieces : bitBoard.black_pieces;
    for (int i = 0; i < 6; i += 1)
    {
        if (i == 4)
        {
            // skip all posistions array
            continue;
        }

        if (piece_set[i].test(destination_index))
        {
            taken_piece = i;
            break;
        }
    }

    final_move |= source_index;
    final_move |= destination_index << 6;
    final_move |= taken_piece << 12;
    final_move |= turn << 15;

    return final_move;
}

void run(BitBoard bitboard, bool turn)
{

    std::bitset<16> move = read_move(bitboard, turn);
    if (move == INVALID_INPUT)
    {
        std::cout << "BAD MOVE INPUT" << '\n';
        exit(-1);
    }

    std::cout << move << '\n';
}

int main()
{

    BitBoard board = BitBoard();
    std::cout << ConvertBoardToFENstring(board) << '\n';
    // run(board , true);
    return 0;
}