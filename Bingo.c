#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h> // INT_MAX ���
#pragma warning(disable:4996)

// AI ��� ����
typedef enum {
    AM_EASY = 1,
    AM_HARD
} AI_MODE;

// ���� ���� ��� �Լ�
int CountBingoLines(int* pBoard) {
    int bingo = 0;

    // ���� Ȯ��
    for (int i = 0; i < 5; i++) {
        int isBingo = 1;
        for (int j = 0; j < 5; j++) {
            if (pBoard[i * 5 + j] != INT_MAX) {
                isBingo = 0;
                break;
            }
        }
        if (isBingo)
            bingo++;
    }

    // ���� Ȯ��
    for (int i = 0; i < 5; i++) {
        int isBingo = 1;
        for (int j = 0; j < 5; j++) {
            if (pBoard[j * 5 + i] != INT_MAX) {
                isBingo = 0;
                break;
            }
        }
        if (isBingo)
            bingo++;
    }

    // ���� �밢�� Ȯ��
    int isBingo = 1;
    for (int i = 0; i < 5; i++) {
        if (pBoard[i * 5 + i] != INT_MAX) {
            isBingo = 0;
            break;
        }
    }
    if (isBingo)
        bingo++;

    // ������ �밢�� Ȯ��
    isBingo = 1;
    for (int i = 0; i < 5; i++) {
        if (pBoard[i * 5 + (4 - i)] != INT_MAX) {
            isBingo = 0;
            break;
        }
    }
    if (isBingo)
        bingo++;

    return bingo;
}

// Easy ���: AI�� ������ ���ڸ� ��ȯ
int SelectAINumber_Easy(int* pAINumber) {
    while (1) {
        int randIndex = rand() % 25;

        if (pAINumber[randIndex] != INT_MAX) {
            int selectedNumber = pAINumber[randIndex];
            pAINumber[randIndex] = INT_MAX; // ���õ� ���ڸ� ��ŷ
            return selectedNumber; // ������ ���ڸ� ��ȯ
        }
    }
}

// Hard ���: AI�� ������ ���ڸ� ��ȯ
int SelectAINumber_Hard(int* pAINumber, int* pPlayerNumber) {
    int bestIndex = -1;
    int maxPotentialBingos = -1;

    for (int i = 0; i < 25; i++) {
        if (pAINumber[i] != INT_MAX) {
            int row = i / 5, col = i % 5;
            int rowRemaining = 0, colRemaining = 0, diag1Remaining = 0, diag2Remaining = 0;
            int potentialBingos = 0;

            // ����, ���� ���� ���� ���
            for (int j = 0; j < 5; j++) {
                if (pAINumber[row * 5 + j] != INT_MAX)
                    rowRemaining++;
                if (pAINumber[j * 5 + col] != INT_MAX)
                    colRemaining++;
            }

            // �밢�� ���� ���� ���
            if (row == col) { // ���� �밢��
                for (int j = 0; j < 5; j++) {
                    if (pAINumber[j * 5 + j] != INT_MAX)
                        diag1Remaining++;
                }
            }
            if (row + col == 4) { // ������ �밢��
                for (int j = 0; j < 5; j++) {
                    if (pAINumber[j * 5 + (4 - j)] != INT_MAX)
                        diag2Remaining++;
                }
            }

            // ���� ���ڰ� ���� �ٿ� ������ ��ĥ �� �ִ� ��츦 ����Ͽ� potentialBingos ���
            potentialBingos = 0;
            if (rowRemaining == 1) potentialBingos++;
            if (colRemaining == 1) potentialBingos++;
            if (row == col && diag1Remaining == 1) potentialBingos++;
            if (row + col == 4 && diag2Remaining == 1) potentialBingos++;

            // ���� ����: ������ ���� �� ���� ����ų� �÷��̾��� ���� ���� ����
            if (potentialBingos > maxPotentialBingos) {
                maxPotentialBingos = potentialBingos;
                bestIndex = i;
            }
        }
    }

    if (bestIndex != -1) {
        int selectedNumber = pAINumber[bestIndex];
        pAINumber[bestIndex] = INT_MAX;
        return selectedNumber;
    }
    return -1; // ���� �Ұ����� ���
}

int main()
{
    srand((unsigned int)time(NULL));

    // �÷��̾�� AI ������ �ʱ�ȭ
    int iNumber[25] = { 25 };
    int iAINumber[25] = { 25 };
    for (int i = 0; i < 25; i++) {
        iNumber[i] = i + 1;
        iAINumber[i] = i + 1;
    }

    // ���� ����
    for (int i = 0; i < 100; i++) {
        int idx1 = rand() % 25;
        int idx2 = rand() % 25;
        int temp = iNumber[idx1];
        iNumber[idx1] = iNumber[idx2];
        iNumber[idx2] = temp;

        temp = iAINumber[idx1];
        iAINumber[idx1] = iAINumber[idx2];
        iAINumber[idx2] = temp;
    }

    int iBingo = 0, iAIBingo = 0;
    int iAIMode;

    // AI ��� ����
    while (1) {
        system("cls");
        printf("******** Welcome to Bingo Game *********** \n\n");
        printf("1. Easy\n");
        printf("2. Hard\n\n");
        printf("**************************************** \n\n");
        printf("���̵��� �����ϼ���: ");
        scanf("%d", &iAIMode);
 
        if (iAIMode >= AM_EASY && iAIMode <= AM_HARD)
            break;
    }

    // ���� ����
    while (1) {
        system("cls");

        // �÷��̾� ������ ���
        printf("=========== Player ===========\n");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (iNumber[i * 5 + j] == INT_MAX)
                    printf("*\t");
                else
                    printf("%d\t", iNumber[i * 5 + j]);
            }
            printf("\n");
        }
        printf("Bingo Line : %d\n\n", iBingo);

        // �¸� ���� Ȯ��
        if (iBingo >= 5) {
            printf("====== �¸��ϼ̽��ϴ�! ======\n");
            break;
        }
        if (iAIBingo >= 5) {
            printf("===== �й��ϼ̽��ϴ�. =====\n");
            break;
        }

        // �÷��̾� �Է�
        printf("���ڸ� �Է��ϼ��� (0 : ����) : ");
        int iInput;
        scanf("%d", &iInput);

        if (iInput == 0)
            break;
        else if (iInput < 1 || iInput > 25)
            continue;

        // �Է� ó��
        int isValid = 0;
        for (int i = 0; i < 25; i++) {
            if (iNumber[i] == iInput) {
                iNumber[i] = INT_MAX;
                isValid = 1;
                break;
            }
        }
        if (!isValid)
            continue;

        // AI ���� ����
        int aiSelectedNumber = 0;
        if (iAIMode == AM_EASY)
            aiSelectedNumber = SelectAINumber_Easy(iAINumber);
        else if (iAIMode == AM_HARD)
            aiSelectedNumber = SelectAINumber_Hard(iAINumber, iNumber);

        // AI ���� ��ȣ�� �÷��̾� �����ǿ����� ��ŷ
        for (int i = 0; i < 25; i++) {
            if (iNumber[i] == aiSelectedNumber) {
                iNumber[i] = INT_MAX;
                break;
            }
        }

        // AI�� ������ ���� ���
        printf("AI�� ������ ����: %d \n", aiSelectedNumber);

        // ���� ���� ���
        iBingo = CountBingoLines(iNumber);
        iAIBingo = CountBingoLines(iAINumber);

        // ���� ������ ���� �Ͻ� ����
        system("pause");
    }

    return 0;
}