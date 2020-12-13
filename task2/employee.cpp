#include "company.hpp"

Employee::Employee(string _surname, string _name, string _middleName, 
                   string _function, int _salary)
{
    surname = _surname;
    name = _name;
    middleName = _middleName;
    function_role = _function;
    salary = _salary;
}

string Employee::getSurname(){
    return surname;
}

string Employee::getName(){
    return name;
}

string Employee::getMiddleName(){
    return middleName;
}

string Employee::getFunction(){
    return function_role;
}

int Employee::getSalary(){
    return salary;
}

string Employee::getFIO(){
    return surname + " " + name + " " + middleName;
}

void Employee::setSurname(string _surname){
    surname = _surname;
}

void Employee::setName(string _name){
    name = _name;
}

void Employee::setMiddleName(string _middleName){
    middleName = _middleName;
}

void Employee::setFunction(string _function){
    function_role = _function;
}

void Employee::setSalary(int _salary){
    salary = _salary;
}

void Employee::printer()
{
    cout << CLR_YELLOW << INDENT_EMPLOYEE 
        << "ФИО: " << getFIO()
        << CLR_RESET << endl;
    cout << INDENT_EMPLOYEE << "    Должность: " << function_role << endl;
    cout << INDENT_EMPLOYEE << "    Зарплата: " << salary << endl;
}
