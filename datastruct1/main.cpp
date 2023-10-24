#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<sstream>

using namespace std;

class Person {
public:
    string No;
    string Name;

    Person();

    ~Person();

    string getNo();

    string getName();

    void setNo(string No);

    void setName(string Name);

    virtual void print() = 0;
    //virtual string toString() = 0;
    //virtual void stringtoClass(string strclass) = 0;
};

Person::Person() {
    this->No = "p1";
    this->Name = "p2";
}

Person::~Person() {}

string Person::getNo() {
    return this->No;
}

string Person::getName() {
    return this->Name;
}

void Person::setNo(string No) {
    this->No = No;
}

void Person::setName(string Name) {
    this->Name = Name;
}

//---------------------------------student class---------------------
class Student : public Person {
private:
    int Age;
public:
    Student();

    Student(string no, string name, int age);

    ~Student();

    void print();

    void setAge(int Age);

    int getAge();
};

Student::Student() {
    this->Age = 19;
}

Student::~Student() {}

Student::Student(string no, string name, int age) {
    this->No = no;
    this->Name = name;
    this->Age = age;
}

void Student::print() {
    cout << endl;
    cout << "Student No: " << this->No << ";\t";
    cout << "Student Name: " << this->Name << ";\t";
    cout << "Student Age: " << this->Age << ";\t";
    cout << endl;
}

void Student::setAge(int Age) {
    this->Age = Age;
}

int Student::getAge() {
    return this->Age;
}


//-------------------------Teacher class------------------------------
class Teacher : public Person {
private:
    float Salary;
    string Title;
public:
    Teacher();

    Teacher(string no, string name, float Salary, string Title);

    ~Teacher();

    void print();

    void setSalary(float Salary);

    float getSalary();

    void setTitle(string Title);

    string getTitle();
};

Teacher::Teacher() {
    this->Salary = 0.0;
    this->Title = "no title";
}

Teacher::~Teacher() {}

Teacher::Teacher(string no, string name, float Salary, string Title) {
    this->No = no;
    this->Name = name;
    this->Salary = Salary;
    this->Title = Title;
}

void Teacher::print() {
    cout << endl;
    cout << "Teacher No: " << this->No << ";\t";
    cout << "Teacher Name: " << this->Name << ";\t";
    cout << "Teacher Salary: " << this->Salary << ";\t";
    cout << "Teacher Title: " << this->Title << ";\t";
    cout << endl;
}

void Teacher::setSalary(float Salary) {
    this->Salary = Salary;
}

float Teacher::getSalary() {
    return this->Salary;
}

void Teacher::setTitle(string Title) {
    this->Title = Title;
}

string Teacher::getTitle() {
    return this->Title;
}


//----------------Sequence list class-----------------
template<typename DataType>
class SeqList {
private:
    DataType *Data;
    int Length;
    int MaxSize;
    static int IniSize;//初始化最大容量
    static int AddSize;//扩增容量
    //DataType Data[IniSize];
    //int Length;
public:
    SeqList();

    SeqList(DataType Data[], int Length);

    ~SeqList();

    int getlength();

    void printSeqList();

    void insert(int index, DataType DT);

    int find(string name);

    //int find(string findstr, int type);
    int remove(int index);
    //void save(string fn);
    //void load(string filename);
};

template<typename DataType> int SeqList<DataType>::IniSize = 1;
template<typename DataType> int SeqList<DataType>::AddSize = 1;

template<typename DataType>
SeqList<DataType>::SeqList() {
    MaxSize = IniSize;
    Data = new DataType[MaxSize];
    Length = 0;
}

template<typename DataType>
SeqList<DataType>::SeqList(DataType Data[], int Length) {
    // 初始化最大容量
    MaxSize = IniSize + AddSize;
    // 如果实际长度大于最大容量，根据实际长度重新确定最大容量
    if (Length > MaxSize) {
        MaxSize = Length + AddSize;
    }
    // 创建数组
    this->Data = new DataType[MaxSize];
    // 长度赋值
    this->Length = Length;
    // copy数据
    for (int i = 0; i < Length; i++) {
        this->Data[i] = Data[i];
    }
}


