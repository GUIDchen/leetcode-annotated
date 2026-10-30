// 题目：914. 卡牌分组（X of a Kind in a Deck of Cards）
// 核心思路：统计每个牌面出现的次数，求所有频次的最大公约数 g；只要 g >= 2，就能把每种牌面都按 g 张一组切分完。
// 时间复杂度：O(n + m log C)，n 为牌数、m 为不同牌面数；空间复杂度：O(m)，哈希表保存每个牌面的频次。
class Solution {  // 题解类
public:  // 对外接口
    bool hasGroupsSizeX(vector<int>& deck) {  // 判断能否把整副牌分组：每组牌面相同且组大小 X >= 2，所有组大小一致
        unordered_map<int, int> cnt;  // 统计每个牌面出现的次数
        for (int x : deck) {  // 遍历每张牌
            ++cnt[x];  // 对应牌面的计数加一
        }  // 统计结束
        int g = cnt[deck[0]];  // 以第一张牌的频次作为公约数初值（题目保证 deck 非空）
        for (auto& [_, x] : cnt) {  // 遍历所有频次（结构化绑定：_ 是键，x 是值）
            g = gcd(g, x);  // 所有频次的最大公约数就是能切分出的最大组大小
        }  // 求公约数结束
        return g >= 2;  // 组大小至少为 2 才合规；g 为 1 表示无法满足
    }  // 方法结束
};  // 类定义结束