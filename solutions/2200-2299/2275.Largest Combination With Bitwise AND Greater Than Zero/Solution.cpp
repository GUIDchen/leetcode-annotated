// 题目：2275. 按位与结果大于零的最长组合（Largest Combination With Bitwise AND Greater Than Zero）
// 思路：组合的按位与大于 0，等价于存在某一位在组合中所有数字里都为 1；逐位统计该位为 1 的数字个数，取最大。
// 时间复杂度：O(n × log M)，M 为最大元素（最多 30 位）；空间复杂度：O(1)，只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int largestCombination(vector<int>& candidates) {  // candidates：候选数字数组；返回按位与大于 0 的最长子集长度
        int mx = *max_element(candidates.begin(), candidates.end());  // 找出最大值，它的二进制位数决定需要枚举多少位
        int m = 32 - __builtin_clz(mx);  // __builtin_clz 统计前导零的个数，用 32 减它即得最高有效位的位数
        int ans = 0;  // 记录所有比特位中「1 的个数」的最大值，也就是答案
        for (int i = 0; i < m; ++i) {  // 只需枚举到最高有效位，更高位全是 0，不可能有贡献
            int cnt = 0;  // 统计当前第 i 位上为 1 的数字个数
            for (int x : candidates) {  // 遍历每一个候选数字
                cnt += x >> i & 1;  // 右移 i 位后与 1 取与，取出第 i 位的值并累加（>> 优先级高于 &）
            }
            ans = max(ans, cnt);  // 用当前位上的 1 的个数更新答案
        }
        return ans;  // 返回所有位中 1 的个数的最大值
    }
};
