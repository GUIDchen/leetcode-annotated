// 题目：989. 数组形式的整数加法（Add to Array-Form of Integer）
// 思路：从个位开始把 num 的当前位加到 k 上，逐位取余得到结果，最后反转成高位在前。
// 时间复杂度：O(n + log k)，n 为 num 长度，多出的位数来自 k；空间复杂度：O(1)，除返回数组外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> addToArrayForm(vector<int>& num, int k) {  // num：数组形式的整数（高位在前）；k：要加上的整数；返回相加后的数组形式
        vector<int> ans;  // 结果先按低位到高位追加，最后再整体反转
        for (int i = num.size() - 1; i >= 0 || k > 0; --i) {  // i 从个位开始向前走；num 用完后只要 k 还有剩余就继续补高位
            k += (i >= 0 ? num[i] : 0);  // 取 num 当前位（已用完则视为 0）并累加到 k，k 同时充当剩余值与进位
            ans.push_back(k % 10);  // 当前位的结果是 k 的个位数字
            k /= 10;  // 去掉刚处理的个位，剩下的部分留给更高位
        }
        ranges::reverse(ans);  // C++20 ranges::reverse 把低位在前的 ans 翻成高位在前
        return ans;  // 返回题目要求的数组形式
    }
};  // 类定义结束
