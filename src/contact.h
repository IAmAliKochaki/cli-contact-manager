#ifndef CONTACT_H
#define CONTACT_H

#include <string.h>

#define MAX_NAME        64
#define MAX_PHONE       16
#define MAX_EMAIL       128
#define MAX_ADDRESS     256

typedef struct
{
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char email[MAX_EMAIL];
    char address[MAX_ADDRESS];

} Contact;


static inline Contact create_new_contact(char *name, char *phone, char *email, char *address)
{
    Contact new_contact;

    strncpy(new_contact.name, name, MAX_NAME - 1);
    new_contact.name[MAX_NAME - 1] = '\0';

    strncpy(new_contact.phone, phone, MAX_PHONE - 1);
    new_contact.phone[MAX_PHONE - 1] = '\0';

    strncpy(new_contact.email, email, MAX_EMAIL - 1);
    new_contact.email[MAX_EMAIL - 1] = '\0';

    strncpy(new_contact.address, address, MAX_ADDRESS - 1);
    new_contact.address[MAX_ADDRESS - 1] = '\0';

    return new_contact;
}


static inline void print_contact(Contact contact)
{
    printf("\tname:\t%s\n", contact.name);
    printf("\tphone:\t%s\n", contact.phone);
    printf("\temail:\t%s\n", contact.email);
    printf("\taddress:\t%s\n", contact.address);
}

#endif // CONTACT_H
