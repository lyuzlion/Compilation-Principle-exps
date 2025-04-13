#include"jiexiqi.h"
#include"cifafenxiqi.h"
using namespace std;

int main()
{
    string shuru;
    int cnt = 0;
    string line;
    while(getline(cin, line))
    {
        ++cnt;
        shuru += line + "\n";
        // if(cnt == 23) break;
    }

    Jiexiqi jiexiqi;
    Cifafenxiqi cifafenxiqi;
    auto tmp = cifafenxiqi.Huodesuoyououken(shuru,jiexiqi.shuhebianhao);
    jiexiqi.yunxing(tmp);
    jiexiqi.shuchu();
    return 0;
}