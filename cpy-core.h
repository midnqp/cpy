#ifndef CPY_CORE_H
#define CPY_CORE_H

enum TYPE {
	Void_t   = 10,   Float_t = 1,
	Int_t    = 4,    Short_t = 4,
	Char_t   = 2,    Str_t   = 8,
	Uchar_t  = 3,    Uint_t  = 5,
	Long_t   = 6,    Ulong_t = 7,
	Double_t = 1,    Num_t   = 1,
	Bool_t   = 17,   List_t  = 18,
	DoubleList_t = 19,
	FloatList_t = 20,
	// Literals...
	StrArray_t    = 15,
	CharArray_t   = 9,
	UintArray_t   = 12,
	ShortArray_t  = 13,
	UshortArray_t = 14,
	DoubleArray_t = 11,
	FloatArray_t = 21,
	
	Unknown_t    = 0,
};


typedef struct __list__ {
	void* value;
	int alloc;
	int* types;
} List;


#define type(variable) \
_Generic(variable,     \
    int    : Int_t,    \
    char   : Char_t,   \
    long   : Long_t,   \
    double : Double_t, \
    float  : Float_t,  \
    char*  : Str_t,    \
	double*: DoubleArray_t,\
	float* : FloatArray_t, \
	void*  : Void_t,       \
    default: Unknown_t)


#define vargc(args...) __print_count(args)


#define typeOf(a) ({\
	unsigned short stack[1], *_p = stack + 1;\
	__print_types(a);\
	_p[0] & 0x1F; \
})


#define new(t) ({ \
	new_##t(); \
})


#define new_List_t() ({\
	List list; \
	list.alloc = 8*1024; \
	list.value = malloc(list.alloc); \
	list.types = (int*)malloc(8*1024); \
	for (int i=0; i < 1024;i++) \
		list.types[i] = INT_MAX;\
	list; \
})

#endif
