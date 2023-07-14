#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct map
{

  int values[100][100], numberofnumbers;
};

void createmap(struct map *a)
{

  for (int v = 0; v <= (a->numberofnumbers - 1); v++)
  {
    for (int v2 = 0; v2 <= (a->numberofnumbers - 1); v2++)
    {
      a->values[v][v2] = rand() % 2;
    }
  }
}

void startmap(struct map *a)
{

  printf("   ");
  for (int v = 0; v <= (a->numberofnumbers - 1); v++)
  {
    if (a->numberofnumbers == 10)
    {
      printf("%d. ", v);
    }
    if (a->numberofnumbers == 15)
    {
      if (v < 10)
      {
        printf("%d. ", v);
      }
      else
      {
        printf("%d. ", v);
      }
    }
  }

  printf("\n");

  for (int v = 0; v <= (a->numberofnumbers - 1); v++)
  {
    if (v < 10)
    {
      printf("%d.. ", v);
    }
    else
    {
      printf("%d. ", v);
    }

    for (int v2 = 0; v2 <= (a->numberofnumbers - 1); v2++)
    {
      printf("%d  ", a->values[v][v2]);
    }
    printf("\n");
  }
}

void cleanbuffer(void)
{

  char c;

  while ((c = getchar() != '\n') && (c != EOF))
    ;
}

int verifyNumber(char b){

int value = b;

if(value > 47 && value < 58){
  return 1;
}else{
  return 0;
}
}

void changenumber(struct map *a)
{

  int line, column;
  char inputline, inputcolumn;

  printf("Insert the coordinates of the map: (The first number inserted will "
         "be considered) - insert X to exit the game\n");

  printf("Insert the line:\n");

  scanf("%c", &inputline);
  cleanbuffer();

  if (inputline == 'X' || inputline == 'x')
  {
    exit(0);
  }

  if(!verifyNumber(inputline)){
    printf("Please, insert a correct number (0 to 9)\n");
    sleep(3);
    return;
  }

  printf("Insert the column:\n");

  scanf("%c", &inputcolumn);
  cleanbuffer();

  if (inputcolumn == 'X' || inputcolumn == 'x')
  {
    exit(0);
  }

  if(!verifyNumber(inputcolumn)){
    printf("Please, insert a correct number (0 to 9)\n");
    sleep(3);
    return;
  }

  line = inputline - 48;
  column = inputcolumn - 48;

  int aux;

  if (a->values[line][column] == 1)
  {
    a->values[line][column] = 0;
  }
  else
  {
    a->values[line][column] = 1;
  }
  // special cases:
  if (line == 0 && column == 0)
  {
    if (a->values[9][9] == 1)
    {
      a->values[9][9] = 0;
    }
    else
    {
      a->values[9][9] = 1;
    }
  }
  if (line == 9 && column == 9)
  {
    if (a->values[0][0] == 1)
    {
      a->values[0][0] = 0;
    }
    else
    {
      a->values[0][0] = 1;
    }
  }
  if (line == 0 && column == 9)
  {
    if (a->values[0][9] == 1)
    {
      a->values[0][9] = 0;
    }
    else
    {
      a->values[0][9] = 1;
    }
  }
  if (line == 9 && column == 0)
  {
    if (a->values[9][0] == 1)
    {
      a->values[9][0] = 0;
    }
    else
    {
      a->values[9][0] = 1;
    }
  }

  if (line == (a->numberofnumbers - 1))
  {
    aux = -1;
  }
  else
  {
    aux = line;
  }

  if (a->values[aux + 1][column] == 1)
  {
    a->values[aux + 1][column] = 0;
  }
  else
  {
    a->values[aux + 1][column] = 1;
  }

  if (line == 0)
  {
    aux = a->numberofnumbers;
  }
  else
  {
    aux = line;
  }

  if (a->values[aux - 1][column] == 1)
  {
    a->values[aux - 1][column] = 0;
  }
  else
  {
    a->values[aux - 1][column] = 1;
  }

  if (column == (a->numberofnumbers - 1))
  {
    aux = -1;
  }
  else
  {
    aux = column;
  }

  if (a->values[line][aux + 1] == 1)
  {
    a->values[line][aux + 1] = 0;
  }
  else
  {
    a->values[line][aux + 1] = 1;
  }

  if (column == 0)
  {
    aux = a->numberofnumbers;
  }
  else
  {
    aux = column;
  }

  if (a->values[line][aux - 1] == 1)
  {
    a->values[line][aux - 1] = 0;
  }
  else
  {
    a->values[line][aux - 1] = 1;
  }
}

int verify(struct map *a)
{
  int sum = 0;

  for (int v = 0; v <= (a->numberofnumbers - 1); v++)
  {
    for (int v2 = 0; v2 <= (a->numberofnumbers - 1); v2++)
    {
      sum += a->values[v][v2];
    }
  }
  return sum;
}

void finish(int times)
{

  printf("======Congratulations!======\n");

  printf("You win the game!\n");

  printf("\n");
  printf("Your score will be saved!\n");
  printf("%d times you played to win!", times);
}

void setscore(int times)
{
  int bestscore;
  FILE *score;

  score = fopen("score.txt", "r");

  bestscore = fscanf(score, "%d", &bestscore);

  fclose(score);

  if (bestscore < times)
  {
    bestscore = times;
  }

  score = fopen("score.txt", "w");

  fprintf(score, "%d", bestscore);
  fclose(score);
}

int bestscore()
{
  int bestscore = 0;

  FILE *score;

  score = fopen("score.txt", "r");

  fscanf(score, "%d", &bestscore);

  fclose(score);

  return bestscore;
}
void clearpage() { system("clear"); }
void welcome()
{
  printf("Welcome to 1 and 0 game!\n");

  printf("\n");

  printf("Your best score is: %d\n", bestscore());
  printf("\n");

  sleep(5);
  clearpage();
}

void printscore(int times)
{

  int points = bestscore();

  if (points < times)
  {
    FILE *score;

    score = fopen("score.txt", "w");
    fprintf(score, "%d", points);
    fclose(score);
  }
}

void instructions()
{

  for (int v = 15; v >= 0; v--)
  {
    printf("Instructions:\n");

    printf("In this game, you need to turn all '1' numbers to '0'!\n");
    printf("\n");
    printf("When you change one number, all of the side numbers change too!\n");
    printf("\n");
    printf("You need to think of a strategy to turn the entire board to 0 and win the game! Good luck!\n");
    printf("\n");
    printf("Be careful with the numbers on the ends, they could be the secret to winning!\n");
    printf("\n");

    printf("\n");
    printf("\n");

    printf("The game will start in %d seconds\n", v);
    sleep(1);
    clearpage();
  }
}

int main(void)
{
  int times = 0;

  struct map a;

  a.numberofnumbers = 10;

  welcome();

  instructions();

  createmap(&a);

  while (verify(&a))
  {
    startmap(&a);
    times++;
    changenumber(&a);
    clearpage();
  }

  void finish();
  void setscore();
  void printscore(int times);
}