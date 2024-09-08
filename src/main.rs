use std::process::exit;

use chess_engine::components::chess;
use chess_engine::run::run;


fn main() {

    // let board : chess::Board = chess::Board::build_from_fen("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1".to_string());
    let board : chess::Board = chess::Board::build();
    run(&board);


    println!("i a here");
}
