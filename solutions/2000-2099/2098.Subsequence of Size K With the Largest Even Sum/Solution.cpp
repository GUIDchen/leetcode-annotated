// 题目：2098. 长度为 K 的最大偶数和子序列（Subsequence of Size K With the Largest Even Sum）
// 思路：先取最大的 k 个数；若和为奇数，则用「去掉已选最小偶数换入未选最大奇数」或「去掉已选最小奇数换入未选最大偶数」修正奇偶性，取较优者。
// 时间复杂度：O(n log n)，主要是排序；空间复杂度：O(1)，只用了常数个辅助变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long largestEvenSum(vector<int>& nums, int k) {  // nums：候选数组；k：子序列长度；返回最大偶数和，无解时 -1
        sort(nums.begin(), nums.end());  // 升序排序，方便从尾部取最大元素
        long long ans = 0;  // 当前选中的 k 个元素之和（可能很大，用 long long）
        int n = nums.size();  // 数组长度
        for (int i = 0; i < k; ++i) {  // 从尾部取最大的 k 个数
            ans += nums[n - i - 1];  // 累加倒数第 i+1 个元素
        }
        if (ans % 2 == 0) {  // 和已经是偶数
            return ans;  // 直接就是最优解
        }
        const int inf = 1 << 29;  // 足够大的「不存在」占位值
        int mx1 = -inf, mx2 = -inf;  // 未选部分的：最大奇数 mx1、最大偶数 mx2
        for (int i = 0; i < n - k; ++i) {  // 遍历没有被选中的较小部分
            if (nums[i] % 2) {  // 是奇数
                mx1 = nums[i];  // 因为升序，越往后越大，最终得到最大奇数
            } else {  // 是偶数
                mx2 = nums[i];  // 同理得到最大偶数
            }
        }
        int mi1 = inf, mi2 = inf;  // 已选部分的：最小偶数 mi1、最小奇数 mi2
        for (int i = n - 1; i >= n - k; --i) {  // 从大到小遍历被选中的 k 个数
            if (nums[i] % 2) {  // 是奇数
                mi2 = nums[i];  // 越往后越小，最终得到最小奇数
            } else {  // 是偶数
                mi1 = nums[i];  // 同理得到最小偶数
            }
        }
        ans = max(ans - mi1 + mx1, ans - mi2 + mx2);  // 两种修正方案取较优：去掉最小偶数换入最大奇数，或去掉最小奇数换入最大偶数
        return ans < 0 ? -1 : ans;  // 负数（说明换了不存在的值/无解）时返回 -1，否则返回和
    }
};