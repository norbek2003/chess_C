# Chess Devlog
## Jan 3, 2019
- Created the basic structure of the chess game: pieces, sides, game, and board.
- Created functions to initalize them in the games starting state.
## Jan 4, 2019
- Code refactoring all around
- Started work on piece-moving rules and tests for them. Added tests/rules for pawns and knights.
## Jan 5, 2019
- Basic refactoring
- Finished unit tests and rules for all pieces as well as checking whether or not the move would result in check
## Jan 6, 2019
- The game is now playable on a single computer. Promotion and En Passant are yet to be added. Castling is fully supported!
## Jan 8, 2019
- The game mostly works over networks. They gameplay functions. Unfortunately, the game ending (Draw / Checkmate) still has some kinks that need to be worked out (over the network).
## Jan 9, 2019
- The game now completely works over a network. Game ending(Draw/Checkmate) has been fully implemented
## Jan 11, 2019
- The GUI is now fully operational. The graphics will be improved but for now a decent GUI functions perfectly over a network.
