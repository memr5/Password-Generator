#include<bits/stdc++.h>

using namespace std;

class Password_Generator{
    int length;

    public:

    Password_Generator(int l){
        length=l;
    }

    void get_password();
};

void Password_Generator:: get_password(){


    //Generating current Time
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti = localtime(&tt);

    int x;
    int n,lo,u,s;
    int minn=0,mins=0;
    //MENU
    cout<<"\nChoose one from these two:\n";
    cout<<"Enter 1: Strong Password\n";
    cout<<"Enter 2: Random Password\n";
    cout<<"Enter choice: ";
    cin>>x;
    //WARNING MESSAGE
    if(x==1 && length<8){
        cout<<"\n******WARNING******";
        cout<<"\nLength choosen is for weak password!\nDo you want to change it? (y or n) : ";
        char c;
        cin>>c;
        if(c=='y' || c=='Y'){
            cout<<"Enter new Length : ";
            cin>>length;
        }
    }
    //To Store Newly Created Password
    char pass[length+1];
    pass[length]='\0';
    //Number of Different types of characters to include in Strong Password according to its Length
    n=max(length/8,1); //Number of Numbers :)
    s=max(length/8,1); //Number of Special Characters
    int ud = rand()%2 + 1; 
    ud*=2;
    int ld;
    if(ud==4){
        ld=2;
    }
    else{
        ld=4;
    }
    u=length/ud; //Number of Uppercase Letters
    lo=length/ld; //Number of Lowercase Letters

    string numbers = "1234567890";
    string lower = "qwertyuioplkjhgfdsazxcvbnm";
    string upper = "MNBVCXZPOIUYTREWQASDFGHJKL";
    string special = "!@#$%&?.,)(";
    string mix1 = "QAZxswEDCvfrTGBnhyUJMkiOLpzaqWSXcdeRFVbgtYHNmjuIKloP";
    string mix2 = "1@!9#2$8%(?4)7,5&3.60";

    if(x==1){
        set<char> repeated; //To keep Track on repeated Characters. If found then change it to randomly anything
        int last; //To keep track on last type of character
        int first=rand()%4;
        last=first;
        if(first==0){
            pass[0]=lower[rand()%26];
            --lo;
        }
        else if(first==1){
            pass[0]=upper[rand()%26];
            --u;
        }
        else if(first==2){
            pass[0]=numbers[rand()%10];
            minn=1;
            --n;
        }
        else{
            pass[0]=special[rand()%11];
            mins=1;
            --s;
        }

        repeated.insert(pass[0]);

        for(int i=1;i<length;i++){
            int next=rand()%3;
            pair<set<char>::iterator,bool> result; //To check if "to be added" character is already in Password or not
            if(lo>0 && last!=0 && next==1){
                pass[i]=lower[rand()%26];
                result = repeated.insert(pass[i]);
                while(!result.second){
                    pass[i]=lower[rand()%26];
                    result = repeated.insert(pass[i]);
                }
                --lo;
                last=0;
            }
            else if(s>0 && last!=3 && next==2){
                pass[i]=special[rand()%11];
                result = repeated.insert(pass[i]);
                while(!result.second){
                    pass[i]=special[rand()%11];
                    result = repeated.insert(pass[i]);
                }
                mins=1;
                --s;
                last=3;
            }
            else if(u>0 && last!=1 && next==2){
                pass[i]=upper[rand()%26];
                result = repeated.insert(pass[i]);
                while(!result.second){
                    pass[i]=upper[rand()%26];
                    result = repeated.insert(pass[i]);
                }
                --u;
                last=1;
            }
            else if(n>0 && last!=2 && next==3){
                pass[i]=numbers[rand()%10];
                result = repeated.insert(pass[i]);
                while(!result.second){
                    pass[i]=upper[rand()%10];
                    result = repeated.insert(pass[i]);
                }
                minn=1;
                --n;
                last=2;
            }
            else{
                if(last!=0 && last!=1){
                    pass[i]=mix1[rand()%52];
                    result = repeated.insert(pass[i]);
                    while(!result.second){
                        pass[i]=mix1[rand()%52];
                        result = repeated.insert(pass[i]);
                    }
                    if(pass[i]>96){
                        --lo;
                        last=0;
                    }
                    else{
                        --u;
                        last=1;
                    }
                }
                else{
                    pass[i]=mix2[rand()%21];
                    result = repeated.insert(pass[i]);
                    while(!result.second){
                        pass[i]=mix2[rand()%21];
                        result = repeated.insert(pass[i]);
                    }
                    if(pass[i]>=48 && pass[i]<=57){
                        --n;
                        minn=1;
                        last=2;
                    }
                    else{
                        mins=1;
                        --s;
                        last=3;
                    }
                }
            }
        }
        //To Satisfy Minimum Requirements
        int fin;
        if(!minn){
            fin = rand()%length;
            pass[fin]=numbers[rand()%10];
        }
        if(!mins){
            int i;
            do{
                i =rand()%length;
            }while(i==fin);
            pass[i]=special[rand()%11];
        }
        //Writes Newly Created Passwords to a file for Future Analysis
        ofstream passfile;
        passfile.open("pass.txt",ios::app);
        passfile<<"Strong : "<<pass<<" | Length : "<<length<<" | Day And Time: "<<asctime(ti)<<endl;
        passfile.close();
    }
    else{

        for(int i=0;i<length;i++){
            int w;
            do{
                w=rand()%127;
            }while(w<33);
            pass[i]=(char)w;
        }
        ofstream passfile;
        passfile.open("pass.txt",ios::app);
        passfile<<"Random : "<<pass<<" | Length : "<<length<<" | Day And Time: "<<asctime(ti)<<endl;
        passfile.close();
    }
    cout<<"\nPassword : "<<pass<<endl;
}


int main(){
    srand(time(NULL));
    int len;
    cout<<"<<<<<<<PASSWORD-GENERATOR>>>>>>>"<<endl;
    cout<<"Enter Length: ";
    cin>>len;

    Password_Generator p(len);
    p.get_password();

return 0;
}

