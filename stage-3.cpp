#include "avl.h"


//Drier program to test above function
int main(int argc, char **argv)
{
	if(argc != 5)
	{
		cout << "usage: <excutable- file> " << endl;
		cout << "     : <dictionary-file>" << endl;
		cout << "     : <stage-2-outputFile>" << endl;
		cout << "     : <output-file-sting_is_not_match-in-dictionary> "  << endl;
		cout << "     : <output-file-sting_is_match-in-dictionary>" << endl;
		return 0;
	}
	AVL avl;

	avl.root = NULL;

	ifstream myfile (argv[1]);

	// store all the file data into buffer
	vector <string > strBuffer = avl.getBuffer(myfile);

	// make the AVL tree for all those word
	for(unsigned int i = 0; i < strBuffer.size(); i++){
		const char* wordStr = strBuffer[i].c_str();
		avl.root = avl.insert(avl.root, wordStr);
	}


	avl.temp = NULL;

	// take input from stage-2 file
	ifstream stage_2_File (argv[2]);


	// store those string which are not match with dictionary
	ofstream myfile_string_not_present(argv[3]);


	// store those string which are match with dictionary
	ofstream myfile_string_present(argv[4]);


	string localStr;

	// open stage-2  file
	if(stage_2_File.is_open())
	{
		// take the data line by line
		while(getline(stage_2_File, localStr))
		{
			cout << localStr << endl;
			// search the string form AVL tree
			avl.temp = avl.search(avl.root, localStr.c_str());

			// check whether the string is present or not
			if(avl.temp != NULL)
			{
				// if it is present then again check whether it is match with localStr or not
				if(strcmp(avl.temp->key, localStr.c_str()) == 0)
				{
					cout << "string is present" << endl;
					myfile_string_present << localStr << endl;
				}
				else{
					myfile_string_not_present << localStr << endl;
					cout << "string is not present " << endl;

				}
			}

			else
			{
				myfile_string_not_present << localStr << endl;
				cout << "string is not present " << endl;

			}
		}

	}
	else
	{
		cout << "stage_2_File is not open" << endl;
		return 0;
	}

	avl.deleteNode(avl.root, avl.root->key);

	return 0;
}
