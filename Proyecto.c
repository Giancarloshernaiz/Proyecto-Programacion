#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
struct info {
        int cedula;
        char nombre [12];
        char apellido [12];
        int departamento;
        int cargo;
        int salario;
        char fecha[10];
    };


char dept[6][20] = {"RRHH", "Consultoria", "Diseño", "Producción", "Calidad", "Distribución"};
char cargo[6][20] = {"Gerente", "Supervisor", "Analista", "Diseñador", "Desarrollador", "Auditor"};

void ingresar(int n){
    char op;
    FILE *arch;
    int i, len, band = 0;
    struct info trabajadores[n];
    if((arch = fopen("trabajadores.in", "a+")) == NULL){
        printf("¡Error al abrir el archivo!");
    }else{
        do {
            printf("Ingrese los datos del trabajador \n");
            printf("Cedula: ");
            scanf("%d", &trabajadores[band].cedula);
                for (i=0;i<band;i++){
                    if (trabajadores[band].cedula == trabajadores[i].cedula){
                        printf("¡Esa cédula ya existe!\n");
                        printf("Cedula: ");
                        scanf("%d", &trabajadores[band].cedula);
                        i = -1;
                    }
                }
            printf("Nombre: ");
            scanf("%s", trabajadores[band].nombre);
            printf("Apellido: ");
            scanf("%s", trabajadores[band].apellido);
            printf("Departamento: \n[1] RRHH \n[2] Consultoria \n[3] Diseño \n[4] Producción \n[5] Calidad \n[6] Distribución \n");
            scanf("%d", &trabajadores[band].departamento);
                if (trabajadores[band].departamento < 1 && trabajadores[band].departamento > 6){
                    do{
                        printf("¡El número no corresponde a ningún departamento!");
                    }while(trabajadores[band].departamento < 1 && trabajadores[band].departamento > 6);
                }
            printf("Cargo: \n[1] Gerente \n[2] Supervisor \n[3] Analista \n[4] Diseñador \n[5] Desarrollador \n[6] Auditor \n");
            scanf("%d", &trabajadores[band].cargo);
                if (trabajadores[band].cargo < 1 && trabajadores[band].cargo > 6){
                    do{
                        printf("¡El número no corresponde a ningún cargo!");
                    }while(trabajadores[band].cargo < 1 && trabajadores[band].cargo > 6);
                }
                
            printf("Salario: ");    
            scanf("%d", &trabajadores[band].salario);
            printf("Fecha(dd/MM/aaaa): ");
            scanf("%s", trabajadores[band].fecha);
            len = strlen(trabajadores[band].fecha);
                if (len != 10){
                    do{
                        printf("¡No cumpe con el formato de fecha correcto!\n");
                        printf("Fecha(dd/MM/aaaa): ");
                        scanf("%s", trabajadores[band].fecha);
                        len = strlen(trabajadores[band].fecha);
                    }while(len != 10);
                }
            printf("¡Se ha registrado satisfactoriamente!");
            fprintf(arch,"%s %s %d %s %s %d %s", trabajadores[band].nombre, trabajadores[band].apellido, trabajadores[band].cedula, dept[trabajadores[band].departamento], cargo[trabajadores[band].cargo], trabajadores[band].salario, trabajadores[band].fecha);
            
            printf("¿Desea ingresar otros %d trabajadores? (s/n)\n", n);
            scanf(" %c", &op);
            op = tolower(op);
            band += 1; 
        }while (op == 's');

    }
}
void consultar(int cedula, int n){
    int i;
    struct info trabajadores[n];
    for (i= 0; i < n ;i++){
        if (cedula == trabajadores[i].cedula){
            printf("%s %s %d %s %s %d %s", trabajadores[i].nombre, trabajadores[i].apellido, trabajadores[i].cedula, dept[trabajadores[i].departamento], cargo[trabajadores[i].cargo], trabajadores[i].salario, trabajadores[i].fecha);
                    
        }
    }
}



void menu(){
    int opcion, n, cedula, x = 0;
    printf(" ¡Bienvenido al registro de trabajadores de la empresa Future! \n\n");
    while (x == 0) {
        printf("Seleccione una opción\n");
        printf("[1] Ingresar \n[2] Consultar \n[3] Modificar \n[4] Eliminar \n[5] Salir\n");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1: 
                printf("¿Cuántos trabajadores desea ingresar?: ");
                scanf("%d", &n);
                ingresar(n);
                break;
            case 2:
                printf("Ingrese la cédula a consultar: ");
                scanf("%d", &cedula);
                consultar(cedula, n);
                break;
            case 3:
                //modificar();
                break;
            case 4:
                //eliminar();
                break;
            case 5:
                x = 1;
                break;
            default:
                printf("¡Esa opción no existe!");
            }
    }
}
int main(){
    setlocale(LC_ALL, "spanish"); 
    menu();

    return 0;
}
