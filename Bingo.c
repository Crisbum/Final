#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h> // INT_MAX 사용
#pragma warning(disable:4996)

// AI 모드 정의
typedef enum {
    AM_EASY = 1,
    AM_HARD
} AI_MODE;


// 빙고 라인 계산 함수
int CountBingoLines(int* pBoard) {
    int bingo = 0;

    // 가로 확인
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
  // 세로 확인
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
  // 왼쪽 대각선 확인
    int isBingo = 1;
    for (int i = 0; i < 5; i++) {
        if (pBoard[i * 5 + i] != INT_MAX) {
            isBingo = 0;
            break;
        }
    }
    if (isBingo)
        bingo++;
  // 오른쪽 대각선 확인
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
int main()
{
    srand((unsigned int)time(NULL));

    // 플레이어와 AI 빙고판 초기화
    int iNumber[25] = { 25 };
    int iAINumber[25] = { 25 };
    for (int i = 0; i < 25; i++) {
        iNumber[i] = i + 1;
        iAINumber[i] = i + 1;
    }
    // 숫자 섞기
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

    // AI 모드 선택
    while (1) {
        system("cls");
        printf("******** Welcome to Bingo Game *********** \n\n");
        printf("1. Easy\n");
        printf("2. Hard\n\n");
        printf("**************************************** \n\n");
        printf("난이도를 선택하세요: ");
        scanf("%d", &iAIMode);

        if (iAIMode >= AM_EASY && iAIMode <= AM_HARD)
            break;
    }
    // 게임 시작
    while (1) {
        system("cls");

        // 플레이어 빙고판 출력
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
        // 승리 조건 확인
        if (iBingo >= 5) {
            printf("====== 승리하셨습니다! ======\n");
            break;
        }
        if (iAIBingo >= 5) {
            printf("===== 패배하셨습니다. =====\n");
            break;
        }
        // 플레이어 입력
        printf("숫자를 입력하세요 (0 : 종료) : ");
        int iInput;
        scanf("%d", &iInput);

        if (iInput == 0)
            break;
        else if (iInput < 1 || iInput > 25)
            continue;

        // 입력 처리
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
        /*// AI 숫자 선택
        int aiSelectedNumber = 0;
        if (iAIMode == AM_EASY)
            aiSelectedNumber = SelectAINumber_Easy(iAINumber);
        else if (iAIMode == AM_HARD)
            aiSelectedNumber = SelectAINumber_Hard(iAINumber, iNumber);

        // AI 선택 번호를 플레이어 빙고판에서도 마킹
        for (int i = 0; i < 25; i++) {
            if (iNumber[i] == aiSelectedNumber) {
                iNumber[i] = INT_MAX;
                break;
            }
        }

        // AI가 선택한 숫자 출력
        printf("AI가 선택한 숫자: %d \n", aiSelectedNumber);

        // 빙고 라인 계산
        iBingo = CountBingoLines(iNumber);
        iAIBingo = CountBingoLines(iAINumber);

        // 게임 진행을 위해 일시 정지
        system("pause");
    }

    return 0;
}*/
// AI 숫자 선택
        int aiSelectedNumber = 0;
        if (iAIMode == AM_EASY)
            aiSelectedNumber = SelectAINumber_Easy(iAINumber);
        else if (iAIMode == AM_HARD)
            aiSelectedNumber = SelectAINumber_Hard(iAINumber, iNumber);

        // AI 선택 번호를 플레이어 빙고판에서도 마킹
        for (int i = 0; i < 25; i++) {
            if (iNumber[i] == aiSelectedNumber) {
                iNumber[i] = INT_MAX;
                break;
            }
        }

        // AI가 선택한 숫자 출력
        printf("AI가 선택한 숫자: %d \n", aiSelectedNumber);

        // 빙고 라인 계산
        iBingo = CountBingoLines(iNumber);
        iAIBingo = CountBingoLines(iAINumber);

        // 게임 진행을 위해 일시 정지
        system("pause");
    }

    return 0;
}

