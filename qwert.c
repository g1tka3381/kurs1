#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "ram.txt"

typedef struct {
    char manufacturer[20];
    char model[20];
    int capacity;
    int frequency;
    char type[10];
    float voltage;
    double price;
    short ecc;
} ram;

void clearInputBuffer() {
    while (getchar() != '\n');
}

void inputData(ram* arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nЗапись %d\n", i + 1);

        printf("Производитель: ");
        scanf("%19s", arr[i].manufacturer);

        printf("Модель: ");
        scanf("%19s", arr[i].model);

        printf("Объем (ГБ): ");
        scanf("%d", &arr[i].capacity);

        printf("Частота (МГц): ");
        scanf("%d", &arr[i].frequency);

        printf("Тип (DDR3/DDR4/DDR5): ");
        scanf("%9s", arr[i].type);

        printf("Напряжение (В): ");
        scanf("%f", &arr[i].voltage);

        printf("Цена: ");
        scanf("%lf", &arr[i].price);

        printf("ECC (0 - нет, 1 - да): ");
        scanf("%hd", &arr[i].ecc);
    }
}

void printData(ram* arr, int n) {
    printf("\n%-15s %-15s %-5s %-7s %-6s %-8s %-10s %-3s\n",
           "Производитель", "Модель", "ГБ", "МГц", "Тип", "Вольт", "Цена", "ECC");

    for (int i = 0; i < n; i++) {
        printf("%-15s %-15s %-5d %-7d %-6s %-8.2f %-10.2lf %-3d\n",
               arr[i].manufacturer,
               arr[i].model,
               arr[i].capacity,
               arr[i].frequency,
               arr[i].type,
               arr[i].voltage,
               arr[i].price,
               arr[i].ecc);
    }
}

void search(ram* arr, int n) {
    int cap;
    printf("Введите объем для поиска: ");
    scanf("%d", &cap);

    int found = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].capacity == cap) {
            printData(&arr[i], 1);
            found = 1;
        }
    }

    if (!found)
        printf("Записи не найдены.\n");
}

int compareByPrice(const void* a, const void* b) {
    ram* r1 = (ram*)a;
    ram* r2 = (ram*)b;
    if (r1->price > r2->price) return 1;
    if (r1->price < r2->price) return -1;
    return 0;
}

void editRecord(ram* arr, int n) {
    int index;
    printf("Введите номер записи для изменения (1-%d): ", n);
    scanf("%d", &index);

    if (index < 1 || index > n) {
        printf("Неверный номер!\n");
        return;
    }

    index--;

    printf("Новые данные:\n");
    printf("Производитель: ");
    scanf("%19s", arr[index].manufacturer);

    printf("Модель: ");
    scanf("%19s", arr[index].model);

    printf("Объем: ");
    scanf("%d", &arr[index].capacity);

    printf("Частота: ");
    scanf("%d", &arr[index].frequency);

    printf("Тип: ");
    scanf("%9s", arr[index].type);

    printf("Напряжение: ");
    scanf("%f", &arr[index].voltage);

    printf("Цена: ");
    scanf("%lf", &arr[index].price);

    printf("ECC: ");
    scanf("%hd", &arr[index].ecc);
}

void saveToFile(ram* arr, int n) {
    FILE* f = fopen(FILENAME, "w");
    if (!f) {
        printf("Ошибка открытия файла!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%s %s %d %d %s %f %lf %hd\n",
                arr[i].manufacturer,
                arr[i].model,
                arr[i].capacity,
                arr[i].frequency,
                arr[i].type,
                arr[i].voltage,
                arr[i].price,
                arr[i].ecc);
    }

    fclose(f);
    printf("Данные сохранены в файл.\n");
}

void loadFromFile(ram* arr, int n) {
    FILE* f = fopen(FILENAME, "r");
    if (!f) {
        printf("Файл не найден!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fscanf(f, "%19s %19s %d %d %9s %f %lf %hd",
               arr[i].manufacturer,
               arr[i].model,
               &arr[i].capacity,
               &arr[i].frequency,
               arr[i].type,
               &arr[i].voltage,
               &arr[i].price,
               &arr[i].ecc);
    }

    fclose(f);
    printf("Данные загружены из файла.\n");
}

int main() {
    int n;
    printf("Введите количество ячеек: ");
    scanf("%d", &n);
    ram* arr = (ram*)malloc(n * sizeof(ram));
    if (!arr) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    int choice;

    do {
        printf("\nМЕНЮ:\n");
        printf("1 - Загрузка данных\n");
        printf("2 - Поиск записи\n");
        printf("3 - Сортировка массива\n");
        printf("4 - Изменение записи\n");
        printf("5 - Сохранение массива в файл\n");
        printf("6 - Чтение массива из файла\n");
        printf("0 - Выход\n");
        printf("Выберите функцию: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            inputData(arr, n);
            printData(arr, n);
            break;
        case 2:
            search(arr, n);
            break;
        case 3:
            qsort(arr, n, sizeof(ram), compareByPrice);
            printf("Массив отсортирован по цене.\n");
            printData(arr, n);
            break;
        case 4:
            editRecord(arr, n);
            break;
        case 5:
            saveToFile(arr, n);
            break;
        case 6:
            loadFromFile(arr, n);
            printData(arr, n);
            break;
        case 0:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный пункт меню!\n");
        }

    } while (choice != 0);

    free(arr);
    return 0;
}