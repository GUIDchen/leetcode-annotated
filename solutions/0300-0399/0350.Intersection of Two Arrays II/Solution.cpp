// 题目：350. 两个数组的交集 II（Intersection of Two Arrays II）
// 思路：先用哈希表统计 nums1 中每个元素的出现次数，再遍历 nums2 按“剩余次数”一一配对。
// 时间复杂度：O(m + n)，两次线性遍历；空间复杂度：O(k)，k 为 nums1 中不同元素个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2 为输入数组，返回可含重复元素的交集
        unordered_map<int, int> cnt;  // 哈希表计数：键是元素值，值是该元素还剩几次可以配对
        for (int x : nums1) {  // 先统计 nums1 中每个元素的出现次数
            ++cnt[x];  // 出现一次就加一；键不存在时默认从 0 开始
        }  // 统计结束
        vector<int> ans;  // 存放交集结果
        for (int x : nums2) {  // 再遍历 nums2，用剩余次数与 nums1 配对
            if (cnt[x]-- > 0) {  // 先读旧值再自减：旧值大于 0 说明还能配对一次
                ans.push_back(x);  // 配对成功，该元素进入交集
            }  // 结束配对判断
        }  // 遍历结束
        return ans;  // 返回包含重复元素的交集
    }  // 方法结束
};  // 类定义结束