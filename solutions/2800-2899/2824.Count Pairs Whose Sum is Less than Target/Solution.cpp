// 题目：2824. 统计和小于目标的下标对数目（Count Pairs Whose Sum is Less than Target）
// 思路：先升序排序，再枚举较大的下标 j，用二分在它左边数出有多少个 nums[i] 满足 nums[i] + nums[j] < target。
// 时间复杂度：O(n log n)，排序 O(n log n) 加 n 次二分 O(log n)；空间复杂度：O(log n)，排序的递归栈开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countPairs(vector<int>& nums, int target) {  // nums：输入数组；target：两数之和必须严格小于它的目标值；返回满足条件的下标对数目
        sort(nums.begin(), nums.end());  // 升序排序，让「比某个值小的元素有多少个」可以直接用二分数出来
        int ans = 0;  // 答案累加器，记录所有满足 i < j 且两数之和小于 target 的下标对数量
        for (int j = 0; j < nums.size(); ++j) {  // 枚举下标对中较大的那个下标 j
            int i = lower_bound(nums.begin(), nums.begin() + j, target - nums[j]) - nums.begin();  // 在 [0, j) 内二分出第一个大于等于 target - nums[j] 的位置，它的下标正好等于能与 nums[j] 配对的 i 的个数
            ans += i;  // 把以 j 为较大下标的合法对数累加进答案
        }  // 所有较大的下标都枚举完毕
        return ans;  // 返回统计到的下标对总数
    }  // 方法结束
};  // 类定义结束