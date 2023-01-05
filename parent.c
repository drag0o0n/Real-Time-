/*
Ramiz Alhaj     1181991
Ahmed Barhoum   1183231
Dalia Kusbeh    1182381
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

//Defining Constants
#define NUMBER_OF_CHILDREN 3
#define NUMBER_0F_PLAYERS 2

int number_of_ready_players = 0;  //counter for the number of ready players, reset at the end of every round.
int number_of_rounds = 1;         //the number of needed rounds, it is set to one as a round is initiated by creating the children at first
int big_score1 = 0;               //storing the score of the first player after each round
int big_score2 = 0;               //storing the score of the second player after each round
int *children_pids;               //the pids of all forked processes
char file_name[2][20];            //name of the file that should be created by P1 and P2
int  f_des[2][2];                 //two pipes for communicating between the parent and the referee


//functions' prototypes, each explained in the code below
void sig_quit_catcher(int);
void sig_int_catcher(int);
void start_game();
void calculate_score();
void guess_new_round();
void start_new_round();
void end_game();
void terminate();


int main()
{
  //creating the first pipe for communicating between parent and referee
  if (pipe(f_des[0]) == -1 ) {
    printf("\033[0;31m"); // set the color to red 
    perror("Pipe");
    printf("\033[0m");// reset the color to the default
    exit(-1);
  }  
  //creating the second pipe for communicating between parent and referee
  if (pipe(f_des[1]) == -1 ) {
    printf("\033[0;31m"); // set the color to red 
    perror("Pipe");
    printf("\033[0m");// reset the color to the default
    exit(-1);
  }
  //making the parent process sensitive to both SIGINT and SIGQUIT//
  if ( sigset(SIGQUIT, sig_quit_catcher) == SIG_ERR ) {
    printf("\033[0;31m"); // set the color to red 
      perror("Sigset can not set SIGQUIT");
      printf("\033[0m");// reset the color to the default
      exit(-1);
  } 
  if ( sigset(SIGINT, sig_int_catcher) == SIG_ERR ) {
      printf("\033[0;31m"); // set the color to red 
      perror("Sigset can not set SIGINT");
      printf("\033[0m");// reset the color to the default
      exit(-2);
  }
  start_game();               //forking the children and start the first round
  close(f_des[0][0]);         //close the read end for pipe one  
  close(f_des[1][1]);         //close the write end for pipe two
  
  
  while(1){
    //number_of_ready_players variable is increamented when the parent receives either SIGINT from player1 or SIGQUIT from player2
    //if this variable reaches a 2(Number_of_players) then we need to calculate the score
    if(number_of_ready_players == NUMBER_0F_PLAYERS) {
      number_of_ready_players = 0; 
      calculate_score();
    }
  }
  return(0);
}
//if a quit signal sent by P2 is received by the parent, the number of ready playes is increamented 
void sig_quit_catcher(int sig_num){
    number_of_ready_players+=1;
}
//if a int signal sent by P2 is received by the parent, the number of ready playes is increamented 
void sig_int_catcher(int sig_num){
    number_of_ready_players+=1;
}

void start_game(){
  printf("\033[1;36m"); //set the color to cyan, and make the text bold
  printf("\t\tWe Are Starting This INTERESTING Game!\n");
  printf("\033[0m");    // reset the color to the default
  printf("\t\t--------------------------------------\n\n");
  printf("\033[1;36m"); //set the color to cyan
  printf("The results of round no.%d are as follows:\n",number_of_rounds);
  int i, pid;
  //file descripters of the pipes
  char read_pipe_number1[20], write_pipe_number1[20], read_pipe_number2[20], write_pipe_number2[20]; 
  children_pids = malloc(3 * sizeof(int));
  //Forking
  for ( i = 0; i < NUMBER_OF_CHILDREN; i++ ) {
    //creating the players' files names
    if(i != NUMBER_0F_PLAYERS){               
      sprintf(file_name[i],"child%d.txt",i+1);
    }
    if ((pid = fork()) == -1) {
      printf("\033[0;31m"); // set the color to red 
      printf("fork failure ... getting out\n");
      printf("\033[0m");// reset the color to the default
      exit (-1);
    }
    if ( pid != 0 ) {             //parent 
      *(children_pids+i) = pid; 
    }
    else {                         //forked child
      if (i == NUMBER_0F_PLAYERS){ //referee
        sprintf(read_pipe_number1, "%d", f_des[0][0]);
        sprintf(write_pipe_number1, "%d", f_des[0][1]);
        sprintf(read_pipe_number2, "%d", f_des[1][0]);
        sprintf(write_pipe_number2, "%d", f_des[1][1]);
        execlp("./comparison", "./comparison", read_pipe_number1, write_pipe_number1, read_pipe_number2, write_pipe_number2,(char *) NULL);   
      }
      else{                       //players
        execlp("./child", "./child", file_name[i], "Start", (char *) NULL);
      }
    }
  }
}
/*this function calculates the score of the current round, by sending the files names of the playes to the referee, and then receiving the score
from the referee, all done using the pipes*/
void calculate_score(){
  //pass messgae to referee
  char files_name[41]; 
  sprintf(files_name,"%s-%s",file_name[0],file_name[1]);
  if ( write(f_des[0][1], files_name, sizeof(files_name)) != -1 ) {
  }
  else {
    printf("\033[0;31m"); // set the color to red 
    perror("Write");
    printf("\033[0m");// reset the color to the default
    exit(-1);
  }
  //wait for the reply message from the referee
  char message[20]; 
  if ( read(f_des[1][0], message, sizeof(message)) != -1 ) {
      char *token = strtok(message,"-");
      //printf("P1's Score in Current Round is: %d", atoi(token));
      big_score1 += atoi(token);        //Adding the result to score1 
      char *token2 = strtok(NULL,"\n");
      //printf("\tP2's Score in the Current Round is: %d\n", atoi(token2));
      big_score2 += atoi(token2);       //Adding the result to score2
      printf("BigScore1: %d  \t\t\t BigScore2: %d\n", big_score1, big_score2);
      printf("\033[0m");// reset the color to the default
      printf("\n\t\t==================================================\n");

      
  }
  else {
      printf("\033[0;31m"); // set the color to red 
      perror("Read");
      printf("\033[0m");// reset the color to the default
      exit(-1);
  }
  //guessing the need for a new round  
  guess_new_round();

}

