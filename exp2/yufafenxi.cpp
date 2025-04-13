#include "jiexiqi.h"
using namespace std;

Jiexiqi::Jiexiqi()
{   
    grammar={
        {START,{PROG},[&](){
            int loopsz=1;
            
            
            
            while(loopsz--){
                fuhaozhan.pop_back();
                
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(START);
            
            fuhaozhan.push_back(fuhao);
        }},
        {PROG,{SUBPROG},[&](){
            
            
            int loopsz=1;
            
            while(loopsz--){
                
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(PROG);
            fuhaozhan.push_back(fuhao);
        }},
        {SUBPROG,{M,VARIABLES,STATEMENT},[&](){
            
            
            int loopsz=3;
            
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            
            
            
            
            auto zhuangtaiment=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            
            auto variables=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            auto m=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            Fuhao fuhao(SUBPROG);
            
            func1(zhuangtaiment.xiaobiao,to_string(nxq));
            
            chansheng("End","-","-","-");
            
            fuhaozhan.push_back(fuhao);
        }},
        {M,{ONE},[&](){
            
            OFFSET=0;
            
            zhuangtaizhan.pop();
            
            Fuhao fuhao(M);
            
            fuhaozhan.push_back(fuhao);
            
        }},
        {N,{ONE},[&](){
            
            zhuangtaizhan.pop();
            
            Fuhao fuhao(N);
            
            fuhao.quad=to_string(nxq);
            
            fuhaozhan.push_back(fuhao);
            
            
        }},
        //变量声明部分
        {VARIABLES,{VARIABLES,VARIABLE,SEMICOLON},[&](){
            
            
            int loopsz=3;
            
            while(loopsz--){
                
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(VARIABLES);
            
            fuhaozhan.push_back(fuhao);
        }},
        {VARIABLES,{VARIABLE,SEMICOLON},[&](){
            int loopsz=2;
            
            
            while(loopsz--){
                
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            
            Fuhao fuhao(VARIABLES);
            
            fuhaozhan.push_back(fuhao);
        }},
        {T,{INTSYM},[&](){
            
            
            
            fuhaozhan.pop_back();
            
            zhuangtaizhan.pop();
            Fuhao fuhao(T);
            
            fuhao.leixing=SYMINT;
            
            fuhao.kuandu=4;
            
            fuhaozhan.push_back(fuhao);
        }},
        {T,{DOUBLESYM},[&](){
            
            fuhaozhan.pop_back();
            zhuangtaizhan.pop();
            
            Fuhao fuhao(T);
            
            fuhao.leixing=SYMDOUBLE;
            
            fuhao.kuandu=8;
            
            fuhaozhan.push_back(fuhao);
        }},
        {ID,{IDENT},[&](){
            
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
            
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(ID);
            fuhao.mingzi=shuhebianhao.front();
            
            shuhebianhao.pop_front();
            
            fuhaozhan.push_back(fuhao);
        }},
        {VARIABLE,{T,ID},[&](){
            
            
            
            int loopsz=2;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto id=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            auto t=fuhaozhan.back();
            
            
            fuhaozhan.pop_back();
            
            jinru(id.mingzi,t.leixing,OFFSET);
            OFFSET+=t.kuandu;
            
            
            Fuhao fuhao(VARIABLE);
            
            fuhao.leixing=t.leixing;
            
            fuhao.kuandu=t.kuandu;
            
            fuhaozhan.push_back(fuhao);
        }},
        {VARIABLE,{VARIABLE,COMMA,ID},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            
            auto id=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            fuhaozhan.pop_back();
            
            auto varible=fuhaozhan.back();
            fuhaozhan.pop_back();
            jinru(id.mingzi,varible.leixing,OFFSET);
            
            OFFSET+=varible.kuandu;
            Fuhao fuhao(VARIABLE);
            
            fuhao.leixing=varible.leixing;
            fuhao.kuandu=varible.kuandu;
            
            fuhaozhan.push_back(fuhao);
        }},
        //语句部分
        {STATEMENT,{ASSIGN},[&](){
            
            
            int loopsz=1;
            
            while(loopsz--){
            
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            
            Fuhao fuhao(STATEMENT);
            
            fuhao.xiaobiao="null";
            
            fuhaozhan.push_back(fuhao);
        }},
        {STATEMENT,{SCANF},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(STATEMENT);
            
            fuhao.xiaobiao="null";
            
            fuhaozhan.push_back(fuhao);
        }},
        {STATEMENT,{PRINTF},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(STATEMENT);
            
            fuhao.xiaobiao="null";
            
            fuhaozhan.push_back(fuhao);
        }},
        {STATEMENT,{ONE},[&](){
            
            
            zhuangtaizhan.pop();
            
            Fuhao fuhao(STATEMENT);
            
            fuhao.xiaobiao="null";
            fuhaozhan.push_back(fuhao);
        }},
        {STATEMENT,{LBRACE2,L,SEMICOLON,RBRACE2},[&](){
            
            
            int loopsz=4;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            fuhaozhan.pop_back();
            fuhaozhan.pop_back();
            
            auto l=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            
            
            Fuhao fuhao(STATEMENT);
            
            fuhao.xiaobiao=l.xiaobiao;
            
            fuhaozhan.push_back(fuhao);
        }},
        {STATEMENT,{WHILESYM,N,B,DOSYM,N,STATEMENT},[&](){
            
            
            int loopsz=6;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto zhuangtaiment=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            auto n2=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            
            auto b=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            auto n1=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            Fuhao fuhao(STATEMENT);
            func1(zhuangtaiment.xiaobiao,n1.quad);
            
            func1(b.duibiao,n2.quad);
            
            fuhao.xiaobiao=b.cuobiao;
            chansheng("j","-","-",n1.quad);
            fuhaozhan.push_back(fuhao);
        }},
        {STATEMENT,{IFSYM,B,THENSYM,N,STATEMENT},[&](){
            
            
            int loopsz=5;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto zhuangtaiment=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            auto n=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            auto b=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            fuhaozhan.pop_back();
            Fuhao fuhao(STATEMENT);
            func1(b.duibiao,n.quad);
            
            fuhao.xiaobiao=hebing(b.cuobiao,zhuangtaiment.xiaobiao);
            fuhaozhan.push_back(fuhao);
        }},
        {ASSIGN,{ID,EQU,EXPR},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto expr=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            fuhaozhan.pop_back();
            auto id=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            Fuhao fuhao(ASSIGN);
            
            auto p=kanshang(id.mingzi);
            chansheng("=",expr.difang,"-",p);
            
            fuhaozhan.push_back(fuhao);
        }},
        {L,{L,SEMICOLON,N,STATEMENT},[&](){
            
            
            int loopsz=4;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto zhuangtaiment=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            auto n=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            auto l=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            Fuhao fuhao(L);
            func1(l.xiaobiao,n.quad);
            
            fuhao.xiaobiao=zhuangtaiment.xiaobiao;
            
            fuhaozhan.push_back(fuhao);
        }},
        {L,{STATEMENT},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto zhuangtaiment=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            Fuhao fuhao(L);
            
            fuhao.xiaobiao=zhuangtaiment.xiaobiao;
            fuhaozhan.push_back(fuhao);
        }},
        //数值表达式部分
        {EXPR,{EXPR,OR,ORITEM},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto orItem=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            fuhaozhan.pop_back();
            
            auto expr=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            Fuhao fuhao(EXPR);
            fuhao.difang=xinzhong(SYMINT);
            fuhao.leixing=SYMINT;
            
            chansheng("||",expr.difang,orItem.difang,fuhao.difang);
            fuhaozhan.push_back(fuhao);
        }},
        {EXPR,{ORITEM},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto orItem=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            Fuhao fuhao(EXPR);
            fuhao.difang=orItem.difang;
            
            fuhao.leixing=orItem.leixing;
            
            fuhaozhan.push_back(fuhao);
        }},
        {ORITEM,{ORITEM,AND,ANDITEM},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto andItem=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            fuhaozhan.pop_back();
            
            auto orItem=fuhaozhan.back();
            fuhaozhan.pop_back();
            Fuhao fuhao(ORITEM);
            
            fuhao.difang=xinzhong(SYMINT);
            
            fuhao.leixing=SYMINT;
            chansheng("&&",orItem.difang,andItem.difang,fuhao.difang);
            
            fuhaozhan.push_back(fuhao);
        }},
        {ORITEM,{ANDITEM},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto andItem=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            Fuhao fuhao(ORITEM);
            fuhao.difang=andItem.difang;
            
            fuhao.leixing=andItem.leixing;
            
            fuhaozhan.push_back(fuhao);
        }},
        {ANDITEM,{NOITEM},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto noItem=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            Fuhao fuhao(ANDITEM);
            
            fuhao.difang=noItem.difang;
            fuhao.leixing=noItem.leixing;
            
            fuhaozhan.push_back(fuhao);
        }},
        {ANDITEM,{NOT,NOITEM},[&](){
            
            
            
            int loopsz=2;
            
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto noItem=fuhaozhan.back();
            fuhaozhan.pop_back();
            fuhaozhan.pop_back();
            
            Fuhao fuhao(ANDITEM);
            
            fuhao.difang=xinzhong(SYMINT);
            fuhao.leixing=SYMINT;
            
            chansheng("!",noItem.difang,"-",fuhao.difang);
            
            fuhaozhan.push_back(fuhao);
        }},
        {NOITEM,{NOITEM,REL,RELITEM},[&](){
            
            
            
            int loopsz=3;
            
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto relItem=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            
            auto rel=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            auto noItem=fuhaozhan.back();
            fuhaozhan.pop_back();
            Fuhao fuhao(NOITEM);
            
            fuhao.difang=xinzhong(SYMINT);
            fuhao.leixing=SYMINT;
            chansheng(rel.op,noItem.difang,relItem.difang,fuhao.difang);
            
            fuhaozhan.push_back(fuhao);
        }},
        {NOITEM,{RELITEM},[&](){
            
            
            
            int loopsz=1;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto relItem=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            
            Fuhao fuhao(NOITEM);
            
            fuhao.difang=relItem.difang;
            fuhao.leixing=relItem.leixing;
            
            fuhaozhan.push_back(fuhao);
        }},
        {RELITEM,{RELITEM,PLUS_MINUS,ITEM},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto item=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            auto plusMinus=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            
            auto relItem=fuhaozhan.back();
            
            
            fuhaozhan.pop_back();
            Fuhao fuhao(RELITEM);
            
            fuhao.difang=xinzhong(relItem.leixing);
            fuhao.leixing=relItem.leixing;
            
            chansheng(plusMinus.op,relItem.difang,item.difang,fuhao.difang);
            fuhaozhan.push_back(fuhao);
            
        }},
        {RELITEM,{ITEM},[&](){
            
            
            
            int loopsz=1;
            
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            
            
            
            auto item=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            Fuhao fuhao(RELITEM);
            
            fuhao.difang=item.difang;
            fuhao.leixing=item.leixing;
            
            fuhaozhan.push_back(fuhao);
            
        }},
        {ITEM,{FACTOR},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto factor=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            Fuhao fuhao(ITEM);
            fuhao.difang=factor.difang;
            
            
            fuhao.leixing=factor.leixing;
            fuhaozhan.push_back(fuhao);
        }},
        {ITEM,{ITEM,MUL_DIV,FACTOR},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            
            auto factor=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            auto mulDiv=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            auto item=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            Fuhao fuhao(ITEM);
            fuhao.difang=xinzhong(factor.leixing);
            
            fuhao.leixing=factor.leixing;
            chansheng(mulDiv.op,item.difang,factor.difang,fuhao.difang);
            
            
            fuhaozhan.push_back(fuhao);
        }},
        {FACTOR,{ID},[&](){
            
            
            
            
            int loopsz=1;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto id=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            Fuhao fuhao(FACTOR);
            
            
            fuhao.difang=kanshang(id.mingzi);
            
            fuhao.leixing=(fuhaoTableIndex.find(id.mingzi)!=fuhaoTableIndex.end() ? fuhaoTable[fuhaoTableIndex[id.mingzi]].leixing : -1);
            
            fuhaozhan.push_back(fuhao);
        }},
        {FACTOR,{UINT},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(FACTOR);
            
            fuhao.difang=xinzhong(SYMINT);
            fuhao.leixing=SYMINT;
            
            chansheng("=",shuhebianhao.front(),"-",fuhao.difang);
            
            
            shuhebianhao.pop_front();
            
            fuhaozhan.push_back(fuhao);
        }},
        {FACTOR,{UDOUBLE},[&](){
            
            
            
            int loopsz=1;
            
            while(loopsz--){
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            
            Fuhao fuhao(FACTOR);
            
            fuhao.difang=xinzhong(SYMDOUBLE);
            
            fuhao.leixing=SYMDOUBLE;
            
            
            chansheng("=",shuhebianhao.front(),"-",fuhao.difang);
            shuhebianhao.pop_front();
            
            fuhaozhan.push_back(fuhao);
        }},
        {FACTOR,{LBRACE1,EXPR,RBRACE1},[&](){
            
            
            
            int loopsz=3;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            fuhaozhan.pop_back();
            
            auto expr=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            
            Fuhao fuhao(FACTOR);
            
            fuhao.difang=expr.difang;
            
            fuhao.leixing=expr.leixing;
            
            
            fuhaozhan.push_back(fuhao);
        }},
        {FACTOR,{PLUS_MINUS,FACTOR},[&](){
            
            
            
            
            int loopsz=2;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            
            auto factor=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            
            auto plusMinus=fuhaozhan.back();
            
            
            fuhaozhan.pop_back();
            
            
            Fuhao fuhao(FACTOR);
            fuhao.difang=xinzhong(factor.leixing);
            
            fuhao.leixing=factor.leixing;
            
            chansheng(plusMinus.op,"0",factor.difang,fuhao.difang);
            fuhaozhan.push_back(fuhao);
        }},
        //条件控制表达式
        {B,{B,OR,N,BORTERM},[&](){
            
            
            int loopsz=4;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto bOrTerm=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            
            auto n=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            auto b=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            Fuhao fuhao(B);
            func1(b.cuobiao,n.quad);
            fuhao.duibiao=hebing(b.duibiao,bOrTerm.duibiao);
            fuhao.cuobiao=bOrTerm.cuobiao;
            
            fuhaozhan.push_back(fuhao);
        }},
        {B,{BORTERM},[&](){
            
            
            int loopsz=1;
            
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            
            auto bOrTerm=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            Fuhao fuhao(B);
            fuhao.duibiao=bOrTerm.duibiao;
            fuhao.cuobiao=bOrTerm.cuobiao;
            
            fuhaozhan.push_back(fuhao);
        }},
        {BORTERM,{BORTERM,AND,N,BANDTERM},[&](){
            
            
            int loopsz=4;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            
            auto bianliang1=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            auto n=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            
            auto bOrTerm=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            Fuhao fuhao(BORTERM);
            func1(bOrTerm.duibiao,n.quad);
            
            fuhao.cuobiao=hebing(bOrTerm.cuobiao,bianliang1.cuobiao);
            fuhao.duibiao=bianliang1.duibiao;
            
            fuhaozhan.push_back(fuhao);
        }},
        {BORTERM,{BANDTERM},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            
            Fuhao fuhao(BORTERM);
            auto bianliang1=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            
            fuhao.duibiao=bianliang1.duibiao;
            
            fuhao.cuobiao=bianliang1.cuobiao;
            fuhaozhan.push_back(fuhao);
        }},
        {BANDTERM,{LBRACE1,B,RBRACE1},[&](){
            
            
            
            
            int loopsz=3;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            
            fuhaozhan.pop_back();
            
            auto b=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            Fuhao fuhao(BANDTERM);
            fuhao.duibiao=b.duibiao;
            
            fuhao.cuobiao=b.cuobiao;
            fuhaozhan.push_back(fuhao);
        }},
        {BANDTERM,{NOT,BANDTERM},[&](){
            
            
            
            int loopsz=2;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto bianliang1=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            Fuhao fuhao(BANDTERM);
            
            fuhao.duibiao=bianliang1.cuobiao;
            
            fuhao.cuobiao=bianliang1.duibiao;
            fuhaozhan.push_back(fuhao);
        }},
        {BANDTERM,{BFACTOR,REL,BFACTOR},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto bFactor2=fuhaozhan.back();
            fuhaozhan.pop_back();
            auto rel=fuhaozhan.back();
            fuhaozhan.pop_back();
            auto bFactor1=fuhaozhan.back();
            fuhaozhan.pop_back();
            Fuhao fuhao(BANDTERM);
            fuhao.duibiao=to_string(nxq);
            fuhao.cuobiao=to_string(nxq+1);
            
            chansheng("j"+rel.op,bFactor1.difang,bFactor2.difang,"0");
            
            chansheng("j","-","-","0");
            fuhaozhan.push_back(fuhao);
        }},
        {BANDTERM,{BFACTOR},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            
            auto bFactor=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            
            Fuhao fuhao(BANDTERM);
            
            fuhao.duibiao=to_string(nxq);
            fuhao.cuobiao=to_string(nxq+1);
            
            
            chansheng("jnz",bFactor.difang,"-","0");
            chansheng("j","-","-","0");
            fuhaozhan.push_back(fuhao);
        }},
        {BFACTOR,{UINT},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            
            Fuhao fuhao(BFACTOR);
            
            fuhao.difang=xinzhong(SYMINT);
            
            
            fuhao.leixing=SYMINT;
            
            chansheng("=",shuhebianhao.front(),"-",fuhao.difang);
            
            shuhebianhao.pop_front();
            
            fuhaozhan.push_back(fuhao);
        }},
        {BFACTOR,{UDOUBLE},[&](){
            
            
            
            int loopsz=1;
            while(loopsz--){
                
                fuhaozhan.pop_back();
                
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(BFACTOR);
            
            fuhao.difang=xinzhong(SYMDOUBLE);
            
            fuhao.leixing=SYMDOUBLE;
            
            
            chansheng("=",shuhebianhao.front(),"-",fuhao.difang);
            shuhebianhao.pop_front();
            fuhaozhan.push_back(fuhao);
        }},
        {BFACTOR,{ID},[&](){
            
            
            
            int loopsz=1;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto id=fuhaozhan.back();
            
            fuhaozhan.pop_back();
            Fuhao fuhao(BFACTOR);
            
            fuhao.difang=kanshang(id.mingzi);
            fuhao.leixing=(fuhaoTableIndex.find(id.mingzi)!=fuhaoTableIndex.end() ? fuhaoTable[fuhaoTableIndex[id.mingzi]].leixing : -1);
            
            fuhaozhan.push_back(fuhao);
        }},
        //运算符
        {PLUS_MINUS,{PLUS},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(PLUS_MINUS);
            
            
            
            fuhao.op="+";
            
            fuhaozhan.push_back(fuhao);
        }},
        {PLUS_MINUS,{MINUS},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                
                zhuangtaizhan.pop();
            }
            
            Fuhao fuhao(PLUS_MINUS);
            
            fuhao.op="-";
            fuhaozhan.push_back(fuhao);
        }},
        {MUL_DIV,{TIMES},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(MUL_DIV);
            
            fuhao.op="*";
            
            fuhaozhan.push_back(fuhao);
        }},
        {MUL_DIV,{DIVISION},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(MUL_DIV);
            
            fuhao.op="/";
            
            fuhaozhan.push_back(fuhao);
        }},
        {REL,{EQUEQU},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(REL);
            
            fuhao.op="==";
            
            fuhaozhan.push_back(fuhao);
        }},
        {REL,{NOTEQU},[&](){
            
            
            
            int loopsz=1;
            while(loopsz--){
                
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(REL);
            
            fuhao.op="!=";
            
            fuhaozhan.push_back(fuhao);
        }},
        {REL,{LESS},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(REL);
            
            fuhao.op="<";
            
            fuhaozhan.push_back(fuhao);
        }},
        {REL,{LE},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(REL);
            
            fuhao.op="<=";
            
            fuhaozhan.push_back(fuhao);
        }},
        {REL,{GREATER},[&](){
            int loopsz=1;
            
            
            while(loopsz--){
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(REL);
            
            fuhao.op=">";
            
            fuhaozhan.push_back(fuhao);
        }},
        {REL,{GE},[&](){
            
            
            int loopsz=1;
            while(loopsz--){
                fuhaozhan.pop_back();
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(REL);
            
            fuhao.op=">=";
            
            fuhaozhan.push_back(fuhao);
        }},
        //读写语句
        {SCANF,{SCANF_BEGIN,RBRACE1},[&](){
            
            
            
            
            int loopsz=2;
            while(loopsz--){
                fuhaozhan.pop_back();
                
                
                
                zhuangtaizhan.pop();
            }
            Fuhao fuhao(SCANF);
            
            fuhaozhan.push_back(fuhao);
        }},
        {SCANF_BEGIN,{SCANF_BEGIN,COMMA,ID},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto id=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            
            auto p=kanshang(id.mingzi);
            
            chansheng("R","-","-",p);
            
            
            Fuhao fuhao(SCANF_BEGIN);
            
            fuhaozhan.push_back(fuhao);
        }},
        {SCANF_BEGIN,{SCANFSYM,LBRACE1,ID},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            auto id=fuhaozhan.back();
            
            
            
            fuhaozhan.pop_back();
            fuhaozhan.pop_back();
            
            
            
            fuhaozhan.pop_back();
            auto p=kanshang(id.mingzi);
            
            
            chansheng("R","-","-",p);
            
            Fuhao fuhao(SCANF_BEGIN);
            fuhaozhan.push_back(fuhao);
            
        }},
        {PRINTF,{PRINTF_BEGIN,RBRACE1},[&](){
            
            
            int loopsz=2;
            
            while(loopsz--){
                fuhaozhan.pop_back();
                
                zhuangtaizhan.pop();
            }
            
            Fuhao fuhao(PRINTF);
            fuhaozhan.push_back(fuhao);
        }},
        {PRINTF_BEGIN,{PRINTFSYM,LBRACE1,ID},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                zhuangtaizhan.pop();
            }
            
            auto id=fuhaozhan.back();
            fuhaozhan.pop_back();
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            auto p=kanshang(id.mingzi);
            
            chansheng("W","-","-",p);
            
            Fuhao fuhao(PRINTF_BEGIN);
            
            fuhaozhan.push_back(fuhao);
        }},
        {PRINTF_BEGIN,{PRINTF_BEGIN,COMMA,ID},[&](){
            
            
            int loopsz=3;
            while(loopsz--){
                
                zhuangtaizhan.pop();
            }
            auto id=fuhaozhan.back();
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            
            fuhaozhan.pop_back();
            
            auto p=kanshang(id.mingzi);
            
            chansheng("W","-","-",p);
            Fuhao fuhao(PRINTF_BEGIN);
            
            fuhaozhan.push_back(fuhao);
        }},
        
    };

    for(auto i=0;i<grammar.size();i++){
        l2r[grammar[i].left].push_back(i);
    }
    huodediyige();
    // huodexiayige();
    getC();
    Huodebiao();
}