typedef struct {
	int num ;
	char *name ;
} Monkey ;

Monkey* CreateMonkeyArray(int );
void FreeMonkeyArray(Monkey* , int );

void SetVal(Monkey* , int , int , char []);
int Compare(Monkey* , int , int );
void Swap(Monkey* , int , int );




