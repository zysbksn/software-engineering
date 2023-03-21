#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// 定义一个结构体来表示每个输入
struct Input {
    vector<int> ints;  // int 类型的变量
    vector<char> chars;  // char 类型的变量
    vector<string> strings;  // string 类型的变量
};

// 读取 stdin_format.txt 中的输入格式
vector<string> read_input_format(const string& input_format_file) {
    vector<string> input_format;
    ifstream input_file(input_format_file);
    if (input_file.is_open()) {
        string line;
        getline(input_file, line);
        stringstream ss(line);
        string item;
        while (getline(ss, item, ' ')) {
            input_format.push_back(item);
        }
        input_file.close();
    } else {
        cerr << "Failed to open input format file: " << input_format_file << endl;
        exit(1);
    }
    return input_format;
}

// 生成一个随机输入
Input generate_input(const vector<string>& input_format) {
    Input input;
    for (const string& item : input_format) {
        // 获取 type 和范围
        string type = item.substr(0, item.find("("));
        string range = item.substr(item.find("(") + 1, item.find(")") - item.find("(") - 1);
        // 解析范围
        int lower_bound = stoi(range.substr(0, range.find(",")));
        int upper_bound = stoi(range.substr(range.find(",") + 1));
        // 生成随机值
        if (type == "int") {
            int value = rand() % (upper_bound - lower_bound + 1) + lower_bound;
            input.ints.push_back(value);
        } else if (type == "char") {
            char value = 'a' + rand() % 26;
            input.chars.push_back(value);
        } else if (type == "string") {
            int length = rand() % (upper_bound - lower_bound + 1) + lower_bound;
            string value(length, ' ');
            for (int i = 0; i < length; i++) {
                value[i] = 'a' + rand() % 26;
            }
            input.strings.push_back(value);
        } else {
            cerr << "Invalid input format: " << type << endl;
            exit(1);
        }
    }
    return input;
}

// 读取程序的输出
string read_output(const string& output_file) {
    string output;
    ifstream output_stream(output_file);
    if (output_stream.is_open()) {
        string line;
        while (getline(output_stream, line)) {
            output += line + "\n";
        }
        output_stream.close();
    } else {
        cerr << "Failed to open output file: " << output_file << endl;
        exit(1);
    }
    return output;
}
