#include "roulette.h"

int msg_id;
int status;
message msg;
credit *cr;
table *tbl;

//funcao comprar
void buy(message *msg)
{
	int _cash_value;

	msg->type = 1;
	msg->pid = getpid();

	printf("   Valor[EUR]: ");
	scanf("%i",&_cash_value);
	msg->request.buy.cash_value=_cash_value;

	status = msgsnd (msg_id, msg,SIZEOF_MSG,0);
	exit_on_error(status,"Envio");

	status = msgrcv(msg_id,msg,SIZEOF_MSG,getpid(), 0);
	exit_on_error(status,"Resposta");

	printf("Fichas: %i\n",msg->request.buy.credits);
	
	system("clear");
	printf("%s\n",msg->request.status.lot);
}

//funcao apostar
void bet(message *msg)
{
	int _credits;
	int _number;
	
	msg->type = 1;
	msg->pid = getpid();

	printf("\n Fichas a Apostar: ");
	scanf("%i",&_credits);
	msg->request.bet.credits=_credits;
		
	//onde bet
	printf("\n   Numeros [1-36]\n");
	printf("   Vermelho [37]\n");
	printf("   Preto [38]\n");
	printf("   1a Metade [39]\n");
	printf("   2a Metade [40]\n");
	printf("   1a Duzia [41]\n");
	printf("   2a Duzia [42]\n");
	printf("   3a Duzia [43]\n");
	printf("   Par [44]\n");
	printf("   Impar [45]\n");

	printf("\n Apostar em: ");
	
	scanf("%i",&_number);
	msg->request.bet.bet_no = _number;
	printf("%i\n",msg->request.bet.credits);
	
	status = msgsnd (msg_id, msg,SIZEOF_MSG,0);
	exit_on_error(status,"Envio");

	status = msgrcv(msg_id,msg,SIZEOF_MSG,getpid(), 0);
	exit_on_error(status,"Resposta");

	system("clear");
	printf("%s\n",msg->request.status.lot);
}

//funcao cancelar
void cancel(message *msg)
{
	msg->type = 1;
	msg->pid = getpid();
	status = msgsnd (msg_id, msg,SIZEOF_MSG,0);
	exit_on_error(status,"Envio");

	status = msgrcv(msg_id,msg,SIZEOF_MSG,getpid(), 0);
	exit_on_error(status,"Resposta");

	system("clear");
	printf("%s\n",msg->request.status.lot);
}

//funcao saldo
void chk_balance(message *msg)
{
	msg->type = 1;
	msg->pid = getpid();

	status = msgsnd (msg_id, msg,SIZEOF_MSG,0);
	exit_on_error(status,"Envio");

	status = msgrcv(msg_id,msg,SIZEOF_MSG,getpid(), 0);
	exit_on_error(status,"Resposta");

	printf(" Saldo Atual: %i\n\n", msg->request.buy.credits);
}

int main()
{
	int op;
	int shm_id;
	int shm_tbl_id;
	
	
	//ligar a fila de mensagens 
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

	//player menu
	while(1)
	{
		//system("clear"); for clear UI, no STATUS msgs tho

		printf("\n User PID (%d)\n",getpid());

		msg.operation = BALANCE;
		chk_balance(&msg);

		printf("   Apostar................1\n");
		printf("   Comprar................2\n");
		printf("   Cancelar Aposta........3\n\n");

		printf("   Sair...................0\n\n   ");
		scanf("%i",&op);
		
		switch(op)
		{

			case 1:
				msg.operation = BET;
				bet(&msg);
				break;
				
			case 2:
				msg.operation = BUY;
				buy(&msg);
				break;

			case 3:
				msg.operation = BET_CANCEL;
				cancel(&msg);
				break;

			case 0: 
				return 0;
				break;
			     	   
			default: 
				printf("Opcao Invalida, Tente Novamente\n");
				sleep(1);
				break;
		}
	}
}
