#include <stdio.h>
#include <stdlib.h>
#include "contact.h"
#include "menu.h"

#define MAX_CONTACTS 100

const char *FILE_NAME = "../db/contacts.dat";

Contact *contacts = NULL;
int contact_count;


static int is_phone_unique(char *phone)
{
    for (int i = 0; i < contact_count; i++)
        if (strcmp(contacts[i].phone, phone) == 0)
            return 0;
    return 1;
}

static void save(const char *filename)
{
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    fwrite(&contact_count, sizeof(int), 1, file);  // Save number of contacts first
    fwrite(contacts, sizeof(Contact), contact_count, file); // Save contact data
    fclose(file);
}

static int is_file_empty(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return -1; // error
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    return size == 0; // 1 if empty, 0 if not
}

static void load(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file for reading");
        return;
    }

    fread(&contact_count, sizeof(int), 1, file);

    fread(contacts, sizeof(Contact), contact_count, file);
    fclose(file);
}

static int find_contact_by_name(char *name)
{
    // Binary search
    int low = 0, high = contact_count - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (strcmp(contacts[mid].name, name) == 0)
            return mid;

        if (strcmp(contacts[mid].name, name) < 0)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return -1;
}

int add_contact(Contact new_contact)
{
    // IF FULL
    if (contact_count >= MAX_CONTACTS)
    {
        // TO_DO: complete the error message
        printf("error\n");
        return -1;
    }
    // Check the number is not already exist.
    if (!is_phone_unique(new_contact.phone))
    {
        // TO_DO: complete the error message
        printf("error\n");
        return -1;
    }
    for (int i = 0; i < contact_count; i++)
    {
        if (strcmp(contacts[i].name, new_contact.name) > 0)
        {
            for (int j = contact_count - 1; j >= i; j--)
                contacts[j + 1] = contacts[j];
            contacts[i] = new_contact;
            contact_count++;
            save(FILE_NAME);
            return 1;
        }
    }
    // If name is greater than all existing ones
    contacts[contact_count++] = new_contact;
    save(FILE_NAME);
    return 1;
}

void delete_contact(char *name)
{
    int contact_index = find_contact_by_name(name);
    // if contact not exist
    if (contact_index == -1)
        // TO_DO: complete the error message
        printf("error\n");
    else
    {
        for (int i = contact_index; i < contact_count - 1; i++)
            contacts[i] = contacts[i + 1];
        contact_count--;
        save(FILE_NAME);
        // TO_DO: complete the message
        printf("success!\n");
    }
}

void search_contact(char *name)
{
    int contact_index = find_contact_by_name(name);
    // if contact not exist
    if (contact_index == -1)
        // TO_DO: complete the error message
        printf("error\n");
    else
        print_contact(contacts[contact_index]);
}

void view_all_contact()
{
    for (int i = 0; i < contact_count; i++)
    {
        printf("%d:\n", i + 1);
        print_contact(contacts[i]);
    }
}

void run()
{
    contacts = (Contact *)malloc(MAX_CONTACTS * sizeof(Contact));

    load(FILE_NAME);
        
    main_menu();
    
    free(contacts);
}
