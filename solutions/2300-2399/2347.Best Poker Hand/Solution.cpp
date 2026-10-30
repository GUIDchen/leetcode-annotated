// 题目：2347. 最好的扑克手牌（Best Poker Hand）
// 思路：先判 5 张是否同花；否则用点数桶统计频次，出现 3 张为三条，出现 2 张为对子，否则高牌。
// 时间复杂度：O(n)，n = 5，一次花色扫描加一次点数扫描；空间复杂度：O(1)，点数桶固定 14 个。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    string bestHand(vector<int>& ranks, vector<char>& suits) {  // ranks：点数数组；suits：花色数组
        bool flush = true;  // 默认认为是同花
        for (int i = 1; i < 5 && flush; ++i) {  // 相邻两张比较；flush 变 false 后循环条件立即失效
            flush = suits[i] == suits[i - 1];  // 任何一对相邻花色不同都会把 flush 置为 false
        }
        if (flush) {  // 五张花色全部一致
            return "Flush";  // 同花最大，直接返回
        }
        int cnt[14]{};  // 点数 1..13，开 14 个桶并值初始化（全部清零）
        bool pair = false;  // 是否出现过对子
        for (int& x : ranks) {  // 逐个统计点数频次
            if (++cnt[x] == 3) {  // 先自增再比较：该点数达到 3 张
                return "Three of a Kind";  // 三条优先于对子，立即返回
            }
            pair |= cnt[x] == 2;  // 用按位或累积：出现过恰好 2 张就永久标记为真
        }
        return pair ? "Pair" : "High Card";  // 有对子返回 Pair，否则只剩高牌
    }
};