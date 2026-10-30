// 题目：402. 移掉 K 位数字（Remove K Digits）
// 思路：单调栈 + 贪心。从左到右扫描，只要还能删且栈顶比当前位大，就弹掉栈顶（让高位更小），最后删掉多余的名额、去掉前导 0。
// 时间复杂度：O(n)，每个数字最多入栈出栈各一次；空间复杂度：O(n)，栈最多保存 n 个字符。
class Solution {  // LeetCode 约定的题解类
public:  // 方法对外可见
    string removeKdigits(string num, int k) {  // 从数字字符串 num 中删掉 k 个字符，使剩下的数字最小
        string stk;  // 用字符串当单调栈，栈中始终保持数字不降
        for (char& c : num) {  // 从左到右逐位扫描数字
            while (k && stk.size() && stk.back() > c) {  // 只要还能删、栈非空、且栈顶比当前位大，就弹出栈顶：高位更大必然更差
                stk.pop_back();  // 弹出比当前位大的栈顶
                --k;  // 消耗一次删除名额
            }
            stk += c;  // 当前位入栈，继续向后看
        }
        while (k--) {  // 扫描结束后还有删除名额，说明剩余数字已经不降，只能从末尾删
            stk.pop_back();  // 弹出末尾（也是最大的）一位
        }
        int i = 0;  // i 用来跳过前导 0
        for (; i < stk.size() && stk[i] == '0'; ++i) {  // 跳过所有前导 0（循环体为空）
        }
        string ans = stk.substr(i);  // 截取非前导 0 的部分作为答案
        return ans == "" ? "0" : ans;  // 结果为空（全被删光或全是 0）时按题目要求返回 "0"
    }
};  // 题解类结束