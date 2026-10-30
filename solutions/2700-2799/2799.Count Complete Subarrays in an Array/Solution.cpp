// 题目：2799. 统计完全子数组的数目（Count Complete Subarrays in an Array）
// 思路：先求整个数组的元素种类数 cnt，再枚举起点 i 用集合向右扩展，集合大小等于 cnt 即为完全子数组。
// 时间复杂度：O(n^2)，最坏情况枚举所有子数组；空间复杂度：O(n)，集合最多保存 n 个不同的值。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countCompleteSubarrays(vector<int>& nums) {  // nums：输入数组；返回完全子数组的个数
        unordered_set<int> s(nums.begin(), nums.end());  // 用整个数组构造集合，去重后的大小就是「完全」所需的种类数
        int cnt = s.size();  // cnt：整个数组的元素种类数，子数组必须覆盖全部这些种类
        int ans = 0, n = nums.size();  // ans：答案计数器；n：数组长度
        for (int i = 0; i < n; ++i) {  // 枚举子数组的左端点 i
            s.clear();  // 复用同一个集合，先清空，准备统计以 i 为起点的子数组
            for (int j = i; j < n; ++j) {  // 枚举右端点 j，从 i 开始逐步向右扩展
                s.insert(nums[j]);  // 把新纳入的元素加入集合，集合大小即当前子数组的种类数
                if (s.size() == cnt) {  // 种类数达到全局种类数，说明当前子数组是「完全子数组」
                    ++ans;  // 答案加一
                }
            }
        }
        return ans;  // 返回完全子数组的总数
    }
};