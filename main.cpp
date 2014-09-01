#include "jvTerm.hpp"

int main(int argc, char* argv[])
{
	if(argc == 4)
	{
		jvTermClass jvTerm(argv[1], argv[2], argv[3]);

		jvTerm.run();

		return 0;
	}

	return 1;
}
