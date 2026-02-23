#ifndef STUDENT_H // chống include student.h nhiều lần
#define STUDENT_H // chống include student.h nhiều lần

typedef struct {
    char name[100];
    char studentclass[100];
    char mssv[100];
    double gpa;
} Student;

void trim(char *buffer);
void addStudent(Student *sinhvien);
void printStudent(const Student *sinhvien);
void findStudent(const Student a[], int n, const char id[]);
void deleteStudent(Student student[], int *n, const char mssv[]);
int gpaCompa(const void *a, const void *b);

#endif // chống include student.h nhiều lần