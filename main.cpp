#include <iostream>
#include <fstream>
#include <stdexcept>

const char* filepath  = "default.txt";

class Token
{
public:
	char kind;
	int value;
};

class TokenStream
{
public:
	TokenStream(std::istream& stream = std::cin): in(stream) {};
	Token Get();
	//Token Peak();
	void PutBack(Token t);
private:
	bool full{false};
	Token buffer;
	std::istream& in;
};

TokenStream* tsp;

int Expression();
int Time();
int Hour();
int Minute();

int main(int argc, char* argv[])
{
	std::cout << "Hours" << std::endl;

	if(1 < argc) filepath = argv[1];
	std::cout << "Open file " << filepath << std::endl;
	std::ifstream file(filepath);
	if(!file) throw std::runtime_error("File bad");
	TokenStream tokenStream(file);
	::tsp = &tokenStream;

	int sum = 0;
	while(file && EOF != file.peek()) //TODO: should be 'while(tokenStream)'. Look into this
	{
		if('\r' == file.peek() || '\n' == file.peek()) file.ignore();
		else sum += Expression();
	}

	std::cout << "Hours: " << sum/60 << " Minutes: " << sum%60 << std::endl;

	return 0;
}

int Expression()
{	
	int left = Time();
	Token t = tsp->Get();
	if('-' == t.kind || '+' == t.kind ) return Time() - left;
	else throw std::runtime_error("Bad expression");
}

int Time()
{
	int minutes = 60*Hour();
	Token t = tsp->Get();
	if('.' == t.kind || ':' == t.kind) return minutes+Minute();
	else
	{
		tsp->PutBack(t);
		return minutes;
	}
}

int Hour()
{
	Token t = tsp->Get();
	if('1' != t.kind || (0 > t.value || 23 < t.value)) throw std::runtime_error("Bad hour token");
	return t.value;
}

int Minute()
{
	Token t = tsp->Get();
	if('1' != t.kind || (0 > t.value || 59 < t.value)) throw std::runtime_error("Bad minute token");
	return t.value;
}

void TokenStream::PutBack(Token t)
{
	if(full)
	{
		//std::cerr << "putback error\n";
		//return;
		throw std::runtime_error("Putback Error");
	}
	buffer = t;
	full  = true;
}

Token TokenStream::Get()
{
	if(full)
	{
		full = false;
		return buffer;
	}

	char ch;
	in >> ch;

	switch(ch)
	{
		case '-':
		case '+':
		case '.':
		case ':':
			return Token{ch};
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			in.putback(ch);
			int val;
			in >> val;
			return Token{'1', val};
		}
		default:
			throw std::runtime_error("Bad token");
	}
}
