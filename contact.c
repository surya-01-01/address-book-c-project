#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
void listContacts(AddressBook *addressBook)
{

    int choice;
    printf("\n\t\t\t...CONTACTS...\n");
    printf("%-20s\t%-20s\t%-20s\n", "NAME", "PHONE", "EMAIL");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("%-20s\t%-20s\t%-20s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    printf("\nBACK TO MAIN MENU(press 1)\t\tEXIT(press 2)\n");
    do
    {
        printf("Enter your choice :");
        scanf("%d", &choice);
        if (choice == 1)
            return;
        else if (choice == 2)
        {
            printf("\n...Thanks For Suppoting Us...\n...Have a Nice Day...\n");
            exit(EXIT_SUCCESS);
        }
        else
            printf("INVALID INPUT TRY AGAIN\n");
    } while (choice != 1);
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);

    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to

    exit(EXIT_SUCCESS); // Exit the program
}

void createContact(AddressBook *addressBook)
{
    int choice;
    char temp_name[50];
    char temp_phone[20];
    char temp_email[50];
    int i = 0, ret = 0;
    printf("\n\tCREATING A CONTACT\n");
    printf("Enter a name :");
    scanf(" %[^\n]", temp_name);
    do
    {
        printf("Enter a valid phone number :");
        scanf("%s", temp_phone);
        if (strlen(temp_phone) != 10)
        {
            printf("\t\tINVALID! please Enter 10 digits.\n");
        }
        else if (strlen(temp_phone) == 10)
        {
            while (temp_phone[i])
            {
                if (temp_phone[i] >= '0' && temp_phone[i] <= '9')
                    ret = 1;
                else
                {
                    ret = 0;
                    break;
                }
                i++;
            }
            i = 0;
            if (ret == 0)
                printf("\t\tINVALID! please use only 0-9 digits.\n");
            else if (ret)
            {
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(temp_phone, addressBook->contacts[i].phone) == 0)
                    {
                        printf("\t\tPHONE NUMBER ALREADY EXISTING...\n\t\tTRY AGAIN\n");
                        ret = 0;
                    }
                }
            }
        }
    } while (ret != 1);
    ret = 0;
    i = 0;
    do
    {
        printf("Enter a valid Email ID :");
        scanf("%s", temp_email);
        if (strstr(temp_email, ".com") == NULL || strchr(temp_email, '@') == NULL || temp_email[0] == '@' || strstr(temp_email,"@.")!=0)
        {
            printf("INVALID EMAIL..\n");
        }
        else
            ret = 2;

        if (ret == 2)
        {
            for (int i = 0; i < addressBook->contactCount; i++)
            {
                if (strcmp(temp_email, addressBook->contacts[i].email) == 0)
                {
                    printf("\t\tEMAIL ID ALREADY EXISTING...\n\t\tTRY AGAIN\n");
                    ret = 0;
                }
            }
        }
        else
        {
            printf("\t\tINVALID EMAIL ID...TRY AGAIN\n");
        }
    } while (ret != 2);
    strcpy(addressBook->contacts[addressBook->contactCount].name, temp_name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, temp_phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, temp_email);

    addressBook->contactCount++;
    printf("...CONTACT CREATED SUCESSFULLY...");
    printf("\nBACK TO MAIN MENU(press 1)\t\tEXIT(press 2)\n");
    do
    {
        printf("Enter your choice :");
        scanf("%d", &choice);
        if (choice == 1)
            return;
        else if (choice == 2)
        {
            printf("\n...Thanks For Suppoting Us...\n...Have a Nice Day...\n");
            exit(EXIT_SUCCESS);
        }
        else
            printf("INVALID INPUT TRY AGAIN\n");
    } while (choice != 1);
}

