#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_10 10
#define MAX_30 30

int ID_g;
char cedula_g[MAX_10];
char apellidos_g[MAX_30];
char nombres_g[MAX_30];
char telefono_g[MAX_10];
double sueldo_g;
char estado_g;
char tipo_pariente_g;
int edad_g;

struct empleado {
    int ID;
    char cedula[MAX_10];
    char apellidos[MAX_30];
    char nombres[MAX_30];
    char telefono[MAX_10];
    double sueldo;
    char estado;
    struct empleado *sig;
};

struct empleado_carga_familiar {
    char cedula_empleado[MAX_10];
    char apellidos[MAX_30];
    char nombres[MAX_30];
    char tipo_pariente;
    int edad;
    struct empleado_carga_familiar *sig;
};

int vacia_empleado(struct empleado **cab1);
int vacia_carga_familiar(struct empleado_carga_familiar **cab2);
void ingreso_empleado(struct empleado **cab1, struct empleado **ult1);
int compara(struct empleado **cab1);
void ingreso_carga_familiar(struct empleado_carga_familiar **cab2, struct empleado_carga_familiar **ult2, struct empleado **cab1);
void mostrar_todos_empleados(struct empleado **cab1);
void mostrar_carga_familiar(struct empleado_carga_familiar **cab2);
void inactivar(struct empleado **cab1);

int main() {
    struct empleado *cab1 = NULL, *ult1 = NULL;
    struct empleado_carga_familiar *cab2 = NULL, *ult2 = NULL;
    int opc, opcion, cont = 0;

    do {
        system("cls");
        printf("1.- INGRESO EMPLEADOS\n");
        printf("2.- INGRESO CARGAS FAMILIARES\n");
        printf("3.- ELIMINAR (INACTIVAR) UN EMPLEADO\n");
        printf("4.- CONSULTA\n");
        printf("5.- SALIR\n");
        printf("Digite opcion: ");
        scanf("%d", &opc);
        getchar(); // limpia el buffer de entrada

        switch(opc) {
            case 1:
                system("cls");
                printf("-------------- INGRESO DE INFORMACION DE LOS EMPLEADOS --------------\n");
                ID_g = ++cont;
                printf("EMPLEADO CON ID NUMERO %d\n", ID_g);
                printf("Ingrese la cedula: ");
                fgets(cedula_g, MAX_10, stdin);
                cedula_g[strcspn(cedula_g, "\n")] = 0;
                printf("Apellidos: ");
                fgets(apellidos_g, MAX_30, stdin);
                apellidos_g[strcspn(apellidos_g, "\n")] = 0;
                printf("Nombres: ");
                fgets(nombres_g, MAX_30, stdin);
                nombres_g[strcspn(nombres_g, "\n")] = 0;
                printf("Numero de telefono: ");
                fgets(telefono_g, MAX_10, stdin);
                telefono_g[strcspn(telefono_g, "\n")] = 0;
                printf("Sueldo percibido (en dolares): ");
                char c[MAX_10];
                fgets(c, MAX_10, stdin);
                c[strcspn(c, "\n")] = 0;
                sueldo_g = c[0] == '\0' ? 0 : atof(c);
                estado_g = 'A';
                ingreso_empleado(&cab1, &ult1);
                printf("\nPresione una tecla para continuar...");
                getch();
                break;

            case 2:
                system("cls");
                printf("----------- Registro de cargas familiares -----------\n");
                printf("Ingrese la cedula del empleado: ");
                fgets(cedula_g, MAX_10, stdin);
                cedula_g[strcspn(cedula_g, "\n")] = 0;
                printf("Ingrese apellidos: ");
                fgets(apellidos_g, MAX_30, stdin);
                apellidos_g[strcspn(apellidos_g, "\n")] = 0;
                printf("Ingrese nombres: ");
                fgets(nombres_g, MAX_30, stdin);
                nombres_g[strcspn(nombres_g, "\n")] = 0;
                printf("Ingrese el parentesco:  E (esposa), H (hijo), P (padre): ");
                scanf("%c", &tipo_pariente_g);
                getchar();
                tipo_pariente_g = toupper(tipo_pariente_g);
                printf("Ingrese edad: ");
                scanf("%d", &edad_g);
                getchar();
                ingreso_carga_familiar(&cab2, &ult2, &cab1);
                printf("\nPresione una tecla para continuar...");
                getch();
                break;

            case 3:
                system("cls");
                printf("------- ELIMINAR A UN EMPLEADO -------\n");
                printf("Ingrese la cedula: ");
                fgets(cedula_g, MAX_10, stdin);
                cedula_g[strcspn(cedula_g, "\n")] = 0;
                if (compara(&cab1)) {
                    inactivar(&cab1);
                } else {
                    printf("No se encontró coincidencia con la cedula!\n");
                }
                printf("\nPresione una tecla para continuar...");
                getch();
                break;

            case 4:
                do {
                    system("cls");
                    printf("1.- TODOS LOS EMPLEADOS\n");
                    printf("2.- CARGAS FAMILIARES POR EMPLEADOS\n");
                    printf("3.- REGRESAR AL MENU PRINCIPAL\n");
                    printf("Digite opcion: ");
                    scanf("%d", &opcion);
                    getchar();

                    switch(opcion) {
                        case 1:
                            system("cls");
                            printf("----------- TODOS LOS EMPLEADOS -----------\n");
                            mostrar_todos_empleados(&cab1);
                            printf("\nPresione una tecla para continuar...");
                            getch();
                            break;

                        case 2:
                            system("cls");
                            printf("----------- CONSULTA DE CARGAS FAMILIARES -----------\n");
                            printf("Ingrese la cedula del empleado: ");
                            fgets(cedula_g, MAX_10, stdin);
                            cedula_g[strcspn(cedula_g, "\n")] = 0;
                            if (compara(&cab1)) {
                                printf("\tSUS CARGAS FAMILIARES SON\n");
                                mostrar_carga_familiar(&cab2);
                            } else {
                                printf("No se encontro coincidencia con la cedula empleado!\n");
                            }
                            printf("\nPresione una tecla para continuar...");
                            getch();
                            break;
                    }
                } while (opcion != 3);
                break;
        }
    } while (opc != 5);

    return 0;
}

