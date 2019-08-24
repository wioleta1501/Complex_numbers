#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct complex_t
{
    float re;
    float im;
};

int read(struct complex_t* cp);
void show(const struct complex_t* cp);

int add(const struct complex_t *first, const struct complex_t *second, struct complex_t* result);
int subtract(const struct complex_t *first, const struct complex_t *second, struct complex_t* result);
int multiply(const struct complex_t *first, const struct complex_t *second, struct complex_t* result);
int divide(const struct complex_t *first, const struct complex_t *second, struct complex_t* result);

float complex_abs(struct complex_t* cp, int * err_code);

int main()
{
    struct complex_t liczba1;
    struct complex_t *wsk_licz1 = &liczba1;

    struct complex_t liczba2;
    struct complex_t *wsk_licz2 = &liczba2;

    struct complex_t wynik;
    struct complex_t *wsk_w = &wynik;

    int error;

    printf("Enter first complex number:  ");
    int pobierz1 = read(wsk_licz1);
    if (pobierz1==1)
    {
        printf("Incorrect input");
        return 1;
    }
    else if (pobierz1==2)
    {
        printf("Incorrect input");
        return 1;
    }

    printf("Enter second complex number:  ");
    int pobierz2 = read(wsk_licz2);
    if (pobierz2==1)
    {
        printf("Incorrect input");
        return 1;
    }
    else if (pobierz2==2)
    {
        printf("Incorrect input");
        return 1;
    }
    float modul1=complex_abs(wsk_licz1,&error);
    if (modul1==-1)
    {
        printf("Incorrect input");
        return 1;
    }
    float modul2=complex_abs(wsk_licz2,&error);
    if (modul2==-1)
    {
        printf("Incorrect input");
        return 1;
    }

    if (modul1>modul2) printf("FIRST IS BIGGER\n");
    else if (modul1<modul2) printf("SECOND IS BIGGER\n");
    else printf("THEY ARE EQUAL\n");

    int dodawanie = add(wsk_licz1, wsk_licz2, wsk_w);
    if (dodawanie==1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("ADD: ");
    show(wsk_w);

    int odejmowanie = subtract(wsk_licz1, wsk_licz2, wsk_w);
    if (odejmowanie==1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("SUBSTRACT: ");
    show(wsk_w);

    int mnozenie = multiply(wsk_licz1, wsk_licz2, wsk_w);
    if (mnozenie==1)
    {
        printf("Incorrect input");
        return 1;
    }
    printf("MULTIPLY: ");
    show(wsk_w);

    int dzielenie = divide(wsk_licz1, wsk_licz2, wsk_w);
    if (dzielenie==1)
    {
        printf("Incorrect input");
        return 1;
    }
    else if (dzielenie==2) printf("Operation not permitted - dividing by 0!");
    else
    {
        printf("DIVIDE: ");
        show(wsk_w);
    }
    return 0;
}

int read(struct complex_t* cp)
{
    if(cp==NULL) return 1;

    float real;
    float imag;
    char znak;

    if (scanf("%f%ci%f", &real, &znak, &imag)!=3) return 2;
    else if (znak!='-' && znak!='+') return 2;
    else if (imag<0) return 2;
    else if (znak=='-') imag=(-imag);
    cp->re=real;
    cp->im=imag;

    return 0;
}

void show(const struct complex_t* cp)
{
    if(cp!=NULL)
    {
        if (cp->im<0)
        {
            float imag = -(cp->im);
            printf("%.2f - i%.2f\n",cp->re,imag);
        }
        else if (cp->im==0) printf("%.2f - i%.2f\n",cp->re,cp->im);
        else
        printf("%.2f + i%.2f\n",cp->re,cp->im);
    }
}

int add(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
    if(first==NULL) return 1;
    if(second==NULL) return 1;
    if(result==NULL) return 1;

    result->re = first->re + second->re;
    result->im = first->im+ second->im;

    return 0;
}

int subtract(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
    if(first==NULL) return 1;
    if(second==NULL) return 1;
    if(result==NULL) return 1;

    result->re = first->re - second->re;
    result->im = first->im - second->im;

    return 0;
}
int multiply(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
    if(first==NULL) return 1;
    if(second==NULL) return 1;
    if(result==NULL) return 1;

    result->re = (first->re * second->re) - (first->im * second->im);
    result->im = (first->re * second->im) + (first->im * second->re);

    return 0;
}
int divide(const struct complex_t *first, const struct complex_t *second, struct complex_t* result)
{
    if(first==NULL) return 1;
    if(second==NULL) return 1;
    if(result==NULL) return 1;
    float check = (second->re*second->re) + (second->im*second->im);
    if (check<=0) return 2;

    result->re = ((first->re * second->re) + (first->im * second->im)) / ((second->re*second->re) + (second->im*second->im));
    result->im = ((first->im * second->re) - (first->re * second->im)) / ((second->re*second->re) + (second->im*second->im));

    return 0;
}


float complex_abs(struct complex_t* cp, int * err_code)
{
    if(cp==NULL)
    {
        if (err_code!=NULL) *err_code=1;
        return -1;
    }
    float modul = sqrt((cp->re)*(cp->re)+(cp->im)*(cp->im));

    if (err_code!=NULL) *err_code=0;
    return modul;
}
