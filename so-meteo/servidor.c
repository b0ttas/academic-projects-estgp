#include "asciiesc.h"

int client_num = 0;



void *thr_meteo_read(void *ptr)
{
	int client_s = *(int *)ptr;
	char msg[MAXBUF];
	int i;
	

		FILE *infile = fopen("bla.csv","r");
		

		if(infile == NULL)
		{
			printf("\n<<404 Error, Not Found or Unexpected Exit>>\n");
			exit(1);
		}
		
		while(fgets(msg, MAXBUF, infile)!=NULL)
		{

			msg[strcspn(msg,"\r\n")] = '\0';
			//msg não deve guardar caso a linha comece por A-z
			for(i=0; i<client_num; i++)
			{	
				write(client_s, msg, strlen(msg)+1);
			}
			printf("%s\n",msg);
			sleep(1);
		}
	
		
}


//while(!feof(FILE))







int main(int argc, char **argv)
{
	int s, client_s;
  	struct sockaddr_in self, client;
	int addrlen = sizeof(client);

  	pthread_t tclient;  
	
	s = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&self, sizeof(self));
	self.sin_family = AF_INET;
	self.sin_port = htons(9999);
	self.sin_addr.s_addr = INADDR_ANY;

	bind(s, (struct sockaddr*)&self, sizeof(self));

	listen(s, 5);

	while (1) 
	{
		printf("Waiting for clients\n");
		client_s = accept(s, (struct sockaddr*)&client, &addrlen);
		printf("Connection with client established\n");
	
		if(client_s!=0);
		{
			client_num++;
			printf("Now connected: %i Clients\n",client_num);
		}

		if (pthread_create(&tclient, NULL, thr_meteo_read, &client_s) != 0)
		{
		   printf("Error creating thread.\n");
		   return -1;
   		}

	}
}