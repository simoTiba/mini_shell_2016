#include "csapp.h"
#define MAXARGS 128
#define MAXJOBS 10

typedef struct {
	int job_number;	// numéro du job(entier>0)
	pid_t job_pid;	// pid du processus qui l'execute
	int sig; 	// état du job
	char cmdline[MAXARGS]; //ligne de commande executée par le job
} job;



// tableau contenant des structures job
job* TabJob;
	

//initialise le tableau
job initialisation(job* TabJob);

//affichage pour le test
void afficher_test(job* TabJob,int TabJob_size);

//numéro de la première case libre du tableau
//int premiere_case(job *TabJob, int TabJob_size);

//numéro du job de premier plan (s'il existe)
int numero_job(job *TabJob, int TabJob_size);

//ajouter un nouveau job
void ajouter_job(job *TabJob, int *TabJob_size, int number, int sign);

//supprime un job
void supprime_job(job *TabJob, int *TabJob_size, int number);

/*   la variable étant partagée entre le programme principal (lance_commande) et
   un handler de signal asynchrone (sigchld), elle dont être marquée volatile 
*/

void sigchld(int signal);
 
