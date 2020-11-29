#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#define BUF_SZ 80

typedef struct Pair {
	gchar *key;
	gint value;
} Pair;

int cmp(gpointer lhs, gpointer rhs)
{
	return ((Pair *)rhs)->value - ((Pair *)lhs)->value;
}

void my_list_add(gpointer key, gpointer value, gpointer list)
{
	Pair* pair = malloc(sizeof(Pair));
	pair->key = key;
	pair->value = value;
	*(GList**)list = g_list_append(*(GList**)list, pair);
}

void my_print(gpointer pair, gpointer null)
{
	printf("%s %d\n", ((Pair *)pair)->key, ((Pair *)pair)->value);
}

int main()
{
	GHashTable* ht = g_hash_table_new(g_str_hash, g_str_equal);
	char buf[BUF_SZ];

	while (scanf(" %s ", buf) != EOF)
	{
		GString* str = g_strdup(buf);

		gint new_value = g_hash_table_lookup(ht, str) + 1;
		g_hash_table_insert(ht, str, new_value);
	}
	
	GList* list;
	g_hash_table_foreach(ht, my_list_add, &list); 
	list = g_list_sort(list, cmp);
	g_list_foreach(list, my_print, NULL);
	return 0;
}

