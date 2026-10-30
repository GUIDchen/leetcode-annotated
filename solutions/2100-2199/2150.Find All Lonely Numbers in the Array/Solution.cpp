// 题目：2150. 找出数组中的所有孤独数字（Find All Lonely Numbers in the Array）
// 思路：先用哈希表统计每个数字的出现次数，再筛出「只出现一次且 x-1、x+1 都不存在」的数字。
// 时间复杂度：O(n)，两次线性扫描；空间复杂度：O(n)，哈希表最多存放 n 个不同数字。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findLonely(vector<int>& nums) {  // nums：输入整数数组；返回所有「孤独数字」
        unordered_map<int, int> cnt;  // 哈希表：键是数组中的数字，值是它出现的次数
        for (int x : nums) {  // 第一遍扫描：统计每个数字的出现次数
            cnt[x]++;  // 当前数字的计数加一
        }  // 结束统计循环
        vector<int> ans;  // 保存结果的动态数组
        for (auto& [x, v] : cnt) {  // 第二遍扫描：结构化绑定拿到「数字 x → 次数 v」
            if (v == 1 && !cnt.contains(x - 1) && !cnt.contains(x + 1)) {  // 孤独条件：只出现一次，且 x-1、x+1 都不在表中
                ans.push_back(x);  // 满足条件，把 x 放入答案
            }  // 结束 if 判断
        }  // 结束遍历计数表
        return ans;  // 返回所有孤独数字
    }  // 结束方法
};  // 结束题解类