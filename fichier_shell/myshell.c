#include "myshell.h"

// fonctions externes
void eval(char*cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

/*
void sigchld(int signal)
{
  // un signal peut correspondre à plusieurs fils finis, donc on boucle 
  while (1) {
    int status;
    pid_t pid = waitpid(-1,&status,WNOHANG);
    if (pid<0) { 
      if (errno==EINTR) continue; // interrompu => on recommence 
      if (errno==ECHILD) break;   // plus de fils terminé => on quitte
      printf("erreur de wait (%s)\n",strerror(errno));
      break;
    }

    if (pid==0) break; // plus de fils terminé => on quitte 

    //signale à execute que front_pid s'est terminé 
    if (pid==front_pid) front_pid = -1;

  }
}
*/
int main()
{
    	char cmdline[MAXLINE];                 // ligne de commande
    	/*
	int taille = 8;
	job Tab;
	
	 initialisation(&Tab);
	 
	 afficher_test(&Tab,taille); 		//test d'affichage avant l'ajout

	//int t = premiere_case(&Tab, taille);
	//printf("%d\n",t);

	int n = numero_job(&Tab, taille);
	printf("%d\n",n);


	ajouter_job(&Tab, &taille, 3, 8);
	ajouter_job(&Tab, &taille, 2, 5);


	afficher_test(&Tab,taille); 	//test d'affichage apres l'ajout

	supprime_job(&Tab, &taille,3);
	   	
	afficher_test(&Tab,taille); 	//test d'afichage apres la supression
	*/
	
	    
	   /*installation du handler pour le signal SIGCHLD */
	  struct sigaction sig;
	  sig.sa_flags = 0;
	  sig.sa_handler = sigchld;
	  //sigemptyset(&sig.sa_mask);
	  sigaction(SIGCHLD,&sig,NULL);

	  /*désactivation l'interruption par Contrôle+C */
	  sig.sa_handler = SIG_IGN;
	  sigaction(SIGINT, &sig, NULL);

    while (1) {                            // boucle d'interpretation  
        printf("<my_shell> ");             // message d'invite
	Fgets(cmdline, MAXLINE, stdin);    // lire commande
        if (feof(stdin))                   // fin (control-D)
            exit(0);
        eval(cmdline);                     // interpreter commande
    }
    
}

