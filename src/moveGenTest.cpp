#include "moveGenerator.h"
#include "attackMaps.h"
#include "engine.h"
#include <iostream>

void printMoves(const std::vector<std::bitset<16>>& moves) {
    for (auto x : moves) {
        for (int i = 0; i < 2; i += 1) {
            int thing = (x.to_ulong() & 7) * 8;
            x = x >> 3;
            thing += (x.to_ulong() & 7);
            x = x >> 3;
            std::cout << thing << " ";
        }
        std::cout << (x.to_ullong() & 15) << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
}

void testStriaghtSlidingPiece()
{
    PieceSet ally_set;
    PieceSet enemey_set;
    std::bitset<64> occupied;

    ally_set.occupied |= 1ll << 7;
    ally_set.occupied |= 1ll << 15;
    ally_set.occupied |= 1ll << 3;

    // enemey_set.knights |= 1ll << 51;
    // enemey_set.pawns |= 1ll << 38;

    // enemey_set.occupied |= 1ll << 51 | 1ll << 38;
    occupied = enemey_set.occupied | ally_set.occupied;

    std::bitset<64> piece = 1ll << 7;

    std::vector<std::bitset<16>> moves = iteratePossibleMoves(
        piece, &enemey_set,
        &ally_set,
        generateStraightMoves,
        occupied
    );

    printMoves(moves);
}

void testDiagonalSlidingPiece()
{
    PieceSet ally_set;
    PieceSet enemey_set;
    std::bitset<64> occupied;

    ally_set.occupied |= 1ll << 17;
    ally_set.occupied |= 1ll << 56;

    enemey_set.knights |= 1ll << 28;
    enemey_set.pawns |= 1ll << 54;

    enemey_set.occupied |= 1ll << 54 | 1ll << 28;
    occupied = enemey_set.occupied | ally_set.occupied;

    std::bitset<64> piece = 1ll << 35;
    
    std::vector<std::bitset<16>>moves = iteratePossibleMoves( piece,
    &enemey_set,
    &ally_set,
    generateDiagonalMoves,
    occupied );


    printMoves(moves);
}


void testPawnOnePush()
{
    PieceSet ally_set;
    PieceSet enemey_set;
    std::bitset<64> occupied;

    ally_set.occupied |= 1ll << 15;

    enemey_set.knights |= 1ll << 47;
    // enemey_set.pawns |= 1ll << 54;

    enemey_set.occupied |= 1ll << 47;
    // enemey_set.occupied |= 1ll << 24;
    occupied = enemey_set.occupied | ally_set.occupied;

    std::bitset<64> piece = 1ll << 15;
    
    std::vector<std::bitset<16>>moves = iteratePossibleMoves( piece,
    &enemey_set,
    &ally_set,
    generatePawnMoves,
    &enemey_set , occupied  , 1);


    printMoves(moves);
}


void testPawnCapture()
{
    PieceSet ally_set;
    PieceSet enemey_set;
    std::bitset<64> occupied;

    ally_set.occupied |= 1ll << 25;

    enemey_set.doublePushPawns.set(18);
    // enemey_set.knights |= 1ll << 47;
    // enemey_set.pawns |= 1ll << 54;

    enemey_set.occupied |= 1ll << 26;
    // enemey_set.occupied |= 1ll << 24;
    occupied = enemey_set.occupied | ally_set.occupied;

    std::bitset<64> piece = 1ll << 25;
    
    std::vector<std::bitset<16>>moves = iteratePossibleMoves( piece,
    &enemey_set,
    &ally_set,
    generatePawnMoves,
    &enemey_set,
    occupied  , 1);   

    printMoves(moves);
}


void testPawnEnpessantCapture()
{
    PieceSet ally_set;
    PieceSet enemey_set;
    std::bitset<64> occupied;

    ally_set.occupied |= 1ll << 25;

    // enemey_set.doublePushPawns.set(18);
    // enemey_set.knights |= 1ll << 47;
    enemey_set.pawns |= 1ll << 18;

    enemey_set.occupied |= 1ll << 18;
    // enemey_set.occupied |= 1ll << 24;
    occupied = enemey_set.occupied | ally_set.occupied;

    std::bitset<64> piece = 1ll << 25;
    
    std::vector<std::bitset<16>>moves = iteratePossibleMoves( piece,
    &enemey_set,
    &ally_set,
    generatePawnMoves,
    &enemey_set,
    occupied  , 1);   

    printMoves(moves);

}


void testKingMoves()
{
    PieceSet ally_set;
    PieceSet enemey_set;
    std::bitset<64> occupied;

    ally_set.kings |= 1ll << 4;
    enemey_set.occupied |= 1ll << 12;
    ally_set.occupied |= 1ll << 3;

    

    occupied = enemey_set.occupied | ally_set.occupied;

    std::bitset<64> piece = 1ll << 4;
    
    std::vector<std::bitset<16>>moves = iteratePossibleMoves( piece,
    &enemey_set,
    &ally_set,
    generateKingMoves,
    occupied  ,
    0,
    false);   

    printMoves(moves);

}

void testKingCastle()
{
    
    PieceSet ally_set;
    PieceSet enemey_set;
    std::bitset<64> occupied;

    ally_set.kings |= 1ll << 4;
    ally_set.occupied |= 1ll << 1;

    
    ally_set.castleRooks.set(0);
    ally_set.castleRooks.set(7);



    occupied = enemey_set.occupied | ally_set.occupied;

    std::bitset<64> piece = 1ll << 4;
    
    std::vector<std::bitset<16>>moves = iteratePossibleMoves( piece,
    &enemey_set,
    &ally_set,
    generateKingMoves,
    occupied  ,
    ally_set.castleRooks
    ,false);   

    printMoves(moves);
}


void testKingInCheck()
{
    bitBoard *board = ( bitBoard *)malloc(sizeof(bitBoard));
    PieceSet ally_set;
    PieceSet enemey_set;
    std::bitset<64> occupied;
    ally_set.kings |= 1ll << 28;
    enemey_set.pawns |= 1ll << 35;
    occupied = enemey_set.occupied | ally_set.occupied;

    board->black = enemey_set;
    board->white = ally_set;

    std::bitset<64> king = 1ll << 28;
    
    bool res = kingInCheck(board , false);

    std::cout << res << '\n';

    free(board);
}

int main()
{
    
    generateAttackMaps();

    testKingInCheck();    


}