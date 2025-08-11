#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

// Data structure to store chatbot responses
struct ChatbotResponse {
    string prompt;
    string response;
};

// Chatbot class
class Chatbot {
private:
    map<string, ChatbotResponse> responses;
    ifstream dataFile;

public:
    Chatbot(const string& filename) {
        dataFile.open(filename);
        if (!dataFile) {
            cerr << "Error opening file: " << filename << endl;
            exit(1);
        }
        loadResponses();
    }

    void loadResponses() {
        string line;
        while (getline(dataFile, line)) {
            size_t delimiterPos = line.find(",");
            if (delimiterPos != string::npos) {
                string prompt = line.substr(0, delimiterPos);
                string response = line.substr(delimiterPos + 1);
                responses[prompt] = {prompt, response};
            }
        }
    }

    string getResponse(const string& userInput) {
        if (responses.find(userInput) != responses.end()) {
            return responses[userInput].response;
        } else {
            return "I didn't understand that. Please try again!";
        }
    }
};

int main() {
    Chatbot chatbot("chatbot_data.txt");

    string userInput;
    while (true) {
        cout << "User: ";
        getline(cin, userInput);

        string response = chatbot.getResponse(userInput);
        cout << "Chatbot: " << response << endl;
    }

    return 0;
}