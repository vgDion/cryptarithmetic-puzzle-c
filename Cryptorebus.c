#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#pragma warning (disable: 4996)



// структура для хранения буквы и соответствующего ей целого числа
typedef struct node
{
    char c;
    int v;
} Node;

int sum_array(int a[], int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum = sum + a[i];
    }

    return sum;
}

bool is_letter(char c) {
    if (c >= 65 && c <= 97) return true;
    return false;
}

int use[10] = { 0 };

// проверка для правильного решения
int check(Node* nodeArr, const int count, char adds[][100], int addsCount, int* addsl)
{
    int values[8] = { 0 };
    int m = 1;
    int i, j;

    for (int k = 0; k < addsCount; k++) {
        for (i = addsl[k] - 1; i >= 0; i--)
        {
            char ch = adds[k][i];
            for (j = 0; j < count; j++)
                if (nodeArr[j].c == ch)
                    break;

            values[k] += m * nodeArr[j].v;
            m *= 10;
        }
        m = 1;
    }

    if (values[addsCount - 1] == sum_array(values, addsCount - 1))
        return 1;

    return 0;
}

// Рекурсивная функция для проверки решения для всех перестановок
bool permutation(Node* nodeArr, const int count, char adds[][100], int addsCount, int n, int* addsl)
{

    if (n == count - 1)
    {

        // проверка все не использованных цифр 
        for (int i = 0; i < 10; i++)
        {

            // если не используется 
            if (use[i] == 0)
            {

                // присвоить букве по индексу n целое число i 
                nodeArr[n].v = i;

                // если решение найдено 
                if (check(nodeArr, count, adds, addsCount, addsl) == 1)
                {
                    printf("\nSolution found: ");
                    for (int i = 0; i < addsCount; i++) {
                        for (int j = 0; j < 100; j++) {
                            for (int k = 0; k < count; k++) {
                                if (adds[i][j] == nodeArr[k].c) printf("%d", nodeArr[k].v);
                            }
                        }
                        if (i == addsCount - 1) break;
                        if (i != addsCount - 2) printf(" + ");
                        else printf(" = ");
                    }
                    return true;
                }
            }
        }
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        bool nextStep = false;
        if (i == 0) {

            for (int j = 0; j < addsCount; j++) {
                if (adds[j][0] == nodeArr[n].c) {
                    nextStep = true;
                }
            }
        }

        if (nextStep) continue;

        // если i-е целое число еще не используется
        if (use[i] == 0)
        {

            // присвоить букве по индексу n целое число i
            nodeArr[n].v = i;

            // запрет на использование
            use[i] = 1;

            // вызвать рекурсивную функцию
            if (permutation(nodeArr, count, adds, addsCount, n + 1, addsl))
                return true;

            // проверка других решений
            use[i] = 0;
        }
    }
    return false;
}

bool solveCryptographic(char adds[][100], int addsCount, int* addsl)
{
    // счетчик для хранения числа уникальных символов 
    int count = 0;
    int lengths[8] = { 0 };

    for (int i = 0; i < addsCount; i++) {
        lengths[i] = addsl[i];
    }

    // массив для хранения частоты упоминания каждого символа
    int frequency[26] = { 0 };

    for (int i = 0; i < addsCount; i++) {
        for (int j = 0; j < lengths[i]; j++) {
            frequency[adds[i][j] - 65]++;
        }
    }

    // подсчитать количество уникальных символов
    for (int i = 0; i < 26; i++)
        if (frequency[i] > 0)
            count++;

    // решение невозможно для количества больше 10
    if (count > 10)
    {
        printf("No solution, too many various letters");
        return 0;
    }

    // массив узлов
    Node nodeArr[10];

    // хранить все уникальные символы в nodeArr
    int j = 0;
    for (int i = 0; i < 26; i++)
    {
        if (frequency[i] > 0)
        {
            nodeArr[j].c = i + 65;
            j++;
        }
    }
    return permutation(nodeArr, count, adds, addsCount, 0, addsl);
}

int main() {
    char adds[8][100] = { 0 };
    char tmp[1000] = { 0 };
    char setOfLetters[26] = { 0 };



    gets(tmp);
    int length = strlen(tmp);

    int starttm = clock();
    int addIndex = 0;
    int charIndex = 0;
    int addsl[8] = { 0 };
    for (int i = 0, j = 0; i < length; i++) {
        if (is_letter(tmp[i])) {
            adds[addIndex][charIndex] = tmp[i];
            charIndex++;
        }

        if (i < length - 1) {
            if (is_letter(tmp[i]) && !is_letter(tmp[i + 1])) {
                charIndex = 0;
                addIndex++;
            }
        }
        if (is_letter(tmp[i]))
            addsl[j]++;
        else
        {
            j++;
            i += 2;
        }
    }

    int addsCount = 0;
    for (int i = 0; i < 7; i++) {
        if (strlen(adds[i]) > 0) addsCount++;
    }

    if (solveCryptographic(adds, addsCount, addsl) == false)
        printf("No solution \n");
    int endtm = clock();
    printf(" %.3f", ((float)endtm - (float)starttm) / 1000);

    //SEND + MORE = MONEY
}

