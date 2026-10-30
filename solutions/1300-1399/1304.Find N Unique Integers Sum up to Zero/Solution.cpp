// 题目：1304. 和为零的 N 个不同整数（Find N Unique Integers Sum up to Zero）
// 思路：成对写入 i 与 -i，两两抵消；若 n 为奇数，数组最后一位保持默认的 0 即可。
// 时间复杂度：O(n)，每个位置只写一次；空间复杂度：O(1)，除返回数组外只用常数变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> sumZero(int n) {  // n：需要生成的整数个数
        vector<int> ans(n);  // 结果数组长度固定为 n，值默认初始化为 0
        for (int i = 1, j = 0; i <= n / 2; ++i) {  // i 是成对使用的正数，j 是待写入的下标
            ans[j++] = i;  // 写入正数 i
            ans[j++] = -i;  // 写入对应的负数，与正数相互抵消
        }
        return ans;  // 奇数 n 时剩下的一位仍是 0，总和依然为 0
    }
};