# include <cstdint>
# include <bitset>


// 0 is the rooks
// 1 is the knights
// 2 is the bishops
// 3 is the queens
// 4 is the map of occupied positions
// 5 is the pawns
// 6 is the kings

struct PieceSet
{
    std::bitset<64> rooks;
    std::bitset<64> knights;
    std::bitset<64> bishops;
    std::bitset<64> queens;
    std::bitset<64> kings;
    std::bitset<64> pawns;
    std::bitset<64> occupied;
    std::bitset<64> doublePushPawns;
    std::bitset<64> castleRooks;
};


struct BitBoard
{       
    PieceSet white;
    PieceSet black;


    BitBoard()
    {
        
    }

    // BitBoard(){
    //     for(short i = 48 ; i < 56 ; i += 1){
    //         black_pieces[5] |= 1LL << i;
    //         white_pieces[5] |= 1LL << (i - 40);
    //     }

    //     white_pieces[0] = 1 | (1 << 7);
    //     black_pieces[0] = (1LL << 56)  | (1LL << 63);

    //     white_pieces[1] = (1 << 1) | (1 << 6);
    //     black_pieces[1] = (1LL << 57)  | (1LL << 62);

    //     white_pieces[2] = (1 << 2) | (1 << 5);
    //     black_pieces[2] = (1LL << 58) | (1LL << 61);

    //     white_pieces[3] = 1 << 3;
    //     black_pieces[3] = 1LL << 59;

    //     white_pieces[6] = 1 << 4;
    //     black_pieces[6] = 1LL << 60;

    //     for(int i = 0 ; i < 7 ; i += 1){
    //         if(i == 4)
    //         {
    //             continue;
    //         }
    //         white_pieces[4] |= white_pieces[i];
    //         black_pieces[4] |= black_pieces[i];
    //     }
    // }

};