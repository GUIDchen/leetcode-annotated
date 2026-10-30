// 题目：846. 一手顺子（Hand of Straights）
// 思路：排序后按点数从小到大贪心分组，每遇到还有剩余的牌，就强制以它开头取 groupSize 张连续牌。
// 时间复杂度：O(n log n)，主要开销是排序；空间复杂度：O(n)，哈希表统计每个点数出现次数。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    bool isNStraightHand(vector<int>& hand, int groupSize) {  // hand 是手牌点数，groupSize 是每组顺子的长度；返回能否恰好分成若干组
        if (hand.size() % groupSize) {  // 牌数必须能被 groupSize 整除，否则一定分不完
            return false;  // 余数非零，直接返回 false
        }  // 整除判断结束
        ranges::sort(hand);  // 先按点数升序排序，保证每次从最小的牌开始组顺子
        unordered_map<int, int> cnt;  // 哈希表：统计每个点数还剩多少张牌
        for (int x : hand) {  // 遍历所有牌，累计每个点数出现的次数
            ++cnt[x];  // 点数 x 的计数加一
        }  // 计数结束
        for (int x : hand) {  // 再按点数从小到大遍历，依次把每张牌安排进顺子
            if (cnt.contains(x)) {  // 只有该点数还有剩余牌时才需要为它开头分组
                for (int y = x; y < x + groupSize; ++y) {  // 以 x 开头向后取 groupSize 张连续牌，构成一条顺子
                    if (!cnt.contains(y)) {  // 若某个需要的点数已经没有牌了，说明无法凑成顺子
                        return false;  // 缺少所需点数，返回 false
                    }  // 缺少点数判断结束
                    if (--cnt[y] == 0) {  // 取出点数 y 的一张牌，计数减到 0 时从表中删除
                        cnt.erase(y);  // 计数归零就删除该键，contains 判断才准确
                    }  // 删除归零键结束
                }  // 本组顺子取完
            }  // 该点数分组结束
        }  // 所有牌处理完毕
        return true;  // 全部成功分组，返回 true
    }  // 方法结束
};  // 类定义结束
