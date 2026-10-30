// 题目：3143. 正方形中的最多点数（Maximum Points Inside the Square）
// 思路：正方形以原点为中心，半边长 k 时能覆盖 max(|x|,|y|) ≤ k 的点；按这个切比雪夫距离分层，由内向外整层判断，层内标签若与内层重复就立刻截断，否则整层纳入。
// 时间复杂度：O(n log n)，把 n 个点插入有序 map；空间复杂度：O(n)，存放分层结果与 26 个标签的访问标记。
class Solution {
public:
    int maxPointsInsideSquare(vector<vector<int>>& points, string s) {  // points：所有点的坐标；s：每个点对应的标签字符
        map<int, vector<int>> g;  // g：切比雪夫距离 → 该距离上的所有点下标，用 map 保证从小到大遍历
        for (int i = 0; i < points.size(); ++i) {  // 逐个点算出它到原点的切比雪夫距离并分组
            auto& p = points[i];  // p 是当前点的坐标 (x, y)
            int key = max(abs(p[0]), abs(p[1]));  // key = max(|x|, |y|)：覆盖该点所需的最小半边长
            g[key].push_back(i);  // 把下标塞进对应距离的桶，稍后整层一起处理
        }
        bool vis[26]{};  // vis：标记 26 个标签字母是否已被更内层占用
        int ans = 0;  // ans：目前已经确认可以整层覆盖的点数
        for (auto& [_, idx] : g) {  // 按距离从小到大逐层处理，保证内层标签先被占住
            for (int i : idx) {  // 先检查本层所有点，只要有一个标签冲突就整层作废
                int j = s[i] - 'a';  // j：把标签字符映射到 0~25
                if (vis[j]) {  // 该标签在内层已经出现过，正方形不能再扩大
                    return ans;  // 直接返回此前已经完整纳入的点数
                }
                vis[j] = true;  // 标签首次出现，标记为已占用
            }
            ans += idx.size();  // 本层全部合法，整层计入答案（边长取本层的距离）
        }
        return ans;  // 所有层都不冲突，返回总点数
    }
};