#include<bits/stdc++.h>
using namespace std;
class node{
    public:
        struct user
        {
            char u[21],p[9];  //hold username and password.
        }us;
        node* next;
};

void sign_up(node* &);  //USER CAN CREATE A NEW USERNAME AND PASSWORD HERE.
void log_in(node* &);   //USER CAN CHECK HIS/HER EXISTING DATA.
int server(node* &,node*); //MAIN SERVER WHICH PROVIDES MULTIPLE FUNCTIONALITY.
int validate(char*,node* );  //CHECK WHETHER THE NEW USERNAME ALREADY EXISTS.
char encrypt(char);           //ENCRYPTS THE PASSWORD PROVIDED BY THE USER AND STORE IT IN THE DATABASE.
void delete_node(node* &,char *);  //DELETES THE USER DATA BASED ON USER'S OR ADMIN'S REQUEST.
void admin(node* &,char*,char*);  //ADMIN FUNCTIONALITIES ARE PROVIDED HERE.

int main()
{
    node* head=NULL;
    int c;
    char admin_name[]={"Sumit"};
    char admin_password[]={"179300"};
    cout<<"Welcome....\n";
    cout<<"\n";
    while(1)
    {
        cout<<"Enter your Choice..\n";
        cout<<"\n";
        cout<<"1.Admin\t 2.Sign UP\t3.Log In\t4.Exit\n";
        cout<<"\n";
        cin>>c;
        switch(c)
        {
            case 1:admin(head,admin_name,admin_password);
                    break;
            case 2:sign_up(head);
                    break;
            case 3:log_in(head);        
                    break;
            default:cout<<"Closing DataBase..\n";
                    return 0;        
        }
    }
}

//admin begins

void delete_node(node* &h,char *s)
{
    node* t=h,*p=NULL;
    while(1)
    {
        if(strcmp((t->us).u,s)==0)
        {
            break;
        }
        p=t;
        t=t->next;
    }
    if(p==NULL)
    {
        h=h->next;
        cout<<"Operation under process \n Deleted successfully..\n";
        delete t;
        return;
    }
    p->next=t->next;
    cout<<"Operation under process \n Deleted successfully..\n";
    delete t;
}

void admin(node* &h,char* name,char* password)
{
    char s[21],p[8];
    cout<<"Admin_Name-- ";
    cin>>s;
    cout<<"Admin_Password-- ";
    cin>>p;
    node* x=h;
    if(strcmp(name,s)==0 && strcmp(password,p)==0)
    {
        cout<<"Welcome Admin..How may I help you\n";
        cout<<"\n";
        int c;
        while(1)
        {
            cout<<"Enter your choice\n";
            cout<<"\n";
            cout<<"1.Delete_User\t2.Display_Data\t3.Change_Admin_Name\t4.Change_Admin_Pasword\t5.Exit\n";
            cout<<"\n";
            cin>>c;
            switch(c)
            {
                case 1:char user[21];
                    cout<<"Enter the user_name\n";
                    cin>>user;
                    delete_node(h,user);
                    break;
                case 2:cout<<"Displaying the Database....\n";
                        //node* x=h;
                        cout<<"\n";
                        if(x==NULL)
                        {
                            cout<<"Empty DataBase\n";
                            cout<<"\n";
                            break;
                        }
                        while(x!=NULL)
                        {
                            cout<<"User_name-- "<<(x->us).u<<endl<<"Password-- "<<(x->us).p<<endl;
                            cout<<"\n";
                            x=x->next;
                        }    
                        break;
                case 3:char admin_new[21];
                        cout<<"Admin_Name-- ";
                        cin>>admin_new;
                        strcpy(name,admin_new);
                        cout<<"Admin_Name updated Successfully...\n";
                        cout<<"\n";
                        break;
                case 4:char admin_newp[9];
                        cout<<"Admin_Password-- ";
                        cin>>admin_newp;
                        strcpy(password,admin_newp);
                        cout<<"Admin_Password updated Successfully...\n";
                        cout<<"\n";
                        break;     
                default:cout<<"Redirecting to the main menu....\n";
                cout<<"\n";
                        return;                   
            }
        }
    }
}

