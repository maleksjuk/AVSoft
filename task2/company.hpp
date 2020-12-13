#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <cctype>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

// for parser XML-file
#include "pugixml.hpp"
#include "pugiconfig.hpp"

using namespace std;

#define XML_FILE "tst.xml"

#define SLEEP_WAIT 200000
#define BUFF_SIZE 255

#define INDENT_DEPARTMENT "  "
#define INDENT_EMPLOYEE   "    "

#define CLR_RESET   "\033[0m"
#define CLR_BOLD    "\033[1m"
#define CLR_INVERSE "\033[7m"

#define CLR_RED     "\033[31m"
#define CLR_GREEN   "\033[32m"
#define CLR_YELLOW  "\033[33m"
#define CLR_BLUE    "\033[34m"
#define CLR_MAGENTA "\033[35m"
#define CLR_CYAN    "\033[36m"

typedef struct s_term
{
    int             fd;
    struct termios  oldt;
    struct termios  newt;
} t_term;

static t_term *g_terminal;

class Employee
{
private:
    string  surname;
    string  name;
    string  middleName;
    string  function_role;
    int     salary;

public:
    Employee(string _surname, string _name, string _middleName, 
             string _function, int _salary);

    string  getSurname();
    string  getName();
    string  getMiddleName();
    string  getFunction();
    int     getSalary();

    string  getFIO();

    void setSurname(string _surname);
    void setName(string _name);
    void setMiddleName(string _middleName);
    void setFunction(string _function);
    void setSalary(int _salary);

    void printer();
};


class Department
{
private:
    string              name;
    int                 count_employee;
    float               mean_salary;
    vector<Employee>    employments;

public:
    Department(string _name);

    string  getName();
    int     getCount();
    float   getMeanSalary();

    void setName(string _name);

    vector<Employee> getEmployment();

    void addEmployee(string _surname, string _name, string _middleName,
                     string _function, int _salary);
    void delEmployee(string FIO);
    void editEmployee(int id, char cmd, string new_value);

    void printer();
};


class Menu
{
private:
    string title;
    map<char, string> actions;
public:
    Menu(string _title);
    string getTitle();
    void addAction(char c, string action);
    void printer();
};


// main.cpp
int     error_msg(std::string block, std::string msg);
void    print_company(vector<Department> &company);
int     term_set();
void    term_reset(void);

// parser.cpp
vector<Department> parser_company();

// menu.cpp
Menu    create_menu_main();
Menu    create_menu_department();
Menu    create_menu_employee();

void    main_menu(vector<Department> &company, vector<Menu> &menu_list);
void    menu_department(vector<Department> &company, vector<Menu> &menu_list, int id);
void    menu_employee(Department &department, vector<Menu> &menu_list, int id);

// department.cpp
void    delete_department(vector<Department> &company, string name);
void    edit_department(vector<Department> &company, string name_old, string name_new);
void    add_department(vector<Department> &company, string _name);

#endif
