// 3775. 反转元音数相同的单词 / Reverse Words With Same Vowel Count
// 核心思路：先统计第一个单词的元音个数作为基准，再用 stringstream 逐个读出单词，元音数与基准相同的单词原地反转，最后拼回句子。
// 复杂度：时间复杂度 O(n)，空间复杂度 O(n)，其中 n 为字符串长度。
class Solution {  // 定义题解类
public:  // 公有成员
    string reverseWords(string s) {  // 返回把元音数相同的单词反转之后的新句子
        stringstream ss(s);  // 用字符串流按空白切分单词
        string w;  // 当前读到的单词
        ss >> w;  // 先读出第一个单词作为基准
        int cnt = calc(w);  // 第一个单词的元音字母个数

        string ans = w;  // 答案先放入第一个单词

        while (ss >> w) {  // 依次处理后面读到的每个单词
            ans.push_back(' ');  // 单词之间补一个空格
            if (calc(w) == cnt) {  // 元音个数与第一个单词相同
                reverse(w.begin(), w.end());  // 原地反转该单词
            }  // 判断结束
            ans += w;  // 把处理后的单词拼进答案
        }  // 所有单词处理完毕

        return ans;  // 返回拼接结果
    }  // 方法结束

private:  // 私有辅助函数区
    int calc(const string& w) {  // 统计单词中的元音字母个数
        return count_if(w.begin(), w.end(), [](char c) {  // 遍历每个字符并计数
            return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';  // 判断字符是否为元音字母
        });  // 范围遍历结束
    }  // 辅助函数结束
};  // 类定义结束
