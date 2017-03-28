#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

struct time {
int hour;
int mins;
};

typedef struct time Time;

Time subTime (Time t1, Time t2) {
  Time newtime;
  newtime.hour = t1.hour - t2.hour;
  if((t1.mins - t2.mins) < 0) {
    newtime.hour--;
    newtime.mins = 60 + (t1.mins - t2.mins);
  } else {
    newtime.mins = (t1.mins - t2.mins);
  }
  return newtime;
}

int compTime(Time t2, Time t1) {
   if (t2.hour == t1.hour) {
      return (t2.mins>t1.mins ? 1 : 0);
  } else {
    return (t2.hour>t1.hour ? 1 : 0);
  }
}

void printTime(Time t) {

  if(t.mins<10) {
  printf("%d:0%d", t.hour, t.mins);
  } else {
  printf("%d:%d", t.hour, t.mins);
  }

}

int main(int argc, char **argv) {
  Time interval = {0, 35};
  Time opentime;
  Time finalclosetime;

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

for(int w = 0; w < (k+1); w++) {
  for(j=0; j<4; j++) {
  if(j==3){
    printf("%s\n", movies[w][j]);
    Time runtime;
    char *token2 = strtok(movies[w][j], d);
    runtime.hour = atoi(token2);
    token2 = strtok(NULL, d);
  if(token2 != NULL) {
    runtime.mins = atoi(token2);
    Time tmp;
    Time closetime = finalclosetime;
    while(compTime(subTime(closetime, runtime), opentime)) {
      tmp = subTime(closetime, runtime);
      if((tmp.mins % 5) != 0) {
        Time z = {0, (tmp.mins % 5)};
        tmp = subTime(tmp, z);
        closetime = subTime(closetime, z);
      }
      printf("\t"); printTime(tmp); printf(" - "); printTime(closetime); printf("\n");
      closetime = subTime(tmp, interval);
    }
  }
  } else if (j==2){
    printf(" - Rated%s,", movies[w][j]);
  }else if(j==1){
    continue;
  } else {
    printf("%s", movies[w][j]);
    }
}
  printf("\n");
}

  free(input);
  return 0;
}
