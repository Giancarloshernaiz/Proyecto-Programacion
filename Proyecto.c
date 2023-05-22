#include <stdio.h>
#include <string.h> // en clase
#include <stdlib.h> // atoi (para pasar de un string a un numero)
#include <ctype.h> //  distinguir si un carácter es una letra, un número o un espacio
#include <locale.h>

void menu();
void ingresar();
void consultar();
int modificar();
void eliminar();
int consulta_cedula(int cedula);
int consulta_departamento(char departamento_f[]);
int consulta_cargo(char cargo_f[]);
int consulta_sueldo();
int comprobar_elementos(FILE **archivo_f);
int validar_fecha(int anio, int mes, int dia);
int validar_numero(char num[]);

struct info {
        int cedula;
        char nombre [12];
        char apellido [12];
        char departamento[20];
        char cargo[20];
        char fecha[12];
        long salario;
    };
char dept[6][20] = {"RRHH", "Consultoria", "Diseño", "Produccion", "Calidad", "Distribucion"};
char cargo[6][20] = {"Gerente", "Supervisor", "Analista", "Diseñador", "Desarrollador", "Auditor"};
char motivo_despido[4][20] = {"Traslado", "Renuncia", "Despido", "Otros"};

int main(){
    setlocale(LC_ALL, "spanish");
    menu();
    return 0;
}
// procedimientos y funciones
void menu(){
    int numero, op, x = 0;
    char val [20];
    printf("\n!Bienvenido al registro de trabajadores de la empresa Future C.A.! \n");
    while (x == 0) {
        printf("\n+--------- MENU -----------+\n");
        printf("|                          |\n");
        printf("| [1] Ingresar             |\n");
        printf("| [2] Consultar            |\n");
        printf("| [3] Modificar            |\n");
        printf("| [4] Eliminar             |\n");
        printf("| [5] Salir                |\n");
        printf("|                          |\n");
        printf("+--------------------------+\n");
        printf("Opcion: "); 
        do{
            scanf("%s", val);
            numero = validar_numero(val);
        }while(numero == 0);
        op = atoi(val);
        switch (op) {
            case 1:
				system("cls"); 
                ingresar();
                break;
            case 2:
            	system("cls");
                consultar();
                break;
            case 3:
            	system("cls");
                modificar();
                break;
            case 4:
            	system("cls");
                eliminar();
                break;
            case 5:
            	system("cls");
                x = 1;
				printf("\n\t>>> Gracias por Utilizar el Programa");
                break;
            default:
                printf("!Esa opcion no es valida!\n");
            }
    }
}

