// 题目：1805. 字符串中不同整数的数目（Number of Different Integers in a String）
// 思路：顺序扫描字符串，遇到数字段就跳过前导零、截取到该段结束，把去零后的子串放进哈希集合去重，集合大小即答案。
// 时间复杂度：O(n)，每段数字只被扫描一次、每个字符最多进一个子串；空间复杂度：O(n)，集合存放各段数字子串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int numDifferentIntegers(string word) {  // word 只含字母和数字，返回其中不同非负整数的个数
        unordered_set<string> s;  // 用字符串存去掉前导零后的整数，避免大整数溢出
        int n = word.size();  // n 为字符串长度
        for (int i = 0; i < n; ++i) {  // 从左到右扫描字符串
            if (isdigit(word[i])) {  // 发现一段数字的开头
                while (i < n && word[i] == '0') ++i;  // 跳过前导零，使 "001" 与 "1" 归一（全零段会一直跳到段尾）
                int j = i;  // j 指向有效数字的起点，同时用作向后扫描的指针
                while (j < n && isdigit(word[j])) ++j;  // 一直走到这段数字结束
                s.insert(word.substr(i, j - i));  // 截取剩余数字部分放入集合，自动去重
                i = j;  // 跳过整段数字，避免重复处理
            }
        }
        return s.size();  // 集合大小就是不同整数的个数
    }
};