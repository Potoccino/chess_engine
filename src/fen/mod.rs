
pub mod fen {
    use crate::components::chess::{Board, Color, Error, Piece, PieceType};

    pub struct Fen {
        pieces : String,
        turn : char,
        castling : String,
        en_passant : (u8 , u8),
        half_moves : u32,
        full_moves : u32,
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

    pub fn build_fen(board : &Board) -> String {
        let mut fen = "".to_string();

        let mut empty_sqaures : u32 = 0;
        let mut rank = 8;
        let mut file = 1;
        for square in &board.squares {
            if square.piece.piece_type == PieceType::Empty {
                empty_sqaures += 1;
            }else{
                if empty_sqaures != 0 {
                    fen.push_str( &char::from_digit(empty_sqaures , 10).unwrap().to_string() );
                }
                empty_sqaures = 0;
                fen.push_str(
                    &get_char_from_piece(&square.piece).unwrap().to_string()
                );
            }
            file += 1;

            if file == 9 { 
                file = 1; 
                rank -= 1;
                if empty_sqaures != 0 {
                    fen.push_str( &char::from_digit(empty_sqaures , 10).unwrap().to_string() );
                }
                empty_sqaures = 0;
                if rank != 0 {
                    fen.push('/');
                }
            }

        }
        fen.to_string()
    }



}