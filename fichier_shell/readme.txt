voila presque 90% du travail.

	Premièrement, si une commande est en cours d'exécution, un appui sur Contrôle+C interrompe la commande et redonne la main à l'utilisateur sans toutefois quitter le shell. pour le test, j'ai mis un fichier test, qui un itérateur de 1 à 10, avec un sleep.
	tu fait: ./myshell puis ./test et puis Ctrl+C and done ;)

	Deuxièmement, dans eval.c, j'ai remplacer "...execve..." par "...execvp...." pour évaluer les commande directement sans écrire le lien, par exemple ls à la palse de /bin/ls.

	Troisièmement, dans parceline.c j'ai ajouté "if (strchr(argv[argc-1],'&'))...." pour détecter le "&".

	Le programme marche bien pour les exécutions qui ne sont pas en arrière_plan, par exemple si tu met, ./myshell puis gedit test_1.c sans le "&", le programme marche, et si tu met un "Entree", ça te donne la main à l'utilisateur sans toutefois quitter le shell.

	ce qui me reste c'est quand j’écris une commande + le "&", il s’exécute, mais je quitte le shell, on m’affiche 'Fgets Error'
