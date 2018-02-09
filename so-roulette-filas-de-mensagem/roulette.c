#include "roulette.h"

message msg;
credit *cr;
table *tbl;

//funcao compara
//compara o tipo de aposta com o outcome, distribui as fichas
int compare(int number)
{
	int i,j;

	for(i=0;i<PL_MAX;i++)
	{
		if(tbl[i].pid!=-1)  //verifica apostas
		{
			if(tbl[i].num==number) //numero
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid)
					{
						cr[j].credits = cr[j].credits+36*tbl[i].credits;
						msg.request.buy.credits= cr[j].credits;
						printf("[WIN]\t\tPID(%i) - +%i credits\n", tbl[i].pid, msg.request.buy.credits);
						break;
					}
				}
			}

		//vermelho
			else if((tbl[i].num==37)&&((number==1)||(number==3)||(number==5)||(number==7)||(number==9)||(number==12)||(number==14)||(number==16)||(number==18)||(number==19)||(number==21)||(number==23)||(number==25)||(number==27)||(number==30)||(number==32)||(number==34)||(number==36)))
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid)
					{
						cr[j].credits = cr[j].credits+(2*tbl[i].credits);
						msg.request.buy.credits= cr[j].credits;
						printf("[WIN]\t\tPID(%i) - +%i credits\n",tbl[i].pid,msg.request.buy.credits);
						break;
					}
				}
			}

		//preto
			else if((tbl[i].num==38)&&((number==2)||(number==4)||(number==6)||(number==8)||(number==10)||(number==11)||(number==13)||(number==15)||(number==17)||(number==20)||(number==22)||(number==24)||(number==26)||(number==28)||(number==29)||(number==31)||(number==33)||(number==35)))
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid){
			
						cr[j].credits = cr[j].credits+(2*tbl[i].credits);
						msg.request.buy.credits= cr[j].credits;
						printf("[WIN]\t\tPID(%i) - +%i credits\n",tbl[i].pid,
 						msg.request.buy.credits);
						break;
					}
				}
			}

		//1a metade
			else if((tbl[i].num==39)&&(1<=number<=18))
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid)
					{
						cr[j].credits = cr[j].credits+(2*tbl[i].credits);
						msg.request.buy.credits= cr[j].credits;
						printf("[WIN]\t\tPID(%i) - +%i credits\n",tbl[i].pid,
						msg.request.buy.credits);
						break;
					}
				}
			}

		//2a metade
			else if((tbl[i].num==40)&&(19<=number<=36))
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid)
					{
						cr[j].credits = cr[j].credits+(2*tbl[i].credits);
						msg.request.buy.credits= cr[j].credits;
						printf("[WIN]\t\tPID(%i) - +%i credits\n",tbl[i].pid, 
						msg.request.buy.credits);
						break;
					}
				}
			}

			//1a duzia
			else if((tbl[i].num==41)&&(1<=number<=12))
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid)
					{
						cr[j].credits = cr[j].credits+(3*tbl[i].credits);
						msg.request.buy.credits= cr[j].credits;
						printf("[WIN]\t\tPID(%i) - +%i credits\n",tbl[i].pid,
						msg.request.buy.credits);
						break;
					}
				}
			}

			//2a duzia
			else if((tbl[i].num==42)&&(13<=number<=24))
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid)
					{
						cr[j].credits = cr[j].credits+(3*tbl[i].credits);
						msg.request.buy.credits= cr[j].credits;
						printf("[WIN]\t\tPID(%i) - +%i credits\n",tbl[i].pid,    
				        msg.request.buy.credits);
						break;
					}
				}
			}

			//3a duzia
			else if((tbl[i].num==43)&&(25<=number<=36))
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid)
					{
						cr[j].credits = cr[j].credits+(3*tbl[i].credits);
						msg.request.buy.credits= cr[j].credits;
						printf("[WIN]\t\tPID(%i) - +%i credits\n",tbl[i].pid, msg.request.buy.credits);
						break;
					}
				}
			}

			//par
			else if((tbl[i].num==44)&&(number % 2==0))
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid)
					{
						cr[j].credits = cr[j].credits+(2*tbl[i].credits);
						msg.request.buy.credits= cr[j].credits;
						printf("[WIN]\t\tPID(%i) - +%i credits\n",tbl[i].pid, msg.request.buy.credits);
						break;
					}
				}
			}

			//impar
			else if((tbl[i].num==45)&&(number % 2 !=0))
			{
				for(j=0;j<PL_MAX;j++)
				{
					if(cr[j].pid==tbl[i].pid)
					{
					cr[j].credits = cr[j].credits+(2*tbl[i].credits);
					msg.request.buy.credits= cr[j].credits;
					printf("[WIN]\t\tPID(%i) - +%i credits\n",tbl[i].pid,
					msg.request.buy.credits);
					break;
				}
			}
		}
		//perder
		else printf("[LOSE]\t\tPID(%i) - -%i credits\n",tbl[i].pid, tbl[i].credits);
		}
	}
}

