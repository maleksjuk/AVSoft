#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <cctype>
#include <map>
#include <string>

#ifdef __linux__
    #include <cstring>
#endif

#include <vector>
#include <list>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

// for parser XML-file
#include "pugixml.hpp"
#include "pugiconfig.hpp"

#define XML_FILE "tst.xml"

#define SLEEP_WAIT 200000
#define BUFF_SIZE 255
#define HISTORY_SIZE 100

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


class Employee
{
private:
    std::string surname;
    std::string name;
    std::string middleName;
    std::string function_role;
    int         salary;

public:
    Employee(std::string _surname, std::string _name, std::string _middleName, 
             std::string _function, int _salary);

    std::string getSurname();
    std::string getName();
    std::string getMiddleName();
    std::string getFunction();
    int         getSalary();

    std::string getFIO();

    void setSurname(std::string _surname);
    void setName(std::string _name);
    void setMiddleName(std::string _middleName);
    void setFunction(std::string _function);
    void setSalary(int _salary);

    void printer();
};


class Department
{
private:
    std::string             name;
    int                     count_employee;
    float                   mean_salary;
    std::vector<Employee>   employments;

public:
    Department(std::string _name);

    std::string getName();
    int         getCount();
    float       getMeanSalary();

    void setName(std::string _name);

    std::vector<Employee> getEmployment();

    void addEmployee(std::string _surname, std::string _name, std::string _middleName,
                     std::string _function, int _salary);
    void delEmployee(std::string FIO);
    void editEmployee(int id, char cmd, std::string new_value);

    void printer();
};


class Menu
{
private:
    std::string                 title;
    std::map<char, std::string> actions;
public:
    Menu(std::string _title);
    std::string getTitle();
    void addAction(char c, std::string action);
    void printer();
};


typedef struct s_term
{
    int             fd;
    struct termios  oldt;
    struct termios  newt;
} t_term;

typedef struct s_history
{
    std::vector<Department> company;
    struct s_history        *prev;
    struct s_history        *next;
} t_history;

static t_history    *history;
static t_term       *g_terminal;


// main.cpp
int         error_msg(std::string block, std::string msg);
void        print_company(std::vector<Department> &company);
t_history   *save_to_history(t_history *current, std::vector<Department> company);

// terminal.cpp
int     term_new_setting();
int     term_set();
void    term_reset(void);

// parser.cpp
std::vector<Department> parser_company();

// menu_init.cpp
Menu    create_menu_main();
Menu    create_menu_department();
Menu    create_menu_employee();

// menu_process.cpp
void    main_menu(std::vector<Department> *company, std::vector<Menu> &menu_list);
void    menu_department(std::vector<Department> *company, std::vector<Menu> &menu_list, int id);
void    menu_employee(std::vector<Department> *company, Department &department, std::vector<Menu> &menu_list, int id);

// department.cpp
void    delete_department(std::vector<Department> &company, std::string name);
void    edit_department(std::vector<Department> &company, std::string name_old, std::string name_new);
void    add_department(std::vector<Department> &company, std::string _name);

#endif
