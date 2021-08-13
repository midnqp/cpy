`#include <cpy.h>`

<br>

An incredible script using `cpy.h` looks as nice as:
```C
#include <cpy.h>
int main () {

    char* name = input("👨🏻‍💻 Your Name? ");
    print("Reversed: ", str_reverse(name));

    print(str_split(name, "-"));
    
}

To link this library to your code:
```bash
# For GCC or MinGW
gcc cpy.c main.c
```batch
:: For Microsoft Visual Studio C++
:: The print implementation needs to be ported. Other than, it's all good.

cl.exe /EHsc /c cpy.c
lib.exe cpy.obj

cl.exe /EHsc main.c /link cpy.lib
```
<br><br><br><br><br>




The library contains `+` and aims to implement `-`:
```
+ Standard headers
+ ANSI colors
- dict
+ file_append  
+ file_read    
+ file_write   
+ file_size    
+ input        
- list_add     
- list_count   
- list_index   
- list_eq
- list_join    
- list_len     
+ list_max     
+ list_min     
- list_reverse 
- list_remove  
- list_slice   
+ list_sort    
+ list_sum     
+ new
+ print
- str          
+ str_add      
+ str_count    
+ str_eq       
+ str_index   
+ str_isalpha 
+ str_len
+ str_replace  
+ str_reverse  
+ str_slice    
+ str_split    
+ str_substr   
- subprocess_getoutput
+ type         
```
The implementations for list, can easily be done having ideas from the string counterparts. Work In Progress.
<br><br><br><br><br>



Words of caution from the Author, for aspiring programmers:
>Maybe you're used to `print(str.reverse("1234567"))`. But in C/C++, you need to allocate and deallocate memory like a good & responsible programmer. So, you need to do
```c
char* rev = str_reverse("123"); 
print(rev); 
free(rev);
```

>C/C++ gives you control and performance and power. Never misuse your power. Always deallocate the memory you've been using gracefully.

It may sound tedious. But don't worry, I've got two tricks up my sleeve.
<br><br><br><br><br>




### 1. Memory allocation and deallocation by Task
```c
// Allocate memory as you need under task name "user's introduction"
char* username = new("user's information", char*, 20);
char* website = new("Another Task", char*, 10);
...
...
// do whatever you wanted with the variables
...

// When you're done, empty all allocations 
// for task named "user's information"
new("user's information", void*, 0);
```

### 2. Address-based operations
Returning a pointer after operation, causes the programmer to initialize new variables. Alternatively, address-based operations are like:
```c
// new() is still kept return-based 
// because they're better this way.

char* username = new("info", char*, 20);     
input(username, "Your name? ");
// The string from stdin is appended to the var pointer `username`
...
...

str_reverse(username, username);
// The string at `username` is reversed and...
// put in the place of itself.
// Hence not requiring to use another variable.

// And, we can integrate free-by-task
new("info", void*, 0);
```

The address-based implementations of the methods/functions will be available at the [address-based](http://github.com/MidnQP/cpy/tree/address-based) branch.
