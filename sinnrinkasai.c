/*
カーソルの操作:矢印キーを使用してカーソルを移動できます。カーソルの位置は、森のセルに木を配置するために使用されます。
木の配置:'f'キーを押すことで、カーソルの位置に木（状態5）が配置されます。
ランダムな木の配置:スペースキーを押すと、ランダムな配置でフィールドに木が配置されます。
森林火災のシミュレーション:Enterキーを押すと、森林火災のシミュレーションが実行されます。各セルの周囲の木の数に応じて、セルの状態が変化します。
初期化:Escキーを押すと、フィールドがクリアされ、すべてのセルの状態がリセットされます。
表示:森の状態は定期的に画面に表示され、木や空白がそれぞれ異なる記号で表現されます。
プログラムのループ:メインの無限ループによって、ユーザーの入力を待ち続け、森の状態が更新されます。
*/
#include <conio.h>  // コンソール入力のためのヘッダーファイル
#include <stdio.h>  // 標準入出力のためのヘッダーファイル
#include <stdlib.h> // 乱数生成のためのヘッダーファイル
#include <time.h>   // 時間関連の処理のためのヘッダーファイル

#define FIELD_WIDTH 25  // フィールドの幅を定義
#define FIELD_HEIGHT 25 // フィールドの高さを定義

int cells[2][FIELD_HEIGHT][FIELD_WIDTH]; // セルの状態を保持する配列
int current;                               // 現在の状態を示すインデックス
int cursorX = 1;                           // カーソルのX座標を初期化
int cursorY = 1;                           // カーソルのY座標を初期化

// 指定した座標周辺の木の状態をカウントする関数
int forest_Fire_Simulation(int x2, int y2) {
    int count = 0;
    // 周囲のセルを調べる
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            // 周囲のセルの座標を計算する
            int x3 = (FIELD_WIDTH + x2 + x) % FIELD_WIDTH;
            int y3 = (FIELD_HEIGHT + y2 + y) % FIELD_HEIGHT;
            
            // 境界のセルは無視する
            if (x2 == 0 || x2 == 24 || y2 == 0 || y2 == 24)
                continue;
            
            // セルの状態が5以下（木が生えている状態）ならカウントを増やす
            if (cells[current][y3][x3] <= 5)
                count++;
        }
    }
    return count;
}

// フィールドに木をランダムに配置する関数
void set_trees() {
    srand((unsigned int)time(NULL)); // 乱数の種を設定
    
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        for (int x = 0; x < FIELD_WIDTH; x++) {
            // 50%の確率でセルに木（状態5）を配置する
            cells[current][y][x] = rand() % 2 ? 5 : 0;
        }
    }
}

int main() {
    // メインの無限ループ
    while (1) {
        system("cls"); // コンソールをクリア
        
        // フィールドを描画
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            for (int x = 0; x < FIELD_WIDTH; x++) {
                if ((x == cursorX) && (y == cursorY)) {
                    printf("◎ "); // カーソルの位置を描画
                }
                else if ((x == 0) || (x == 24) || (y == 0) || (y == 24)) {
                    printf("  "); // フィールドの境界を描画
                }
                else {
                    // セルの状態に応じて異なる記号で描画
                    switch (cells[current][y][x]) {
                        case 0: printf("・ "); break; // 空白（無し）
                        case 1: printf("△ "); break; // 状態1
                        case 2: printf("□ "); break; // 状態2
                        case 3: printf("□ "); break; // 状態3
                        case 4: printf("□ "); break; // 状態4
                        case 5: printf("■ "); break; // 状態5
                        case 6: printf("■ "); break; // 状態6
                        case 7: printf("■ "); break; // 状態7
                        case 8: printf("■ "); break; // 状態8
                        case 9: printf("▲ "); break; // 状態9
                    }
                }
            }
            printf("\n"); // 改行
        }
        
        // キーボード入力の処理
        switch (_getch()) {
            case 0x48: cursorY--; break;        // 上キーが押された場合
            case 0x50: cursorY++; break;        // 下キーが押された場合
            case 0x4b: cursorX--; break;        // 左キーが押された場合
            case 0x4D: cursorX++; break;        // 右キーが押された場合
            case 'f': cells[current][cursorY][cursorX] = 5; break; // 'f'キーが押された場合、セルに木（状態5）を配置
            case 0x1B: // Escキーが押された場合、フィールドをクリア
                for (int y = 0; y < FIELD_HEIGHT; y++) {
                    for (int x = 0; x < FIELD_WIDTH; x++) {
                        cells[current][y][x] = 0;
                    }
                }
                break;
            case ' ': set_trees(); break; // スペースキーが押された場合、ランダムに木を配置
            case '\r': // Enterキーが押された場合、森林火災シ
// 森林火災シミュレーションを実行
                for (int y = 0; y < FIELD_HEIGHT; y++) {
                    for (int x = 0; x < FIELD_WIDTH; x++) {
                        int n = forest_Fire_Simulation(x, y); // 周囲の木の数を取得
                        int next = cells[current][y][x];     // 次の状態のための変数を初期化

                        // セルの状態に応じたルールで次の状態を計算
                        switch (cells[current][y][x]) {
                            case 0:
                                next = 0;
                                break;
                            case 1:
                            case 2:
                            case 3:
                            case 4:
                                if (n >= 2 && n <= 4)
                                    next = cells[current][y][x] + 1;
                                break;
                            case 5:
                                if (n >= 1 && n <= 6)
                                    next = 6;
                                break;
                            case 6:
                            case 7:
                            case 8:
                                if (n >= 1 && n <= 8)
                                    next = cells[current][y][x] + 1;
                                break;
                            case 9:
                                next = 9;
                                break;
                        }
                        cells[current ^ 1][y][x] = next; // 次の状態を更新
                    }
                }
                current ^= 1; // 現在の状態を反転させる
                break;
        }
    }
    return 0; // プログラムの正常終了を示す
}
