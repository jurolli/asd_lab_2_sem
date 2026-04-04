
#ifndef PARSER_H
#define PARSER_H

#include "tree.h"

TreeNode *parse_expression(char *expr);
int priority(char sign);

#endif