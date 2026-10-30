// 题目：2454. 下一个更大元素 IV（Next Greater Element IV）
// 思路：按数值从大到小处理下标，用有序集合 set 维护已处理过的下标；当前下标右侧第二个已处理下标，就是它的第二个更大元素。
// 时间复杂度：O(n log n)，排序 O(n log n) 且每次 set 查询/插入 O(log n)；空间复杂度：O(n)，答案数组、排序数组与有序集合各占 O(n)。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> secondGreaterElement(vector<int>& nums) {  // nums：输入数组
        int n = nums.size();  // 数组长度
        vector<int> ans(n, -1);  // 答案数组，默认 -1 表示不存在第二个更大元素
        vector<pair<int, int>> arr(n);  // 保存 (-数值, 下标)，用于把数值按从大到小排序
        for (int i = 0; i < n; ++i) {  // 构造排序用的二元组
            arr[i] = {-nums[i], i};  // 数值取负号，使数值大的排到前面；同值按下标升序
        }
        sort(arr.begin(), arr.end());  // 按 (-数值, 下标) 的字典序升序排列
        set<int> ts;  // 有序集合，保存已处理过的元素下标（其值不小于当前值）
        for (auto& [_, i] : arr) {  // 按数值从大到小，依次处理每个下标
            auto it = ts.upper_bound(i);  // 二分找到集合中第一个大于 i 的下标
            if (it != ts.end() && ts.upper_bound(*it) != ts.end()) {  // 右侧还有下标，且再右侧仍有一个，说明存在第二个更大元素
                ans[i] = nums[*ts.upper_bound(*it)];  // 取右侧第二个已处理下标处的值作为答案
            }
            ts.insert(i);  // 把当前下标加入集合，供数值更小的元素查询
        }
        return ans;  // 返回每个位置的第二个更大元素
    }
};