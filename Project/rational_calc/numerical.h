/*numerical.h -- Numerical typeclass*/
#ifndef _NUMERICAL_H
#define _NUMERICAL_H

typedef struct numerical
{
    struct numerical * method;
    void (*Add)(void * p_A, void * p_B, void * p_C);  
    void (*Sub)(void * p_A, void * p_B, void * p_C); 
    void (*Mul)(void * p_A, void * p_B, void * p_C);   
    void (*Div)(void * p_A, void * p_B, void * p_C);   
    void (*Abs)(void * p_A, void * p_C);  
    void (*Ops)(void * p_A, void * p_C);
    void (*Get)(void * p_A);
    void (*Print)(void * p_A);
} Numerical;

static inline void Add(void * p_A, void * p_B, void * p_C)
{
    ((Numerical *)p_A)->method->Add(p_A, p_B, p_C);
}

static inline void Sub(void * p_A, void * p_B, void * p_C)
{
    ((Numerical *)p_A)->method->Sub(p_A, p_B, p_C);
}

static inline void Mul(void * p_A, void * p_B, void * p_C)
{
    ((Numerical *)p_A)->method->Mul(p_A, p_B, p_C);
}

static inline void Div(void * p_A, void * p_B, void * p_C)
{
    ((Numerical *)p_A)->method->Div(p_A, p_B, p_C);
}
static inline void Abs(void * p_A, void * p_C)
{
    ((Numerical *)p_A)->method->Abs(p_A, p_C);
}
static inline void Ops(void * p_A, void * p_C)
{
    ((Numerical *)p_A)->method->Ops(p_A, p_C);
}
static inline void Get(void * p_A)
{
    ((Numerical *)p_A)->method->Get(p_A);
}
static inline void Print(void * p_A)
{
    ((Numerical *)p_A)->method->Print(p_A);
}

#endif