// 题目：870. 优势洗牌（Advantage Shuffle）
// 思路：把 nums2 连下标按值升序排序、nums1 也升序；双指针贪心——能用最小的数赢下 nums2 当前最小值就赢，赢不了就把这个最小的数送去和 nums2 的最大值配对。
// 时间复杂度：O(n log n)，瓶颈是两次排序；空间复杂度：O(n)，辅助数组 t 与答案数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {  // nums1 可重排、nums2 固定，要求让 nums1[i] > nums2[i] 成立的位置尽量多
        int n = nums1.size();  // n 是数组长度，两个数组等长
        vector<pair<int, int>> t;  // t 保存 (nums2 的值, 它的原始下标)，按值排序后仍能找回下标
        for (int i = 0; i < n; ++i) t.push_back({nums2[i], i});  // 把 nums2 的每个值连同原始下标一起放进 t
        sort(t.begin(), t.end());  // 按 nums2 的值从小到大排序，同时保留下标信息
        sort(nums1.begin(), nums1.end());  // nums1 也升序排序，便于用「最小的能赢的数」去配对
        int i = 0, j = n - 1;  // i 指向 t 中最小的待配对值，j 指向最大的待配对值，两者向中间收缩
        vector<int> ans(n);  // 答案按 nums2 的原始下标填写，先按 n 开好空间
        for (int v : nums1) {  // 按升序依次取出 nums1 的每个值
            if (v <= t[i].first)  // 当前最小值连 nums2 目前最小的值都赢不了，就让它去「送死」
                ans[t[j--].second] = v;  // 配对给 nums2 中最大的值，右端指针左移，消耗掉这个位置
            else  // 否则当前值能赢下 nums2 最小的值
                ans[t[i++].second] = v;  // 就用它拿下这个位置，左端指针右移，消耗掉这个位置
        }
        return ans;  // 返回构造好的答案，答案下标与 nums2 一一对应
    }
};  // 题解类定义结束