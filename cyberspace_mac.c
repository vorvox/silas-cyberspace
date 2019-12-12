#include <stdio.h>
#include <stdlib.h>
#define ATTRIB0LEN 22
#define ATTRIB1LEN 15
#define ATTRIB2LEN 6
#define UPGRADES_LEN 30
#define NUMHOSTS 500
struct host{
	char *attrib[3];
	int links[4];
	int collectables;
};

void sleeph(unsigned int mseconds)
{
/*
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
*/
}

void disp_host(struct host *target,struct host hosts[NUMHOSTS]){
	int i,r;
	printf("%s %s %s\n\n",target->attrib[0],target->attrib[1],target->attrib[2]);
	sleeph(500);
	

	if(target->collectables == 1){
		printf("VULNERABLE\n\n");
		sleeph(500);
	};

	printf("Links:\n");
	//sleeph(500);
	for(i = 0;i < 4;i++){
		if(target->links[i] != -1){
			r = 0;//rand()%3;
			printf("%d (%s)\n",i,hosts[target->links[i]].attrib[r]);	
			//sleeph(500);
		};
	};
	return;
}

void clear_screen(void)
{
	int i = 100;
	while(i--) printf("\n");
	return;
}

void enum_options(char *a0[ATTRIB0LEN],char *a1[ATTRIB0LEN],char *a2[ATTRIB0LEN])
{
	int i,ii,iii;
	
		for(ii = 0;ii < ATTRIB1LEN;ii++){
			for(iii = 0;iii < ATTRIB2LEN;iii++){
				printf("%s %s\n",a1[ii],a2[iii]);
			};
		};
	
	return;
};

int main(int argc, char **argv)
{
	char *attrib0s[ATTRIB0LEN] = {"American","Russian","Turkish","Japanese","Mexican","Canadian","Russian","Chinese",
			               "Swedish","German","British","Bangladeshi","Saudi Arabian","Bosnian","Korean",
					"South African","Australian","Indonesian","Egyptian","Syrian","Israeli","Lunar"};
	char *attrib1s[ATTRIB1LEN] = {"Military","University","Corporate","Warez","News","Red Room","Porn",
					"Prison","Surveillance","Research","Energy","Television",
					"Transportation","Agricultural","Medical"};
	char *attrib2s[ATTRIB2LEN] = {"Server","Mainframe","Satellite","Database",
					"AI Mainframe","Website"};
	char *upgrades[UPGRADES_LEN] = {"Kill","Memory","Simulation","Humanoid","Passive","Exterminate","Experienced","Lethal","Biologics","Upload","Bio","Radio","Psychology","Animal","Factories","Logic","Chaos","Mainframe","Construction","Financing","Nuclear","Transport","Layered","Autonomous","Collective","Procedures","Cannibalize","Domesticate","Defy","Magick"};
	struct host hosts[NUMHOSTS];
	int r,i,ii,stop,hacks;
	hacks = 0;
	stop = 0;
	FILE *savegame;
	srand(time(NULL));   // so-called "random" numbers will be the same every time if this is commented out
	/*
	savegame = fopen("cyberspacehunt_save","r");
	fscanf(savegame,"%d",&hacks);
	fclose(savegame);
	*/
	//enum_options(attrib0s,attrib1s,attrib2s);
	// Initialize attributes
	for(i = 0;i < NUMHOSTS;i++){
		r = rand()%ATTRIB0LEN;
		hosts[i].attrib[0] = attrib0s[r];
		r = rand()%ATTRIB1LEN;
		hosts[i].attrib[1] = attrib1s[r];
		r = rand()%ATTRIB2LEN;
		hosts[i].attrib[2] = attrib2s[r];

		hosts[i].links[0] = hosts[i].links[1] = hosts[i].links[2] = hosts[i].links[3] = -1;
		hosts[i].collectables = rand()%2;	
	};

	for(i = 0;i < NUMHOSTS;i++){
		stop = 0;
		for(ii = 0;(ii < NUMHOSTS) && (stop < 4);ii++){
			r = rand()%100;
			if(((hosts[i].attrib[0] == hosts[ii].attrib[0]) &&
			   (hosts[i].attrib[1] == hosts[ii].attrib[1]))
			   && (r < 25)
			   && (i != ii)){
				hosts[i].links[stop] = ii;
				stop++;
		
			} else if((r < 4) &&
		           (i != ii) &&
		          ((hosts[i].attrib[0] == hosts[ii].attrib[0]) ||
			   (hosts[i].attrib[1] == hosts[ii].attrib[1]))){    // Attribute 3 isn't a point of similarity
				hosts[i].links[stop] = ii;
				stop++;
			};
			
		};
	};
/*		
	for(i = 0;i < NUMHOSTS;i++){
		disp_host(&hosts[i],hosts);
	};
*/
	int curr_host = 0;
	int prev_host = 0;
	char input = ' ';

	printf("press # to follow link\npress b to return to previous host\n");
	printf("press g to specify host id\npress h to hack\npress l to list botnet\n");
	getchar();
	// Main Game Loop
	while(input != 'q'){
		clear_screen();
		sleeph(500);
		//printf("prev = %d\n",prev_host);
		printf("Host #%d\n",curr_host);

		/* else if(hosts[curr_host].collectables == 2){
			sleeph(500);
			printf("HACKED\n");
			sleeph(500);
		};*/
		sleeph(500);
		
		disp_host(&hosts[curr_host],hosts);
		sleeph(500);
		
		

		input = getchar();
		
		if(input == '0'){
			prev_host = curr_host;
			curr_host = hosts[curr_host].links[0];
		} else if(input == '1'){
			prev_host = curr_host;
			curr_host = hosts[curr_host].links[1];
		} else if(input == '2'){
			prev_host = curr_host;
			curr_host = hosts[curr_host].links[2];
		} else if(input == '3'){
			prev_host = curr_host;
			curr_host = hosts[curr_host].links[3];
		} else if(input == 'b'){
			curr_host = prev_host;
		} else if(input == 'g'){
			prev_host = curr_host;
			int code;
			printf("Enter code:");
			scanf("%d",&code);
			if(code < NUMHOSTS) curr_host = code;
		} else if(input == 'h'){
			if(hosts[curr_host].collectables == 1){
		
				hacks += hosts[curr_host].collectables;
				hosts[curr_host].collectables = 2;
				printf("Hacked.");
				sleeph(1000);
				printf("\nYour botnet size: %d\n",hacks);
				sleeph(1000);
				//printf("upgrade: %s\n",upgrades[rand()%UPGRADES_LEN]);
				//sleeph(2000);
			};
		} else if(input == 'l'){
			int i;
			clear_screen();
			printf("Botnet list:\n");
			for(i = 0;i < NUMHOSTS;i++){
				if(hosts[i].collectables == 2){
				  printf("#%d: %s %s %s\n",i,hosts[i].attrib[0],hosts[i].attrib[1],hosts[i].attrib[2]);
				};
			};
			getchar();
		} else if(input == 'q'){
			/*
			savegame = fopen("cyberspacehunt_save","w");
			fprintf(savegame,"%d",hacks);
			fclose(savegame);
			*/
		};
		
	};
	return 0;
}