// 题目：3181. 执行操作可获得的最大总奖励 II（Maximum Total Reward Using Operations II）
// 思路：把「能否凑出总奖励 s」压进 bitset，第 s 位为 1 表示可达；对每个奖励值 v，只把小于 v 的可达和整体加 v 来更新，最后从高位往下找最高可达位。
// 时间复杂度：O(n * maxV / 64)，移位与或运算由字并行完成；空间复杂度：O(maxV)，一个 bitset。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int maxTotalReward(vector<int>& rewardValues) {  // rewardValues：可选的奖励值集合
        sort(rewardValues.begin(), rewardValues.end());  // 排序保证处理顺序是从小到大
        rewardValues.erase(unique(rewardValues.begin(), rewardValues.end()), rewardValues.end());  // 去重：重复的奖励值不可能被选两次
        bitset<100000> f{1};  // 位图 f，第 s 位为 1 表示总和 s 可达；只初始化第 0 位为 1
        for (int v : rewardValues) {  // 逐个把奖励值当作可选操作
            int shift = f.size() - v;  // 先算左移量，使高位先移到 bitset 之外
            f |= f << shift >> (shift - v);  // 左移再回移，等价于「只把小于 v 的可达和加上 v」，同时丢弃 >= v 的旧状态
        }
        for (int i = rewardValues.back() * 2 - 1;; i--) {  // 从理论上界（2*最大值-1）向下枚举，找最高可达总和
            if (f.test(i)) {  // 该总和可达，且因为是自高向低查找，它必然最大
                return i;  // 返回最大总奖励
            }
        }
    }
};