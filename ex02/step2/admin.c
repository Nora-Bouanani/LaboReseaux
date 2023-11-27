/******************************************
  Herman Vanstapel
  2017 Basé sur Fichiers 
*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "LibSerBL.h"

// include pour les fonctions entrees sortie
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

static struct termios old, new;
 
//clrscr() function definition
// #include <stdlib.h>
void ClrScr(void)
{
    system("clear");
}

void Gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y,x);
}

/* Initialize new terminal i/o settings */
// #include <stdio.h>
// #include <stdlib.h>

void initTermios(int echo) 
{
  tcgetattr(0, &old); //grab old terminal i/o settings
  new = old; //make new settings same as old settings
  new.c_lflag &= ~ICANON; //disable buffered i/o
  new.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &new); //apply terminal io settings
}
 
/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}
 
/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}
 
/* 
Read 1 character without echo 
getch() function definition.
*/
char Getch(void) 
{
  return getch_(0);
}
 
/* 
Read 1 character with echo 
getche() function definition.
*/
char GetchE(void) 
{
  return getch_(1);
}



// permet de supprimer le cr qui placé dans la chaine lors d'un fgets
void DelNewLine(char *Chaine)
{

 Chaine[strlen(Chaine)-1] = 0 ;
}



void MonPrintf(char* tempo, int espace,int taille )
{
 int Count ;
 printf("%s",tempo) ; 
 Count = espace-taille ;
 while ( Count>0 )
 {
       printf(" ");
       Count-- ;
 }
}

void AfficheEnteteVehiculeBL ()
{
 char Tampon[80] ;
 sprintf(Tampon,"%s","Ref" ) ;MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s","Constructeur") ;    MonPrintf(Tampon,30,strlen(Tampon)) ;
 sprintf(Tampon,"%s","Modele") ;    MonPrintf(Tampon,30,strlen(Tampon)) ;
 sprintf(Tampon,"%s","Quantite") ; MonPrintf(Tampon,6,strlen(Tampon)) ;
 //----------------ajout------------------------
 sprintf(Tampon,"%s","Portes") ; MonPrintf(Tampon,6,strlen(Tampon)) ; 
 printf("\n") ;
}

void AfficheVehiculeBL (struct VehiculeBL    *UnRecord)
{
 char Tampon[80] ;
 sprintf(Tampon,"%d",UnRecord->Reference ) ;  MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s",UnRecord->Constructeur ) ;    MonPrintf(Tampon,30,strlen(Tampon)) ;
 sprintf(Tampon,"%s",UnRecord->Modele ) ;    MonPrintf(Tampon,30,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UnRecord->Quantite ) ; MonPrintf(Tampon,12,strlen(Tampon)) ;
 //----------------ajout------------------------
 sprintf(Tampon,"%d",UnRecord->Portes ) ; MonPrintf(Tampon,6,strlen(Tampon)) ; 
 printf("\n") ;
}

