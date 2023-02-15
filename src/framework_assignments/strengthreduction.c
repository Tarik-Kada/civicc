/**
 * @file
 *
 * Traversal: StrengthReduction
 * UID      : SR
 *
 *
 */

#include "ccn/ccn.h"
#include "ccngen/ast.h"
#include "ccngen/trav.h"
#include "ccngen/enum.h"

/**
 * @fn SRbinop **
 */
node_st *SRbinop(node_st *node)
{
    TRAVchildren(node);
    if (BINOP_TYPE(node) == BO_mul) {
        node_st *variable_copy;
        node_st *value_copy;
        // Check what type children have.
        if (NODE_TYPE(BINOP_LEFT(node)) == NT_VAR && NODE_TYPE(BINOP_RIGHT(node)) == NT_NUM) {
            variable_copy = BINOP_LEFT(node);
            value_copy = BINOP_RIGHT(node);
        } else if (NODE_TYPE(BINOP_RIGHT(node)) == NT_VAR && NODE_TYPE(BINOP_LEFT(node)) == NT_NUM) {
            variable_copy = BINOP_RIGHT(node);
            value_copy = BINOP_LEFT(node);
        } else {
            return node;
        }
        // If value is equal to one, don't expand at all.
        if (NUM_VAL(value_copy) == 1) {
            node = variable_copy;
        } else {
            for (int i = 1; i < NUM_VAL(value_copy); i++) {
                if (i == 1) {
                    node = ASTbinop(CCNcopy(variable_copy), CCNcopy(variable_copy), BO_add);
                } else {
                    node = ASTbinop(CCNcopy(node), CCNcopy(variable_copy), BO_add);
                }
            }
        }
    }
    return node;
}
