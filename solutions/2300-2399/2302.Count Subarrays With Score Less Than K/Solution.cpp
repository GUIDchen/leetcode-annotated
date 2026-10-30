// 题目：2302. 统计得分小于 K 的子数组数目（Count Subarrays With Score Less Than K）
// 思路：先求前缀和，再枚举右端点 i，对以 i 结尾的子数组长度做二分：区间和乘长度随长度单调递增，二分出满足得分小于 k 的最大长度，累加个数。
// 时间复杂度：O(n log n)，每个右端点做一次二分；空间复杂度：O(n)，需要前缀和数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long countSubarrays(vector<int>& nums, long long k) {  // nums：正整数数组；k：得分上限
        int n = nums.size();  // 数组长度
        long long s[n + 1];  // 前缀和数组，s[i] 表示前 i 个元素之和，多留一格便于表示空前缀
        s[0] = 0;  // 空前缀和为 0
        for (int i = 0; i < n; ++i) {  // 顺序递推前缀和
            s[i + 1] = s[i] + nums[i];  // 累加当前元素，得到下一个前缀和
        }  // 前缀和计算结束
        long long ans = 0;  // 统计满足得分小于 k 的子数组个数
        for (int i = 1; i <= n; ++i) {  // 枚举右端点 i，前缀和下标从 1 开始
            int l = 0, r = i;  // 二分区间：以 i 结尾的子数组长度可以取 0 到 i
            while (l < r) {  // 二分找满足条件的最大长度
                int mid = (l + r + 1) >> 1;  // 上取整的中点，配合下面的 l 取 mid 避免死循环
                if ((s[i] - s[i - mid]) * mid < k) {  // 区间 [i-mid, i) 的元素和乘上长度 mid 就是得分，判断是否小于 k
                    l = mid;  // 长度 mid 可行，答案在右半区，保留 mid
                } else {  // 得分不小于 k，说明长度过大
                    r = mid - 1;  // 收缩右边界
                }  // 分支结束
            }  // 二分结束
            ans += l;  // 长度为 1 到 l 的子数组都满足条件，共 l 个
        }  // 右端点枚举结束
        return ans;  // 返回满足条件的子数组总数
    }  // 方法结束
};  // 类定义结束