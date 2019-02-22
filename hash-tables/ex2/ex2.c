#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(16);
  char **route = malloc(length * sizeof(char *));

  // First insert tickets into hash
  for (int i = 0; i < length; i++)
  {
    // If source is NONE this is start of route
    if (strcmp(tickets[i]->source, "NONE") == 0)
    {
      route[0] = tickets[i]->destination;
    }
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
  }

  // Reconstruct Route
  for (int i = 1; i < length; i++)
  {
    // Get previous destination (route - 1) as source then retrieve new Source destination from hash table
    if (hash_table_retrieve(ht, route[i - 1]) != NULL)
    {
      // set next route destination
      route[i] = hash_table_retrieve(ht, route[i - 1]);
    }
    else
    {
      // If no matching key set last destination as NONE
      route[i] = "NONE";
    }
  }
  // destroy hash and return result
  destroy_hash_table(ht);
  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%s\n", route[i]);
  }
}

#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif
