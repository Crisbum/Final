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
// Hard 모드: AI가 선택한 숫자를 반환
int SelectAINumber_Hard(int* pAINumber, int* pPlayerNumber) {
    int bestIndex = -1;
    int maxPotentialBingos = -1;

    for (int i = 0; i < 25; i++) {
        if (pAINumber[i] != INT_MAX) {
            int row = i / 5, col = i % 5;
            int rowRemaining = 0, colRemaining = 0, diag1Remaining = 0, diag2Remaining = 0;
            int potentialBingos = 0;
            // 대각선 남은 숫자 계산
            if (row == col) { // 왼쪽 대각선
                for (int j = 0; j < 5; j++) {
                    if (pAINumber[j * 5 + j] != INT_MAX)
                        diag1Remaining++;
                }
            }
            if (row + col == 4) { // 오른쪽 대각선
                for (int j = 0; j < 5; j++) {
                    if (pAINumber[j * 5 + (4 - j)] != INT_MAX)
                        diag2Remaining++;
                }
            }

            // 현재 숫자가 여러 줄에 영향을 미칠 수 있는 경우를 고려하여 potentialBingos 계산
            potentialBingos = 0;
            if (rowRemaining == 1) potentialBingos++;
            if (colRemaining == 1) potentialBingos++;
            if (row == col && diag1Remaining == 1) potentialBingos++;
            if (row + col == 4 && diag2Remaining == 1) potentialBingos++;

            // 최적 선택: 가능한 빙고를 더 많이 만들거나 플레이어의 빙고를 막는 선택
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
    return -1; // 선택 불가능한 경우
}
