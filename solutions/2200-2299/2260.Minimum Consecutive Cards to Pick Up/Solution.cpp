// 题目：2260. 必须拿起的最小连续卡牌数（Minimum Consecutive Cards to Pick Up）
// 思路：从左往右扫描，哈希表记录每种卡牌上次出现的下标；再次遇到同一张牌时，两个下标之间就是含这对相同卡牌的最短连续区间，全局取最小。
// 时间复杂度：O(n)，每个元素只扫描一次；空间复杂度：O(n)，哈希表最多保存 n 种卡牌。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumCardPickup(vector<int>& cards) {  // cards：卡牌数组；返回必须拿起的最少卡牌张数，无解返回 -1
        unordered_map<int, int> last;  // 哈希表：卡牌值 → 该卡牌最近一次出现的下标
        int n = cards.size();  // 卡牌总数，同时用来构造「无解」哨兵
        int ans = n + 1;  // 初值取 n+1，比任何合法区间都长，表示「还没有找到重复卡牌」
        for (int i = 0; i < n; ++i) {  // 从左到右枚举区间的右端点
            if (last.count(cards[i])) {  // 当前卡牌以前出现过，才能和上次那张配成一对
                ans = min(ans, i - last[cards[i]] + 1);  // 区间长度 = 两个下标之差 + 1，保留更短的那个
            }
            last[cards[i]] = i;  // 无论是否配对成功，都把当前位置更新为该卡牌的最新下标
        }
        return ans > n ? -1 : ans;  // ans 仍是哨兵说明没有重复卡牌，按题意返回 -1
    }
};