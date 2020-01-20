# Chess Devlog
## Jan 3, 2020
- Created the basic structure of the chess game: pieces, sides, game, and board.
- Created functions to initalize them in the games starting state.
## Jan 4, 2020
- Code refactoring all around
- Started work on piece-moving rules and tests for them. Added tests/rules for pawns and knights.
## Jan 5, 2020
- Basic refactoring
- Finished unit tests and rules for all pieces as well as checking whether or not the move would result in check
## Jan 6, 2020
- The game is now playable on a single computer. Promotion and En Passant are yet to be added. Castling is fully supported!
## Jan 8, 2020
- The game mostly works over networks. They gameplay functions. Unfortunately, the game ending (Draw / Checkmate) still has some kinks that need to be worked out (over the network).
## Jan 9, 2020
- The game now completely works over a network. Game ending(Draw/Checkmate) has been fully implemented
## Jan 11, 2020
- The GUI is now fully operational. The graphics will be improved but for now a decent GUI functions perfectly over a network.
## Jan 12, 2020
- GUI Asthetic improvements. Perspective swapping for each player. Border with positions.
## Jan 14, 2020
- Added GUI Feature to display pieces that you've captured.
- Improved networking, got rid of timeout error.
## Jan 19, 2020
- Added GUI feature to display game's move history
- Added button to save that information to a file
## Jan 20, 2020
- Added promotion
- Refactored networking code to be faster and less prone to mistakes.