void SaiSieVehiculeBL (int Reference, struct VehiculeBL  *UnRecord )
{
 char Tampon[80] ;

 printf("Reference :%d \n",Reference) ;
 UnRecord->Reference = Reference ; 
 printf("Saisie Constructeur :") ;
 fgets(UnRecord->Constructeur ,sizeof UnRecord->Constructeur ,stdin ) ;
 printf("Saisie Modele :") ;
 fgets(UnRecord->Modele ,sizeof UnRecord->Modele ,stdin ) ;
 printf("Saisie Quantite :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Quantite = atoi(Tampon) ;
 //----------------ajout------------------------
 printf("Saisie Portes (3 ou 4 ou 5):") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
  UnRecord -> Portes= atoi(Tampon) ; 
 // do
 // {
 //    fgets(Tampon,sizeof Tampon,stdin ) ;
 //    UnRecord -> Portes= atoi(Tampon) ; 

 //    if ((UnRecord -> Portes !=3 ) && (UnRecord -> Portes !=4) && (UnRecord -> Portes !=5 ))
 //    {
 //        printf("Nombres de portes incorrect...\n");
 //    }

 // }while((UnRecord -> Portes !=3 ) && (UnRecord -> Portes !=4) && (UnRecord -> Portes !=5 ));
 

 
 DelNewLine(UnRecord->Constructeur) ;
 DelNewLine(UnRecord->Modele) ;
 AfficheEnteteVehiculeBL () ;
 AfficheVehiculeBL (UnRecord) ;
 printf("-----------------------\n") ;
 return ;
}

int NombreVehiculesBL (char *NomFichier)
{
 FILE *sortie ;
 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Pas de fichier\n") ;
     return 0 ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;
 fseek(sortie, 0, SEEK_END ) ;
 return (ftell(sortie)/ sizeof(struct VehiculeBL  )) ;
}

void CreationAjoutVehiculeBL (char *NomFichier,struct VehiculeBL  *UnRecord )
{
 FILE *sortie ;
 char Redo ;
 int nbr ;

 sortie = fopen(NomFichier,"a") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;

 
  printf("Position actuelle dans le fichier %ld\n",ftell(sortie)) ;
  UnRecord-> Supprime = 0 ;
  nbr = fwrite(UnRecord,sizeof(struct VehiculeBL  ),1,sortie) ;
  fflush(sortie) ;
 fclose(sortie) ;
}



void AfficheFacture(struct FactureBL *UneFacture)
{
 char Tampon[80] ;
 sprintf(Tampon,"%d",UneFacture->NumeroFacturation ) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%s",UneFacture->Acheteur ) ; MonPrintf(Tampon,60,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->Quantite  ) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 sprintf(Tampon,"%d",UneFacture->Reference) ; MonPrintf(Tampon,4,strlen(Tampon)) ;
 
 printf("\n") ;
}

void ListingVehiculesBL (char *NomFichier)
{
 struct VehiculeBL   UnRecord ;
 FILE *sortie ;
 char Tampon[80] ;
 int  Numero ;
 int  nbr ;

 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;

 AfficheEnteteVehiculeBL () ;
 nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;
 
 while ( !feof(sortie) )
 {
  //fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %ld\n",nbr,ftell(sortie)) ;
  AfficheVehiculeBL ( &UnRecord) ;
  nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;
 }
 fclose(sortie) ;
}

void ListingFacturesBL(char *NomFichier)
{
 struct FactureBL UneFacture ;
 FILE *sortie ;
 char Tampon[80] ;
 int  Numero ;
 int  nbr ;

 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;

 
 nbr = fread(&UneFacture,sizeof(struct FactureBL),1,sortie) ;
 
 while ( !feof(sortie) )
 {
  //fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %ld\n",nbr,ftell(sortie)) ;
  AfficheFacture( &UneFacture) ;
  nbr = fread(&UneFacture,sizeof(struct FactureBL ),1,sortie) ;
 }
 fclose(sortie) ;
}

int main()
{
 char Choix ;
 char Tampon[80] ;
 int res ;
 struct VehiculeBL  UnRecord ;
 int Numero ,reference;
 while(1)
 {
  printf("-------2023-----------\n") ; //modifier 
  printf("1) Ajout              \n") ;
  printf("2) Vehicule           \n") ; 
  printf("4) Recherche          \n") ;   
  printf("5) Achat              \n") ;  
  printf("6) Factures           \n") ;
  printf("7) A propos           \n") ;
  printf("8) exit               \n") ; 
  printf("----------------------\n") ; 
  printf(">>") ; Choix=GetchE() ; printf("\n") ;
  switch(Choix)
  {
   case '1': 
             {
              struct VehiculeBL   UnRecord ;
 	     FILE *sortie ;
             char Redo ;
		
             Redo='y' ;
 	    while ( Redo=='Y' || Redo=='y')
 	    { 
             int Nombre ;
             Nombre= NombreVehiculesBL ("VehiculesBL") ;
  	     SaiSieVehiculeBL (Nombre+1, &UnRecord ) ;
  	     CreationAjoutVehiculeBL ("VehiculesBL",&UnRecord) ; 
  	     printf("Encoder un autre (Y/N) ?)") ;
  	     printf(">>") ; Redo=GetchE() ; printf("\n") ;
 	   }
 
	     break ;	
             }
   case '2': ListingVehiculesBL ("VehiculesBL") ;
             break ;
    //------------ajout--------------         
   case '4':printf("Saisie Reference :") ;
            fgets(Tampon,sizeof Tampon,stdin ) ;
            reference = atoi(Tampon) ;
            if((RechercheBL("VehiculesBL",reference,&UnRecord))==1) 
            { 
               AfficheEnteteVehiculeBL();
               AfficheVehiculeBL(&UnRecord);
            }
             break ;

   case '6': ListingFacturesBL("FactureBL") ;
	     break ;
    //------------modification--------------
   case '7': AProposServeurBL("V 1","Bouanani","Laghsas") ; 
             break ;
   
	
   case '8': exit(0) ; 
  }
 }
}
