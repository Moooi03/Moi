//este es un juego simple donde el codigo, mediante preguntas y por el intento y error, va  atratar de adivinar en que animal estas pensando
//empezando con la base de un caballo, cada vez que el codigo se equivoque te ira pidiendo que coloques preguntas para identificar
//al verdadero animal en el cual estas pensando, las respuestsa solo seran de si o no, y entre mas juegues mas informacion tendra el programa;
//la informacion se ira recopilando en un archivo con nombre "data.pan", este archivo estara en blanco, se podria decir que es un akinator 2.0
//pero con animales.//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1

#define FALSE 0

typedef struct _Nodo
{
   char Texto[80];			
   struct _Nodo *Si, *No;  
   								
} Nodo;

Nodo *Raiz;						
Nodo *Q, *P;					

char Linea[80];				
int n, i;						


int Respuesta(void);
void Borrar(Nodo *A);
Nodo *Cargar(void);
Nodo *LeeArbol(FILE *fe);
void Salvar(Nodo *A);
void EscribeArbol(FILE *fs, Nodo *A);
void VerArbol(Nodo *A);


int main()
{
   int Salir = FALSE;		
   int Resp2;					
	int Resp;				
   char Nuevo[80];			
   char Pregunta[80];		

   Raiz = Cargar();			

   do
   {
   	
      printf("Piensa en un animal y yo intentar‚ adivinarlo.\n");
      printf("Pulsa una tecla para comenzar.\n");
      Respuesta();

      P = Raiz;				

      do							
      {
			Q = P;				
         if(P->Si)         
            printf("%s?\n", P->Texto);	
         else
            printf("Se trata de: %s\n", P->Texto); 

			Resp = Respuesta(); 

         if(P->Si)			
            if(Resp) P = P->Si; else P = P->No;
      }
      while(Q->Si);			

      if(Resp)					
         printf("Lo he adivinado!!!\n");
      else						
      {
         printf("No conozco este animal, pero si me respondes a unas\n");
         printf("preguntas lo incluire en mi lista.\n");
         do						
         {
            printf("\nDe que animal se trata?\n");
            fgets(Nuevo, 80, stdin);	
			   while(Nuevo[strlen(Nuevo) - 1] < ' ')
            	Nuevo[strlen(Nuevo) - 1] = 0; 
            printf("Dame una pregunta que sirva para distinguir un/a\n");
            printf("%s\nde un/a\n%s\n", P->Texto, Nuevo);
            printf("a la que se pueda contestar si o no:\n");
            fgets(Pregunta, 80, stdin);
			   while(Pregunta[strlen(Pregunta) - 1] < ' ')
            	Pregunta[strlen(Pregunta) - 1] = 0; 
            printf("Que respuesta se ha de dar a esta pregunta:\n");
            printf("%s?\n", Pregunta);
            printf("Para obtener: %s\n", Nuevo);
            printf("como respuesta: Si o No:\n");
            Resp = Respuesta();		
            printf("Veamos si lo he entendido bien:\n");
            printf("A la pregunta: %s?\n", Pregunta);
            if(Resp)
            {
               printf("Si se responde SI se trata de un %s\n", Nuevo);
               printf("y si se responde NO de un %s\n", P->Texto);
            }
            else
            {
               printf("Si se responde SI se trata de un %s\n", P->Texto);
               printf("y si se responde NO de un %s\n", Nuevo);
            }
            printf("Es correcto?");
		      Resp2 = Respuesta();	
         }
         while(!Resp2);		
         Q = malloc(sizeof(Nodo)); 	
         strcpy(Q->Texto, P->Texto);
         Q->Si = NULL;					
         Q->No = NULL;					
         if(Resp) P->No = Q;			
         	else P->Si = Q;         

         Q = malloc(sizeof(Nodo));	
         strcpy(Q->Texto, Nuevo);   
         Q->Si = NULL;					
         Q->No = NULL;
         if(Resp) P->Si = Q;			
         else P->No = Q;				

         strcpy(P->Texto, Pregunta);
      }

      printf("Deseas terminar el juego y salir? (S/N)");
      Salir = Respuesta();
   }
   while(!Salir);	

   
   Salvar(Raiz);				
	VerArbol(Raiz);			
   Borrar(Raiz);				
   return 0;					
}
int Respuesta(void)
{
   char Respuesta[10];    
	fgets(Respuesta, 9, stdin);	

   return Respuesta[0] == 'S' || Respuesta[0] == 's';
}


void Borrar(Nodo *A)
{
   if(A->Si) Borrar(A->Si);	
   if(A->No) Borrar(A->No);   
   free(A);                   
}


Nodo *Cargar(void)
{
   FILE *fe;					
   Nodo *A;						

   fe = fopen("Data.pan", "r");	
   if(fe)						
   {
      A = LeeArbol(fe);		
      fclose(fe);				
   }
   else
   {
      A = malloc(sizeof(Nodo));	
      strcpy(A->Texto, "Caballo");
      A->Si = NULL;
      A->No = NULL;
   }
   return(A);					
}

Nodo *LeeArbol(FILE *fe)
{
   Nodo *A;						

//   A = NULL;					
   fgets(Linea, 80, fe);	
   while(Linea[strlen(Linea) - 1] < ' ') Linea[strlen(Linea) - 1] = 0;

   A = malloc(sizeof(Nodo));		
   strcpy(A->Texto, &Linea[1]);  
   										

   if(Linea[0] == 'P')		
   {
      A->Si = LeeArbol(fe);			
      A->No = LeeArbol(fe);         
   }
   else							
   {
      A->Si = NULL;						
      A->No = NULL;	   	   	   
   }

   return(A);
}


void Salvar(Nodo *A)
{
   FILE *fs;					

   fs = fopen("Data.pan", "w");	

   EscribeArbol(fs, A);		
   fclose(fs);					
}


void EscribeArbol(FILE *fs, Nodo *A)
{
	if(A->Si)					
   {
   	fprintf(fs, "P%s\n", A->Texto);	
      EscribeArbol(fs, A->Si);			
      EscribeArbol(fs, A->No);         
   }
   else							
   	fprintf(fs, "R%s\n", A->Texto);	
}


void VerArbol(Nodo *A)
{
	for(i = 0; i < n; i++) putchar(' ');
	n += 3;
   printf(">%s\n", A->Texto);
   if(A->Si) {printf("S "); VerArbol(A->Si);}
   if(A->No) {printf("N "); VerArbol(A->No);}
	n -= 3;
}
