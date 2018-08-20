#include <iostream>
#include <fstream>
#include <regex>
#include <map>

struct Lexer
{
    static std::map<std::size_t, std::pair<std::string, std::string>> tokenize(const std::string obj_str)
    {

        //Regex for Symbols
        const std::map<std::string, std::string> token_patterns{
            {"[0-9]+", "NUMBER"},
            {"\\{", "OPEN_BRACE"},
            {"\\}", "CLOSE_BRACE"},
            {"\\(", "OPEN_PARANTHESIS"},
            {"\\)", "CLOSED_PARANTHESIS"},
            {"return", "RETURN_KEYWORD"},
            {"[a-zA-Z]+", "IDENTIFIER"},
            {";", "SEMICOLON"},
            {"=", "EQUAL"}};

        std::map<std::size_t, std::pair<std::string, std::string>> matches;

        //Applied regex on string, saved in map
        for (auto pat = token_patterns.begin(); pat != token_patterns.end(); ++pat)
        {
            std::regex r(pat->first);
            auto words_begin = std::sregex_iterator(obj_str.begin(), obj_str.end(), r);
            auto words_end = std::sregex_iterator();

            for (auto it = words_begin; it != words_end; ++it)
            {
                matches[it->position()] = std::make_pair(it->str(), pat->second);
            }
        }

        //Print Function
        // for (auto match = matches.begin(); match != matches.end(); ++match)
        //     std::cout << match->second.first << " " << match->second.second << std::endl;

        return matches;
    }
};

struct Parser
{
    static void Parse(std::map<std::size_t, std::pair<std::string, std::string>> tokens)
    {
	std::cout << "Parseing begun" << std::endl;

        for (auto match = tokens.begin(); match != tokens.end(); ++match)
            std::cout << match->second.first << " " << match->second.second << std::endl;
    }
};


struct FileReader
{
	static std::string ReadFile(std::string filename)
	{
		//The return string
		std::string return_string = "";

		
		//File to be opened
		std::ifstream mystream (filename, std::ifstream::in);
		
		return_string += mystream.get();

		while(mystream.good())
		{
		 
			return_string += mystream.get();
		
		}

		//Close the stream
		mystream.close();

		return return_string;
	}

};



int main(int argc, char const *argv[])
{
    /* code */
 
//	std::cout << argv[1]<< std::endl;

    auto codefile = FileReader::ReadFile(argv[1]);

    // std::cout << FileReader::ReadFile("main.dro");

    //std::string hep = "int main() { int A = 4; return 2; }";

    auto matches = Lexer::tokenize(codefile);

    Parser::Parse(matches);

    return 0;
}
