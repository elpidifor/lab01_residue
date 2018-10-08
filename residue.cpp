#include <iostream>
#include "residue.h"

int gcdex(int a, int b, int &x, int &y){
    if (a == 0){
        x = 0; y = 1;
        return b;
    }
    int t_x, t_y;
    int d = gcdex(b % a, a, t_x, t_y);
    x = t_y - (b / a) * t_x;
    y = t_x;
    return d;
}

Residue::Residue(ui64 a, ui64 p){
    modu = p;
    C = a % p;
}

Residue::Residue(const Residue& data)
: C(data.C), modu(data.modu)
{}

Residue::~Residue()
{}

Residue& Residue::operator=(const Residue& data){
    C = data.C;
    modu = data.modu;
    return *this;
}

bool Residue::operator == (Residue b) const{
    if (modu != b.modu){
        throw std::runtime_error("different modules");
    }else if (C == b.C){
        return true;
    }else{
        return false;
    }
}

bool Residue::operator < (Residue b) const{
    if (modu != b.modu){
        throw std::runtime_error("different modules");
    }else{
        return C < b.C ? true : false;
    }
}

Residue& Residue::operator += (Residue b){
    if (modu != b.modu){
        throw std::runtime_error("different modules");
    }else{
        C = C + b.C;
        C = C % modu;
    }
    return *this;
}

Residue& Residue::operator -= (Residue b){
    if (modu != b.modu){
        throw std::runtime_error("different modules");
    }else{
        C = (C - b.C + modu) % modu;
    }
    return *this;
}

Residue& Residue::operator *= (Residue b){
    if (modu != b.modu){
        throw std::runtime_error("different modules");
    }else{
        C = C * b.C;
        C = C % modu;
    }
    return *this;
}

Residue& Residue::operator *= (ui64 b){
    C = C * b;
    C = C % modu;
    return *this;
}

Residue& Residue::operator /= (Residue b) {
	if (modu != b.modu) {
		throw std::runtime_error("the residues have different modules");
	}
	else {
		int t_X = 0;
		int t_Y = 0;
		gcdex(static_cast<int>(b.C), static_cast<int>(b.modu), t_X, t_Y);
		C = C * t_X;
		C = C % modu;
	}
	return *this;
}

Residue Residue::operator ++(int b) {
	Residue temp(*this);
	C += 1;
	C = C % modu;
	return temp;
}

Residue& Residue::operator ++() {
	C += 1;
	C = C % modu;
	return *this;
}

Residue Residue::operator --(int b) {
	Residue temp(*this);
	C = (C - 1 + Mod()) % Mod();
	return temp;
}

Residue& Residue::operator --() {
	C = (C - 1 + Mod()) % Mod();
	return *this;
}

// обратный по умножению
// если P составное - бросить исключение
Residue Residue::operator ~() const{
    int t_X = 0;
    int t_Y = 0;
    int result = gcdex(static_cast<int>(C), static_cast<int>(modu), t_X, t_Y);
    if (result != 1){
        throw std::runtime_error("Not prime");
    }else{
        Residue temp((t_X + modu) % modu, modu);
        return temp;
    }
}
// обратный по сложению
Residue Residue::operator - () const{
    ui64 temp = modu - C;
    Residue t_Obj(temp, modu);
    return t_Obj;
}
// возведение в степень b
Residue Residue::operator ^= (ui64 b) const{
    Residue t_Obj(*this);
    ui64 temp = t_Obj.C;
    size_t k = 1;
    while (k <= b){
        t_Obj.C = t_Obj.C * temp;
    }
    t_Obj.C = t_Obj.C % modu;
    return t_Obj;
}

ui64 Residue::Mod() const{
    return modu;
}

Residue operator + (Residue a, Residue b){
    return a += b;
}

Residue operator - (Residue a, Residue b){
    return a -= b;
}

Residue operator * (Residue a, Residue b){
    return a *= b;
}'

Residue operator * (Residue a, ui64 b) {
	return a *= b;
}

Residue operator * (ui64 a, Residue b) {
	return b *= a;
}
Residue operator / (Residue a, Residue b){
    return a /= b;
}
// возведение a в степень b
Residue operator ^ (Residue a, ui64 b) {
	return a ^= b;
}

bool operator != (Residue a, Residue b) {
	return !(a == b);
}

bool operator > (Residue a, Residue b) {
	if (a == b) {
		return false;
	}
	return !(a < b);
}

bool operator >= (Residue a, Residue b) {
	if (a == b) {
		return true;
	}
	return !(a < b);
}

bool operator <= (Residue a, Residue b) {
	if (a == b) {
		return true;
	}
	return a < b;
}