void searchContact(AddressBook *addressBook)
{
    int choice, ret = 0, count = 0, fur_search, fur_search1,fur=0;
    char temp_name[50];
    char temp_phone[20];
    char temp_email[50];
    printf("\n\tSEARCHING A CONTACT\n");
    do
    {
        printf("search by name(1)\nsearch by phone(2)\nsearch by email(3)\n");
        printf("Enter your choice :");
        scanf("%d", &choice);
        if (choice > 3)
        {
            printf("Invalid Iutput....Try again\n");
        }
        else
            ret = 1;
    } while (ret != 1);

    ret = 0;
    switch (choice)
    {
    case 1:
        printf("Enter the name to search:");
        scanf(" %[^\n]", temp_name);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, temp_name))
            {
                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                ret = 1;
                count++;
            }
        }
        if (ret != 1)
            printf("...CONTACT NOT FOUND...");
        else if (count > 1)
        {
            do
            {
                printf("NEED FURTHER SEARCH?\n");
                printf("YES(1)\t\tNO(2)\n");
                printf("Enter your option:");

                scanf("%d", &fur_search);
                if (fur_search <= 2)
                    count = 0;
            } while (count != 0);
            switch (fur_search)
            {
            case 1:
                do
                {
                    printf("SEARCH BY PHONE(1)\t\tSEARCH BY MAIL(2)\n");
                    printf("Enter your option:");
                    scanf("%d", &fur_search1);
                    if (fur_search1 == 1)
                    {
                        printf("enter phone number");
                        scanf(" %s", temp_phone);
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (strstr(addressBook->contacts[i].phone, temp_phone))
                            {
                                printf("...CONTACT FOUND...\n");
                                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                                fur = 1;
                            }
                        }
                        if (fur != 1)
                            printf("...CONTACT NOT FOUND...");
                    }
                    else if (fur_search1 == 2)
                    {
                        printf("Enter the email to search:");
                        scanf(" %s", temp_email);
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (strstr(addressBook->contacts[i].email, temp_email))
                            {
                                printf("...CONTACT FOUND...\n");
                                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                                fur = 1;
                            }
                        }
                        if (fur != 1)
                            printf("...CONTACT NOT FOUND...");
                    }

                } while (fur_search1 != 1 && fur_search1 != 2);

                break;
            case 2:
                break;
            }
        }
        break;
    case 2:
        printf("Enter the phone number to search:");
        scanf(" %s", temp_phone);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].phone, temp_phone))
            {
                printf("...CONTACT FOUND...\n");
                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                ret = 1;
            }
        }
        if (ret != 1)
            printf("...CONTACT NOT FOUND...");
        break;
    case 3:
        printf("Enter the email to search:");
        scanf(" %s", temp_email);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].email, temp_email))
            {
                printf("...CONTACT FOUND...\n");
                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                ret = 1;
            }
        }
        if (ret != 1)
            printf("...CONTACT NOT FOUND...");
        break;
    }

    printf("\nBACK TO MAIN MENU(press 1)\t\tEXIT(press 2)\n");
    do
    {
        printf("Enter your choice :");
        scanf("%d", &choice);
        if (choice == 1)
            return;
        else if (choice == 2)
        {
            printf("\n...Thanks For Suppoting Us...\n...Have a Nice Day...\n");
            exit(EXIT_SUCCESS);
        }
        else
            printf("INVALID INPUT TRY AGAIN\n");
    } while (choice != 1);
}

