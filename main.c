#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define BUFFER_SIZE 1000
#define SLEEP_TIME 1


// Functions
void menu();
void reder();
void Delete(FILE *src, FILE *temp, const int count);
void back();
void exitp();
void DeleteStudent(int ID);
int Login(FILE *fpa);

int numPlaces (int n);


// Variables
int count = 1;
bool running = true;
int AllStudents = 0;
int AllCourses = 0;
int AllInstructor = 0;

FILE *AllStu;
FILE *AllCou;
FILE *AllInst;
FILE *AllAuthentic;
FILE *temp;
FILE *fpn;

// Struct
struct Student {
    char StuFname[30];
    char StuLname[30];
    int StuNum;
    char StuMajor[20];
};

struct Course {
    char CourseCode[10];
    char CourseName[30];
    int Weight;
};

struct Instructor {
    char InstFname[30];
    char InstLname[30];
    char InstPos[30];
    char InstMajor[30];
};

struct Authentic {
    char User[20];
    char Pass[20];
    char Role[20];
};

struct Student ListStudents[100];
struct Course ListCourses[100];
struct Instructor ListInstructor[100];
struct Authentic ListAuthentic[100];


// Main Function
int main(){

    int mn = 1;
    char name[50];

    //temp = fopen("delete.tmp", "w+");
    AllStu = fopen("list.txt", "r+");
    if (AllStu == NULL){
        printf("File can't be opened !");
        exit(1);
    }
    int flag = 1;

    system("cls");
    while(running){
        menu();
        int input;
        scanf("%i", &input);
        int d_line;

        switch (input) {
            // Exit
            case 0:
                running = false;
                exitp();
                break;

            // Add new student
            case 1:
                AllStu = fopen("list.txt", "a");
                system("cls");
               
                printf("***********************************   Add New Student   **************************************\n\n");

                printf("\tenter First Name : ");
                scanf("%s", &ListStudents[AllStudents].StuFname);
                printf("\tenter Last Name : ");
                scanf("%s", &ListStudents[AllStudents].StuLname);
                printf("\tenter ID : ");
                scanf("%i", &ListStudents[AllStudents].StuNum);
                printf("\tenter Major : ");
                scanf("%s", &ListStudents[AllStudents].StuMajor);

                fprintf(AllStu, "%s, %s, %i, %s\n", ListStudents[AllStudents].StuFname, 
                                                ListStudents[AllStudents].StuLname, 
                                                ListStudents[AllStudents].StuNum, 
                                                ListStudents[AllStudents].StuMajor);

                sprintf(name, "%i.txt",ListStudents[AllStudents].StuNum);

                fpn = fopen(name, "w+");
                fclose(fpn);
                AllStudents += 1;
                back();
                break;

            // Delete Studetn
            case 2:
            /*
                system("cls");
                printf("****************** Delete Student ******************\n\n");

                printf("    Enter id of student you want to delete : ");
                scanf("%i", &d_line);

                rewind(fp);
                Delete(fp, temp, d_line);
                fclose(temp);
                fclose(fp);
                remove("list.txt");
                rename("delete.tmp", "list.txt");
                printf("    - Student Deleted successfully.\n");
                sleep(SLEEP_TIME);
                fclose(temp);
                

                break;
            */

            // Show all student
            case 3:
                system("cls");
                sleep(SLEEP_TIME);
                printf("***********************************   Show All Students   ************************************\n\n");

                StudentReader();
                back();
                break;

            // Add new course
            case 4:
                system("cls");
                sleep(SLEEP_TIME);
                printf("************************************    Add New Course    ************************************\n\n");

                AllCou = fopen("course.txt", "a");      

                printf("\tenter Code : ");
                scanf("%s", &ListCourses[AllCourses].CourseCode);
                fflush(stdin);
                printf("\tenter Name : ");
                gets(ListCourses[AllCourses].CourseName);
                printf("\tenter Weight: ");
                scanf("%i", &ListCourses[AllCourses].Weight);

                fprintf(AllCou, "%s, %s, %i\n", ListCourses[AllCourses].CourseCode, 
                                                ListCourses[AllCourses].CourseName, 
                                                ListCourses[AllCourses].Weight);                            
                AllCourses += 1;
                back();
                break;

            // Show All Courses
            case 5:
                system("cls");
                sleep(SLEEP_TIME);
                printf("**********************************   Show All Courses   **************************************\n\n");

                CourseReader();
                back();
                break;

            //Delete Course
            case 6:
                /*

                break;
                */
            
            // Add Instructor
            case 7: 
                system("cls");
                sleep(SLEEP_TIME);
                printf("************************************    Add New Instructor    ************************************\n\n");

                AllInst = fopen("instructor.txt", "a");      

                printf("\tenter First Name : ");
                scanf("%s", &ListInstructor[AllInstructor].InstFname);
                printf("\tenter Last Name : ");
                scanf("%s", &ListInstructor[AllInstructor].InstLname);
                fflush(stdin);
                printf("\tenter Position : ");
                gets(ListInstructor[AllInstructor].InstPos);
                printf("\tenter Major: ");
                scanf("%s", &ListInstructor[AllInstructor].InstMajor);

                fprintf(AllCou, "%s, %s, %s, %s\n", ListInstructor[AllInstructor].InstFname, 
                                                ListInstructor[AllInstructor].InstLname, 
                                                ListInstructor[AllInstructor].InstPos,
                                                ListInstructor[AllInstructor].InstMajor);                            
                AllInstructor += 1;
                back();
                break;

            //Show All Instructor
            case 8:
                system("cls");
                sleep(SLEEP_TIME);
                printf("***********************************   Show All Instructors   ****************************************\n\n");

                InstructorReader();
                back();
                break;
            // Authentication 
            case 9:
                while(flag){
                    system("cls");
                    flag = Login(AllAuthentic);
                }
                back();
                break;

            default:
                exitp();
                break;
        }
    }   

    fclose(AllStu);
    return 0;
}

