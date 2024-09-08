

pub mod chess {
    use std::{f32::consts::E, fmt::{self}, io::Empty, vec};
    use crate::{fen::fen::{self, build_board_from_fen, Fen}, moves::moves::{get_protected_squares, Move}};

    #[derive(Debug)]
    pub enum Error {
        InvalidPieceChar(char),
        InvalidPieceType(PieceType),
        InvalidInput(String),
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
                Error::InvalidInput(s ) =>write!(f, "Invalid Input: '{}'", s),
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
    
    #[derive(Debug)]
    #[derive(PartialEq)]
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
    #[derive(Debug)]
    pub struct Square {
        pub piece: Piece,
        pub rank : u8 ,
        pub file : u8,
    }

    #[derive(Debug)]
    pub struct Piece {
        pub piece_type: PieceType,
        pub color: Color,
    }

    pub struct Board {
        pub squares: Vec<Square>,
        pub squares_seen_by_white : u64,
        pub squares_seen_by_black : u64,
        pub moves : Vec<Move>,
        pub fen : Fen,
    }

    impl Board {
        pub fn construct_board_vector() -> Vec<Square> {
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

        pub fn build_from_fen(fen : String) -> Board {
            let fen_vector : Vec<&str>  = fen.split_ascii_whitespace().into_iter().collect();
            let fen = Fen {
                pieces : fen_vector[0].to_string(),
                turn : fen_vector[1].chars().next().unwrap(),
                castling : fen_vector[2].to_string(),
                en_passant : fen_vector[3].to_string(),
                half_moves : fen_vector[4].parse().unwrap(),
                full_moves : fen_vector[5].parse().unwrap()
            };
            let squares = build_board_from_fen(&fen.pieces);
            let mut squares_seen_by_black = 0;
            let mut squares_seen_by_white = 0;
            for square in &squares {
                if square.piece.piece_type == PieceType::Empty {
                    continue;
                }

                if square.piece.color == Color::Black {
                    squares_seen_by_black |= get_protected_squares(&square, &squares);
                }else {
                    squares_seen_by_white |= get_protected_squares(&square, &squares);
                }

            }
            Board {
                squares : build_board_from_fen(&fen.pieces),
                squares_seen_by_white,
                squares_seen_by_black,
                moves : vec![],
                fen,
            }
        }

        pub fn build() -> Board {
            let mut squares_seen_by_white: u64 = 0;
            let mut squares_seen_by_black: u64 = 0;
            
            let fen : Fen = fen::start_fen();
            let squares: Vec<Square> = build_board_from_fen(&fen.pieces);
            for square in &squares {
                if square.piece.piece_type == PieceType::Empty {
                    continue;
                }

                if square.piece.color == Color::Black {
                    squares_seen_by_black |= get_protected_squares(&square, &squares);
                }else {
                    squares_seen_by_white |= get_protected_squares(&square, &squares);
                }

            }

            Board {
                squares,
                moves : vec![] , 
                squares_seen_by_black, 
                squares_seen_by_white, 
                fen,
            }
        }


        pub fn add_move(& mut self , mv : Move) ->() {
            self.moves.push(mv);
        }

    }


}



