/*
----------------------------------------------------------------
RPG game
By: Tyler Versluys

I used these topics in my programs
	1: Strings
	2: File I/O
	3: Command Line Arguments
	4: Pass by Reference
	5: Structures
	6: Header Files

	After compiling the program, run the program. Make sure to 
use “final.txt” or you can make your own input file. When the game 
starts, it will ask you for basic info like your name that you 
would wish to use. After selecting a class, a monster will appear. 
You start with three attacking options and with levels (you get 
from killing monsters) you can unlock more. Keep attacking the 
monsters until you lose, and see how far you can make it.

----------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Final.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    //Initializing variables
    int x, hit, enemy, class, game = 0, monsterHealth, monsterAttack;
    int i, extraHealth = 0, normalHealth, items, level = 1;
    char junk[100], dump, monsterName[50];

    player player;

    monster zombie;
	monster skeleton;
	monster goblins;
	monster vampire;
	monster golem;

	FILE *fp;
	fp = fopen(argv[1], "r");
	
	if(fp == NULL)
	{
		printf("Syntax error: ./a.out <filename>\n");
		exit(1);
	}

	fscanf(fp, "%d", &items);

    weapon weapon[items];

	for(i = 0; i < items; ++i)
	{
		getitem(fp, &weapon[i]);
	}
    
    //Asks the user basic starting info
    printf("Name: ");
    fgets(player.name, 100, stdin);
    removeN(player.name);

    printf("(M)ale, (F)emale or (O)ther: ");
    scanf("%s", &junk);

    printf("Select your class:\n 1:Warrior\n 2:Archer\n 3:Mage\n");
    scanf("%d", &class);
	
	//"spawns monsters" returns a number
	enemy = spawnMonster(&zombie, &skeleton, &goblins, &vampire, &golem);

	//takes number and makes sets monster stats
	switch(enemy)
	{
		case 1:
			strcpy (monsterName, zombie.name);
			monsterHealth = zombie.Health;
			monsterAttack = zombie.Attack;
			break;
		case 2:
			strcpy (monsterName, skeleton.name);
			monsterHealth = skeleton.Health;
			monsterAttack = skeleton.Attack;
			break;
		case 3:
			strcpy (monsterName, goblins.name);
			monsterHealth = goblins.Health;
			monsterAttack = goblins.Attack;
			break;
		case 4:
			strcpy (monsterName, vampire.name);
			monsterHealth = vampire.Health;
			monsterAttack = vampire.Attack;
			break;
		case 5:
			strcpy (monsterName, golem.name);
			monsterHealth = golem.Health;
			monsterAttack = golem.Attack;
			break;
	}

	//Stores the monsters max health
	normalHealth = monsterHealth;

	//Lets the user know about the monster
	printf("\n\n-------------------------------------------------\n");
	printf("|         A wild %10s has appeared.       |\n", monsterName);
	printf("|          Health: %3d | Attack: %3d            |\n", monsterHealth, monsterAttack);
	printf("-------------------------------------------------\n\n\n");
    
	//sets the players health
    player.Health = 100;

    while (game != 1)
    {
    	//is where the attacking takes place
    	switch(class)
    	{
    		case 1:
				AttackingW(x, &player, monsterName, &monsterHealth, monsterAttack, level, &weapon[0]);
				break;
			case 2:
				AttackingA(x, &player, monsterName, &monsterHealth, monsterAttack, level, &weapon[1]);
				break;
			case 3:
				AttackingM(x, &player, monsterName, &monsterHealth, monsterAttack, level, &weapon[2]);
				break;
			default:
				AttackingW(x, &player, monsterName, &monsterHealth, monsterAttack, level, &weapon[0]);
				break;
    	}

    	//if the player dies, game tells the user that they lost
		if(player.Health <= 0 && monsterHealth > 0)
		{
			for (i = 0; i < 10; ++i)
			{
				printf("\n");
			}

			printf("          You have been killed you lose\n");
			game = 1;
		}

		if (monsterHealth <= 0 && player.Health > 0)
		{
			//leveling system
			level += 1;

			for (i = 0; i < 10; ++i)
			{
				printf("\n");
			}

			//tells user that they killed the monster
			printf("-------------------------------------------------\n");
			printf("|              Congradgulations!                |\n");
			printf("|          You killed the %10s            |\n", monsterName);
			
			//gives some health back to the user
			extraHealth = player.Health;
			player.Health += rand() %(normalHealth) + 1;
			extraHealth = player.Health - extraHealth;

			//makes it so that the player cannot have more than 100 health
			if (player.Health > 100)
				player.Health = 100;

			//"spawns" another monster
			enemy = spawnMonster(&zombie, &skeleton, &goblins, &vampire, &golem);

			switch(enemy)
			{
				case 1:
					strcpy (monsterName, zombie.name);
					monsterHealth = zombie.Health + (level * 2);
					monsterAttack = zombie.Attack;
					break;
				case 2:
					strcpy (monsterName, skeleton.name);
					monsterHealth = skeleton.Health + (level * 2);
					monsterAttack = skeleton.Attack;
					break;
				case 3:
					strcpy (monsterName, goblins.name);
					monsterHealth = goblins.Health + (level * 2);
					monsterAttack = goblins.Attack;
					break;
				case 4:
					strcpy (monsterName, vampire.name);
					monsterHealth = vampire.Health + (level * 2);
					monsterAttack = vampire.Attack;
					break;
				case 5:
					strcpy (monsterName, golem.name);
					monsterHealth = golem.Health + (level * 2);
					monsterAttack = golem.Attack;
					break;
			}

			normalHealth = monsterHealth;

			//tells the user about the new monster
			printf("|          You recieved %3d health              |\n", extraHealth);
			printf("|         A wild %10s has appeared.       |\n", monsterName);
			printf("|          Health: %3d | Attack: %3d            |\n", monsterHealth, monsterAttack);
			printf("-------------------------------------------------\n");

			for (i = 0; i < 10; ++i)
			{
				printf("\n");
			}
		}
    }

	printf("                Your score was %d\n", level - 1);
    printf("                    Game Over.\n");

	for (i = 0; i < 10; ++i)
	{
		printf("\n");
	}

	return 0;
}
