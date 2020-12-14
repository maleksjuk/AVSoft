#include "company.hpp"

Employee::Employee(std::string _surname, std::string _name, std::string _middleName, 
                   std::string _function, int _salary)
{
    surname = _surname;
    name = _name;
    middleName = _middleName;
    function_role = _function;
    salary = _salary;
}

std::string Employee::getSurname(){
    return surname;
}

std::string Employee::getName(){
    return name;
}

std::string Employee::getMiddleName(){
    return middleName;
}

std::string Employee::getFunction(){
    return function_role;
}

int Employee::getSalary(){
    return salary;
}

std::string Employee::getFIO(){
    return surname + " " + name + " " + middleName;
}

void Employee::setSurname(std::string _surname){
    surname = _surname;
}

void Employee::setName(std::string _name){
    name = _name;
}

void Employee::setMiddleName(std::string _middleName){
    middleName = _middleName;
}

void Employee::setFunction(std::string _function){
    function_role = _function;
}

void Employee::setSalary(int _salary){
    salary = _salary;
}

void Employee::printer()
{
    std::cout << CLR_YELLOW << INDENT_EMPLOYEE 
        << "ФИО: " << getFIO()
        << CLR_RESET << std::endl;
    std::cout << INDENT_EMPLOYEE
        << "    Должность: " << function_role
        << std::endl;
    std::cout << INDENT_EMPLOYEE
        << "    Зарплата: " << salary
        << std::endl;
}
