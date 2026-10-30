// 题目：2863. 最长半递减子数组的长度（Maximum Length of Semi-Decreasing Subarrays）
// 思路：下标按值分组，值从大到小扫描；k 维护「已扫描过的更大值中出现的最小下标」，用当前值的最大下标与 k 配对得到半递减子数组长度。
// 时间复杂度：O(n log n)，map 的插入与遍历；空间复杂度：O(n)，保存每个元素的下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxSubarrayLength(vector<int>& nums) {  // nums：输入数组，返回最长半递减子数组的长度
        map<int, vector<int>, greater<int>> d;  // 值 → 该值出现的所有下标；greater 让键按从大到小排列
        for (int i = 0; i < nums.size(); ++i) {  // 从左到右扫描一遍，收集每种值的下标
            d[nums[i]].push_back(i);  // 把当前下标追加到对应值的列表末尾，列表因此保持升序
        }
        int ans = 0, k = 1 << 30;  // ans 记录答案；k 是「更大值中出现过的最小下标」，先置为足够大的数
        for (auto& [_, idx] : d) {  // 按值从大到小遍历每组：_ 是值本身，idx 是它的升序下标列表
            ans = max(ans, idx.back() - k + 1);  // 用 k 处的大值做左端、本组最大下标做右端，更新最长长度
            k = min(k, idx[0]);  // 本组的值之后要当作「更大的值」，用它的最小下标收紧 k
        }
        return ans;  // 返回扫描过程中得到的最大长度
    }
};