#include <bits/stdc++.h>


using namespace std;
int main()
{
    FILE *fp, *ft;
    char choice,choice2,temp;
    string brch1,brch2,name2,name1;
    struct student
    {
        string name,branch;
        int student_id;

    } s;
    struct student t;
    int st_id,er=0;

    fp=fopen("student.txt","rb+");
    if (fp == NULL)
    {
        fp = fopen("student.txt","wb+");
        if (fp==NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }
    long int recsize = sizeof(s);
    while(1)
    {
        system("cls");

        cout << "====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
        cout << "\n\n";
        cout << "\n  1. Add    A Student";
        cout << "\n  2. Modify A Student";
        cout << "\n  3. Delete A Student";
        cout << "\n  4. Search A Student";
        cout << "\n  5. Display Dataabase";
        cout << "\n  6. Exit";
        cout << "\n\n";
        cout << " Select Your Choice :=> ";
        fflush(stdin);
        choice = getchar();
        switch(choice)
        {
        case '1' :
            fseek(fp,0,SEEK_END);
            temp ='Y';
            while(temp == 'Y' || temp == 'y')
            {
                system("cls");
                cout << "Enter the Student Id   : ";
                cin >> st_id;
                rewind(fp);
                while (fread(&t,recsize,1,fp) == 1)
                {
                    if(t.student_id==st_id)
                    {
                        cout<<"There is a student with same roll number so try again";
                        goto TRYAGAIN;
                    }
                }
                s.student_id = st_id;
                cout << "Enter Student Name : ";
                cin.clear();
                cin.sync();
                getline(cin, s.name);
                cout << "Enter the Branch    : ";
                cin >> s.branch;
                fwrite(&s,recsize,1,fp);
TRYAGAIN:
                cout << "\n Add another Student (Y/N) ";
                fflush(stdin);
                temp = getchar();

            }
            break;

        case '2' :
            system("cls");
            temp = 'Y';
            while (temp == 'Y'|| temp == 'y')
            {
                cout << "\n Enter Student Id : ";
                cin >> st_id;

                rewind(fp);
                while (fread(&s,recsize,1,fp) == 1)
                {
                    er =0;
                    if (st_id == s.student_id)
                    {
                        cout << "Enter new Name : ";
                        cin.clear();
                        cin.sync();
                        getline(cin, s.name);
                        cout << "Enter new Branch   : ";
                        cin >> s.branch;
                        fseek(fp, - recsize, SEEK_CUR);
                        fwrite(&s,recsize,1,fp);
                        er=1;
                        break;
                    }

                }
                if(er==0) cout<<"Record not found";
                cout << "\n Modify another Student Record (Y/N) ";
                fflush(stdin);
                temp = getchar();
            }
            break;

        case '3':
            system("cls");
            temp = 'Y';
            while (temp == 'Y'|| temp == 'y')
            {
                cout << "\n Enter the Student ID of the student to delete : ";
                cin >> st_id;

                ft = fopen("temp.txt", "wb");

                rewind(fp);
                while (fread (&s, recsize,1,fp) == 1)

                    if (st_id != s.student_id)
                    {
                        fwrite(&s,recsize,1,ft);
                    }
                fclose(fp);
                fclose(ft);
                remove("student.txt");
                rename("temp.txt","student.txt");

                fp=fopen("student.txt","rb+");

                cout << "\n Delete Another Record (Y/N) ";
                fflush(stdin);
                temp = getchar();
            }

            break;

        case '4' :
            while(1)
            {
                cout<<"1. Search Student using Branch \n";
                cout<<"2. Search Student using Name \n";
                cout<<"3. Return to main menu \n";
                cout << " Select Your Choice :=> ";
                fflush(stdin);
                choice2 = getchar();
                switch (choice2)
                {
                case '1' :
                    cout << "\n Enter Student Branch : ";
                    cin >> brch1;

                    rewind(fp);
                    while (fread(&s,recsize,1,fp) == 1)
                    {

                        if (brch1 == s.branch)
                        {
                            cout << "Name : "<< s.name;

                            cout << "   Student ID   : "<< s.student_id<<"\n";

                            break;
                        }
                    }
                    cout<<"\nNO OTHER RESULT FOUND\n";
                    system("pause");
                    break;
                case '2' :
                    cout << "\n Enter Student Name : ";
                    cin >> name1;

                    rewind(fp);
                    while (fread(&s,recsize,1,fp) == 1)
                    {

                        if (name1 == s.name)
                        {
                            cout << "Student ID   : " <<s.student_id<<"  Branch   :"<<s.branch <<"\n";
                            break;
                        }
                    }
                    cout<<"\nNO OTHER RESULT FOUND\n";
                    system("pause");
                    break;

                case '3' :
                    goto MAINMENU;

                default:
                    cout<<"Invalid Input\n";
                    break;
                }

            }


        case '5' :
            system("cls");
            rewind(fp);
            cout << "=== View the Records in the database ===";
            cout << "\n";
            while (fread(&s,recsize,1,fp) == 1)
            {
                cout << "\n" <<s.student_id;
                cout <<"\t" << s.name;
                cout <<"\t" <<s.branch ;
            }
            cout << "\n\n";
            system("pause");
            break;
        case '6':
            fclose(fp);
            cout << "\n\n";
            cout << "\t\t     THANK YOU FOR USING THIS SOFTWARE. IT IS DESIGNED BY DIVYANSH RASTOGI";
            cout << "\n\n";
            exit(0);


MAINMENU: ;

        }
    }


}