template<typename DataType>
SeqList<DataType>::~SeqList() {
    delete Data;
}

template<typename DataType>
int SeqList<DataType>::getlength() {
    return this->Length;
}

template<typename DataType>
void SeqList<DataType>::printSeqList() {
    cout << "------SeqList info--------" << endl;
    cout << "The length is  :" << this->Length << endl;
    cout << "The MaxSize is :" << this->MaxSize << endl;
    cout << "The list  is: " << endl;
    for (int i = 0; i < this->Length; i++) {
        this->Data[i].print();
    }
    cout << "----------------------------" << endl;
}

template<typename DataType>
void SeqList<DataType>::insert(int index, DataType DT) {
    //判断索引是否溢出
    if (index < 0 || index > Length) {
        cout << "Index out of range" << endl;
        return;
    }
    //判断是否需要扩容
    if (Length == MaxSize) {
        //扩容
        MaxSize += AddSize;
        //创建新数组
        DataType *newData = new DataType[MaxSize];
        //迁移数据
        for (int i = 0; i < Length; i++) {
            newData[i] = Data[i];
        }
        //删除旧数据
        delete Data;
        //赋值
        Data = newData;
    }
    //index后的数据后移，使用倒序循环
    for (int i = Length - 1; i >= index; i--) {
        Data[i + 1] = Data[i];
    }
    //插入
    Data[index] = DT;
    //改变长度
    Length++;
}

template<typename DataType>
int SeqList<DataType>::find(string findstr) {
    //遍历求解
    for (int i = 0; i < Length; ++i) {
        if (Data[i].getName() == findstr) {
            return i;
        }
    }
    return -1;
}

template<typename DataType>
int SeqList<DataType>::remove(int index) {
    if (index < 0 || index >= Length) {
        cout << "index is out of bounds" << endl;
        return -1;
    }
    //数据前移
    for (int i = 0; i < Length - 1; ++i) {
        Data[i] = Data[i + 1];
    }
    Length--;
    return 0;
}

/*
template <typename DataType>
void SeqList<DataType>::save(string fn)
{

}

template <typename DataType>
void SeqList<DataType>::load(string filename)
{

}
*/

int main() {

    Student a("No0001", "Xiao Wang", 17);
    Student a1("No0002", "Xiao Li", 18);
    Student a2("No0003", "Xiao Hong", 19);
    Student a3("No0004", "Xiao Zhang", 20);
    Teacher t("NoT1", "Xiao Huang", 120000, "lecturer");
    Teacher t1("NoT2", "Xiao Chen", 130000, "lecturer");
    Teacher t2("NoT3", "Xiao Bai", 300000, "full professor");
    Teacher t3("NoT4", "Xiao Tan", 200000, "associate professor");
    Student aa[] = {a, a1, a2};
    Teacher tt[] = {t, t1, t2};

    SeqList<Student> Studentlist(aa, 3);
    SeqList<Teacher> Teacherlist(tt, 3);

    Teacherlist.insert(2, t3);
    Teacherlist.printSeqList();
    Teacherlist.find("Xiao Bai");

    Studentlist.insert(2, a3);
    Studentlist.printSeqList();
    Studentlist.find("Xiao Zhang");
    Studentlist.remove(1);
    Studentlist.printSeqList();

    //Studentlist.save("student.txt");
    //Teacherlist.save("teacher.txt");


    /*
    SeqList<Student> Studentlist;
    SeqList<Teacher> Teacherlist;
    Studentlist.load("student.txt");
    Teacherlist.load("teacher.txt");
    Studentlist.printSeqList();
    Teacherlist.printSeqList();
    */

    return 0;
}
