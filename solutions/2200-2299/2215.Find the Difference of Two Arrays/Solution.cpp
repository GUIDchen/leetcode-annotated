// 题目：2215. 找出两数组的不同（Find the Difference of Two Arrays）
// 思路：把两个数组分别去重成集合，再各自算差集：s1 - s2 是只属于 nums1 的值，s2 - s1 是只属于 nums2 的值。
// 时间复杂度：O(m + n)，建集合与遍历各一次；空间复杂度：O(m + n)，两个集合加答案列表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {  // nums1、nums2 是两个输入数组
        unordered_set<int> s1(nums1.begin(), nums1.end());  // 把 nums1 去重成哈希集合，便于 O(1) 判断某个值是否存在
        unordered_set<int> s2(nums2.begin(), nums2.end());  // nums2 同样去重成哈希集合
        vector<vector<int>> ans(2);  // 答案固定两个列表：ans[0] 只在 nums1 中，ans[1] 只在 nums2 中
        for (int v : s1) {  // 遍历 nums1 去重后的每个值
            if (!s2.contains(v)) {  // C++20 的 contains：该值在 nums2 中不存在
                ans[0].push_back(v);  // 放入第一个列表
            }
        }
        for (int v : s2) {  // 遍历 nums2 去重后的每个值
            if (!s1.contains(v)) {  // 该值在 nums1 中不存在
                ans[1].push_back(v);  // 放入第二个列表
            }
        }
        return ans;  // 返回两个差集列表
    }
};