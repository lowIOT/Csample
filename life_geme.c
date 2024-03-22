/*
ライフゲームのシミュレーション
*/
#include <conio.h>  // コンソール入力のためのヘッダーファイル
#include <stdio.h>  // 標準入出力のためのヘッダーファイル
#include <stdlib.h> // 乱数生成のためのヘッダーファイル
#include <time.h>   // 時間関連の処理のためのヘッダーファイル

#define FIELD_HEIGHT 24  // フィールドの高さを定義
#define FIELD_WIDTH 24   // フィールドの幅を定義

int cursorX = 1;          // カーソルのX座標を初期化
int cursorY = 1;          // カーソルのY座標を初期化

int cells[2][FIELD_HEIGHT][FIELD_WIDTH]; // セルの状態を保持する配列
int current;                              // 現在の状態を示すインデックス

// 指定した座標周辺の生きているセルの数を返す関数
int getAdjacentLivesCount(int x2, int y2) {
    int count = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if ((x == 0) && (y == 0)) {
                continue;
            }
            int x3 = ((x + x2) + FIELD_WIDTH) % FIELD_WIDTH;
            int y3 = ((y + y2) + FIELD_HEIGHT) % FIELD_HEIGHT;
            count += cells[current][y3][x3];
        }
    }
    return count;
}

int main(void) {
    while (1) {
        system("cls");  // コンソールをクリア

        // フィールドを描画
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            for (int x = 0; x < FIELD_WIDTH; x++) {
                if ((x == cursorX) && (y == cursorY)) {
                    printf("◎ "); // カーソルの位置を描画
                } else {
                    printf("%s", cells[current][y][x] ? "■" : "・"); // セルの状態に応じて描画
                }
            }
            printf("\n");
        }

        // キーボード入力の処理
        switch (_getch()) {
            case 0x48:	cursorY--; break; // 上キーが押された場合
            case 0x50:	cursorY++; break; // 下キーが押された場合
            case 0x4b:	cursorX--; break; // 左キーが押された場合
            case 0x4D:	cursorX++; break; // 右キーが押された場合
            case 0x1b:  // Escキーが押された場合
                // フィールドをクリアして初期化
                for (int y = 0; y < FIELD_HEIGHT; y++) {
                    for (int x = 0; x < FIELD_WIDTH; x++) {
                        cells[current][y][x] = 0;
                    }
                }
                break;
            case 'f':   // 'f'キーが押された場合
                srand((unsigned int)time(NULL)); // 乱数の種を設定

                // フィールドをランダムに初期化
                for (int y = 0; y < FIELD_HEIGHT; y++) {
                    for (int x = 0; x < FIELD_WIDTH; x++) {
                        cells[current][y][x] = rand() % 2;
                    }
                }
                break;
            case ' ':   // スペースキーが押された場合
                cells[current][cursorY][cursorX] ^= 1; // カーソル位置のセルの状態を反転
                break;
            case '\r':  // Enterキーが押された場合
                // セルの更新
                for (int y = 0; y < FIELD_HEIGHT; y++) {
                    for (int x = 0; x < FIELD_WIDTH; x++) {
                        int n = getAdjacentLivesCount(x, y); // 周囲の生きているセルの数を取得
                        int next = cells[current][y][x];     // 次の状態のための変数を初期化

                        // セルのルールに基づいて次の状態を設定
                        if (cells[current][y][x] == 1) {
                            if ((n <= 1) || (n >= 4)) {
                                next = 0;
                            }
                        } else {
                            if (n == 3) {
                                next = 1;
                            }
                        }
                        cells[current ^ 1][y][x] = next; // 次の状態を反映
                    }
                }
                current ^= 1; // 現在の状態を切り替える
                break;
        }
    }
    return 0;
}
