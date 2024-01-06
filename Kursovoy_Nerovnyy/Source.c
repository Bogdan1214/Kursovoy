#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// ����������� ���������
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

// ������� ��� ����� ������ �� ������������
void inputData(Facade* facade);

// ������� ��� ������� ������� ������ ��� �������
float calculateNetFacadeArea(Facade* facade);

// ������� ��� ������� ������������ ���������� ����������
void calculatePlasterRequired(Facade* facade);

// ������� ��� ������ �����������
void printResults(Facade* facade);

// ������� ��� ���������� ������ � ����
void saveToFile(Facade* facade);

// ������� ��� ���������� ������ �� �����
int readFromFile(Facade* facade);

int main() {
    setlocale(LC_ALL, "RUS");

    Facade facade;

    int choice;
    do {
        // ����� ����
        printf("����:\n");
        printf("1. ���� ������\n");
        printf("2. ������ �����������\n");
        printf("3. ��������� ������ � ����\n");
        printf("4. ������� ������ �� �����\n");
        printf("5. �����\n");
        printf("�������� ����� ����: ");
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
                printf("������ ������� ��������� � ����\n");
                break;
            case 4:
                if (readFromFile(&facade))
                    printf("������ ������� ������� �� �����\n");
                else
                    printf("������ ��� ���������� ������ �� �����\n");
                break;
            case 5:
                printf("����� �� ���������\n");
                break;
            default:
                printf("�������� ����� ����\n");
                break;
        }
        printf("\n");

    } while (choice != 5);

    return 0;
}

// ������� ��� ����� ������ �� ������������
void inputData(Facade* facade) {
    printf("������� ����� ������ (�): ");
    scanf("%f", &facade->length);

    printf("������� ������ ������ (�): ");
    scanf("%f", &facade->width);

    printf("������� ������ ������ (�): ");
    scanf("%f", &facade->height);

    printf("������� ������� ���� (�^2): ");
    scanf("%f", &facade->windowArea);

    printf("������� ������� ������ (�^2): ");
    scanf("%f", &facade->doorArea);

    printf("������� ������ ���������� �� ���� ���������� (��/�^2): ");
    scanf("%f", &facade->plasterRate);
}

// ������� ��� ������� ������� ������ ��� �������
float calculateNetFacadeArea(Facade* facade) {
    facade->facadeArea = 2 * (facade->length + facade->width) * facade->height;
    return facade->facadeArea - facade->windowArea - facade->doorArea;
}

// ������� ��� ������� ������������ ���������� ����������
void calculatePlasterRequired(Facade* facade) {
    float netFacadeArea = calculateNetFacadeArea(facade);

    // �����������, ��� ��� ������� ����� ���������� ��������� 25 ��
    facade->plasterBags = netFacadeArea * facade->plasterRate / 25;

    // �����������, ��� ������ ���� ���������� ������������ 1 ��
    facade->plasterLiters = netFacadeArea * facade->plasterRate;

    // ���������� ���������� � ����������� ����� ���������� ������ * 25
    facade->plasterKilograms = facade->plasterBags * 25;
}

// ������� ��� ������ �����������
void printResults(Facade* facade) {
    printf("����� ������� ������: %.2f �^2\n", facade->facadeArea);
    printf("������� ������ ��� �������: %.2f �^2\n", calculateNetFacadeArea(facade));
    printf("����������� ���������� ���������� � ������: %.2f ������\n", facade->plasterBags);
    printf("����������� ���������� ���������� � ������: %.2f �\n", facade->plasterLiters);
    printf("����������� ���������� ���������� � �����������: %.2f ��\n", facade->plasterKilograms);
}

// ������� ��� ���������� ������ � ����
void saveToFile(Facade* facade) {
    FILE* file = fopen("������.txt", "w");
    if (file == NULL) {
        printf("������ ��� �������� �����!");
        return;
    }

    fprintf(file, "����� ������: %.2f �\n", facade->length);
    fprintf(file, "������ ������: %.2f �\n", facade->width);
    fprintf(file, "������ ������: %.2f �\n", facade->height);
    fprintf(file, "������� ����: %.2f �^2\n", facade->windowArea);
    fprintf(file, "������� ������: %.2f �^2\n", facade->doorArea);
    fprintf(file, "������ ���������� �� ���� ����������: %.2f ��/�^2\n", facade->plasterRate);
    fprintf(file, "����� ������� ������: %.2f �^2\n", facade->facadeArea);
    fprintf(file, "����������� ���������� ���������� � ������: %.2f ������\n", facade->plasterBags);
    fprintf(file, "����������� ���������� ���������� � ������: %.2f �\n", facade->plasterLiters);
    fprintf(file, "����������� ���������� ���������� � �����������: %.2f ��\n", facade->plasterKilograms);

    fclose(file);
}

// ������� ��� ���������� ������ �� �����
int readFromFile(Facade* facade) {
    FILE* file = fopen("������.txt", "r");
    if (file == NULL) {
        printf("������ ��� �������� �����!");
        return 0;
    }

    if(fscanf(file, "����� ������: %f �\n", &facade->length) != 1) return 0;
    if(fscanf(file, "������ ������: %f �\n", &facade->width) != 1) return 0;
    if(fscanf(file, "������ ������: %f �\n", &facade->height) != 1) return 0;
    if(fscanf(file, "������� ����: %f �^2\n", &facade->windowArea) != 1) return 0;
    if(fscanf(file, "������� ������: %f �^2\n", &facade->doorArea) != 1) return 0;
    if(fscanf(file, "������ ���������� �� ���� ����������: %f ��/�^2\n", &facade->plasterRate) != 1) return 0;
    if(fscanf(file, "����� ������� ������: %f �^2\n", &facade->facadeArea) != 1) return 0;
    if(fscanf(file, "����������� ���������� ���������� � ������: %f ������\n", &facade->plasterBags) != 1) return 0;
    if(fscanf(file, "����������� ���������� ���������� � ������: %f �\n", &facade->plasterLiters) != 1) return 0;
    if(fscanf(file, "����������� ���������� ���������� � �����������: %f ��\n", &facade->plasterKilograms) != 1) return 0;

    fclose(file);
    return 1;
}