// 题目：220. 存在重复元素 III（Contains Duplicate III）
// 核心思路：用有序集合维护长度为 indexDiff+1 的滑动窗口，每次二分找不小于 nums[i]-valueDiff 的最小值并检查是否不超过 nums[i]+valueDiff。
// 时间复杂度：O(n log n)，每个元素一次 lower_bound 与一次插入/删除；空间复杂度：O(k)，窗口内最多 indexDiff+1 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 对外接口
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {  // 判断是否存在下标差 <= indexDiff 且值差 <= valueDiff 的一对元素
        set<long> s;  // 有序集合，维护窗口内最近若干个元素的值；用 long 防止加减时溢出
        for (int i = 0; i < nums.size(); ++i) {  // 右端点 i 从左往右滑动，窗口左端为 i-indexDiff
            auto it = s.lower_bound((long) nums[i] - valueDiff);  // 找第一个不小于 nums[i]-valueDiff 的元素，它是最接近的下界候选
            if (it != s.end() && *it <= (long) nums[i] + valueDiff) return true;  // 若该元素同时不超过 nums[i]+valueDiff，则窗口内存在值差满足要求的元素
            s.insert((long) nums[i]);  // 把当前值加入窗口
            if (i >= indexDiff) s.erase((long) nums[i - indexDiff]);  // 窗口只保留最近 indexDiff 个元素，故在 i >= indexDiff 时移除下标 i-indexDiff 的旧值
        }  // 循环结束
        return false;  // 没有找到满足条件的元素对
    }  // 方法结束
};  // 类定义结束