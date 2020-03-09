#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct student {
	char name[20];
	int midterm;
	int final;
	int studentno;
	double average;
};
typedef struct student stu;
stu * ptr_stu = NULL;

int student_count = 0;
void mainmenu();
void AddStudents();
int get_StudentRecordCount();

int get_StudentRecordCount()
{
	int countofstudent = 0;
	FILE * f = fopen("student_info.dat", "r+b"); // Open file with read mode.
	if (f != NULL)
	{
		fseek(f, 0, SEEK_END); // Take the file pointer to the end of file.
		int sizeoffile = ftell(f); // Get the size of file.
		countofstudent = sizeoffile / sizeof(stu); // At this point if we want to know student count we have to divide file size to struct size of student, then we will get a student count as a result.
		fclose(f);
	}
	return countofstudent;
}


void AddStudents()
{
	char names[1000][20]; // Allocating place for 1000 students' names and we assume each student can only have maximum 20 letters name.
	int properties[1000][3]; // Allocating place for 1000 students' properties. (midterm,final,student no)
	double averages[1000]; // Allocating place for 1000 students' average.

	printf("Please enter a count of students to add memory : ");
	scanf("%d", &student_count);
	ptr_stu = (stu*)malloc(sizeof(stu) * student_count); // Allocating memory for struct.
	int i = 0;
	for (i; i < student_count; i++) // Take all informations from keyboard and save into memory.
	{

		printf("\nPlease enter the name of %d. student : ", (i + 1));
		scanf("%s", names[i]);
		strcpy(ptr_stu[i].name, names[i]);
		printf("\nPlease enter the midterm exam result of %d. student : ", (i + 1));
		scanf("%d", &properties[i][0]);
		ptr_stu[i].midterm = properties[i][0];
		printf("\nPlease enter the final exam result of %d. student : ", (i + 1));
		scanf("%d", &properties[i][1]);
		ptr_stu[i].final = properties[i][1];
		printf("\nPlease enter the student no of %d. student : ", (i + 1));
		scanf("%d", &properties[i][2]);
		ptr_stu[i].studentno = properties[i][2];
		averages[i] = (double)((double)properties[i][0] * 0.4 + (double)properties[i][1] * 0.6); // Calculate average.
		ptr_stu[i].average = averages[i];
	}
	printf("Do you want to save informations to file ?(y/n) : ");
	if (getch() == 'y')
	{
		FILE * file = fopen("student_info.dat", "a+b"); // Open file with read mode.
		int countofstu = get_StudentRecordCount(); // Get count of students recorded.
		fseek(file, ((countofstu) * sizeof(stu)), SEEK_SET); // Set the file pointer to the next student.
		fwrite(ptr_stu, sizeof(stu)* student_count, 1, file); // Write our new student data to file.
		fclose(file); // Close file
		printf("\nStudent informations has been saved into student_info.dat.\nPlease enter a key to resume main menu.");
		getch();
		mainmenu();
	}
	else
	{
		mainmenu();
	}
}

void ReadStudentsFromFile()
{
	int count = get_StudentRecordCount(); // Get count of student from file.
	if (count == 0)
	{
		printf("There isnt any student information in file.\nPlease enter a key to resume main menu.");
		getch();
		mainmenu();
	}
	else
	{
		system("cls");
		FILE * f = fopen("student_info.dat", "r+b");
		stu * new_ptr_stu = (stu*)malloc(sizeof(stu) * count); // Allocate struct for read data from file.
		int i = 0;
		for (i; i < count; i++) // Take informations to struct pointer by using i variable and struct size.
		{
			fseek(f, i * sizeof(stu), SEEK_SET);
			fread(&new_ptr_stu[i], sizeof(stu), 1, f);
		}
		fclose(f);

		i = 0;
		for (i; i < count; i++)
		{
			printf("--------------------------------------------------------------------\n");
			printf("Student Name : %s\nStudent No : %d\nMidterm Result : %d\nFinal Result : %d\nAverage : %lf\nPass : %s\n", new_ptr_stu[i].name, new_ptr_stu[i].studentno, new_ptr_stu[i].midterm, new_ptr_stu[i].final, new_ptr_stu[i].average, new_ptr_stu[i].average >= 60.0 ? "Yes" : "No");
			printf("--------------------------------------------------------------------\n");
		}
		printf("Please enter a key to resume main menu.");
		getch();
		mainmenu();
	}
}

void ReadStudentsFromMemory()
{
	if (ptr_stu != NULL)
	{
		int i = 0;
		for (i; i < student_count; i++)
		{
			printf("--------------------------------------------------------------------\n");
			printf("Student Name : %s\nStudent No : %d\nMidterm Result : %d\nFinal Result : %d\nAverage : %lf\nPass : %s\n", ptr_stu[i].name, ptr_stu[i].studentno, ptr_stu[i].midterm, ptr_stu[i].final, ptr_stu[i].average, ptr_stu[i].average >= 60.0 ? "Yes" : "No");
			printf("--------------------------------------------------------------------\n");
		}
		printf("Please enter a key to resume main menu.");
		getch();
		mainmenu();
	}
	else
	{
		printf("There isnt any recorded information of student in memory\nPlease enter a key to resume main menu.");
		getch();
		mainmenu();
	}
}

void mainmenu()
{
	system("cls");
	printf("1-Add Students\n2-Show Saved Student Informations\n3-Show Student Informations In Memory\n4-Exit\n");
	int a;
	scanf("%d", &a);
	switch (a)
	{
	case 1:
		AddStudents();
		break;
	case 2:
		ReadStudentsFromFile();
		break;
	case 3:
		ReadStudentsFromMemory();
		break;
	case 4:
		return;
	}
}

int main()
{
	mainmenu();
	return 0;
}
