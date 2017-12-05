/* eval : interprete une ligne de commande passee en parametre       */
#include "myshell.h"

// fonctions externes
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

int front_pid=-1;

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

 void eval(char *cmdline)
{
    char *argv[MAXARGS]; // argv pour execve()
    char buf[MAXLINE];   // contient ligne commande modifiee
    int bg;              // arriere-plan ou premier plan ?
    pid_t pid;           // process id
    sigset_t sigset;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);   
    printf("%d\n",bg); 
    if (argv[0] == NULL)
        return;                      // ignorer lignes vides

    if (!builtin_command(argv)) {    // commande integree ?
          // si oui, executee directement
        if ((pid = Fork()) == 0) {   // si non, executee par un fils
		if(!bg){
		      /*réactivation de SIGINT & débloque SIGCLHD */
		      struct sigaction sig;
		      sig.sa_flags = 0;
		      sig.sa_handler = SIG_DFL;
		      sigemptyset(&sig.sa_mask);
		      sigaction(SIGINT,&sig,NULL);
		      sigprocmask(SIG_UNBLOCK,&sigset,NULL);
		}
	
		
		
		 /*if (execve(argv[0], argv, environ) < 0) {
		        printf("%s: Command not found.\n", argv[0]);
		        exit(0);
		  }*/
		  
		  
	   	 execvp(argv[0], /* programme à exécuter */
		   argv     /* argv du programme à exécuter */
		   );
		   printf("%s: Command not found.\n", argv[0]);
				exit(0);
		  
		  
        }else if (pid > 0){       
        	 if (!bg) {

		      /* attent la fin du processus au premier plan */
		      printf("pid %i\n",pid);
		      front_pid = pid;
		      sigprocmask(SIG_UNBLOCK,&sigset,NULL);

		      /* attente bloquante jusqu'à ce que sigchld signale que front_pid
			 s'est terminé */
		      while (front_pid!=-1) pause();
		  }
            printf("%d %s\n", pid, cmdline);
    	}else{
    		 
    		printf("fork a échoué (%s)\n",strerror(errno));
    	}
   } 
    return;
}

// si le premier parametre est une commande integree,
// l'executer et renvoyer "vrai"
int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "quit")) // commande "quitter"
        exit(0);
    if (!strcmp(argv[0], "&"))    // ignorer & tout seul
        return 1;
    return 0;                     // ce n'est pas une commande integree
}


