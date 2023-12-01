#include "LibSerBL.h"

void AProposServeurBL(char *Version,char *Nom1,char* Nom2)
{
 printf("Version : %s \n",Version ) ;
 printf("Nom1 : %s \n",Nom1 ) ;
 printf("Nom2 : %s \n",Nom2 ) ;
}

//----------------ajout------------------------
int RechercheBL(char* NomFichier,int Reference ,struct VehiculeBL *UnRecord) //ajout
{
    FILE *fichier ;

    fichier = fopen(NomFichier, "r");
    if (fichier == NULL) 
    {
        fprintf(stderr,"Echec Ouverture1\n") ;
        exit(0) ;
    }
    else
        fprintf(stderr,"Ouverture reussie \n") ;


    while (fread(UnRecord, sizeof(struct VehiculeBL), 1, fichier) == 1) 
    {
        if (UnRecord->Reference == Reference) 
        {
            
            fclose(fichier);
            return 1; 
        }
        else
        {
            printf("Reference incorrect...\n");
        }
    }

    fclose(fichier);
    return 0;  
}