//admin end

//sign_up begin

int validate(char* s,node* h)
{
    node *t=h;
    char n[21];
    while(t!=NULL)
    {
        strcpy(n,(t->us).u);
        if(strcmp(n,s)==0)
        {
            return 0;
        }
        t=t->next;
    }
    return 1;
}

void sign_up(node* &h)
{
    cout<<"Welcome to our DataBase..\n";
    cout<<"\n";
    node* t=new node();
    string pass;
    int i=1;
    while(i)
    {
        cout<<"Username-- ";
        cin>>(t->us).u;
        cout<<"Password-- ";
        cin>>pass;
        t->next=NULL;
        int x=validate((t->us).u,h);
        if(x==0)
        {
            cout<<"User Already Exists...Try again\n";
            cout<<"\n";
            delete t;
            node* t=new node();
        }
        else{
            for(int i=0;pass[i]!='\0';i++)
            {
                char q=pass[i];
                (t->us).p[i]=encrypt(q);
            }
            i=0;
        }
    }
    cout<<"Successfully Registered\n";
    cout<<"\n";
    if(h==NULL)
    {
        h=t;
    }
    else{
        t->next=h;
        h=t;
    }
}

//sign up end

//login begin
void log_in(node* &h)
{
    if(h==NULL)
    {
        cout<<"Empty Database..\n";
        cout<<"\n";
        return;
    }
    cout<<"Welcome Back...\n";
    cout<<"\n";
    node* t=new node();
    string pass;
    while(1)
    {
        cout<<"UserName-- ";
        cin>>(t->us).u;
        cout<<"Password-- ";
        cin>>pass;
        for(int i=0;pass[i]!='\0';i++)
            {
                char q=pass[i];
                (t->us).p[i]=encrypt(q);
            }
        if(server(h,t)==1)
        {
            return;
        }
        else if(server(h,t)==0){
            cout<<"Invalid Credentail..Try again..\n";
            cout<<"\n";
        }
    }
}

int server(node* &h, node* s)
{
    node* t=h,*p=NULL;
    while(t!=NULL)
    {
        if(strcmp((t->us).u,(s->us).u)==0 && strcmp((t->us).p,(s->us).p)==0 ){
            cout<<"Access Granted..\n";
            cout<<"\n";
            int c;
            cout<<"1.Change username\t2.Change Password\t3.Delete\t4.Exit\n";
            cout<<"\n";
            cin>>c;
            switch (c)
            {
                case 1:char s[21];
                        while(1)
                        {
                            cout<<"New Username-- ";
                            cin>>s;
                            int x=validate(s,h);
                            if(x==1)
                            {
                                strcpy((t->us).u,s);
                                cout<<"UserName updated..\n";
                                cout<<"\n";
                                break;
                            }
                            else{
                                cout<<"Username Already Exists..Try again\n";
                                cout<<"\n";
                            }
                        }
                        break;
                case 2:char q[9];
                        cout<<"New Password-- ";
                        cin>>q;
                        strcpy((t->us).p,q);
                        cout<<"Password Updated Successfully..\n";
                        cout<<"\n";
                        break;
                case 3:delete_node(h,(t->us).u);
                        break;
                default:cout<<"Redirecting to the main menu...\n";
                cout<<"\n";
                        break;        
            } 
            return 1;
        }
        p=t;
        t=t->next;
    }
    return 0;
}

//log_in end

//encryption begins

char encrypt(char c)
{
    switch (c)
    {
        case '0':return '&';
        case '1':return '*';
        case '2':return '!';
        case '3':return '/';
        case '4':return '$';
        case '5':return '^';
        case '6':return '<';
        case '7':return '>';
        case '8':return '?';
        case '9':return '@';
    }
}