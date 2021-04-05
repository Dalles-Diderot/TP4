#include "c_numeration.h"

c_numeration::c_numeration()
{
	m_nbBase10=0;
}
c_numeration::~c_numeration()
{

}

bool c_numeration::setNbBase10(unsigned short nb)
{
	//pas besoin de vérification, m_nbBase10 peut prendre n'importe quelle valeur entre 0 et 65535
	bool retour=false;
	if(nb>1)
	{
		m_nbBase10=nb;
		retour=true;
	}
	return retour;  
}

bool c_numeration::setNbBase10(char *nb)
{
	bool retour=false;
	//On vérifie que la chaine de caractères nb a une longueur d'au maximum 5 caractères
	if(strlen(nb)<6)
	{
	//On appelle convASCII2Int() qui convertit la chaine en nombre entier
		m_nbBase10=convASCII2Int(nb,strlen(nb));
		retour=true;
	}
	return retour;
}

unsigned short c_numeration::getNbBase10()
{
	return m_nbBase10;
}

unsigned short c_numeration::convASCII2Int(char *nb, int taille)
{
	unsigned short int resultat=0;
	unsigned int res=0;

	//On vérifie que la taille de la chaine est bien inférieure à 6 caractères
	for(int i=0;i<taille&&taille<6;i++)
	{
		//Si un caractère de la chaine n'est pas numérique, on retourne 0
		if(nb[i]<'0'||nb[i]>'9')
		{
			res=0;
			break;
		}
		/*On décompose la chaine, on prend un caractère, on lui retire la valeur 48
		  un nombre étant une somme de chiffres pondérés, c'est exactement ce qu'on fait ici:
		  on ajoute la valeur calculée précédemment et on l'ajoute au calcul précédent multiplié par 10.
		  Part exemple, si l'utilisateur saisit la valeur 187, notre méthode va procéder comme suit:
		  	- res vaut 0, le caractère 1 vaut 49
		  	- on soustrait 48 à 49, ce qui donne la valeur numérique 1
		  	- on ajoute 1 à res * 10 soit 0 ce qui donne res égal à 1 en sortie de boucle
		  	- res vaut 1, le caractère 8 vaut 56
		  	- on soustrait 48 à 56, ce qui donne la valeur numérique 8
		  	- on ajoute 8 à res * 10 soit 10 ce qui donne res égal à 18 en sortie de boucle
		  	- res vaut 18, le caractère 7 vaut 55
		  	- on soustrait 48 à 55, ce qui donne la valeur numérique 7
		  	- on ajoute 7 à res * 10 soit 180 ce qui donne res égal à 187 en sortie de boucle */
		res=res*10+(nb[i]-48);
	}

	// Avec ce traitement, on peut gérer des valeurs supérieures à 65535, on décide donc de retourner 0 si tel est le cas
	if(res<65536) resultat=res;
	return resultat;

}

std::string c_numeration::DeterminerBinaire()
{
	//Une seule méthode contient le code permettant de faire la représentation: une seule méthode à déboguer en cas de problème
	return DeterminerNombre('b');
}

std::string c_numeration::DeterminerOctal()
{
	return DeterminerNombre('o');
}

std::string c_numeration::DeterminerHexa()
{
	return DeterminerNombre('h');
}

std::string c_numeration::DeterminerShadok()
{
	return DeterminerNombre('s');
}

std::string c_numeration::DeterminerNombre(char base)
{
	std::string nbChaine;
	int i=0;
	unsigned short basenb=0;
	unsigned short nb[16]={0};
	unsigned short nb10=m_nbBase10;

	//On détermine dans quelle base on va représenter le nombre
	switch(base)
	{
		case 'b': //petite astuce permettant de gérer les majuscules et minuscules en n'utilisant pas break
		case 'B': basenb=2;break;
		case 'o':
		case 'O': basenb=8;break;
		case 'h':
		case 'H': basenb=16;break;
		case 's':
		case 'S': basenb=4;break;
		default: nbChaine="Base non reconnue";
	}

	if(basenb!=0)
	{
		do
		{
			//On utilise ici la méthode du masque sur le chiffre de pois faible
			//Les masques vaudront ici 1, 3, 7 et 15, soit la valeur du plus grand chiffre de chaque base
			nb[i]=nb10&(basenb-1);
			
			//On gère les valeurs ASCII de chaque caractère (0 à 9 et A à F)
			if(nb[i]>9) nb[i]+=55;
			else nb[i]+=48;

			//On insère le caractère trouvé à la première place de la chaine que l'on retourne
			//Cela permet d'avoir un affichage dans le bon sens
			if(basenb!=4)
				nbChaine.insert(0,1,nb[i]);
			else
			{
			//Si on est en base 4, on est en base Shadok, donc on gère un peu différemment le résultat
				switch(nb[i])
				{
					case '0': nbChaine.insert(0,"Ga");break;
					case '1': nbChaine.insert(0,"Bu");break;
					case '2': nbChaine.insert(0,"Zo");break;
					case '3': nbChaine.insert(0,"Meu");break;
				}
			}

			i++;
			//On pratique un décalage vers la gauche du nombre de bits nécessaire pour coder un chiffre dans la base choisie
			//1 pour binaire, 2 pour Shadok, 3 pour octal et 4 pour héxadécimal
			nb10=nb10>>(int)log2(basenb);		

		}while(nb10>0);
	}


return nbChaine;
}
