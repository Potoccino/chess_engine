
use std::io::{self, ErrorKind};

use crate::{components::chess::{Board, Color, Piece, PieceType, Square}, moves::moves::{get_moves, Move}};


static  CASTLE_LONG_WHITE : Move = Move{
    takes : false,
    castle : Some(true),
    rank : None,
    file : None,
    source : (5 , 1),
    destination : (3 , 1),
};

static  CASTLE_SHORT_WHITE : Move = Move{
    takes : false,
    castle : Some(true),
    rank : None,
    file : None,
    source : (5 , 1),
    destination : (7 , 1),
};

static  CASTLE_LONG_BLACK : Move = Move{
    takes : false,
    castle : Some(false),
    rank : None,
    file : None,
    source : (5 , 8),
    destination : (3 , 8),
};


static  CASTLE_SHORT_BLACK : Move = Move{
    takes : false,
    castle : Some(false),
    rank : None,
    file : None,
    source : (5 , 8),
    destination : (7 , 8),
};



fn get_king_position(board : &Board , color : &Color) -> (u8,u8) {
    let res = (0,0);
    for square in &board.squares {
        if square.piece.color != *color || square.piece.piece_type != PieceType::King {
            continue;
        }
        return res;
    }
    res
}

fn read_move(board : &Board) -> Result<Move , ErrorKind> {
    let mut play = String::new(); 
    loop {
        io::stdin()
            .read_line(&mut play).unwrap();
        if play == "o-o-o" {
            return if board.fen.turn == 'w' {Ok(CASTLE_LONG_WHITE)} else {Ok(CASTLE_LONG_BLACK)}; 
        }

        if play == "o-o" {
            return if board.fen.turn == 'w' {Ok(CASTLE_SHORT_WHITE)} else {Ok(CASTLE_SHORT_BLACK)}; 
        }
        
        let check: bool = play.ends_with('+');
        if check == true {
            play.pop();
        }

        if play.contains('x') {
            let mut iter = play.split('x');
            let piece = match iter.next() {
                Some(str) => str,
                None => return Err(ErrorKind::InvalidInput),
            };
            let destination = match iter.next() {
                Some(str) => str,
                None => return Err(ErrorKind::InvalidInput),
            };

        }else {

        }


        break;
    }

    Ok(CASTLE_LONG_BLACK)
}

pub fn run(board : &Board) -> () {

    loop {
        let turn = if board.fen.turn == 'w' {Color::White} else {Color::Black};
        
        let (x , y) = get_king_position(board, &turn); 

        let moves = get_moves(board, &turn);

        read_move(&board);


        break;
    }

}