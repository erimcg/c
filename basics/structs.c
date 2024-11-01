#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct contact {
	char *name;
	char phone[9];
};

typedef struct contact CONTACT;

void print_contact(struct contact c);
void pass_the_struct(CONTACT* c);

int main(int argc, char* argv[]) {

	struct contact joe;
	joe.name = "Joe";
	strncpy(joe.phone, "212-5432", sizeof(joe.phone));
	print_contact(joe);
	pass_the_struct(&joe);

	struct contact my_contacts[10];
	my_contacts[0].name = "Liz";
	strncpy(my_contacts[0].phone, "280-4544", sizeof(my_contacts[0].phone));
	print_contact(my_contacts[0]);
	pass_the_struct(&my_contacts[0]);

	CONTACT boss;
	boss.name = "Verne";
	strncpy(boss.phone, "555-1212", sizeof(boss.phone));
	print_contact(boss);
	pass_the_struct(&boss);

	CONTACT* alice = malloc(sizeof(CONTACT));
	alice->name = "Alice";
	strncpy(alice->phone, "212-1212", sizeof(alice->phone));
	print_contact(*alice);
	pass_the_struct(alice);
}

void print_contact(struct contact c) {
	printf("Name: %s\n", c.name);
	printf("Phone: %s\n", c.phone);
}

void pass_the_struct(CONTACT *c) {
	printf("Name: %s\n", c->name);
	printf("Phone: %s\n", c->phone);
}


//End of file
