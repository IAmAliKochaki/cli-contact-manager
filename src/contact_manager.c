#include <stdio.h>
#include <stdlib.h>
#include "contact.h"
#include "menu.h"

#define MAX_CONTACTS 100

const char *FILE_NAME = "../db/contacts.dat";

Contact *contacts = NULL;
int contact_count = 0;

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
    if (!file)
    {
        perror("Error opening file for writing");
        return;
    }

    fwrite(&contact_count, sizeof(int), 1, file);           // Save number of contacts first
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
    if (!file)
    {
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

void add_contact(Contact new_contact)
{
    // If full.
    if (contact_count >= MAX_CONTACTS)
        printf("Error: Cannot add contact. Contact list is full (max %d contacts).\n", MAX_CONTACTS);

    // Check the phone number already exists.
    else if (!is_phone_unique(new_contact.phone))
        printf("Error: Cannot add contact. Phone number '%s' already exists.\n", new_contact.phone);

    else
    {
        for (int i = 0; i < contact_count; i++)
        {
            if (strcmp(contacts[i].name, new_contact.name) > 0)
            {
                for (int j = contact_count - 1; j >= i; j--)
                    contacts[j + 1] = contacts[j];
                contacts[i] = new_contact;
                contact_count++;
                save(FILE_NAME);
                return;
            }
        }
        // If name is greater than all existing ones.
        contacts[contact_count++] = new_contact;
        save(FILE_NAME);
    }
}

void delete_contact(char *name)
{
    int contact_index = find_contact_by_name(name);
    // if contact does not exist
    if (contact_index == -1)
        printf("Error: Contact with name '%s' not found.\n", name);
    else
    {
        for (int i = contact_index; i < contact_count - 1; i++)
            contacts[i] = contacts[i + 1];
        contact_count--;
        save(FILE_NAME);
        printf("Success: Contact '%s' has been deleted.\n", name);
    }
}

void search_contact(char *name)
{
    int contact_index = find_contact_by_name(name);
    // if contact does not exist
    if (contact_index == -1)
        printf("Error: Contact with name '%s' not found.\n", name);
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
