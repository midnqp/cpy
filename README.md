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

    double arr[] = { 1.2, -3.4 };
    bool ls_type = type(ls) == List_t;  // true
    print(ls, name);
    print("anything", -5.6, ls_type, false, arr);
}
```

```c
// Count variadic args
#define function(args...) ({       \
    int count = va_argc(args);     \
    print("Count: ", count);       \
})
function(0, 1, 2, 3); // Count: 4


// Overload a function
void _add(int argc, unsigned short argv[], ...); 
#define Add(args...) ({ va_argv(_add, args); })
Add(1, 2, 3, 4, 5);
```





##### List functions

Initialize first: `List* ls = new(List_t);`. Now use these functions for operations with the `List` type.
Arguments with `<optional>` tag can be omitted. They have a default value.


| Description           | Signature                 |
| :---                  | :----                     |
| Append items | `void listAdd(List* ls, ...);`
| Find/Index an item | `int listIndex(List* ls, <any> item, int start <optional>, int end <optional>)`;
| List includes item? | `bool listIncludes(List* ls);`
| Slice | `List* listSlice(List* ls, int from, int end);`
| Count items | `int listLen(List* ls);`
| Copy & return a list | `List* listDup(List* ls);`
| Free after use | `void listFree(List* ls);`
| Minimum item from numbers | `double listMin(List* ls);`
| Maximum item from numbers | `double listMax(List* ls);`
| Sort & return a list | `List* listSort(List* ls);`
| Sum of number items | `double listSum(List* ls);`
| Remove an item | `void listRemove(List* ls, <any> item);`
| Splice | `void listSplice(List* ls, int index, int count);`

```c
listAdd(list, "any", -0.1, "data type");

listIndex(list, "any");
listIndex(list, 7);
// Yes, second argument `item` can be of any type.
// `start` and `end` are optional arguments.
// Default of `start` is 0, and `end` is length of list.
```


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
