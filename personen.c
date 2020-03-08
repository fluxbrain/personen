// Bjoern Oke Maas - Aufgabe 21

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 40

typedef struct Person {
    char name[STR_MAX];
    char vorname[STR_MAX];
    struct Person *prev;
    struct Person *next;
} Person;

int menu(void);
void new_person(Person **head, Person **tail);
void delete_person(Person **head);
void print_persons(Person *head);

/*----------------------------------------------------------
 *  Legt DVK von Personen an. Personen lassen sich zufuegen,
 *  loeschen oder die komplette Liste ausgeben.
 *  Pro Person wird Vorname und Name gespeichert.
 */
int main(void) {
    int choice;

    Person *head = NULL;
    Person *tail = NULL;

    do {
        choice = menu();

        switch (choice) {
            case 1:
                new_person(&head, &tail);
                break;
            case 2:
                delete_person(&head);
                break;
            case 3:
                print_persons(head);
                break;
        }
    } while (choice != 4);

    while (head) {
        Person *del = head;
        head = head->next;
        free(del);
    }

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------
 *  Gibt Menu aus, liest und prueft Auswahl, gibt Auswahl
 *  an main zurueck.
 */
int menu(void) {
    int choice;

    do {
        puts("\nOptionen:\n"
                     "1) Neue Person anlegen\n"
                     "2) Person loeschen\n"
                     "3) Liste der Personen ausgeben\n"
                     "4) exit\n");
        scanf("%1u", &choice);
        while (getchar() != '\n') {}
        if (choice < 1 || choice > 4) {
            puts("Ungueltige Eingabe!");
        }
    } while (choice < 1 || choice > 4);

    return choice;
}

/*----------------------------------------------------------
 *  Neue Person wird angelegt. Vorname und Name abgefragt
 *  und eingetragen.
 *  Mehrfacheintraege von Namen werden akzeptiert.
 */
void new_person(Person **head, Person **tail) {
    Person *pers;
    if ((pers = malloc(sizeof *pers)) == 0) {
        perror("malloc error");
    }
    if (!*head) {
        *head = pers;
        pers->prev = NULL;
    } else {
        (*tail)->next = pers;
        pers->prev = *tail;
    }
    *tail = pers;
    pers->next = NULL;

    printf("Vorname: ");
    scanf("%40s", pers->vorname);
    while (getchar() != '\n') {}
    printf("Name: ");
    scanf("%40s", pers->name);
    while (getchar() != '\n') {}
}

/*----------------------------------------------------------
 *  Zu loeschende Person wird abgefragt, in der Liste gesucht
 *  und (alle Treffer) geloescht.
 */
void delete_person(Person **tracer) {
    char vorname[STR_MAX];
    char name[STR_MAX];
    Person *del;
    int flag = 0;

    if (!*tracer) {
        fprintf(stderr, "Liste ist leer!\n");
        return;
    }

    printf("Bitte geben Sie Vornamen und Namen der zu loeschenden Person ein:\nVorname: ");
    scanf("%40s", vorname);
    while (getchar() != '\n') {}
    printf("Name: ");
    scanf("%40s", name);
    while (getchar() != '\n') {}

    while (*tracer) {
        if (!strcmp((*tracer)->vorname, vorname) && !strcmp((*tracer)->name, name)) {
            del = *tracer;
            *tracer = (*tracer)->next;
            if (*tracer) { (*tracer)->prev = del->prev; }
            free(del);
            flag = 1;
        } else {
            tracer = &(*tracer)->next;
        }
    }
    if (flag == 1) { printf("\nPerson aus der Liste geloescht!\n"); }
    else { fprintf(stderr, "\nPerson nicht in der Liste gefunden!\n"); }
}

/*----------------------------------------------------------
 *  Ausgabe der kompletten Liste.
 */
void print_persons(Person *head) {
    Person *cur = head;
    if (!cur) {
        fprintf(stderr, "Liste ist leer!\n");
    } else {
        while (cur) {
            printf("%s %s\n", cur->vorname, cur->name);
            cur = cur->next;
        }
    }
}
