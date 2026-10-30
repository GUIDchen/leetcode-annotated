// 题目：3741. 三个相等元素之间的最小距离 II（Minimum Distance Between Three Equal Elements II）
// 核心思路：与版本 I 相同——用哈希表把每个取值出现过的下标按顺序收集起来；同一取值中三个下标的两两距离之和为 2*(最大下标-最小下标)，所以只需枚举同一下标列表里相邻的三个位置，取 2*(ls[h+2]-ls[h]) 的最小值。
// 复杂度：时间 O(n)，建表一次扫描，之后每个下标至多被枚举一次；空间 O(n)，哈希表存下所有下标。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDistance(vector<int>& nums) {  // nums：整数数组；返回三个相等元素之间的最小距离，凑不出三个则为 -1
        int n = nums.size();  // 数组长度
        unordered_map<int, vector<int>> g;  // 每个取值对应一个下标列表，列表天然递增
        for (int i = 0; i < n; ++i) {  // 一遍扫描建立分组
            g[nums[i]].push_back(i);  // 把当前下标加入该取值的列表
        }  // 建表结束
        const int inf = 1 << 30;  // 用一个足够大的数表示无穷
        int ans = inf;  // 记录最小距离
        for (auto& [_, ls] : g) {  // 遍历每个取值对应的下标列表
            int m = ls.size();  // 该取值在数组中出现的次数
            for (int h = 0; h < m - 2; ++h) {  // 枚举同一取值中三个连续下标里的第一个
                int i = ls[h];  // 第一个下标
                int k = ls[h + 2];  // 第三个下标（跳过中间那个，三者必然相邻才最优）
                int t = (k - i) * 2;  // 三个下标的两两距离之和等于最远跨度乘 2
                ans = min(ans, t);  // 更新最小距离
            }  // 枚举结束
        }  // 分组遍历结束
        return ans == inf ? -1 : ans;  // 从未更新过说明一个取值不足三个，返回 -1
    }  // 方法结束
};  // 类定义结束
