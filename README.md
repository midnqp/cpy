![cpy](https://user-images.githubusercontent.com/90899789/147235026-dfaca003-9b46-4fea-b602-e34edc8c7c87.png)

<p align="left">
<a href="https://opensource.org/licenses/MIT">
    <img src="https://img.shields.io/badge/License-MIT-brightgreen.svg?style=for-the-badge">
</a>
    &emsp;
    <img src="https://img.shields.io/github/languages/code-size/midnqp/cpy?style=for-the-badge">
    &emsp;
    <img src="https://img.shields.io/tokei/lines/github.com/midnqp/cpy?style=for-the-badge">
</p>



`libcpy` is a library written in C, that:
- implements commonly-used data-type operations
- brings the best/relevant from `libnica` `c-utils` `sc` `libstb` `awesome-c` ...
- modules: `json`, `request`, ...
- attempts to simplify general-purpose scripting in C


## Build
- To build libcpy from source, run: `make build`
- To compile a simple script written using libcpy, run: `make script file=./path/to/script.c link=<static|shared>`




## API :: Core

| Description | Signature |
| :--         | :--       |
| Enumerated types| `List_t` `Str_t` `Num_t` ...
| Initialize a variable | `new(type_t);` 
| Print | `print(<any>, ...);`
| Input | `void input(char* name, const char* prompt);`
| Type | `type(variable);`
| Count variadic args | `va_argc(args...);`
| Overload a function | `va_argv(func, args...);`
| Colorful texts (Optional) | See `cpy-colors.h`


```c
#include <cpy.h>
int main() {

    char* name = new(Str_t);
    input(name, "👨🏻‍💻 Username: ");
    
    List* ls = new(List_t);
    listAdd(ls, 1.2, -3.4, name);

    double arr[] = { 1.2, -3.4 };
    bool t = type(ls) == List_t;  // true
    print(ls, name);
    print("🔥 anything", -5.6, t, arr);
}
```

```c
// Count variadic args
#define function(args...) ({       \
    int count = va_argc(args);     \
    print("Count: ", count);       \
})
function(0, 1, 2, 3); // Count: 4
```

```c
// Overload a function
void _add(int argc, unsigned short argv[], ...); 
#define Add(args...) ({ va_argv(_add, args); })
Add(1, 2, 3, 4, 5);
```





## API :: List

- Initialize: `List* ls = new(List_t);`
- Arguments with `<any>` tag can be of any type.
- Arguments with `<optional>` tag can be omitted. They have a default value.


| Description           | Signature                 |
| :---                  | :----                     |
| Append items | `void listAdd(List* ls, ...);`
| Find/Index an item | `int listIndex(List* ls, <any> item, int start <optional>, int end <optional>)`;
| Remove an item | `void listRemove(List* ls, <any> item);`
| Count items | `int listLen(List* ls);`
| [Includes](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/includes) | `bool listIncludes(List* ls, <any> item);`
| Slice | `List* listSlice(List* ls, int start <optional>, int end <optional>);`
| [Splice](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Array/splice)  | `void listSplice(List* ls, int index <optional>, int count <optional>);`
| Copy & return a list | `List* listDup(List* ls);`
| Min item among numbers | `double listMin(List* ls);`
| Max item among numbers | `double listMax(List* ls);`
| Sum of numbers | `double listSum(List* ls);`
| Sort & return a list | `List* listSort(List* ls);`
| Free | `void listFree(List* ls);`




## API :: String

- Initialize: `char* name = new(Str_t);`.
- Arguments with `<optional>` tag can be omitted. They have a default value.

| Description           | Signature                 |
| :---                  | :----                     |
| Append strings | `void strAdd(char* str, const char* items, ...);`
| Strings equal? |  `bool strEq(const char* foo, const char* bar);`
| Reverse | `char* strReverse(const char* str);`
| Substring exists? |  `bool strSub(const char* str, const char* sub);` 
| Index/Find a string | `int strIndex(const char* str, const char* sub);`
| Count occurencences of a string | `int strCount(const char* str, const char* sub);`
| Alphanumeric? | `bool strAlnum(const char* str);`
| Replace | `void strReplace(const char* str, const char* a, const char* b);`
| Slice | `char* strSlice(const char* str, int start <optional>, int end <optional>);`
| Split | `List* strSplit(const char* str, const char* delimiter);`
| Free | `void strFree(const char* string);`




## API :: File

- Initialize: `<none>`
- The following are for overly simple operations, and can be made better/powerful.

| Description         | Signature           |
|:---                 | :---                |
| File exists? | `bool fileExists(const char* filepath);`
| Directory/Folder exists? | `bool dirExists(const char* path); `
| Read a file | `bool fileRead(const char* filepath, char* content);`
| Write to a file | `bool fileWrite(const char* filepath, const char* content);`
| Append to a file | `bool fileWrite(const char* filepath, const char* content);`
| Remove a file | `bool fileRemove(const char* filepath);`
| File size | `int fileSize(const char* filepath);`
| Remove a directory/folder | `bool dirRemove(const char* path, bool recursive);`
| `TODO` Asynchronously read/write a huge file | `void fileReadAsync(...);` `void fileWriteAsync(...);`
