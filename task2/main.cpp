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

int term_new_setting()
{
    extern t_term *g_terminal;

    g_terminal = (t_term *)malloc(sizeof(t_term));
    g_terminal->fd = STDOUT_FILENO;

    tcgetattr(g_terminal->fd, &g_terminal->oldt);

    memcpy(&g_terminal->newt, &g_terminal->oldt, sizeof(g_terminal->oldt));
    g_terminal->newt.c_lflag &= ~(ICANON | ECHO | ECHONL | IEXTEN);
    g_terminal->newt.c_cc[VMIN] = 1;
    g_terminal->newt.c_cc[VTIME] = 0;
    return 0;
}

int term_set()
{
    extern t_term *g_terminal;

    if (tcsetattr(g_terminal->fd, TCSANOW, &g_terminal->newt) == -1)
        return error_msg("Termcap", "failed set new attributes in tcsetattr()");
    return 0;
}

void term_reset(void)
{
    extern t_term *g_terminal;

    g_terminal->oldt.c_lflag &= 0x200005cb;
    tcsetattr(g_terminal->fd, TCSANOW, &g_terminal->oldt);
}

int main()
{
    term_new_setting();

    std::vector<Department> company = parser_company();

    // extern std::list<std::vector<Department>> history;
    // history.push_back(company);

    std::vector<Menu> menu_list;
    menu_list.push_back(create_menu_main());
    menu_list.push_back(create_menu_department());
    menu_list.push_back(create_menu_employee());

    main_menu(&company, menu_list);

    return 0;
}
