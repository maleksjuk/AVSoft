#include "company.hpp"

int error_msg(std::string block, std::string msg)
{
    std::cout << "\033[31m[ошибка]\033[m " << block << ": " << msg << std::endl;
    return 1;
}

void print_company(std::vector<Department> &company)
{
    for (auto &dep : company)
    {
        dep.printer();
        std::cout << std::endl;
    }
}

t_history *save_to_history(t_history *current, std::vector<Department> company)
{
    t_history *new_hist;

    new_hist = (t_history *)malloc(sizeof(t_history));
    new_hist->company.assign(company.begin(), company.end());
    new_hist->prev = current;
    new_hist->next = NULL;

    if (current)
        current->next = new_hist;

    return new_hist;
}

void clear_history()
{
    while (history->next)
        history = history->next;
    while (history->prev)
    {
        history = history->prev;
        free(history->next);
    }
    if (history)
        free(history);
}

int main()
{
    term_new_setting();

    std::vector<Department> company = parser_company();

    // history = save_to_history(NULL, company);
    // std::vector<Department> *company_main = &(history->company);

    std::vector<Menu> menu_list;
    menu_list.push_back(create_menu_main());
    menu_list.push_back(create_menu_department());
    menu_list.push_back(create_menu_employee());

    main_menu(&company, menu_list);
    // main_menu(company_main, menu_list);

    // clear_history();
    return 0;
}
