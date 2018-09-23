#include <TaskScheduler.h>
#include <TaskSchedulerDeclarations.h>
#include <math.h>
int xPin = A1;
int yPin = A0;
int buttonPin = 2;
int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

int a[2][10],curr,anti1,anti1_state,a_where,anti1_where;
int anti2,anti2_state,anti2_where;
Scheduler Sch;

void loop1();
Task t1(150, TASK_FOREVER, &loop1);

void loop2();
Task t2(150, TASK_FOREVER, &loop2);

void loop3();
Task t3(1500, TASK_FOREVER, &loop3);


void loop4();
Task t4(150, TASK_FOREVER, &loop4);


void loop5();
Task t5(2000, TASK_FOREVER, &loop5);


void setup() {
  // put your setup code here, to run once:
  for (int i=0;i<8;i++) a[0][i] = 31+2*i;
  for (int i=0;i<8;i++) pinMode(a[0][i], OUTPUT);
  for (int i=0;i<8;i++) digitalWrite(a[0][i], LOW); 
  
  for (int i=0;i<8;i++) a[1][i] = 30+2*i;
  for (int i=0;i<8;i++) pinMode(a[1][i], OUTPUT);
  for (int i=0;i<8;i++) digitalWrite(a[1][i], LOW); 
  a_where = 0;
  anti1_where = 0;
  anti2_where = 1;
  curr = 0;
  anti1 = anti2 = 4;
  anti1_state = anti2_state = 0;
  digitalWrite(a[a_where][anti1], LOW); 
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //activate pull-up resistor on the push-button pin
  pinMode(buttonPin, INPUT_PULLUP); 
  Sch.addTask(t1); 
  t1.enable();

  Sch.addTask(t2); 
  t2.enable();
  
  Sch.addTask(t3);
  t3.enable();

  Sch.addTask(t4);
  t4.enable();
  
  Sch.addTask(t5);
  t5.enable();
  
}


void loop()
{
  Sch.execute();
}

void light_All()
{
  for (int i=0;i<8;i++) digitalWrite(a[0][i], LOW); 
  for (int i=0;i<8;i++) digitalWrite(a[1][i], LOW); 
  delay(100);
  for (int i=0;i<4;i++) {digitalWrite(a[0][i], HIGH); digitalWrite(a[0][i+4], HIGH); delay(200);}
  for (int i=3;i>=0;i--) {digitalWrite(a[1][i], HIGH); digitalWrite(a[1][i+4], HIGH); delay(200);}
}


void check_dead()
{
  if (anti1 == curr && a_where==anti1_where ) 
  {
    light_All();
    setup();
  }
  if (anti2 == curr && a_where==anti2_where ) 
  {
    light_All();
    setup();
  }
}

void loop1() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  check_dead();
  if (buttonState == 0)
  {
     if (a[a_where][curr] == 30 || a[a_where][curr] == 31 || a[a_where][curr] == 34 || a[a_where][curr] == 35)
     {
        digitalWrite(a[a_where][curr], LOW); 
        a_where=1-a_where;
     }
     else if (a[a_where][curr] == 38 || a[a_where][curr] == 39 || a[a_where][curr] == 42 || a[a_where][curr] == 43)
     {
        digitalWrite(a[a_where][curr], LOW); 
        a_where=1-a_where;
     }
  }
  
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  digitalWrite(a[a_where][curr], LOW); 
  if (xPosition<=50||xPosition>=1000) curr = (curr+4)%8;
  if (yPosition <= 10) curr=(curr-1+8)%8;
  if (yPosition >= 1010) curr = (curr+1)%8;
  digitalWrite(a[a_where][curr], HIGH); 
}


void loop2() {
  if (anti1_state == 0) {digitalWrite(a[anti1_where][anti1], HIGH);anti1_state=1;}
    else {anti1_state = 0;digitalWrite(a[anti1_where][anti1], LOW);}
}


void loop3(){
  int x = anti1;
  if (anti1 - curr <= 4 && anti1 - curr >0 ) anti1=(anti1+7)%8;
    else if (anti1 - curr!=0) anti1=(anti1+1)%8;
  digitalWrite(a[anti1_where][x], LOW);
}


void loop4() {
  if (anti2_state == 0) {digitalWrite(a[anti2_where][anti2], HIGH);anti2_state=1;}
    else {anti2_state = 0;digitalWrite(a[anti2_where][anti2], LOW);}
}

void loop5(){
  int x = anti2;
  if (anti2 - curr <= 4 && anti2 - curr >0 ) anti2=(anti2+7)%8;
    else if (anti2 - curr!=0) anti2=(anti2+1)%8;
  digitalWrite(a[anti2_where][x], LOW);
}