int Login(FILE *fpa){
    fpa = fopen("auth.txt", "r");
    int lines =0;
    while (EOF != (fscanf(fpa, "%*[^\n]"), fscanf(fpa,"%*c"))){
        ++lines;
    }   

    struct Authentic l;
    
    char user[20];
    char pass[20];

    printf("\n\n\n");
    printf("\t\t\t _______________________________ \n");
    printf("\t\t\t|                               |\n");
    printf("\t\t\t|             Login             |\n");
    printf("\t\t\t|_______________________________|\n\n");
    
    printf("\t\t\t      Username : ");
    scanf("%s", user);
    printf("\t\t\t      Password : ");
    scanf("%s", pass);
    

    for (int i = 0; i < lines; i++){
        printf("%i", i);
        if(strcmp("mamad", user) == 0){
            if(strcmp("3422", pass) == 0){
                system("cls");
                printf("Login seccussfully !\n");
                sleep(SLEEP_TIME + 2);
                return 0;
            }
            else{
                system("cls");
                printf("Wrong Password !\n");
                sleep(SLEEP_TIME + 2);
                return 1;
            }
        }
        else{
            system("cls");
            printf("Username Not Found !\n");
            sleep(SLEEP_TIME + 2);
            return 1;
        }
    }
    fclose(fpa);
    printf("\n\n");

    }

void menu(){
    printf("\n\n\t===================================================================\n");
    printf("\t||                                                               ||\n");
    printf("\t||              Amirkabir University of Technology               ||\n");
    printf("\t||                                                               ||\n");
    printf("\t||---------------------------------------------------------------||\n");
    printf("\t||                            MENU                               ||\n");
    printf("\t||---------------------------------------------------------------||\n");
    printf("\t||                                                               ||\n");
    printf("\t||\t\t[ 1 ] Add New Student                            ||\n");
    printf("\t||\t\t[ 2 ] Delete Student                             ||\n"); 
    printf("\t||\t\t[ 3 ] Show All Students                          ||\n");
    printf("\t||\t\t[ 4 ] Add New Course                             ||\n");
    printf("\t||\t\t[ 5 ] Show All Courses                           ||\n");
    printf("\t||\t\t[ 6 ] Delete Course                              ||\n");
    printf("\t||\t\t[ 7 ] Add New Instructor                         ||\n");
    printf("\t||\t\t[ 8 ] Show All Instructors                       ||\n");
    printf("\t||\t\t[ 0 ] Exit                                       ||\n");
    printf("\t||                                                               ||\n");
    printf("\t||---------------------------------------------------------------||\n\n");
    printf("\t\t\tenter : ");

}

