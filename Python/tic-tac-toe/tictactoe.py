"""
display matrix

1 2 3
4 5 6
7 8 9

display available positions: 1 2 3 4 5 6 7 8 9

make your choice:
replace the position by O/X in matrix:
complete dictionnary for player O/X
    win if 147, 258, 369, 159, 753, 456 in dictionary
switch O/X

"""
from random import randint
import math
import sys

player_1 = "\033[32mO\033[0m"
player_2 = "\033[31mX\033[0m"


def init_positions(dimension):
    positions = [str(i) for i in range(1,dimension**2+1)]
    return positions

def print_tic_tac_toe(positions):
    dimension = int(math.sqrt(len(positions)))
    for i in range(dimension):
        print(*positions[i*dimension:(i+1)*dimension])
    
def winning_moves(dimension):
    list_win=[]
    for i in range(dimension):
        # rows
        l = [j for j in range(i*dimension+1,(i+1)*dimension+1)]
        list_win.append(set(l))
        # columns
        l = [i+1+j*dimension for j in range(dimension)]
        list_win.append(set(l))
    # diagonal \
    l = [i for i in range(1,dimension**2+1,dimension+1)]
    list_win.append(set(l))
    """
    for i in range(1,dimension+1):
        for j in range(1,dimension+1):
            if i==j:
                l.append((i-1)*dimension+j)
    """
    # diagonal /
    l = [i for i in range(dimension, dimension**2-(dimension-1)+1,\
        dimension-1)]
    list_win.append(set(l))
    return list_win

def test_win(player_set, dimension, list_win):
    game_over = False
    if(len(player_set) >= dimension ):
        for w in list_win:
            if  w.issubset(player_set):
                game_over = True
                return game_over
    return game_over

def test_move(move, players_set, dimension):
    """
    output: 
        -1 : not numeric
        0 : not allowed
        1 : allowed
    """
    if move.isnumeric():
        if not (int(move) in players_set) and\
             ( 0 < int(move) <= dimension**2 ):
            allowed = 1
        else:
            allowed = 0
    else:
        allowed = -1
    return allowed

def possible_move(player_set_1, player_set_2, dimension):
    l_possible_move = []
    for ipos in range(1,dimension**2 + 1):
        if test_move(str(ipos), player_set_1.union(player_set_2), dimension ) == 1:
            l_possible_move.append(ipos)
    return l_possible_move

def number_of_winning_moves(player_set_1, player_set_2, dimension, list_win):
    pass
            
def run_tic_tac_toe(dimension):
    # Initializations
    positions = init_positions(dimension)
    dicO = set()
    dicX = set()
    dico_player = {player_1:dicO, player_2:dicX}
    #[{1,2,3},{4,5,6},{7,8,9},{1,4,7},{2,5,8},{3,6,9},\
    # {1,5,9},{3,5,7}]
    list_win = winning_moves(dimension) 
    game_over = False
    turn = 0

    while(not game_over):
        dico_players = dico_player[player_1].union(dico_player[player_2])
        turn += 1
        print_tic_tac_toe(positions)

        if turn % 2 == 0:
            player = player_1
        else:
            player = player_2
        
        if player == player_1:
            # Human player
            chain = "(Player "+player+") Make your choice among\n\n"
            available_positions = ""
            for c in positions:
                if c.isnumeric(): available_positions += c
            chain += (' '.join(available_positions)).center(len(chain))+" \n"

            ipos = input(chain)
            test = test_move(ipos, dico_players, dimension )
            print()
            """
            if not ipos.isdigit():
                break
            else:
                ipos = int(ipos)
            while (not (str(ipos) in available_positions)):
                ipos = int(input(chain))
            """
            while (1 != test):
                test = test_move(ipos, dico_players, dimension )
                ipos = input(chain)
            # Add chosen position to player set
            (dico_player[player]).add(int(ipos))
            positions[int(ipos)-1] = player
        else:
            # Random player
            chain = "(Player "+player+") Make your choice among\n\n"
            available_positions = ""
            for c in positions:
                if c.isnumeric(): available_positions += c
            chain += (' '.join(available_positions)).center(len(chain))+" \n"

            irand =  randint(0, len(available_positions)-1 )
            ipos = available_positions[irand]
            while 1 != test_move(ipos, dico_players, dimension ):
                irand =  randint(0, len(available_positions.split(" "))-1 )
                ipos = available_positions[irand]
            print(chain)
            print(ipos+"\n")
        
            # Add chosen position to player set
            (dico_player[player]).add(int(ipos))
            positions[int(ipos)-1] = player

        # Test win conditions
        if test_win(dico_player[player], dimension, list_win):
            print("Player "+player+" win!\n")
            print_tic_tac_toe(positions)
            game_over = True
            break
        
        # Draw condition
        if(turn == dimension**2):
            print("\nDraw !")
            print_tic_tac_toe(positions)
            game_over = True
    
if __name__ == "__main__":
    print ("test_move:")
    dimension = 3
    positions = init_positions(dimension)
    players_set = set()
    list_win = winning_moves(dimension)
    move = "1"
    check = test_move(move, players_set, dimension)
    print("allowed move: (1) "+str(check))
    players_set.add(move)
    move = "1"
    check = test_move(move, players_set, dimension)
    print("not allowed move: (0) "+str(check))
    move = "exit"
    check = test_move(move, players_set, dimension)
    print("not numeric: (-1) "+str(check)+"\n")

    print("possible_move:")
    player_set_1 = {1}
    player_set_2 = {2}
    l = possible_move(player_set_1, player_set_2, dimension)
    print(l)

    print("test_win:")
    player_set_1 = set()
    player_set_1.add(1)
    print(test_win(player_set_1, dimension, list_win))

"""
    print("test all moves:")
    player_set_1 = set()
    player_set_2 = set()
    n = number_of_winning_moves()
    print(str(n))
"""