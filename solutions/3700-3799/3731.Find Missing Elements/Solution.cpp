// 3731. 找出缺失的元素 / Find Missing Elements
// 核心思路：先求数组最小值与最大值，把它们之间的每个整数逐个检查是否出现在哈希集合中，缺失的即为答案。
// 复杂度：时间 O(n + max - min)，空间 O(n)。
class Solution {  // 定义 LeetCode 解法类
public:  // 公有接口
    vector<int> findMissingElements(vector<int>& nums) {  // 返回区间内缺失的所有元素
        int mn = 100, mx = 0;  // 极值按题目值域初始化
        unordered_set<int> s;  // 哈希集合用于 O(1) 判断元素是否存在
        for (int x : nums) {  // 遍历数组每个元素
            mn = min(mn, x);  // 维护最小值
            mx = max(mx, x);  // 维护最大值
            s.insert(x);  // 记录出现过的元素
        }  // 遍历结束
        vector<int> ans;  // 存放答案
        for (int x = mn + 1; x < mx; ++x) {  // 枚举最小值与最大值之间的每个整数
            if (!s.count(x)) {  // 该整数未在数组中出现
                ans.push_back(x);  // 加入答案
            }  // 分支结束
        }  // 枚举结束
        return ans;  // 返回缺失元素列表
    }  // 方法结束
};  // 类定义结束
