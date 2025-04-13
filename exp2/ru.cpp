#include "jiexiqi.h"
using namespace std;

void Jiexiqi::huodediyige()
{

    for (auto leixing : allTypes)
    {
        if (endsymbosSet.find(leixing) != endsymbosSet.end())
        {
            first[leixing].insert(leixing);
        }
        else{
            first[leixing]=set<Type>();
        }
    }
    while (true)
    {
        bool isChanged = false;
        for (auto &expression : grammar)
        {
            set<Type> jieguo = huodediyigeForCandidate(expression.right);
            if (first[expression.left].size() == 0&&jieguo.size()!=0)
            {
                first[expression.left] = jieguo;
                isChanged = true;
            }
            else
            {
                for (auto &leixing : jieguo)
                {
                    auto res=first[expression.left].insert(leixing);
    
                    if(res.second){
    
                        isChanged = true;
                    }
                }
            }
        }
        if (!isChanged)
        {
    
            break;
        }
    }
}

void Jiexiqi::huodexiayige()
{
    
    
    
    for(auto leixing:allTypes){
        if(endsymbosSet.find(leixing) == endsymbosSet.end()){
    
    
            follow[leixing]=set<Type>();
    
        }
    
    }
    follow[START]={END};
    
    
    for(auto &expression:grammar){
        int k=expression.right.size()-1;
    
        for(int i=0;i<k-1;i++){
    
            if(endsymbosSet.find(expression.right[i]) == endsymbosSet.end()){
    
                set<Type> jieguo = huodediyigeForCandidate(vector<Type>(expression.right.begin()+i+1,expression.right.end()));
    
                jieguo.erase(ONE);
    
                if(jieguo.size()!=0){
    
                    follow[expression.right[i]].insert(jieguo.begin(),jieguo.end());
                }
            }
        }
    
    }
    
    bool isChanged=true;
    
    while(isChanged){
    
        isChanged=false;
    
    
        for(auto &expression:grammar){
    
    
    
            int k=expression.right.size()-1;
            if(endsymbosSet.find(expression.right[k]) == endsymbosSet.end()){
    
                for(auto &leixing:follow[expression.left]){
    
    
                    auto res=follow[expression.right[k]].insert(leixing);
                    if(res.second){
                        isChanged=true;
                    }
                }
            }
            else{
    
    
    
    
                continue;
            }
            for(int i=k-1;i>=0;i--){
    
    
    
                if(endsymbosSet.find(expression.right[i]) == endsymbosSet.end()&&first[expression.right[i+1]].find(ONE)!=first[expression.right[i+1]].end()){
    
    
    
                    for(auto &leixing:follow[expression.left]){
    
    
                        auto res=follow[expression.right[i]].insert(leixing);
                        if(res.second){
    
    
    
                            isChanged=true;
                        }
                    }
                }
                else{
                    break;
                }
            }
        }
    }
}

set<Type> Jiexiqi::huodediyigeForCandidate(vector<Type> candidate)
{
    
    
    

     
    set<Type> jieguo;
    if ((candidate.size() == 1 )&& (candidate[0]==ONE))
    {
     
        jieguo.insert(ONE);
        return jieguo;
    }
    jieguo = first[candidate[0]];
     
    jieguo.erase(ONE);
     
    bool isEmpty = true;
    for (int i = 1; i < (int)candidate.size(); i++)
    {
        if (first[candidate[i - 1]].find(ONE) != first[candidate[i - 1]].end())
        {
     

            jieguo.insert(first[candidate[i]].begin(), first[candidate[i]].end());
     
            jieguo.erase(ONE);
        }
        else
        {
     
            isEmpty = false;
            break;
        }
    }
    if (isEmpty && first[candidate[candidate.size() - 1]].find(ONE) != first[candidate[candidate.size() - 1]].end())
    {
     
        jieguo.insert(ONE);
    }
    return jieguo;
}

set<Bixiang> Jiexiqi::Bibao(Bixiang sourceItem)
{
    
    
    
    set<Bixiang> jieguo;
     
    queue<Bixiang> q;
    q.push(sourceItem);
    jieguo.insert(sourceItem);
     
    while(!q.empty()){
        Bixiang item=q.front();
        q.pop();
     
        // jieguo.insert(item);
        if(item.dot<grammar[item.expressionIndex].right.size()){
            Type nextType=grammar[item.expressionIndex].right[item.dot];
            if(endsymbosSet.find(nextType) == endsymbosSet.end()){
     
                for(auto &exprIt:l2r[nextType]){
                    auto expressionIndex=exprIt;
     
                    Bixiang newItem={expressionIndex,0,{}};
     
                    if(item.dot==grammar[item.expressionIndex].right.size()-1){
     
                        newItem.lookAhead.insert(item.lookAhead.begin(),item.lookAhead.end());
                    }
                    else{
                        set<Type> firstSet=first[grammar[item.expressionIndex].right[item.dot+1]];
     
                        newItem.lookAhead.insert(firstSet.begin(),firstSet.end());
                    }
     
                    auto res=jieguo.insert(newItem);
                    if(res.second){
     
                        q.push(newItem);
                    }
                    else if(!res.second){
     
                        if(res.first->lookAhead!=newItem.lookAhead){
                            auto temp=*res.first;
     
                            jieguo.erase(res.first);
     
                            bool changed=false;
                            for(auto &leixing:newItem.lookAhead){
     
                                auto res2=temp.lookAhead.insert(leixing);
                                if(res2.second){
                                    changed=true;
     
                                }
                            }
                            if(changed){
                                jieguo.insert(temp);
     
                                q.push(temp);
     
                            }
                            else{
     
                                jieguo.insert(temp);
                            }
                        }
                    }
     
                }
     
            }
     
        }
    }
    return jieguo;
}

