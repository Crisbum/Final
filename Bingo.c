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

// Easy 모드: AI가 선택한 숫자를 반환
int SelectAINumber_Easy(int* pAINumber) {
    while (1) {
        int randIndex = rand() % 25;

        if (pAINumber[randIndex] != INT_MAX) {
            int selectedNumber = pAINumber[randIndex];
            pAINumber[randIndex] = INT_MAX; // 선택된 숫자를 마킹
            return selectedNumber; // 선택한 숫자를 반환
        }
    }
}
