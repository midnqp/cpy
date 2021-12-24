![cpy](https://user-images.githubusercontent.com/90899789/147235026-dfaca003-9b46-4fea-b602-e34edc8c7c87.png)

`libcpy` is a cross-platform library written in C, that implements convenient functions of Python and Javascript. This library intends to simplify writing code in C.


## Build
- To build libcpy from source, run: `make build`
- To compile a simple script written using libcpy, run: `make script file=./path/to/file.c link=<static|shared>`


## API :: Core

| Description | Signature |
| :--         | :--       |
| Enumerated types| `List_t` `Str_t` `Num_t` ...
| Initialize a variable | `new(type_t)` 
| Print | `print(<any>, ...)`
| Input | `void input(char* name, const char*);`
| Count variadic args | `va_argc(args...)`
| Overload a function | `va_argv(func, args...)`  
| Colorful texts (Optional) | See `cpy-colors.h`


```c
#include <cpy.h>
int main() {


    char* name = new(Str_t);
    input(name, "You are: ");
    
    List* ls = new(List_t);
    listAdd(ls, 1.2, -3.4, name);

    print("anything", name, { 1.2, -3.4 }, -5.6, ls, type(ls) == List_t);
}
```

```c
// Count variadic args
#define function(args...) ({       \
    int count = va_argc(args);     \
    print("Count: ", count);       \
})
// Define an overloadable function
void _add(List* list, int argc, unsigned short argv[], ...); 
#define add(list, args...) ({ va_argv(_add, args); })


function(0, 1, 2, 3); // Count: 4
print(RED("text in red")  GRN("text in green"));
```





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
