#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct movie {
    char name[50];
    int duration;
    int price;
};

struct user {
    char name[50];
    int age;
    char phone[20];
    char email[50];
    char password[20];
    int ticket_count;
    struct movie booked_movies[10];
};

void display_movies() {
    struct movie movies[3] = {
        {"The Godfather", 175, 150},
        {"The Dark Knight", 152, 130},
        {"Star Wars: Episode IV - A New Hope", 121, 120}
    };
    printf("\nCurrent Movies:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. %s (Duration: %d min, Price: Rs.%d)\n", i+1, movies[i].name, movies[i].duration, movies[i].price);
    }
}

void register_user(struct user *u) {
    printf("\nEnter Name: ");
    scanf("%s", u->name);
    printf("Enter Age: ");
    scanf("%d", &u->age);
    printf("Enter Phone Number: ");
    scanf("%s", u->phone);
    printf("Enter Email: ");
    scanf("%s", u->email);
    printf("Enter Password: ");
    scanf("%s", u->password);
    u->ticket_count = 0;
    printf("Registration Successful!\n");
}

int login_user(struct user *u) {
    char email[50], password[20];
    printf("\nEnter Email: ");
    scanf("%s", email);
    printf("Enter Password: ");
    scanf("%s", password);
    if (strcmp(u->email, email) == 0 && strcmp(u->password, password) == 0) {
        printf("Login Successful!\n");
        return 1;
    }
    printf("Invalid Email or Password!\n");
    return 0;
}

void book_ticket(struct user *u) {
    int movie_choice, num_tickets;
    printf("\nEnter the Movie Number: ");
    scanf("%d", &movie_choice);
    printf("Enter the Number of Tickets: ");
    scanf("%d", &num_tickets);
    if (num_tickets <= 0) {
        printf("Invalid Number of Tickets!\n");
        return;
    }
    if (u->ticket_count + num_tickets > 10) {
        printf("Maximum 10 Tickets per User!\n");
        return;
    }
    struct movie movies[3] = {
        {"The Godfather", 175, 150},
        {"The Dark Knight", 152, 130},
        {"Star Wars: Episode IV - A New Hope", 121, 120}
    };
    if (movie_choice < 1 || movie_choice > 3) {
        printf("Invalid Movie Choice!\n");
        return;
    }
    movie_choice--;
    struct movie chosen_movie = movies[movie_choice];
    int total_price = chosen_movie.price * num_tickets;
    printf("Total Price: Rs.%d\n", total_price);
    printf("Confirm Booking? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if (choice != 'y' && choice != 'Y') {
        printf("Booking Cancelled!\n");
        return;
    }
    for (int i = u->ticket_count; i < u->ticket_count + num_tickets; i++) {
        u->booked_movies[i] = chosen_movie;
    }
   
    u->ticket_count += num_tickets;
    printf("Booking Successful!\n");
}

void cancel_ticket(struct user *u) {
if (u->ticket_count == 0) {
printf("\nNo Booked Tickets Found!\n");
return;
}
printf("\nBooked Movies:\n");
for (int i = 0; i < u->ticket_count; i++) {
printf("%d. %s (Duration: %d min, Price: Rs.%d)\n", i+1, u->booked_movies[i].name, u->booked_movies[i].duration, u->booked_movies[i].price);
}
printf("Enter the Movie Number to Cancel Booking: ");
int movie_choice;
scanf("%d", &movie_choice);
if (movie_choice < 1 || movie_choice > u->ticket_count) {
printf("Invalid Movie Choice!\n");
return;
}
movie_choice--;
int refund_amount = u->booked_movies[movie_choice].price;
printf("Refund Amount: Rs.%d\n", refund_amount);
printf("Confirm Cancellation? (y/n): ");
char choice;
scanf(" %c", &choice);
if (choice != 'y' && choice != 'Y') {
printf("Cancellation Cancelled!\n");
return;
}
for (int i = movie_choice; i < u->ticket_count - 1; i++) {
u->booked_movies[i] = u->booked_movies[i+1];
}
u->ticket_count--;
printf("Cancellation Successful!\n");
}

void display_payment_options() {
printf("\nPayment Options:\n");
printf("1. Credit Card\n");
printf("2. Debit Card\n");
printf("3. Net Banking\n");
}

int main() {
struct user u;
int choice;
while (1) {
printf("\nWelcome to Movie Ticket Booking System!\n");
printf("1. Display Current Movies\n");
printf("2. Register\n");
printf("3. Login\n");
printf("4. Book Ticket\n");
printf("5. Cancel Ticket\n");
printf("6. Display Payment Options\n");
printf("7. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch (choice) {
case 1:
display_movies();
break;
case 2:
register_user(&u);
break;
case 3:
if (login_user(&u)) {
printf("Welcome %s!\n", u.name);
}
break;
case 4:
if (u.ticket_count == 10) {
printf("\nMaximum 10 Tickets per User!\n");
} else {
book_ticket(&u);
}
break;
case 5:
cancel_ticket(&u);
break;
case 6:
display_payment_options();
break;
case 7:
printf("\nThank you for using Movie Ticket Booking System!\n");
exit(0);
default:
printf("\nInvalid Choice!\n");
}
}
return 0;

}