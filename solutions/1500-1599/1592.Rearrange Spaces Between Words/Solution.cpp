// 题目：1592. 重新排列单词间的空格（Rearrange Spaces Between Words）
// 思路：统计空格总数与单词个数，把空格尽量均匀地放进单词间隙，除不尽的余数补在末尾。
// 时间复杂度：O(n)，扫描与拼接都是线性；空间复杂度：O(n)，保存切分出的单词。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string reorderSpaces(string text) {  // text 为原始字符串，单词之间可能夹着多余空格
        int spaces = ranges::count(text, ' ');  // C++20 的 ranges::count 统计空格总数
        auto words = split(text);  // 按空白切分出所有单词

        if (words.size() == 1) {  // 只有一个单词时没有“间隙”可分
            return words[0] + string(spaces, ' ');  // 所有空格全部追加在单词后面
        }

        int cnt = spaces / (words.size() - 1);  // 单词之间每个间隙放 cnt 个空格
        int mod = spaces % (words.size() - 1);  // 除不尽的剩余空格数

        string result = join(words, string(cnt, ' '));  // 用 cnt 个空格把单词连接起来
        result += string(mod, ' ');  // 剩余空格补在末尾

        return result;  // 返回重新排列后的字符串
    }

private:  // 内部辅助函数
    vector<string> split(const string& text) {  // 按空白切分出单词
        vector<string> words;  // 保存切分结果
        istringstream stream(text);  // 借用字符串流做分词
        string word;  // 临时存放一个单词
        while (stream >> word) {  // operator>> 会自动跳过任意长度的连续空白
            words.push_back(word);  // 收集单词
        }
        return words;  // 返回单词列表
    }

    string join(const vector<string>& words, const string& separator) {  // 用 separator 连接所有单词
        ostringstream result;  // 拼接到输出流中
        for (size_t i = 0; i < words.size(); ++i) {  // 逐个单词追加
            result << words[i];  // 先写入单词本身
            if (i < words.size() - 1) {  // 最后一个单词后面不加分隔符
                result << separator;  // 单词之间写入分隔符
            }
        }
        return result.str();  // 取出拼接好的字符串
    }
};
