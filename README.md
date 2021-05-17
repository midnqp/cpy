## GETTING INVOLVED
To contribute code to the upstream: fork this repository, make changes, and pull request! And always feel free to open up an issue if you'd like to add something to the list below.

```
+ 8-bit ANSI escape sequences, for colored texts.
- double       (str representing type double)
+ file_append  (filename, buffer)
+ file_read    (filename)      
+ file_write   (filename, buffer)
+ file_size    (filename)
- getarg       ("cmdline", "-option", "default")
+ input        (str)           
- int          (str)                 
- list         (str)
- list_add     (destArr, itemToAdd)
- list_count   (arr, item)
- list_index   (arr, item)         
- list_isequal (arr1, arr2)
- list_join    (arr)
- list_len     (arr)
+ list_max     (arr, len(arr)) 
+ list_min     (arr, len(arr))       
- list_reverse (arr)
- list_remove  (arr, item, occurence)
- list_slice   (start, end)
- list_sort    (arr, len(arr))    
+ list_sum     (arr, len(arr))    
+ new          (type, bytes)     :: (type*)malloc(bytes)
- print        (any, any, ...)  
- self_document(__FILE__)
- str          (int | float)                 
+ str_add      (dest, strToAdd)  :: returns pointer to the two added strings.
+ str_addva    (dest, src, ...)  :: returns pointer to the added multiple strings.
+ str_count    (str, substr, headstart)
+ str_eq       (a, b)
+ str_index    (str, substr, headstart)  :: returns index to first occurence
+ str_replace  (main, replace, with)
- str_reverse  (str)
- str_slice    (start, end)
- str_split    (str, delim) 
+ str_substr   (str, substr)     
- sys_out      ("command")       
+ type         (variable name)
```
