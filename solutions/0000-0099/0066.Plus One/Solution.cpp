// 题目：66. 加一（Plus One）
// 思路：从最低位开始逐位加一并逢十置零，若某位加完不为 0 说明没有进位可就地返回；所有位都变 0 时在最前面补 1。
// 时间复杂度：O(n)，最坏要扫完所有 n 位；空间复杂度：O(1)，除返回值外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> plusOne(vector<int>& digits) {  // digits：按高位到低位存放的数字数组，原地修改后返回
        for (int i = digits.size() - 1; i >= 0; --i) {  // 从个位（数组末位）向高位倒序遍历
            ++digits[i];  // 把当前这一位加上 1
            digits[i] %= 10;  // 取模 10：若原来是 9，加一后变成 0 并向下一位进 1
            if (digits[i] != 0) return digits;  // 加完还不是 0，说明没进位，后续高位不受影响，直接返回
        }
        digits.insert(digits.begin(), 1);  // 全部位都变成了 0（例如 999 -> 000），说明最高位还进了一位，前插 1
        return digits;  // 返回补上最高位后的结果
    }
};