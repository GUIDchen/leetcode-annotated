// 3758. 将数字词转换为数字（Convert Number Words to Digits）
// 核心思路：按数字 0~9 顺序准备英文单词表，从左到右在每个位置尝试与单词做前缀匹配，命中就把该数字写入答案并跳过整个单词长度。
// 复杂度：时间 O(n × 10 × 5) 即 O(n)，空间 O(1)（不含答案）。
class Solution {  // 定义解法类
public:  // 公有接口
    string convertNumber(string s) {  // 接口：把由英文数字单词拼成的字符串转换回数字串
        vector<string> d = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};  // d 按 0~9 的顺序保存对应的英文单词
        int n = s.length();  // n 为输入串长度
        string ans;  // ans 收集转换出的数字字符
        for (int i = 0; i < n; ++i) {  // 从左到右扫描输入串的每个位置
            for (int j = 0; j < d.size(); ++j) {  // 依次尝试 0~9 这十个单词
                string t = d[j];  // 取出当前候选单词
                int m = t.length();  // m 为该单词长度，即要跳过的字符数
                if (i + m <= n && s.substr(i, m) == t) {  // 先保证不越界，再判断从 i 起是否正好是这个词
                    ans += to_string(j);  // 命中则把对应数字字符追加到答案
                    i += m - 1;  // 跳过整个单词（循环末尾还有一次 ++i，故减一）
                    break;  // 同一个位置无需再试别的单词
                }  // if 结束
            }  // 内层 for 结束
        }  // 外层 for 结束
        return ans;  // 返回转换得到的数字串
    }  // 方法结束
};  // 类定义结束
