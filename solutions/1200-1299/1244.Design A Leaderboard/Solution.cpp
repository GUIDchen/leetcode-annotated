// 题目：1244. 力扣排行榜（Design A Leaderboard）
// 思路：哈希表存玩家总分，另用一个降序 multiset 存所有玩家分数，addScore 时先删旧分再插新分，top 直接从头累加 K 个。
// 时间复杂度：addScore O(log n)、reset O(log n)、top O(K)；空间复杂度：O(n)，n 为玩家数。
class Leaderboard {  // 排行榜类，需要支持加分、查询前 K 名总分、重置三种操作
public:  // 对外接口
    Leaderboard() {  // 构造函数：成员容器会自动初始化，无需额外动作
    }

    void addScore(int playerId, int score) {  // 给玩家加分
        d[playerId] += score;  // 在哈希表里累加该玩家的总分
        int newScore = d[playerId];  // 取出累加后的总分
        if (newScore != score) {  // 累加后大于本次加分，说明玩家此前有分数，要删掉旧分
            rank.erase(rank.find(newScore - score));  // 从有序集合中删除旧总分
        }
        rank.insert(newScore);  // 把新的总分插入有序集合
    }

    int top(int K) {  // 求前 K 名玩家的总分之和
        int ans = 0;  // 累加结果
        for (auto& x : rank) {  // rank 用 greater<int> 排序，因此是从大到小遍历
            ans += x;  // 累加当前名次的分数
            if (--K == 0) {  // 已经取满 K 个玩家
                break;  // 提前结束循环
            }
        }
        return ans;  // 返回前 K 名的总分和
    }

    void reset(int playerId) {  // 重置某个玩家的分数
        int score = d[playerId];  // 先查出该玩家的当前总分
        d.erase(playerId);  // 把它从哈希表中移除
        rank.erase(rank.find(score));  // 同步从有序集合中删除这个分数
    }

private:  // 内部数据结构
    unordered_map<int, int> d;  // 玩家编号 → 当前总分
    multiset<int, greater<int>> rank;  // 所有玩家的总分，按降序排列且允许重复
};  // 类定义结束

/**
 * Your Leaderboard object will be instantiated and called as such:
 * Leaderboard* obj = new Leaderboard();
 * obj->addScore(playerId,score);
 * int param_2 = obj->top(K);
 * obj->reset(playerId);
 */