#ifndef ARVOREUTILS_H
#define ARVOREUTILS_H

#include "arvoreb.h"

btree* load_tree_from_txt(const char* file_name);
bool save_tree_to_txt(btree* root, const char* output_file_name);

#endif
