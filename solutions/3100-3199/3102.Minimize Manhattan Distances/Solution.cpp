// 题目：3102. 最小化曼哈顿距离（Minimize Manhattan Distances）
// 思路：做切比雪夫变换 u = x + y、v = x - y，则最大曼哈顿距离等于 max(max u - min u, max v - min v)；枚举删掉的点，用有序集合随时取两族值的最小/最大值。
// 时间复杂度：O(n log n)，建集合与每次插入删除都是对数级；空间复杂度：O(n)，两个有序集合各存 n 个数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumDistance(vector<vector<int>>& points) {  // points：所有点坐标，返回删掉一个点后其余点之间最大曼哈顿距离的最小可能值
        multiset<int> st1;  // 有序集合一：维护所有已存在点的 x + y
        multiset<int> st2;  // 有序集合二：维护所有已存在点的 x - y
        for (auto& p : points) {  // 先遍历全部点建立两个集合
            int x = p[0], y = p[1];  // 取出当前点的横纵坐标
            st1.insert(x + y);  // 把 x + y 放入第一个集合
            st2.insert(x - y);  // 把 x - y 放入第二个集合
        }  // 结束建表循环
        int ans = INT_MAX;  // 答案先设为无穷大，等待取 min
        for (auto& p : points) {  // 依次枚举“被删掉的那个点”
            int x = p[0], y = p[1];  // 取出本轮要删除的点坐标
            st1.erase(st1.find(x + y));  // 只删一个 x + y：用 find 定位后 erase 迭代器，避免 erase(key) 抹掉全部重复值
            st2.erase(st2.find(x - y));  // 同样只删一个 x - y
            ans = min(ans, max(*st1.rbegin() - *st1.begin(), *st2.rbegin() - *st2.begin()));  // 删点后剩余点集的最大曼哈顿距离等于两族极差中的较大者，用它更新答案
            st1.insert(x + y);  // 把该点还原到集合一，供下一轮枚举使用
            st2.insert(x - y);  // 把该点还原到集合二
        }  // 结束枚举循环
        return ans;  // 返回最小的“剩余点最大曼哈顿距离”
    }  // 结束题解方法
};  // 结束题解类