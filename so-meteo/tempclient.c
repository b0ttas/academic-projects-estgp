#include "asciiesc.h"

void draw_graph()
{
	int maxheight = 25;
	int i,j;
	
	//header
	set_color(RED);
	set_cursor_position(1, 24);	
	printf("Wheather History for Portalegre");
	clear_attr();

	for (i = 20; i>=0; i--) //XX
	{
		set_cursor_position(22 - i+1, 0);
		
		if (i%5 == 0)
		{
			printf("%2d", i); //MARCA OS NRS NA Y SCALE
			set_cursor_position(22 - i+1, 3);		//linha , coluna

			set_background_color(BLACK);
			printf("+");
			
			for (j = 0; j < 24; j++)
			{
				printf("---");
			}

			clear_attr();
		}

		else
		{
			printf("  ");
			set_background_color(BLACK);
			printf("|");
			for (j = 0; j < 24; j++)
			{
			printf("   ");
			}
			
			clear_attr();
		}
	}

	for (i = 0; i <=23 ; i++) //YY
	{
		set_background_color(BLACK);

		set_cursor_position(23,4+3*(i));
		printf("-+-");
		clear_attr();

		set_cursor_position(24,4+3*(i));
		printf("%2d",i );
	}

	fflush(stdout);
}


void draw_spaces(int temp, int hour) //desenha no gráfico
{

	int i;

	set_background_color(GREEN);

	for (i = 0; i<=temp; i++)
	{
		set_cursor_position(22-i, 5+hour*3);
		printf(" ");
	}	
}

void center(int line, int column, const char *s)
{
	set_cursor_position(line, column);
	set_color(GREEN);
	printf("%*s%s%*s", 36 - (int)(strlen(s) / 2), " ", s, 36 - (int)(strlen(s) / 2), " ");
}

//temp,humidade,wind direct,wind speed,condicoes,wind ang,date hour
void add_temp(int temp,int humi, char *windir, float windspeed, char *condition, int hour,char *date)
{	
	char buffer[80];
	int day, earlier_time;
	
	sprintf(buffer, "%s %dh   %dºc   %d%%   %s %.2f km/h   %s",date,hour,temp,humi,windir,windspeed,condition);
	center(2,3,buffer);

	clear_attr();

	if(earlier_time > hour)	
	{
		day++;
		clear_display();
		draw_graph();	
	}


	draw_spaces(temp,hour);
	earlier_time = hour;

	clear_attr();
	fflush(stdout);
	sleep(1);	
}


int main(int argc, char **argv)
{


	int s;
	struct sockaddr_in dest;
	char msg_write[MAXBUF], msg_read[MAXBUF];


	s = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(9999);
	inet_aton("127.0.0.1", (struct in_addr*)&dest.sin_addr.s_addr);

	printf("\nConnecting to server\n");
	if (connect(s, (struct sockaddr*)&dest, sizeof(dest)) == 0)
	{
		printf("Connection established with server\n");
		do {
				// scanf("%s",msg_write);
				write (s, msg_write, strlen(msg_write)+1);
				
				read (s, msg_read, MAXBUF);
				printf("[RCV] %s\n", msg_read);

			
				//if (strcmp(msg_write,"meteo") == 0)
				//{
					//clear_display();
					//draw_graph();

					while(1)
					{
					//do read, get string, convert string to add_temp arguments
					//
					read (s, msg_read, MAXBUF);
					
					printf("%s\n", msg_read);

					}
					
				//}

			} while (strcmp(msg_write,"exit"));
	}
	else {
		printf("Unable to establish connection to server\n");
	}


   close(s);
}