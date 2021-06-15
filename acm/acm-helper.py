#!/usr/bin/env python
 
import os
import argparse

parser = argparse.ArgumentParser()

parser.add_argument("subcmd", type=str)
parser.add_argument("number", type=str)
args = parser.parse_args()

dir_path = args.subcmd + "-"+ args.number
os.makedirs(dir_path)

template = """
#include <iostream>

using namespace std;

#define TEST

int main()
{{
#ifdef TEST
    freopen("{}-{}-input.txt", "r", stdin);
#endif
// code goes here


// code ends
#ifdef TEST
    fclose(stdin);
#endif
}}
""".format(args.subcmd, args.number)


cpp_path = os.path.join(dir_path, dir_path + '.cpp')
with open(cpp_path, 'w') as f:
    f.write(template)

input_path = os.path.join(dir_path, dir_path + '-input.txt')
with open(input_path, "w") as f:
    pass




