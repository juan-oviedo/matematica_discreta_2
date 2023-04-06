#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "int_to_str.h"


// char * int_to_string (unsigned int x){
//     char str = NULL;
//     if (x >= 10)
//     {
//         if (x >= 100)
//         {
//             if (x >= 1.000)
//             {
//                 if (x>= 10.000)
//                 {
//                     if (x >= 100.000)
//                     {
//                         if (x >= 1.000.000)
//                         {
//                             if (x >= 10.000.000)
//                             {
//                                 if (x >= 100.000.000)
//                                 {
//                                     if (x >= 1.000.000.000)
//                                     {
//                                         char str [11];
//                                     }
                                    
//                                     if (str != NULL)
//                                     {
//                                         /* code */
//                                     }
//                                     else
//                                     {
//                                         /* code */
//                                     }





//                                 }

//                                 if (str != NULL)
//                                 {
//                                     /* code */
//                                 }
//                                 else
//                                 {
//                                     /* code */
//                                 }






//                             }

//                             if (str != NULL)
//                             {
//                                 /* code */
//                             }
//                             else
//                             {
//                                 /* code */
//                             }





//                         }

//                         if (str != NULL)
//                         {
//                             /* code */
//                         }
//                         else
//                         {
//                             /* code */
//                         }




//                     }

//                     if (str != NULL)
//                     {
//                         /* code */
//                     }
//                     else
//                     {
//                         /* code */
//                     }




                    
//                 }
//             }
//         }
//     }
// }


// char * int_to_string (unsigned int x){
//     float y = x / 10^9;
//     if ( y >= 1){
//         char * str [11];
//         if (y < 2)
//         {
//             str[0] = '1';
//         }
//         else if (y < 3)
//         {
//             str[0] = '2';
//         }
//         else if (y < 4)
//         {
//             str[0] = '3';
//         }
//         else if (y < 5)
//         {
//             str[0] = '4';
//         }
//     }
// }

char * int_to_string (unsigned int x){
    char str [11];
    bool ya_tomo_el_primer_digito = false;
    int y;
    unsigned int temp = x;

    for (int i = 9; i >= 0; i--)
    {
        unsigned int divisor = 1;
        
        for (int j = 0; j < i; j++)
        {
            divisor = divisor * 10;
        }

        y = temp / divisor;
        
        if (y >= 1 || ya_tomo_el_primer_digito)
        {
            ya_tomo_el_primer_digito = true;

            if (y < 1)
            {
                str[9-i] = '0';
            }
            else if (y < 2)
            {
                str[9-i] = '1';
                temp = temp - divisor;
            }
            else if (y < 3)
            {
                str[9-i] = '2';
                temp = temp - (2 * (divisor));
            }
            else if (y < 4)
            {
                str[9-i] = '3';
                temp = temp - (3 * (divisor));
            }
            else if (y < 5)
            {
                str[9-i] = '4';
                temp = temp - (4 * (divisor));
            }
            else if (y < 6)
            {
                str[9-i] = '5';
                temp = temp - (5 * (divisor));
            }
            else if (y < 7)
            {
                str[9-i] = '6';
                temp = temp - (6 * (divisor));
            }
            else if (y < 8)
            {
                str[9-i] = '7';
                temp = temp - (7 * (divisor));
            }
            else if (y < 9)
            {
                str[9-i] = '8';
                temp = temp - (8 * (divisor));
            }
            else{
                str[9-i] = '9';
                temp = temp - (9 * (divisor));
            }
        }
        else
        {
            str[9-i] = 'a';
        }
    }

    char * res = malloc(sizeof(char) * 11);
    res = strcpy (res, str);
    return res;
}

// char * int_to_string (unsigned int x){
//     char str[11];

//     for (int i = 9; i >= 0; i--)
//     {
//         str[9-i] = '0';
//     }

//     char * aux = malloc(sizeof(char) * 11);
//     aux = strcpy(aux, str);
//     return aux;
// }


// char * fun(){
//     char a[11];
//     for (int i = 9; i >= 0; i--)
//     {
//         a[9-i] = '0';
//     }
    
//     char * b = malloc(sizeof(char) * 5);
//     b = strcpy(b, a);
//     return b;
// }

// int main()
// {
//     unsigned int x;
//     scanf("%u", &x);

//     char * res = int_to_string (x);
//     printf ("%s\n", res);


//     // char str [3];
//     // str [0] = '1';
//     // str [1] = '2';
//     // printf("%s\n", str);
    
    
//     // char * asd = fun();
//     // printf("%s\n", asd);

//     return 0;
// }
