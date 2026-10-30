// 题目：1583. 统计不开心的朋友（Count Unhappy Friends）
// 思路：先用二维表记录每人的亲密度排名，再枚举每个人与“比现任更亲密”的人，检查对方是否也更喜欢他。
// 时间复杂度：O(n^2)，建表与枚举排名都是平方级；空间复杂度：O(n^2)，保存排名表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int unhappyFriends(int n, vector<vector<int>>& preferences, vector<vector<int>>& pairs) {  // n：人数；preferences：每人的亲密度排序；pairs：配对结果
        vector<vector<int>> d(n, vector<int>(n));  // d[i][j] 记录 j 在 i 心中的排名，数字越小越亲密
        for (int i = 0; i < n; ++i) {  // 逐个处理每个人的偏好列表
            for (int j = 0; j < n - 1; ++j) {  // 每人恰好给其余 n-1 个人排序
                d[i][preferences[i][j]] = j;  // 把“人 → 排名”反查表填好，后续可 O(1) 比较亲密度
            }
        }
        vector<int> p(n, 0);  // p[x] 表示 x 当前的配对伙伴
        for (auto& e : pairs) {  // 遍历所有配对
            int x = e[0], y = e[1];  // 配对的两个人
            p[x] = y;  // 双向登记伙伴关系
            p[y] = x;  // 保证从任意一方都能查到对方
        }
        int ans = 0;  // 不开心的人数
        for (int x = 0; x < n; ++x) {  // 逐个人判断是否不开心
            int y = p[x];  // x 的现任伙伴
            for (int i = 0; i < d[x][y]; ++i) {  // 只枚举比现任 y 更亲密的人
                int u = preferences[x][i];  // 排名比 y 靠前的候选 u
                int v = p[u];  // u 的现任伙伴 v
                if (d[u][x] < d[u][v]) {  // u 也觉得 x 比 v 更亲密，即两人互相更喜欢
                    ++ans;  // 记 x 为不开心的朋友
                    break;  // 同一个人只统计一次，跳出内层循环
                }
            }
        }
        return ans;  // 返回不开心的朋友总数
    }
};
