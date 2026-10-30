// 题目：3160. 所有球里面不同颜色的数目（Find the Number of Distinct Colors Among the Balls）
// 核心思路：用 g 记录「球 → 当前颜色」，用 cnt 记录「颜色 → 该颜色的球数」；每次改色先维护计数，再用 cnt.size() 直接得到当前不同颜色数。
// 时间复杂度：O(m)，m 为操作数，哈希表操作均摊 O(1)；空间复杂度：O(m)，最坏存 m 个球与颜色。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {  // limit：球编号上界（本题实际用不到）；queries：每次把某个球涂成某种颜色的操作
        unordered_map<int, int> g;  // 球编号 → 当前颜色
        unordered_map<int, int> cnt;  // 颜色 → 拥有该颜色的球的数量
        vector<int> ans;  // 依次记录每次操作后不同颜色的数目
        for (auto& q : queries) {  // 逐条处理涂色操作
            int x = q[0], y = q[1];  // 取出球编号 x 与新颜色 y
            cnt[y]++;  // 新颜色的球数加一
            if (g.contains(x) && --cnt[g[x]] == 0) {  // 若该球原来有颜色，则旧颜色球数减一；减到 0 就从表里删除
                cnt.erase(g[x]);  // 旧颜色已经没有球了，删掉它保证 cnt.size() 准确
            }  // if 结束
            g[x] = y;  // 更新该球当前颜色
            ans.push_back(cnt.size());  // 不同颜色数就是 cnt 中键的个数
        }  // 操作处理结束
        return ans;  // 返回每次操作后的不同颜色数
    }  // 方法结束
};  // 类定义结束