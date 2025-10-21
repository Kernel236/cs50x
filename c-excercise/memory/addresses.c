 #include <stdio.h>
 #include <cs50.h>

 int main(void) 
 {

    /*
    & -> operatore che ritorna l'address della variabile 
    * -> operatore che punta all'address indicato dopo 
    %p in printf stampa l'address della variabile &n
    */
    int n = get_int("Save a number: ");
    int *p = &n;
    printf("Your number %i is stored at: %p\n", *p, p);
    return 0;
 }