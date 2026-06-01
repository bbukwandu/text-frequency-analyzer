#include "Bar.h"

// Name: Bar (Default Constructor) (not used)
// Desc: Dynamically allocates m_data for strings (always). m_fileName defaults to test.txt
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
Bar::Bar(){
  m_fileName = "test.txt";//sets members to default 
  m_data = new LL<string>();
}

// Name: Bar (Overloaded Constructor)
// Desc: Used to pass an input file
//       Dynamically allocates m_data for strings (always)
//       Sets m_fileName and nothing done with m_dataSorted until SortData
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated
Bar::Bar(string filename){
  m_fileName = filename;//set filename and creates LL
  m_data = new LL<string>();
}

// Name: ~Bar (Destructor)
// Desc: Deallocates m_data
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar (){
  delete m_data; //calls LL deconstructor to deallocate LL
  m_dataSorted.clear();//empties multimap
  m_fileName = "";//sets filename to nothing
}

// Name: Start
// Desc: Calls LoadFile, RemoveCommon, RemoveSingles, Sort, DisplayBars, and Export
//       During testing, may want to call Display
// Preconditions: None (filename is available)
// Postconditions: None
void Bar::Start(){
  LoadFile();
  RemoveCommon();
  RemoveSingles();
  SortData();
  DisplayBars();
  Export();
}

// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Calls RemovePunct as each item is loaded
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_data is populated
void Bar::LoadFile(){
  int count = 0;
  string myString;
  ifstream inputStream;
  inputStream.open(m_fileName);
  if(inputStream.is_open()){
    while(inputStream >> myString){//iterates while inputing file word by word
    RemovePunct(myString);
    m_data -> Insert(myString);//adds each word to LL 
    count++;
    }
  }
  inputStream.close();
  cout << count << " words loaded" << endl;
}

// Name: RemovePunct (passed a string)
// Desc: Converts all input into lowercase using tolower
//       When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
//       You can use ispunct - https://www.geeksforgeeks.org/ispunct-function-c/
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(string& inputString){
  for (unsigned int i = 0; i < inputString.length(); i++){
    inputString[i] = tolower(inputString[i]);//capitilizes word
  }
  if(ispunct(inputString[inputString.length()-1])){//removes punctuation from the end of word
    inputString.erase(inputString.end()-1);
  }
  if(ispunct(inputString[0])){
    inputString.erase(inputString.begin());//removes punctuation from the start of word
  }
}

// Name: RemoveCommon
// Desc: Asks user if they want to remove common words
//       If yes, iterates through m_data and removes all common words after they are read
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon(){
  string choice;
  cout << "Would you like to remove all common words (Only use with essays)?" << endl;
  cin >> choice;
  if(choice == "yes"){//if user doesnt want common words
    for(unsigned int i = 0; i < EXCLUDE_LIST.size(); i++){
      m_data -> RemoveAt(EXCLUDE_LIST[i]);  //iterates list of common words and removes them from LL
    }
    cout << "All common words removed." << endl;
  }
  else{
    return;
  }
}

// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_data is a pointer!
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles(){
  int count = 0;
  string choice;
  cout << "Would you like to remove all words with a frequency of 1?" <<endl;
  cin >> choice;
  if(choice == "yes"){//if uses doesnt want words with frequency if 1
    for(int i = 0; i < m_data ->GetSize(); i++){//iterates LL and removes words with frequency if 1
      if((*m_data)[i].second == 1){
	m_data -> RemoveAt((*m_data)[i].first);
	count ++;
	i --;
      }
    }
    cout << count << " words removed." << endl;
  }
  else{
    return;
  }
}

// Name: SortData
// Desc: Iterates through each items in m_data and inserts into
//       m_dataSorted using the frequency as the key (can use make_pair)
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData(){
  pair<int, string> pairAdd;
  for(int i = 0; i < m_data ->GetSize(); i++){//iterates LL
    pairAdd = make_pair((*m_data)[i].second, (*m_data)[i].first);//creates pairs but with frequency as the key so when added to multimap it is ordered
    m_dataSorted.insert(pairAdd);
  }
}

// Name: DisplayBars
// Desc: Displays a bar chart for each item in m_dataSorted from highest
//       frequency (at the top) to lowest frequency (at the bottom) (iterate backwards)
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars(){
  for(multimap<int, string>::reverse_iterator it = m_dataSorted.rbegin(); it != m_dataSorted.rend(); it++){//iterates multimap
    cout << setw(15) << it -> second << ":";
    for(int i = 0; i < it ->first; i++){//displays multimap data with formatting
      cout << "*";
  }
    cout<< endl;
      }
}

// Name: Export
// Desc: Asks the user what name the export file should be called
//       Iterates through m_dataSorted and exports to file
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export(){
  string filename;
  cout << "What would you like to call the export file?" << endl;
  cin >> filename;//takes in user filename
  ofstream myFile(filename);
  for(multimap<int, string>::reverse_iterator it = m_dataSorted.rbegin(); it != m_dataSorted.rend(); it++){//iterates multimap
    myFile << setw(15) << it -> second << ":";
    for(int i = 0; i < it ->first; i++){//inputs  multimap data with formatting into file
      myFile << "*";
  }
    myFile << endl;
      }
  myFile.close();
}
