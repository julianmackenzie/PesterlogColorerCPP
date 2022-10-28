

//
// This program was written in less than 24 hours by Julian Mackenzie, or "Jug", for the MSPFA and Homestuck community.
//
// The purpose of this program is to format a .txt file containing a "Pesterlog" in proper format.
// This format is detailed in the program in a formatting help menu option.
//
// To learn what a Pesterlog is, visit https://www.homestuck.com to read the webcomic that inspired this whole project.
//
// You can find this project hosted at https://github.com/julianmackenzie/PesterlogColorer
//
// This project is open source. Feel free to modify anything and everything, but please do cite Julian Mackenzie as the creator and link back to the original repo!
//




#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <map>


using namespace std;




//
// Menu prompt displayed on each input loop
//
void displayBroadMenu() {
    cout << endl << endl << "-- Main Menu --" << endl << endl
    << "p. Process pesterlog" << endl << "h. Pesterlog formatting help" << endl << "x. Quit" << endl << endl
    << "> User: Make a choice ==> ";

    return;
}



//
// Abstracted file opening for user input file
//
void openInputFile(ifstream &infile, string &filename, string &filepath) {
    cout << "Choose input file (should be placed in \"unformatted\" folder) ==> ";
    cin >> filename;  // get name of user file

    filepath = "unformatted/" + filename;  // prepend the input directory to name of file

    infile.open(filepath);  // attempt to open specified file

    while (!infile.good()) {  // if file failed to open
        cout << endl << "ERROR: file does not exist, isn't in the right directory, or its name was inputted incorrectly. Please try again." << endl
        << "Choose input file (should be placed in \"unformatted\" folder) ==> ";

        cin >> filename;  // try inputting again
        filepath = "unformatted/" + filename;  // prepend the input directory to name of file
        infile.open(filepath);
    }

    return;

}




//
// Command loop for adding user handles and corresponding hex color codes to a map
//
void inputCharacters(map<string, string> &charData) {
string cmd = "y";

    while (cmd == "y" || cmd == "Y") {

        string handle = "";
        string color = "";

        cout << endl << "Specify character's two-letter chumhandle abbreviation as it appears in the log (i.e. TG for turntechGodhead) ==> ";

        cin >> handle;  // input two-letter handle

        if (charData.count(handle)) {  // if handle is a duplicate, avoid overwriting
            cout << endl << endl << "ERROR: Unfortunately, this program cannot process logs with duplicate handles." << endl
            << "You'll need to do this one on your own or replace their abbreviation with a unique placeholder, then change it back after processing.";
        }
        
        else if (handle.length() != 2 || !isupper(handle[0]) || !isupper(handle[1])) {  // enforce XX format for chumhandle abbreviations
            cout << endl << endl << "ERROR: Your handle abbreviation must be two capital letters.";
        }
        
        else {
            cout << endl << "Specify text color hex value for " + handle + " without the # (i.e. AF59FF) ==> #";

            cin >> color;  // input hex color value
            

            if (std::all_of(color.begin(), color.end(), ::isxdigit) && color.length() == 6) {  // all_of bit used from https://stackoverflow.com/questions/8899069/how-to-find-if-a-given-string-conforms-to-hex-notation-eg-0x34ff-without-regex
                color = "#" + color;

                charData.insert(pair<string, string>(handle, color));  // Add handle and text color to character data map

                cout << endl << endl << "Added character " << handle << " with text color " << charData[handle] << ".";
            }

            else {
                cout << endl << endl << "ERROR: Your color code is not a proper hex color value. It must be six characters long and only contain 0-9, a-f, and A-F.";
            }

        }

        
        cout << endl << "Would you like to add another character? (y/n) ==> ";

        cin >> cmd;  // ask user if they want to add another character
    }

    return;

}




//
// Prints the data in the charData map and asks user to confirm that they wish to process their file with that data
//
int outputCharacters(map<string, string> &charData, ifstream &infile) {
    cout << endl << endl << endl << "Please review the character data:" << endl << endl;


    for (auto const& p : charData) {  // Iterate through the map and print character data
        cout << "Chumhandle abbreviation: " << p.first << "  Text color: " << p.second << endl;
    }


    cout << endl << "Check that chumhandles are two capitalized letters and colors are in hex format (#xxxxxx)" << endl
    << "Is all of the data correct? If not, or if you wish to cancel processing, you will be returned to the main menu. (y/n) ==> ";


    string cmd = "";
    cin >> cmd;

    if (cmd != "y" && cmd != "Y") {  // Let user cancel if data is incorrect
        cout << endl << endl << "Pesterlog processing cancelled." << endl;
        infile.close();
        return 1;  // user chooses to cancel
    }

    return 0;  // user chooses to proceed
}



//
// Abstracted file opening for output file
//
void openOutputFile(ofstream &outfile, string filename) {
    string ofilepath = "formatted/formatted_" + filename;  // prepend the output directory to name of file
    outfile.open(ofilepath);
}

//
// Main logic function, reads file line by line and applies rules based on data from charData map
//
void processFile(ifstream &infile, ofstream &outfile, map<string, string> charData) {
    string line;

    outfile << "[spoiler open=\"Show Pesterlog\" close=\"Hide Pesterlog\"]" << endl;

    while (getline(infile, line)) {  // for each line in the input file

        string linekey = line.substr(0,2);  // check first two characters of line

        if (charData.count(linekey)) {  // if charData contains the linekey (linekey is a chumhandle abbreviation)
            line = "[color=" + charData[linekey] + "]" + line + "[/color]";  // add corresponding color code
        } else if (linekey == "--") {  // if line is a header or footer
            for (auto const& p : charData) {  // iterate through the charData array to search for each abbreviation in the line
                
                string headerAbbrev = "[" + p.first + "]";  // format of abbreviation to look for
                
                int abbrevIndex = line.find(headerAbbrev);  // search for the abbreviation and its enclosing brackets

                if (abbrevIndex != -1) {  // if abbreviation is found
                    line.insert(abbrevIndex + 4, "[/color]");  // add closing color tag to end of abbreviation
                    string colorCode = "[color=" + p.second + "]";
                    line.insert(abbrevIndex, colorCode);  // add opening color tag to beginning of abbreviation
                }
            }
        } 


        outfile << line << endl;  // commit all changes to output file
    }
    outfile << "[/spoiler]";
    
    return;

}



