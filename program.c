
#include <windows.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 256

struct StudentInfo
{
    char ID[10];
    char Name[20];
    char Email[30];
    char Phone[20];
    int  NumberOfCourse;
    int rollNumber;
};

struct CourseInfo
{
    char StudentID[10];
    char Code[10];
    char Name[20];
};

typedef struct User {
    char username[30];
    char password[30];
} User;

User users[] = {{"admin", "admin123"}, {"user1", "password1"}, {"user2", "password2"}};
int numUsers = sizeof(users) / sizeof(users[0]);


struct StudentInfo Students[100];
struct CourseInfo Courses[500];

// some global variables
#define MAX_LINE_LENGTH 255
int i,j;
int TotalStudents = 0;
int TotalCourse = 0;
char StudentID[10];
FILE *AllStudents;
FILE *AllCourses;
FILE *ExistingAllStudents;
FILE *TempAllStudents;
FILE *ExistingAllCourses;
FILE *TempAllCourses;
// end

bool IsRunning = true;
void displayHeader();
int login();
void Menu();
void AddNewStudent();
void ShowAllStudents();
bool SearchStudent(char StudentID[10]);
void EditStudent(char StudentID[10]);
void DeleteStudent(char StudentID[10]);
void DeleteAllStudents();
int countValue(char *givenLine,char InfoType);
void ErrorAndRestart(char *Error[100]);
void DeleteCourseByIndex(int CourseIndex);
void DeleteStudentByIndex(int CourseIndex);
void GoBackOrExit();
void ExitProject();


