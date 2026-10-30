// 题目：910. 最小差值 II（Smallest Range II）
// 核心思路：先排序，再枚举分界点：分界点左侧元素统一加 k、右侧统一减 k，答案一定出现在这 O(n) 种划分中，每种划分只需用两端极值算出极差。
// 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(1)，除排序外只用了常数个变量。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int smallestRangeII(vector<int>& nums, int k) {  // nums：输入数组；k：每个元素可以加或减的固定幅度
        sort(nums.begin(), nums.end());  // 升序排序：排序后最优方案必然是「某个前缀加 k、后缀减 k」
        int n = nums.size();  // 缓存长度，避免循环中反复调用 size()
        int ans = nums[n - 1] - nums[0];  // 初始答案：全部同向加减时最大值和最小值同时平移，极差保持不变
        for (int i = 1; i < n; ++i) {  // 枚举分界下标 i：i 之前的元素加 k，i 及之后的元素减 k
            int mi = min(nums[0] + k, nums[i] - k);  // 划分后的最小值只可能是 nums[0]+k（左段最小）或 nums[i]-k（右段最小）
            int mx = max(nums[i - 1] + k, nums[n - 1] - k);  // 划分后的最大值只可能是 nums[i-1]+k（左段最大）或 nums[n-1]-k（右段最大）
            ans = min(ans, mx - mi);  // 当前划分的极差是 mx-mi，用它更新全局最优答案
        }  // 分界点右移，继续尝试下一种划分
        return ans;  // 所有划分中的最小极差即为答案
    }  // 方法结束
};  // 类定义结束