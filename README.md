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

- Append items, e.g. many at once: `listAdd(list, "any", -0.1, "data type");`
- Free after use: `list_free(list);`
