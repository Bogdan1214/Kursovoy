#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Определение структуры
typedef struct{
    float length;
    float width;
    float height;
    float windowArea;
    float doorArea;
    float facadeArea;
    float plasterRate;
    float plasterBags;
    float plasterLiters;
    float plasterKilograms;
} Facade;

// Функция для ввода данных от пользователя
void inputData(Facade* facade);

// Функция для расчета площади фасада без проемов
float calculateNetFacadeArea(Facade* facade);

// Функция для расчета необходимого количества штукатурки
void calculatePlasterRequired(Facade* facade);

// Функция для вывода результатов
void printResults(Facade* facade);

// Функция для сохранения данных в файл
void saveToFile(Facade* facade);

// Функция для считывания данных из файла
int readFromFile(Facade* facade);

int main() {
    setlocale(LC_ALL, "RUS");

    Facade facade;

    int choice;
    do {
        // Вывод меню
        printf("Меню:\n");
        printf("1. Ввод данных\n");
        printf("2. Расчет результатов\n");
        printf("3. Сохранить данные в файл\n");
        printf("4. Считать данные из файла\n");
        printf("5. Выход\n");
        printf("Выберите пункт меню: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputData(&facade);
                break;
            case 2:
                calculatePlasterRequired(&facade);
                printResults(&facade);
                break;
            case 3:
                saveToFile(&facade);
                printf("Данные успешно сохранены в файл\n");
                break;
            case 4:
                if (readFromFile(&facade))
                    printf("Данные успешно считаны из файла\n");
                else
                    printf("Ошибка при считывании данных из файла\n");
                break;
            case 5:
                printf("Выход из программы\n");
                break;
            default:
                printf("Неверный пункт меню\n");
                break;
        }
        printf("\n");

    } while (choice != 5);

    return 0;
}

// Функция для ввода данных от пользователя
void inputData(Facade* facade) {
    printf("Введите длину фасада (м): ");
    scanf("%f", &facade->length);

    printf("Введите ширину фасада (м): ");
    scanf("%f", &facade->width);

    printf("Введите высоту фасада (м): ");
    scanf("%f", &facade->height);

    printf("Введите площадь окон (м^2): ");
    scanf("%f", &facade->windowArea);

    printf("Введите площадь дверей (м^2): ");
    scanf("%f", &facade->doorArea);

    printf("Введите расход штукатурки на метр квадратный (кг/м^2): ");
    scanf("%f", &facade->plasterRate);
}

// Функция для расчета площади фасада без проемов
float calculateNetFacadeArea(Facade* facade) {
    facade->facadeArea = 2 * (facade->length + facade->width) * facade->height;
    return facade->facadeArea - facade->windowArea - facade->doorArea;
}

// Функция для расчета необходимого количества штукатурки
void calculatePlasterRequired(Facade* facade) {
    float netFacadeArea = calculateNetFacadeArea(facade);

    // Предположим, что для каждого мешка штукатурки требуется 25 кг
    facade->plasterBags = netFacadeArea * facade->plasterRate / 25;

    // Предположим, что каждый литр штукатурки эквивалентен 1 кг
    facade->plasterLiters = netFacadeArea * facade->plasterRate;

    // Количество штукатурки в килограммах равно количеству мешков * 25
    facade->plasterKilograms = facade->plasterBags * 25;
}

// Функция для вывода результатов
void printResults(Facade* facade) {
    printf("Общая площадь фасада: %.2f м^2\n", facade->facadeArea);
    printf("Площадь фасада без проемов: %.2f м^2\n", calculateNetFacadeArea(facade));
    printf("Необходимое количество штукатурки в мешках: %.2f мешков\n", facade->plasterBags);
    printf("Необходимое количество штукатурки в литрах: %.2f л\n", facade->plasterLiters);
    printf("Необходимое количество штукатурки в килограммах: %.2f кг\n", facade->plasterKilograms);
}

// Функция для сохранения данных в файл
void saveToFile(Facade* facade) {
    FILE* file = fopen("данные.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла!");
        return;
    }

    fprintf(file, "Длина фасада: %.2f м\n", facade->length);
    fprintf(file, "Ширина фасада: %.2f м\n", facade->width);
    fprintf(file, "Высота фасада: %.2f м\n", facade->height);
    fprintf(file, "Площадь окон: %.2f м^2\n", facade->windowArea);
    fprintf(file, "Площадь дверей: %.2f м^2\n", facade->doorArea);
    fprintf(file, "Расход штукатурки на метр квадратный: %.2f кг/м^2\n", facade->plasterRate);
    fprintf(file, "Общая площадь фасада: %.2f м^2\n", facade->facadeArea);
    fprintf(file, "Необходимое количество штукатурки в мешках: %.2f мешков\n", facade->plasterBags);
    fprintf(file, "Необходимое количество штукатурки в литрах: %.2f л\n", facade->plasterLiters);
    fprintf(file, "Необходимое количество штукатурки в килограммах: %.2f кг\n", facade->plasterKilograms);

    fclose(file);
}

// Функция для считывания данных из файла
int readFromFile(Facade* facade) {
    FILE* file = fopen("данные.txt", "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла!");
        return 0;
    }

    if(fscanf(file, "Длина фасада: %f м\n", &facade->length) != 1) return 0;
    if(fscanf(file, "Ширина фасада: %f м\n", &facade->width) != 1) return 0;
    if(fscanf(file, "Высота фасада: %f м\n", &facade->height) != 1) return 0;
    if(fscanf(file, "Площадь окон: %f м^2\n", &facade->windowArea) != 1) return 0;
    if(fscanf(file, "Площадь дверей: %f м^2\n", &facade->doorArea) != 1) return 0;
    if(fscanf(file, "Расход штукатурки на метр квадратный: %f кг/м^2\n", &facade->plasterRate) != 1) return 0;
    if(fscanf(file, "Общая площадь фасада: %f м^2\n", &facade->facadeArea) != 1) return 0;
    if(fscanf(file, "Необходимое количество штукатурки в мешках: %f мешков\n", &facade->plasterBags) != 1) return 0;
    if(fscanf(file, "Необходимое количество штукатурки в литрах: %f л\n", &facade->plasterLiters) != 1) return 0;
    if(fscanf(file, "Необходимое количество штукатурки в килограммах: %f кг\n", &facade->plasterKilograms) != 1) return 0;

    fclose(file);
    return 1;
}