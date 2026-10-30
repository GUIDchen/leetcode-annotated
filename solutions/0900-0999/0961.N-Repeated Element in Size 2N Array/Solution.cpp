// 题目：961. 在长度 2N 的数组中找出重复 N 次的元素（N-Repeated Element in Size 2N Array）
// 思路：用哈希集合记录出现过的元素，第一个再次出现的元素就是重复 N 次的那个，必然在 O(n) 内返回。
// 时间复杂度：O(n)，最多遍历一遍数组；空间复杂度：O(n)，集合最多保存 n 个不同元素。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int repeatedNTimes(vector<int>& nums) {  // nums：长度为 2N 的数组，其中恰好有一个元素重复了 N 次
        unordered_set<int> s;  // 哈希集合用来记录已经见过的元素
        for (int i = 0;; ++i) {  // 从左到右遍历；题目保证有重复元素，循环一定会返回
            if (s.count(nums[i])) {  // 这个元素之前已经出现过
                return nums[i];  // 那么它就是重复 N 次的那个元素
            }
            s.insert(nums[i]);  // 第一次出现，加入集合供后面的元素比对
        }
    }
};  // 类定义结束