//
// Makes calls to functions needed to process through an input file.
//
void startFileProcessing() {

    cout << endl << endl << endl << endl << endl << endl << "-- PESTERLOG PROCESSING --" << endl << endl;

    ifstream infile;  // input stream from log file, opened in openInputFile() below
    
    string filename;  // name of input file, specified in openInputFile() below
    string filepath;  // full path of input file, specified in openInputFile() below


    openInputFile(infile, filename, filepath);  // prompt user and open specified file

    cout << endl << "Successfully opened log file!" << endl << endl << endl << "-- Chumhandle setup -- " << endl;  // Success message!


    map<string, string> charData;  // will be used to store all character handles and colors

    inputCharacters(charData);  // take user input and add to map


    // Print all data and give user option to cancel
    if (outputCharacters(charData, infile) == 1) {
        return;
    }


    // PROCESSING
    cout << endl << endl << endl << endl << endl << endl << "Preparing to process " << filename << "..." << endl;


    ofstream outfile;  // output filestream

    openOutputFile(outfile, filename);  // open new file or overwrite existing file in /formatted dir for writing

    cout << endl << "Output file opened..." << endl;


    processFile(infile, outfile, charData);  // apply logic line by line to edit the file

    cout << endl << "Pesterlog modification was successful! The modified copy is available in the \"formatted\" folder." << endl << endl << endl;  // file processing success message


    // Close filestreams
    infile.close();
    outfile.close();


    cout << "Input literally anything to return to the menu. Anything you want. I won't tell.\n==> ";
    string nothingBurger;  // Dummy variable to create the illusion of a system("PAUSE") call without the archaic repercussions of actually doing that
    cin >> nothingBurger;

    return;
}



void displayFormatHelp() {
    cout << endl << endl << endl << endl << endl << endl << "--- PESTERLOG FORMATTING HELP ---" << endl << endl << "The .txt file that you provide should follow Homestuck's pesterlog format." << endl << endl
    << "Here is a template of how this should look." << endl << endl << endl
    << "-- firstHandle [XX] began pestering secondHandle [YY] --" << endl << endl
    << "XX: this is the first line of dialog" << endl
    << "XX: this is the second line of dialog" << endl
    << "YY: this is the third line of dialog" << endl
    << "XX: this is the fourth line of dialog" << endl << endl
    << "-- firstHandle [XX] ceased pestering secondHandle [YY] --" << endl << endl << endl
    << "The header and footer are optional (and shouldn't be used when logs involve more than 2 characters) but must be in the proper format if included." << endl << endl
    << "\"firstHandle\" and \"secondHandle\" are the chumhandles of your characters." << endl
    << "They are generally a lowercase word followed by a word with an uppercase first letter, with no space between, like \"gardenGnostic\" or \"tentacleTherapist\"." << endl << endl
    << "More importantly, XX and YY are the shortened chumhandles, the first letter of each word in the chumhandle capitalized." << endl
    << "For example, if your chumhandle was turntechGodhead, you would put TG in place of XX." << endl << endl
    << "The actual header and footer can technically contain anything as long as [XX] and [YY] are present (the [] is what is checked for)\nand as long as they begin and end with a \"--\"." << endl
    << "Each line of dialog needs to begin with XX or YY, and XX and YY must be different." << endl
    << "If two characters have the same abbreviation, choose one and replace all instances of theirs with a unique placeholder, then change it back after processing." << endl << endl << endl;

    cout << "Input literally anything to return to the menu. Anything you want. I won't tell.\n==> ";
    string nothingBurger;  // Dummy variable to create the illusion of a system("PAUSE") call without the archaic repercussions of actually doing that
    cin >> nothingBurger;

    cout << endl << endl << endl;

    return;
}




// Handles the main command loop
void mainCmdLoop(string cmd) {



    while (cmd != "x") {  // While user does not wish to quit
        if (cmd == "p") startFileProcessing();
        else if (cmd == "h") displayFormatHelp();
        else if (cmd == "");  // for the first loop
        else cout << endl << "That was an invalid command. Nice try, pooplord!" << endl;


        displayBroadMenu();  // Display menu to user
        cin >> cmd;  // Take input from user
    }

    return;

}



int main()
{

    // Opening monologue (very interesting/important. very.)
    cout << endl << endl << endl << "Welcome to Jug's Chumhandle-to-Text-Color interface!" << endl << endl
    << "This program was written to process pesterlog .txt files (in proper pesterlog format) for use on https://mspfa.com" << endl << endl
    << "If you don't know what a pesterlog is, visit https://www.homestuck.com and offer a blood sacrifice to the shittest fandom on Earth!" << endl
    << "If you don't know how to format a pesterlog, select the \"Pesterlog formatting help\" option when prompted." << endl;


    string cmd = "";  // Will be used to process user input
    mainCmdLoop(cmd);


    // Epilogue
    cout << endl << endl << "Thank you for using Jug's Chumhandle-to-Text-Color interface!" << endl
    << "Check out the VirtualVexed webcomic on https://mspfa.com!" << endl << endl << endl;

}