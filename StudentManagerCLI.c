#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "StudentHeader.h" // include file student.h

int main(void){
    //tránh user bấm các option khác trước 1.
    int capacity = 0; // số lượng sinh viên tối đa.
    int studentCount = 0; // số lượng sinh viên hiện có.
    int currentStudentIdx = 0; //chỉ số của sinh viên trong mảng hiện tại
    int luachon;
    char mssv1[20], mssv2[20]; 
    Student student[100];
    while(1) {
        printf("-------Menu-------\n");
        printf("1. Nhap/Cap nhat so luong sinh vien\n");
        printf("2. Nhap thong tin sinh vien\n");
        printf("3. Hien thi danh sach sinh vien\n");
        printf("4. Xoa sinh vien theo MSSV\n");
        printf("5. Liet ke sinh vien theo GPA giam dan\n");
        printf("6. Tim kiem sinh vien theo MSSV\n");
        printf("7. Exit\n");
        printf("------------------\n");

        printf("Nhap lua chon chua ban: ");
        scanf("%d", &luachon);
        while(getchar() != '\n');

        printf("\n");

        if(luachon < 1 || luachon > 7) {
            printf("Option khong hop le!!\n");
        }
        else if(luachon == 7) {
            break;
        }
        else {
            if(luachon == 1) { //Nhap/Capnhat
                while(capacity > 0) {
                    int opt;
                    printf("---------------------------------\n");
                    printf("1. Cap nhat so luong sinh vien toi da\n");
                    printf("2. Thoat\n");
                    printf("---------------------------------\n");
                    printf("So luong toi da hien tai: %d\n", capacity);
                    printf("Nhap lua chon: ");
                    scanf("%d", &opt);

                    if(opt == 1) {
                        printf("Nhap so luong toi da can cap nhat: ");
                        scanf("%d", &capacity);
                        while(getchar() != '\n');
                    }
                    else if(opt == 2) break;
                    else if (opt < 1 || opt > 2) {
                        printf("Lua chon khong hop le!\n");
                    }
                }
                while(capacity <= 0){
                    printf("Nhap so luong sinh vien: \n");
                    scanf("%d", &capacity);
                    while(getchar() != '\n');
                    if(capacity <= 0) {
                        printf("So luong nhap vao khong hop le !\n");
                    }
                }
                printf("\n");
            }

            if(capacity == 0) {
                printf("Chua nhap so luong!!\n");
            }
            else {
                if(luachon == 2) { //Them thong tin svien
                    for(int i = studentCount; i < capacity; i++) {
                        addStudent(&student[i]);
                        studentCount = i + 1;
                        ++studentCount;
                    }
                    printf("\n");
                }
                else if(luachon == 3) { //Hien thi thong tin sinh vien
                    if(studentCount != 0) {
                        for(int i = 0; i < studentCount - 1; i++) {
                            printStudent(&student[i]);
                        }
                    }
                    else printf("Danh sach sinh vien rong!!\n");
                }
                else if(luachon == 4){ //Xoa sinh vien voi mssv
                    printf("Nhap MSSV can xoa: ");
                    fgets(mssv1, sizeof(mssv1), stdin);
                    trim(mssv1);
                    deleteStudent(student, &studentCount, mssv1);
                }
                else if(luachon == 5) { //Sap xep sinh vien theo gpa
                    //size của struct
                    if(studentCount != 0) {
                        qsort(student, studentCount, sizeof(Student), gpaCompa);
                        for(int i = 0; i < studentCount; i++) {
                            printStudent(&student[i]);
                        }
                    }
                    else printf("Danh sach sinh vien rong!!\n");
                }
                else if(luachon == 6) { //Tim sinh vien theo mssv
                    if(studentCount != 0) { 
                        printf("Nhap MSSV can tim: ");
                        fgets(mssv2, sizeof(mssv2), stdin);
                        trim(mssv2);
                        printf("\n");
                        findStudent(student, studentCount, mssv2);
                    }
                    else printf("Danh sach sinh vien rong!!\n");
                }
            }
        }
    }
    return 0;
}

//Student.xxx trả về kiểu char do mình muốn làm việc với kiểu dữ liệu là char
void trim(char *buffer){
    size_t pos = strcspn(buffer, "\n");
    buffer[pos] = '\0';
}

// Hàm nhập sinh viên
void addStudent(Student *sinhvien){
    printf("Nhap ho va ten: ");
    // Con trỏ tới struct Student => Student.name == char[100]
    fgets(sinhvien->name, sizeof(sinhvien->name), stdin);
    trim(sinhvien->name); 
    printf("Nhap lop: ");
    fgets(sinhvien->studentclass, sizeof(sinhvien->studentclass), stdin);
    trim(sinhvien->studentclass);
    printf("Nhap MSSV: ");
    fgets(sinhvien->mssv, sizeof(sinhvien->mssv), stdin);
    trim(sinhvien->mssv);
    //Cần đọc địa chỉ => địa chỉ của biến Student.age
    printf("Nhap GPA: ");
    scanf("%lf", &sinhvien->gpa);
    while(getchar() != '\n');
    printf("\n");
}

//không cần sửa dữ liệu thì không cần pointer.
//mà nếu hàm tạo bản sao của struct -> chậm hơn -> dùng pointer để lấy trực tiếp
// Hàm xuất sinh viên
void printStudent(const Student *sinhvien){
    //là   *sinhvien.name (địa chỉ ký tự đầu trong mảng)
    // tại name của sinhvien đó.
    printf("Ho va ten: %s\n", sinhvien->name); //đã tự là địa chỉ rồi (do array decay)
    printf("Lop: %s\n", sinhvien->studentclass);
    printf("MSSV: %s\n", sinhvien->mssv);
    printf("GPA: %.2lf\n", sinhvien->gpa);
    printf("\n");
}

//Sắp xếp sinh viên theo gpa dùng hàm qsort
int gpaCompa(const void *a, const void *b) {
    Student *x = (Student*)a; // phải cùng kiểu struct x = struct a
    Student *y = (Student*)b;
    if (x->gpa > y->gpa) return -1;// tại struct student x.gpa
    else if(x->gpa < y->gpa) return 1;
    return 0;
}

//Tìm sinh viên theo mssv
// mảng struct student vì đang làm việc với mảng đó.
void findStudent(const Student a[], int n, const char id[]){
    int found = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(a[i].mssv, id) == 0) {
         // truyền địa chỉ để con trỏ hàm print trỏ đến nó.
            printStudent(&a[i]);
            found = 1;
            break; //nhanh hon
        }
    }
    if(!found) printf("Khong tim thay sinh vien.\n");
    printf("\n");
}

//Xóa sinh viên khỏi danh sách theo mssv
void deleteStudent(Student student[], int *n, const char mssv[]) {
    for (int i = 0; i < *n; i++) {
        if (strcmp(student[i].mssv, mssv) == 0) {
            for (int j = i; j < *n - 1; j++) {
                student[j] = student[j + 1];
            }
            (*n)--;
            printf("Da xoa sinh vien voi mssv: %s.\n", mssv);
            return; // tránh duyệt tiếp
        }
    }
    printf("Khong tim thay sinh vien can xoa!\n");
}
