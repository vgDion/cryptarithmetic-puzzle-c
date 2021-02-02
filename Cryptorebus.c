#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#pragma warning (disable: 4996)

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

// structure to store char and its corresponding integer 


// function check for correct solution 
int check(Node* nodeArr, const int count, char adds[][100], int addsCount)
{
    int values[8] = { 0 };
    int m = 1;
    int i, j;

    for (int k = 0; k < addsCount; k++) {
        for (i = strlen(adds[k]) - 1; i >= 0; i--)
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

// Recursive function to check solution for all permutations 
bool permutation(Node* nodeArr, const int count, char adds[][100], int addsCount, int n)
{
    // Base case 
    if (n == count - 1)
    {

        // check for all numbers not used yet 
        for (int i = 0; i < 10; i++)
        {

            // if not used 
            if (use[i] == 0)
            {

                // assign char at index n integer i 
                nodeArr[n].v = i;

                // if solution found 
                if (check(nodeArr, count, adds, addsCount) == 1)
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

        // if ith integer not used yet 
        if (use[i] == 0)
        {

            // assign char at index n integer i 
            nodeArr[n].v = i;

            // mark it as not available for other char 
            use[i] = 1;

            // call recursive function 
            if (permutation(nodeArr, count, adds, addsCount, n + 1))
                return true;

            // backtrack for all other possible solutions 
            use[i] = 0;
        }
    }
    return false;
}

bool solveCryptographic(char adds[][100], int addsCount)
{
    // count to store number of unique char 
    int count = 0;
    int lengths[8] = { 0 };

    for (int i = 0; i < addsCount; i++) {
        lengths[i] = strlen(adds[i]);
    }

    // vector to store frequency of each char 
    int frequency[26] = { 0 };

    for (int i = 0; i < addsCount; i++) {
        for (int j = 0; j < lengths[i]; j++) {
            frequency[adds[i][j] - 65]++;
        }
    }

    // count number of unique char 
    for (int i = 0; i < 26; i++)
        if (frequency[i] > 0)
            count++;

    // solution not possible for count greater than 10 
    if (count > 10)
    {
        printf("No solution, too many various letters");
        return 0;
    }

    // array of nodes 
    Node nodeArr[10];

    // store all unique char in nodeArr 
    int j = 0;
    for (int i = 0; i < 26; i++)
    {
        if (frequency[i] > 0)
        {
            nodeArr[j].c = i + 65;
            j++;
        }
    }
    return permutation(nodeArr, count, adds, addsCount, 0);
}

int main() {
    char adds[8][100] = { 0 };
    char tmp[1000] = { 0 };
    char setOfLetters[26] = { 0 };

    gets(tmp);
    int length = strlen(tmp);

    int addIndex = 0;
    int charIndex = 0;
    for (int i = 0; i < length; i++) {
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
    }

    int addsCount = 0;
    for (int i = 0; i < 7; i++) {
        if (strlen(adds[i]) > 0) addsCount++;
    }

    if (solveCryptographic(adds, addsCount) == false)
        printf("No solution");


    //SEND + MORE = MONEY
}

