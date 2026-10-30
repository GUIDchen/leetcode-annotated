// 题目：2710. 移除字符串中的尾随零（Remove Trailing Zeros From a String）
// 思路：从末尾往前，只要最后一个字符是 '0' 就弹出，直到末尾不是 '0' 为止。
// 时间复杂度：O(n)，每个尾部零各弹出一次；空间复杂度：O(1)，只在原字符串上原地删改。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string removeTrailingZeros(string num) {  // num：只由数字字符组成的字符串
        while (num.back() == '0') {  // 只要末尾还是 '0' 就继续删
            num.pop_back();  // 删掉末尾字符（题目保证末尾不会全是 0，因此不会删空）
        }
        return num;  // 返回去掉尾随零后的非空字符串
    }
};