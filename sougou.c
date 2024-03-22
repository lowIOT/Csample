#include <stdio.h>
#include <string.h>

//生徒の要素
typedef struct student{

    int num;           //出席番号
    int test_1[5];     //直近1回目のテストの点数用（国語,数学,英語,理科,社会）
    int test_2[5];     //直近2回目のテストの点数用（国語,数学,英語,理科,社会）
    int test_3[5];     //直近3回目のテストの点数用（国語,数学,英語,理科,社会）
    int hantei[4];     //大学の判定用(65→A, 66→B, 67→C)

} student;

//ログイン分岐動作
//パスワード入力とシステム終了
int login(char *pass_1, char *pass_2){

    int select, end_f;      //ログイン選択用（select）,どちらを選択したのかmainに返す用（end_f）

    //システムのタイトル表示
    printf("成績管理システム\n");
    
    while(1){
        //ログイン選択
        printf("ログイン[1], システム終了[2]\n");
        scanf("%d", &select);

        //ログインを選択した場合
        if(select == 1){
            end_f = 1;
            break;

        //システム終了を選択した場合
        }else if(select == 2){
            end_f = 2;
            break;
        
        //選択肢以外の場合
        }else{
            printf("1 or 2 で入力してください。\n");
        }
    }

    //ログインが選択された場合のパスワード入力
    if(end_f == 1){
        while(1){
            //パスワードの入力
            printf("パスワードを入力してください。\n");
            scanf("%s", pass_2);

            //設定してあるパスワード（pass_2）と入力したパスワード(pass_1)が同じ場合
            if(strcmp(pass_1, pass_2) == 0){
                printf("ログインできました。\n");
                printf("\n");
                break;

            //設定してあるパスワード（pass_2）と入力したパスワード(pass_1)が違う場合
            }else{
                printf("パスワードが違います。\n");
                printf("入力しなおしてください。\n");
                printf("\n");
            }
        }
    }
    
    return end_f;      //ログインしたら1をシステム終了したら2をmainに返す

}

//モード選択分岐動作
//パスワード設定、編集、閲覧、ログアウトの中から選ぶ
int mode(void){

    int mode_f;     //どのモードが選ばれたか保存しとく用(1～4)

    while(1){
        
        //選択モードの入力
        printf("モードを選択してください。\n");
        printf("(パスワード設定[1], 編集モード[2], 閲覧モード[3], ログアウト[4])\n");
        scanf("%d", &mode_f);

        //モードが正常に選ばれたら
        if(mode_f > 0 && mode_f <= 4){
            break;
        //モードが正常に選ばれなかったら
        }else{
            printf("1～4で選択してください。\n");
        }
    }

    return mode_f;  //選択したモードの番号をmainに返す

}

//パスワード設定の動作
void password_set(char *pass_1){

    printf("新しいパスワードを入力してください。\n");
    scanf("%s", pass_1);    //新しいパスワードの入力
    printf("パスワードを設定しました。\n");
    printf("\n");

}

//編集モードの動作
int hensyu(student *stu){

    int num_select;     //入力したい生徒の出席番号格納用
    int test_now[5];    //入力したテストの点数を一時的に保存する用
    int hantei[4];      //大学の判定結果を格納する用
    int sum = 0;        //直近のテスト結果の合計用
    int yes_no = 0;     //入力継続の判断用    

    while(1){
        while(1){
            //編集したい生徒の番号を入力
            printf("テストの点数を入力したい生徒の出席番号を入力してください。\n");
            scanf("%d", &num_select);

            //出席番号が1～10で正常に選ばれたら
            if(num_select >= 1 && num_select <= 10){
                break;

            //出席番号が1～10以外で選ばれたら
            }else{
                printf("出席番号は1～10で入力してください。\n");
            }
        }

        //点数の入力
        printf("テスト結果入力\n");

        //点数入力5回分ループ
        for(int i = 0; i < 5; i++){

            while(1){
                //入力する科目の表示
                switch (i){
                case 0:
                    printf("国語の点数は？");
                    break;
                case 1:
                    printf("数学の点数は？");
                    break;
                case 2:
                    printf("英語の点数は？");
                    break;
                case 3:
                    printf("理科の点数は？");
                    break;
                case 4:
                    printf("社会の点数は？");
                    break;
                }

                //テストの点数を入力(iが変動するので科目ごとに入力できる)
                scanf("%d", &test_now[i]);

                //入力したテストの点数が0～100の場合
                if(test_now[i] >= 0 && test_now[i] <= 100){
                    break;

                //入力したテストの点数が0～100以外の場合
                }else{
                    printf("テストの点数は0～100で入力してください。\n");
                }
            }
        }
        
        //テストの点数の入れ替え(古いものから消えて、直近3回分が残るようにする)
        for(int i = 0; i < 5; i++){
            stu[num_select-1].test_3[i] = stu[num_select-1].test_2[i];  //直近3回目に2回目のテストの点数を入れる
            stu[num_select-1].test_2[i] = stu[num_select-1].test_1[i];  //直近2回目に1回目のテストの点数を入れる
            stu[num_select-1].test_1[i] = test_now[i];                  //直近1回目に今入力したテストの点数を入れる
        }

        while(1){
            //入力継続の有無
            printf("入力を続けますか？(続ける[1],やめる[2])\n");
            scanf("%d", &yes_no);

            if(yes_no == 1 || yes_no ==2){
                break;
            }else{
                printf("1 or 2 で入力してください。\n");
            }
        }

        //継続の判断
        //やめる[2]が選択されたらループから抜ける
        if(yes_no == 2){
            break;
        }
    }
}

