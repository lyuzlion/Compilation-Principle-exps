#ifndef _STRUCT_H
#define _STRUCT_H
#include <bits/stdc++.h>
using namespace std;

#define Type int

#define        START 1
#define        BORTERM 55
#define        PRINTF 45
#define        L 46
#define        B 47
#define        PRINTF_BEGIN 62
#define        END 63
#define        EXPR 48
#define        ORITEM 49
#define        ANDITEM 50
#define        ONE 2
#define        THENSYM 8
#define        PRINTFSYM 6
#define        IFSYM 7
#define        REL 60
#define        LE 15
#define        WHILESYM 9
#define        AND 17
#define        NOT 18
#define        NOTEQU 19
#define        VARIABLE 41
#define        PLUS 20
#define        TIMES 22
#define        DIVISION 23
#define        BANDTERM 56
#define        BFACTOR 57
#define        IDENT 31
#define        COMMA 24
#define        OR 16
#define        ID 30
#define        VARIABLES 39
#define        UDOUBLE 32
#define        UINT 33
#define        RBRACE1 26
#define        LBRACE2 27
#define        RBRACE2 28
#define        DOSYM 10
#define        SCANFSYM 5
#define        ASSIGN 43
#define        SCANF 44
#define        INTSYM 3
#define        EQU 11
#define        GREATER 12
#define        GE 13
#define        LESS 14
#define        SEMICOLON 29
#define        LBRACE1 25
#define        T 42
#define        EQUEQU 34
#define        SUBPROG 36
#define        DOUBLESYM 4
#define        M 37
#define        N 38
#define        MUL_DIV 59
#define        SCANF_BEGIN 61
#define        PLUS_MINUS 58
#define        PROG 35
#define        STATEMENT 40
#define        RELITEM 51
#define        NOITEM 52
#define        ITEM 53
#define        MINUS 21
#define        FACTOR 54
class Fuhao
{
public:
    Fuhao() {
        rleixing = ONE;
    }
    Fuhao(Type leixing) : rleixing(leixing){};
    Type rleixing;
    string quad = "";
    string mingzi = "";
    string xiaobiao = "";
    string duibiao = "";
    string cuobiao = "";
    int leixing = 0;
    int kuandu = 0;
    string op = "";
    string difang = "";
};
class Biaodashi {
public:
    Biaodashi(Type left, vector<Type> right, function<void(void)> action) : left(left), right(right), action(action){};
    Type left;
    vector<Type> right;
    function<void(void)> action;
};
struct Bixiang {
    int expressionIndex;
    size_t dot;
    set<Type> lookAhead;
    bool operator<(const Bixiang &item) const
    {
        if (expressionIndex != item.expressionIndex)
        {
            return expressionIndex < item.expressionIndex;
        }
        if (dot != item.dot)
        {
            return dot < item.dot;
        }

        return false;
    }
    bool operator==(const Bixiang &item) const
    {
        return (!(item<*this))&&(!(*this<item));
    }
};

struct Zhuangtaizhuanyi {
    int oldZhuangtai;
    Type go;
    int newZhuangtai;
    Zhuangtaizhuanyi(int oldZhuangtai,Type go,int newZhuangtai):oldZhuangtai(oldZhuangtai),go(go),newZhuangtai(newZhuangtai){};
    bool operator<(const Zhuangtaizhuanyi &trans) const
    {
        if(this->oldZhuangtai!=trans.oldZhuangtai){
            return this->oldZhuangtai<trans.oldZhuangtai;
        }
        else if(this->go!=trans.go){
            return this->go<trans.go;
        }
        return this->newZhuangtai<trans.newZhuangtai;
    }
};

struct Bijiao {
    bool operator() (const pair<set<Bixiang>,int>& qwe, const pair<set<Bixiang>,int>& asd) const {
        return qwe.first < asd.first;
    }
};

#define SYMINT 0
#define SYMDOUBLE 1

struct Fuhaobiaoxiang{
    string mingzi;
    string value;
    int pianyiliang;
    int leixing;
    bool hasValue=false;
    Fuhaobiaoxiang()=default;
    Fuhaobiaoxiang(string mingzi,int leixing,string value,int pianyiliang):mingzi(mingzi),leixing(leixing),value(value),pianyiliang(pianyiliang){};
};

struct Siyuansshi{
    string op;
    string lczs;
    string rczs;
    string jieguo;
    Siyuansshi(string op,string lczs,string rczs,string jieguo):op(op),lczs(lczs),rczs(rczs),jieguo(jieguo){};
};


struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0): x(x), y(y) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }
};

struct Circle {
    Point O;
    double r;
    Circle(Point O, double r): O(O), r(r) {}
    Point point(double a) {
        return Point(O.x + cos(a) * r, O.y + sin(a) * r);
    }
};

#endif