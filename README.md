##### [`#include <cpy.h>`]()
The library contains widely-used functions - **simplified** for scripting & general-purpose programming in C/C++.

- Intended to help people have a easy life at C/C++
- Intended mostly for beginners at programming
- Or those coming from more high-level, interpreted languages like Python - wishing performance
- Or anyone enthusiastic about C/C++

An incredible script using `cpy.h` looks as nice as:
```C
#include <cpy.h>
int main () {

    char* username = input("Can I have your name? 👨🏻‍💻 ");
    print("Your name is: ", username);

    print("Reversed ⚙️🛠️: ", str_reverse(username));
    
}
```
<br><br><br><br><br>




The library contains `+` and aims to implement `-`:
```
+ Standard headers
+ ANSI escape sequences
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
- list_sort    
+ list_sum     
+ new
+ print
- str          
+ str_add      
+ str_count    
+ str_eq       
+ str_index    
+ str_replace  
+ str_reverse  
+ str_slice    
+ str_split    
+ str_substr   
- sys_out      
+ type         
```
<br><br><br><br><br>

Words of caution from the Author, for aspiring programmers:
>Look, I know you're used to `print(str.reverse("1234567"))`. But in C/C++, you need to allocate and deallocate memory like a good & responsible programmer. So, you need to do
```
char* rev = str_reverse("123"); 
print(rev); 
free(rev);
```

>C/C++ gives you control and performance and power. Never misuse your power. Always deallocate the memory you've been using gracefully.

It may sound tedious. But don't worry, I've two tricks up my sleeve:
### 1. Memory allocation and deallocation by Task
```c
// Allocate memory as you need under task name "user's introduction"
char* username = new("user's information", char*, 20);
char* website = new("A Task", char*, 10);
...
...
// do whatever you wanted with the variables
...

// When you're done, empty all allocations 
// for task named "user's information"
new("A Task", void*, 0);
```
<br>
<br>

### 2. Pointer-based operations
Returning a pointer after
