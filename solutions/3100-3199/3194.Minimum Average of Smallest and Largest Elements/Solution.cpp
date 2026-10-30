// 题目：3194. 最小元素和最大元素的最小平均值（Minimum Average of Smallest and Largest Elements）
// 思路：先排序，最优策略一定是每次取当前最小值与最大值配对；把每对的和求最小，再除以 2 得到最小平均值。
// 时间复杂度：O(n log n)，瓶颈在排序；空间复杂度：O(1)，除排序外只用常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    double minimumAverage(vector<int>& nums) {  // nums：输入整数数组，返回所有配对平均值的下界
        sort(nums.begin(), nums.end());  // 升序排序，便于从两端取最小值与最大值
        int ans = 1 << 30, n = nums.size();  // ans 初始化为一个足够大的数，n 为数组长度
        for (int i = 0; i < n; ++i) {  // 枚举配对：第 i 小元素与第 i 大元素
            ans = min(ans, nums[i] + nums[n - i - 1]);  // 用「两数之和」比较即可，避免浮点误差
        }
        return ans / 2.0;  // 用 2.0 触发浮点除法，得到最小平均值
    }
};