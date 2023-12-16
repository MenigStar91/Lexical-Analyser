#include<bits/stdc++.h>
#include<string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "def.h"
using namespace std;

unordered_map <string,int> keywords;
unordered_map <string,int> encKeysIds;
fstream symout;
fstream fout;

int lines=1;


bool isLet(char c)
{
    return ((65<=c && c<=90) || (97<=c && c<=122));
}

bool isDig(char c)
{
    return (48<=c && c<=57);
}

bool isId(string &s)
{
    if(s.size()>1 && s[0]==95 && s[1]==95) return false;
    if(s[0]!=95 && !isLet(s[0])) return false;
    int ind=1;
    while(ind<s.size())
    {
        if(isLet(s[ind]) || isDig(s[ind]) || s[ind]==95) ind++;
        else return false;
    }
    return true;
}

bool isArOp(string s)
{
    if(s=="+")
    {
        if(fout.is_open())
        {
            fout<<PLUS<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="-")
    {
        if(fout.is_open())
        {
            fout<<MINUS<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="*")
    {
        if(fout.is_open())
        {
            fout<<MULT<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="/")
    {
        if(fout.is_open())
        {
            fout<<DIV<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="%")
    {
        if(fout.is_open())
        {
            fout<<PERCENT<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="++")
    {
        if(fout.is_open())
        {
            fout<<PLUS_PLUS<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="--")
    {
        if(fout.is_open())
        {
            fout<<MINUS_MINUS<<"\n";
            lines+=1;
        }
        return true;
    }
    return false;
}

bool isAsOp(string s)
{
    if(s=="=")
    {
        if(fout.is_open())
        {
            fout<<EQ<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="+=")
    {
        if(fout.is_open())
        {
            fout<<PLUS_EQ<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="-=")
    {
        if(fout.is_open())
        {
            fout<<MINUS_EQ<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="*=")
    {
        if(fout.is_open())
        {
            fout<<MULT_EQ<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="/=")
    {
        if(fout.is_open())
        {
            fout<<DIV_EQ<<"\n";
            lines+=1;
        }
        return true;
    }
    return false;
}

bool isReOp(string s)
{
    if(s=="<")
    {
        if(fout.is_open())
        {
            fout<<LESSER<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s==">")
    {
        if(fout.is_open())
        {
            fout<<GREATER<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="<=")
    {
        if(fout.is_open())
        {
            fout<<LESS_EQ<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s==">=")
    {
        if(fout.is_open())
        {
            fout<<GREAT_EQ<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=="==")
    {
        if(fout.is_open())
        {
            fout<<EQ_EQ<<"\n";
            lines+=1;
        }
        return true;
    }
    return false;
}

bool isSpSym(char s)
{
    if(s=='(')
    {
        if(fout.is_open())
        {
            fout<<L_PARAEN<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s==')')
    {
        if(fout.is_open())
        {
            fout<<R_PARAEN<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s==',')
    {
        if(fout.is_open())
        {
            fout<<COMMA<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=='[')
    {
        if(fout.is_open())
        {
            fout<<L_SQUARE<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s==']')
    {
        if(fout.is_open())
        {
            fout<<R_SQUARE<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=='{')
    {
        if(fout.is_open())
        {
            fout<<L_CBRACE<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s=='}')
    {
        if(fout.is_open())
        {
            fout<<R_CBRACE<<"\n";
            lines+=1;
        }
        return true;
    }
    if(s==';')
    {
        if(fout.is_open())
        {
            fout<<SEMICOL<<"\n";
            lines+=1;
        }
        return true;
    } 
    return false;
}

void FSM(string &content)
{
    string tmpcontent;
    tmpcontent=content;
    int ind=0;
    while(ind<content.length())
    {
        if(content[ind]==32) ind++;
        else if(isSpSym(content[ind]))
        {
            ind++;
        }
        else if(content[ind]<48 || (57<content[ind] && content[ind]<65) || (90<content[ind] && content[ind]<97) || 122<content[ind])
        {
            string tmp;
            if(content[ind+1]!=32 && (content[ind+1]<48 || (57<content[ind+1] && content[ind+1]<65) || (90<content[ind+1] && content[ind+1]<97) || 122<content[ind+1]))
            {
                tmp+=content[ind];
                tmp+=content[ind+1];
                ind+=2;
            }
            else
            {
                tmp+=content[ind];
                ind++;
            }
            if(isArOp(tmp))
            {
                continue;
            }
            else if(isAsOp(tmp))
            {
                continue;
            }
            else if(isReOp(tmp))
            {
                continue;
            }
            else if(isDig(content[ind-1]))
            {
                ind--;
                string num;
                int decimal=0;
                while(isDig(content[ind]) || content[ind]==46)
                {
                    if(content[ind]==46) decimal++;
                    num+=content[ind++];
                }
                if(symout.is_open() && encKeysIds.find(num)==encKeysIds.end())
                {
                    symout<<num<<" 1\n";
                    encKeysIds[num]++;
                }
                if(decimal==0)
                {
                    if(fout.is_open())
                    {
                        fout<<INT_CONST<<" "<<num<<"\n";
                        lines+=1;
                    }
                }
                else if(decimal==1)
                {
                    if(fout.is_open())
                    {
                        fout<<FLO_CONST<<" "<<num<<"\n";
                        lines+=1;
                    }
                }
            }
        }
        else
        {
            string tmp;
            while(keywords.find(tmp)==keywords.end() && content[ind]!=32 && !isSpSym(content[ind]) && !isArOp(tmp) && !isAsOp(tmp) && !isReOp(tmp) && content[ind+1]!='(')
            {
                tmp+=content[ind++];
            }   
            if(content[ind+1]=='(') tmp+=content[ind++];
            if(keywords.find(tmp)!=keywords.end())
            {
                if(fout.is_open() && tmp=="short")
                {
                    fout<<SHORT<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="int")
                {
                    fout<<INT<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="float")
                {
                    fout<<FLOAT<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="double")
                {
                    fout<<DOUBLE<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="bool")
                {
                    fout<<BOOL<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="char")
                {
                    fout<<CHAR<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="signed")
                {
                    fout<<SIGNED<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="unsigned")
                {
                    fout<<UNSIGNED<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="for")
                {
                    fout<<FOR<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="while")
                {
                    fout<<WHILE<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="do")
                {
                    fout<<DO<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="return")
                {
                    fout<<RETURN<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="void")
                {
                    fout<<VOID<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="switch")
                {
                    fout<<SWITCH<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="break")
                {
                    fout<<BREAK<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="case")
                {
                    fout<<CASE<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="continue")
                {
                    fout<<CONTINUE<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="goto")
                {
                    fout<<GOTO<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="long")
                {
                    fout<<LONG<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="static")
                {
                    fout<<STATIC<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="union")
                {
                    fout<<UNION<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(fout.is_open() && tmp=="default")
                {
                    fout<<DEFAULT<<" "<<tmp<<"\n";
                    lines+=1;
                }
                if(symout.is_open() && encKeysIds.find(tmp)==encKeysIds.end())
                {
                    symout<<tmp<<" 0\n";
                    encKeysIds[tmp]++;
                }
            }
            else if(isId(tmp))
            {
                if(symout.is_open() && encKeysIds.find(tmp)==encKeysIds.end())
                {
                    symout<<tmp<<" 1\n";
                    encKeysIds[tmp]++;
                }
                if(fout.is_open())
                {
                    fout<<IDNTIFIER<<" "<<tmp<<"\n";
                    lines+=1;
                }
            }
            else if(isArOp(tmp))
            {
                continue;
            }
            else if(isAsOp(tmp))
            {
                continue;
            }
            else if(isReOp(tmp))
            {
                continue;
            }
            else if(isDig(content[ind-1]))
            {
                ind--;
                string num;
                int decimal=0;
                while(isDig(content[ind]) || content[ind]==46)
                {
                    if(content[ind]==46) decimal++;
                    num+=content[ind++];
                }
                if(symout.is_open() && encKeysIds.find(num)==encKeysIds.end())
                {
                    symout<<num<<" 1\n";
                    encKeysIds[num]++;
                }
                if(decimal==0)
                {
                    if(fout.is_open())
                    {
                        fout<<INT_CONST<<" "<<num<<"\n";
                        lines+=1;
                    }         
                }
                else if(decimal==1)
                {
                    if(fout.is_open())
                    {
                        fout<<FLO_CONST<<" "<<num<<"\n";
                        lines+=1;
                    }
                }
            }
        }
    }
}

void readFileIntoString(const string& path, string *res) {
    fstream file;
    file.open(path,ios::in);
    if(file.is_open())
    {
        string tmp;
        while(getline(file,tmp))
        {
            (*res)+=tmp;
        }
        file.close();
    }
    cout<<res<<endl;
}


int main(int argc, char **argv)
{
    keywords["short"]++;
    keywords["int"]++;
    keywords["float"]++;
    keywords["double"]++;
    keywords["bool"]++;
    keywords["char"]++;
    keywords["signed"]++;
    keywords["unsigned"]++;
    keywords["for"]++;
    keywords["while"]++;
    keywords["do"]++;
    keywords["return"]++;
    keywords["void"]++;
    keywords["switch"]++;
    keywords["break"]++;
    keywords["case"]++;
    keywords["continue"]++;
    keywords["goto"]++;
    keywords["long"]++;
    keywords["static"]++;
    keywords["union"]++;
    keywords["default"]++;

    // argv[1] is input file
    string content;
    fstream file;
    symout.open("symbol_table_1.out",ios::out);
    fout.open("pa_1.out",ios::out);
    file.open(argv[1],ios::in);
    if(file.is_open())
    {
        string tmp;
        while(getline(file,tmp))
        {
            content+=tmp;
        }
        file.close();
    }
    FSM(content);
    symout.close();
    fout.close();
    return 0;
}