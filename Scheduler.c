#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


//create data structure for storing time (hours and minutes)

struct time {
int hour;
int mins;
};

typedef struct time Time;

//function for subtracting two time strucures
Time subTime (Time t1, Time t2) {
  Time newtime;
  newtime.hour = t1.hour - t2.hour;
  //carry over from the hours if the mins become negative
  if((t1.mins - t2.mins) < 0) {
    newtime.hour--;
    newtime.mins = 60 + (t1.mins - t2.mins);
  } else {
    newtime.mins = (t1.mins - t2.mins);
  }
  return newtime;
}

//function for comparing times: returns 1 if t2>t1 and 0 if t1>t2
int compTime(Time t2, Time t1) {
   if (t2.hour == t1.hour) {
      return (t2.mins>t1.mins ? 1 : 0);
  } else {
    return (t2.hour>t1.hour ? 1 : 0);
  }
}

void printTime(Time t) {
//if mins are single digit add print a zero
  if(t.mins<10) {
  printf("%d:0%d", t.hour, t.mins);
  } else {
  printf("%d:%d", t.hour, t.mins);
  }

}

int main(int argc, char **argv) {
  //create time structures for when the theater opens, closes, and the time needed to clean
  Time interval = {0, 35};
  Time opentime;
  Time finalclosetime;
  //search the arguments to set open and close times
  if(argc == 1) {
    printf("Usage: -monday -tuesday -wednesday etc.\n");
    return 0;
  } else if(argc == 2) {
    if(!strcmp(argv[1], "-monday") || !strcmp(argv[1], "-tuesday") || !strcmp(argv[1], "-wednesday") || !strcmp(argv[1], "-thursday")) {
      opentime.hour = 9;
      opentime.mins = 0;
      finalclosetime.hour = 23;
      finalclosetime.mins = 0;
      printf("\n%s\n\n", argv[1]);
    }else if(!strcmp(argv[1], "-friday") || !strcmp(argv[1], "-saturday") || !strcmp(argv[1], "-sunday")) {
      opentime.hour = 11;
      opentime.mins = 30;
      finalclosetime.hour = 23;
      finalclosetime.mins = 30;
      printf("\n%s\n\n", argv[1]);
    } else {
      printf("Usage: -monday -tuesday -wednesday etc.\n");
      return 0;
    }
  }

  //capture the file from standard input into a string
  char *input;
  int size = 1024;
  input = malloc(size*sizeof(char));
  assert(input);
  int i = 0;
  int linecount = 0;

  for(char ch = getchar(); ch != EOF; ch = getchar()) {
    input[i++] = ch;
    if(i >= (size - 2)) {
      size *= 2;
      input = realloc(input, size*sizeof(char));
      assert(input);
    }
    if(ch == '\n') {
      linecount++;
    }
  }
  input[i] = '\0';

  //create an array of strings for storing tokens
  char *movies[(linecount-1)][4];

  const char s[4]= ",\n";
  char *token = strtok(input, s);
  int j = 0;
  int k = 0;
  while(token != NULL) {
    if(j<4) {
      movies[k][j++] = token;
    } else {
      j = 0;
      k++;
      movies[k][j++] = token;
    }
    token = strtok(NULL, s);
  }

const char d[2] = ":\n";
//cycle through movies
for(k = 0; k < (linecount-1); k++) {

  //cycle through each token of the movie
  for(j=0; j<4; j++) {

      //if we reach the runtime token, parse it then create the schedule
      if(j==3){
        printf("%s\n", movies[k][j]);

        //parsing
        Time runtime;
        char *token2 = strtok(movies[k][j], d);
        runtime.hour = atoi(token2);
        token2 = strtok(NULL, d);
      if(token2 != NULL) {
        runtime.mins = atoi(token2);
        Time tmp;
        Time endtime = finalclosetime;

        //create the schedule
        while(compTime(subTime(endtime, runtime), opentime)) {
          tmp = subTime(endtime, runtime);
          //make the starttimes a multiple of 5
          if((tmp.mins % 5) != 0) {
            Time z = {0, (tmp.mins % 5)};
            tmp = subTime(tmp, z);
            endtime = subTime(endtime, z);
          }

          printf("\t"); printTime(tmp); printf(" - "); printTime(endtime); printf("\n");
          //take away time for cleaning
          endtime = subTime(tmp, interval);
        }
        }

        //print the rest of the info

      } else if (j==2){
        printf(" - Rated%s,", movies[k][j]);
      }else if(j==1){
        continue;
      } else {
        printf("%s", movies[k][j]);
        }
}
  printf("\n");
}

  free(input);
  return 0;
}
