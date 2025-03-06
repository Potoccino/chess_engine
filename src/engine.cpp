
#include "moveGenerator.h"
#include "attackMaps.h"



std::vector<std::bitset<16>>  generateMoves(bitBoard bitboard, bool turn)
{
    PieceSet white = bitboard.white;
    PieceSet black = bitboard.black;
    std::vector<std::bitset<16>> moves , movesPiece;
    if(turn == 0)
    {
        movesPiece = iteratePossibleMoves(white.rooks, &white , &black , generateStraightMoves,
            white.occupied | black.occupied );
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());
        
        movesPiece = iteratePossibleMoves(white.knights , &white , &black , generateKnightMoves);
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end()); 

        movesPiece = iteratePossibleMoves(white.bishops , &white , &black , generateDiagonalMoves,
            white.occupied | black.occupied ); 
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end()); 


        movesPiece = iteratePossibleMoves(white.queens , &white , &black , generateDiagonalMoves,
            white.occupied | black.occupied );
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());

        movesPiece = iteratePossibleMoves(white.queens , &white , &black , generateStraightMoves,
            white.occupied | black.occupied ); 
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());

        movesPiece = iteratePossibleMoves(white.kings , &white , &black , generateKingMoves,
            white.occupied | black.occupied , white.castleRooks ,0);

        movesPiece = iteratePossibleMoves(white.pawns , &white , &black , generatePawnMoves,
            &black , white.occupied | black.occupied , 0);
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());
    }
    else
    {
        movesPiece = iteratePossibleMoves(black.rooks , &black , &white , generateStraightMoves,
            white.occupied | black.occupied );
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());

        movesPiece = iteratePossibleMoves(black.knights , &black , &white , generateKnightMoves);
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());

        movesPiece = iteratePossibleMoves(black.bishops  , &black , &white , generateDiagonalMoves,
            white.occupied | black.occupied ); 
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end()); 

        movesPiece = iteratePossibleMoves(black.queens , &black, &white  , generateDiagonalMoves,
            white.occupied | black.occupied );  
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());

        movesPiece = iteratePossibleMoves(black.queens , &black , &white , generateStraightMoves,
            white.occupied | black.occupied );
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());

        movesPiece = iteratePossibleMoves(black.kings , &black , &white , generateKingMoves,
            white.occupied | black.occupied , black.castleRooks ,0);    
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());

        movesPiece = iteratePossibleMoves(black.pawns  , &black, &white  , generatePawnMoves,
            &white , white.occupied | black.occupied , 1);
        moves.insert(moves.end() , movesPiece.begin() , movesPiece.end());
    }

    return moves;
}



std::bitset<64>* getAffectedBitSet(PieceSet &PieceSet , size_t index)
{
    if(PieceSet.rooks.test(index))
    {
        return &PieceSet.rooks;
    }
    else if(PieceSet.knights.test(index))
    {
        return &PieceSet.knights;
    }
    else if(PieceSet.bishops.test(index))
    {
        return &PieceSet.bishops;
    }
    else if(PieceSet.queens.test(index))
    {
        return &PieceSet.queens;
    }
    else if(PieceSet.kings.test(index))
    {
        return &PieceSet.kings;
    }
    else if(PieceSet.pawns.test(index))
    {
        return &PieceSet.pawns;
    }
    return nullptr;
    
}


bool kingInCheck(bitBoard * bitBoard , bool turn)
{
    PieceSet * ally = turn ? &bitBoard->black : &bitBoard->white;
    PieceSet * enemy = turn ? &bitBoard->white : &bitBoard->black;

    std::bitset<64> king = ally->kings;
    size_t kingIndex = king._Find_first();

    std::bitset<64> knightAttacks = knightJumps[kingIndex] & enemy->knights;
    if(knightAttacks.any())
    {
        return true;
    }

    std::bitset<64> onSameFileAndRank;
    std::bitset<64> onSameDiagonal;
    onSameFileAndRank |= straightRays[0][kingIndex] & (enemy->rooks | enemy->queens);
    onSameFileAndRank |= straightRays[1][kingIndex] & (enemy->rooks | enemy->queens);
    onSameFileAndRank |= straightRays[2][kingIndex] & (enemy->rooks | enemy->queens);
    onSameFileAndRank |= straightRays[3][kingIndex] & (enemy->rooks | enemy->queens);

    size_t index , size = onSameFileAndRank.size();
    while (( index = onSameFileAndRank._Find_first()) != size)
    {
        std::bitset<64> attacks = generateStraightMoves(index , ally->occupied | enemy->occupied) & king;
        if(attacks.any())
        {
            return true;
        }  
        onSameFileAndRank.flip(index);
    }



    onSameDiagonal |= diagonalRays[0][kingIndex] & (enemy->bishops | enemy->queens);
    onSameDiagonal |= diagonalRays[1][kingIndex] & (enemy->bishops | enemy->queens);
    onSameDiagonal |= diagonalRays[2][kingIndex] & (enemy->bishops | enemy->queens);
    onSameDiagonal |= diagonalRays[3][kingIndex] & (enemy->bishops | enemy->queens);

    size = onSameDiagonal.size();
    while((index = onSameDiagonal._Find_first()) != size)
    {
        std::bitset<64> attacks = generateDiagonalMoves(index , ally->occupied | enemy->occupied) & king;
        if(attacks.any())
        {
            return true;
        }
        onSameDiagonal.flip(index);
    }
    
    size_t attackersDirection = (turn ? -8 : 8) + kingIndex;
    if(attackersDirection < 0 || attackersDirection > 63)
    {
        return false;
    }

    if(enemy->pawns.test(attackersDirection + 1) || enemy->pawns.test(attackersDirection - 1))
    {
        return true;
    }
    {
        return false;
    }

}


std::pair <std::bitset<64>* , std::bitset<64>*>  makeMove(bitBoard * bitBoard , bool turn , std::bitset<16> move)
{
    PieceSet * ally = turn ? &bitBoard->black : &bitBoard->white;
    PieceSet * enemy = turn ? &bitBoard->white : &bitBoard->black;

    size_t srcIndex = move.to_ulong() & 0b111111;
    size_t destIndex = (move.to_ulong() >> 6) & 0b111111;

    std::bitset<64> *srcPiece = getAffectedBitSet(*ally , srcIndex);
    std::bitset<64> *destPiece = getAffectedBitSet(*enemy , destIndex);

    srcPiece->reset(srcIndex);
    srcPiece->set(destIndex);
    ally->occupied.reset(srcIndex);
    ally->occupied.set(destIndex);

    if(destPiece != nullptr)
    {
        destPiece->reset(destIndex);
        enemy->occupied.reset(destIndex);
    }

    return make_pair(srcPiece , destPiece);

}



void unMakeMove(bitBoard * bitBoard , bool turn , std::bitset<16> move , std::pair <std::bitset<64>* , std::bitset<64>*> affectedBitsets)
{
    PieceSet * ally = turn ? &bitBoard->black : &bitBoard->white;
    PieceSet * enemy = turn ? &bitBoard->white : &bitBoard->black;

    size_t srcIndex = move.to_ulong() & 0b111111;
    size_t destIndex = (move.to_ulong() >> 6) & 0b111111;

    std::bitset<64> *destPiece = getAffectedBitSet(*ally , destIndex);

    ally->occupied.reset(destIndex);
    ally->occupied.set(srcIndex);
    affectedBitsets.first->set(srcIndex);
    affectedBitsets.first->reset(destIndex);


    if(affectedBitsets.second != nullptr)
    {
        affectedBitsets.second->set(destIndex);
        enemy->occupied.set(destIndex);
    }
}


