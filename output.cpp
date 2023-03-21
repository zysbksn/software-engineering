#include <fstream>
#include <iostream>
#include <vector>

void write_csv(const std::string& file_path, const std::vector<std::pair<std::string, std::string>>& data) {
    std::ofstream file(file_path);
    if (!file) {
        std::cerr << "Failed to open file " << file_path << std::endl;
        return;
    }
    for (const auto& item : data) {
        file << item.first << "," << item.second << std::endl;
    }
    std::cout << "Output file " << file_path << " generated successfully!" << std::endl;
}

void output(const std::vector<std::pair<std::string, std::string>>& equal_pairs, 
            const std::vector<std::pair<std::string, std::string>>& inequal_pairs,
            const std::string& output_dir) {
    std::string equal_file = output_dir + "/equal.csv";
    std::string inequal_file = output_dir + "/inequal.csv";
    write_csv(equal_file, equal_pairs);
    write_csv(inequal_file, inequal_pairs);
}

//有两个函数，一个是将数据写入CSV文件的write_csv函数，另一个是将等价和不等价的OJ程序对输出到对应的CSV文件的output函数。