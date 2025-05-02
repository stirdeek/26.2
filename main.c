#include <stdio.h>
#include <stdlib.h>
#include "desc.h"
#include <locale.h>

int main() {
    setlocale(LC_CTYPE, "Russian");
    printf("Программа для работы с циклическими двусвязными списками\n");
    CyclicList list1, list2;
    init_list(&list1);
    init_list(&list2);

    int choice, value, list_num;
    CyclicList copy;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Перейти к следующему элементу\n");
        printf("2. Перейти к предыдущему элементу\n");
        printf("3. Вставить элемент после текущего\n");
        printf("4. Вставить элемент перед текущим\n");
        printf("5. Удалить текущий элемент\n");
        printf("6. Создать копию списка\n");
        printf("7. Вывести все элементы списка\n");
        printf("8. Обменять списки местами (list1 ↔ list2)\n");
        printf("9. Выход\n");

        printf("Выберите пункт меню: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 6) {
            printf("Выберите список (1 или 2): ");
            scanf("%d", &list_num);
            if (list_num != 1 && list_num != 2) {
                printf("Ошибка: неверный номер списка\n");
                continue;
            }
        }

        CyclicList* current_list = (list_num == 1) ? &list1 : &list2;

        switch (choice) {
            case 1:
                if (is_empty(current_list)) {
                    printf("Список %d пуст\n", list_num);
                } else {
                    move_next(current_list);
                    printf("В списке %d перешли к следующему элементу. Текущий: %d\n",
                           list_num, current_list->current->value);
                }
                break;

            case 2:
                if (is_empty(current_list)) {
                    printf("Список %d пуст\n", list_num);
                } else {
                    move_prev(current_list);
                    printf("В списке %d перешли к предыдущему элементу. Текущий: %d\n",
                           list_num, current_list->current->value);
                }
                break;

            case 3:
                printf("Введите значение для вставки: ");
                scanf("%d", &value);
                insert_after(current_list, value);
                printf("Элемент %d вставлен после текущего в списке %d\n", value, list_num);
                break;

            case 4:
                printf("Введите значение для вставки: ");
                scanf("%d", &value);
                insert_before(current_list, value);
                printf("Элемент %d вставлен перед текущим в списке %d\n", value, list_num);
                break;

            case 5:
                value = remove_current(current_list);
                if (value == -1) {
                    printf("Список %d пуст, удалять нечего\n", list_num);
                } else {
                    printf("Из списка %d удален элемент: %d\n", list_num, value);
                }
                break;

            case 6:
                if (list_num == 1) {
                    printf("1. Создать временную копию\n");
                    printf("2. Скопировать в список 2\n");
                    printf("Выберите действие: ");
                int copy_action;
                scanf("%d", &copy_action);

                if (copy_action == 1) {
                    copy_list(&list1, &copy);
                    printf("Создана временная копия списка 1:\n");
                    display_list(&copy);
                    free_list(&copy);
               } else if (copy_action == 2) {
                    free_list(&list2); // Очищаем список 2 перед копированием
                    copy_list(&list1, &list2);
                    printf("Список 1 скопирован в список 2:\n");
                    display_list(&list2);
               }
               } else {
                   copy_list(&list2, &copy);
                   printf("Создана временная копия списка 2:\n");
                   display_list(&copy);
                   free_list(&copy);
               }
                 break;

            case 7:
                printf("Список 1:\n");
                display_list(&list1);
                printf("Список 2:\n");
                display_list(&list2);
                break;
           case 8: {
                CyclicList temp;
                init_list(&temp);

                copy_list(&list1, &temp);

                free_list(&list1);
                copy_list(&list2, &list1);

                free_list(&list2);
                copy_list(&temp, &list2);

                free_list(&temp);
                printf("Списки обменяны местами!\n");
                break;
                }

            case 9:
                free_list(&list1);
                free_list(&list2);
                printf("Программа завершена\n");
                return 0;

            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    }
    return 0;
}