int main()
{
    displayHeader();
    system("cls"); // FOR CLEARING SCREEN
    if (login())
        {
        printf("\t\t\t\t\t      WELCOME !!!! LOGIN IS SUCCESSFUL               \n");
        printf(" \n Press any key to continue:");
        getch();
        system("cls"); // FOR CLEARING SCREEN
    while(IsRunning)
    {
        system("cls"); // FOR CLEARING SCREEN
        Menu();
        int Option;
        scanf("%d",&Option);
        switch(Option)
        {
        case 0:
            IsRunning = false;
            ExitProject();
            break;
        case 1:
            system("cls");
            printf("\n\t\t\t **** Add A New Student ****\n\n");
            AddNewStudent();
            GoBackOrExit();
            break;
        case 2:
            system("cls");
            printf("\n\t\t\t\t\t **** All Students ****\n\n");
            ShowAllStudents();
            GoBackOrExit();
            break;

        case 5:
        {
            system("cls");
            printf("\n\t\t\t **** Search Students ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            bool IsFound = SearchStudent(StudentID);
            if(!IsFound)
            {
                printf("\n\n!!! No Student Found!!!\n\n");
            }
            printf("\n");
            GoBackOrExit();
            break;
        }
        case 6:
            system("cls");
            printf("\n\t\t\t **** Edit a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);
            bool StudentFoundIndex = SearchStudent(StudentID);

            if(StudentFoundIndex>=0)
            {
                EditStudent(StudentID);
            }
            else
            {
                printf(" No Student Found\n\n");
            }
            GoBackOrExit();
            break;
        case 7:
            system("cls");
            printf("\n\t\t\t **** Delete a Student ****\n\n");
            printf(" Enter The Student ID: ");
            scanf("%s",StudentID);

            bool DeleteStudentFoundIndex = SearchStudent(StudentID);

            if(DeleteStudentFoundIndex>=0)
            {
                char Sure = 'N';
                getchar();
                printf("\n\n");
                printf(" Are you sure want to delete this student? (Y/N): ");
                scanf("%c",&Sure);

                if(Sure == 'Y' || Sure == 'y')
                {
                    DeleteStudent(StudentID);
                }
                else
                {
                    printf(" Your Data is Safe.\n\n");
                    GoBackOrExit();
                }

            }
            else
            {
                printf(" No Student Found\n\n");
                GoBackOrExit();
            }

            break;
        case 8:
        {
            char Sure = 'N';
            getchar();
            system("cls");
            printf("\n\t\t\t **** Delete ALL Students ****\n\n");

            printf(" Are you sure want to delete all the students? (Y/N): ");
            scanf("%c",&Sure);
            if(Sure == 'Y' || Sure == 'y')
            {
                DeleteAllStudents();
            }
            else
            {
                printf(" Your Data is Safe.\n\n");
                GoBackOrExit();
            }
            break;
        }

        case 9:
            system("cls");
            break;
        default:
            ExitProject();
            break;
        }
    }}
    else
    {
        printf("\t\t\t\t\t      Sorry, incorrect username or password.              \n");
    }

    // Wait for user input to exit
    printf("\nPress any key to exit...");
    getch(); // Use getch() to capture a key press
    return 0;
} // end main function

void displayHeader()
{
    system("cls"); // FOR CLEARING SCREEN
    printf("\t\t\t -------------------------------------------------------------------------\n");
    printf("\t\t\t|                                                                         |\n");
    printf("\t\t\t|                                                                         |\n");
    printf("\t\t\t|       W      W  WW W W  W       WW W W  WW W WW  WW    WW  WW W W       |\n");
    printf("\t\t\t|       W      W  W       W       W       W     W  W W  W W  W            |\n");
    printf("\t\t\t|       W  WW  W  WW W W  W       W       W     W  W  WW  W  WW W W       |\n");
    printf("\t\t\t|       W W  W W  W       W       W       W     W  W      W  W            |\n");
    printf("\t\t\t|       WW    WW  WW W W  WW W W  WW W W  WW W WW  W      W  WW W W       |\n");
    printf("\t\t\t|                                                                         |\n");
    printf("\t\t\t|                                                                         |\n");
    printf("\t\t\t -------------------------------------------------------------------------\n");

    printf("\t\t\t\t\t*************************************************\n");
    printf("\t\t\t\t\t*                                               *\n");
    printf("\t\t\t\t\t*       -----------------------------           *\n");
    printf("\t\t\t\t\t*          STUDENT DATA MANAGEMENT              *\n");
    printf("\t\t\t\t\t*       -----------------------------           *\n");
    printf("\t\t\t\t\t*                                               *\n");
    printf("\t\t\t\t\t*                                               *\n");
    printf("\t\t\t\t\t*                                               *\n");
    printf("\t\t\t\t\t*             Brought To You By                 *\n");
    printf("\t\t\t\t\t*             1. Arun Sadalgekar                *\n");
    printf("\t\t\t\t\t*             2. Rohan Mushannavar              *\n");
    printf("\t\t\t\t\t*             3. Varad Belgaonkar               *\n");
    printf("\t\t\t\t\t*             4. Nitin Chavan                   *\n");
    printf("\t\t\t\t\t*************************************************\n\n\n");

    printf(" \n Press any key to continue:");

    getch();
}

int authenticateUser(char username[], char password[]) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}


int login()
{
    char username[30], password[30];
    int loginAttempts = 0;
    printf("\n\n\n\n\n\n");
    printf("\t\t\t\t\t*************************************************\n");
    printf("\t\t\t\t\t                                                 \n");
    printf("\t\t\t\t\t        -----------------------------            \n");
    printf("\t\t\t\t\t                    LOGIN                        \n");
    printf("\t\t\t\t\t        -----------------------------            \n");
    printf("\t\t\t\t\t                                                 \n");
    printf("\t\t\t\t\t        ENTER USERNAME :-  ");
    scanf("%s", username);
    printf("\t\t\t\t\t                                                 \n");
    printf("\t\t\t\t\t        ENTER PASSWORD :-  ");
    scanf("%s", password);
    printf("\t\t\t\t\t                                                 \n");
    printf("\t\t\t\t\t                                                 \n");
    printf("\t\t\t\t\t*************************************************\n\n\n");

    // Check if username and password match
    if (authenticateUser(username, password))
    {
        return 1; // Login successful
    }
    else
    {
        return 0; // Login failed
    }
}

void Menu()
{
    printf("\n\n\t***Student Management System Using C***\n\n");
    printf("\t\t\tMAIN MENU\n");
    printf("\t\t=======================\n");
    printf("\t\t[1] Add A New student.\n");
    printf("\t\t[2] Show All students.\n");
    printf("\t\t[5] Search A student.\n");
    printf("\t\t[6] Edit A student.\n");
    printf("\t\t[7] Delete A student.\n");
    printf("\t\t[8] Delete All students.\n");
    printf("\t\t[9] Clear The window.\n");
    printf("\t\t[0] Exit the Program.\n");
    printf("\t\t=======================\n");
    printf("\t\tEnter The Choice: ");
} // end menu

void AddNewStudent()
{

    struct StudentInfo NewStudent;


    bool IsValidID = false;
    while(!IsValidID)
    {
        printf(" Enter The ID: ");
        scanf("%s",&NewStudent.ID);

        if(countValue(NewStudent.ID,'i') > 0)
        {
            printf(" Error: This ID is already exists.\n\n");
            IsValidID = false;
        }
        else if(strlen(NewStudent.ID) > 10)
        {
            printf(" Error: ID can not be more than 10 characters.\n\n");
            IsValidID = false;
        }
        else if(strlen(NewStudent.ID) <= 0)
        {
            printf(" Error: ID can not be empty.\n\n");
            IsValidID = false;
        }
        else
        {
            IsValidID = true;
        }
    }

        printf(" Enter The Roll No. : ");
        scanf("%d",&NewStudent.rollNumber);



    bool IsValidName = false;
    while(!IsValidName)
    {
        printf(" Enter The Name: ");
        scanf(" %[^\n]s",&NewStudent.Name);

        if(strlen(NewStudent.Name) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = false;
        }
        if(strlen(NewStudent.Name) <= 0)
        {
            printf(" Error: Name can not be empty.\n\n");
            IsValidName = false;
        }
        else
        {
            IsValidName = true;
        }
    }


    bool IsValidEmail = false;
    while(!IsValidEmail)
    {
        printf(" Enter The Email: ");
        scanf("%s",&NewStudent.Email);

        if(countValue(NewStudent.Email,'e') > 0)
        {
            printf(" This Email is Already Exists.\n");
            IsValidEmail = false;
        }
        else if(strlen(NewStudent.Email) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = false;
        }
        else if(strlen(NewStudent.Email) <= 0)
        {
            printf(" Error: Email can not be empty.\n\n");
            IsValidEmail = false;
        }
        else
        {
            IsValidEmail = true;
        }
    }


    bool IsValidPhone = false;
    while(!IsValidPhone)
    {
        printf(" Enter The Phone: ");
        scanf("%s",&NewStudent.Phone);
        if(countValue(NewStudent.Phone,'p') > 0)
        {
            printf(" This Phone Number is Already Exists\n");
            IsValidPhone = false;
        }
        else if(strlen(NewStudent.Phone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = false;
        }
        else if(strlen(NewStudent.Phone) <= 0)
        {
            printf(" Error: Phone can not be empty.\n\n");
            IsValidPhone = false;
        }
        else
        {
            IsValidPhone = true;
        }
    }

    bool IsValidNumberOfCourse = false;
    while(!IsValidNumberOfCourse)
    {
        printf(" Number of courses: ");
        scanf("%d",&NewStudent.NumberOfCourse);

        if(NewStudent.NumberOfCourse <= 0 || NewStudent.NumberOfCourse > 4)
        {
            printf(" Error: Number of courses can not be more than 4 and lees than 1.\n\n");
            IsValidNumberOfCourse = false;
        }
        else
        {
            IsValidNumberOfCourse = true;
        }
    }

    // store information in file
    FILE *file_students = fopen("students.txt", "a");
    fprintf(file_students, "%s,%d,%s,%s,%s,%d\n",NewStudent.ID,NewStudent.rollNumber,NewStudent.Name,NewStudent.Email,NewStudent.Phone,NewStudent.NumberOfCourse);
    fclose(file_students);
    // end

    struct CourseInfo Course;

    for(i=0; i<NewStudent.NumberOfCourse; i++)
    {
        printf(" Enter Course %d Code: ",i+1);
        scanf("%s",&Course.Code);

        printf(" Enter Course %d Name: ",i+1);
        scanf(" %[^\n]s",&Course.Name);

        strcpy(Course.StudentID,NewStudent.ID);

        // store Course in file
        FILE *file_courses = fopen("courses.txt", "a");
        fprintf(file_courses, "%s,%s,%s\n",Course.StudentID,Course.Code,Course.Name);
        fclose(file_courses);
        // end
    }

    printf("\n\n Successfully Added New Student.\n");

}

void ShowAllStudents()
{

    char line[MAX_LINE_LENGTH];
    char *delimiter = ",";
    char *ID;
    char *RollNumber;
    char *Name;
    char *Email;
    char *Phone;
    char *NumberOfCourse;



    printf("|==========|============|====================|==============================|====================|=============|\n");
    printf("|    ID    |  Roll No   |        Name        |            Email             |       Phone        |  NO.Course  |\n");
    printf("|==========|============|====================|==============================|====================|=============|\n");


    FILE *StudentFile = fopen("students.txt","r");

    while(fgets(line,MAX_LINE_LENGTH,StudentFile)){

        ID = strtok(line,delimiter);
        RollNumber = strtok(NULL,delimiter);
        Name = strtok(NULL,delimiter);
        Email = strtok(NULL,delimiter);
        Phone = strtok(NULL,delimiter);
        NumberOfCourse = strtok(NULL,delimiter);
        NumberOfCourse[1] = '\0'; // as we already know number of course will be always one character.

        printf("|");
        printf("%s",ID);
        for(i=0;i< (10 - strlen(ID)); i++){
            printf(" ");
        }

        printf("|");
        printf("%s",RollNumber);
        for(i=0;i< (12 - strlen(RollNumber)); i++){
            printf(" ");
        }

        printf("|");
        printf("%s",Name);
        for(i=0;i< (20 - strlen(Name)); i++){
            printf(" ");
        }

        printf("|");
        printf("%s",Email);
        for(i=0;i< (30 - strlen(Email)); i++){
            printf(" ");
        }

        printf("|");
        printf("%s",Phone);
        for(i=0;i< (20 - strlen(Phone)); i++){
            printf(" ");
        }

        printf("|");
        printf("%s",NumberOfCourse);
        for(i=0;i< (13 - strlen(NumberOfCourse)); i++){
            printf(" ");
        }

        printf("|\n");
        printf("|----------|------------|--------------------|------------------------------|--------------------|-------------|\n");
    }

    fclose(StudentFile);
}




bool SearchStudent(char StudentID[10])
{
    system("cls");

    // student search from file

    char line[MAX_LINE_LENGTH];
    char *ID;
    char *RollNumber;
    char *Name;
    char *Email;
    char *Phone;
    char *NumberOfCourse;

    char *delimiter = ",";
    bool found = false;


    FILE *studentsFile = fopen("students.txt", "r");

    while(fgets(line,MAX_LINE_LENGTH,studentsFile))
    {

        ID = strtok(line,delimiter);

        if(strcmp(ID,StudentID) == 0)
        {
            // we found a student
            found = true;
            printf("\n One Student Found for ID: %s\n\n",StudentID);
            printf(" Student Informations\n");
            printf("-------------------------\n");

            printf(" ID         :  %s\n",ID);

            RollNumber = strtok(NULL,delimiter);
            printf(" Roll No    :  %s\n",RollNumber);

            Name = strtok(NULL,delimiter); // name
            printf(" Name       :  %s\n",Name);

            Email = strtok(NULL,delimiter); // email
            printf(" Email      :  %s\n",Email);

            Phone = strtok(NULL,delimiter); // phone
            printf(" Phone      :  %s\n",Phone);

            NumberOfCourse = strtok(NULL,delimiter); // number of courses
            printf(" Number of Courses : %s\n",NumberOfCourse);

            break;
        }
    }
    fclose(studentsFile);

    // show course information from file

    char *Code;
    char *CourseName;
    int course_count_from_file = 0;
    FILE *coursesFile = fopen("courses.txt", "r");

    while(fgets(line,MAX_LINE_LENGTH,coursesFile))
    {
        ID = strtok(line,delimiter);

        if(strcmp(ID,StudentID) == 0)
        {
            course_count_from_file++;
            Code = strtok(NULL,delimiter); // code
            printf(" Course %d Code : %s\n",course_count_from_file,Code);
            CourseName = strtok(NULL,delimiter); // name
            printf(" Course %d Name : %s\n",course_count_from_file,CourseName);
        }
    }
    fclose(coursesFile);
    // end

    return found;
}











void EditStudent(char StudentID[10])
{
    printf("\n\t\t **** Update The New Student ****\n\n");

    // get old student information from file
    // we have index
    char line[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];
    char *old_ID;
    char *old_Name;
    char *old_Email;
    char *old_Phone;
    char *old_NumberOfCourse;
    char *delimiter = ",";
    int count_line = -1;

    FILE *studentsFile = fopen("students.txt", "r");
    while(fgets(line,MAX_LINE_LENGTH,studentsFile))
    {
        count_line++;
        old_ID = strtok(line,delimiter);
        if(strcmp(old_ID,StudentID) == 0)
        {
            old_Name = strtok(NULL,delimiter);
            old_Email = strtok(NULL,delimiter);
            old_Phone = strtok(NULL,delimiter);
            old_NumberOfCourse = strtok(NULL,delimiter);
            break;
        }
    }
    // end

    fclose(studentsFile);

    struct StudentInfo NewStudent;
    struct StudentInfo UpdatedStudent;

    bool IsValidName = false;
    while(!IsValidName)
    {
        printf(" Enter The New Name(0 for skip): ");
        scanf(" %[^\n]s",&NewStudent.Name);

        if(strlen(NewStudent.Name) > 20)
        {
            printf(" Error: Name can not be more than 20 characters.\n\n");
            IsValidName = false;
        }
        if(strlen(NewStudent.Name) <= 0)
        {
            printf(" Error: Name can not be empty.\n\n");
            IsValidName = false;
        }
        else
        {
            IsValidName = true;
        }
    }


    bool IsValidEmail = false;
    while(!IsValidEmail)
    {
        printf(" Enter The New Email(0 for skip): ");
        scanf("%s",&NewStudent.Email);

        if(countValue(NewStudent.Email,'e') > 1 && strcmp(old_Email,NewStudent.Email) != 0)
        {
            printf(" This Email is Already Exists.\n");
            IsValidEmail = false;
        }
        else if(strlen(NewStudent.Email) > 30)
        {
            printf(" Error: Email can not be more than 30 characters.\n\n");
            IsValidEmail = false;
        }
        else if(strlen(NewStudent.Email) <= 0)
        {
            printf(" Error: Email can not be empty.\n\n");
            IsValidEmail = false;
        }
        else
        {
            IsValidEmail = true;
        }
    }

    bool IsValidPhone = false;
    while(!IsValidPhone)
    {
        printf(" Enter The New Phone(0 for skip): ");
        scanf("%s",&NewStudent.Phone);
        if(countValue(NewStudent.Phone,'p') > 1 && strcmp(old_Phone,NewStudent.Phone) !=0)
        {
            printf(" This Phone Number is Already Exists\n");
            IsValidPhone = false;
        }
        else if(strlen(NewStudent.Phone) > 20)
        {
            printf(" Error: Phone can not be more than 20 characters.\n\n");
            IsValidPhone = false;
        }
        else if(strlen(NewStudent.Phone) <= 0)
        {
            printf(" Error: Phone can not be empty.\n\n");
            IsValidPhone = false;
        }
        else
        {
            IsValidPhone = true;
        }
    }

    bool IsValidNumberOfCourse = false;
    while(!IsValidNumberOfCourse)
    {
        printf(" Number of New courses(0 for skip): ");
        scanf("%d",&NewStudent.NumberOfCourse);

        if(NewStudent.NumberOfCourse <= 0 || NewStudent.NumberOfCourse > 4)
        {
            printf(" Error: Number of courses can not be more than 4 and lees than 1.\n\n");
            IsValidNumberOfCourse = false;
        }
        else
        {
            IsValidNumberOfCourse = true;
        }
    }

    strcpy(UpdatedStudent.ID,old_ID);

    if(strcmp(NewStudent.Email,"0") != 0)
    {
        strcpy(UpdatedStudent.Name,NewStudent.Email);
    }else{
        strcpy(UpdatedStudent.Name,old_Email);
    }

    if(strcmp(NewStudent.Email,"0") != 0)
    {
        strcpy(UpdatedStudent.Email,NewStudent.Email);
    }else{
        strcpy(UpdatedStudent.Email,old_Email);
    }

    if(strcmp(NewStudent.Phone,"0") != 0)
    {
        strcpy(UpdatedStudent.Phone,NewStudent.Phone);
    }else{
        strcpy(UpdatedStudent.Phone,old_Phone);
    }


    if(NewStudent.NumberOfCourse > 0){
        //itoa(num, snum, 10);
        UpdatedStudent.NumberOfCourse = NewStudent.NumberOfCourse;

    }else{
        UpdatedStudent.NumberOfCourse = atoi(old_NumberOfCourse);
    }

    // update the text file

    FILE *MainStudentsFile = fopen("students.txt", "r");
    FILE *TempStudentsFile = fopen("temp-students.txt", "w");

    while(fgets(line,MAX_LINE_LENGTH,MainStudentsFile)){
        strcpy(line2,line);
        old_ID = strtok(line,delimiter);

        if(strcmp(old_ID,StudentID) != 0)
        {
            fprintf(TempStudentsFile,"%s",line2);
        }
    }

    fprintf(TempStudentsFile, "%s,%s,%s,%s,%d\n",UpdatedStudent.ID,UpdatedStudent.Name,UpdatedStudent.Email,UpdatedStudent.Phone,UpdatedStudent.NumberOfCourse);
    fclose(TempStudentsFile);
    fclose(MainStudentsFile);

    remove("students.txt");
    rename("temp-students.txt","students.txt");
    // end

    if(UpdatedStudent.NumberOfCourse != 0)
    {
        // store Course in file
        FILE *CoursesFile = fopen("courses.txt", "r");
        FILE *TempCoursesFile = fopen("temp-courses.txt", "w");
        while(fgets(line,MAX_LINE_LENGTH,CoursesFile)){
            strcpy(line2,line);
            old_ID = strtok(line,delimiter);
            if(strcmp(old_ID,StudentID) != 0){
                fprintf(TempCoursesFile,line2);
            }
        }

        struct CourseInfo Course;

        for(i=0; i<UpdatedStudent.NumberOfCourse; i++)
        {
            printf(" Enter Course %d Code: ",i+1);
            scanf("%s",&Course.Code);

            printf(" Enter Course %d Name: ",i+1);
            scanf(" %[^\n]s",&Course.Name);

            strcpy(Course.StudentID,UpdatedStudent.ID);

            fprintf(TempCoursesFile, "%s,%s,%s\n",Course.StudentID,Course.Code,Course.Name);
            // end
        }

        fclose(CoursesFile);
        fclose(TempCoursesFile);

        remove("courses.txt");
        rename("temp-courses.txt","courses.txt");
    }
    printf(" Student Updated Successfully.\n\n");

}

void DeleteStudent(char StudentID[10])
{

    char line[MAX_LINE_LENGTH];
    char line2[MAX_LINE_LENGTH];
    char *ID;
    char *delimiter = ",";

    FILE *MainStudentsFile = fopen("students.txt", "r");
    FILE *TempStudentsFile = fopen("temp-students.txt", "w");

    while(fgets(line,MAX_LINE_LENGTH,MainStudentsFile)){
        strcpy(line2,line);
        ID = strtok(line,delimiter);

        if(strcmp(ID,StudentID) != 0)
        {
            fprintf(TempStudentsFile,"%s",line2);
        }
    }

    fclose(TempStudentsFile);
    fclose(MainStudentsFile);

    remove("students.txt");
    rename("temp-students.txt","students.txt");

    // store Course in file
    FILE *CoursesFile = fopen("courses.txt", "r");
    FILE *TempCoursesFile = fopen("temp-courses.txt", "w");
    while(fgets(line,MAX_LINE_LENGTH,CoursesFile)){
        strcpy(line2,line);
        ID = strtok(line,delimiter);
        if(strcmp(ID,StudentID) != 0){
            fprintf(TempCoursesFile,line2);
        }
    }

    fclose(CoursesFile);
    fclose(TempCoursesFile);

    remove("courses.txt");
    rename("temp-courses.txt","courses.txt");


    printf(" Student Deleted Successfully.\n\n");
    GoBackOrExit();
}

void DeleteAllStudents()
{
    remove("students.txt");
    FILE *TempStudentsFile = fopen("students.txt", "w");
    fclose(TempStudentsFile);

    remove("courses.txt");
    FILE *TempCoursesFile = fopen("courses.txt", "w");
    fclose(TempCoursesFile);

    printf(" All Students Deleted Successfully.\n\n");
    GoBackOrExit();
}

int countValue(char *givenLine, char InfoType)
{
    char line[MAX_LINE_LENGTH];
    char *ID,*RollNumber,*Name,*Email,*Phone,*NumberOfCourse;
    char *delimiter = ",";
    FILE *studentsFile;
    int count = 0;

    studentsFile = fopen("students.txt","r");

    while(fgets(line,MAX_LINE_LENGTH,studentsFile))
    {

        ID = strtok(line,delimiter);
        RollNumber = strtok(NULL,delimiter);
        Name = strtok(NULL,delimiter);
        Email = strtok(NULL,delimiter);
        Phone = strtok(NULL,delimiter);
        NumberOfCourse = strtok(NULL,delimiter);

        if(strcmp(ID,givenLine) == 0 && InfoType == 'i')
        {
            count++;
        }
           else if(strcmp(RollNumber,givenLine) == 0 && InfoType == 'r')
        {
            count++;
        }
        else if(strcmp(Email,givenLine) == 0 && InfoType == 'e')
        {
            count++;
        }
        else if(strcmp(Phone,givenLine) == 0 && InfoType == 'p')
        {
            count++;
        }
    }

    fclose(studentsFile);
    return count;
}

void ErrorAndRestart(char *error[100])
{
    printf("%s\n",error);
    int i = 0;
    printf("Restarting the program: ");
    for(i=0; i<10; i++)
    {
        printf(".");
        Sleep(500);
    }
    system("cls");
    main();
}

void GoBackOrExit()
{
    getchar();
    char Option;
    printf(" Go back(b)? or Exit(0)?: ");
    scanf("%c",&Option);
    if(Option == '0')
    {
        ExitProject();
    }
    else
    {
        system("cls");
    }
}

void ExitProject()
{
    system("cls");
    int i;
    char ThankYou[100]     = "\n\n\n\n\t\t\t\t\t ========= Thank You =========\n";
    char SeeYouSoon[100]   = "\n\n\n\n\t\t\t\t\t ========= See You Soon ======\n";
    for(i=0; i<strlen(ThankYou); i++)
    {
        printf("%c",ThankYou[i]);
        Sleep(30);
    }
    for(i=0; i<strlen(SeeYouSoon); i++)
    {
        printf("%c",SeeYouSoon[i]);
        Sleep(30);
    }
    printf("\n\n\n\n\n\n\n\n");
    exit(0);
}