//大学の判定結果を分類する動作
void college_check(student *stu){

    int sum[10];    //直近のテストの合計を格納する(10人分)

    //大学判定
    //直近のテストの合計を計算
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 5; j++){
            sum[i] = sum[i] + stu[i].test_1[j];
        }
    }

    for(int i = 0; i < 10; i++){
        //A大学判定
        //合計点数が400以上かつ数学90点以上かつ理科90点以上
        if(sum[i] >= 400 && stu[i].test_1[1] >= 90 && stu[i].test_1[3] >= 90){
            stu[i].hantei[0] = 65;    //A判定→「65」はアスキーコードで「A」を表示するため

        //合計点数が300以上かつ数学70点以上かつ理科70点以上
        }else if(sum[i] >= 300 && stu[i].test_1[1] >= 70 && stu[i].test_1[3] >= 70){
            stu[i].hantei[0] = 66;    //B判定→「66」はアスキーコードで「B」を表示するため

        //上記以外
        }else{
            stu[i].hantei[0] = 67;    //C判定→「67」はアスキーコードで「C」を表示するため
        }

        //B大学判定
        //合計点数が400以上かつ国語90点以上かつ英語90点以上
        if(sum[i] >= 400 && stu[i].test_1[0] >= 90 && stu[i].test_1[2] >= 90){
            stu[i].hantei[1] = 65;    //A判定→「65」はアスキーコードで「A」を表示するため

        //合計点数が300以上かつ国語70点以上かつ英語70点以上
        }else if(sum[i] >= 300 && stu[i].test_1[0] >= 70 && stu[i].test_1[2] >= 70){
            stu[i].hantei[1] = 66;    //B判定→「66」はアスキーコードで「B」を表示するため

        //上記以外
        }else{
            stu[i].hantei[1] = 67;    //C判定→「67」はアスキーコードで「C」を表示するため
        }

        //C大学判定
        //合計点数が450以上かつ国語90点以上かつ数学90点以上かつ英語90点以上
        if(sum[i] >= 450 && stu[i].test_1[0] >= 90 && stu[i].test_1[1] >= 90 && stu[i].test_1[2] >= 90){
            stu[i].hantei[2] = 65;    //A判定→「65」はアスキーコードで「A」を表示するため

        //合計点数が400以上かつ国語70点以上かつ数学70点以上かつ英語70点以上
        }else if(sum[i] >= 400 && stu[i].test_1[0] >= 70 && stu[i].test_1[1] >= 70 && stu[i].test_1[2] >= 70){
            stu[i].hantei[2] = 66;    //B判定→「66」はアスキーコードで「B」を表示するため

        //上記以外
        }else{
            stu[i].hantei[2] = 67;    //C判定→「67」はアスキーコードで「C」を表示するため
        }

        //D大学判定
        //合計点数が350以上かつ理科80点以上または社会80点以上
        if(sum[i] >= 350 && (stu[i].test_1[3] >= 80 || stu[i].test_1[4] >= 80)){
            stu[i].hantei[3] = 65;    //A判定→「65」はアスキーコードで「A」を表示するため

        //合計点数が300以上かつ理科60点以上または社会60点以上
        }else if(sum[i] >= 300 && (stu[i].test_1[3] >= 60 || stu[i].test_1[4] >= 60)){
            stu[i].hantei[3] = 66;    //B判定→「66」はアスキーコードで「B」を表示するため

        //上記以外
        }else{
            stu[i].hantei[3] = 67;    //C判定→「67」はアスキーコードで「C」を表示するため
        }
    }
}

