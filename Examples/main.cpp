#include <cargs/cargs.hpp>
#include <cstdio>

int main(int argc, char* argv[])
{
	(void)argc;(void)argv;
	printf("Hello cargs\n");

	//! Create cargs with program name
	cargs::Cargs option(argv[0]);

	//! Define command line arguments option
	option.add_flag('h', "help", "Print help commands", cargs::Value())
					('i', "input", "Set input file path", cargs::Value())
					('o', "output", "Set output file path", cargs::Value());
	
	//! Parse the command line arguments
	cargs::Result parse_result = option.parse_args(argc, argv);

	//! Check wrong command line arguments exists
	for (const auto& wrong_arg : parse_result.get_wrong_arguments())
	{
		//! Print similar commands
		cargs::Flag similar_flag = option.get_similar_flag(wrong_arg);
		std::cout << argv[0] << ": '" << wrong_arg << "' is not a git command. See '" << argv[0] << "' --help\n";
		std::cout << "The most similar command ist\n\t\t" << similar_flag.get_long_hint() << '\n';
	}

	//! Print parsed result
	// std::cout << parse_result["input"] << '\n';
	// std::cout << parse_result["output"] << '\n';

	return 0;
}