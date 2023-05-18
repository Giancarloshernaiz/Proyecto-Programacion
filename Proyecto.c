#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <locale.h>
#include <windows.h>

struct info {
        int cedula;
        char nombre [12];
        char apellido [12];
        char departamento[20];
        char cargo[20];
        char fecha[12];
        int salario;
    };

char dept[6][20] = {"RRHH", "Consultoria", "Diseño", "Producción", "Calidad", "Distribución"};
char cargo[6][20] = {"Gerente", "Supervisor", "Analista", "Diseñador", "Desarrollador", "Auditor"};
char motivo_despido[4][20] ={"Traslado", "Renuncia", "Despido", "Otros"};
int validar_numero(char num[]);

void eliminar(){
    int i, k,indice=-1, cedula,numero, op, bandf,re_menu=0;
    char val[20], descarte[20], fecha[12],confirmacion[10],fecha_despido[12],despido[20]; 
    FILE *archivo, *leer, *archivof, *leerf;
    
    
    if((leer = fopen("trabajadores.in", "r")) == NULL){
        printf("¡Error al abrir el archivo!");
    }else{
        k = 0;
        while(!feof(leer)){
            fscanf(leer,"%s %s %s %s %s %s %s\n", descarte,descarte,descarte,descarte,descarte,descarte,descarte);
            k += 1;
        }
    }
    fclose(leer);

    struct info trabajadores[k];
    if((leer = fopen("trabajadores.in", "r")) == NULL){
        printf("¡Error al abrir el archivo!");
    }else{
        i = 0;
        while(!feof(leer)){
            fscanf(leer,"%d", &trabajadores[i].cedula);
            fscanf(leer,"%s", trabajadores[i].nombre);
            fscanf(leer,"%s", trabajadores[i].apellido);
            fscanf(leer,"%s", trabajadores[i].departamento);
            fscanf(leer,"%s", trabajadores[i].cargo);
            fscanf(leer,"%s", trabajadores[i].fecha);
            fscanf(leer,"%d", &trabajadores[i].salario);
            i += 1;
        }
    }
    fclose(leer);//lERR estructura activa


    if(((archivo = fopen("trabajadores.in", "w")) == NULL)||(archivof = fopen("extrabajadores.txt", "a+")) == NULL){
        printf("¡Error al abrir el archivo!");
    }else{
        printf("\nIndique la cédula del trabajador: ");
        do{
            scanf("%s", val);
            numero = validar_numero(val);
        }while(numero == 0);
        cedula = atoi(val); //validar cedula
			for(i = 0; i < k; i++){ //bucle para buscar cedula y confirmacion de eliminacion
        		if(trabajadores[i].cedula == cedula){     		
						printf("Seguro desea eliminar al trabajador:");
						printf("\n%d %s %s %s %s %s %d", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].fecha, trabajadores[i].salario);
		            	printf("\nSeleccione [si]-para Eliminar o [no] para volver al menu principal:");
						scanf("%s",confirmacion);
						do{
							if((strcmp(confirmacion,"si")!=0)&&(strcmp(confirmacion,"no")!=0))
							{
								printf("Ingreso un dato incorrecto, vuelva a intentarlo:");
								scanf("%s",confirmacion);	
							}
						}while((strcmp(confirmacion,"si")!=0)&&(strcmp(confirmacion,"no")!=0));
							if(strcmp(confirmacion,"si")==0)
								{
									indice=i;
								}else{
									re_menu=1;
								}
				}//cierre condicional cedula	
			}// cierre for
					if((strcmp(confirmacion,"si")==0)&&(re_menu==0)){ //codicional para continuar con la eliminacion
					
						do { // bucle de horas
		                bandf = 0;
		                printf("Fecha de retiro (dia-mes-año): "); //ingrese fecha retiro
		                scanf("%s", val);
		                char *dia = strtok(val, "-/ ");
		                char *mes = strtok(NULL, "-/ ");
		                char *anio = strtok(NULL, "-/ ");
		                
		                if (atoi(anio) < 1 || atoi(anio) > 2023){
		                    printf("¡No cumple con el formato de fecha correcto!\n");
		                    bandf = 1;
		                }else if (atoi(anio) == 2023){
		                    if (atoi(mes) < 1 || atoi(mes) > 5){
		                        printf("¡No cumple con el formato de fecha correcto!\n");
		                        bandf = 1;
		                    }else if (atoi(mes) == 5){
		                        if (atoi(dia) < 1 || atoi(dia) > 31){
		                            printf("¡No cumple con el formato de fecha correcto!\n");
		                            bandf = 1;
		                        }
		                    }else{
		                        if (atoi(mes) == 2){
		                            if (atoi(dia) < 1 || atoi(dia) > 29){
		                                printf("¡No cumple con el formato de fecha correcto!\n");
		                                bandf = 1;
		                            }
		                        }else if (atoi(mes) % 2 != 0){
		                            if (atoi(dia) < 1 || atoi(dia) > 31){
		                                printf("¡No cumpe con el formato de fecha correcto!\n");
		                                bandf = 1;
		                            }
		                        }else{
		                            if (atoi(dia) < 1 || atoi(dia) > 30){
		                                printf("¡No cumple con el formato de fecha correcto!\n");
		                                bandf = 1;
		                            }
		                        }
		                    }
		                }else{
		                    if (atoi(mes) == 2){
		                        if (atoi(dia) < 1 || atoi(dia) > 29){
		                            printf("¡No cumple con el formato de fecha correcto!\n");
		                            bandf = 1;
		                        }
		                    }else if (atoi(mes) % 2 != 0){
		                        if (atoi(dia) < 1 || atoi(dia) > 31){
		                            printf("¡No cumple con el formato de fecha correcto!\n");
		                            bandf = 1;
		                        }
		                    }else{
		                        if (atoi(dia) < 1 || atoi(dia) > 30){
		                            printf("¡No cumple con el formato de fecha correcto!\n");
		                            bandf = 1;
		                        }
		                    }
		                }
		            
		                strcpy(fecha_despido, dia);
		                strcat(fecha_despido, "/");
		                strcat(fecha_despido, mes);
		                strcat(fecha_despido, "/");
		                strcat(fecha_despido, anio);
		            	}while(bandf == 1);
		            		/*Motivo de eliminacion de empleado*/
						printf("Motivo de eliminacion:\n[1]-Traslado\n[2]-Renuncia\n[3]-Despido\n[4]-Otros\nSeleccione una opcion:");                                        
		            	do{
		                	do{
		                    scanf("%s", val);
		                    numero = validar_numero(val);
		                }while(numero == 0);
		                numero = atoi(val);
		                if (numero < 1 || numero > 6){
						    printf("El número no corresponde a ninguna Eliminacion!\nIntente de nuevo: ");
		            		}
						}while(numero < 1 || numero > 4);
		            	strcpy(despido,motivo_despido[numero-1]);
        	for(i=0;i<k;i++){//buble para escribir
				 
	           		if(i!=indice){
		           		fprintf(archivo,"%d %s %s %s %s %s %d\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].fecha, trabajadores[i].salario);
		        	}else{
						fprintf(archivof,"%d %s %s %s %s %s %d %s %s\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].fecha, trabajadores[i].salario,despido,fecha_despido);		
					}
				}
            system("cls");			
        	printf("\n¡Se ha eliminado los datos exitosamente!\n");
			}else{
			for(i=0;i<k;i++){//buble para escribir
				 
	           		if(i!=indice){
		           		fprintf(archivo,"%d %s %s %s %s %s %d\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].fecha, trabajadores[i].salario);
		        	}
				}		
				system("cls");
			}	
	}
    fclose(archivo);
    fclose(archivof);
}


void modificar(){
    int i, k, cedula,numero, op, band = 0;
    char val[20], descarte[20], fecha[12]; 
    FILE *archivo, *leer;
    

    if((leer = fopen("trabajadores.in", "r")) == NULL){
        printf("¡Error al abrir el archivo!");
    }else{
        k = 0;
        while(!feof(leer)){
            fscanf(leer,"%s %s %s %s %s %s %s\n", descarte,descarte,descarte,descarte,descarte,descarte,descarte);
            k += 1;
        }
    }
    fclose(leer);

    struct info trabajadores[k];
    if((leer = fopen("trabajadores.in", "r")) == NULL){
        printf("¡Error al abrir el archivo!");
    }else{
        i = 0;
        while(!feof(leer)){
            fscanf(leer,"%d", &trabajadores[i].cedula);
            fscanf(leer,"%s", trabajadores[i].nombre);
            fscanf(leer,"%s", trabajadores[i].apellido);
            fscanf(leer,"%s", trabajadores[i].departamento);
            fscanf(leer,"%s", trabajadores[i].cargo);
            fscanf(leer,"%s", trabajadores[i].fecha);
            fscanf(leer,"%d", &trabajadores[i].salario);
            i += 1;
        }
    }
    fclose(leer);


    if((archivo = fopen("trabajadores.in", "w")) == NULL){
        printf("¡Error al abrir el archivo!");
    }else{
        printf("\nIndique la cédula del trabajador: ");
        do{
            scanf("%s", val);
            numero = validar_numero(val);
        }while(numero == 0);
        cedula = atoi(val);
        for (i = 0; i < k; i++){
            if (trabajadores[i].cedula == cedula){
                do{
                    printf("\nIndique el atributo a modificar: \n");
                    printf("[1] Nombre\n[2] Apellido \n[3] Departamento \n[4] Cargo \n[5] Fecha de ingreso \n[6] Salario\n[7] Salir\n");
                    do{
                        scanf("%s", val);
                        numero = validar_numero(val);
                    }while(numero == 0);
                    op = atoi(val);
                    switch (op){
                    
                        case 1:
                            printf("\nNombre: \n");
                            scanf("%s", trabajadores[i].nombre);
                            band = 1;
                            break; 
                        case 2:
                            printf("\nApellido: \n");
                            scanf("%s", trabajadores[i].apellido);
                            band = 1;
                            break; 
                        case 3:
                            printf("Departamento: \n[1] RRHH \n[2] Consultoria \n[3] Diseéo \n[4] Producción \n[5] Calidad \n[6] Distribución \n");
                            do{
                                do{
                                    scanf("%s", val);
                                    numero = validar_numero(val);
                                }while(numero == 0);
                                numero = atoi(val);
                                if (numero < 1 || numero > 6)
                                    printf("El número no corresponde a ningún departamento!\nIntente de nuevo: ");
                            }while(numero < 1 || numero > 6);
                            strcpy(trabajadores[i].departamento, dept[numero-1]);
                            band = 1;
                            break;
                        case 4:
                            printf("Cargo: \n[1] Gerente \n[2] Supervisor \n[3] Analista \n[4] Diseñador \n[5] Desarrollador \n[6] Auditor \n");
                            do{
                                do{
                                    scanf("%s", val);
                                    numero = validar_numero(val);
                                }while(numero == 0);
                                numero = atoi(val);
                                if (numero < 1 || numero > 6)
                                    printf("El número no corresponde a ningún departamento!\nIntente de nuevo: ");
                            }while(numero < 1 || numero > 6);
                            strcpy(trabajadores[i].cargo, cargo[numero-1]);
                            band = 1;
                            break;  
                        case 5:
                            do {
                                printf("Fecha de ingreso (dia-mes-año): ");
                                band = 0;
                                scanf("%s", val);
                                char *dia = strtok(val, "-/");
                                char *mes = strtok(NULL, "-/");
                                char *anio = strtok(NULL, "-/");
                                
                                if (atoi(anio) < 1 || atoi(anio) > 2023){
                                    printf("¡No cumple con el formato de fecha correcto!\n");
                                    band = 1;
                                }else if (atoi(anio) == 2023){
                                    if (atoi(mes) < 1 || atoi(mes) > 5){
                                        printf("¡No cumple con el formato de fecha correcto!\n");
                                        band = 1;
                                    }else if (atoi(mes) == 5){
                                        if (atoi(dia) < 1 || atoi(dia) > 31){
                                            printf("¡No cumple con el formato de fecha correcto!\n");
                                            band = 1;
                                        }
                                    }else{
                                        if (atoi(mes) == 2){
                                            if (atoi(dia) < 1 || atoi(dia) > 29){
                                                printf("¡No cumple con el formato de fecha correcto!\n");
                                                band = 1;
                                            }
                                        }else if (atoi(mes) % 2 != 0){
                                            if (atoi(dia) < 1 || atoi(dia) > 31){
                                                printf("¡No cumpe con el formato de fecha correcto!\n");
                                                band = 1;
                                            }
                                        }else{
                                            if (atoi(dia) < 1 || atoi(dia) > 30){
                                                printf("¡No cumple con el formato de fecha correcto!\n");
                                                band = 1;
                                            }
                                        }
                                    }
                                }else{
                                    if (atoi(mes) == 2){
                                        if (atoi(dia) < 1 || atoi(dia) > 29){
                                            printf("¡No cumple con el formato de fecha correcto!\n");
                                            band = 1;
                                        }
                                    }else if (atoi(mes) % 2 != 0){
                                        if (atoi(dia) < 1 || atoi(dia) > 31){
                                            printf("¡No cumple con el formato de fecha correcto!\n");
                                            band = 1;
                                        }
                                    }else{
                                        if (atoi(dia) < 1 || atoi(dia) > 30){
                                            printf("¡No cumple con el formato de fecha correcto!\n");
                                            band = 1;
                                        }
                                    }
                                }
                                strcpy(fecha, dia);
                                strcat(fecha, "/");
                                strcat(fecha, mes);
                                strcat(fecha, "/");
                                strcat(fecha, anio);
                            }while(band == 1);
                            strcpy(trabajadores[i].fecha, fecha);
                            band = 1;
                            break; 
                        case 6: 
                            printf("Salario: $");    
                            do{
                                scanf("%s", val);
                                numero = validar_numero(val);
                            }while(numero == 0);
                            trabajadores[i].salario = atoi(val);
                            band = 1;
                            break;
                        case 7:
                            band = 1;
                            break;
                        default:
                            printf("¡Esa opción no existe!");
                            break;
                    }
                }while(band == 0);
            }
            fprintf(archivo,"%d %s %s %s %s %s %d\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].fecha, trabajadores[i].salario);
        }

        fclose(archivo);
       
    }
}

int consulta_cedula(int cedula){
    char dato [20]; 
    FILE *archivo;
    if((archivo = fopen("trabajadores.in", "a+")) == NULL){
        printf("¡Error al abrir el archivo!");
    }else{
        struct info trabajadores;
        while(feof(archivo) == 0){
            fscanf(archivo, "%s", dato);
            if (atoi(dato) == cedula) {
                    trabajadores.cedula = atoi(dato);
                    fscanf(archivo, "%s", trabajadores.nombre);
                    fscanf(archivo, "%s", trabajadores.apellido);
                    fscanf(archivo, "%s", trabajadores.departamento);
                    fscanf(archivo, "%s", trabajadores.cargo);
                    fscanf(archivo, "%s", trabajadores.fecha);
                    fscanf(archivo, "%d", &trabajadores.salario);
                    printf("\n%s %s %d %s %s %s %d\n", trabajadores.nombre, trabajadores.apellido, trabajadores.cedula, trabajadores.departamento, trabajadores.cargo, trabajadores.fecha, trabajadores.salario);
                    return 1;
                }
            }
        }
    fclose(archivo);
    printf("\n¡La CI indicada no está asociada a ningún trabajador de la empresa!\n");
    return 0;
}

void consultar(){ 
    int op, cedula, numero, band = 0;
    char val[20];
    do {
        printf("\nMÉTODO DE CONSULTA: \n[1] Cédula \n[2] Departamento \n[3] Cargo \n[4] Sueldo \n[5] Volver \n");
        do{
            scanf("%s", val);
            numero = validar_numero(val);
        }while(numero == 0);
        op = atoi(val);
        switch (op){
        case 1 :
            printf("\nIndique la cédula a consultar: ");
            do{
                scanf("%s", val);
                numero = validar_numero(val);
            }while(numero == 0);
            cedula = atoi(val);
            consulta_cedula(cedula);
            break;
        case 2 :
            break;

        case 3 :
            break;

        case 4 : 
            break;

        case 5 :
            band = 1; 
            break;

        default:
            printf("La opcion seleccionada es incorrecta!!");
            break;
        }
    }while (band == 0);
    
}

void ingresar(){
    char dato[20], val[20], op;
    FILE *arch;
    int numero, cedula, band = 0;
    if((arch = fopen("trabajadores.in", "a+")) == NULL){
        printf("¡Error al abrir el archivo!");
    }else{
        do {
            struct info trabajadores;
            printf("\nIngrese los datos del trabajador\n");
            printf("Cedula: ");
            do{
                scanf("%s", val);
                numero = validar_numero(val);
            }while(numero == 0);
            trabajadores.cedula = atoi(val);
            int k = 0;
            fscanf(arch, "%d", &cedula);
            while(feof(arch) == 0){
                if (k % 6 == 0){
                    if (trabajadores.cedula == cedula) {
                        printf("¡Esa cédula ya existe!\n");
                        printf("Cedula: ");
                        do{
                            scanf("%s", val);
                            numero = validar_numero(val);
                        }while(numero == 0);
                        trabajadores.cedula = atoi(val);
                        k = -1;
                    }
                    fscanf(arch, "%d", &cedula);
                }
                fscanf(arch,"%s", dato);
                k += 1;
            }
            printf("Nombre: ");
            scanf("%s", trabajadores.nombre);
            printf("Apellido: ");
            scanf("%s", trabajadores.apellido);
            printf("Departamento: \n[1] RRHH \n[2] Consultoria \n[3] Diseño \n[4] Producción \n[5] Calidad \n[6] Distribución \n");
            do{
                do{
                    scanf("%s", val);
                    numero = validar_numero(val);
                }while(numero == 0);
                numero = atoi(val);
                if (numero < 1 || numero > 6)
                    printf("El número no corresponde a ningún departamento!\nIntente de nuevo: ");
            }while(numero < 1 || numero > 6);
            strcpy(trabajadores.departamento, dept[numero-1]);
            printf("Cargo: \n[1] Gerente \n[2] Supervisor \n[3] Analista \n[4] Diseñador \n[5] Desarrollador \n[6] Auditor \n");
            do{
                do{
                    scanf("%s", val);
                    numero = validar_numero(val);
                }while(numero == 0);
                numero = atoi(val);
                if (numero < 1 || numero > 6)
                    printf("El número no corresponde a ningún cargo!\nIntente de nuevo: ");
            }while(numero < 1 || numero > 6);
            strcpy(trabajadores.cargo, cargo[numero -1]);

            do {
                band = 0;
                printf("Fecha de ingreso (dia-mes-año): ");
                scanf("%s", val);
                char *dia = strtok(val, "-/ ");
                char *mes = strtok(NULL, "-/ ");
                char *anio = strtok(NULL, "-/ ");
                
                if (atoi(anio) < 1 || atoi(anio) > 2023){
                    printf("¡No cumple con el formato de fecha correcto!\n");
                    band = 1;
                }else if (atoi(anio) == 2023){
                    if (atoi(mes) < 1 || atoi(mes) > 5){
                        printf("¡No cumple con el formato de fecha correcto!\n");
                        band = 1;
                    }else if (atoi(mes) == 5){
                        if (atoi(dia) < 1 || atoi(dia) > 31){
                            printf("¡No cumple con el formato de fecha correcto!\n");
                            band = 1;
                        }
                    }else{
                        if (atoi(mes) == 2){
                            if (atoi(dia) < 1 || atoi(dia) > 29){
                                printf("¡No cumple con el formato de fecha correcto!\n");
                                band = 1;
                            }
                        }else if (atoi(mes) % 2 != 0){
                            if (atoi(dia) < 1 || atoi(dia) > 31){
                                printf("¡No cumpe con el formato de fecha correcto!\n");
                                band = 1;
                            }
                        }else{
                            if (atoi(dia) < 1 || atoi(dia) > 30){
                                printf("¡No cumple con el formato de fecha correcto!\n");
                                band = 1;
                            }
                        }
                    }
                }else{
                    if (atoi(mes) == 2){
                        if (atoi(dia) < 1 || atoi(dia) > 29){
                            printf("¡No cumple con el formato de fecha correcto!\n");
                            band = 1;
                        }
                    }else if (atoi(mes) % 2 != 0){
                        if (atoi(dia) < 1 || atoi(dia) > 31){
                            printf("¡No cumple con el formato de fecha correcto!\n");
                            band = 1;
                        }
                    }else{
                        if (atoi(dia) < 1 || atoi(dia) > 30){
                            printf("¡No cumple con el formato de fecha correcto!\n");
                            band = 1;
                        }
                    }
                }
                strcpy(trabajadores.fecha, dia);
                strcat(trabajadores.fecha, "/");
                strcat(trabajadores.fecha, mes);
                strcat(trabajadores.fecha, "/");
                strcat(trabajadores.fecha, anio);
            }while(band == 1);
            
            printf("Salario: $");    
            do{
                scanf("%s", val);
                numero = validar_numero(val);
            }while(numero == 0);
            trabajadores.salario = atoi(val);
            fprintf(arch,"%d %s %s %s %s %s %d\n", trabajadores.cedula, trabajadores.nombre, trabajadores.apellido, trabajadores.departamento, trabajadores.cargo, trabajadores.fecha, trabajadores.salario);
            fclose(arch);
            printf("\n¡Se han registrado los datos exitosamente!\n");
            op = 'n';
        }while (op == 's');
    }
}

void menu(){
    int numero, op, x = 0;
    char val [20];
    printf("\n¡Bienvenido al registro de trabajadores de la empresa Future! \n");
    while (x == 0) {
        printf("\nSeleccione una opción\n");
        printf("[1] Ingresar \n[2] Consultar \n[3] Modificar \n[4] Eliminar \n[5] Salir\n");
        do{
            scanf("%s", val);
            numero = validar_numero(val);
        }while(numero == 0);
        op = atoi(val);
        switch (op) {
            case 1: 
                ingresar();
                break;
            case 2:
                consultar();
                break;
            case 3:
                modificar();
                break;
            case 4:
                eliminar();
                break;
            case 5:
                x = 1; 
                break;
            default:
                printf("!Esa opción no existe!\n");
            }
    }
}

int main(){
    setlocale(LC_ALL, "spanish"); 
    SetConsoleCP(1252); 
    SetConsoleOutputCP(1252);
    menu();
    return 0;
}

int validar_numero(char num[]){
    int i, len;
    len = strlen(num);
    for (i = 0; i < len ; i++){
        if (!(isdigit(num[i]))){
            printf("!Solo se permiten números!\nIntente de nuevo: ");
            return 0;
        }
    }
return 1;
}
