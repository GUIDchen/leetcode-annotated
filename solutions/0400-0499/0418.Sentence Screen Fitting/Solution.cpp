// 题目：418. 屏幕可显示句子的数量（Sentence Screen Fitting，会员题）
// 思路：把句子拼成「每个单词后缀一个空格」的循环串，用 cur 跨行累计已排下的字符数，每行先加 cols 再按空格边界回退。
// 时间复杂度：O(rows * cols)，每行最坏回退 cols 步；空间复杂度：O(L)，L 是整个句子的字符数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int wordsTyping(vector<string>& sentence, int rows, int cols) {  // sentence 是单词列表，rows/cols 是屏幕行数与每行字符数，返回能完整显示的句子遍数
        string s;  // s 用来存放拼接后的循环串
        for (auto& t : sentence) {  // 逐个单词拼接
            s += t;  // 先追加单词本身
            s += " ";  // 单词之间（以及句尾）都留一个空格，方便按空格切分
        }  // 拼接结束
        int m = s.size();  // m 是循环串长度，用取模实现无限重复
        int cur = 0;  // cur 表示「已经排下的字符总数」，跨行累计
        while (rows--) {  // 每处理一行（rows 递减到 0 为止）
            cur += cols;  // 先假设本行能放满 cols 个字符
            if (s[cur % m] == ' ') {  // 若这个位置正好是空格，说明上一个单词刚好在这一行结束
                ++cur;  // 跳过这个空格，下一个单词从下一行开头开始
            } else {  // 否则说明某个单词被行尾截断了
                while (cur && s[(cur - 1) % m] != ' ') {  // 往回退，直到退到某个空格之后（即完整的单词边界）
                    --cur;  // 退一个字符
                }  // 回退结束
            }  // if-else 分支结束
        }  // 所有行处理完毕
        return cur / m;  // 一个完整句子占 m 个字符（含句尾空格），cur / m 就是完整的遍数
    }  // wordsTyping 方法结束
};  // Solution 类结束