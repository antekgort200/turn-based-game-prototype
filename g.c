#include<ncurses.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

void print_gnome(){
	mvprintw(0,10,"            __");
	mvprintw(1,10,"         .-'  |");
	mvprintw(2,10,"        /   <\|");
	mvprintw(3,10,"       /     \'");
	mvprintw(4,10,"       |_.- o-o");
	mvprintw(5,10,"       / C  -._)\"");
	mvprintw(6,10,"      /',        |");
	mvprintw(7,10,"     |   `-,_,__,'");
	mvprintw(8,10,"     (,,)====[_]=|");
	mvprintw(9,10,"       '.   ____/");
	mvprintw(10,10,"        | -|-|_");
	mvprintw(11,10,"        |____)_) ");
}


int main(){
	initscr();
	//data
	const char attack[] = "attack";
        const char potion[] = "potion";
	const char fireball[] = "fireball";
	int ktory = 1;
	int monster = 10;
	int player = 100;
	int manna = 100;
	int potions = 2;
	int killed = 0;
	int player_dmg = 3;
	int znak;
	const short int min_wybor = 1;
	const short int max_wybor = 3;

	do{
		if(monster <= 0){
			//nalicz moc miecza co 15 zabójstw
			killed++;
			if(killed == 15){
				clear();
				printw("you feel blessing upon your sword ,it becomes more powerfull");
				system("aplay bless.wav");
				usleep(100000);
				player_dmg++;
				killed = 0;
			}
			//drop
			srand(time(NULL));
			int drop = 1 + rand()% (2 - 1 + 1);
			if(drop == 1)
				potions++;
			monster = 15;
		}
		if(manna <= 10)
			mvprintw(3,0,"[!]low manna");

		znak = getch();
		clear();
		print_gnome();
		mvprintw(0,0,"monster %d",monster);
		mvprintw(1,0,"player %d", player);
		mvprintw(2,0,"manna %d",manna);
		mvprintw(3,0,"potions %d", potions);
		print_gnome();
		if(znak == 97 && ktory != min_wybor)
			ktory--;
		else if(znak == 122 && ktory != max_wybor)
		       ktory++;
		
		if(znak == 10){
			manna += 5;
			player -= 2;
			switch(ktory){
				case 1:
					monster -= player_dmg;
					break;
				case 2:
					if(potions != 0){
						player += 10;
						potions--;
					}
					break;
				case 3:
					if(manna >= 10){
						monster -= 5;
						manna -= 20;
					}
					break;
			}
		}
		
		switch(ktory){
			case 1:
				mvprintw(6,0,potion);
				mvprintw(7,0,fireball);
				attron(A_REVERSE);
				mvprintw(5,0,attack);
				break;
			case 2:
				mvprintw(5,0,attack);
				mvprintw(7,0,fireball);
				attron(A_REVERSE);
				mvprintw(6,0,potion);
				break;
			case 3:
				mvprintw(5,0,attack);
				mvprintw(6,0,potion);
				attron(A_REVERSE);
				mvprintw(7,0,fireball);
				break;
		}
	attroff(A_REVERSE);
	}while(player != 0);
clear();
printw("game over press any key to continue");
getch();
endwin();

		
}
