
#include <bitset>

typedef unsigned short u_short;

const u_short NOTHING_TAKEN = 0;
const u_short ROOK_TAKEN = 1;
const u_short KNIGHT_TAKEN = 2;
const u_short BISHOP_TAKEN = 3;
const u_short QUEEN_TAKEN = 4;
const u_short PAWN_TAKEN = 5;


const std::bitset<16> KNIGHT_PROMOTED = 1 << 12;
const std::bitset<16> BISHOP_PROMOTED = 2 << 12;
const std::bitset<16> ROOK_PROMOTED = 3 << 12;
const std::bitset<16> QUEEN_PROMOTED = 4 << 12;

const std::bitset<16> castleQueen = 5 << 12;
const std::bitset<16> castleKing = 6 << 12;

const std::bitset<16> EN_PASSANT = 7 << 12;



// const u_short ROOK = 0;
// const u_short KNIGHT = 1;
// const u_short BISHOP = 2;
// const u_short QUEEN = 3;
// const u_short EMPTY = 4;
// const u_short PAWN = 5;
// const u_short KING = 6;


// std::pair<int,bool> convertCharToPiece(char c)
// {
//     int piece = 0;
//     bool color = isupper(c);
//     c = tolower(c);

//     if(c == 'r'){
//         piece = ROOK;
//     }else if(c == 'n'){
//         piece = KNIGHT;
//     }else if(c == 'b'){
//         piece = BISHOP;
//     }else if(c == 'q'){
//         piece = QUEEN;
//     }else if(c == 'k'){
        // piece = KING;
//     }else if(c == 'p'){
//         piece = PAWN;
//     }else{
//         piece = EMPTY;
//     }

//     return std::make_pair(piece , color); 
// }


// char convertPieceToChar(int piece , bool color = 1)
// {
//     char res;
//     if(piece == ROOK)
//     {
//         res = 'R';
//     }
//     else if(piece == KNIGHT)
//     {
//         res = 'N';
//     }
//     else if(piece == BISHOP)
//     {
//         res = 'B';
//     }
//     else if(piece ==  QUEEN)
//     {
//         res = 'Q';
//     }
//     else if(piece == EMPTY)
//     {
//         res = 'E';
//     }
//     else if(piece == PAWN)
//     {
//         res = 'P';
//     }
//     else if(piece == KING)
//     {
//         res = 'K';
//     }
//     else
//     {
//         exit(-1);
//     }

//     return color ? res : tolower(res);

// }


// BitBoard convertFENstringToBoard(const std::string &FEN){
//     int currnet_counter_squares = 0;
//     int i = 0;
//     BitBoard board = BitBoard();
//     for(int index : {56 , 48 , 40 , 32 , 24 , 16 , 8 , 0})
//     {

//         for( ; i < FEN.size() && FEN[i] != '/' ; i += 1)
//         {
//             if(isdigit(FEN[i])){
//                 index += int(FEN[i] - '0');
//             }else{
//                 auto [piece , color] = convertCharToPiece(FEN[i]);
//                 if(color)
//                 {
//                     board.white_pieces[piece] |= 1ll << index;
//                 }
//                 else
//                 {
//                     board.black_pieces[piece] |= 1ll << index;
//                 }
//                 index += 1;
//             }
//         }
//         i ++ ;
//     }

//     for(int i = 0 ; i < 7 ; i += 1)
//     {
//         board.black_pieces[4] |= board.black_pieces[i];
//         board.white_pieces[4] |= board.white_pieces[i];
//     }


//     return board;

// }



// std::string ConvertBoardToFENstring(BitBoard board)
// {

//     std::string FEN;
//     int index = 56, current_counted_squares = 0, free_squares = 0;
//     for (int rep = 0; rep < 64; rep += 1)
//     {
//         int found_piece = 0;
//         bool color;

//         if (board.black_pieces[4].test(index) ^ board.white_pieces[4].test(index) == 0)
//         {
//             found_piece = 4;
//         }
//         else
//         {
//             std::bitset<64> *piece_set = board.black_pieces[4].test(index) ? board.black_pieces : board.white_pieces;
//             color = !board.black_pieces[4].test(index);
//             for (int i = 0; i < 7; i += 1)
//             {
//                 if (i == 4)
//                 {
//                     continue;
//                 }
//                 if (piece_set[i].test(index) == 1)
//                 {
//                     found_piece = i;
//                     break;
//                 }
//             }
//         }


//         // the current index is empty
//         if (found_piece == 4)
//         {
//             free_squares += 1;
//         }

//         current_counted_squares += 1;
//         index += 1;
//         if (current_counted_squares == 8)
//         {

//             index -= 16;
//             current_counted_squares = 0;
//             if (free_squares > 0)
//             {
//                 FEN += char('0' + free_squares);
//             }
            
//             if(found_piece != 4)
//             {
//                 FEN += convertPieceToChar(found_piece, color);
//             }

//             FEN += '/';
//             free_squares = 0;
//             continue;
//         }

//         if (found_piece == 4)
//         {
//             continue;
//         }

//         if (free_squares > 0)
//         {
//             FEN += char('0' + free_squares);
//             free_squares = 0;
//         }

//         FEN += convertPieceToChar(found_piece, color);
//     }
//     FEN.pop_back();
//     return FEN;
// }