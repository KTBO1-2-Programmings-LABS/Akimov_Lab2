#define  _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Определение структуры для односвязного списка
struct Student {
    char surname[50];
    int student_number;
    int score;
    struct Student* next;
};

//1. Функция для добавления студента в конец списка
void append(struct Student** head, const char* surname, int student_number, int score) {
    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
    strcpy(new_student->surname, surname);
    new_student->student_number = student_number;
    new_student->score = score;
    new_student->next = NULL;

    if (*head == NULL) {
        *head = new_student;
        return;
    }

    struct Student* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = new_student;
}

//2. функция для добавления студента на заданную позицию
void insert_at_position(struct Student** head, const char* surname, int student_number, int score, int position) {
    if (position < 0) {
        printf("Позиция должна быть неотрицательным числом.\n");
        return;
    }

    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
    strcpy(new_student->surname, surname);
    new_student->student_number = student_number;
    new_student->score = score;

    if (position == 0) {
        new_student->next = *head;
        *head = new_student;
        return;
    }

    struct Student* current = *head;
    for (int i = 0; i < position - 1; ++i) {
        if (current == NULL) {
            printf("Недопустимая позиция.\n");
            return;
        }
        current = current->next;
    }

    if (current == NULL) {
        printf("Недопустимая позиция.\n");
        return;
    }

    new_student->next = current->next;
    current->next = new_student;
}

//3. Функция для включения нового элемента после элемента с заданной информационной частью
void insert_after(struct Student* head, const char* surname, const char* newSurname, int newStudentNumber, int newScore) {
    struct Student* current = head;
    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
            strcpy(new_student->surname, newSurname);
            new_student->student_number = newStudentNumber;
            new_student->score = newScore;
            new_student->next = current->next;
            current->next = new_student;
            break;
        }
        current = current->next;
    }
}

//4. Функция для добавления студента перед элементом с заданной информационной частью
void insert_before(struct Student* head, char* target_surname, char* surname, int student_number, int score) {
    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
    strcpy(new_student->surname, surname);
    new_student->student_number = student_number;
    new_student->score = score;

    if (strcmp((head)->surname, target_surname) == 0) {
        new_student->next = head;
        head = new_student;
        return;
    }

    struct Student* current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->surname, target_surname) == 0) {
            new_student->next = current->next;
            current->next = new_student;
            return;
        }
        current = current->next;
    }

    printf("Студент с фамилией %s не найден в списке.\n", target_surname);
}


//5. Функция для добавления студента в середину списка
void insert_in_middle(struct Student* head, char* surname, int student_number, int score) {
    struct Student* new_student = (struct Student*)malloc(sizeof(struct Student));
    strcpy(new_student->surname, surname);
    new_student->student_number = student_number;
    new_student->score = score;

    int count = 0;
    struct Student* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    int middle_position = count / 2;
    current = head;
    for (int i = 0; i + 1 < middle_position; ++i) {
        current = current->next;
    }

    new_student->next = current->next;
    current->next = new_student;
}

//6. Исключить элемент из середины списка.
void delete_from_middle(struct Student* head)
{
    int count = 0;
    struct Student* current = head;
    struct Student* prev = NULL;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    int middle_position = count / 2;
    current = head;
    for (int i = 0; i < middle_position; ++i) {
        prev = current;
        current = current->next;
    }
    

    prev->next = current->next;
    return;
}

//7. Функция для удаления студента с заданной информационной частью
void delete_by_surname(struct Student** head, char* surname) {
    if (*head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    struct Student* current = *head;
    struct Student* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->surname, surname) == 0) {
            if (prev == NULL) {
                *head = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            printf("Студент с фамилией %s удален из списка.\n", surname);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Студент с фамилией %s не найден в списке.\n", surname);
}

//8. Функция для исключения элемента из конца списка
void delete_from_tail(struct Student* head) {
    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }
    if (head->next == NULL) {
        free(head);
        return;
    }
    struct Student* current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return;
}

//9. функция для удаления студента на заданной позиции
void delete_by_position(struct Student** head, int position) {
    if (*head == NULL) {
        printf("Список пуст.\n");
        return;
    }

    if (position == 0) {
        printf("Недопустимая позиция.\n");
        return;
    }

    struct Student* current = *head;
    struct Student* prev = NULL;
    int count = 0;

    while (current != NULL) {
        if (count == position) {
            prev->next = current->next;
            free(current);
            return;
        }
        prev = current;
        current = current->next;
        count++;
    }

    printf("Недопустимая позиция.\n");
}

// Функция для отображения списка студентов (10)
void display_10(struct Student* newHead) {
    setlocale(LC_ALL, "rus");
    struct Student* current = newHead;
    while (current != NULL) {
        printf("Фамилия: %s, Номер: %d, Балл: %d\n", current->surname, current->student_number, current->score);
        current = current->next;
    }
}

//10 . Функция для исключения элемента из головы списка
void delete_from_head(struct Student* head) {
    setlocale(LC_ALL, "rus");
    if (head == NULL) {
        printf("Список пуст.\n");
        return;
    }
    struct Student* newHead = head->next;
    free(head);
    display_10(newHead);
    free(newHead);
    return;
}

