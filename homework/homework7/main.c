// based on raul`s code ; para compilar el trabajo lo que vas a hacer es poner primero el main.c en tu compilador web, seguido del registro.h 
//depues de eso hay que crear 5 archivos mas con "cntrl + m" con los siguientes nombres:  sistema.txt, entradas.txt, horario.txt, reporte.txt, salidas.txt;
//estos ultimos 5 archivos estaran en blanco, y al correr el programa se iran llenando automaticamente sigas el programa.
//Todo lo realizado en el programa se iran guardando en los archivos con terminacion ".txt"//

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "registros.h"

int main()
{
    header();
    int i;
    int j;
    int pintemporal;
    matrix = (int*)malloc(sizeof(int) * USUARIOS);
    for (i = 0; i < USUARIOS; i ++){
            matrix[i] = (int*)malloc(sizeof(int) * 6);
            for (j=0; j<6; j++){
            matrix[i][j]=-1;
            }
    }
    int salir=0;
    int opcion=0;
    while(salir==0){
        int limite;
        limite=count();
        printf("\n We have %d registered employees\n", limite);
        printf("check your input well before hitting enter\n");
        printf("*THE FIRST THING YOU NEED TODO IS OPTION 3: REGISTER AN EMPLOYEE, then you can select any other option*");
        printf("\nType\n1 To register an entery \n2 To register an exit\n3 To register an employee\n4 To finish\n");
        scanf("%d", &opcion);
        if (opcion==1){
            
        printf("Please, type your pin\n");
        scanf("%d", &pintemporal);
        
        if (pintemporal<=0){
            printf("Type a valid entry\n");
        }
        
            else if (pintemporal<=limite){
                if (matrix[pintemporal-1][1]==-1){ 
                    entradaosalida(pintemporal, 0);
                }
                else{
                    printf("you have already registered your entry\n");
                }
            }
            else{
                printf("There are %d employees. Invalid pin\n", limite);
            }
        }
        else if (opcion==2){
            
        printf("Please, type your pin\n");
        scanf("%d", &pintemporal);
        
        if (pintemporal<=0){
            printf("Invalid entry\n");
        }
        
            else if (pintemporal<=limite){
                if (matrix[pintemporal-1][1]!=-1){ 
                    entradaosalida(pintemporal, 1);
                }
                else{
                    printf("Please, type an entry to register an exit\n");
                }
            }
            else{
                printf("There are %d employees. Invalid pin\n", limite);
            }
        }
        else if (opcion==3){
            registrar();
        }
        else if (opcion==4){
            int flag=0;
            for (i=0; i<MAX; i++){
                if(matrix[i][0]*matrix[i][1]*matrix[i][2]>0&&matrix[i][3]*matrix[i][4]*matrix[i][5]<0){
                    flag=-1; 
                    printf("Error: User <%d> did not register an exit\n\n", i+1);
                }
            }
            if (flag==0){
            horario();
            printf("Have a nice day :)!\n");
            salir=1;
            }
        }
        else{
            printf("option not available\n\n");
        }
    }

    return 0;
}

int count(){
    FILE* sistema = fopen("sistema.txt", "r");
    char c;
    int count=0;
    while ((c = fgetc(sistema)) != EOF) {
    if (c == '\n') {
      count++; 
    }
    }
    
    return count;
}

void registrar(){
    int pin;
    pin=count()+1;
    char user[MAX];
    int domingo;
    int lunes;
    int martes;
    int miercoles;
    int jueves;
    int viernes;
    int sabado;
    int hora;
    int min;
    int trabajo;
    printf("New pin: <%d>\n", pin);
    registrados++;
    printf("Type an username\n");
    scanf("%s", user);
    
     do{
        printf("\nType 0 (False) and 1 (True) for the days that the employee will work\nFor example: 0 1 1 0 1 1 0\nThere must be at least one 1\n");
        printf("Make sure to write 7 numbers\n");
        printf("Sun Mon Tue Wed Thu Fri Sat\n");
        scanf("%d %d %d %d %d %d %d", &domingo, &lunes, &martes, &miercoles, &jueves, &viernes, &sabado);
    } while(domingo+lunes+martes+miercoles+jueves+viernes+sabado==0||domingo!=0&&domingo!=1||lunes!=0&&lunes!=1||martes!=0&&martes!=1||miercoles!=0&&miercoles!=1||jueves!=0&&jueves!=1||viernes!=0&&viernes!=1||sabado!=0&&sabado!=1);
    
    do {
        printf("\nEnter hour and minute to work (Use an space)\n");
        printf("For example: 23 59\n");
        scanf("%d %d", &hora, &min);
    } while(hora<0||hora>23||min<0||min>60);
        
    do {
        printf("\nType how many seconds will you work? (a number between 1 to 60)\n");
        scanf("%d", &trabajo);
    }while(trabajo<=0||trabajo>60);
    printf("Registered succesfully!!\n\n");
    
    FILE* escribirsistema = fopen("sistema.txt", "a");
    fprintf(escribirsistema, "%d %s %d %d %d %d %d %d %d %d %d %d\n",pin, user, domingo, lunes,martes,miercoles,jueves,viernes,sabado, hora, min, trabajo);
    fclose(escribirsistema);
}

