#include "company.hpp"

Menu::Menu(std::string _title){
    title = _title;
}

std::string Menu::getTitle(){
    return title;
}

void Menu::addAction(char c, std::string action)
{
    if (!actions.count(c))
        actions.insert({c, action});
    else
        actions[c] = action;
}

void Menu::printer()
{
    std::cout
        << "____________________\n"
        << CLR_MAGENTA << getTitle() << CLR_RESET << std::endl;
    for (auto &action : actions)
        std::cout << action.first << " --> " << action.second << std::endl;
    std::cout
        << "^^^^^^^^^^^^^^^^^^^^\n" << std::endl;
}

Menu create_menu_main()
{
    Menu menu("ГЛАВНОЕ МЕНЮ");
    menu.addAction('x', "выйти");
    menu.addAction('p', "распечатать всё предприятие");
    menu.addAction('c', "выбрать подразделение");
    menu.addAction('a', "добавить подразделение");
    menu.addAction('r', "удалить подразделение");
    menu.addAction('b', "отменить последнее изменение");
    return menu;
}

Menu create_menu_department()
{
    Menu menu("МЕНЮ ПОДРАЗДЕЛЕНИЯ");
    menu.addAction('x', "вернуться в главное меню");
    menu.addAction('p', "распечатать подразделение");
    menu.addAction('n', "переименовать подразделение");
    menu.addAction('c', "выбрать сотрудника");
    menu.addAction('a', "добавить сотрудника");
    menu.addAction('r', "удалить сотрудника");
    return menu;
}

Menu create_menu_employee()
{
    Menu menu("МЕНЮ СОТРУДНИКА");
    menu.addAction('x', "вернуться в меню подразделения");
    menu.addAction('p', "распечатать данные о сотруднике");
    menu.addAction('1', "изменить фамилию");
    menu.addAction('2', "изменить имя");
    menu.addAction('3', "изменить отчество");
    menu.addAction('4', "изменить должность");
    menu.addAction('5', "изменить зарплату");
    return menu;
}
