
// #include <iostream>
// #include <vector>
// #include "bitBoard.h"
// #include "pieces.h"
// #include <assert.h>


// std :: vector<std :: string> generateFENStrings()
// {
//     std::vector<std::string> FENStrings;

//     const std::string chars = "RNBQKPrnbqkp12345678";

//     auto generateRow = [&]() -> std::string
//     {
//         std::string row;
//         int filled = 0 ;
//         bool lastChoosenIsDigit = false;
//         while(filled < 8)
//         {

//             int index;
//             if(lastChoosenIsDigit)
//             {
//                 index = std::rand() % 12;
//             }
//             else
//             {
//                 index = std::rand() % (20 - filled); 
//             }
//             row += chars[index];
//             if(isdigit(chars[index]))
//             {
//                 filled += chars[index] - '0';
//                 lastChoosenIsDigit = true;
//             }
//             else
//             {
//                 filled += 1;
//                 lastChoosenIsDigit = false;
//             }
//         }
//         row += '/';
//         return row;
//     };

//     for(int reps = 0 ; reps < 10000 ; reps += 1)
//     {
//       std::string FENstring;
//       for(int i = 0 ; i < 8 ; i += 1)
//       {
//         FENstring += generateRow();
//       }
//       FENstring.pop_back();
//       FENStrings.push_back(FENstring);
//     }

//     return FENStrings;

// }


// int main()
// {
//     std::vector<std::string> strings = generateFENStrings();
//     for(auto x : strings)
//     {
//         BitBoard board = convertFENstringToBoard(x);
//         std::string result = ConvertBoardToFENstring(board);
//         assert(x == result);
//     }
// }