void ingresar(){
    char dato[20], val[20];
    FILE *arch;
    int numero, cedula, band = 0;
    if((arch = fopen("trabajadores.in", "a+")) == NULL){
        printf(" !Error al abrir el archivo!");
    }else{
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
                    printf("!Esa cedula ya existe!\n");
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
        printf("Departamento: \n[1] RRHH \n[2] Consultoria \n[3] Diseño \n[4] Produccion \n[5] Calidad \n[6] Distribucion \nOpcion: ");
        do{
            do{
                scanf("%s", val);
                numero = validar_numero(val);
            }while(numero == 0);
            numero = atoi(val);
            if (numero < 1 || numero > 6)
                printf("El numero no corresponde a ningun departamento!\nIntente de nuevo: ");
        }while(numero < 1 || numero > 6);
        strcpy(trabajadores.departamento, dept[numero-1]);
        printf("Cargo: \n[1] Gerente \n[2] Supervisor \n[3] Analista \n[4] Diseñador \n[5] Desarrollador \n[6] Auditor \nOpcion: ");
        do{
            do{
                scanf("%s", val);
                numero = validar_numero(val);
            }while(numero == 0);
            numero = atoi(val);
            if (numero < 1 || numero > 6)
                printf("El numero no corresponde a ningun cargo!\nIntente de nuevo: ");
        }while(numero < 1 || numero > 6);
        strcpy(trabajadores.cargo, cargo[numero -1]);

        do {
            band = 0;
            printf("Fecha de ingreso (dia-mes-año): ");
            scanf("%s", val);
            char *dia = strtok(val, "-/ ");
            char *mes = strtok(NULL, "-/ ");
            char *anio = strtok(NULL, "-/ ");
            
            band = validar_fecha(atoi(anio), atoi(mes), atoi(dia));

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
        fprintf(arch,"%d %s %s %s %s %s %ld\n", trabajadores.cedula, trabajadores.nombre, trabajadores.apellido, trabajadores.departamento, trabajadores.cargo, trabajadores.fecha, trabajadores.salario);
        fclose(arch);
        system("cls");
        printf("\n!Se han registrado los datos exitosamente!\n");
    }
}

void consultar(){ 
    int op, cedula, numero, band = 0,departamento;
    char val[20];
    do {
        printf("\n+-- METODO DE CONSULTA --+\n");
        printf("|                        |\n");
        printf("| [1] Cedula             |\n");
        printf("| [2] Departamento       |\n");
        printf("| [3] Cargo              |\n");
        printf("| [4] Sueldo             |\n");
        printf("| [5] Volver             |\n");
        printf("|                        |\n");
        printf("+------------------------+\n");
        printf("Opcion: ");
        do{
            scanf("%s", val);
            numero = validar_numero(val);
        }while(numero == 0);
        op = atoi(val);
        switch (op){
        case 1 :
        	system("cls");
            printf("\nIndique la cedula a consultar: ");
            do{
                scanf("%s", val);
                numero = validar_numero(val);
            }while(numero == 0);
            cedula = atoi(val);
            consulta_cedula(cedula);
            break;
        case 2 :
            system("cls");
            do{
				printf("\nIndique el Departamento a consultar: ");
				printf("\nDepartamento: \n[1] RRHH \n[2] Consultoria \n[3] Diseño \n[4] Produccion \n[5] Calidad \n[6] Distribucion \nOpcion: ");
				do{
                scanf("%s", val);
                        numero = validar_numero(val);
                }while(numero == 0);
                    departamento = atoi(val);
                }while((departamento<1)||(departamento>6));
                band=consulta_departamento(dept[departamento-1]);
            break;
        case 3 :
            system("cls");
			do{
				printf("\nIndique el Cargo a consultar: ");
				printf("\nCargo: \n[1] Gerente \n[2] Supervisor \n[3] Analista \n[4] Diseñador \n[5] Desarrollador \n[6] Auditor \nOpcion: ");
				do{
                	scanf("%s", val);
                	numero = validar_numero(val);
            	}while(numero == 0);
            	numero = atoi(val);
            }while((numero<1)||(numero>6));
                band=consulta_cargo(cargo[numero-1]);
            break;
        case 4 :
            system("cls");
            band = consulta_sueldo();
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

int modificar(){
    int i, k, cedula,numero, op, band = 0;
    char val[20], fecha[12]; 
    FILE *archivo, *leer;
    

    if((leer = fopen("trabajadores.in", "r")) == NULL){
        printf("!Error al abrir el archivo!");
    }else{
      k =comprobar_elementos(&leer); //leer cada elemento para saber la cantidad de lineas
    }
    fclose(leer);

    struct info trabajadores[k];
    if((leer = fopen("trabajadores.in", "r")) == NULL){
        printf("!Error al abrir el archivo!");
    }else{
        i = 0;
        while(!feof(leer)){
            fscanf(leer,"%d", &trabajadores[i].cedula);
            fscanf(leer,"%s", trabajadores[i].nombre);
            fscanf(leer,"%s", trabajadores[i].apellido);
            fscanf(leer,"%s", trabajadores[i].departamento);
            fscanf(leer,"%s", trabajadores[i].cargo);
            fscanf(leer,"%s", trabajadores[i].fecha);
            fscanf(leer,"%ld", &trabajadores[i].salario);
            i += 1;
        }
    }
    fclose(leer);
    
    printf("\nIndique la cedula del trabajador: ");
    do{
        scanf("%s", val);
        numero = validar_numero(val);
    }while(numero == 0);
    cedula = atoi(val);
    for (i = 0; i < k; i++){
        if (trabajadores[i].cedula == cedula){
            band = 1;
            break;
        }
    }
    if (band == 0){ printf("\n!La CI indicada no esta asociada a ningun trabajador de la empresa!\n"); return 0;}
    band = 0;
    if((archivo = fopen("trabajadores.in", "w")) == NULL){
        printf("!Error al abrir el archivo!");
    }else{
        for (i = 0; i < k; i++){
            if (trabajadores[i].cedula == cedula){
                do{
                    printf("\n+--- METODO MODIFICAR ---+\n");
                    printf("|                        |\n");
                    printf("| [1] Nombre             |\n");
                    printf("| [2] Apellido           |\n");
                    printf("| [3] Departamento       |\n");
                    printf("| [4] Cargo              |\n");
                    printf("| [5] Fecha de ingreso   |\n");
                    printf("| [6] Salario            |\n");
                    printf("| [7] Volver             |\n");
                    printf("|                        |\n");
                    printf("+------------------------+\n");
                    printf("Opcion: ");
                    do{
                        scanf("%s", val);
                        numero = validar_numero(val);
                    }while(numero == 0);
                    op = atoi(val);
                    switch (op){
                        case 1:
                            printf("\nNombre: ");
                            scanf("%s", trabajadores[i].nombre);
                            band = 1;
                            break; 
                        case 2:
                            printf("\nApellido: ");
                            scanf("%s", trabajadores[i].apellido);
                            band = 1;
                            break; 
                        case 3:
                            printf("\nDepartamento: \n[1] RRHH \n[2] Consultoria \n[3] Diseño \n[4] Produccion \n[5] Calidad \n[6] Distribucion \nOpcion: ");
                            do{
                                do{
                                    scanf("%s", val);
                                    numero = validar_numero(val);
                                }while(numero == 0);
                                numero = atoi(val);
                                if (numero < 1 || numero > 6)
                                    printf("El numero no corresponde a ningun departamento!\nIntente de nuevo: ");
                            }while(numero < 1 || numero > 6);
                            strcpy(trabajadores[i].departamento, dept[numero-1]);
                            band = 1;
                            break;
                        case 4:
                            printf("Cargo: \n[1] Gerente \n[2] Supervisor \n[3] Analista \n[4] Diseñador \n[5] Desarrollador \n[6] Auditor \nOpcion: ");
                            do{
                                do{
                                    scanf("%s", val);
                                    numero = validar_numero(val);
                                }while(numero == 0);
                                numero = atoi(val);
                                if (numero < 1 || numero > 6)
                                    printf("El numero no corresponde a ningun departamento!\nIntente de nuevo: ");
                            }while(numero < 1 || numero > 6);
                            strcpy(trabajadores[i].cargo, cargo[numero-1]);
                            band = 1;
                            break;  
                        case 5:
                            do {
                                printf("\nFecha de ingreso (dia-mes-año): ");
                                band = 0;
                                scanf("%s", val);
                                char *dia = strtok(val, "-/");
                                char *mes = strtok(NULL, "-/");
                                char *anio = strtok(NULL, "-/");
                                
                                band = validar_fecha(atoi(anio), atoi(mes), atoi(dia));
                                
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
                            printf("\nSalario: $");    
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
                            printf("!Esa opcion no existe!");
                            break;
                    }
                }while(band == 0);
            }
            
            fprintf(archivo,"%d %s %s %s %s %s %ld\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].fecha, trabajadores[i].salario);
        }
        fclose(archivo);
        printf("\n!Se ha modificado exitosamente el archivo!\n");
    }
    return 0;
}

void eliminar(){
    int i, k,indice=-1, cedula,numero, bandf,re_menu=0;
    char val[20], confirmacion[10],fecha_despido[12],despido[20]; 
    FILE *archivo, *leer, *archivof;
    
    
    if((leer = fopen("trabajadores.in", "r")) == NULL){
        printf("!Error al abrir el archivo!");
    }else{
       k=comprobar_elementos(&leer);
    }
    fclose(leer);

    struct info trabajadores[k];
    if((leer = fopen("trabajadores.in", "r")) == NULL){
        printf("!Error al abrir el archivo!");
    }else{
        i = 0;
        while(!feof(leer)){
            fscanf(leer,"%d", &trabajadores[i].cedula);
            fscanf(leer,"%s", trabajadores[i].nombre);
            fscanf(leer,"%s", trabajadores[i].apellido);
            fscanf(leer,"%s", trabajadores[i].departamento);
            fscanf(leer,"%s", trabajadores[i].cargo);
            fscanf(leer,"%s", trabajadores[i].fecha);
            fscanf(leer,"%ld", &trabajadores[i].salario);
            i += 1;
        }
    }
    fclose(leer);//lERR estructura activa

    printf("\nIndique la cedula del trabajador: ");
    do{
        scanf("%s", val);
        numero = validar_numero(val);
    }while(numero == 0);
    cedula = atoi(val); //validar cedula
    if(consulta_cedula(cedula) == 1){
        if(((archivo = fopen("trabajadores.in", "w")) == NULL)||(archivof = fopen("extrabajadores.txt", "a+")) == NULL){
            printf("!Error al abrir el archivo!");
        }else{
            for(i = 0; i < k; i++){ //bucle para buscar cedula y confirmacion de eliminacion
                if(trabajadores[i].cedula == cedula){     		
                    printf("\nSeguro desea eliminar al trabajador:");
                    printf("\nSeleccione [si]-para Eliminar o [no] para volver al menu principal:");
                    scanf("%s",confirmacion);
                do{
                    if((strcmp(confirmacion,"si")!=0)&&(strcmp(confirmacion,"no")!=0)){
                        printf("!Ingreso un dato incorrecto, vuelva a intentarlo!: ");
                        scanf("%s",confirmacion);	
                    }
                    }while((strcmp(confirmacion,"si")!=0)&&(strcmp(confirmacion,"no")!=0));
                    if(strcmp(confirmacion,"si")==0){
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
                    
                    bandf = validar_fecha(atoi(anio), atoi(mes), atoi(dia));
                   
                    strcpy(fecha_despido, dia);
                    strcat(fecha_despido, "/");
                    strcat(fecha_despido, mes);
                    strcat(fecha_despido, "/");
                    strcat(fecha_despido, anio);
                }while(bandf == 1);
                            /*Motivo de eliminacion de empleado*/
                printf("Motivo de eliminacion:\n[1]-Traslado\n[2]-Renuncia\n[3]-Despido\n[4]-Otros\nSeleccione una opcion: ");                                        
                do{
                    do{
                    scanf("%s", val);
                    numero = validar_numero(val);
                }while(numero == 0);
                numero = atoi(val);
                if (numero < 1 || numero > 4){
                    printf("El numero no corresponde a ninguna Eliminacion!\nIntente de nuevo: ");
                    }
                }while(numero < 1 || numero > 4);
                strcpy(despido,motivo_despido[numero-1]);
                for(i=0;i<k;i++){//bucle para escribir
                    if(i!=indice){
                        fprintf(archivo,"%d %s %s %s %s %s %ld\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].fecha, trabajadores[i].salario);
                    }else{
                        fprintf(archivof,"%d %s %s %s %s %s %ld %s %s\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].fecha, trabajadores[i].salario,despido,fecha_despido);		
                    }
                }
                system("cls");
                printf("\n!Se ha eliminado los datos exitosamente!\n");
                }else{
                    for(i=0;i<k;i++){//buble para escribir
                        if(i!=indice){
                            fprintf(archivo,"%d %s %s %s %s %s %ld\n", trabajadores[i].cedula, trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].departamento, trabajadores[i].cargo, trabajadores[i].fecha, trabajadores[i].salario);
                        }
                    }
                system("cls");
                }
        }
        fclose(archivo);
        fclose(archivof);
    }
}

int consulta_cedula(int cedula){
    char dato [20]; 
    FILE *archivo;
    if((archivo = fopen("trabajadores.in", "a+")) == NULL){
        printf("!Error al abrir el archivo!");
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
                    fscanf(archivo, "%ld", &trabajadores.salario);
                    printf("\n%s %s %d %s %s %s %ld\n", trabajadores.nombre, trabajadores.apellido, trabajadores.cedula, trabajadores.departamento, trabajadores.cargo, trabajadores.fecha, trabajadores.salario);
                    return 1;
                }
            }
        }
    fclose(archivo);
    printf("\n!La CI indicada no esta asociada a ningun trabajador de la empresa!\n");
    return 0;
}

int consulta_departamento(char departamento_f[]){
	int band_f=0, i, j; 
    long sueldo = 0;
    FILE *archivo, *arch;
    struct info trabajadores;
    archivo = fopen("trabajadores.in", "r");
    arch = fopen("departamento.txt", "a+");

    if(archivo == NULL){
        printf("!Error al abrir el archivo!");
    }else{
        j = comprobar_elementos(&archivo);
        fclose(archivo);
	}
    
    archivo = fopen("trabajadores.in", "r");
	if(archivo == NULL){
        printf("!Error al abrir el archivo!");
    }else{
        if(arch == NULL){
            printf("!Error al abrir el archivo!");
        }else{
            for(i = 0; i < j; i++){    
                fscanf(archivo, "%d", &trabajadores.cedula);
                fscanf(archivo, "%s", trabajadores.nombre);
                fscanf(archivo, "%s", trabajadores.apellido);
                fscanf(archivo, "%s", trabajadores.departamento);
                fscanf(archivo, "%s", trabajadores.cargo);
                fscanf(archivo, "%s", trabajadores.fecha);
                fscanf(archivo, "%ld", &trabajadores.salario);
                if ((strcmp(trabajadores.departamento,departamento_f)==0)){
                    printf("\n%d %s %s %s %s %s %ld\n",trabajadores.cedula,trabajadores.nombre, trabajadores.apellido, trabajadores.departamento, trabajadores.cargo, trabajadores.fecha, trabajadores.salario);
                    fprintf(arch,"%d %s %s %s %s %s %ld\n",trabajadores.cedula,trabajadores.nombre, trabajadores.apellido, trabajadores.departamento, trabajadores.cargo, trabajadores.fecha, trabajadores.salario);
                    band_f=1;
                    sueldo += trabajadores.salario;
                }
            }
        }         
    }
    if(band_f==1){
        fclose(archivo);
        fclose(arch);
        printf("\nTotal de sueldos devengados: $%ld \n", sueldo);
        return 1;
    }
    fclose(archivo);
    fclose(arch);
    printf("\n!el Departamento indicado no esta asociada a ningun trabajador de la empresa!\n");
    return 0;
}

int consulta_sueldo(){

    int i, k, indice_mayor = 0, indice_menor = 0; 
    long mayor, menor;
    FILE *archivo;
    
    if((archivo = fopen("trabajadores.in", "r")) == NULL){
        printf("!Error al abrir el archivo!");
    }else{
        k = comprobar_elementos(&archivo);
        fclose(archivo);
    }
    struct info trabajadores[k];
    if((archivo = fopen("trabajadores.in", "r")) == NULL){
        printf("!Error al abrir el archivo!");
    }else{
        for(i = 0; i < k; i++){    
            fscanf(archivo, "%d", &trabajadores[i].cedula);
            fscanf(archivo, "%s", trabajadores[i].nombre);
            fscanf(archivo, "%s", trabajadores[i].apellido);
            fscanf(archivo, "%s", trabajadores[i].departamento);
            fscanf(archivo, "%s", trabajadores[i].cargo);
            fscanf(archivo, "%s", trabajadores[i].fecha);
            fscanf(archivo, "%ld", &trabajadores[i].salario);
        }
        fclose(archivo);
    }
    mayor = trabajadores[0].salario;
    menor = trabajadores[0].salario;
    
    for(i = 0; i < k; i++){ 
        if (trabajadores[i].salario > mayor){
            mayor = trabajadores[i].salario;
            indice_mayor = i;
        }
        if (trabajadores[i].salario < menor){
            menor = trabajadores[i].salario;
            indice_menor = i;
        }
    }
    printf("\nEl trabajador con mayor sueldo es: %d %s %s %ld\n",trabajadores[indice_mayor].cedula, trabajadores[indice_mayor].nombre, trabajadores[indice_mayor].apellido, trabajadores[indice_mayor].salario);
    printf("\nEl trabajador con menor sueldo es: %d %s %s %ld\n",trabajadores[indice_menor].cedula, trabajadores[indice_menor].nombre, trabajadores[indice_menor].apellido, trabajadores[indice_menor].salario);   
    return 1;
}

int consulta_cargo(char cargo_f[]){
	int band_f=0, i, j; 
    long sueldo = 0;
    FILE *archivo, *arch;
    struct info trabajadores;
    archivo = fopen("trabajadores.in", "r");
    arch = fopen("cargo.txt", "a+");
    if(archivo == NULL){
        printf("!Error al abrir el archivo!");
    }else{
        j = comprobar_elementos(&archivo);
    fclose(archivo);
	}
    archivo = fopen("trabajadores.in", "r");
	if(archivo == NULL){
        printf("!Error al abrir el archivo!");
    }else{
        if(archivo == NULL){
            printf("!Error al abrir el archivo!");
        }else{
            for(i = 0; i < j; i++){    
                	fscanf(archivo, "%d", &trabajadores.cedula);
                    fscanf(archivo, "%s", trabajadores.nombre);
                    fscanf(archivo, "%s", trabajadores.apellido);
                    fscanf(archivo, "%s", trabajadores.departamento);
                    fscanf(archivo, "%s", trabajadores.cargo);
                    fscanf(archivo, "%s", trabajadores.fecha);
                    fscanf(archivo, "%ld", &trabajadores.salario);
					if ((strcmp(trabajadores.cargo, cargo_f) == 0)){
                        printf("\n%d %s %s %s %s %s %ld\n",trabajadores.cedula,trabajadores.nombre, trabajadores.apellido, trabajadores.departamento, trabajadores.cargo, trabajadores.fecha, trabajadores.salario);
                        fprintf(arch,"%d %s %s %s %s %s %ld\n",trabajadores.cedula,trabajadores.nombre, trabajadores.apellido, trabajadores.departamento, trabajadores.cargo, trabajadores.fecha, trabajadores.salario);
                        band_f=1;
                        sueldo += trabajadores.salario;
                }
            }
        }         
    }
    if(band_f==1){
        fclose(archivo);
        fclose(arch);
        printf("\nTotal de sueldos devengados: $%ld \n", sueldo);
        return 1;
    }
    fclose(archivo);
    fclose(arch);
    printf("\n!el Cargo indicado no esta  asociada a ningun trabajador de la empresa!\n");
    return 0;
}

int comprobar_elementos(FILE **archivo_f){
        int z = 0;
        char descarte[20];
        while(!feof(*archivo_f)){
            fscanf(*archivo_f,"%s %s %s %s %s %s %s\n", descarte,descarte,descarte,descarte,descarte,descarte,descarte);
            z += 1;
        }
    return z;
}

int validar_fecha(int anio, int mes, int dia){

    if ( anio < 1 ||  anio > 2023){
        printf("!No cumple con el formato de fecha correcto!\n");
        return 1;
    }else if ( anio == 2023){
        if (mes < 1 || mes > 5){
            printf("!No cumple con el formato de fecha correcto!\n");
            return 1;
        }else if (mes == 5){
            if (dia < 1 || dia > 22){
                printf("!No cumple con el formato de fecha correcto!\n");
                return 1;
            }
        }else{
            if (mes == 2){
                if (dia < 1 || dia > 29){
                    printf("!No cumple con el formato de fecha correcto!\n");
                    return 1;
                }
            }else if (mes % 2 == 0){
                if (dia < 1 || dia > 31){
                    printf("!No cumple con el formato de fecha correcto!\n");
                    return 1;
                }
            }else{
                if (dia < 1 || dia > 30){
                    printf("!No cumple con el formato de fecha correcto!\n");
                    return 1;
                }
            }
        }
    }else{
        if (mes < 1 || mes > 12){
            printf("!No cumple con el formato de fecha correcto!\n");
            return 1;
            
        }else if (mes == 2){
            if (dia < 1 || dia > 29){
                printf("!No cumple con el formato de fecha correcto!\n");
                return 1;
            }
        }else if (mes % 2 == 0){
            if (dia < 1 || dia > 31){
                printf("!No cumple con el formato de fecha correcto!\n");
                return 1;
            }
        }else{
            if (dia < 1 || dia > 30){
                printf("!No cumple con el formato de fecha correcto!\n");
                return 1;
            }
        }
    }
return 0;
}

int validar_numero(char num[]){
    int i, len;
    len = strlen(num);
    for (i = 0; i < len ; i++){
        if (!(isdigit(num[i]))){
            printf("!Solo se permiten numeros!\nIntente de nuevo: ");
            return 0;
        }
    }
return 1;
}