int vacia_empleado(struct empleado **cab1) {
    return *cab1 == NULL ? 1 : 0;
}

int vacia_carga_familiar(struct empleado_carga_familiar **cab2) {
    return *cab2 == NULL ? 1 : 0;
}

void ingreso_empleado(struct empleado **cab1, struct empleado **ult1) {
    struct empleado *p, *aux = NULL;
    p = (struct empleado *)malloc(sizeof(struct empleado));
    p->ID = ID_g;
    strcpy(p->cedula, cedula_g);
    strcpy(p->apellidos, apellidos_g);
    strcpy(p->nombres, nombres_g);
    strcpy(p->telefono, telefono_g);
    p->sueldo = sueldo_g;
    p->estado = estado_g;
    p->sig = NULL;

    if (vacia_empleado(cab1)) {
        *cab1 = p;
    } else {
        aux = *ult1;
        aux->sig = p;
    }
    *ult1 = p;
    printf("\tINFORMACION INSERTADA CORRECTAMENTE\n");
}

int compara(struct empleado **cab1) {
    struct empleado *aux = NULL;
    if (!vacia_empleado(cab1)) {
        aux = *cab1;
        while (aux != NULL) {
            if (strcmp(aux->cedula, cedula_g) == 0) {
                return 1;
            }
            aux = aux->sig;
        }
    }
    return 0;
}

void ingreso_carga_familiar(struct empleado_carga_familiar **cab2, struct empleado_carga_familiar **ult2, struct empleado **cab1) {
    struct empleado_carga_familiar *q, *aux = NULL;
    if (compara(cab1)) {
        q = (struct empleado_carga_familiar *)malloc(sizeof(struct empleado_carga_familiar));
        strcpy(q->cedula_empleado, cedula_g);
        strcpy(q->apellidos, apellidos_g);
        strcpy(q->nombres, nombres_g);
        q->tipo_pariente = tipo_pariente_g;
        q->edad = edad_g;
        q->sig = NULL;

        if (vacia_carga_familiar(cab2)) {
            *cab2 = q;
        } else {
            aux = *ult2;
            aux->sig = q;
        }
        *ult2 = q;
        printf("\tINFORMACION INGRESADA CON EXITO!\n");
    } else {
        printf("\tInformacion no ingresada. No se encontro coincidencia con la cedula empleado\n");
    }
}

void mostrar_todos_empleados(struct empleado **cab1) {
    struct empleado *p = NULL;
    if (vacia_empleado(cab1)) {
        printf("\tNO HAY INFORMACION EN LA COLA\n");
    } else {
        p = *cab1;
        while (p != NULL) {
            if (p->estado == 'A') {
                printf("\nEMPLEADO CON ID %d\n", p->ID);
                printf("C.I.: %s\n", p->cedula);
                printf("Apellidos: %s\n", p->apellidos);
                printf("Nombres: %s\n", p->nombres);
                printf("Tel.: %s\n", p->telefono);
                printf("Salario (en dolares): %.2f\n", p->sueldo);
            }
            p = p->sig;
        }
    }
}

void mostrar_carga_familiar(struct empleado_carga_familiar **cab2) {
    struct empleado_carga_familiar *aux = NULL;
    if (vacia_carga_familiar(cab2)) {
        printf("\tNO HAY INFORMACION EN LA COLA\n");
    } else {
        aux = *cab2;
        while (aux != NULL) {
            if (strcmp(aux->cedula_empleado, cedula_g) == 0) {
                printf("Apellidos: %s\n", aux->apellidos);
                printf("Nombres: %s\n", aux->nombres);
                printf("Parentesco: ");
                switch (aux->tipo_pariente) {
                    case 'E':
                        printf("Esposa\n");
                        break;
                    case 'H':
                        printf("Hijo\n");
                        break;
                    case 'P':
                        printf("Padre\n");
                        break;
                }
                printf("Edad: %d\n", aux->edad);
            }
            aux = aux->sig;
        }
    }
}

void inactivar(struct empleado **cab1) {
    struct empleado *aux;
    aux = *cab1;
    while (aux != NULL) {
        if (strcmp(aux->cedula, cedula_g) == 0) {
            aux->estado = 'I';
        }
        aux = aux->sig;
    }
    printf("EMPLEADO INACTIVADO CON EXITO\n");
}