//starting a new round is done by sending the SIGUSR1 to the players.
void start_new_round(){
  number_of_rounds+=1;
  printf("\033[1;36m"); //set the color to cyan
  printf("The results of round no.%d are as follows:\n",number_of_rounds);
  for( int i = 0; i < NUMBER_0F_PLAYERS; i ++){
    kill(*(children_pids+i),SIGUSR1);
  }
}

//if the big_scores are still less than 50, a new round is declared, else end_game is called
void guess_new_round(){
  if (number_of_rounds < 5){                        
    start_new_round();
  }
  else{
    end_game();
  }
}

//end gamr function states the needed number of round and declares the winner adn finally call terminate
void end_game(){
  printf("\033[1m");
  printf("\033[5;33m");    // set the color to yellow
  printf("\n\n\t\t\tWe hope Morocco get the World Cup\n\n");
  printf("\033[0m");
  printf("\033[1;33m");    // set the color to yellow
  printf("The Number Of Rounds We Have is: %d\n\n",number_of_rounds);
  if(big_score1 > big_score2){
    printf("The Winner is: Team1 - Green Team :-)\n");
  }
  else if (big_score1 < big_score2){
    printf("The Winner is: Team2 - Red Team :-)\n");
  }
  else{
    printf("The Winner is no winner: Both Teams Have The Same Result :-)\n"); // 
  }
  terminate();
}
void terminate(){
  //killing the forked processes
  for (int i = 0; i < NUMBER_OF_CHILDREN ; i++){
    kill(*(children_pids+i), SIGTERM);
  }
  //closing the pipes 
  close(f_des[0][1]);
  close(f_des[1][0]);
  //free the children_pids 
  free(children_pids);
  exit(0);
}