// Функция для отображения списка студентов
void display(struct Student* head) {
    setlocale(LC_ALL, "rus");
    struct Student* current = head;
    while (current != NULL) {
        printf("Фамилия: %s, Номер: %d, Балл: %d\n", current->surname, current->student_number, current->score);
        current = current->next;
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    struct Student* head = NULL;
    int number, score, position;
    char surname[30], target_surname[30];

    append(&head, "Петров", 101, 78);
    append(&head, "Сидоров", 102, 92);
    append(&head, "Кузнецов", 103, 41);
    append(&head, "Иванов", 104, 60);
    append(&head, "Михалков", 105, 84);
    append(&head, "Смирнов", 106, 61);
    append(&head, "Попов", 107, 26);
    append(&head, "Лебедев", 108, 33);
    append(&head, "Волков", 109, 72);
    append(&head, "Павлов", 110, 94);

    //Выбор функции
    int vibor;
    printf("Выберите функцию:\n1. Включить новый элемент в конец списка.\n2. Включить новый элемент на заданное пользователемместо списка.\n3. Включить новый элемент после элемента с заданной информационной частью.\n4. Включить новый элемент перед элементом с заданной информационной частью.\n5. Включить новый элемент в середину списка.\n6. Исключить элемент из середины списка.\n7. Исключить элемент с заданной информационнойчастью.\n8. Исключить элемент из конца списка.\n9. Исключить элемент из заданного пользователем местасписка.\n10. Исключить элемент из головы списка.\n");
    scanf("%d", &vibor);

    switch (vibor) 
    {
        // Пример добавления в конец списка
        case(1):
            printf("Введите фамилию\n");
            scanf("%s", &surname);
            printf("Введите номер\n");
            scanf("%d", &number);
            printf("Введите балл\n");
            scanf("%d", &score);
            append(&head, surname, number, score);
            printf("Список после добавления студента:\n");
            display(head);
            while (head != NULL) {
                struct Student* temp = head;
                head = head->next;
                free(temp);
            }
            break;

        // Пример добавления на заданное место списка
        case(2):
            printf("Введите фамилию\n");
            scanf("%s", &surname);
            printf("Введите номер\n");
            scanf("%d", &number);
            printf("Введите балл\n");
            scanf("%d", &score);
            printf("Введите позицию\n");
            scanf("%d", &position);
            insert_at_position(&head, surname, number, score, position);
            printf("Список после добавления студента:\n");
            display(head);
            while (head != NULL) {
                struct Student* temp = head;
                head = head->next;
                free(temp);
            }
            break;

        // Включение нового элемента после элемента с заданной информационной частью
        case(3):
            printf("Введите фамилию, после которой вставить новую\n");
            scanf("%s", &target_surname);
            printf("Введите фамилию\n");
            scanf("%s", &surname);
            printf("Введите номер\n");
            scanf("%d", &number);
            printf("Введите балл\n");
            scanf("%d", &score);
            insert_after(head, target_surname, surname, number, score);
            printf("Список после включение нового элемента:\n");
            display(head);
            while (head != NULL) {
                struct Student* temp = head;
                head = head->next;
                free(temp);
            }
            break;

        // Включение нового элемента перед элемента с заданной информационной частью
        case(4):
            printf("Введите фамилию, перед которой вставить новую\n");
            scanf("%s", &target_surname);
            printf("Введите фамилию\n");
            scanf("%s", &surname);
            printf("Введите номер\n");
            scanf("%d", &number);
            printf("Введите балл\n");
            scanf("%d", &score);
            insert_before(head, target_surname, surname, number, score);
            printf("Список после добавления студента:\n");
            display(head);
            while (head != NULL) {
                struct Student* temp = head;
                head = head->next;
                free(temp);
            }
            break;

        // Включить новый элемент в середину списка.
        case(5):
            printf("Введите фамилию\n");
            scanf("%s", &surname);
            printf("Введите номер\n");
            scanf("%d", &number);
            printf("Введите балл\n");
            scanf("%d", &score);
            insert_in_middle(head, surname, number, score);
            printf("Список после добавления студента в середину:\n");
            display(head);
            while (head != NULL) {
                struct Student* temp = head;
                head = head->next;
                free(temp);
            }
            break;

        // Исключить элемент из середины списка.
        case(6):
            delete_from_middle(head);
            printf("Список после удаления студента из середины:\n");
            display(head);
            while (head != NULL) {
                struct Student* temp = head;
                head = head->next;
                free(temp);
            }
            break;

        // Исключить элемент с заданной информационной частью.
        case(7):
            printf("Введите фамилию\n");
            scanf("%s", &target_surname);
            delete_by_surname(&head, target_surname);
            printf("\nПосле исключения заданного студента:\n");
            display(head);
            while (head != NULL) {
                struct Student* temp = head;
                head = head->next;
                free(temp);
            }
            break;
        
        // Исключение элемента из конца списка
        case(8):
            delete_from_tail(head);
            printf("\nПосле исключения элемента из конца списка:\n");
            display(head);
            while (head != NULL) {
                struct Student* temp = head;
                head = head->next;
                free(temp);
            }
            break;

        // Исключить элемент из заданного пользователем места списка.
        case(9):
            printf("Введите позицию\n");
            scanf("%d", &position);
            delete_by_position(&head, position);
            printf("Список после удаления студента на %d позиции:\n", position);
            display(head);
            while (head != NULL) {
                struct Student* temp = head;
                head = head->next;
                free(temp);
            }
            break;

        // Исключить элемент из головы списка.
        case(10):
            printf("Список после удаления студента из головы списка:\n");
            delete_from_head(head);
            break;
    }
}
