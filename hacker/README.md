# Le principe

la valise est protégée par mot de passe. un keypad permet de rentrer les codes.  
  
La méthode normale permettant d'ouvrir la valise est de rentrer un mot de passe de 4 chiffres (pas de lettres) puis un second mot de passe dans les 30 secondes.
les mots de passes sont générés aléatoirement dès que la valise est mise sous tension.

La solution consiste donc à bruteforcer la valise.

# La technique

pour que le participant puisse réussir l'exercice dans un temps raisonnable, 1 faille hardware  et une faille software sont ajoutées:

faille hardware:
en soulevant un capot, on accède au branchement du Keypad et aux 2 leds de feedback (une rouge = valise verrouillée, une verte = valise ouverte)
ça permet le branchement d'un ESP 32 à la place du keypad pour simuler le fonctionnement de celui ci.
ça permet également d'accéder à la masse du système électrique (via la pin de masse de l'une ou l'autre des leds)
ça permet enfin d'accéder à la pin commandant la led verte pour savoir quand le code est valide.

faille software:
le fonctionnement de l'esp32 interne à la valise est légèrement ralenti pour permettre à l'ESP32 attaquant de le prendre de vitesse et simuler correctement le keypad.


# Fonctionnement global d'un keypad

un keypad est une matrice de boutons mettant en liaison une ligne et une colonne quand le bouton est enfoncé. 
la lecture de keypad se fait par scan. le microcontroleur lecteur met un potentiel haut (ou bas si l'état par défaut est haut) sur une ligne, puis lit l'état de chaque colonne tour à tour. il passe ensuite à la ligne suivante et répète le procédé. 
Le tout est effectué en boucle. 

Lorsqu'une colonne est lue à l'état haut (ou à l'état bas selon l'état par défaut) la touche enfoncée correspond à l'intersection de la ligne en cours de scan et de la colonne dont l'état est différent de l'état par défaut.

# Méthode de hack

1 - il faut déterminer l'état par défaut des colonnes.
solution: il suffit de se brancher sur une colonne, et de faire afficher par la sortie standard l'état de la colonne en continu. l'état majoritaire correspond à l'état par défaut.

2 - il faut ensuite développer une fonction permettant de simuler une touche du keypad.
en gros: 
tant que la ligne correspondante à la touche est à l'état par défaut, l'attaquant maintient toutes les colonnes à l'état par défaut.
dès que la ligne correspondant à la touche voulue passe à l'état actif, la colonne correspondante doit être placée à l'état actif.
dès que la ligne repasse à l'état par défaut, la colonne est ramenée à l'état par défaut.

autrement dit, il faut copier la valeur de la ligne de la touche voulue sur la colonne voulue en temps quasi réel.

3 - le plus dur étant fait, il faut itérer de 0000 à 9999 en écoutant constamment l'état de la led de succès pour déterminer si le code est valide ou non.

4- le fonctionnement à 2 codes permet simplement de vérifier que le mécanisme de bruteforce développé est suffisamment rapide et efficace. (la découverte du 2ème code étant soumise à un timer) mais la méthode est la même.

