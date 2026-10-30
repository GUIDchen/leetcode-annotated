// 题目：2032. 至少在两个数组中出现的值（Two Out of Three）
// 思路：分别给三个数组做「出现过」的标记数组（同一个值重复出现只记 1），再枚举 1..100，三个标记之和大于 1 即为答案。
// 时间复杂度：O(n1 + n2 + n3 + 100)，三趟遍历加一次固定 100 的枚举；空间复杂度：O(100)，只用了三个长度为 101 的标记数组，与输入规模无关。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> twoOutOfThree(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3) {  // nums1/nums2/nums3 是三个输入数组，返回至少在两个数组中出现过的值（升序）
        auto get = [](vector<int>& nums) {  // 局部 lambda：把任意一个数组压成「值 → 是否出现过」的标记数组
            vector<int> cnt(101);  // 题目值域是 1..100，开长度 101 的数组，下标 0 空置不用
            for (int& v : nums) cnt[v] = 1;  // 只置 1 而不是累加，重复元素在同一数组里也只算出现过一次
            return cnt;  // 返回该数组的标记数组
        };  // lambda 定义结束
        auto s1 = get(nums1), s2 = get(nums2), s3 = get(nums3);  // 一次性求出三个数组各自的出现标记
        vector<int> ans;  // 收集答案：至少出现在两个数组中的那些值
        for (int i = 1; i <= 100; ++i) {  // 按值从小到大枚举，天然得到升序结果
            if (s1[i] + s2[i] + s3[i] > 1) {  // 三个标记相加大于 1，说明该值至少落在两个数组里
                ans.emplace_back(i);  // 满足条件就追加到答案
            }  // 结束 if 分支
        }  // 结束枚举循环
        return ans;  // 返回升序答案数组
    }  // 结束 twoOutOfThree
};  // 结束 Solution 类