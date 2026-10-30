// 题目：2864. 最大二进制奇数（Maximum Odd Binary Number）
// 思路：二进制数是奇数当且仅当最低位为 1；因此把 1 个 '1' 放末位，其余 cnt-1 个 '1' 全部放最高位，'0' 排在中间即可最大。
// 时间复杂度：O(n)，统计一次 1 的个数并拼出长度为 n 的串；空间复杂度：O(n)，结果串本身。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string maximumOddBinaryNumber(string s) {  // s：只含 '0' 与 '1' 的输入串，返回重排后的最大奇数
        int cnt = count(s.begin(), s.end(), '1');  // 数出 1 的个数，0 的个数就是 s.size() - cnt
        // 高位堆 cnt-1 个 '1' 让数值最大，接着补齐所有 '0'，末位固定放 '1' 保证结果是奇数
        return string(cnt - 1, '1') + string(s.size() - cnt, '0') + '1';  // 拼接出答案字符串
    }
};