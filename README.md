![cpy](https://user-images.githubusercontent.com/90899789/147235026-dfaca003-9b46-4fea-b602-e34edc8c7c87.png)

`libcpy` is a cross-platform library written in C, that implements convenient functions of Python and Javascript. This library intends to simplify writing code in C.


## Build
- To build libcpy from source, run: `make build`
- To compile a simple script written using libcpy, run: `make script file=./path/to/file.c link=<static|shared>`


## API

##### Modules & data types
- `json` Encode and decode json.
- `request` Make simple requests.
- `List` Data type.

##### Core helpers
- Enumerated types: `Str_t` `List_t` `Num_t` ...
- Initialize a type: `new(type_t)` e.g. `List* list = new(List_t);`
- Get type of a variable: `type(variable)`
- Count number of variadic args: `va_argc(args...)`
- Overload a function: `va_argv(func, args...)`
- (Optional, potentially deprecable) Colorful terminal: `printf(RED("Text in red")  GRN("Text in green"));`


##### List functions

Initialize first: `List* list = new(List_t);`. Now use these functions for operations with the `List` type.

- Append items, e.g. many at once: `listAdd(list, "any", -0.1, "data type")`
- Find/Index an item: `int listIndex(List* list, <any> item, int start, int end);` Yes, second argument `item` can be of any type. `start` and `end` are optional arguments. Default value `start` is 0, and `end` is length of list.
- List Includes? `bool listIncludes(List* list);`
- List slice (Javascript) `List* listSlice(List* list, int from, int end);`
- Length of list: `listLen(list)`
- Copy & return a list: `listDup(list)`
- Free after use: `listFree(list)`
- Minimum item from numbers: `listMin(list)`
- Maximum item from numbers: `listMax(list)`
- Sort a list: `listSort(list)`
- Sum of number items: `listSum(list)`
- Remove an item: `void listRemove(List* list, <any> item);`

##### String functions

Initialize: `char* name = new(Str_t);`.

- Append items, e.g. many at once: `strAdd(name, "Muhammad")`
- Check if strings are equal: `strEq("abc", "abcd")`
- Reverse a string: `strReverse(name)`
- Does this substring exist?  `bool strSub(char* name, char* substring);` e.g. `strSub("Muhammad", "Muham")`
- Index a string: `int strIndex("Muhammad", "u");`
- Count occurencence of a string: `int strCount("Muhammad", "m");`
- Is the string alphanumeric? `bool strAlnum(name);`
- Replace a string with another: `strReplace(name, "replace this string", "with this.")`
- Slice a string (Javascript) `char* strSlice(char* name, int start, int end);`
- Split: `List* strSplit(char* string, char* delimiter);`
- Free: `strFree(char* string);`
