#include<iostream>
#include<string>
#include<fstream>
using namespace std;


//单词计数器程序 

int standard = 0;

void ChangeStandard(); 
bool IsLetters(char c);
int SelectMode();
string GetStrFromInput();
string GetStrFromFile();
void WordCount(string str);

int main(){
	
	ChangeStandard();
	switch(SelectMode()){
		case 1: WordCount(GetStrFromFile()); break;
		case 2: WordCount(GetStrFromInput()); break;
		default: cout << "错误，无此选项";break;
	}
	
	return 0;
	
} 



bool IsLetters(char c){
	switch(standard){
		case 1: return isalpha(c) || (c == '-');
		case 2: return isalnum(c);
		case 3: return isalnum(c) || (c == '-');
		default: return isalpha(c);
	}
	
} 

int SelectMode(){
	int modeNum = 0;
	cout << "--------------------------------------" << endl;
	cout << "1\t统计txt文本内单词数" << endl;
	cout << "2\t统计输入的一行语句内单词数" << endl; 
	cout << "请输入选择>>>";
	cin >> modeNum;
	return modeNum;
}

string GetStrFromInput(){
	string input;
	cout << "请输入一行待统计的语句，用回车键结束" << endl;
	cout << ">>>";
	getchar();
	getline(cin, input);
	return input;
}

string GetStrFromFile(){
	string fileName, input, temp;
	//char temp;
	cout << "请输入待统计的txt文件名>>>";
	cin >> fileName;
	getchar();
	ifstream fin;
	fin.open(fileName);
	if(!fin){
		cout << "文件不存在";
		return "";
	}
	
	input = "";
	while(!fin.eof()){
		getline(fin, temp);
		input += temp;
		input += "\n";
	}
	
	char c = '\0';
	cout << "如需显示该文本内容，请直接输入回车键，否则请输入其他\n>>>";
	c = getchar();
	if(c == '\n')
		cout << input << endl;
	else
		getchar();
		
	return input;
	
}

void WordCount(string str){
	int length = str.size();
	int last, now, wordNum = 0;
	//1代表字母，0代表非字母 
	
	if(length <= 0){
		cout << "该字符串过短，无法统计单词数" << endl;
		return;
	}
	
	last = IsLetters(str[0]);
	for(int i = 0; i < length; ++i){
		now = IsLetters(str[i]);
		if(last&& !now)
			++wordNum;
		last = now;
	}
	if(last) ++wordNum;
	
	cout << "该字符串长度为 " << length << endl;
	cout << "该字符串共有 " << wordNum << " 个单词" << endl;
	
} 


void ChangeStandard(){
	char select = '\0';
	
	cout << "当出现连词符时，(如ten-year-old)是否认为是一个单词？(直接输入回车表示yes，其他表示no)\n>>>";
	select = getchar();
	if(select == '\n')
		standard += 1;
	else
		getchar();
	
	cout << "当出现数字时，(如3 years old)是否认为‘3’是一个单词？(直接输入回车表示yes，其他表示no)\n>>>";
	select = getchar();
	if(select == '\n')
		standard += 2;
	else
		getchar();
		
	cout << standard << endl;
	
}

