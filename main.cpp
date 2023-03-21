#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

#include "input.cpp"
#include "equal.cpp"
#include "output.cpp"

int main() {
    // 定义需要遍历的文件夹路径
    std::string folder_path = "./input";

    // 定义每组测试输入的数量
    int test_count = 10;

    // 定义输出文件夹路径
    std::string output_dir = "./output";

    // 读取所有的OJ程序
    auto oj_files = read_files(folder_path);

    // 定义相对路径存储等价和不等价的OJ程序
    std::vector<std::pair<std::string, std::string>> equal_pairs;
    std::vector<std::pair<std::string, std::string>> inequal_pairs;

    // 遍历所有OJ程序，并进行判断
    for (int i = 0; i < oj_files.size(); i++) {
        for (int j = i + 1; j < oj_files.size(); j++) {
            // 构造每组测试输入
            auto test_inputs = generate_inputs(folder_path + "/stdin_format.txt", test_count);

            // 遍历每组测试输入，并进行比较
            bool is_equal = true;
            for (auto input : test_inputs) {
                if (!judge_equal(oj_files[i], oj_files[j], input, output_dir)) {
                    is_equal = false;
                    break;
                }
            }

            // 根据比较结果将OJ程序相对路径存入对应的vector中
            if (is_equal) {
                equal_pairs.push_back(std::make_pair(oj_files[i], oj_files[j]));
            } else {
                inequal_pairs.push_back(std::make_pair(oj_files[i], oj_files[j]));
            }
        }
    }

    // 输出结果到CSV文件
    write_output("equal.csv", equal_pairs);
    write_output("inequal.csv", inequal_pairs);

    return 0;
}