set<Bixiang> Jiexiqi::Xiayige(set<Bixiang> i,Type a)
{
    
    
    
    set<Bixiang> jieguo;
     
    for(auto &item:i){
     
        if(item.dot<grammar[item.expressionIndex].right.size()&&grammar[item.expressionIndex].right[item.dot]==a){
            Bixiang newItem={item.expressionIndex,item.dot+1,item.lookAhead};
     
            set<Bixiang> closure=Bibao(newItem);
            jieguo.insert(closure.begin(),closure.end());
        }
    }
    return jieguo;
}

void Jiexiqi::getC()
{
    
    
    
    int zhuangtai=0;
     
    Bixiang startItem={(l2r[START].begin())[0],0,{END}};
    set<Bixiang> I0=Bibao(startItem);
    C.insert({I0,zhuangtai});
     
    int2I[zhuangtai]=C.begin()->first;
     
    zhuangtai++;
     
    zhuangtaizhan.push(C.begin()->second);
     
    list<set<pair<set<Bixiang>,int>>::iterator> closureQueue;
     
    closureQueue.push_back(C.begin());
    while(!closureQueue.empty()){
        auto cur=closureQueue.front();
     
        auto i=cur->first;
        auto curZhuangtai=cur->second;
        closureQueue.pop_front();
     
        for(auto &item:i){
            if(item.dot<grammar[item.expressionIndex].right.size()){
     
                Type a=grammar[item.expressionIndex].right[item.dot];
                set<Bixiang> newI=Xiayige(i,a);
     
                auto res=C.insert({newI,zhuangtai});
                if(res.second){
     
                    ZhuangtaizhuanyiSet.insert({curZhuangtai,a,zhuangtai});
                    //cout<<"Zhuangtaizhuanyi "<<curZhuangtai<<" "<<a<<" "<<zhuangtai<<endl;
     
                    int2I[zhuangtai]=res.first->first;
                    zhuangtai++;
                    closureQueue.push_back(res.first);
                }
                else{
                    auto temp=*res.first;
                    auto tempI=temp.first;
     
                    bool outChanged=false;
     
                    for(auto &closureIt:newI){//对于新的I中的每一个项目
                        auto res2=tempI.find(closureIt);//在已有的I中查找是否有相同的项目
                        if(res2!=tempI.end()){//如果有
     
                            bool changed=false;
     
                            auto tempItem=*res2;
     
                            for(auto &leixing:closureIt.lookAhead){
                                auto res3=tempItem.lookAhead.insert(leixing);
                                if(res3.second){
     
                                    changed=true;
                                    outChanged=true;
                                }
                            }
                            if(changed){
                                tempI.erase(res2);
                                tempI.insert(tempItem);
     
                            }
                        }
     
                    }
     
                    temp.first=tempI;
                    if(outChanged){
                        C.erase(res.first);
     
                        auto delIt=find(closureQueue.begin(),closureQueue.end(),res.first);
                        if(delIt!=closureQueue.end()){
     
                            closureQueue.erase(delIt);
                        }
                        C.insert(temp);
                        closureQueue.push_back(C.find(temp));
                    }
                    ZhuangtaizhuanyiSet.insert({curZhuangtai,a,temp.second});
                    //cout<<"Zhuangtaizhuanyi "<<curZhuangtai<<" "<<a<<" "<<res.first->second<<endl;
                }
     
            }
     
        }
    }
}