void StudentReader(){
    AllStu = fopen("list.txt", "r");

    printf("\t|=====================|=====================|===================|================|\n");
    printf("\t|      First Name     |      Last Name      |     Student ID    |      Major     |\n");
    printf("\t|=====================|=====================|===================|================|\n");
    
    for(int i = 0; i < AllStudents; i++){
        printf("\t| %s", ListStudents[i].StuFname);
        for (int j = 0; j < 20-strlen(ListStudents[i].StuFname); j++){
            printf(" ");
        }
        
        printf("| %s", ListStudents[i].StuLname);
        for (int j = 0; j < 20-strlen(ListStudents[i].StuLname); j++){
            printf(" ");
        }
        printf("| %i", ListStudents[i].StuNum);
        for (int j = 0; j < 10; j++){
            printf(" ");
        }
        printf("| %s", ListStudents[i].StuMajor);
        for (int j = 0; j < 15-strlen(ListStudents[i].StuMajor); j++){
            printf(" ");
        }
        printf("|\n");
        printf("\t|---------------------|---------------------|-------------------|----------------|\n");

    }
}

void CourseReader(){
    AllCou = fopen("course.txt", "r");

    printf("\t|=====================|===============================|============|\n");
    printf("\t|         Code        |             Name              |   Weight   |\n");
    printf("\t|=====================|===============================|============|\n");

    for(int i = 0; i < AllCourses; i++){
        printf("\t| %s", ListCourses[i].CourseCode);
        for (int j = 0; j < 20-strlen(ListCourses[i].CourseCode); j++){
            printf(" ");
        }
        
        printf("| %s", ListCourses[i].CourseName);
        for (int j = 0; j < 30 - strlen(ListCourses[i].CourseName); j++){
            printf(" ");
        }
        printf("| %i", ListCourses[i].Weight);
        for (int j = 0; j < 10; j++){
            printf(" ");
        }
        printf("|\n");
        printf("\t|---------------------|-------------------------------|------------|\n");

    }
}

void InstructorReader(){
    AllInst = fopen("instructor.txt", "r");

    printf("\t|=====================|=====================|===============================|================|\n");
    printf("\t|      First Name     |      Last Name      |            Position           |      Major     |\n");
    printf("\t|=====================|=====================|===============================|================|\n");

    for(int i = 0; i < AllInstructor; i++){
        printf("\t| %s", ListInstructor[i].InstFname);
        for (int j = 0; j < 20-strlen(ListInstructor[i].InstFname); j++){
            printf(" ");
        }
        printf("| %s", ListInstructor[i].InstLname);
        for (int j = 0; j < 20-strlen(ListInstructor[i].InstLname); j++){
            printf(" ");
        }
        
        printf("| %s", ListInstructor[i].InstPos);
        for (int j = 0; j < 30 - strlen(ListInstructor[i].InstPos); j++){
            printf(" ");
        }
        printf("| %s", ListInstructor[i].InstMajor);
        for (int j = 0; j < 15 - strlen(ListInstructor[i].InstMajor); j++){
            printf(" ");
        }

        printf("|\n");
        printf("\t|---------------------|---------------------|-------------------------------|----------------|\n");

    }
}

void DeleteStudent(int ID){

    temp = fopen("delete.tmp", "w+");
    AllStu = fopen("list.txt", "wr");
    

    rewind(AllStu);
    Delete(AllStu, temp, ID);
    fclose(temp);
    fclose(AllStu);
    remove("list.txt");
    rename("delete.tmp", "list.txt");
}

void Delete(FILE *src, FILE *temp, const int count){
    char buffer[BUFFER_SIZE];
    int counter = 1;
   
    while ((fgets(buffer, BUFFER_SIZE, src)) != NULL){
        if (count != counter){
            fputs(buffer, temp);
        }
        counter++;
   }
}

void back(){
    getchar();
    char io;
    printf("\n        - Enter any key to go back.\n");
    printf("        - Enter 0 to exit.\n");
    scanf("%c", &io);

    if (io == '0'){
        exitp();
    }
    else{
        system("cls");
    }
}

void exitp(){
    system("cls");
    printf("\n\n\n");
    printf("*****************************************************************************************\n");
    printf("***************************     Thanks for your time.     *******************************\n");
    printf("***************************                               *******************************\n");
    printf("***************************                               *******************************\n");
    printf("*****************************************************************************************\n");
    printf("\n\n\n");

    fclose(AllStu);
    fclose(temp);
    exit(0);
}

int numPlaces (int n) {
    if (n < 10) return 1;
    return 1 + numPlaces (n / 10);
}