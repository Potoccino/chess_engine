
#include<vector>
#include<bitset>
#include "bitBoard.h"


std::vector<std::bitset<16>>  generateMoves(bitBoard , bool );

std::pair <std::bitset<64>* , std::bitset<64>*>  makeMove(bitBoard * bitBoard , bool turn , std::bitset<16> move);

bool kingInCheck(bitBoard * bitBoard , bool turn);

void unMakeMove(bitBoard * bitBoard , bool turn , std::bitset<16> move , std::pair <std::bitset<64>* , std::bitset<64>*> affectedBitsets);