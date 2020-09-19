#include <bits/stdc++.h>


using namespace std;
int main()
{
    FILE *fp1,*fp2, *ft;
    char choice,choice2,temp;
    string brch1,brch2,name2,name1;
    struct student
    {
        string firstname,lastname,branch;
        int student_id;

    } s;
    struct marks
    {
        int id;
        int dbms_m,ds_m,c_m;

    } m;
    struct student t;
    int st_id,er=0,per,counter=0;

    fp1=fopen("student.txt","rb+");
    if (fp1 == NULL)
    {
        fp1 = fopen("student.txt","wb+");
        if (fp1==NULL)
        {
            puts("Cannot open file");
            return 0;
        }
    }
    fp2=fopen("marks.txt","rb+");
    if (fp2 == NULL)
    {
        fp2 = fopen("marks.txt","wb+");
        if (fp2==NULL)
        {
            puts("Cannot open Marks file");
            return 0;
        }
    }
    long int recsize1 = sizeof(s);
    long int recsize2 = sizeof(m);
    while(1)
    {
        system("cls");

        cout << "====== STUDENT DATABASE MANAGEMENT SYSTEM ======";
        cout << "\n\n";
        cout << "\n  1. Add     Students";
        cout << "\n  2. Modify A Student";
        cout << "\n  3. Delete A Student";
        cout << "\n  4. Search A Student";
        cout << "\n  5. Display Database";
        cout << "\n  6. Insert Marks of a Student";
        cout << "\n  7. Update Marks of a Student";
        cout << "\n  8. Search a Student using % & branch";
        cout << "\n  9. Display Marks of a Student";
        cout << "\n  0. Exit";
        cout << "\n\n";
        cout << " Select Your Choice :=> ";
        fflush(stdin);
        choice = getchar();
        switch(choice)
        {
        case '1' :
            fseek(fp1,0,SEEK_END);
                counter=0;
                cout << "How much Students you wants to add: ";
                cin>>counter;
                while(counter)
                {
                system("cls");
                cout << "Enter the Student Id   : ";
                cin >> st_id;
                rewind(fp1);
                while (fread(&t,recsize1,1,fp1) == 1)
                {
                    if(t.student_id==st_id)
                    {
                        cout<<"There is a student with same roll number so try again\n";
                        system("pause");
                        goto TRYAGAIN;
                    }
                }
                s.student_id = st_id;
                cout << "Enter Student first Name : ";
                cin>>s.firstname;
                cout << "Enter Student Last Name : ";
                cin>>s.lastname;
                cout << "Enter the Branch    : ";
                cin >> s.branch;
                fwrite(&s,recsize1,1,fp1);
                counter--;
TRYAGAIN:

                fflush(stdin);

                }

            break;

        case '2' :
            system("cls");
            temp = 'Y';
            while (temp == 'Y'|| temp == 'y')
            {
                cout << "\n Enter Student Id : ";
                cin >> st_id;

                rewind(fp1);
                while (fread(&s,recsize1,1,fp1) == 1)
                {
                    er =0;
                    if (st_id == s.student_id)
                    {
                        cout << "Enter Student New first Name : ";
                        cin>>s.firstname;
                        cout << "Enter Student Last Name : ";
                        cin>>s.lastname;
                        cout << "Enter new Branch   : ";
                        cin >> s.branch;
                        fseek(fp1, - recsize1, SEEK_CUR);
                        fwrite(&s,recsize1,1,fp1);
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

                rewind(fp1);
                while (fread (&s, recsize1,1,fp1) == 1)

                    if (st_id != s.student_id)
                    {
                        fwrite(&s,recsize1,1,ft);
                    }
                fclose(fp1);
                fclose(ft);
                remove("student.txt");
                rename("temp.txt","student.txt");

                fp1=fopen("student.txt","rb+");

                cout << "\n Delete Another Record (Y/N) ";
                fflush(stdin);
                temp = getchar();
            }

            break;

        case '4' :
            while(1)
            {
                cout<<"\n1. Search Student using Branch \n";
                cout<<"2. Search Student using First Name \n";
                cout<<"3. Return to main menu \n";
                cout << " Select Your Choice :=> ";
                fflush(stdin);
                choice2 = getchar();
                switch (choice2)
                {
                case '1' :
                    cout << "\n Enter Student Branch : ";
                    cin >> brch1;

                    rewind(fp1);
                    while (fread(&s,recsize1,1,fp1) == 1)
                    {

                        if (brch1 == s.branch)
                        {
                            cout << "Name : "<< s.firstname<<" "<<s.lastname;

                            cout << "   Student ID   : "<< s.student_id<<"\n";

                        }
                    }
                    cout<<"\nNO OTHER RESULT FOUND\n";
                    system("pause");
                    break;
                case '2' :
                    cout << "\n Enter Student Name : ";
                    cin >> name1;

                    rewind(fp1);
                    while (fread(&s,recsize1,1,fp1) == 1)
                    {

                        if (name1 == s.firstname)
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
            rewind(fp1);
            cout << "=== View the Records in the database ===";
            cout << "\nS.ID:   Name:    \t\t\tBranch:  ";
            while (fread(&s,recsize1,1,fp1) == 1)
            {
                cout << "\n"<<s.student_id<<"\t";
                cout <<setw(10)<< s.firstname<<setw(10)<<s.lastname<<"\t";
                cout <<setw(10)<<s.branch ;
            }
            cout << "\n\n";
            system("pause");
            break;
        case '6':
            fseek(fp1,0,SEEK_END);
            temp ='Y';
            while(temp == 'Y' || temp == 'y')
            {
                system("cls");
                cout << "Enter the Student Id   : ";
                cin >> st_id;
                rewind(fp1);

                while (fread(&t,recsize1,1,fp1) == 1)
                {
                    if(t.student_id==st_id)
                    {
                        m.id = st_id;
                        cout << "Enter DBMS Marks: ";
                        cin >> m.dbms_m;
                        if(m.dbms_m>100)
                            goto TRYAGAIN1;
                        cout << "Enter DS Marks    : ";
                        cin >> m.ds_m;
                        if(m.ds_m>100)
                            goto TRYAGAIN1;
                        cout << "Enter C Marks: ";
                        cin >> m.c_m;
                        if(m.c_m>100)
                            goto TRYAGAIN1;
                        fwrite(&m,recsize2,1,fp2);
                        goto TRYAGAIN1;
                    }
                }
                cout<<"Student is not registered";

TRYAGAIN1:
                cout << "\n Add another Student Marks (Y/N) ";
                fflush(stdin);
                temp = getchar();

            }
            break;

        case '7':
            fseek(fp1,0,SEEK_END);
            temp ='Y';
            while(temp == 'Y' || temp == 'y')
            {
                system("cls");
                cout << "Enter the Student Id whom you want to change marks   : ";
                cin >> st_id;
                rewind(fp1);
                while (fread(&t,recsize1,1,fp1) == 1)
                {
                    if(t.student_id==st_id)
                    {
                        ft = fopen("temp.txt", "wb");

                        rewind(fp2);
                        while (fread (&m, recsize2,1,fp2) == 1)

                            if (st_id != m.id)
                            {
                                fwrite(&m,recsize2,1,ft);
                            }
                        fclose(fp2);
                        fclose(ft);
                        remove("marks.txt");
                        rename("temp.txt","marks.txt");

                        fp2=fopen("marks.txt","rb+");
                        fseek(fp2,0,SEEK_END);
                        m.id = st_id;
                        cout << "Enter updated DBMS Marks: ";
                        cin >> m.dbms_m;
                        if(m.dbms_m>100)
                            goto TRYAGAIN2;
                        cout << "Enter updated DS Marks    : ";
                        cin >> m.ds_m;
                        if(m.ds_m>100)
                            goto TRYAGAIN2;
                        cout << "Enter updated C Marks: ";
                        cin >> m.c_m;
                        if(m.c_m>100)
                            goto TRYAGAIN2;
                        fwrite(&m,recsize2,1,fp2);
                        goto TRYAGAIN2;
                    }
                }
                cout<<"Student is not registered";

TRYAGAIN2:
                cout << "\n Update another Student Marks (Y/N) ";
                fflush(stdin);
                temp = getchar();

            }
            break;
        case '8':
            system("cls");
                cout << "Enter the Student Branch  : ";
                cin >> brch1;
                cout << "\nEnter the Student %  : ";
                cin >> per;
                rewind(fp1);


                while (fread(&t,recsize1,1,fp1) == 1)
                {
                    if(t.branch==brch1)
                    {
                       rewind(fp2);
                       while (fread(&m,recsize2,1,fp2) == 1)
                        {
                            if ((m.dbms_m+m.ds_m+m.c_m)/3 >= per)
                            {

                            cout << "   Student ID   : "<< m.id<<"\n";
                            system("pause");
                            }

                       }
                    }

                }



            break;
        case '9':
            system("cls");
            rewind(fp2);
            cout << "=== View the Records in the database ===";
            cout << "\nS.Id.  First Name    \tMarks(DBMS,DS,S)  \tTotal  \tPercentage ";
            while (fread(&m,recsize2,1,fp2) == 1)
            {

                rewind(fp1);
                while (fread(&s,recsize1,1,fp1) == 1)
                {
                    if(s.student_id==m.id)
                    {
                        cout << "\n" <<m.id;
                        cout<<"\t"<<setw(10)<<s.firstname<<" "<<s.lastname;
                        cout <<"\t" << m.dbms_m;
                        cout <<"\t" <<m.ds_m;
                        cout <<"\t" <<m.c_m;
                        cout <<"\t" <<(m.c_m+m.dbms_m+m.ds_m);
                        cout <<"\t" <<(m.c_m+m.dbms_m+m.ds_m)/3<<"%";
                        break;
                    }
                }


            }
            cout << "\n\n";
            system("pause");
            break;
        case '0':
            fclose(fp1);
            cout << "\n\n";
            cout << "\t\t     THANK YOU FOR USING THIS SOFTWARE. IT IS DESIGNED BY DIVYANSH RASTOGI";
            cout << "\n\n";
            exit(0);
        default:
                    cout<<"Invalid Input\n";
                    break;


MAINMENU: ;

        }
    }


}

