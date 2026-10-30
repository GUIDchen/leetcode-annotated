// 题目：1733. 需要教语言的最少人数（Minimum Number of People to Teach）
// 思路：先找出“与好友没有任何共同语言”的人放进集合，再统计这些人已会语言的频次；选其中最普及的一种语言统一教，答案即集合大小减去最大频次。
// 时间复杂度：O(m·L² + n + k)，m 为好友对数、L 为每人语言数、k 为集合人数；空间复杂度：O(n + 25)，集合与频次数组的开销。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {  // n 为语言总数，languages[u-1] 是第 u 人会说的语言，friendships 是好友对
        unordered_set<int> s;  // 存放“存在无法沟通好友关系”的人，用集合自动去重
        auto check = [&](int u, int v) {  // 判断编号 u 与 v 两人之间是否有共同语言
            for (int x : languages[u - 1]) {  // 枚举 u 会说的每一种语言
                for (int y : languages[v - 1]) {  // 枚举 v 会说的每一种语言
                    if (x == y) {  // 两种语言相同
                        return true;  // 说明两人可以直接沟通
                    }
                }
            }
            return false;  // 双重循环结束仍无交集，说明这一对好友无法沟通
        };
        for (auto& e : friendships) {  // 遍历所有好友关系
            int u = e[0], v = e[1];  // 取出这一对好友的编号
            if (!check(u, v)) {  // 只有彼此听不懂对方的好友才需要被“补救”
                s.insert(u);  // 记录其中一人
                s.insert(v);  // 记录另一人
            }
        }
        if (s.empty()) {  // 所有人本来就能和好友沟通
            return 0;  // 无需教学，直接返回 0（也避免下面 max 作用在空数组上）
        }
        vector<int> cnt(n + 1);  // cnt[l] 统计集合 s 中会说语言 l 的人数，语言下标是 1..n
        for (int u : s) {  // 遍历所有需要被覆盖的人
            for (int& l : languages[u - 1]) {  // 遍历他会说的每一种语言
                ++cnt[l];  // 该语言的“已会人数”加一
            }
        }
        return s.size() - ranges::max(cnt);  // 挑众数语言统一教，不会它的人各改学一次，故人数最少
    }
};
