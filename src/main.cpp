#include "mbed.h"           //mbed.hのインクルード
#include "FIRSTPENGUIN.hpp" //FIRSTPENGUIN.hppのインクルード

constexpr uint32_t can_id = 35; // FPのCAN通信のIDを設定
int16_t counter = 0;            // カウンターの初期値を設定
bool orientation = true;        // 向きを設定

DigitalIn button(BUTTON1); // ボタンの設定

BufferedSerial pc(USBTX, USBRX, 115200); // シリアル通信の設定
CAN can(PA_11, PA_12, (int)1e6);         // CAN通信の設定

FirstPenguin penguin(can_id, can); // FPの設定

// メイン関数
int main()
{
    while (1) // 無限ループ
    {
        if (button == 0) // ボタンが押されたら
        {

            penguin.pwm[0] = counter; // FPのPWMの値を設定
            penguin.pwm[1] = counter;
            penguin.pwm[2] = counter;
            penguin.pwm[3] = counter;
            if (counter > 10000) // カウンターが10000を超えたら
            {
                orientation = false; // 向きを逆にする
            }
            else if (counter < -10000)
            {
                orientation = true;
            }
            if (orientation)
            {
                counter += 100;
            }
            else
            {
                counter -= 100;
            }
            printf("counter: %d\n", counter); // カウンターの値を表示
            penguin.send();                   // FPにデータを送信
        }
        else // ボタンが押されていないとき
        {
            counter = 0; // カウンターをリセット
        }
        ThisThread::sleep_for(20ms);
    }
}
