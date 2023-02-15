/**
 * @file
 *
 * Traversal: IdentifierCount
 * UID      : IC
 *
 *
 */

#include <stdio.h>
#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "palm/hash_table.h"
#include "palm/memory.h"

void ICinit()
{
    struct data_ic *data = DATA_IC_GET();
    data->id_table = HTnew_String(1);
    return;
}

void *print_table(void *key, void *item) {
    printf("%s: %d\n", (char *) key, * (int *) item);
    return item;
}

void *free_values(void *key, void *item) {
    MEMfree(item);
    return key;
}

void ICfini()
{
    printf("Identifier count:\n");
    struct data_ic *data = DATA_IC_GET();
    HTmapWithKey(data->id_table, (mapk_ft) print_table);
    HTmapWithKey(data->id_table, (mapk_ft) free_values);
    HTdelete(data->id_table);
    return;
}

/**
 * @fn ICvar
 */
node_st *ICvar(node_st *node)
{
    TRAVchildren(node);
    struct data_ic *data = DATA_IC_GET();
    int *value = HTlookup(data->id_table, VAR_NAME(node));
    if (value != NULL) {
        *value += 1;
    } else {
        int *tmp = MEMmalloc(sizeof(int));
        *tmp = 1;
        value = tmp;
    }
    HTinsert(data->id_table, VAR_NAME(node), value);
    return node;
}

/**
 * @fn ICvarlet
 */
node_st *ICvarlet(node_st *node)
{
    TRAVchildren(node);
    struct data_ic *data = DATA_IC_GET();
    int *value = HTlookup(data->id_table, VARLET_NAME(node));
    if (value != NULL) {
        *value += 1;
    } else {
        int *tmp = MEMmalloc(sizeof(int));
        *tmp = 1;
        value = tmp;
    }
    HTinsert(data->id_table, VARLET_NAME(node), value);
    return node;
}
