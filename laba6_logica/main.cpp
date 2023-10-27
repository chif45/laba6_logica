#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <random>
#include <locale.h>

int** generate_matrix(int len) {
    int** m = (int**)malloc(len * sizeof(int*));
    for (int i = 0; i < len; i++) {
        m[i] = (int*)malloc(len * sizeof(int));
    }

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++)
        {
            int s = rand() % 2;
            m[i][j] = s; // заполняем массив случайными числами
            m[j][i] = s; // заполняем массив случайными числами
        }
        
    }
    return m;
}
int** print_matrix(int** m,int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++)
        {
            printf("%d", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}


int** k(int** m1, int len, int id) {
    int** m = generate_matrix(len-1);
    int k = 0, f = 0;
    for (int i = 0; i < len-1; i++){
        for (int j = 0; j < len-1; j++){
            k = i == id ? 1 : k;
            f = j == id ? 1 : f;
            m[i][j] = m1[i+k][j+f];
        }
    }
    
    return m;
}

int** otv(int** m, int len, int id1, int id2) {

    for (int i = 0; i < len; i++) {
        if (m[id1][i] == 1) {
            m[id2][i] = 1;
            m[i][id2] = 1;
        }
    }
    for (int i = 0; i < len; i++) {
        m[id1][i] = 0;
        m[i][id1] = 0;
    }

    m[id1][id1] = 1;

    return m;
}

void styg(int** m, int len, int id1, int id2) {
    for (int i = 0; i < len; i++) {
        if (m[id1][i] == 1) {
            m[id2][i] = 1;
            m[i][id2] = 1;
        }
    }

    for (int i = 0; i < len; i++){
        m[id1][i] = 0;
        m[i][id1] = 0;
    }
}

int** ras(int** m, int len, int id1) {
    len++;
    int** nm = (int**)malloc(len * sizeof(int*));
    for (int i = 0; i < len; i++) {
        nm[i] = (int*)malloc(len * sizeof(int));
    }

    for (int i = 0; i < len-1; i++){
        for (int j = 0; j < len-1; j++){
            nm[i][j] = m[i][j];
        }
    }
    for (int i = 0; i < len; i++){
        nm[i][len - 1] = 0;
        nm[len - 1][i] = 0;
    }

    for (int i = 0; i < len; i++){
        nm[len - 1][i] = nm[id1][i];
        nm[i][len - 1] = nm[i][id1];
    }

    return nm;
}

int** merge(int** m1, int** m2, int len) {
    for (int i = 0; i < len; i++){
        for (int j = 0; j < len; j++){
            m1[i][j] += m1[i][j] == 0 ? m2[i][j] : 0;
        }
    }
    return m1;
}

int** per(int** m1, int** m2, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (m1[i][j] == 1) {
                m1[i][j] = m2[i][j] == 1 ? 1 : 0;
            }
        }
    }

    return m1;
}

int** xor1(int** m1, int** m2, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (m1[i][j] == 1) {
                m1[i][j] = m2[i][j] == 0 ? 1 : 0;
            }
            else {
                m1[i][j] = m2[i][j] == 1 ? 1 : 0;
            }
        }
    }

    return m1;
}

void menu(int** m1, int** m2, int len) {
    int ch;
    int id1, id2;
    printf("Размер матрицы %dx%d\n", len, len);
    print_matrix(m1, len);
    print_matrix(m2, len);
    printf("Выберите функцию:\n 0 - Изменить размер матриц\n 1 - Перегенерировать матрицы\n 2 - Отождествление\n 3 - Стягивание\n 4 - Расщепление\n 5 - Слияние\n 6 - Пересечение\n 7 - Кольцевая сумма\n");
    scanf("%d", &ch);

    switch (ch) {
    case 0:
        printf("Введите размер матрицы: ");
        scanf("%d", &len);
    case 1:
        m1 = generate_matrix(len);
        m2 = generate_matrix(len);
        break;
    case 2:
        printf("Введите ID вершин: ");
        scanf("%d %d", &id1, &id2);
        otv(m1,len,id1, id2);
        m1 = k(m1, len, id1);
        len--;
        break;
    case 3:
        printf("Введите ID вершин: ");
        scanf("%d %d", &id1, &id2);
        if (m1[id1][id2] == 0) {
            break;
        }
        styg(m1, len, id1, id2);
        m1 = k(m1, len, id1);
        len--;
        break;
    case 4:
        printf("Введите ID вершины: ");
        scanf("%d", &id1);
        ras(m1, len, id1);
        break;
    case 5:
        merge(m1, m2, len);
        break;
    case 6:
        per(m1, m2, len);
        break;
    case 7:
        xor1(m1,m2,len);
        break;
    default:
        break;
    }
    menu(m1, m2, len);
}

int main() {
	setlocale(LC_ALL, "rus");
	int len = 5;
    int** m1 = generate_matrix(len);
    int** m2 = generate_matrix(len);

    menu(m1,m2,len);

	return 0;
}