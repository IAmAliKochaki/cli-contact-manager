#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "menu.h"
#include "contact_manager.h"

static void trim_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

static void add_contact_menu()
{
    printf("Enter the name:");
    char name[MAX_NAME] = {'0'};
    fgets(name, MAX_NAME, stdin);
    trim_newline(name);
    if (strlen(name) == 0) {
        printf("name cannot be null\n");
        return;
    }

    printf("Enter the phone:");
    char phone[MAX_PHONE] = {'0'};
    fgets(phone, MAX_PHONE, stdin);
    trim_newline(phone);
    if (strlen(phone) == 0) {
        printf("phone cannot be null\n");
        return;
    }

    printf("Enter the email:");
    char email[MAX_EMAIL] = {'0'};
    fgets(email, MAX_EMAIL, stdin);
    trim_newline(email);

    printf("Enter the address:");
    char address[MAX_ADDRESS] = {'0'};
    fgets(address, MAX_ADDRESS, stdin);
    trim_newline(address);

    add_contact(create_new_contact(name, phone, email, address));
}

static void delete_contact_menu()
{
    printf("Enter the name:");
    char name[MAX_NAME] = {'0'};
    fgets(name, MAX_NAME, stdin);
    trim_newline(name);

    delete_contact(name);
}

static void search_contact_menu()
{
    printf("Enter the name:");
    char name[MAX_NAME] = {'0'};
    fgets(name, MAX_NAME, stdin);
    trim_newline(name);

    search_contact(name);
}

static void view_all_contact_menu()
{
    view_all_contact();
}

static void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

static void clear_buffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ; // flush the newline
}

static void back_loop()
{
    printf("Enter 'b' for back\n");
    while (getchar() != 'b')
        ;
    clear_buffer();
}

void main_menu()
{
    while (1)
    {
        clear_screen();
        printf("1:  add contact\n");
        printf("2:  view all contacts\n");
        printf("3:  search contact\n");
        printf("4:  delete contact\n");
        printf("5:  quit\n");

        char option;
        option = getchar();
        clear_buffer();
        
        switch (option)
        {
        case '1':
            add_contact_menu();
            back_loop();
            break;
        case '2':
            view_all_contact_menu();
            back_loop();
            break;
        case '3':
            search_contact_menu();
            back_loop();
            break;
        case '4':
            delete_contact_menu();
            back_loop();
            break;
        case '5':
            return;
        default:
            clear_screen();
            printf("Invalid input!\n");
            usleep(1000000);
            break;
        }
    }
}
