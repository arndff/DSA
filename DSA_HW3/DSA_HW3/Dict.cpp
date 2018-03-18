#include "Dict.h"

Dict::Dict(const char* dictFile, const char* textFile)
{
	if (!dictFile)
	{
		throw std::runtime_error("Invalid first arg has been passed.\n");
	}
	else
	{
		std::ifstream in(dictFile);
		if (!in) 
		{
			throw std::runtime_error("Problem while opening the dict file for reading.\n");
		}
		parseDict(in); //and find the length of the longest phrase in the dictionary
		
		std::ifstream eval(textFile);
		if (!eval) 
		{ 
			throw std::runtime_error("Problem while opening the text file for reading.\n"); 
		}
		
		evaluateTxt(eval);
		
		eval.close();
		in.close();
	}
}

void Dict::parseDict(std::ifstream& in)
{
	int coeff;
	bool isPhrase;
	char delim;
	MAX_PHRASE_LEN = 0;

	while (!in.eof())
	{
		String word, phrase;
		isPhrase = false;

		extractWord(in, word, delim);
		if (in.eof()) { break; } //if there's a newline after the last word in dict file...

		while (delim != '\t')
		{
			isPhrase = true;
			
			phrase += word;
			phrase += ' ';
			
			word.destroy();
			extractWord(in, word, delim);
		}

		in >> coeff;
		in.get(); //for the \n in the end of the curr line

		if (isPhrase)
		{
			phrase += word;
			dict.insert(phrase, coeff);

			if (phrase.getLen() > MAX_PHRASE_LEN) 
			{ 
				MAX_PHRASE_LEN = phrase.getLen(); 
			}
		}
		else
		{
			dict.insert(word, coeff);

			if (word.getLen() > MAX_PHRASE_LEN) 
			{ 
				MAX_PHRASE_LEN = word.getLen(); 
			}
		}
	}
}

//refactor
void Dict::extractWord(std::ifstream& in, String& word, char& delim) const
{
	char c = in.get();
	if (in.eof()) { return; }
	
	while (isLetter(c))
	{
		word += c;
		c = in.get();
		if (in.eof()) { return; }
	}

	delim = c;
}

void Dict::evaluateTxt(std::ifstream& eval)
{
	String word, phrase;
	int coeff = 0, res = 0, cnt = 0; //move seekg with cnt bytes
	char delim;
	bool phrase_found;
	size_t word_len, phrase_len; //helper variables used to calc cnt

	while (!eval.eof())
	{
		//set
		phrase_found = false;
		word_len = 0;
		coeff = 0;

		extractWord(eval, word, delim);
		if (!eval || (word.getLen() == 0)) { break; }

		cnt += word.getLen() + 1; //+1 çàðàäè delim
		word_len = word.getLen() + 1;
		if (word.getLen() <= MAX_PHRASE_LEN && word.toLower())
		{
			dict.search(word, coeff);
		}

		phrase += word;

		while (true)
		{
			word.destroy();
			extractWord(eval, word, delim);
			if (!eval || (word.getLen() == 0)) { break; }
			if (!word.toLower()) { break; }
			phrase += ' ';
			phrase += word;
			if (phrase.getLen() <= MAX_PHRASE_LEN)
			{
				if (dict.search(phrase, coeff))
				{
					phrase_found = true;
					phrase_len = phrase.getLen() + 1;
				}
			}
			else
			{
				if (phrase_found)
				{
					cnt -= word_len;
					cnt += phrase_len;
					eval.seekg(cnt, std::ios::beg);
				}

				word.destroy();
				phrase.destroy();

				break;
			}
		}

		res += coeff; //if there's: selection sort algorithm
		              //and the dict contains: selection 10, selection sort 20
		              //at res, we add +20

		eval.clear(); //if we tried to read AFTER the end of the file, tellg will be equal to -1

		if (!phrase_found)
		{
			eval.seekg(cnt, std::ios::beg); //move seekg as many bytes as we read in the beginning of the loop (cnt bytes)
		}
	}

	std::cout << res << "\n\n";
}

bool Dict::isLetter(char c) const
{
	return c >= 'a' && c <= 'z' ||
		   c >= 'A' && c <= 'Z';
}
