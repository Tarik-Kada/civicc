/**
 * @file
 *
 * Traversal: ArithmeticCount
 * UID      : AC
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"

void ACinit() { return; }
void ACfini() { return; }

/**
 * @fn ACbinop
 */
node_st *ACbinop(node_st *node)
{
    TRAVchildren(node);
    struct data_ac *data = DATA_AC_GET();
    switch (BINOP_TYPE(node)){
        case BO_add:
            data->add += 1;
            break;
        case BO_sub:
            data->sub += 1;
            break;
        case BO_mul:
            data->mul += 1;
            break;
        case BO_div:
            data->div += 1;
            break;
        case BO_mod:
            data->mod += 1;
            break;
        default:
            break;
    }
    return node;
}

/**
 * @fn ACmodule
 */
node_st *ACmodule(node_st *node)
{
    TRAVchildren(node);
    struct data_ac *data = DATA_AC_GET();
    MODULE_ADD(node) = data->add;
    MODULE_SUB(node) = data->sub;
    MODULE_MUL(node) = data->mul;
    MODULE_DIV(node) = data->div;
    MODULE_MOD(node) = data->mod;
    return node;
}