//閲覧モードの動作
int eturan(student *stu){

    int mode_eturan;    //閲覧したいものの選択用
    int num;            //閲覧したい生徒の出席番号入力用
    int f = 0;          //閲覧モードの終了用フラグ
    
    while(f == 0){

        //閲覧したいものの選択
        printf("閲覧したいものを選択してください。\n");
        printf("(テスト結果閲覧[1], 判定結果閲覧[2], 閲覧終了[3])\n");
        scanf("%d", &mode_eturan);

        switch (mode_eturan){

        //テスト結果閲覧が選択された場合
        case 1:

            while(1){
                //閲覧したい生徒の出席番号を入力
                printf("閲覧したい生徒の出席番号を入力してください。\n");
                scanf("%d", &num);
                printf("\n");

                //出席番号が1～10で正常に選ばれたら
                if(num >= 1 && num <= 10){
                    break;

                //出席番号が1～10以外で選ばれたら
                }else{
                    printf("出席番号は1～10で入力してください。\n");
                }
            }

            //入力した番号の生徒のテスト結果表示
            printf("出席番号%d番の人のテスト結果\n", num);
            printf("\n");

            //直近のテスト結果
            printf("直近のテスト結果\n");
            printf("国語%d点,数学%d点,英語%d点,理科%d点,社会%d点\n", stu[num-1].test_1[0],stu[num-1].test_1[1],stu[num-1].test_1[2],stu[num-1].test_1[3],stu[num-1].test_1[4]);
            printf("\n");

            //1回前のテスト結果
            printf("1回前のテスト結果\n");
            printf("国語%d点,数学%d点,英語%d点,理科%d点,社会%d点\n", stu[num-1].test_2[0],stu[num-1].test_2[1],stu[num-1].test_2[2],stu[num-1].test_2[3],stu[num-1].test_2[4]);
            printf("\n");

            //2回前のテスト結果
            printf("2回前のテスト結果\n");
            printf("国語%d点,数学%d点,英語%d点,理科%d点,社会%d点\n", stu[num-1].test_3[0],stu[num-1].test_3[1],stu[num-1].test_3[2],stu[num-1].test_3[3],stu[num-1].test_3[4]);
            printf("\n");
            break;

        //判定結果閲覧が選択された場合
        case 2:

            while(1){
                //閲覧したい生徒の出席番号を入力
                printf("閲覧したい生徒の出席番号を入力してください。\n");
                scanf("%d", &num);

                //出席番号が1～10で正常に選ばれたら
                if(num >= 1 && num <= 10){
                    break;

                //出席番号が1～10以外で選ばれたら
                }else{
                    printf("出席番号は1～10で入力してください。\n");
                }
            }

            //入力した番号の生徒の大学判定結果表示
            printf("出席番号%d番の人の大学判定結果\n", num);
            //A大学の判定結果
            printf("A大学の判定結果 %c判定\n", stu[num-1].hantei[0]);
            //B大学の判定結果
            printf("B大学の判定結果 %c判定\n", stu[num-1].hantei[1]);
            //C大学の判定結果
            printf("C大学の判定結果 %c判定\n", stu[num-1].hantei[2]);
            //D大学の判定結果
            printf("D大学の判定結果 %c判定\n", stu[num-1].hantei[3]);

            break;

        //閲覧終了が選択された場合
        case 3:
            f = 1;      //閲覧終了が選ばれたら、フラグを立てる
            break;
        
        //選択肢に無い数字を入力された場合
        default:
            printf("1～3で選択してください。\n");
            break;
        }
    }
}

int main(void){

    //生徒情報格納用
    //生徒情報の宣言と初期値設定{出席番号,{テスト結果1[5]},{テスト結果2[5]},{テスト結果3[5]},{大学判定[4]}} → 10人分
    student stu[10] = {{1,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}},{2,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}},
                       {3,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}},{4,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}},
                       {5,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}},{6,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}},
                       {7,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}},{8,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}},
                       {9,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}},{10,{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0}}
                      };

    char pass_1[10] = "pass";   //参照用のパスワード用
    char pass_2[10];            //入力用のパスワード用

    int end;            //システム終了判断用
    int mode_main;      //どのモードがえらばれたか用
    int logout = 0;     //ログアウト用フラグ

    while(1){

        end = login(pass_1, pass_2);    //ログイン用の関数を呼び出して、戻り値をendに代入

        //ログインを選択された場合 → login関数から1が戻ってきたら
        if(end == 1){
            logout = 0;             //ログアウト用のフラグを0にする
            while(logout == 0){
                mode_main = mode();     //モード選択用の関数を呼び出し
                
                switch (mode_main){
                //パスワード設定が選択された場合
                case 1:
                    password_set(pass_1);   //パスワード設定用の関数を呼び出し
                    break;
                
                //編集モードが選択された場合
                case 2:
                    hensyu(stu);            //編集モード用の関数を呼び出し
                    college_check(stu);     //大学判定用の関数を呼び出し
                    break;
            
                //閲覧モードが選択された場合
                case 3:
                    eturan(stu);            //閲覧モード用の関数を呼び出し
                    break;
                
                //ログアウトが選択された場合
                case 4:
                    printf("ログアウトしました。\n");
                    printf("\n");
                    logout = 1;         //ログアウト用のフラグを1にする
                    break;
                }
            }

        //システム終了が選択された場合 → login関数から2が戻ってきたら
        }else{
            printf("システムを終了します。\n");
            break;
        }
    }
}