//funcao buy
void buy( message *msg)
{
	int i;
	int pl_count=0;
	int status;
	int msg_id;

	msg->type= msg->pid;
	msg->request.buy.credits = msg->request.buy.cash_value/5;
	
	for(i=0;i<PL_MAX;i++)
	{	//atualiza fichas
	 	if(cr[i].pid==msg->pid)
	 	{
			cr[i].credits = cr[i].credits + msg->request.buy.credits;
			msg->request.buy.credits=cr[i].credits;
			printf("[BUY]\t\tPID(%i) - %i credits. \n",cr[i].pid,cr[i].credits);
			strcpy(msg->request.status.lot,"\0");
			break;
		}

		//adiciona fichas
		if (cr[i].pid==-1)
		{
			cr[i].pid =msg->pid;
			cr[i].credits = cr[i].credits + msg->request.buy.credits;
			pl_count++;
			msg->request.buy.credits=cr[i].credits;
			printf("[BUY]\t\tPID(%i) - %i credits. \n",cr[i].pid,cr[i].credits);
			strcpy(msg->request.status.lot,"\0");
			break;
		}
			
		//lotacao esgotada
		if(pl_count==PL_MAX)
		{  
			strcpy(msg->request.status.lot,"[ERROR]\tReached Max Player Count");
			break;
		}
	}
}


//funcao cancelar
void cancel(message *msg)
{
	int i,j;
	int status;
	int msg_id;

	msg->type= msg->pid;
	
	for(i=0;i<PL_MAX;i++)
	{
		if(tbl[i].pid==msg->pid)
		{
			for(j=0;j<PL_MAX;j++)
			{
				if(cr[j].pid == tbl[i].pid)
				{
					cr[j].credits=cr[j].credits+tbl[i].credits;
				}
			
			//limpa a aposta da mesa
			tbl[i].pid=-1;
			tbl[i].credits=0;
			tbl[i].num=-1;			
			strcpy(msg->request.status.lot,"[STATUS]\tBet Cancelled\n");	
			}
		}
	}	
}

//funcao bet
void bet(message *msg)
{
	int i,j;
	int pl_pos=-1;
	int status;
	int msg_id;

	msg->type= msg->pid;
	
	//procura pid no array creditos
	for(i=0;i<PL_MAX;i++)
	{
	 	if(cr[i].pid==msg->pid)
	 	{
			pl_pos=i;	
			break;
		}
	}

	//jogador não encontrado
	if (pl_pos==-1)
	{
		printf("[ERROR]\t\tPlayer Not Registered\n");
		strcpy(msg->request.status.lot,"[ERROR]\tPlayer Not Registered");
	}

	else
	{
		//verifica se tem fichas suficientes
		if(cr[pl_pos].credits<msg->request.bet.credits)
		{
			printf("[ERROR]\t\tNot Enough Credits\n");
			strcpy(msg->request.status.lot,"[ERROR]\tNot Enough Credits");
		}	

		//verifica se a aposta e valida
		else if (0>msg->request.bet.bet_no || msg->request.bet.bet_no>47)
		{
			printf("[ERROR]\t\tInvalid Number\n");
			strcpy(msg->request.status.lot,"[ERROR]\tInvalid Number");
		}
			//valida/regista na mesa
		else
		{
			for(i=0;i<PL_MAX;i++)
			{
				//aposta
				if (tbl[i].pid==-1)
				{
					tbl[i].pid=msg->pid;
					tbl[i].credits=msg->request.bet.credits;
					tbl[i].num=msg->request.bet.bet_no;
					strcpy(msg->request.status.lot,"[STATUS]\tBet Registered");
					printf("[NEW BET]\tPID(%i) - %i credits in %i\n",
					tbl[i].pid,tbl[i].credits,tbl[i].num);
	
					for(j=0;j<PL_MAX;j++)
					{
						if(cr[j].pid==msg->pid)
						{
							cr[j].credits = cr[j].credits - tbl[i].credits;
							break;
						}
					}
					
					break;
				}
					
				//altera a aposta
				if(tbl[i].pid==msg->pid)
				{
					for(j=0;j<PL_MAX;j++) //devolve a bet anterior
					{
						if(cr[j].pid==msg->pid)
						{
							cr[j].credits = cr[j].credits + tbl[i].credits;
							break;
						}
					}

					tbl[i].credits=msg->request.bet.credits;
					tbl[i].num=msg->request.bet.bet_no;
					strcpy(msg->request.status.lot,"[STATUS]\tBet Altered");
					printf("[ALTER BET]\tPID(%i) - %i credits in %i\n",
					tbl[i].pid,tbl[i].credits,tbl[i].num);
					
					for(j=0;j<PL_MAX;j++)
					{
						if(cr[j].pid==msg->pid)
						{
							cr[j].credits = cr[j].credits - tbl[i].credits;
							break;
						}
					}

					break;
				}
			}
		}
	}			
}

