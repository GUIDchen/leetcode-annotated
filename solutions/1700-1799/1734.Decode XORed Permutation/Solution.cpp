// 题目：1734. 解码异或后的排列（Decode XORed Permutation）
// 思路：encoded[i] = perm[i] ^ perm[i+1]。先把 encoded 的偶数下标项异或得到 a，再把 1..n 全异或得到 b，则 perm[n-1] = a ^ b，最后从后往前逐项反推。
// 时间复杂度：O(n)，两趟线性扫描加一趟回推；空间复杂度：O(n)，额外的结果数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> decode(vector<int>& encoded) {  // encoded 的长度是 n-1，由原排列相邻两项异或得到
        int n = encoded.size() + 1;  // n 是原排列的长度
        int a = 0, b = 0;  // a 累积 encoded 的偶数下标项，b 累积 1..n 的全部异或
        for (int i = 0; i < n - 1; i += 2) {  // 只走偶数下标 0, 2, 4, ...
            a ^= encoded[i];  // 得到 perm[0] ^ perm[2] ^ perm[4] ...
        }
        for (int i = 1; i <= n; ++i) {  // 遍历 1..n
            b ^= i;  // 由 x^x=0 可知，b 恰好等于 perm 全部元素的异或
        }
        vector<int> perm(n);  // 预先分配长度为 n 的结果数组
        perm[n - 1] = a ^ b;  // a 与 b 中其余项两两抵消，只剩下 perm[n-1]
        for (int i = n - 2; ~i; --i) {  // ~i 在 i<0 时为 0，等价于 i >= 0，可省一次比较
            perm[i] = encoded[i] ^ perm[i + 1];  // 由 perm[i] ^ perm[i+1] = encoded[i] 反解出 perm[i]
        }
        return perm;  // 返回还原出的原排列
    }
};