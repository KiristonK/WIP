// Nums_In_Safety.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <time.h>
#include <string.h>
#include <string>
#include <fstream>
//#include <math.h>

#define MAX 1000


bool Prime(unsigned int p) {
	for (int i = 2; i < p/2; i++) {
		if (p % i == 0)
			return false;
	}
	return true;
}

int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}

void crypt(unsigned long long int e, unsigned int n) {
	std::cout << "\nCrypting with public key : " << e << ' ' << n << "\n";
	char* buff = new char[MAX];
	std::cout << "\nEnter text for cypting (MAX : 1000 symbols) :\n";
	std::cin.get(buff, MAX);
	std::ofstream fout;
	fout.open("cryptedText.txt");
	std::cout << "\n\nCrypted text :";
	unsigned long long int c;
	for (int i = 0; buff[i] != 0; i++) {
		c = 1;
		unsigned long long int j = 0;
		while (j < e) {
			c = c * (static_cast<int>(buff[i]));
			c = c % n;
			j++;
		}
		fout << ' ' << c;
		std::cout << ' ' << c;
	}
	fout.close();
}

void encrypt(unsigned int d, unsigned int n) {
	std::cout << "\n\nEncrypting...\n";
	std::ifstream fin;
	unsigned long long int* buff = new unsigned long long int[MAX], i = 0;
	unsigned long long int m;
	int tmp;
	fin.open("RSA_Keys.txt");
	fin >> tmp >> n >> d;
	fin.close();
	std::cout << "\nPrivate key : " << d << ' ' << n << "\n";
	fin.open("cryptedText.txt");
	std::cout << "\nCryptogramm : ";
	while (!fin.eof()) {
		fin >> buff[i];
		std::cout << buff[i] << ' ';
		i++;
	}
	buff[i] = NULL;
	fin.close();
	std::cout << "\n\nEncrypted text : ";
	for (i = 0; buff[i] != 0; i++) {
		m = 1;
		unsigned long long int j = 0;
		while (j < d)
		{
			m = m * buff[i];
			m = m % n;
			j++;
		}
		std::cout << static_cast<char>(m);
	}

}

int main()
{
	bool r = true;
	int primeNums[9999];
	int c = 0;
	for (int i = 2; i < 9999; i++) {
		r = true;
		for (int j = 2; j < (i / 2); j++) {
			if (i % j == 0) {
				r = false;
				break;
			}
		}
		if (r) {
			primeNums[c] = i;
			c++;
		}
	}
	primeNums[c] = NULL;
	std::cout << "Prime numbers - [";
	for (int i = 0; primeNums[i] != NULL; i++) {
		std::cout << primeNums[i] << "\t";
	}
	std::cout << "]\n";
	srand(time(NULL));
	unsigned int p, q, n;
    std::cout << "\nPrime number 1 : ";
	while (Prime(p = 1000 + rand() % 9999) != true);
	std::cout << p << "\nPrime number 2 : ";
	while (Prime(q = 1000 + rand() % 9999) != true);
	n = p * q;
	std::cout << q << "\n\nN = " << n << "\n";
	unsigned int fi = (p - 1) * (q - 1); 
	std::cout << "\nfi(" << n << ") = " << fi << "\n";
	unsigned int d, d_s = 0;
	while (d_s != 1) {
		d = 1000 + rand() % 9999;
		d_s = gcd(d, fi);
	}
	std::cout << "\nd = " << d << "\n";
	unsigned long long int e = 0, e_s = 0;
	while (e_s != 1) {
		e += 1;
		e_s = (e * d) % (fi);
	}
	std::cout << "\ne = " << e << "\n";
	std::cout << "\nPublic key: \t" << e  << ' ' << n << "\n";
	std::cout << "Private key : \t" << d << ' ' << n << "\n\n";

	std::ofstream fout;
	fout.open("RSA_Keys.txt");
		fout << e << ' ' << n << "\n" << d << ' ' << n;
	fout.close();
	system("pause");
	crypt(e, n);		
	encrypt(d, n);
	std::cout << "\n";
	system("pause");
	return EXIT_SUCCESS;
}


