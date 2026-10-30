// 题目：2347. 最好的扑克手牌（Best Poker Hand）
// 思路：先判同花（5 张花色全相同）；否则统计各点数出现次数，出现 3 张即三条，出现 2 张即对子，都不是则高牌。
// 时间复杂度：O(n)，n = 5，两次线性扫描；空间复杂度：O(1)，点数桶固定 14 个。
char* bestHand(int* ranks, int ranksSize, char* suits, int suitsSize) {  // ranks：5 张牌的点数；suits：5 张牌的花色
    bool isFlush = true;  // 先假设是同花，遇到不同花色再否定
    for (int i = 1; i < suitsSize; i++) {  // 从第二张牌开始，逐个与第一张牌比较
        if (suits[0] != suits[i]) {  // 出现与首张不同的花色
            isFlush = false;  // 否定同花
            break;  // 已能确定不是同花，提前结束循环
        }
    }
    if (isFlush) {  // 五张花色完全相同
        return "Flush";  // 同花是最高牌型，直接返回字符串字面量（静态存储，不需 malloc）
    }
    int count[14] = {0};  // 点数范围 1..13，开 14 个桶并全部清零，用来统计每个点数出现的张数
    bool isPair = false;  // 是否已经出现过恰好两张同点数的对子
    for (int i = 0; i < ranksSize; i++) {  // 逐张统计点数
        if (++count[ranks[i]] == 3) {  // 该点数计数加一后正好达到 3 张
            return "Three of a Kind";  // 三条优先于对子，立即返回
        }
        isPair = isPair || count[ranks[i]] == 2;  // 该点数恰好出现两张时标记对子；一旦为真就保持为真
    }
    if (isPair) {  // 不是同花也没有三条，但存在对子
        return "Pair";  // 返回对子
    }
    return "High Card";  // 既非同花、无三条也无对子，只剩高牌
}