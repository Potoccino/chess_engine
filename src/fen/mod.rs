
pub mod fen {
    use std::fmt;

    use crate::components::chess::{Board, Color, Error, Piece, PieceType, Square};

    #[derive(Debug)]
    pub struct Fen {
        pub pieces : String,
        pub turn : char,
        pub castling : String,
        pub en_passant : String,
        pub half_moves : u32,
        pub full_moves : u32,
    }

    impl fmt::Display for Fen {
        fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
            write!(
                f,
                "{} {} {} {} {} {}",
                self.pieces,
                self.turn,
                self.castling,
                self.en_passant,
                self.half_moves,
                self.full_moves
            )
        }
    }


    pub fn start_fen() -> Fen{
        Fen{
            pieces : "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR".to_string(),
            turn : 'w',
            castling : "KQkq".to_string(),
            en_passant : "-".to_string(),
            half_moves : 0,
            full_moves : 1,
        }
    }

    pub fn get_piece_from_char(c: &char) -> Result<PieceType, Error> {
        match c {
            'r' | 'R' => Ok(PieceType::Rook),
            'p' | 'P' => Ok(PieceType::Pawn),
            'n' | 'N' => Ok(PieceType::Knight),
            'b' | 'B' => Ok(PieceType::Bishop),
            'k' | 'K' => Ok(PieceType::King),
            'q' | 'Q' => Ok(PieceType::Queen),
            _ => Err(Error::InvalidPieceChar(*c)),
        }
    }


    pub fn get_char_from_piece(piece: & Piece) -> Result<char , Error> {
        match ( &piece.piece_type , &piece.color) {
            (PieceType::Rook, Color::Black) => Ok('R'),
            (PieceType::Rook, Color::White) => Ok('r'),
            (PieceType::Pawn, Color::Black) => Ok('P'),
            (PieceType::Pawn, Color::White) => Ok('p'),
            (PieceType::Knight, Color::Black) => Ok('N'),
            (PieceType::Knight, Color::White) => Ok('n'),
            (PieceType::Bishop, Color::Black) => Ok('B'),
            (PieceType::Bishop, Color::White) => Ok('b'),
            (PieceType::King, Color::Black) => Ok('K'),
            (PieceType::King, Color::White) => Ok('k'),
            (PieceType::Queen, Color::Black) => Ok('Q'),
            (PieceType::Queen, Color::White) => Ok('q'),
            (_, _) => Err(Error::InvalidPieceType(PieceType::Bishop)), //this will never happen
        }   

    }

    pub fn get_fen_string(fen: &String) -> Vec<&str> {
        fen.split('/').collect()
    }

    // PPD = piece placement data
    pub fn build_ppd(squares : &Vec<Square>) -> String {
        let mut ppd = String::new();
        let mut empty_squares = 0;
        let mut rank = 8;

        for (i, square) in squares.iter().enumerate() {
            if square.piece.piece_type == PieceType::Empty {
                empty_squares += 1;
            } else {
                if empty_squares > 0 {
                    ppd.push_str(&empty_squares.to_string());
                    empty_squares = 0;
                }
                let piece_char = get_char_from_piece(&square.piece) .unwrap();
                ppd.push(piece_char);
            }

            if (i + 1) % 8 == 0 {
                if empty_squares > 0 {
                    ppd.push_str(&empty_squares.to_string());
                    empty_squares = 0;
                }
                if rank > 1 {
                    ppd.push('/');
                }
                rank -= 1;
            }
        }
        ppd
    }

    pub fn build_board_from_fen(fen_string : &String) -> Vec<Square> {
        let mut squares : Vec<Square> = Board::construct_board_vector();
        let mut index: i8 = 56;

        for c in fen_string.chars(){
            if c == '/' {
                continue;
            }
            if index < 0 {
                break;
            }

            if c.is_digit(10) {
                index += c.to_digit(10).unwrap() as i8;
                if index & 7== 0 {
                    index -= 16 ;
                }
                continue;
            }

            let piece = Piece{
                piece_type : get_piece_from_char(&c).unwrap(),
                color : if c.is_uppercase() {Color::White} else {Color::Black},
            };

            squares[index as usize] = Square{
                piece,
                rank : (index as u8 >> 3) + 1,
                file : (index as u8 & 7) + 1,
            };
            index += 1;
            if index & 7== 0 {
                index -= 16 ;
            }
        }

        squares
    }

    pub fn build_fen(board : &Board) ->  Fen {
        Fen {
            pieces : self::build_ppd(&board.squares),
            turn : board.fen.turn,
            castling : board.fen.castling.clone(),
            en_passant : board.fen.en_passant.clone(),
            half_moves : board.fen.half_moves,
            full_moves : board.fen.full_moves,
        }
        
    }



}