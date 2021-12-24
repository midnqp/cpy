![cpy](https://user-images.githubusercontent.com/90899789/147235026-dfaca003-9b46-4fea-b602-e34edc8c7c87.png)

`libcpy` is a cross-platform library written in C, that implements convenient functions of Python and Javascript. This library intends to simplify writing code in C.


## Build
- To build libcpy from source, run: `make build`
- To compile a simple script written using libcpy, run: `make script file=./path/to/file.c link=<static|shared>`


## API

#### Modules & data types
- `json` Encode and decode json.
- `request` Make simple requests.
- `List` Data type.

#### Core helpers
- Enumerated types: `List_t` `Str_t` `Num_t` ... and more.
- Initialize a variable with a type:  `new(type_t)` 
```c
List* list = new(List_t);
char* name = new(Str_t);
```
- Print: `print(<any>, ...)`
```c
List* ls = new(List_t);
listAdd(ls, 1.2, "string");
print("print anything", { 1.2, -3 }, -9.1, ls);
```


| Input                             | `void input(char* name, const char*);` | `char* name = new(Str_t);` `input(name, "Your name: ");`|
| Type of a variable                | `type(variable);` | `int a; type(a);` `// returns Int_t` |
| Count number of variadic args     | `va_argc(args...)` | `#define vafunc(args...) ({ ...; int count = va_argc(args); })`
| Overload a function | | `int _index(int count, unsigned short argv[], ...);`  <br><br>  `#define Index(list, a...) ({ va_argv(_index, args...); })` |
| Colorful terminal (Optional) | See `cpy-colors.h` | `printf(RED("Text in red")  GRN("Text in green"));` |


##### List functions

Initialize first: `List* list = new(List_t);`. Now use these functions for operations with the `List` type.

| Description           | Signature                 |             Example       |
| :---                  |    :----                  | :---                      |
| Append items, many at once | `void listAdd(List* list, ...)` | `listAdd(list, "any", -0.1, "data type")`
| Find/Index an item | `int listIndex(List* list, <any> item, int start, int end);` | `listIndex(list, "any")` Yes, second argument `item` can be of any type. `start` and `end` are optional arguments. Default value `start` is 0, and `end` is length of list.

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
