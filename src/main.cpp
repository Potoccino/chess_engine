#include <iostream>
#include "bitBoard.h"
#include "pieces.h"
#include <regex>
#include <cassert>
#include "attackMaps.h"
#include "engine.h"

const std::bitset<16> INVALID_INPUT = 0;


void printMove(std::bitset<16> move) {
    int thing = (move.to_ulong() & 63);
    std::cout << thing << ' ';
    move = move >> 6;
    thing = (move.to_ulong() & 63);
    std::cout << thing << ' ';
    move = move >> 6;
    std::cout << (move.to_ullong() & 15) << ' ';
    std::cout << '\n';
}


void printMoves(const std::vector<std::bitset<16>>& moves) {
    for (auto x : moves) {
        printMove(x);
    }
    std::cout << '\n';
}



// a move is a 16 bit bitset
// 6 bits for the source
// 6 bits for the destination
// 3 bits in case of a promotion
// 1 bit for the color
std::bitset<16> read_move(bitBoard* bitBoard, std::vector<std::bitset<16>> & moves ,bool turn)
{
    std::string move;
    std::cin >> move;

    bool match = std::regex_match(move, std::regex("[a-h][1-8][a-h][1-8][rbkq]?"));

    if (!match)
    {
        return INVALID_INPUT;
    }

    u_short source_index , destination_index ;
    source_index  = (move[0] - 'a') + 8 * (move[1] - '1');
    destination_index = (move[2] - 'a') + 8 * (move[3] - '1');

    char promotion_char = move.length() == 4 ? ' ' : move.back();
    std::bitset<16> promotion_piece;

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
        promotion_piece = BISHOP_PROMOTED;
    }
    else if (promotion_char == 'q')
    {
        promotion_piece = QUEEN_PROMOTED;
    }

    std::bitset<16> final_move;
    final_move |= source_index;
    final_move |= destination_index << 6; 
    final_move |= promotion_piece;

    assert(std::find(moves.begin(), moves.end(), final_move) != moves.end());

    return final_move;
}

void run(bitBoard *bitboard, bool turn)
{
    std::vector<std::bitset<16>> moves = generateMoves(*bitboard, turn);

    std::bitset<16> move = read_move(bitboard, moves, turn);

    if (move == INVALID_INPUT)
    {
        std::cout << "Invalid move\n";
        return;
    }

    std::pair <std::bitset<64>* , std::bitset<64>*> affectedBitsets = makeMove(bitboard, turn, move);
    if(kingInCheck(bitboard, turn))
    {
        unMakeMove(bitboard, turn, move, affectedBitsets);
        std::cout << "Check\n";
        return;
    }
}



int main()
{
    generateAttackMaps();
    bitBoard *bitboard = getStartingBitBoard();
    run(bitboard, 0);   

}
