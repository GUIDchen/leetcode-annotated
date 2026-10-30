// 题目：1436. 旅行终点站（Destination City）
// 思路：把所有作为「起点」出现过的城市放进哈希集合，再找一条只被当作终点的航段，它的终点就是答案。
// 时间复杂度：O(n)，n 为航段数；空间复杂度：O(n)，集合最多保存 n 个城市名。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string destCity(vector<vector<string>>& paths) {  // paths 的每一项是 [起点城市, 终点城市] 的一条航段
        unordered_set<string> s;  // 集合 s 用来记录「曾经作为起点出现过」的城市
        for (auto& p : paths) {  // 遍历每条航段
            s.insert(p[0]);  // 把起点城市放入集合，之后可以 O(1) 判断某城市是否当过起点
        }
        for (int i = 0;; ++i) {  // 题目保证终点唯一，所以循环上界可以省略
            auto b = paths[i][1];  // 取出第 i 条航段的终点城市（auto 推导为 string）
            if (!s.contains(b)) {  // C++20 的 contains：判断该城市是否从未当过起点
                return b;  // 只进不出的城市就是旅行终点站
            }
        }
    }
};