void Jiexiqi::Huodebiao()
{
    
    
    
    for(auto &trans:ZhuangtaizhuanyiSet){
     
        if(endsymbosSet.find(trans.go) != endsymbosSet.end()){
            analyticalTable[trans.oldZhuangtai][trans.go]=[&](){
     
                Fuhao fuhao(shuru.front());
     
                shuru.pop_front();
     
                fuhaozhan.push_back(fuhao);
                zhuangtaizhan.push(trans.newZhuangtai);
            };
        }
        else{
     
            analyticalTable[trans.oldZhuangtai][trans.go]=[&](){
                zhuangtaizhan.push(trans.newZhuangtai);
            };
     
        }
    }
    for(auto i=C.begin();i!=C.end();i++){
     
        for(auto &item:i->first){
            if(item.dot==grammar[item.expressionIndex].right.size()){
     
                if(grammar[item.expressionIndex].left==START){
                    analyticalTable[i->second][END]=[&](){
     
                        shuru.pop_front();
                    };
     
                }
                else{
                    for(auto &leixing:item.lookAhead){
                        analyticalTable[i->second][leixing]=[&](){
                            grammar[item.expressionIndex].action();
     
                            auto action=analyticalTable[zhuangtaizhan.top()][grammar[item.expressionIndex].left];
                            if(action){
     
                                action();
                            }
                            else{
     
                                abort();
                            }
                        };
                    }
     
                }
            }
     
        }
    }
    
}

void Jiexiqi::func1(string p,string t)
{
    
    
    
    string q;
    while(p!="null"&&p!="0"){
        q=SiyuansshiTable[stoi(p)].jieguo;
     
     
        SiyuansshiTable[stoi(p)].jieguo=t;
     
        p=q;
    }
}

string Jiexiqi::hebing(string p1,string p2)
{
    
    
    
    if(p1=="null"){
     
        return p2;
    }
    if(p2=="null"){
     
        return p1;
     
    }
    string p=p2;
     
    while(SiyuansshiTable[stoi(p)].jieguo!="null"&&SiyuansshiTable[stoi(p)].jieguo!="0"){
        p=SiyuansshiTable[stoi(p)].jieguo;
    }
     
    SiyuansshiTable[stoi(p)].jieguo=p1;
    return p2;
}

void Jiexiqi::chansheng(string op,string lczs,string rczs,string jieguo)
{
    
    
    
    if((int)SiyuansshiTable.size()<nxq+1){
     
        SiyuansshiTable.push_back(Siyuansshi(op,lczs,rczs,jieguo));
     
    }
    else{
     
        SiyuansshiTable[nxq]=Siyuansshi(op,lczs,rczs,jieguo);
     
    }
    nxq++;
}

void Jiexiqi::jinru(string mingzi,int leixing,int pianyiliang)
{
    
    
    
    if(fuhaoTableIndex.find(mingzi)!=fuhaoTableIndex.end()){
        cout<<"Syntax Error"<<endl;
     
        exit(0);
    }
    Fuhaobiaoxiang item(mingzi,leixing,"null",pianyiliang);
     
    fuhaoTable.push_back(item);
     
    fuhaoTableIndex[mingzi]=fuhaoTable.size()-1;
}

string Jiexiqi::xinzhong(int leixing)
{
    
    
    
    
    string mingzi="T"+to_string(tempIndex++);
     
    if(leixing==SYMINT){
    
     
        mingzi+="_i";
    }
    else if(leixing==SYMDOUBLE){
     
    
        mingzi+="_d";
    }
    
    return mingzi;
}

string Jiexiqi::kanshang(string mingzi)
{
    
    
    
    if(fuhaoTableIndex.find(mingzi)!=fuhaoTableIndex.end()){
    
        return "TB"+to_string(fuhaoTableIndex[mingzi]);
    
    }
    
    cout<<"Syntax Error"<<endl;
    
    exit(0);
    return "Syntax Error";
}

void Jiexiqi::shuchu()
{
    
    
    
    
    cout<<fuhaoTable.size()<<endl;
    for(auto &item:fuhaoTable){
    
        cout<<item.mingzi<<" "<<item.leixing<<" "<<item.value<<" "<<item.pianyiliang<<endl;
    }
    cout<<tempIndex<<endl;
    
    cout<<SiyuansshiTable.size()<<endl;
    for(size_t i=0;i<SiyuansshiTable.size();i++){
    
        cout<<i<<": ("<<SiyuansshiTable[i].op<<","<<SiyuansshiTable[i].lczs<<","<<SiyuansshiTable[i].rczs<<","<<SiyuansshiTable[i].jieguo<<")"<<endl;
    }
}

void Jiexiqi::yunxing(list<Type> oshuru)
{
    
    
    
    
    this->shuru = oshuru;
    
    this->shuru.push_back(END);
    while (!shuru.empty())
    {
        
        auto zhuangtai = zhuangtaizhan.top();
        
        auto fuhao = shuru.front();
        auto action = analyticalTable[zhuangtai][fuhao];
        if (action)
        {
            
            action();
        }
        else if(fuhao!=ONE){
            
            fuhao=ONE;
    
            action=analyticalTable[zhuangtai][fuhao];
            if(action){
    
                action();
            }
            else{
                cout<<"Syntax Error"<<endl;
    
                exit(0);
                break;
            }
        }
        else
        {
    
            cout << "Syntax Error" << endl;
    
            exit(0);
            break;
        }
    }
}