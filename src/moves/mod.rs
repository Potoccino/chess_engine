pub mod moves {

    use crate::{
        components::chess::{Board, Color, PieceType, Square},
        fen::fen::Fen,
    };

    pub struct Move {
        takes: bool,
        rank: Option<u8>,
        file: Option<u8>,
        destination: (u8, u8),
    }

    pub const KING_MOVES_FILE: [i8; 8] = [0, 0, 1, 1, 1, -1, -1, -1];
    pub const KING_MOVES_RANK: [i8; 8] = [1, -1, 0, 1, -1, 0, 1, -1];

    pub const ROOK_MOVES_FILE: [i8; 4] = [0, 0, -1, 1];
    pub const ROOK_MOVES_RANK: [i8; 4] = [1, -1, 0, 0];

    pub const BISHOP_MOVES_FILE: [i8; 4] = [1, 1, -1, -1];
    pub const BISHOP_MOVES_RANK: [i8; 4] = [-1, 1, -1, 1];

    pub const KNIGHT_MOVES_FILE: [i8; 8] = [1, 1, -1, -1, 2, -2, 2, -2];
    pub const KNIGHT_MOVES_RANK: [i8; 8] = [2, -2, 2, -2, 1, 1, -1, -1];

    fn legal_move(rank: i8, file: i8) -> bool {
        rank >= 1 && rank <= 8 && file >= 1 && file <= 8
    }

    pub fn create_move(square: &Square, board: &Board, file: i8, rank: i8) -> Option<Move> {
        let index = (((rank - 1) << 3) + file - 1) as usize;
        let &destination = &board.squares.get(index).unwrap();

        if destination.piece.color == square.piece.color {
            return None;
        }

        if square.piece.piece_type == PieceType::Pawn && destination.piece.color != Color::NoColor {
            return None;
        }

        if destination.piece.color != Color::NoColor {
            return Some(Move {
                takes: true,
                rank: None,
                file: None,
                destination: (rank as u8, file as u8),
            });
        }

        Some(Move {
            takes: false,
            rank: None,
            file: None,
            destination: (rank as u8, file as u8),
        })
    }

    pub fn create_move_for_pawn(
        square: &Square,
        board: &Board,
        file: i8,
        rank: i8,
        take: bool,
    ) -> Option<Move> {
        let index = (((rank - 1) << 3) + file - 1) as usize;
        let &destination = &board.squares.get(index).unwrap();

        if destination.piece.color == square.piece.color {
            return None;
        }

        if take {
            if destination.piece.color != Color::NoColor {
                return Some(Move {
                    takes: true,
                    rank: None,
                    file: None,
                    destination: (rank as u8, file as u8),
                });
            } else {
                return None;
            }
        } else {
            if destination.piece.color == Color::NoColor {
                return Some(Move {
                    takes: false,
                    rank: None,
                    file: None,
                    destination: (rank as u8, file as u8),
                });
            } else {
                return None;
            }
        }
    }

    pub fn get_moves(square: &Square, board: &Board, fen: &Fen) -> Vec<Move> {
        let vector = match square.piece.piece_type {
            PieceType::King => {
                get_king_moves(&square, &board, fen)
            }
            PieceType::Bishop => {
                get_bishop_moves(&square, &board)
            },
            PieceType::Knight => {
                get_knight_moves(&square, &board)
            },
            PieceType::Queen => {
                get_queen_moves(&square, &board)
            },
            PieceType::Pawn => {
                get_pawn_moves(&square, &board , fen)
            },
            PieceType::Rook => {
                get_rook_moves(square, &board)
            },
            PieceType::Empty => {
                Vec::new()
            }
        };
        vector
    }

    fn get_king_moves(square: &Square, board: &Board, fen: &Fen) -> Vec<Move> {
        let mut moves: Vec<Move> = vec![];
        for index in 0..8 {
            let new_rank = square.rank as i8 + KING_MOVES_RANK[index];
            let new_file = square.file as i8 + KING_MOVES_FILE[index];

            if !legal_move(new_rank, new_file) {
                continue;
            }

            let the_move: Option<Move> = create_move(square, board, new_file, new_rank);

            if the_move.is_none() {
                continue;
            }
            moves.push(the_move.unwrap())
        }
        moves
    }

    fn get_queen_moves(square: &Square, board: &Board) -> Vec<Move> {
        let mut rook_like_moves = get_rook_moves(square, board);
        let mut bishop_like_moves = get_bishop_moves(square, board);

        rook_like_moves.append(&mut bishop_like_moves);

        rook_like_moves
    }

    fn get_knight_moves(square: &Square, board: &Board) -> Vec<Move> {
        let mut moves = vec![];

        for index in 1..8 {
            let index = index as usize;
            let new_file = (square.file as i8) + KNIGHT_MOVES_FILE[index];
            let new_rank = (square.rank as i8) + KNIGHT_MOVES_RANK[index];

            if !legal_move(new_rank, new_file) {
                break;
            }

            let the_move: Option<Move> = create_move(square, board, new_file, new_rank);

            if the_move.is_none() {
                continue;
            }
            moves.push(the_move.unwrap())
        }

        moves
    }

    fn get_rook_moves(square: &Square, board: &Board) -> Vec<Move> {
        let mut moves = vec![];

        for direction in 0..4 {
            let direction = direction as usize;
            for shift in 1..8 {
                let new_file = (square.file as i8) + shift * ROOK_MOVES_FILE[direction];
                let new_rank = (square.rank as i8) + shift * ROOK_MOVES_RANK[direction];

                if !legal_move(new_rank, new_file) {
                    break;
                }

                let the_move: Option<Move> = create_move(square, board, new_file, new_rank);

                if the_move.is_none() {
                    break;
                }
                moves.push(the_move.unwrap())
            }
        }
        moves
    }

    fn get_bishop_moves(square: &Square, board: &Board) -> Vec<Move> {
        let mut moves: Vec<Move> = vec![];

        for direction in 0..4 {
            let direction = direction as usize;
            for shift in 1..8 {
                let new_file = (square.file as i8) + shift * BISHOP_MOVES_FILE[direction];
                let new_rank = (square.rank as i8) + shift * BISHOP_MOVES_RANK[direction];

                if !legal_move(new_rank, new_file) {
                    break;
                }

                let the_move: Option<Move> = create_move(square, board, new_file, new_rank);

                if the_move.is_none() {
                    break;
                }
                moves.push(the_move.unwrap())
            }
        }
        moves
    }

    fn get_pawn_moves(square: &Square, board: &Board, fen: &Fen) -> Vec<Move> {
        let mut moves = vec![];

        let rank = square.rank;
        let file = square.rank;
        let direction_based_on_color: i8 = if square.piece.color == Color::White {
            1
        } else {
            -1
        };

        for reps in 1..3 {
            if legal_move(rank as i8 + direction_based_on_color * reps, file as i8) {
                let the_move = create_move_for_pawn(
                    square,
                    board,
                    file as i8,
                    rank as i8 + direction_based_on_color * reps,
                    false,
                );
                if the_move.is_some() {
                    moves.push(the_move.unwrap());
                }
            } else {
                break;
            }
        }

        if legal_move(rank as i8 + direction_based_on_color, file as i8 + 1) {
            let the_move = create_move_for_pawn(
                square,
                board,
                file as i8 + 1,
                rank as i8 + direction_based_on_color,
                true,
            );
            if the_move.is_some() {
                moves.push(the_move.unwrap());
            }
        }

        if legal_move(rank as i8 + direction_based_on_color, file as i8 - 1) {
            let the_move = create_move_for_pawn(
                square,
                board,
                file as i8 - 1,
                rank as i8 + direction_based_on_color,
                true,
            );
            if the_move.is_some() {
                moves.push(the_move.unwrap());
            }
        }

        let en_passent_file = fen.en_passant.as_bytes()[0] - 96;
        let en_passent_rank = fen.en_passant.as_bytes()[1] - 48;

        if rank as i8 + direction_based_on_color == en_passent_rank as i8 && file as i8 - 1 == en_passent_file as i8 {
            moves.push(Move{
                takes : true,
                rank : None,
                file : None,
                destination: (en_passent_file , en_passent_rank),
            })
        }

        if rank as i8 + direction_based_on_color == en_passent_rank as i8 && file as i8 + 1 == en_passent_file as i8 {
            moves.push(Move{
                takes : true,
                rank : None,
                file : None,
                destination: (en_passent_file , en_passent_rank),
            })
        }

        moves
    }
}
