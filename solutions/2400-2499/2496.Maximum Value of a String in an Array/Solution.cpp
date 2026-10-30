// 题目：2496. 数组中字符串的最大值（Maximum Value of a String in an Array）
// 思路：用 lambda 把每个字符串换算成值（全数字取数值，含字母取长度），再取最大值。
// 时间复杂度：O(所有字符总数)；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maximumValue(vector<string>& strs) {  // strs 是字符串数组，返回其中最大的「值」
        auto f = [](string& s) {  // 局部 lambda：负责把单个字符串换算成题目定义的值
            int x = 0;  // 纯数字串的数值累加器
            for (char& c : s) {  // 逐字符扫描
                if (!isdigit(c)) {  // 遇到非数字字符
                    return (int) s.size();  // 含字母时按「字符串长度」作为值返回
                }
                x = x * 10 + c - '0';  // 十进制累加：先左移一位再加上当前数字字符对应的值
            }
            return x;  // 全是数字，返回换算出的整数
        };
        int ans = 0;  // 记录目前的最大值
        for (auto& s : strs) {  // 遍历每个字符串
            ans = max(ans, f(s));  // 用当前字符串的值更新答案
        }
        return ans;  // 返回最大值
    }
};