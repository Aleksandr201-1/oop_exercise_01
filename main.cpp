#include <iostream>

class Rational{
	private:
		int a_, b_; //числитель и знаменатель
	public:
		//конструкторы
		Rational(){}
		Rational(int a_, int b_): a_(a_), b_(b_){}
		int a() const{
			return a_;
		}
		int& a(){
			return a_;
		}
		int b() const{
			return b_;
		}
		int& b(){
			return b_;
		}
		//функция сокращения дроби
		void reduce(){
			//если числитель равен нулю, то сокращать ничего не нужно
			if(a_==0){
				return;
			}
			//если числитель и знаменатель отрицательны, то убрать минусы 
			if(a_<0 && b_<0){
				a_=-a_;
				b_=-b_;
			}
			int c=a_, d=b_;
			//если числитель или знаменатель - отрицательное число, то домножить его на -1
			if(c<0){
				c=-c;
			}
			if(d<0){
				d=-d;
				a_=-a_;
				b_=-b_;
			}
			//нахождение НОД и деление числителя и знаменателя на него
			while(c!=d){
				if(c>d){
					c-=d;
				}
				if(d>c){
					d-=c;
				}
			}
			a_=a_/c;
			b_=b_/c;
		}
		//перегрузка операторов
		friend std::ostream& operator<< (std::ostream& output, const Rational& num); //ввод
		friend std::istream& operator>> (std::istream& input, Rational& num); //вывод
};

//перегрузка операторов
Rational operator+ (const Rational& rat1, const Rational& rat2){
	return Rational(rat1.a()*rat2.b()+rat1.b()*rat2.a(),rat1.b()*rat2.b());
}
Rational operator+ (const Rational& rat, const int num){
	return Rational(rat.a()+rat.b()*num,rat.b());
}

Rational operator- (const Rational& rat1, const Rational& rat2){
	return Rational(rat1.a()*rat2.b()-rat1.b()*rat2.a(),rat1.b()*rat2.b());
}
Rational operator- (const Rational& rat, const int num){
	return Rational(rat.a()-rat.b()*num,rat.b());
}

Rational operator* (const Rational& rat1, const Rational& rat2){
	return Rational(rat1.a()*rat2.a(),rat1.b()*rat2.b());
}
Rational operator* (const Rational& rat, const int num){
	return Rational(rat.a()*num,rat.b());
}

Rational operator/ (const Rational& rat1, const Rational& rat2){
	if(rat2.a()==0){
		std::cerr << "На ноль делить нельзя\n";
		exit(-1);
	}
	return Rational(rat1.a()*rat2.b(),rat1.b()*rat2.a());
}
Rational operator/ (const Rational& rat, const int num){
	if(num==0){
		std::cerr << "На ноль делить нельзя\n";
		exit(-1);
	}
	return Rational(rat.a(),rat.b()*num);
}

int operator== (const Rational& rat1, const Rational& rat2){
	if(rat1.a()*rat2.b()==rat1.b()*rat2.a()){
		return 1;
	} else {
		return 0;
	}
}

std::ostream& operator<< (std::ostream& output, const Rational& rat){
	if(rat.a()!=0 && rat.b()!=1){
		output << rat.a() << "/" << rat.b();
	} else {
		output << rat.a();
	}
	return output;
}

std::istream& operator>> (std::istream& input, Rational& rat){
	input >> rat.a() >> rat.b();
	if(rat.b()==0){
		std::cerr << "Ноль нельзя использовать в качестве знаменателя\n";
		exit(-1);
	}
	return input;
}

int main(){
	Rational rat1, rat2, arg;
	while(1){
		std::cout << "Введите 2 дробных числа в виде 4-х чисел (числитель1 знаменатель1 числитель2 знаменатель2)\n";
		std::cin >> rat1 >> rat2;

		if(rat1==rat2){
				std::cout << "Дроби равны\n";
		} else {
				std::cout << "Дроби не равны\n";
		}

		arg=rat1+rat2;
		arg.reduce();
		std::cout << rat1 << " + " << rat2 << " = " << arg << "\n";

		arg=rat1-rat2;
		arg.reduce();
		std::cout << rat1 << " - " << rat2 << " = " << arg << "\n";
		
		arg=rat1*rat2;
		arg.reduce();
		std::cout << rat1 << " * " << rat2 << " = " << arg << "\n";
		
		arg=rat1/rat2;
		arg.reduce();
		std::cout << rat1 << " / " << rat2 << " = " << arg << "\n";
	}
	return 0;
}
