#include<ncurses.h>
#include<stdlib.h>
using namespace std;
int score=0;
struct node{
int i;
int j;
char a;
node* next;
};
struct node* rev(struct node *head,char &last_move){
struct node *ptr=head;
struct node *ptr1=head->next;
ptr->next=NULL;
struct node *ptr2=head;
while(ptr2!=NULL){
ptr2=ptr1->next;
ptr1->next=ptr;
if(ptr2!=NULL){
ptr=ptr1;
ptr1=ptr2;
}
}
if(last_move=='w'){
last_move='s';
}
else{
if(last_move=='a'){
last_move='d';
}
else{
if(last_move=='s'){
last_move='w';
}
else{
if(last_move=='d'){
last_move='a';
}
}
}
}

head=ptr1;
return head;
}
void food(char a[20][20],int &x,int &y){
for(int i=0;i!=1;i){
x=rand()%19;
y=rand()%19;
if(a[x][y]==' '&& x!=0&&y!=0){
i=1;
score++;
}
}
}
struct node* start_snake(){
struct node *start=NULL;
struct node *ptr=NULL;
int x=9,y=10;
for(int k=0;k<5;k++,y--){
node* n=new node;
n->a='#';
n->next=NULL;
n->i=x;
n->j=y;
if(start==NULL){
start=n;
ptr=n;
}
else{
ptr->next=n;
ptr=ptr->next;
}
}
return start;
}
int start_screen(char a[20][20],int max_col,int max_row){
int flag=0;
for(int i=0;i<max_col;i++){
for(int j=0;j<max_row;j++){
a[i][j]=' ';
}
flag=1;
}
return flag;
}
int game_over(char a[20][20],int new_col,int new_row,int remove_col,int remove_row){
if(new_col==remove_col&&new_row==remove_row){
return 1;
}
else{
if(a[new_col][new_row]=='#'){
return 0;
}
else
return 1;
}
}

void add_snake(struct node* &head,int remove_col,int remove_row){
struct node *n=new node;
struct node *ptr=head;
while(ptr->next!=NULL){
ptr=ptr->next;
}
n->i=remove_col;
n->j=remove_row;
n->a='#';
ptr->next=n;
n->next=NULL;
}
void print_screen(char a[20][20],struct node *head,int &food_col,int &food_row,int remove_col=0,int remove_row=0){
struct node *ptr=head;
if(food_col==ptr->i&&food_row==ptr->j){
food(a,food_col,food_row);
add_snake(head,remove_col,remove_row);
}
else{
a[remove_col][remove_row]=' ';
}
while(ptr!=NULL){
a[ptr->i][ptr->j]=ptr->a;
ptr=ptr->next;
}
a[food_col][food_row]='*';
ptr=head;
while(ptr!=NULL){
move(ptr->i,ptr->j);
addch(ptr->a);
ptr=ptr->next;
}
move(food_col,food_row);
addch('*');
move(remove_col,remove_row);
addch(' ');
move(0,80);
//printw("current score:=%d",score);
move(0,0);
}
struct node* path(char a[20][20],char move,struct node *head,int &remove_col,int &remove_row,char &last_move,int food_col,int food_row){
int new_col,new_row,flag=1;
if(move!='d'&&move!='s'&&move!='a'&&move!='w'){
move=last_move;
}
char move_save=move;
for(int p=0;flag==1;p++){
flag=0;
if(move=='w'){
if(last_move=='s'){
flag=1;
move='s';
}
else {
flag=0;
if(head->i-1<0){
new_col=head->i-1+20;
new_row=head->j;
}
else{
new_col=head->i-1;
new_row=head->j;
}
}
}
else{
if(move=='a'){
if(last_move=='d'){
flag=1;
move='d';
}
else{
flag=0;
if(head->j<=0){
new_col=head->i;
new_row=head->j-1+20;
}
else{
new_col=head->i;
new_row=head->j-1;
}
}
}
else{
if(move=='s'){
if(last_move=='w'){
flag=1;
move='w';
}
else{
flag=0;
if(head->i>=20){
new_col=head->i+1-20;
new_row=head->j;
}
else{
new_col=head->i+1;
new_row=head->j;
}
}
}
else{
if(move=='d'){
if(last_move=='a'){
flag=1;
move='a';
}
else{
flag=0;
if(head->j>=20){
new_col=head->i;
new_row=head->j+1-20;
}
else{
new_col=head->i;
new_row=head->j+1;
}
}
}
}
}
}
}
if(move_save=='a'&&last_move=='d'){
last_move=last_move;
}
else{
if(move_save=='d'&&last_move=='a'){
last_move=last_move;
}
else{
if(move_save=='w'&&last_move=='s'){
last_move=last_move;
}
else{
if(move_save=='s'&&last_move=='w'){
last_move=last_move;
}
else{
if(move!='d'&&move!='s'&&move!='a'&&move!='w'){
move=last_move;
}
else{
last_move=move_save;
}
}
}
}
}
int x,y;
char symbol,swap_symbol;
struct node *ptr1=head;
while(ptr1->next!=NULL){
ptr1=ptr1->next;
}
if(game_over(a,new_col,new_row,ptr1->i,ptr1->j)){
if(food_col==new_col&&food_row==new_row){
symbol='*';
}
else{
symbol='#';
}
struct node *ptr=head;
while(ptr->next!=NULL){
x=ptr->i;
y=ptr->j;
swap_symbol=ptr->a;
ptr->i=new_col;
ptr->a=symbol;
ptr->j=new_row;
new_col=x;
symbol=swap_symbol;
new_row=y;
ptr=ptr->next;
}
remove_col=ptr->i;
remove_row=ptr->j;
ptr->i=new_col;
ptr->j=new_row;
}
}
int main(){
initscr();
noecho();
napms(90);
raw();
nodelay(stdscr, TRUE);
struct node *start=NULL;
struct node *start1=NULL;
char screen[20][20];
start_screen(screen,20,20);
int food_col,food_row,remove_col,remove_row,ncurses_move,flag=0;
char move_start,last_move='p',move1='d';
start=start_snake();
food(screen,food_col,food_row);
print_screen(screen,start,food_col,food_row);
while((move_start=getch())!=1){
napms(90);
if(move_start=='1'){
break;
}
else{
if(move_start=='r'){
start1=rev(start,last_move);
start=start1;
if(move_start=='r'&&move1=='d'){
move_start='a';
}
else{
if(move_start=='r'&&move1=='w'){
move_start='s';
}
else{
if(move_start=='r'&&move1=='s'){
move_start='w';
}
else{
if(move_start=='r'&&move1=='a'){
move_start='d';
}
}
}
}
}
else{
if(move_start=='w'||move_start=='a'||move_start=='s'||move_start=='d'){
move1=move_start;
}
path(screen,move_start,start,remove_col,remove_row,last_move,food_col,food_row);
if(!game_over(screen,start->i,start->j,remove_col,remove_row)&&flag==1){
break;
flag=2;
}
if(move_start=='d'){
flag=1;
}
print_screen(screen,start,food_col,food_row,remove_col,remove_row);

}
}
refresh();
}
move(10,10);
printw("GAME OVER");
move(12,10);
printw("SCORE:=%d",score);
refresh();
napms(1000);
getch();
endwin();
return 0;
}
