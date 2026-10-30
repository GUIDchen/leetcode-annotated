// 题目：2917. 找出数组中的 K-or 值（Find the K-or of an Array）
// 思路：按位统计，某一二进制位上为 1 的元素不少于 k 个，就把答案的该位置 1。
// 时间复杂度：O(32n)，逐位扫一遍数组；空间复杂度：O(1)，只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findKOr(vector<int>& nums, int k) {  // nums 是输入数组，k 是阈值；返回 K-or 值
        int ans = 0;  // 按位构造答案
        for (int i = 0; i < 32; ++i) {  // 依次检查第 0 到第 31 个二进制位
            int cnt = 0;  // 统计当前这一位上为 1 的元素个数
            for (int x : nums) {  // 遍历数组里的每个数
                cnt += (x >> i & 1);  // 把 x 右移 i 位再与 1 相与，得到第 i 位并累加
            }
            if (cnt >= k) {  // 至少有 k 个数的第 i 位为 1
                ans |= 1 << i;  // 把答案的第 i 位置为 1
            }
        }
        return ans;  // 返回按位构造出的 K-or 值
    }
};