//inicia array jogadores
void start_player()
{
	int i;

 	for(i=0; i<PL_MAX;i++)
	{
		cr[i].credits= 0;
 		cr[i].pid= -1;
	}
}

//inicia array mesa
void start_tbl()
{
	int i;
 	for(i=0; i<PL_MAX;i++)
	{
		tbl[i].credits= 0;
 		tbl[i].pid= -1;
		tbl[i].num=-1;
	}
}

// funcao sair numero e compara
void num_seed(int sinal)
{		
	int number =1+rand()%36;
	printf("[TABLE]\t\tOutcome: %d\n",number);
	
	//compara as bets com o outcome
	compare(number);

	//limpa a mesa, espera o intervalo
	start_tbl();
	alarm(INTERVAL);
}

//funcao saldo
void balance(message *msg)
{
	int status;
	int msg_id,i;

	msg->type= msg->pid;

	for(i=0;i<PL_MAX;i++)
	{
	 	if(cr[i].pid==msg->pid)
	 	{
			msg->request.buy.credits=cr[i].credits;
			strcpy(msg->request.status.lot,"\0");
			break;
		}
	}
}

int main()
{
	system("clear");
	int msg_id,shm_id;	
	int shm_tbl_id;
	int status;
	int i;

	//inicia gerador rands
	srand(time(NULL));
	
	//ligacao fila de mensagens
	msg_id = msgget (1000, 0600 | IPC_CREAT);
	exit_on_error(msg_id, "Criação/Ligação");


	//shmem creditos
 	shm_id=shmget(1000,PL_MAX*sizeof(credit),0600 |IPC_CREAT);
 	exit_on_error(shm_id,"Criacao");

 	cr = (credit*)shmat (shm_id,NULL,0);
 	exit_on_null(cr, "Attach");

	//shmem mesa
 	shm_tbl_id=shmget(1001,36*sizeof(tbl),0600 |IPC_CREAT);
 	exit_on_error(shm_tbl_id,"Criacao");

 	tbl = (table*)shmat (shm_tbl_id,NULL,0);
 	exit_on_null(tbl, "Attach");

	//output dos nrs
	signal(SIGALRM,num_seed);
	alarm(INTERVAL);

	//inicia array jogadores
	start_player();

	//inicia a mesa
	start_tbl();

	//receber uma mensagem 
	while(1)
	{
		status = msgrcv(msg_id, &msg, SIZEOF_MSG,1,0);

		if(status ==-1 && errno==EINTR)continue;

		exit_on_error(status, "Ler da fila de mensagens");	
		
		//comprar
		if(msg.operation == BUY)
		{
			buy(&msg);
		}

		//apostar
		if(msg.operation == BET)
		{
			bet(&msg);
		}

		//ver saldo
		if(msg.operation == BALANCE)
		{
			balance(&msg);
		}

		//cancelar
		if(msg.operation == BET_CANCEL)
		{
			cancel(&msg);
		}

		//envio de msgs para o jogador
		status = msgsnd(msg_id, &msg,SIZEOF_MSG, 0);
		exit_on_error(status, "Envio");		
	}
}
