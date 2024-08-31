use std::{result, sync::Arc};

use crate::{components::chess::{Board, Color, Piece, PieceType, Square}, moves::moves::get_moves};


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

pub fn run(board : &Board) -> () {

    loop {
        let turn = if board.fen.turn == 'w' {Color::White} else {Color::Black};
        
        let (x , y) = get_king_position(board, &turn); 

        let moves = get_moves(board, &turn);

        for mov in moves  {
            dbg!(mov);
        }

        break;
    }

}