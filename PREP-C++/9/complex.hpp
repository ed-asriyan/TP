#ifndef COMPLEX_H
#define COMPLEX_H

#include <ostream>

#define abs(a) ((a) > 0 ? (a) : -(a))

template<class REAL_TYPE, class IMAGINARY_TYPE> class Complex{
private:
	// Private fields
	REAL_TYPE realValue;
	IMAGINARY_TYPE imagValue;

	// Friend functions
	template<class REAL_D, class IMAG_D, class REAL_1, class IMAG_1, class REAL_2, class IMAG_2>
	friend void Addition(Complex<REAL_D, IMAG_D>&, const Complex<REAL_1, IMAG_1>&, const Complex<REAL_2, IMAG_2>&);

	template<class REAL_D, class IMAG_D, class REAL_1, class IMAG_1, class REAL_2, class IMAG_2>
	friend void Subtraction(Complex<REAL_D, IMAG_D>&, const Complex<REAL_1, IMAG_1>&, const Complex<REAL_2, IMAG_2>&);

	template<class REAL_D, class IMAG_D, class REAL_1, class IMAG_1, class REAL_2, class IMAG_2>
	friend void Multiplication(Complex<REAL_D, IMAG_D>&, const Complex<REAL_1, IMAG_1>&, const Complex<REAL_2, IMAG_2>&);
public:
	// Constructors & Destructors
	Complex() = default;
	
	Complex(const REAL_TYPE& real, const IMAGINARY_TYPE& imaginary){
		realValue = real;
		imagValue = imaginary;
	}

	template<class REAL, class IMAGINARY> 
	Complex(const Complex<REAL, IMAGINARY>& complex){
		realValue = static_cast<REAL>(Re(complex));
		imagValue = static_cast<IMAGINARY>(Im(complex));
	}

	virtual ~Complex(){ 

	}

	// Public methods
	template<class REAL, class IMAG> void Add(const Complex<REAL, IMAG>& complex){
		Addition(*this, *this, complex);
	}

	template<class REAL, class IMAG> void Subtract(const Complex<REAL, IMAG>& complex){
		Subtraction(*this, *this, complex);
	}

	template<class REAL, class IMAG> void Multiply(const Complex<REAL, IMAG>& complex){
		Multiplication(*this, *this, complex);
	}

	// Getters & Setters
	const REAL_TYPE& GetReal() const{
		return realValue;
	}

	void SetReal(const REAL_TYPE real){
		realValue = real;
	}

	const IMAGINARY_TYPE& GetImaginary() const{
		return imagValue;
	}

	void SetImaginary(const IMAGINARY_TYPE& imaginary){
		imagValue = imaginary;
	}

	// Public methods
	template<class REAL, class IMAG> Complex<REAL_TYPE, IMAGINARY_TYPE>& operator=(const Complex<REAL, IMAG>& complex){
		realValue = (REAL_TYPE)Re(complex);
		imagValue = (IMAGINARY_TYPE)Im(complex);

		return *this;
	}

	template<class REAL, class IMAGINARY> auto operator+(const Complex<REAL, IMAGINARY>& complex) const{
		Complex<decltype(realValue + complex.realValue), decltype(imagValue + complex.realValue)> result;
		Addition(result, *this, complex);
		return result;
	}

	template<class REAL, class IMAGINARY> auto operator-(const Complex<REAL, IMAGINARY>& complex) const{
		Complex<decltype(realValue + complex.realValue), decltype(imagValue + complex.realValue)> result;
		Subtraction(result, *this, complex);
		return result;
	}

	template<class REAL, class IMAGINARY>
	auto operator*(const Complex<REAL, IMAGINARY>& complex) const{
		Complex<decltype(realValue + complex.realValue), decltype(imagValue + complex.realValue)> result;
		Multiplication(result, *this, complex);
		return result;
	}

	template<class REAL, class IMAGINARY> const Complex<REAL_TYPE, IMAGINARY_TYPE>& operator+=(const Complex<REAL, IMAGINARY>& complex){
		Add(complex);
		return *this;
	}

	template<class REAL, class IMAGINARY> const Complex<REAL_TYPE, IMAGINARY_TYPE>& operator-=(const Complex<REAL, IMAGINARY>& complex){
		Subtract(complex);
		return *this;
	}

	template<class REAL, class IMAGINARY> const Complex<REAL_TYPE, IMAGINARY_TYPE>& operator*=(const Complex<REAL, IMAGINARY>& complex){
		Multiply(complex);
		return *this;
	}

	// Friend functions
	template<class REAL,class IMAGINARY> friend std::ostream& operator<<(std::ostream&, const Complex<REAL, IMAGINARY>&);

	template<class REAL, class IMAGINARY> friend const REAL& Re(const Complex<REAL, IMAGINARY>&);
	template<class REAL, class IMAGINARY> friend const IMAGINARY& Im(const Complex<REAL, IMAGINARY>&);
};

// Functions
template<class REAL,class IMAGINARY> std::ostream& operator<<(std::ostream& stream, const Complex<REAL, IMAGINARY>& complex){
	auto absIm = abs(complex.imagValue);
	return stream << complex.realValue << " " << (absIm == complex.imagValue ? "+" : "-") << " " << absIm << 'i';
}


template<class REAL, class IMAGINARY> const REAL& Re(const Complex<REAL, IMAGINARY>& complex){
	return complex.realValue;
}

template<class REAL, class IMAGINARY> const IMAGINARY& Im(const Complex<REAL, IMAGINARY>& complex){
	return complex.imagValue;
}

template<class REAL_D, class IMAG_D, class REAL_1, class IMAG_1, class REAL_2, class IMAG_2>
void Addition(Complex<REAL_D, IMAG_D>& dest, const Complex<REAL_1, IMAG_1>& c1, const Complex<REAL_2, IMAG_2>& c2){
	dest.realValue = c1.realValue + c2.realValue;
	dest.imagValue = c2.imagValue + c2.imagValue;
}

template<class REAL_D, class IMAG_D, class REAL_1, class IMAG_1, class REAL_2, class IMAG_2>
void Subtraction(Complex<REAL_D, IMAG_D>& dest, const Complex<REAL_1, IMAG_1>& c1, const Complex<REAL_2, IMAG_2>& c2){
	dest.realValue = c1.realValue - c2.realValue;
	dest.imagValue = c1.imagValue - c2.imagValue;
}

template<class REAL_D, class IMAG_D, class REAL_1, class IMAG_1, class REAL_2, class IMAG_2>
void Multiplication(Complex<REAL_D, IMAG_D>& dest, const Complex<REAL_1, IMAG_1>& c1, const Complex<REAL_2, IMAG_2>& c2){
	auto newReal = c1.realValue * c2.realValue - c1.imagValue * c2.imagValue;
	auto newImag = c1.imagValue * c2.realValue + c1.realValue * c2.imagValue;

	dest.realValue = newReal;
	dest.imagValue = newImag;
}

#undef abs

#endif