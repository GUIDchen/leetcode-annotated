// 3634. 使数组平衡的最少移除数目 / Minimum Removals to Balance Array
// 核心思路：排序后枚举区间左端点，用二分找到满足 max ≤ min×k 的最长区间，答案即 n 减去最长区间长度
// 时间复杂度 O(n log n)，空间复杂度 O(1)
//
class Solution {  // 题目要求实现的类
public:  // 对外接口
    int minRemoval(vector<int>& nums, int k) {  // 返回使数组平衡所需的最少移除元素个数
        ranges::sort(nums);  // 先排序，之后才能用二分和区间技巧
        int cnt = 0;  // cnt 记录最多可以同时保留的元素个数
        int n = nums.size();  // n 为数组长度
        for (int i = 0; i < n; ++i) {  // 枚举保留区间的左端点 i
            int j = n;  // 右端点 j 先默认取 n（表示整个后缀都可行）
            if (1LL * nums[i] * k <= nums[n - 1]) {  // 只有当 nums[i]×k 不超过最大值时，二分才有意义
                j = upper_bound(nums.begin(), nums.end(), 1LL * nums[i] * k) - nums.begin();  // 用二分找第一个大于 nums[i]×k 的位置，它就是可保留区间的右边界
            }  // if 结束
            cnt = max(cnt, j - i);  // 更新最多可保留的元素个数
        }  // 循环结束
        return n - cnt;  // 总长度减去可保留数目，就是最少移除数目
    }  // 函数结束
};  // 类定义结束
