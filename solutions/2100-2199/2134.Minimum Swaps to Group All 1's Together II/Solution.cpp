// 题目：2134. 最少交换次数来组合所有的 1 II（Minimum Swaps to Group All 1's Together II）
// 思路：1 的总数为 k，最终必然聚成一段长度 k 的环形窗口；滑动枚举所有长度 k 的窗口，窗口内 1 最多为 mx 时，只需把窗口内 k-mx 个 0 与窗口外的 1 交换。
// 时间复杂度：O(n)，窗口只滑动一圈；空间复杂度：O(1)，只用了常数个额外变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minSwaps(vector<int>& nums) {  // nums：只含 0/1 的环形数组，返回最少的交换次数
        int k = accumulate(nums.begin(), nums.end(), 0);  // k 是数组中 1 的总个数，也就是最终目标窗口的长度
        int n = nums.size();  // n 是数组长度，配合取模实现环形访问
        int cnt = accumulate(nums.begin(), nums.begin() + k, 0);  // 初始窗口 [0, k) 内 1 的个数
        int mx = cnt;  // mx 记录所有长度为 k 的窗口中 1 的最多个数
        for (int i = k; i < n + k; ++i) {  // 窗口右端从 k 滑到 n+k-1，正好覆盖环形数组的全部 n 个起点
            cnt += nums[i % n] - nums[(i - k + n) % n];  // 右端加入 nums[i % n]，左端移出 nums[(i - k + n) % n]
            mx = max(mx, cnt);  // 更新窗口内 1 的个数最大值
        }  // 滑动窗口枚举结束
        return k - mx;  // 窗口内已有 mx 个 1，还需要把 k-mx 个 0 换成窗口外的 1
    }  // minSwaps 方法结束
};  // Solution 类结束