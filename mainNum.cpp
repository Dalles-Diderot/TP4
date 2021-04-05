#include "c_numeration.h"
using namespace std;

int main (int argc, char **argv)
{
	c_numeration num;
	string aide;

	//Petite aide qui s'affiche lorsqu'on la demande
	aide="Aide en ligne de la commande num:\nsyntaxes:\t./num [nombre en base 10] [OPTION]\n\t\t./num [OPTION] [nombre en base 10]\n\noptions:\t-b,-B: représentation en binaire\n\t\t-o,-O: représentation en octal\n\t\t-h,-H: représentation en hexadécimal\n\t\t-s,-S: représentation en Shadok\n\t\t--help: affichage de cette aide";

	char indBase=0, indNb=0 ;

	//Si le nombre d'arguments est bien de 3 (eg:./tp4 187 -b)
	if(argc==3)
	{ 
		//On détermine où est l'option, où est le nombre grâce au caractère '-' (le nombre ne peut pas être négatif)
		for(int i=1;i<argc;i++)
		{
			if(argv[i][0]=='-'&&argv[i][1]!='-') indBase=i;
			else indNb=i;
		}

		//On convertit la chaine de caractères correspondant au nombre en base 10 en entier et si c'est OK
		if(num.setNbBase10(argv[indNb]))
		{
			//On détermine pour chaque option la représentation numérique correspondante (on peut écrire -bohs)
			for(int i=1;i<strlen(argv[indBase]);i++)
				cout<<argv[indBase][i]<<": "<<num.DeterminerNombre(argv[indBase][i])<<endl;
		}
		else
		{
			cout<<"Vérifiez votre nombre (valeur max 65535)"<<endl;
		}
	}
	else if(argc<3)
	{
		if(argc==2&&argv[1][1]!='-') cout<<"option non valide!"<<endl;
		else cout<<aide<<endl;
	}
	else
	{
		cout<<"Nombre de paramètres incorrect, "<<argc-1<<" au lieu de 2"<<endl;
	}
	return 0;
}
