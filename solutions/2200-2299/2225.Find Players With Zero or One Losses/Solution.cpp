// 题目：2225. 找出输掉零场或一场比赛的玩家（Find Players With Zero or One Losses）
// 思路：用有序 map 统计每位玩家输掉的场次，首次作为赢家出现时补记 0 负；最后按输场次 0 或 1 分装两列表，map 的升序遍历保证结果有序。
// 时间复杂度：O(m log n)，m 为比赛场数、n 为玩家数，每次 map 操作 O(log n)；空间复杂度：O(n)，只保存玩家与其输场次。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<vector<int>> findWinners(vector<vector<int>>& matches) {  // matches：每场比赛形如 [winner, loser]
        map<int, int> cnt;  // 键是玩家编号，值是该玩家输掉的场次；map 默认按键升序
        for (auto& e : matches) {  // 逐场比赛遍历
            if (!cnt.contains(e[0])) {  // 赢家此前可能从未出现，需要先建立记录
                cnt[e[0]] = 0;  // 首次出现的赢家输场次记为 0
            }
            ++cnt[e[1]];  // 输家输场次加一；map 的值默认初始化为 0，首次出现也能直接自增
        }
        vector<vector<int>> ans(2);  // 结果固定两块：ans[0] 存 0 负玩家，ans[1] 存 1 负玩家
        for (auto& [x, v] : cnt) {  // 结构化绑定遍历有序 map：x 是玩家编号，v 是输场次
            if (v < 2) {  // 只关心输 0 场或 1 场的玩家
                ans[v].push_back(x);  // 以输场次 v 作下标直接归入对应列表，升序遍历天然有序
            }
        }
        return ans;  // 返回两个升序列表
    }
};