

pub mod moves{
    use crate::components::chess::{Board, Color, PieceType, Square};


    pub struct Move{
        takes : bool,
        rank : Option<u8>,
        file : Option<u8>,
        destination : (u8 , u8),
    }

    const KING_MOVES_FILE: [i8 ; 8] = [0 , 0 , 1 , 1 , 1 , -1 , -1 , -1];
    const KING_MOVES_RANK: [i8 ; 8] = [1 , -1 , 0 , 1 , -1 , 0 , 1 , -1];


    fn legal_move(rank : i8 , file : i8) -> bool{
        rank >= 1 && rank <= 8 && file >= 1 && file <= 8
    }

    pub fn get_moves(square : &Square, board : &Board) -> Vec<Move>{

        match square.piece.piece_type {
            PieceType::King => {
                get_king_moves(square, &board);
            },
            _ => {

            }
        }

        todo!()
    }

  

    fn get_king_moves(square : &Square , board : &Board) -> Vec<Move>{
        let mut moves : Vec<Move> = vec![];
        for index in 0..8 {
            let mut new_rank = square.rank as i8 + KING_MOVES_RANK[index];
            let mut new_file = square.file as i8 + KING_MOVES_FILE[index];
            if !legal_move(new_rank, new_file){
                continue;
            }
            new_file -= 1; new_rank -= 1;
            
            let index: usize = ((new_rank << 1) + new_file) as usize;

            let &destination =  &board.squares.get(index).unwrap();

            if destination.piece.color == square.piece.color {
                continue;
            }

            let the_move = Move{
                 takes : destination.piece.color != Color::NoColor,
                 rank : None,
                 file : None,
                 destination : ((new_file + 1) as u8, (new_rank + 1) as u8 ),
            };

            moves.push(the_move);

        }

        moves
    }

    fn get_queen_moves(square : &Square) -> Vec<Move>{
        todo!()
    }

    fn get_knight_moves(square : &Square) -> Vec<Move>{
        todo!()
    }

    fn get_rook_moves(square : &Square) -> Vec<Move>{
        todo!()
    }

    fn get_bishop_moves(square : &Square) -> Vec<Move>{
        todo!()
    }

    fn get_pawn_moves(square : &Square) -> Vec<Move>{
        todo!()
    }

}