void entradaosalida(int pin, int estado){
    int diferencia=0; 
    time_t tiempoahora;
    time(&tiempoahora);
    struct tm *mitiempo = localtime(&tiempoahora);
    int actualsec=mitiempo->tm_sec;
    int actualmin=mitiempo->tm_min;
    int actualhora=mitiempo->tm_hour;
    int actualyear=mitiempo->tm_year+1900;
    int actualmes=mitiempo->tm_mon+1;
    int actualdia=mitiempo->tm_mday;
    int actualwdia=mitiempo->tm_wday;
    if (estado==0){ //es una entrada
    FILE* entrada = fopen("entradas.txt", "a");
    fprintf(entrada, "%d %d %d/%d/%d %d:%d:%d\n", pin, actualwdia, actualdia, actualmes, actualyear, actualhora, actualmin, actualsec);
    fclose(entrada);
    matrix[pin-1][0]=actualhora;
    matrix[pin-1][1]=actualmin;
    matrix[pin-1][2]=actualsec;
    printf("Entry registered succesfully\n");
    }
    if (estado==1){
    FILE* salida = fopen("salidas.txt", "a"); 
    fprintf(salida, "%d %d %d/%d/%d %d:%d:%d\n", pin, actualwdia, actualdia, actualmes, actualyear, actualhora, actualmin, actualsec);
    fclose(salida);
    printf("Exit registered succesfully\n");
    matrix[pin-1][3]=actualhora;
    matrix[pin-1][4]=actualmin;
    matrix[pin-1][5]=actualsec;
    FILE* reporte = fopen("reporte.txt", "a");
    if (totaldesalidas==0){
        fprintf(reporte, "data generated the day: "); 
            switch(actualwdia){
                case 0:
                fprintf(reporte, "Sunday");
                break;
                case 1:
                fprintf(reporte, "Monday");
                break;
                case 2:
                fprintf(reporte, "Tuesday");
                break;
                case 3:
                fprintf(reporte, "Wednesday");
                break;
                case 4:
                fprintf(reporte, "Thursday");
                break;
                case 5:
                fprintf(reporte, "Friday");
                break;
                case 6:
                fprintf (reporte, "Saturday");
                break;
            }
        fprintf(reporte, " %d/%d/%d\n", actualdia, actualmes, actualyear);
    } 
    
    diferencia=(matrix[pin-1][3]*3600+matrix[pin-1][4]*60+matrix[pin-1][5])-(matrix[pin-1][0]*3600+matrix[pin-1][1]*60+matrix[pin-1][2]);
    int horapin=matrix[pin-1][0];
    int minpin=matrix[pin-1][1];
    int segundopin=matrix[pin-1][2];                                                                            
    fprintf(reporte, "Employee <%d> entered: <%d:%d:%d> the day: <%d/%d/%d> and worked %d seconds\n", pin, horapin, minpin, segundopin, actualdia, actualmes, actualyear, diferencia);
    fclose(reporte);
    matrix[pin-1][0]=-1;
    matrix[pin-1][1]=-1;
    matrix[pin-1][2]=-1;
    matrix[pin-1][3]=-1;
    matrix[pin-1][4]=-1;
    matrix[pin-1][5]=-1;
    
    totaldesalidas=9; 
    }
}

void header(){
    printf("Record of working hours\n");
    time_t tiempoahora;
    time(&tiempoahora);
    struct tm *mitiempo = localtime(&tiempoahora);
    switch(mitiempo->tm_wday){
        case 0:
        printf("Today is Sunday\n");
        break;
        case 1:
        printf("Today is Monday\n");
        break;
        case 2:
        printf("Today is Tuesday\n");
        break;
        case 3:
        printf("Today is Wednesday\n");
        break;
        case 4:
        printf("Today is Thursday\n");
        break;
        case 5:
        printf("Today is Friday\n");
        break;
        case 6:
        printf ("Today is Saturday\n");
        break;
    }
    printf("Day: %d/%d/%d\n", mitiempo->tm_mday, mitiempo->tm_mon+1, mitiempo->tm_year+1900); 
    printf("Hour: %d:%d\n", mitiempo->tm_hour, mitiempo->tm_min);
    printf("You can only enter %d in this system\n", USUARIOS);
}

void horario(){
    time_t tiempoahora;
    time(&tiempoahora);
    int pinleido;
    char usuarioleido[MAX];
    int domingohorario;
    int luneshorario;
    int marteshorario;
    int miercoleshorario;
    int jueveshorario;
    int vierneshorario;
    int sabadohorario;
    int horaleida;
    int minutoleido;
    int trabajo;
    int i;
    struct tm *mitiempo = localtime(&tiempoahora);
    FILE* leersistema = fopen("sistema.txt", "r");
    FILE* escribirhorario = fopen("horario.txt", "w");
    char c;
    int count;
    while (fscanf(leersistema, "%d %s %d %d %d %d %d %d %d %d %d %d\n", &pinleido, usuarioleido, &domingohorario, &luneshorario, &marteshorario, &miercoleshorario, &jueveshorario, &vierneshorario, &sabadohorario, &horaleida, &minutoleido, &trabajo) == 12) {
    fprintf(escribirhorario, "User <%s> with the pin <%d>, must enter at: %d:%d, must work for <%d seconds> the days:\n", usuarioleido, pinleido,horaleida, minutoleido, trabajo);
    if (domingohorario==1)
    fprintf(escribirhorario, "Sunday ");
    if (luneshorario==1)
    fprintf(escribirhorario, "Monday ");
    if (marteshorario==1)
    fprintf(escribirhorario, "Tuesday ");
    if (miercoleshorario==1)
    fprintf(escribirhorario, "Wednesday ");
    if (jueveshorario==1)
    fprintf(escribirhorario, "Thursday ");
    if (vierneshorario==1)
    fprintf(escribirhorario, "Friday ");
    if (sabadohorario==1)
    fprintf(escribirhorario, "Saturday ");
    
    fprintf(escribirhorario, "\n\n");    
    }
    
    
    fclose(leersistema);
    fclose(escribirhorario);
}
