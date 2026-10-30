// 题目：4048. 统计等间距出现整数数目 I（Count Values With Equally Spaced Occurrences I）
// 思路：哈希表把「整数 → 出现下标列表」分组，再逐组检查：只有恰好出现 3 次且首尾下标之和等于中间下标两倍（即 pos[0]、pos[1]、pos[2] 等差）的整数才算等间距出现。
// 复杂度：时间复杂度 O(n)，n 为数组长度；空间复杂度 O(n)，哈希表存放所有下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countSpecialIntegers(vector<int>& nums) {  // nums：输入数组；返回出现 3 次且三个下标等间距的不同整数个数
        unordered_map<int, vector<int>> g;  // g[x]：整数 x 出现的所有下标（按遍历顺序递增）
        for (int i = 0; i < nums.size(); i++) {  // 遍历数组，记录每个值的出现位置
            g[nums[i]].push_back(i);  // 把下标 i 追加到 nums[i] 对应的位置列表
        }  // 建表循环结束

        int ans = 0;  // 满足条件的整数个数
        for (auto& [x, pos] : g) {  // 遍历每个出现过的值及其位置列表
            if (pos.size() == 3 && pos[0] + pos[2] == pos[1] * 2) {  // 恰好 3 次且首尾下标之和等于中间下标的两倍（即等间距）
                ans++;  // 该整数满足等间距出现，计数加一
            }  // 判断分支结束
        }  // 分组遍历结束
        return ans;  // 返回满足条件的整数个数
    }  // 方法结束
};  // 题解类结束