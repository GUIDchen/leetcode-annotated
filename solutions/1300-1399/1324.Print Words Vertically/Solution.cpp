// 题目：1324. 竖直打印单词（Print Words Vertically）
// 思路：按空格切出所有单词，记下最长单词长度 n 作为输出行数；逐列 j 取每个单词的第 j 个字符（越界补空格），去掉行尾空格后作为第 j 行。
// 时间复杂度：O(n * L)，L 为单词个数，每列都要扫一遍所有单词；空间复杂度：O(n * L)，存放全部输出字符。
class Solution {  // 题解类
public:  // 对外暴露题解接口
    vector<string> printVertically(string s) {  // s：由若干空格分隔的单词组成的字符串
        stringstream ss(s);  // 用字符串流按空白自动切分
        vector<string> words;  // 保存切出来的所有单词，保持原顺序
        string word;  // 临时变量，接收每次 >> 取出的单词
        int n = 0;  // n 记录最长单词长度，也就是输出的总行数
        while (ss >> word) {  // 逐个读取单词，流读完（failbit）时循环结束
            words.emplace_back(word);  // 原地构造，避免拷贝，把单词追加到列表
            n = max(n, (int) word.size());  // 更新最长单词长度
        }  // 切分结束
        vector<string> ans;  // 结果：每个元素是一列（也就是竖直打印的一行）
        for (int j = 0; j < n; ++j) {  // 枚举列下标 j，共 n 列
            string t;  // 当前这一列的字符缓冲区
            for (auto& w : words) {  // 按单词顺序拼接该列的字符
                t += j < w.size() ? w[j] : ' ';  // 单词不够长就用空格补齐，保证后面的对齐
            }  // 内层遍历结束
            while (t.size() && t.back() == ' ') {  // 去掉行尾多余的空格（题目要求行尾不补空格）
                t.pop_back();  // 尾字符是空格就弹出，直到尾字符不是空格
            }  // 去尾空格结束
            ans.emplace_back(t);  // 收下这一行结果
        }  // 列循环结束
        return ans;  // 返回全部列
    }  // 方法结束
};  // 类定义结束