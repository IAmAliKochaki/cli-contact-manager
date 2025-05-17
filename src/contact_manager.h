#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "contact.h"

void run();
void add_contact(Contact contact);
void view_all_contact();
void search_contact(char *name);
void delete_contact(char *name);

#endif // UTILS_H
