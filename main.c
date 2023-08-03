#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int welcome_screen();
void book_ticket();
void view_bus();
void cancelling();

int main() {
	int choice;

menu:
    do {
        choice = welcome_screen();

        if (choice == 1) {
            book_ticket();
        } else if (choice == 2) {
            view_bus();
        } else if (choice == 3) {
            cancelling();
        } else if (choice == 4) {
            exit(0);
        } else {
            printf("Invalid choice!!! Press Any key to try again...");
            getchar();
            goto menu;
        }
    } while (choice != 4);

	return 0;
}

int welcome_screen() {
	int choice, i = 0;

	system("cls");
	printf("------------------------------------------------\n");
    printf("   >>> WELCOME TO BUS RESERVASION SERVICE <<<   \n");
    printf("------------------------------------------------\n\n");
    printf("1>> Book A Ticket\n");
    printf("2>> View Bus\n");
    printf("3>> Cancel Booking\n");
    printf("4>> Exit\n");
    printf("---->>> ");
    scanf("%d", &choice);

    return choice;
}


void book_ticket() {
	float cost;
	int choice, i = 0, num_of_seats, booked = 0, seating_choice;
	char states[255], bus_num[25];
	char* token;
	char* bus_status[32];

bus_list:
	system("cls");
	printf("========================================================================================================\n");
	printf("  BUS.NO\tNAME\t\t\t DESTINATIONS\t\t\tCHARGES\t\tTIME\n");
	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("   1   \t\tVIP VAN\t\t\tPhnom Penh To kampong cham\t   8.8$\t\t07:00 AM\n");
    printf("   2   \t\tStarix\t\t\tPhnom Penh To KamPot      \t   8.8$\t\t08:30 AM\n");
    printf("   3   \t\tLuxury Hotel Bus\tPhnom Penh To Battambang    \t  14.5$   \t12:00 PM\n");
    printf("   4   \t\tHotel Bus\t\tPhnom Penh To Seimreab    \t  17.5$\t\t03:30 AM\n");
    printf("   5   \t\tHotel Bus\t\tPhnom Penh To Beijing \t\t  15.0$\t\t07:00 PM\n");
    printf("   6   \t\tVIP VAN\t\t\tPhnom Penh To Koh Kong  \t  20.0$\t\t11:00 PM\n");
    printf("========================================================================================================\n\n");
    printf("Choose the bus number:> ");
    scanf("%d", &choice);

    while (choice < 1 || choice > 6) {
    	printf("Invalid Option... Press any key to continue...");
    	getchar();
    	getchar();
    	goto bus_list;
    }

    if (choice == 1) {
        strcpy(bus_num, "bus_seat01");
    	cost = 8.8;
    } else if (choice == 2) {
        strcpy(bus_num, "bus_seat02");
    	cost = 8.8;
    } else if (choice == 3) {
        strcpy(bus_num, "bus_seat03");
    	cost = 14.5;
    } else if (choice == 4) {
        strcpy(bus_num, "bus_seat04");
    	cost = 17.5;
    } else if (choice == 5) {
        strcpy(bus_num, "bus_seat05");
    	cost = 15.0;
    } else if (choice == 6) {
        strcpy(bus_num, "bus_seat06");
    	cost = 20;
    }

    FILE* busing;
    busing = fopen(bus_num, "r");

    fscanf(busing, "%s", states);
	fclose(busing);

	token = strtok(states, ",");

	while (token != NULL) {
		bus_status[i] = token;

		if (strcmp(token, "booked") == 0) {
			booked++;
		}

		token = strtok(NULL, ",");
		i++;
	}

	i = 0;

bus_seat:
	system("cls");
	printf("=====================================================================================================\n"
			"\t\t\t\t\tSeating Status\n"
			"-----------------------------------------------------------------------------------------------------\n");

    for (int j = 1; j <= 8; j++) {
    	i += 1;
    	if (i < 10) {
    		printf("\t\t0%d: [%s]\t", i, bus_status[i - 1]);
    	} else {
    		printf("\t\t%d: [%s]\t", i, bus_status[i - 1]);
    	}

    	i += 1;
		if (i < 10) {
    		printf("0%d: [%s]\t\t", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\t\t", i, bus_status[i - 1]);
    	}

    	i += 1;
    	if (i < 10) {
    		printf("0%d: [%s]\t", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\t", i, bus_status[i - 1]);
    	}

    	i += 1;
    	if (i < 10) {
    		printf("0%d: [%s]\n", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\n", i, bus_status[i - 1]);
    	}
    }

    i = 0;

    printf("\nHow many seat do you want?:> ");
    scanf("%d", &num_of_seats);

    cost *= num_of_seats;

    while (num_of_seats < 1 || num_of_seats > (32 - booked)) {
    	printf("Invalid choice or not number of seat available...\nPress Enter to try again...");
    	getchar();
    	getchar();
    	goto bus_seat;
    }

    for (int k = 0; k < num_of_seats; k++) {
    	printf("Enter the seat number: ");
    	scanf("%d", &seating_choice);

    	while (strcmp(bus_status[seating_choice - 1], "booked") == 0) {
    		printf("The seat is already booked or You\'ve already booked it.\nEnter another seat number: ");
    		scanf("%d", &seating_choice);
    	}

    	bus_status[seating_choice - 1] = "booked";
    }

    busing = fopen(bus_num, "w");
    fclose(busing);

    busing = fopen(bus_num, "a+");

    for (int k = 0; k < 32; k++) {
    	if (k == 31) {
    		fprintf(busing, "%s", bus_status[k]);
    	} else {
    		fprintf(busing, "%s,", bus_status[k]);
    	}
    }

    fclose(busing);

    time_t t = time(NULL);
    system("cls");

    FILE *reciept = fopen("reciept", "w");
    fclose(reciept);
    reciept = fopen("reciept", "a+");

    printf("--------------------------------------------------------------------\n");
    printf("  >>                            RECIEPT                         <<  \n");
    printf("--------------------------------------------------------------------\n");
    printf(" From HSSD Company\n");
    printf(" Customer service\n");
    printf(" Tel    : 1800 202020\n");
    printf(" Date   : %s\n", ctime(&t));
    printf(" BUS.NO : 1\n");
    printf("--------------------------------------------------------------------\n");
    // printf(" Customer name   : %s\n", name);
    printf(" Amount of seats : %d\n", num_of_seats);
    printf(" Customer Price  : %.2f$\n", cost);
    printf("--------------------------------------------------------------------\n");
    printf("\n\nPress Enter to continue...\n");
    getchar();
    getchar();

    i = 0;
}

void view_bus() {
    float cost;
	int choice, i = 0, num_of_seats, booked = 0, seating_choice, option;
	char states[255], bus_num[25];
	char* token;
	char* bus_status[32];

bus_list:
	system("cls");
	printf("========================================================================================================\n");
	printf("  BUS.NO\tNAME\t\t\t DESTINATIONS\t\t\tCHARGES\t\tTIME\n");
	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("   1   \t\tVIP VAN\t\t\tPhnom Penh To kampong cham\t   8.8$\t\t07:00 AM\n");
    printf("   2   \t\tStarix\t\t\tPhnom Penh To KamPot      \t   8.8$\t\t08:30 AM\n");
    printf("   3   \t\tLuxury Hotel Bus\tPhnom Penh To Battambang    \t  14.5$   \t12:00 PM\n");
    printf("   4   \t\tHotel Bus\t\tPhnom Penh To Seimreab    \t  17.5$\t\t03:30 AM\n");
    printf("   5   \t\tHotel Bus\t\tPhnom Penh To Beijing \t\t  15.0$\t\t07:00 PM\n");
    printf("   6   \t\tVIP VAN\t\t\tPhnom Penh To Koh Kong  \t  20.0$\t\t11:00 PM\n");
    printf("========================================================================================================\n\n");
    printf("Choose the bus number: ");
    scanf("%d", &choice);

    while (choice < 1 || choice > 6) {
    	printf("Invalid Option... Press any key to continue...");
    	getchar();
    	getchar();
    	goto bus_list;
    }

    if (choice == 1) {
        strcpy(bus_num, "bus_seat01");
    	cost = 7.7;
    } else if (choice == 2) {
        strcpy(bus_num, "bus_seat02");
    	cost = 7.7;
    } else if (choice == 3) {
        strcpy(bus_num, "bus_seat03");
    	cost = 10;
    } else if (choice == 4) {
        strcpy(bus_num, "bus_seat04");
    	cost = 15.5;
    } else if (choice == 5) {
        strcpy(bus_num, "bus_seat05");
    	cost = 7.7;
    } else if (choice == 6) {
        strcpy(bus_num, "bus_seat06");
    	cost = 20;
    }

    FILE* busing;
    busing = fopen(bus_num, "r");

    fscanf(busing, "%s", states);
	fclose(busing);

	token = strtok(states, ",");

	while (token != NULL) {
		bus_status[i] = token;

		if (strcmp(token, "booked") == 0) {
			booked++;
		}

		token = strtok(NULL, ",");
		i++;
	}

	i = 0;

bus_seat:
	system("cls");
	printf("=====================================================================================================\n"
			"\t\t\t\t\tSeating Status\n"
			"-----------------------------------------------------------------------------------------------------\n");

    for (int j = 1; j <= 8; j++) {
    	i += 1;
    	if (i < 10) {
    		printf("\t\t0%d: [%s]\t", i, bus_status[i - 1]);
    	} else {
    		printf("\t\t%d: [%s]\t", i, bus_status[i - 1]);
    	}

    	i += 1;
		if (i < 10) {
    		printf("0%d: [%s]\t\t", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\t\t", i, bus_status[i - 1]);
    	}

    	i += 1;
    	if (i < 10) {
    		printf("0%d: [%s]\t", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\t", i, bus_status[i - 1]);
    	}

    	i += 1;
    	if (i < 10) {
    		printf("0%d: [%s]\n", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\n", i, bus_status[i - 1]);
    	}
    }

    i = 0;

    printf("\n1>> Return to View Bus\n2>> Return to Main Menu\n>> ");
    scanf("%d", &option);

    while (option > 2 || option < 1 ) {
        printf("Invalid option. Try again...\n>> ");
        scanf("%d", &option);
    }

    if (option == 1) {
        view_bus();
    }
}

void cancelling() {
	float cost;
	int choice, i = 0, num_of_seats, booked = 0, seating_choice, option;
	char states[255], bus_num[25];
	char* token;
	char* bus_status[32];

bus_list:
	system("cls");
	printf("========================================================================================================\n");
	printf("  BUS.NO\tNAME\t\t\t DESTINATIONS\t\t\tCHARGES\t\tTIME\n");
	printf("--------------------------------------------------------------------------------------------------------\n");
	printf("   1   \t\tVIP VAN\t\t\tPhnom Penh To kampong cham\t   8.8$\t\t07:00 AM\n");
    printf("   2   \t\tStarix\t\t\tPhnom Penh To KamPot      \t   8.8$\t\t08:30 AM\n");
    printf("   3   \t\tLuxury Hotel Bus\tPhnom Penh To Battambang    \t  14.5$   \t12:00 PM\n");
    printf("   4   \t\tHotel Bus\t\tPhnom Penh To Seimreab    \t  17.5$\t\t03:30 AM\n");
    printf("   5   \t\tHotel Bus\t\tPhnom Penh To Beijing \t\t  15.0$\t\t07:00 PM\n");
    printf("   6   \t\tVIP VAN\t\t\tPhnom Penh To Koh Kong  \t  20.0$\t\t11:00 PM\n");
    printf("========================================================================================================\n\n");
    printf("Choose the bus number: ");
    scanf("%d", &choice);

    while (choice < 1 || choice > 6) {
    	printf("Invalid Option... Press any key to continue...");
    	getchar();
    	getchar();
    	goto bus_list;
    }

    if (choice == 1) {
        strcpy(bus_num, "bus_seat01");
    	cost = 7.7;
    } else if (choice == 2) {
        strcpy(bus_num, "bus_seat02");
    	cost = 7.7;
    } else if (choice == 3) {
        strcpy(bus_num, "bus_seat03");
    	cost = 10;
    } else if (choice == 4) {
        strcpy(bus_num, "bus_seat04");
    	cost = 15.5;
    } else if (choice == 5) {
        strcpy(bus_num, "bus_seat05");
    	cost = 7.7;
    } else if (choice == 6) {
        strcpy(bus_num, "bus_seat06");
    	cost = 20;
    }

    FILE* busing;
    busing = fopen(bus_num, "r");

    fscanf(busing, "%s", states);
	fclose(busing);

	token = strtok(states, ",");

	while (token != NULL) {
		bus_status[i] = token;

		if (strcmp(token, "empty") == 0) {
			booked++;
		}

		token = strtok(NULL, ",");
		i++;
	}

	i = 0;

bus_seat:
	system("cls");
	printf("=====================================================================================================\n"
			"\t\t\t\t\tSeating Status\n"
			"-----------------------------------------------------------------------------------------------------\n");

    for (int j = 1; j <= 8; j++) {
    	i += 1;
    	if (i < 10) {
    		printf("\t\t0%d: [%s]\t", i, bus_status[i - 1]);
    	} else {
    		printf("\t\t%d: [%s]\t", i, bus_status[i - 1]);
    	}

    	i += 1;
		if (i < 10) {
    		printf("0%d: [%s]\t\t", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\t\t", i, bus_status[i - 1]);
    	}

    	i += 1;
    	if (i < 10) {
    		printf("0%d: [%s]\t", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\t", i, bus_status[i - 1]);
    	}

    	i += 1;
    	if (i < 10) {
    		printf("0%d: [%s]\n", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\n", i, bus_status[i - 1]);
    	}
    }

    i = 0;

    printf("\nHow many seat do you want to cancel?:> ");
    scanf("%d", &num_of_seats);

    cost *= num_of_seats;

    while (num_of_seats < 1 || num_of_seats > (32 - booked)) {
    	printf("Invalid choice or number of seat does not match...\nPress Enter to try again...");
    	getchar();
    	getchar();
    	goto bus_seat;
    }

    for (int k = 0; k < num_of_seats; k++) {
    	printf("Enter the seat number: ");
    	scanf("%d", &seating_choice);

    	while (strcmp(bus_status[seating_choice - 1], "empty") == 0) {
    		printf("The seat is already empty or You\'ve alreadt cancelled it.\nEnter another seat number: ");
    		scanf("%d", &seating_choice);
    	}

    	bus_status[seating_choice - 1] = "empty";
    }

    busing = fopen(bus_num, "w");
    fclose(busing);

    busing = fopen(bus_num, "a+");

    for (int k = 0; k < 32; k++) {
    	if (k == 31) {
    		fprintf(busing, "%s", bus_status[k]);
    	} else {
    		fprintf(busing, "%s,", bus_status[k]);
    	}
    }

    fclose(busing);
    i = 0; 

    system("cls");
	printf("=====================================================================================================\n"
			"\t\t\t\t\tSeating Status\n"
			"-----------------------------------------------------------------------------------------------------\n");

    for (int j = 1; j <= 8; j++) {
    	i += 1;
    	if (i < 10) {
    		printf("\t\t0%d: [%s]\t", i, bus_status[i - 1]);
    	} else {
    		printf("\t\t%d: [%s]\t", i, bus_status[i - 1]);
    	}

    	i += 1;
		if (i < 10) {
    		printf("0%d: [%s]\t\t", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\t\t", i, bus_status[i - 1]);
    	}

    	i += 1;
    	if (i < 10) {
    		printf("0%d: [%s]\t", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\t", i, bus_status[i - 1]);
    	}

    	i += 1;
    	if (i < 10) {
    		printf("0%d: [%s]\n", i, bus_status[i - 1]);
    	} else {
    		printf("%d: [%s]\n", i, bus_status[i - 1]);
    	}
    }

    i = 0;

    printf("\n\n1>> Continue cancel other bus...\n2>> Return to main menu\n>> ");
    scanf("%d", &option);

    while (option < 1 || option > 2) {
        printf("\nInvalid Choice. Try again...\n>> ");
        scanf("%d", &option);
    }

    if (option == 1) {
        cancelling();
    }
}