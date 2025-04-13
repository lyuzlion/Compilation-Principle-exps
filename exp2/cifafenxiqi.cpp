#include "cifafenxiqi.h"
using namespace std;

list<Type> Cifafenxiqi::Huodesuoyououken(string &shuru,list<string> &shuhebianhao)
{
    list<Type> shuchu;
    xianzaiweizhi = 0;
    yuchuli(shuru);
    while (xianzaiweizhi < (int)shuru.size())
    {
        string token = huodetouken(shuru);
        if (token.empty())
        {
            continue;
        }
        auto res=jiexitouken(token);
        shuchu.push_back(res.second);
        if(res.second==IDENT)
        {
            shuhebianhao.push_back(res.first);
        }
        else if(res.second==UINT){
            int num=stoi(res.first);
            shuhebianhao.push_back(to_string(num));
        }
        else if(res.second==UDOUBLE){
            double num=stod(res.first);
            shuhebianhao.push_back(to_string(num));
        }
    }
    return shuchu;
}

void Cifafenxiqi::yuchuli(string &shuru)
{
    string temp;
    for (int i = 0; i < (int)shuru.size(); i++)
    {
        if (shuru[i] == '/' && shuru[i + 1] == '*')
        {
            i += 2;
            while (shuru[i] != '*' || shuru[i + 1] != '/')
            {
                i++;
            }
            i += 2;
        }
        temp += shuru[i];
    }
    shuru = temp;
    temp = "";
    for (int i = 0; i < (int)shuru.size(); i++)
    {
        if (shuru[i] == '/' && shuru[i + 1] == '/')
        {
            while (shuru[i] != '\n')
            {
                i++;
            }
        }
        temp += shuru[i];
    }
    shuru = temp;
    temp = "";
    for (int i = 0; i < (int)shuru.size(); i++)
    {
        if (shuru[i] == '\n' || shuru[i] == '\t' || shuru[i] == '\r')
        {
            shuru[i] = ' ';
        }
    }
    temp = "";
    for (int i = 0; i < (int)shuru.size(); i++)
    {
        if (shuru[i] == ' ' && shuru[i + 1] == ' ')
        {
            continue;
        }
        temp += shuru[i];
    }
    shuru = temp;
}

string Cifafenxiqi::huodetouken(string &shuru)
{
    string token;
    zhuangtai = INIT;
    while (shuru[xianzaiweizhi] == ' ' && xianzaiweizhi < (int)shuru.size())
    {
        xianzaiweizhi++;
    }
    while (xianzaiweizhi < (int)shuru.size())
    {
        if (zhuangtai == INIT)
        {
            if (isalpha(static_cast<unsigned char>(shuru[xianzaiweizhi])))
            {
                zhuangtai = READING_WORD;
                token += shuru[xianzaiweizhi];
            }
            else if (isdigit(static_cast<unsigned char>(shuru[xianzaiweizhi])) || shuru[xianzaiweizhi] == '.')
            {
                zhuangtai = READING_NUMBER;
                token += shuru[xianzaiweizhi];
            }
            else if ((std::string("<>=!").find(shuru[xianzaiweizhi]) != std::string::npos))
            {
                token += shuru[xianzaiweizhi];
                xianzaiweizhi++;
                if (shuru[xianzaiweizhi] == '=')
                {
                    token += shuru[xianzaiweizhi];
                    xianzaiweizhi++;
                }
                return token;
            }
            else if (std::string("&|").find(shuru[xianzaiweizhi]) != std::string::npos)
            {
                token += shuru[xianzaiweizhi];
                xianzaiweizhi++;
                if (shuru[xianzaiweizhi] == shuru[xianzaiweizhi - 1])
                {
                    token += shuru[xianzaiweizhi];
                    xianzaiweizhi++;
                }
                return token;
            }
            else if (std::string("{};(),+-*/").find(shuru[xianzaiweizhi]) != std::string::npos)
            {
                token += shuru[xianzaiweizhi];
                xianzaiweizhi++;
                return token;
            }
            else
            {
                cout << "Unrecognizable characters.";
                exit(0);
            }
            xianzaiweizhi++;
        } else if (zhuangtai == READING_WORD) {
            if (isalpha(static_cast<unsigned char>(shuru[xianzaiweizhi])) || isdigit(static_cast<unsigned char>(shuru[xianzaiweizhi])))
            {
                token += shuru[xianzaiweizhi];
            }
            else
            {
                return token;
            }
            xianzaiweizhi++;
        } else if (zhuangtai == READING_NUMBER) {
            if (isdigit(static_cast<unsigned char>(shuru[xianzaiweizhi])) || shuru[xianzaiweizhi] == '.')
            {
                token += shuru[xianzaiweizhi];
            }
            else
            {
                return token;
            }
            xianzaiweizhi++;
        }
    }
    return token;
}

pair<string,Type> Cifafenxiqi::jiexitouken(string &token)
{
    pair<string, Type> temp;
    temp.first = token;
    if (endfuhaos.find(token) != endfuhaos.end())
    {
        temp.second = endfuhaos.at(token);
    }
    else if (isalpha(static_cast<unsigned char>(token[0])))
    {
        temp.second = IDENT;
    }
    else if (isdigit(static_cast<unsigned char>(token[0])) || token[0] == '.')
    {
        if (token[0] == '.' || token[token.size() - 1] == '.')
        {
            cout << "Malformed number: Decimal point at the beginning or end of a floating point number.";
            exit(0);
        }
        if (token[0] == '0')
        {
            if (token.size() > 1)
            {

                if (token[1] != '.')
                {

                    cout << "Malformed number: Leading zeros in an integer.";

                    exit(0);
                }
            }
        }


        bool hasDot = false;
        for (int i = 0; i < (int)token.size(); i++)
        {

            if (token[i] == '.')
            {
                if (hasDot)
                {
                    cout << "Malformed number: More than one decimal point in a floating point number.";
                    exit(0);
                }

                hasDot = true;
            }
            else if (!isdigit(static_cast<unsigned char>(token[i])))
            {
                cout << "Malformed number: Non-digit character in a number.";
                exit(0);
            }
        }
        if (hasDot)
        {
            temp.second = UDOUBLE;
        }
        else
        {
            temp.second = UINT;
        }
    }
    return temp;
}