void editContact(AddressBook *addressBook)
{
    int temp, choice, ret = 0, i = 0, count=0, fur_search, fur_search1,store=0,fur=0;
    char temp_name[50];
    char temp_phone[20];
    char temp_email[50];
    printf("\n\tEDITING A CONTACT\n");
    do
    {
        printf("edit the name(1)\nedit the phone number(2)\nedit the email(3)\n");
        printf("Enter your choice :");
        scanf("%d", &choice);
        if (choice > 3)
        {
            printf("Invalid Iutput....Try again\n");
        }
        else
            ret = 1;
    } while (ret != 1);

    ret = 0;
    switch (choice)
    {
    case 1:
        printf("search a name to edit:");
        scanf(" %[^\n]", temp_name);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, temp_name))
            {
                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                ret = 1;
                temp = i;
                count++;
            }
        }
        if (ret != 1)
            printf("...CONTACT NOT FOUND...");
        else if (count > 1)
        {
            do
            {
                printf("NEED FURTHER SEARCH?\n");
                printf("YES(1)\t\tNO(2)\n");
                printf("Enter your option:");

                scanf("%d", &fur_search);
                if (fur_search <= 2)
                    count = 0;
            } while (count != 0);
            switch (fur_search)
            {
            case 1:
                do
                {
                    printf("SEARCH BY PHONE(1)\t\tSEARCH BY MAIL(2)\n");
                    printf("Enter your option:");
                    scanf("%d", &fur_search1);
                    if (fur_search1 == 1)
                    {
                        printf("enter phone number");
                        scanf(" %s", temp_phone);
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (strstr(addressBook->contacts[i].phone, temp_phone))
                            {
                                printf("...CONTACT FOUND...\n");
                                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                                fur=1;
                                store=i;
                            }
                        }
                        if (fur != 1)
                            printf("...CONTACT NOT FOUND...");
                        else
                        {
                                printf("Enter the new name:");
                                scanf(" %[^\n]", addressBook->contacts[store].name);
                                printf("...CONTACT EDITED SUCESSFULLY...");
                        }
                    }
                    else if (fur_search1 == 2)
                    {
                        printf("Enter the email to search:");
                        scanf(" %s", temp_email);
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (strstr(addressBook->contacts[i].email, temp_email))
                            {
                                printf("...CONTACT FOUND...\n");
                                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                                fur=1;
                            }
                        }
                        if (fur != 1)
                            printf("...CONTACT NOT FOUND...");
                        else
                        {
                                 printf("Enter the new name:");
                                scanf(" %[^\n]", addressBook->contacts[temp].name);
                                printf("...CONTACT EDITED SUCESSFULLY...");
                        }
                    }

                } while (fur_search1 != 1 && fur_search1 != 2);

                break;
            case 2:
                break;
            }
        }
        else
        {
            ret = 0;
            printf("Enter the new name:");
            scanf(" %[^\n]", addressBook->contacts[temp].name);
            printf("...CONTACT EDITED SUCESSFULLY...");
        }

        break;
    case 2:
        printf("search a phone number to edit:\n");
        scanf(" %s", temp_phone);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].phone, temp_phone))
            {
                printf("...CONTACT FOUND...\n");
                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                ret = 1;
                temp = i;
                break;
            }
        }
        if (ret != 1)
            printf("...CONTACT NOT FOUND...");
        else
        {
            do
            {
                printf("Enter a valid new phone number :");
                scanf("%s", temp_phone);
                if (strlen(temp_phone) != 10)
                {
                    printf("\t\tINVALID! please Enter 10 digits.\n");
                }
                else if (strlen(temp_phone) == 10)
                {
                    while (temp_phone[i])
                    {
                        if (temp_phone[i] >= '0' && temp_phone[i] <= '9')
                            ret = 1;
                        else
                        {
                            ret = 0;
                            break;
                        }
                        i++;
                    }
                    i = 0;
                    if (ret == 0)
                        printf("\t\tINVALID! please use only 0-9 digits.\n");
                    else if (ret)
                    {
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (i == temp)
                            {
                            }

                            else if (strcmp(temp_phone, addressBook->contacts[i].phone) == 0)
                            {
                                printf("\t\tPHONE NUMBER ALREADY EXISTING...\n\t\tTRY AGAIN\n");
                                ret = 0;
                            }
                        }
                    }
                }
            } while (ret != 1);
            strcpy(addressBook->contacts[temp].phone, temp_phone);
            printf("...CONTACT EDITED SUCESSFULLY...");
        }
        break;
    case 3:
        printf("search a email to edit:");
        scanf(" %s", temp_email);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].email, temp_email))
            {
                printf("...CONTACT FOUND...\n");
                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                ret = 1;
                temp = i;
                break;
            }
        }
        if (ret != 1)
            printf("...CONTACT NOT FOUND...");
        else
        {
            ret = 0;
            i = 0;
            do
            {
                printf("Enter a valid Email ID :");
                scanf("%s", temp_email);
                if (strstr(temp_email, ".com") == NULL || strchr(temp_email, '@') == NULL || temp_email[0] == '@')
                {
                    printf("INVALID EMAIL..\n");
                }
                else
                    ret = 2;

                if (ret == 2)
                {
                    for (int i = 0; i < addressBook->contactCount; i++)
                    {
                        if (i == temp)
                        {
                        }
                        else if (strcmp(temp_email, addressBook->contacts[i].email) == 0)
                        {
                            printf("\t\tEMAIL ID ALREADY EXISTING...\n\t\tTRY AGAIN\n");
                            ret = 0;
                        }
                    }
                }
                else
                {
                    printf("\t\tINVALID EMAIL ID...TRY AGAIN\n");
                }
            } while (ret != 2);
            strcpy(addressBook->contacts[temp].email, temp_email);
            printf("...CONTACT EDITED SUCESSFULLY...");
        }
        break;
    }
    printf("\nBACK TO MAIN MENU(press 1)\t\tEXIT(press 2)\n");
    do
    {
        printf("Enter your choice :");
        scanf("%d", &choice);
        if (choice == 1)
            return;
        else if (choice == 2)
        {
            printf("\n...Thanks For Suppoting Us...\n...Have a Nice Day...\n");
            exit(EXIT_SUCCESS);
        }
        else
            printf("INVALID INPUT TRY AGAIN\n");
    } while (choice != 1);
}

