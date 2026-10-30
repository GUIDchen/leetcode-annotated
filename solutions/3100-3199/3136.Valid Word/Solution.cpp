// 题目：3136. 有效单词（Valid Word）
// 思路：先把 5 个元音字母登记进布尔表，再扫一遍单词：字母按元音/辅音归类，数字放行，出现其他字符直接判非法。
// 时间复杂度：O(n)，n 为单词长度；空间复杂度：O(1)，只用 26 个字母的定长标记表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isValid(string word) {  // word：待校验的单词，返回它是否有效
        if (word.size() < 3) {  // 题目要求单词长度至少为 3
            return false;  // 长度不足直接判非法
        }  // if 结束
        bool has_vowel = false, has_consonant = false;  // 分别记录是否已出现元音、是否已出现辅音
        bool vs[26]{};  // 元音标记表：vs[c-'a'] 为 true 表示字符 c 是元音
        string vowels = "aeiou";  // 题目限定的五个元音字母
        for (char c : vowels) {  // 逐个把元音登记进标记表
            vs[c - 'a'] = true;  // 用字符与小写 a 的差值作为下标
        }  // 元音登记结束
        for (char c : word) {  // 遍历单词的每个字符
            if (isalpha(c)) {  // 是字母才需要区分元音与辅音
                if (vs[tolower(c) - 'a']) {  // 统一转成小写后查表，判断是否为元音
                    has_vowel = true;  // 标记已出现元音
                } else {  // 不是元音的情形
                    has_consonant = true;  // 字母且非元音，那就是辅音，标记已出现辅音
                }  // 元音/辅音判断结束
            } else if (!isdigit(c)) {  // 既不是字母也不是数字，属于非法字符
                return false;  // 含非法字符，整词无效
            }  // 字符类型判断结束
        }  // 单词遍历结束
        return has_vowel && has_consonant;  // 元音和辅音都至少出现一次才算有效单词
    }  // 方法结束
};  // 类定义结束