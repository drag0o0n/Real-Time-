# Real-Time-



this is a multi-processing application based on the signals facility under
Linux. The idea is to have a parent process fork 10 children processes. The first five forked
children are players that belong to team 1 - the green team while the last 5 are players
that belong to team 2 - the red team.
Each team will be eager to start the race from location A 1 and return to the same location
before the other team. The race scenario can be explained as follows:
• The game playground consists of 5 locations named A 1 to A 5. One player of each
team will be positioned at these 5 locations. For team 1, the first forked child will
be located at location A 1, the second child at location A 2, the third forked child
at location A 3, the fourth forked child at location A 4 and the fifth forked child
at location A 5. For team 2, the sixth forked child will be located at location A 1,
the seventh forked child at location A 2, the eighth forked child at location A 3, the
nineth forked child at location A 4 and the tenth forked child at location A 5.
• Each round of the race starts when the parent gives the order to start. The 2 players
at location A 1 will start running and try to reach location A 2 as quickly as they
can while all the other players do not move. The speed for each player is different
and should be random. When the 2 players reach location A 2, they stop running
and the players located at location A 2 start running towards location A 3. Again,
the speed for the new runners will be different than the previous ones. The same
scenario continues until the last players run from location A 5 back to A 1. The team
that fulfills the round trip first is called the round winner.
• The team that wins should communicate that to the parent process which keeps the
count of winning rounds for each team.
• Once a round is finished, all players for the 2 teams reset their location to the
different steps they belong to and a new round starts when the parent gives the
order.
• The application ends when any of the teams has won a total of a user-defined number
of rounds (default is 5 rounds if no argument is provided by the user). On termination, the parent kills all its child processes, removes any allocated resource and
exits.