void deleteContact(AddressBook *addressBook)
{
    int temp, choice, ret = 0, i = 0, del = 0, count=0, fur_search, fur_search1,store=0,fur=0;
    char temp_name[50];
    char temp_phone[20];
    char temp_email[50];
    printf("\n\tDELETING A CONTACT\n");
    do
    {
        printf("search by name(1)\nsearch by phone number(2)\nesearch by email id(3)\n");
        printf("Enter your choice :");
        scanf("%d", &choice);
        if (choice > 3)
        {
            printf("Invalid Iutput....Try again\n");
        }
        else
            ret = 1;
    } while (ret != 1);

    ret = 0;
    switch (choice)
    {
    case 1:
        printf("search a name to delete:");
        scanf(" %[^\n]", temp_name);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].name, temp_name))
            {
                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                ret = 1;
                temp = i;
                count++;
            }
        }
        if (ret != 1)
            printf("...CONTACT NOT FOUND...\n");
        else if (count > 1)
        {
            do
            {
                printf("NEED FURTHER SEARCH?\n");
                printf("YES(1)\t\tNO(2)\n");
                printf("Enter your option:");

                scanf("%d", &fur_search);
                if (fur_search <= 2)
                    count = 0;
            } while (count != 0);
            switch (fur_search)
            {
            case 1:
                do
                {
                    printf("SEARCH BY PHONE(1)\t\tSEARCH BY MAIL(2)\n");
                    printf("Enter your option:");
                    scanf("%d", &fur_search1);
                    if (fur_search1 == 1)
                    {
                        printf("enter phone number");
                        scanf(" %s", temp_phone);
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (strstr(addressBook->contacts[i].phone, temp_phone))
                            {
                                printf("...CONTACT FOUND...\n");
                                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                                fur=1;
                                store=i;
                            }
                        }
                        if (fur != 1)
                            printf("...CONTACT NOT FOUND...");
                        else
                        {
                            printf("ARE YOU SURE TO DELETE??.\n");
                                do
                                {
                                    printf("Enter your choice\nyes(1)\t\tno(2)\n");
                                    printf("Enter your choice:");
                                    scanf(" %d", &del);
                                    if (del == 1)
                                    {
                                        ret = 1;
                                        for (int i = store; (i - 1) < addressBook->contactCount; i++)
                                        {
                                            addressBook->contacts[i] = addressBook->contacts[i + 1];
                                        }
                                        addressBook->contactCount--;
                                        printf("...CONTACT DELETED SUCESSFULLY...\n");
                                    }
                                    else if (del == 2)
                                    {
                                        printf("...CONTACT NOT DELETED...\n");
                                        return;
                                    }
                                    else
                                    {
                                        printf("Invalid input.....try again\n");
                                    }
                                } while (ret != 1);
                        }
                    }
                    else if (fur_search1 == 2)
                    {
                        printf("Enter the email to search:");
                        scanf(" %s", temp_email);
                        for (int i = 0; i < addressBook->contactCount; i++)
                        {
                            if (strstr(addressBook->contacts[i].email, temp_email))
                            {
                                printf("...CONTACT FOUND...\n");
                                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                                printf("ARE YOU SURE TO DELETE??.\n");
                                do
                                {
                                    printf("Enter your choice\nyes(1)\t\tno(2)\n");
                                    printf("Enter your choice:");
                                    scanf("%d", &del);
                                    if (del == 1)
                                    {
                                        ret = 1;
                                        for (int i = store; (i - 1) < addressBook->contactCount; i++)
                                        {
                                            addressBook->contacts[i] = addressBook->contacts[i + 1];
                                        }
                                        addressBook->contactCount--;
                                        printf("...CONTACT DELETED SUCESSFULLY...\n");
                                    }
                                    else if (del == 2)
                                    {
                                        printf("...CONTACT NOT DELETED...\n");
                                        return;
                                    }
                                    else
                                    {
                                        printf("Invalid input.....try again\n");
                                    }
                                } while (ret != 1);
                            }
                        }
                        if (ret != 1)
                            printf("...CONTACT NOT FOUND...");
                    }

                } while (fur_search1 != 1 && fur_search1 != 2);

                break;
            case 2:
                break;
            }
        }
        else
        {
            printf("ARE YOU SURE TO DELETE??.\n");
            do
            {
                printf("Enter your choice\nyes(1)\t\tno(2)\n");
                printf("Enter your choice:");
                scanf("%d", &del);
                if (del == 1)
                {
                    ret = 1;
                    for (int i = temp; (i - 1) < addressBook->contactCount; i++)
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--;
                    printf("...CONTACT DELETED SUCESSFULLY...\n");
                }
                else if (del == 2)
                {
                    printf("...CONTACT NOT DELETED...\n");
                    return;
                }
                else
                {
                    printf("Invalid input.....try again\n");
                }
            } while (ret != 1);
        }

        break;
    case 2:
        printf("search a phone number to delete:");
        scanf(" %s", temp_phone);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].phone, temp_phone))
            {
                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                ret = 1;
                temp = i;
                break;
            }
        }
        if (ret != 1)
            printf("...CONTACT NOT FOUND...\n");
        else
        {
            printf("ARE YOU SURE TO DELETE??.\n");
            do
            {
                printf("Enter your choice\nyes(1)\t\tno(2)\n");
                printf("Enter your choice:");
                scanf("%d", &del);
                if (del == 1)
                {
                    ret = 1;
                    for (int i = temp; (i - 1) < addressBook->contactCount; i++)
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--;
                    printf("...CONTACT DELETED SUCESSFULLY...\n");
                }
                else if (del == 2)
                {
                    printf("...CONTACT NOT DELETED...\n");
                    return;
                }
                else
                {
                    printf("Invalid input.....try again\n");
                }
            } while (ret != 1);
        }

        break;
    case 3:
        printf("search a email id to delete:");
        scanf(" %s", temp_email);
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strstr(addressBook->contacts[i].email, temp_email))
            {
                printf("%s\t\t%s\t\t%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                ret = 1;
                temp = i;
                break;
            }
        }
        if (ret != 1)
            printf("...CONTACT NOT FOUND...\n");
        else
        {
            printf("ARE YOU SURE TO DELETE??.\n");
            do
            {
                printf("Enter your choice\nyes(1)\t\tno(2)\n");
                printf("Enter your choice:");
                scanf("%d", &del);
                if (del == 1)
                {
                    ret = 1;
                    for (int i = temp; (i - 1) < addressBook->contactCount; i++)
                    {
                        addressBook->contacts[i] = addressBook->contacts[i + 1];
                    }
                    addressBook->contactCount--;
                    printf("...CONTACT DELETED SUCESSFULLY...\n");
                }
                else if (del == 2)
                {
                    printf("...CONTACT NOT DELETED...\n");
                    return;
                }
                else
                {
                    printf("Invalid input.....try again\n");
                }
            } while (ret != 1);
        }

        break;
    }
    printf("\nBACK TO MAIN MENU(press 1)\t\tEXIT(press 2)\n");
    do
    {
        printf("Enter your choice :");
        scanf("%d", &choice);
        if (choice == 1)
            return;
        else if (choice == 2)
        {
            printf("\n...Thanks For Suppoting Us...\n...Have a Nice Day...\n");
            exit(EXIT_SUCCESS);
        }
        else
            printf("INVALID INPUT TRY AGAIN\n");
    } while (choice != 1);
}
