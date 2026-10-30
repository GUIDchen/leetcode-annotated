// 题目：171. Excel 表列序号（Excel Sheet Column Number）
// 思路：把列标题看成 26 进制数，从左到右逐位累加：ans = ans * 26 + 当前字母的序号（A=1 … Z=26）。
// 时间复杂度：O(n)，n 为标题长度；空间复杂度：O(1)，只用一个累加变量。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    int titleToNumber(string columnTitle) {  // 把 Excel 列标题（如 AB）转换成对应的列序号（如 28）
        int ans = 0;  // 结果：按 26 进制逐位累积
        for (char& c : columnTitle) {  // 从左到右处理标题中的每个字符
            ans = ans * 26 + (c - 'A' + 1);  // 相当于 26 进制左移一位，再加上当前字母的值（A 记 1，Z 记 26）
        }  // 循环结束
        return ans;  // 返回最终列序号
    }  // 方法结束
};  // 类定义结束