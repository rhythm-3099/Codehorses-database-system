#include <stdio.h>
#include <stdlib.h>
#include "libpq-fe.h"
#include<string.h>

PGresult *res;

void do_exit(PGconn *conn) {
  
    PQfinish(conn);
    exit(1);
}

void ExecuteQuery(PGconn* conn,char* query)
{
    PQexec(conn, "set search_path to project;");
    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Query failed: %s",PQerrorMessage(conn));
        do_exit(conn);
    }
    else
    {
        int rows = PQntuples(res);
        int ncols = PQnfields(res);
        for(int i=0; i<ncols; i++)
        {                         
            char *name = PQfname(res, i);
            printf("%s      ", name);
        }
        printf("\n");
        for(int i=0; i<rows; i++)
        {
            for(int j=0;j<ncols;j++)
                printf("%s      ",PQgetvalue(res, i, j));
            printf("\n");
        }
        printf("\n\n\n\n\n-------------We received %d records----------------\n\n\n\n",rows);

    }
}

void ExecuteUpdate(PGconn* conn,char* command){
        PQexec(conn, "set search_path to project;");
        res = PQexec(conn, command);
        if (PQresultStatus(res) != PGRES_COMMAND_OK){
            fprintf(stderr, "%.6s failed: %s",command,PQerrorMessage(conn));
            do_exit(conn);
        }
        else
            printf("successful\n");
}


int main()
{
    const char *conninfo = "dbname=201701266 user=201701266 password=viradiya247 hostaddr=10.100.71.21 port=5432";
    PGconn *conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK){
        fprintf(stderr, "Connection to database failed: %s\n",PQerrorMessage(conn));
        do_exit(conn);
    }

    char *user = PQuser(conn);
    char *db_name = PQdb(conn);

    printf("User: %s\n", user);
    printf("Database name: %s\n", db_name);

    while(1){
        char command[1000];
        printf("1 FOR SELECTION QUERY\n2 FOR INSERT,UPDATE AND DELETE QUERY\n3 to exit");
        int n;
        scanf("%d",&n);
        if(n==1)
        {
    printf("Enter 1 to know the information of some user:\n"); // done

    printf("Enter 2 to know the weakest category of the user:\n"); // done
    printf("Enter 3 to know the top 5 programmers of some Institute:\n"); // done
printf("Enter 4 to run any custom selection query:\n");
int option;
scanf("%d",&option);

if(option==1){

printf("Enter the userid:\n");
char usrid[20];
char c;
scanf("%c",&c);
fgets(usrid,20,stdin);
char quer[] = "SELECT * FROM _user where(_user.userid=";
int ind=34,ind2=0;
strcat(quer,usrid);
char end[]=");";
strcat(quer,end);

ExecuteQuery(conn,quer);

} else if(option==2){

printf("Enter the userid:\n");
char usrid[20];
char c;
scanf("%c",&c);
fgets(usrid,20,stdin);
char quer[] = "SELECT weakest_cat(";
int ind=34,ind2=0;
strcat(quer,usrid);
char end[]=");";
strcat(quer,end);
ExecuteQuery(conn,quer);

} else if(option==3){

printf("Enter the institute name in single inverted commas:\n");
char instituteName[20];
char c;
scanf("%c",&c);
fgets(instituteName,20,stdin);
char quer[] = "SELECT username FROM _user WHERE (institute=";
//int ind=34,ind2=0;
strcat(quer,instituteName);
char end[]=") ORDER BY rating DESC LIMIT 5;";
strcat(quer,end);
ExecuteQuery(conn,quer);

}else if(option==4){

printf("Enter Command in a single line\n");
            char c;
            scanf("%c",&c);
            fgets (command, 1000, stdin);
            ExecuteQuery(conn,command);

} else {

printf("Enter a valid option:\n");
}

        }
        else if(n==2)
        {
            printf("Enter Command in a single line\n");
            char c;
            scanf("%c",&c);
            fgets (command, 1000, stdin);
            ExecuteUpdate(conn,command);
        }
        else if(n==3)
        {
            //PQclear(res);
            //PQfinish(conn);
            exit(0);
        }
else
{
printf("Enter a valid input");
}
        PQclear(res);
    } 
    PQfinish(conn);
    return 0;
}
