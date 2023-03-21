std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

bool check_equal(const std::string& output1, const std::string& output2) {
    std::ifstream file1(output1), file2(output2);
    std::string line1, line2;
    while (std::getline(file1, line1) && std::getline(file2, line2)) {
        if (line1 != line2) {
            return false;
        }
    }
    return true;
}
//该函数接收两个参数，分别是两个OJ程序的输出文件路径，返回值为一个布尔类型。
//该函数通过逐行比较两个输出文件的内容，如果发现有一行不相同，则返回false，表示这两个OJ程序不等价，否则返回true，表示这两个OJ程序等价。


void judge(const std::string& oj1, const std::string& oj2, const std::string& input_file,
           const std::string& output_dir, std::ofstream& equal_file, std::ofstream& inequal_file) {
    std::string output1 = output_dir + "/output1.txt";
    std::string output2 = output_dir + "/output2.txt";
    std::string cmd1 = "./" + oj1 + " < " + input_file + " > " + output1;
    std::string cmd2 = "./" + oj2 + " < " + input_file + " > " + output2;
    exec(cmd1.c_str());
    exec(cmd2.c_str());
    if (check_equal(output1, output2)) {
        equal_file << oj1 << "," << oj2 << std::endl;
    } else {
        inequal_file << oj1 << "," << oj2 << std::endl;
    }
}
//该函数接收六个参数，分别为两个OJ程序的路径、标准输入文件的路径、输出文件夹的路径以及两个输出文件流（用于输出等价和不等价的OJ程序）。该函数首先根据输入和输出文件夹的路径，生成两个输出文件的路径。接着，生成两个执行命令cmd1和cmd2，并通过exec函数执行这两个命令，分别将两个OJ程序的输出写入到output1和output2文件中。最后，调用check_equal函数判断这两个输出文件是否相同，如果相同，则输出这两个OJ程序的路径到等价文件流中，否则输出到不等价文件流中。