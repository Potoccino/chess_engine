use std::{
    char,
    io::{self, ErrorKind},
    str::{from_utf8, from_utf8_unchecked},
};

use crate::{
    components::chess::{self, Board, Color, Error, Piece, PieceType, Square},
    fen::fen::get_piece_from_char,
    moves::{
        self,
        moves::{get_move, get_moves, Move},
    },
};

static CASTLE_LONG_WHITE: Move = Move {
    takes: false,
    castle: Some(true),
    source: (5, 1),
    destination: (3, 1),
};

static CASTLE_SHORT_WHITE: Move = Move {
    takes: false,
    castle: Some(true),
    source: (5, 1),
    destination: (7, 1),
};

static CASTLE_LONG_BLACK: Move = Move {
    takes: false,
    castle: Some(false),
    source: (5, 8),
    destination: (3, 8),
};

static CASTLE_SHORT_BLACK: Move = Move {
    takes: false,
    castle: Some(false),
    source: (5, 8),
    destination: (7, 8),
};

fn get_king_position(board: &Board, color: &Color) -> (u8, u8) {
    let res = (0, 0);
    for square in &board.squares {
        if square.piece.color != *color || square.piece.piece_type != PieceType::King {
            continue;
        }
        return res;
    }
    res
}

fn extract_piece(piece: &str) -> Result<(PieceType, Option<u8>, Option<u8>), Error> {
    let mut piece_type: PieceType = PieceType::Pawn;
    let mut rank: Option<u8> = None;
    let mut file: Option<u8> = None;
    for char in piece.chars() {
        if char.is_ascii_uppercase() {
            piece_type = match get_piece_from_char(&char) {
                Ok(piece_type) => piece_type,
                Err(e) => return Err(e),
            }
        } else if char.is_digit(10) {
            rank = Some(char.to_digit(10).unwrap() as u8);
        } else if char.is_lowercase() {
            file = Some(file_to_number(&char));
        }
    }

    Ok((piece_type, rank, file))
}

fn file_to_number(c: &char) -> u8 {
    c.to_ascii_lowercase() as u8 - 96
}

fn get_piece_positions<'a>(
    board: &'a Board,
    piece_type: PieceType,
    color: &Color,
) -> Vec<&'a Square> {
    let mut positions: Vec<&Square> = vec![];

    for square in &board.squares {
        if square.piece.color != *color || square.piece.piece_type != piece_type {
            continue;
        }
        positions.push(square);
    }

    positions
}

fn read_move(board: &Board, color: &Color) -> Result<Move, Error> {
    let mut play = String::new();
    io::stdin().read_line(&mut play).unwrap();
    if play == "o-o-o" {
        return if board.fen.turn == 'w' {
            Ok(CASTLE_LONG_WHITE)
        } else {
            Ok(CASTLE_LONG_BLACK)
        };
    }

    if play == "o-o" {
        return if board.fen.turn == 'w' {
            Ok(CASTLE_SHORT_WHITE)
        } else {
            Ok(CASTLE_SHORT_BLACK)
        };
    }

    let check: bool = play.ends_with('+');
    if check == true {
        play.pop();
    }

    if play.contains('x') {
        let mut iter = play.split('x');
        let piece = match iter.next() {
            Some(str) => str,
            None => return Err(Error::InvalidInput("thing".to_string())),
        };

        let destination = match iter.next() {
            Some(str) => str,
            None => return Err(Error::InvalidInput("thing".to_string())),
        };

        let (piece_type, disambiguate_rank, disambiguate_file) = match extract_piece(piece) {
            Ok((piece_type, rank, file)) => (piece_type, rank, file),
            Err(e) => return Err(e),
        };

        let mut iter = destination.chars();

        let destination_file = match iter.next() {
            Some(c) => file_to_number(&c),
            None => return Err(Error::InvalidInput("thing".to_string())),
        };

        let destination_rank = match iter.next() {
            Some(c) => c.to_digit(10).unwrap() as u8,
            None => return Err(Error::InvalidInput("thing".to_string())),
        };

        let possible_pieces: Vec<&Square> = get_piece_positions(board, piece_type, color);

        let mut played_move: Option<Move> = None;
        for square in possible_pieces {
            if disambiguate_file.is_some() && disambiguate_file.unwrap() != square.file {
                continue;
            }

            if disambiguate_rank.is_some() && disambiguate_rank.unwrap() != square.rank {
                continue;
            }

            let moves: Vec<Move> = get_move(square, board, &board.fen);
            for mv in moves {
                if destination_rank != mv.destination.0 || destination_file != mv.destination.1 {
                    continue;
                }
                played_move = Some(mv);
            }
        }

        if played_move.is_none() {
            return Err(Error::InvalidInput(
                "invalid move, please enter a valid move".to_string(),
            ));
        }

        Ok(played_move.unwrap())
    } else {
        let len = play.len();
        let play = play.as_bytes();
        let slice = &play[..(len - 3)];

        let (piece_type, disambiguate_file, disambiguate_rank) =
            match extract_piece(from_utf8(slice).unwrap()) {
                Ok((piece_type, rank, file)) => (piece_type, rank, file),
                Err(e) => return Err(e),
            };


        let slice = &play[(len - 3)..];
        let destination_file = slice[0] - 96;
        let destination_rank = slice[1] - 48;

        let possible_pieces: Vec<&Square> = get_piece_positions(board, piece_type, color);
        let mut played_move: Option<Move> = None;
        for square in possible_pieces {
            if disambiguate_file.is_some() && disambiguate_file.unwrap() != square.file {
                continue;
            }

            if disambiguate_rank.is_some() && disambiguate_rank.unwrap() != square.rank {
                continue;
            }

            let moves: Vec<Move> = get_move(square, board, &board.fen);
            for mv in moves {
                if destination_rank != mv.destination.0 || destination_file != mv.destination.1 {
                    continue;
                }
                played_move = Some(mv);
            }
        }

        if played_move.is_none() {
            return Err(Error::InvalidInput(
                "invalid move, please enter a valid move".to_string(),
            ));
        }

        dbg!(played_move);

        return Ok(played_move.unwrap());
    }
}

pub fn run(board: &Board) -> () {
    loop {
        let turn = if board.fen.turn == 'w' {
            Color::White
        } else {
            Color::Black
        };

        let (x, y) = get_king_position(&board, &turn);

        let played_move = match read_move(&board, &turn) {
            Ok(mv) => mv,
            Err(_e) => {
                println!("{}", _e);
                continue;
            }
        };

        if played_move.castle.is_none() {
            let dist_index : usize = (played_move.destination.0 + (played_move.destination.1 << 3) - 2 ) as usize;
            let source_index : usize = (played_move.source.0 + played_move.source.1 << 3 - 2) as usize;

            
        } else {

        }

    }
}
