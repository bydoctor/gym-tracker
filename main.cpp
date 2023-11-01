#include <iostream>
#include "Person.h"
#include <ctype.h>
void main_menu();

void selection_handler(int selection)
{
    switch (selection)
    {
    case 1:
        create_person();
        main_menu();
    case 2:
        view_person_list();
        main_menu();
    case 3:
        view_calculations();
        main_menu();
    case 4:
        update_person();
        main_menu();
    case 5:
        delete_person();
        main_menu();
    case 6:
        exit(0);
    default:
        std::cout << "\nSorry. Wrong selection. Try again !\n"
                  << std::endl;
        main_menu();
    }
}
void main_menu()
{
    int selection{};
    std::cout << "1 - Create Person " << std::endl;
    std::cout << "2 - View Person List " << std::endl;
    std::cout << "3 - View Calculations " << std::endl;
    std::cout << "4 - Update Person " << std::endl;
    std::cout << "5 - Delete Person" << std::endl;
    std::cout << "6- Exit" << std::endl;
    std::cout << "\nPlease enter your selection --> ";
    std::cin >> selection;

    if (!std::cin >> selection)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    selection_handler(selection);
}

int main()
{
    main_menu();

    return 0;
}