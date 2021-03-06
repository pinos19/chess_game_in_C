# chess_game_in_C

Creation of a chess game in C, profiles configuration, play against an AI, integration of a timer, visualisation of ended games, saving and loading functionnalities

First we have the main menu.

<img src="https://github.com/pinos19/chess_game_in_C/blob/main/images/menuPrincipal.PNG"/>

There we can choose to play a new game, to finish an unfinished game, to view the currents profiles or our own profile, display the rules of the game, visualize finished games and finally quit the game.

# Display the rules

<img src="https://github.com/pinos19/chess_game_in_C/blob/main/images/menuAide.gif"/>

All the rules which are displayed on the help are implemented in the code.

# Create a profile

To play the game, you have to create a profile with an username and a password, the application allows you to visualize your wins, draws and losses.

<img src="https://github.com/pinos19/chess_game_in_C/blob/main/images/gestionProfils.gif"/>

# Play a new game

<img src="https://github.com/pinos19/chess_game_in_C/blob/main/images/nouvellePartie.gif"/>

We have on the chessboard a timer fixed by the players before launching the game. This timer doesn't make the application blink. I used a technique to update only the space where the timer is, so it is just the timer blinking, not all the application.

# Visualize a game

We have the ability to review a party finished or unfinished. The review can be done manually or automatically, for the manual review, you just have to press "p" for previous move and "s" for the next move.

<img src="https://github.com/pinos19/chess_game_in_C/blob/main/images/visualisationPartie.gif"/>

# Resume a game

We have the ability to resume a game which was not finished.

<img src="https://github.com/pinos19/chess_game_in_C/blob/main/images/reprisePartie.gif"/>

