#ifndef _PARSER_H
#define _PARSER_H
#include"cifafenxiqi.h"
#include"struct.h"
using namespace std;
class Jiexiqi
{
private:
    int OFFSET = 0;
    int nxq = 0;
    int tempIndex = 0;

    list<Fuhao> fuhaozhan;
    stack<int> zhuangtaizhan;
    list<Type> shuru;

    vector<Biaodashi> grammar;
    map<Type, vector<int>> l2r;
    map<Type, set<Type>> first;
    map<Type, set<Type>> follow;
    set<pair<set<Bixiang>,int>,Bijiao> C;
    map<int,set<Bixiang>> int2I;
    set<Zhuangtaizhuanyi> ZhuangtaizhuanyiSet;
    std::map<int, map<Type,function<void(void)>>> analyticalTable;
    vector<Fuhaobiaoxiang> fuhaoTable;
    map<string,int> fuhaoTableIndex;
    vector<Siyuansshi> SiyuansshiTable;
    vector<Type> allTypes = {
        EQU,
        DOSYM,
        GE,
        LESS,
        LE,
        DOUBLESYM,
        SCANFSYM,
        GREATER,
        WHILESYM,
        PRINTFSYM,
        AND,
        NOT,
        LBRACE1,
        RBRACE1,
        OR,
        SEMICOLON,
        MINUS,
        IFSYM,
        NOTEQU,
        COMMA,
        RBRACE2,
        ID,
        LBRACE2,
        TIMES,
        PLUS,
        SUBPROG,
        IDENT,
        INTSYM,
        PROG,
        DIVISION,
        THENSYM,
        VARIABLES,
        VARIABLE,
        UDOUBLE,
        M,
        EQUEQU,
        ONE,
        UINT,
        ASSIGN,
        FACTOR,
        END,
        START,
        STATEMENT,
        N,
        PLUS_MINUS,
        BANDTERM,
        T,
        SCANF,
        PRINTF,
        BORTERM,
        MUL_DIV,
        PRINTF_BEGIN,
        L,
        BFACTOR,
        B,
        EXPR,
        RELITEM,
        NOITEM,
        ANDITEM,
        ORITEM,
        SCANF_BEGIN,
        REL,
        ITEM,
    };

    set<int> endsymbosSet = {
        DOUBLESYM,
        PRINTFSYM,
        INTSYM,
        GREATER,
        SCANFSYM,
        THENSYM,
        AND,
        DOSYM,
        LE,
        OR,
        LESS,
        IFSYM,
        NOT,
        TIMES,
        WHILESYM,
        EQUEQU,
        PLUS,
        EQU,
        NOTEQU,
        MINUS,
        IDENT,
        LBRACE2,
        LBRACE1,
        COMMA,
        DIVISION,
        RBRACE2,
        UINT,
        SEMICOLON,
        RBRACE1,
        UDOUBLE,
        GE,
    };
    void jinru(string mingzi, int leixing, int pianyiliang);
    void huodediyige();
    set<Bixiang> Xiayige(set<Bixiang> i,Type a);
    void func1(string p, string t);
    void huodexiayige();
    void getC();
    set<Bixiang> Bibao(Bixiang sourceItem);
    set<Type> huodediyigeForCandidate(vector<Type> candidate);  
    void Huodebiao();
    void chansheng(string op, string lczs, string rczs, string jieguo);
    string hebing(string p1, string p2);
    string kanshang(string mingzi);

    string xinzhong(int leixing);

public:
    Jiexiqi();
    void yunxing(list<Type> oshuru);
    void shuchu();
    list<string> shuhebianhao;
};
#endif