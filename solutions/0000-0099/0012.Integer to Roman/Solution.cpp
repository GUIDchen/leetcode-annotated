// 题目：12. 整数转罗马数字（Integer to Roman）
// 思路：13 个「符号/数值」按数值从大到小配对，贪心地反复减去最大可用数值并拼接符号（含六个减法特例）。
// 时间复杂度：O(1)，输出长度有常数上界；空间复杂度：O(1)，只存两张常数表和一个结果串。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string intToRoman(int num) {  // num 是待转换的整数（题目范围 1..3999）
        vector<string> cs = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};  // 罗马符号，已拆出六个减法组合
        vector<int> vs = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};  // 与 cs 一一对应的数值，严格递减
        string ans;  // 结果串，初始为空
        for (int i = 0; i < cs.size(); ++i) {  // 从最大数值开始贪心
            while (num >= vs[i]) {  // 剩余数值还能减掉当前数值
                num -= vs[i];  // 减去它，剩下的继续用更小的符号表示
                ans += cs[i];  // 把对应符号拼到结果末尾
            }
        }
        return ans;  // 返回转换结果
    }
};
