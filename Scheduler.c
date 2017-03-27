#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


struct time {
int hour;
int mins;
//ampm = 0 if am 1 if pm
};

typedef struct time Time;

Time addTime (Time t1, Time t2) {
  Time newtime;
  newtime.hour = t1.hour + t2.hour;
  if((t2.mins + t1.mins) >= 60) {
    newtime.hour++;
    newtime.mins = (t2.mins + t1.mins) - 60;
  } else {
    newtime.mins = (t2.mins + t1.mins);
  }
  //newtime.hour = (newtime.hour % 12);
  return newtime;
}

Time subTime (Time t1, Time t2) {
  Time newtime;
  //newtime.ampm = t1.ampm;
  newtime.hour = t1.hour - t2.hour;
  if((t1.mins - t2.mins) < 0) {
    newtime.hour--;
    newtime.mins = 60 + (t1.mins - t2.mins);
  } else {
    newtime.mins = (t1.mins - t2.mins);
  }
//   if(newtime.hour <= 0 ) {
//   newtime.ampm = 0;
//   newtime.hour = newtime.hour + 12;
// }
  return newtime;
}

int compTime(Time t2, Time t1) {
  // if(t2.ampm > t1.ampm) {
  //   return 1;
  // } else if (t2.ampm < t1.ampm){
  //   return 0;
  // } else
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
    //printf("%s\n", token);
    if(j<4) {
      movies[k][j++] = token;
    } else {
      j = 0;
      k++;
      movies[k][j++] = token;
    }
    printf("k %d j %d token %s\n", k, j, token);
    token = strtok(NULL, s);
  }

for(int w = 0; w < (k+1); w++) {
for(j=0; j<4; j++) {
  printf("%s ", movies[w][j]);
}
  printf("\n");
}

Time closetime;
closetime.hour = 23;
closetime.mins = 0;
Time runtime;
runtime.hour = 2;
runtime.mins = 14;
Time opentime;
opentime.hour = 9;
opentime.mins = 0;
Time interval;
interval.hour = 0;
interval.mins = 35;
Time tmp;
while(compTime(subTime(closetime, runtime), opentime)) {
  printf("\t");
  tmp = subTime(closetime, runtime);
  if((tmp.mins % 5) != 0) {
    Time z = {0, (tmp.mins % 5)};
    tmp = subTime(tmp, z);
    closetime = subTime(closetime, z);
  }
  printTime(tmp);
  printf(" - ");
  printTime(closetime);
  printf("\n");
  closetime = subTime(tmp, interval);

}

  free(input);
  return 0;
}
