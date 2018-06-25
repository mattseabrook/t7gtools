// main.cpp

/*

"t7gtools"

Author: Matt Seabrook
Contact: info@mattseabrook.net

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <iostream>


#include "cli.h"
#include "RLFile.h"


/*
==============================================
main

Process CLI arguments
==============================================
*/
int main(int argc, char *argv[])
{
	CLI::tagLine();

	if (argv[1] != NULL)
	{
		switch (switchProc(argv[1]))
		{
		case VERSION:
		{
			CLI::verInfo();

			break;
		}
		case HELP:
		{
			std::cout << USAGE << std::endl;

			break;
		}
		case RLFILE:
		{
			RLFile::open(argv[2]);

			break;
		}
		case TEST:
		{
			//...
			std::cout << "DEBUG-";

			break;
		}
		case INVALID:
		{
			std::cout << "ERROR: Unrecognized switch: '" << argv[1] << "', please see --help for more information:"
				<< "\r\n"
				<< USAGE
				<< std::endl;
			break;
		}
		}
	}
	else {
		std::cout << USAGE << std::endl;
	}

	return 0;
}