#include "myshell.h"

int i,p;


job initialisation(job* TabJob)
{
	TabJob = malloc(sizeof(job) * MAXJOBS);

	if (TabJob == NULL) {
	    printf("Erreur d'allocation pour TabJob");
	}
	return *TabJob;
}

void afficher_test(job* TabJob,int TabJob_size)
{
	for(i=0; i<TabJob_size; i++)
	{
		printf("%d",TabJob[i].job_number);
		printf("%d",TabJob[i].sig);
		printf("\t");
	}
	printf("\n");	
}


int premiere_case(job *TabJob, int TabJob_size) 
{
	return TabJob_size;
}

int numero_job(job *TabJob, int TabJob_size) 
{
	int num;
	for(i=0; i<TabJob_size; i++)
	{
		if(TabJob[i].sig==SIGCONT)
		{	
			num= TabJob[i].job_number;
		}
		else 
		{
			num = -1;
		}
	}
	return num;
}


void ajouter_job(job *TabJob, int *TabJob_size, int number, int sign)
{

	int j =*TabJob_size;

	if(j<MAXJOBS)
	{
		//manque la ligne de commande
		printf("taille j : %d \n", j);
		TabJob[j].job_number=number;
		TabJob[j].sig=sign;
		(*TabJob_size)++;

	} else
	{
		printf("TabJob is full \n");
	}
}


void supprime_job(job *TabJob, int *TabJob_size, int number)
{
	int j =*TabJob_size;
	if(j != 0)
	{
		for(i=0;i<*TabJob_size; i++){
			if(TabJob[i].job_number == number){
				p=i;				
			}
		}
	
		for(i=p;i<*TabJob_size; i++){
			TabJob[i]=TabJob[i+1];
		}
		(*TabJob_size)--;
	} else 
	{
		printf("TabJob is already empty \n");
	}
		
}


