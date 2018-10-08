#pragma once

using ui64 = unsigned long long int;

class Residue
{
public:
    Residue(ui64 a, ui64 p);
    Residue(const Residue&);
    Residue& operator=(const Residue&);
    ~Residue();
    
    bool operator == (Residue b) const;
    bool operator < (Residue b) const;
    
    Residue& operator += (Residue b);
    Residue& operator -= (Residue b);
    Residue& operator *= (Residue b);
    Residue& operator *= (ui64 b);
    Residue& operator /= (Residue b);
    
    Residue operator ++(int b);
    Residue& operator ++();
    Residue operator --(int b);
    Residue& operator --();
    
    // обратный по умножению
    // если P составное - бросить исключение
    Residue operator ~ () const;
    
    // обратный по сложению
    Residue operator - () const;
    
    // возведение в степень b
    Residue operator ^= (ui64 b) const;
    
    ui64 Mod() const;
private:
    ui64 C;
    ui64 Modu;
};

Residue operator + (Residue a, Residue b);
Residue operator - (Residue a, Residue b);
Residue operator * (Residue a, ui64 b);
Residue operator * (ui64 a, Residue b);
Residue operator * (Residue a, Residue b);
Residue operator / (Residue a, Residue b);

// возведение a в степень b
Residue operator ^ (Residue a, ui64 b);

bool operator != (Residue a, Residue b);
bool operator > (Residue a, Residue b);
bool operator >= (Residue a, Residue b);
bool operator <= (Residue a, Residue b);
int gcdex(int, int, int &, int &);
