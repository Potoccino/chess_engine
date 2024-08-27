

pub mod chess {
    use std::{fmt::{self}, vec};
    use crate::fen::fen;

    #[derive(Debug)]
    pub enum Error {
        InvalidPieceChar(char),
        InvalidPieceType(PieceType),
    }

    impl fmt::Display for Color {
        fn fmt(&self , f : &mut fmt::Formatter) -> fmt::Result {
            match *self {
                Color::Black => write!(f , "Black"),
                Color::White => write!(f , "White"),
                Color::NoColor => write!(f , "Not a piece"),
            }
        }
    }

    impl fmt::Display for PieceType {
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
            match *self {
                PieceType::Rook => write!(f, "Rook"),
                PieceType::Pawn => write!(f, "Pawn"),
                PieceType::Knight => write!(f, "Knight"),
                PieceType::Bishop => write!(f, "Bishop"),
                PieceType::King => write!(f, "King"),
                PieceType::Queen => write!(f, "Queen"),
                PieceType::Empty => write!(f, "Empty"), // Display for empty squares
            }
        }
    }
    
    impl fmt::Display for Error {
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
            match self {
                Error::InvalidPieceChar(c) => write!(f, "Invalid piece character: '{}'", c),
                Error::InvalidPieceType(c) => write!(f, "Invalid piece Type: '{}'", c),
            }
        }
    }

    impl fmt::Display for Square {
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
            match self.piece.piece_type {
                PieceType::Rook => write!(f, "{} R", self.piece.color),
                PieceType::Pawn => write!(f, "{} P", self.piece.color),
                PieceType::Knight => write!(f, "{} N", self.piece.color),
                PieceType::Bishop => write!(f, "{} B", self.piece.color),
                PieceType::King => write!(f, "{} K", self.piece.color),
                PieceType::Queen => write!(f, "{} Q", self.piece.color),
                PieceType::Empty => write!(f, "{} .", self.piece.color), // Use a dot for empty squares
            }
        }
    }
    

    pub enum Color {
        White,
        Black,
        NoColor,
    }



    #[derive(Debug)]
    #[derive(PartialEq)]
    pub enum PieceType {
        King,
        Queen,
        Pawn,
        Bishop,
        Rook,
        Knight,
        Empty,
    }

    pub struct Square {
        pub piece: Piece,
        rank : u8 ,
        file : u8,
    }

    pub struct Piece {
        pub piece_type: PieceType,
        pub color: Color,
    }

    pub struct Move{
        takes : bool,
        rank : Option<u8>,
        file : Option<u8>,
        destination : (u8 , u8),
    }

    pub struct Board {
        pub squares: Vec<Square>,
        pub moves : Vec<Move>,
    }

    impl Board {
        fn construct_board_vector() -> Vec<Square> {
            let mut sqaures: Vec<Square> = vec![];
            for rank in 1..9 {
                for file in 1..9 {
                    let piece = Piece {
                        piece_type: PieceType::Empty,
                        color: Color::NoColor,
                    };
                    sqaures.push(Square {
                        piece,
                        rank,
                        file,
                    });
                }
            }
            sqaures
        }

        pub fn build() -> Board {
            let mut board: Vec<Square> = Self::construct_board_vector();

            let fen: String = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR".to_string();
            let fen = fen::get_fen_string(&fen);

            let mut current_rank: u8 = 8;
            for pieces_in_rank in fen {
                
                let mut file: u8 = 1;
                for piece in pieces_in_rank.chars() {
                    
                    if piece.is_ascii_digit() {
                        file += u8::try_from(piece.to_digit(10).unwrap())
                            .ok()
                            .expect("this will never happen");
                        continue;
                    }

                    let color = if piece.is_ascii_uppercase() {
                        Color::White
                    } else {
                        Color::Black
                    };

                    let piece = Piece {
                        piece_type: fen::get_piece_from_char(&piece).unwrap_or_else(|err| {
                                panic!("couldn't parse the char to a piece : {err}");
                        }),
                        color: color,
                    };

                    board[(((current_rank - 1) as usize) << 3) + ((file - 1) as usize)] = Square {
                        piece: piece,
                        rank : current_rank,
                        file ,
                    };
                    file += 1;
                }

                current_rank -= 1;
            }

            Board {
                squares: board,
                moves : vec![] , 
            }
        }


        pub fn add_move(& mut self , mv : Move) ->() {
            self.moves.push(mv);
        }

    }

    impl Square {
        
    }

}



