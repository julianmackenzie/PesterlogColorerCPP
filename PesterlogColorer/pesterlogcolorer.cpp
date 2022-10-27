#include <iostream>
#include <string>


using namespace std;


// Menu prompt displayed on each input loop
void displayBroadMenu() {
    cout << endl << endl << "-- Main Menu --" << endl << endl
    << "p. Process pesterlog" << endl << "h. Pesterlog formatting help" << endl << "x. Quit" << endl << endl
    << "> User: Make a choice ==> ";
}


void displayFormatHelp() {
    cout << endl << endl << endl << endl << endl << endl << "--- PESTERLOG FORMATTING HELP ---" << endl << endl << "The .txt file that you provide should follow Homestuck's pesterlog format." << endl << endl
    << "Here is a template of how this should look. The header and footer are optional but must be in the proper format if included." << endl << endl << endl
    << "-- firstHandle [XX] began pestering secondHandle [YY] --" << endl << endl
    << "XX: this is the first line of dialog" << endl
    << "XX: this is the second line of dialog" << endl
    << "YY: this is the third line of dialog" << endl
    << "XX: this is the fourth line of dialog" << endl << endl
    << "-- firstHandle [XX] ceased pestering secondHandle [YY] --" << endl << endl << endl
    << "\"firstHandle\" and \"secondHandle\" are the chumhandles of your characters." << endl
    << "They are generally a lowercase word followed by a word with an uppercase first letter, with no space between, like \"gardenGnostic\" or \"tentacleTherapist\"." << endl << endl
    << "More importantly, XX and YY are the shortened chumhandles, the first letter of each word in the chumhandle capitalized." << endl
    << "For example, if your chumhandle was turntechGodhead, you would put TG in place of XX." << endl << endl
    << "The actual header and footer can technically contain anything as long as [XX] and [YY] are present (the [] is what is checked for)\nand as long as they begin and end with a \"--\"." << endl
    << "Each line of dialog needs to begin with XX or YY. This is how the color tags are added." << endl << endl << endl;

    cout << "Input literally anything to return to the menu. Anything you want. I won't tell.\n==> ";
    string nothingBurger;  // Dummy variable to create the illusion of a system("PAUSE") call without the archaic repercussions of actually doing that
    cin >> nothingBurger;

    cout << endl << endl << endl;
}




// Handles the main command loop
void mainCmdLoop(string cmd) {
    while (cmd != "x") {  // While user does not wish to quit
        if (cmd == "h") displayFormatHelp();

        


        displayBroadMenu();  // Display menu to user
        cin >> cmd;  // Take input from user
    }
}



int main()
{

    // Opening monologue (very interesting/important)
    cout << endl << endl << endl << "Welcome to Jug's Chumhandle-to-Text-Color interface!" << endl << endl
    << "This program was written to process pesterlog .txt files (in proper pesterlog format) for use on https://mspfa.com" << endl << endl
    << "If you don't know what a pesterlog is, visit https://www.homestuck.com and offer a blood sacrifice to the shittest fandom on Earth!" << endl
    << "If you don't know how to format a pesterlog, select the \"Pesterlog formatting help\" option when prompted." << endl;


    
    displayBroadMenu();  // Initial menu display
    
    string cmd = "";  // Will be used to process user input
    cin >> cmd;  // Take first input from user

    mainCmdLoop(cmd);

    cout << endl << endl << "Thank you for using Jug's Chumhandle-to-Text-Color interface!" << endl
    << "Check out the VirtualVexed webcomic on https://mspfa.com!" << endl << endl << endl;

}