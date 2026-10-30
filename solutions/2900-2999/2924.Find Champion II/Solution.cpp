// 题目：2924. 找到冠军 II（Find Champion II）
// 思路：冠军是从未被战胜过的队伍，统计每支队伍的入度，入度为 0 的队伍恰好只有一支时它就是冠军，否则无法确定。
// 时间复杂度：O(n + m)，m 为边数；空间复杂度：O(n)，额外使用入度数组。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int findChampion(int n, vector<vector<int>>& edges) {  // n 支队伍，edges 中的 [u, v] 表示 u 比 v 强
        int indeg[n];  // 入度：被多少支队伍战胜
        memset(indeg, 0, sizeof(indeg));  // 入度数组清零
        for (auto& e : edges) {  // 统计每条边指向的终点
            ++indeg[e[1]];  // e[1] 被 e[0] 战胜，入度加一
        }  // 建入度结束
        int ans = -1, cnt = 0;  // ans：入度为 0 的队伍；cnt：入度为 0 的队伍数量
        for (int i = 0; i < n; ++i) {  // 枚举所有队伍
            if (indeg[i] == 0) {  // 没有输过的队伍才可能是冠军
                ++cnt;  // 入度为 0 的队伍数加一
                ans = i;  // 记录这个候选
            }  // 判断结束
        }  // 枚举结束
        return cnt == 1 ? ans : -1;  // 唯一候选才是冠军，否则无法确定
    }  // findChampion 结束
};  // 类定义结束