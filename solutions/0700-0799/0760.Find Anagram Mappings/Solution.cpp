// 题目：760. 找出变位映射（Find Anagram Mappings）
// 思路：先遍历 nums2 建立「值 → 下标」哈希表，再按 nums1 的顺序逐个查表得到映射。
// 时间复杂度：O(n)，两次线性遍历；空间复杂度：O(n)，哈希表与答案数组各占 n 个元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> anagramMappings(vector<int>& nums1, vector<int>& nums2) {  // nums1 是待映射数组，nums2 是映射依据的排列
        int n = nums1.size();  // 记录数组长度（两数组等长）
        unordered_map<int, int> d;  // 哈希表：键是 nums2 的元素值，值是它所在的下标
        for (int i = 0; i < n; ++i) {  // 遍历 nums2，建立「值 → 下标」索引
            d[nums2[i]] = i;  // 记下 nums2[i] 出现的位置
        }
        vector<int> ans;  // 保存答案映射数组
        for (int x : nums1) {  // 按 nums1 的顺序逐个元素查询
            ans.push_back(d[x]);  // 取出 x 在 nums2 中的下标，追加到答案
        }
        return ans;  // 返回映射结果
    }
};
