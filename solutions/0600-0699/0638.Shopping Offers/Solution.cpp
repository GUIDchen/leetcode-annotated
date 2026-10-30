// 题目：638. 大礼包（Shopping Offers）
// 核心思路：把每件物品的需求量按 4 位一段压进一个整数当状态，做记忆化搜索；每个状态先算出「全部按单价买」的花费，再枚举可用的大礼包转移到需求更小的状态取最小值。
// 时间复杂度：O(S·n·|special|)，S 为可达状态数（单件需求 ≤ 6，4 位足够，故 S ≤ 16^n）；空间复杂度：O(S)，记忆化哈希表。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {  // price：单价数组；special：大礼包数组（前 n 项是数量、最后一项是价格）；needs：当前需求量
        const int bits = 4;  // 每件物品的需求量占 4 个二进制位（需求量 ≤ 6，4 位足够）
        int n = needs.size();  // 物品种类数
        unordered_map<int, int> f;  // 记忆化表：压缩后的需求状态 → 满足该状态的最小花费
        int mask = 0;  // 把 needs 压成一个整数状态
        for (int i = 0; i < n; ++i) {  // 逐件物品拼装初始状态
            mask |= needs[i] << (i * bits);  // 第 i 件物品的需求量放到第 i*4 位起
        }  // 初始状态构造完成
        function<int(int)> dfs = [&](int cur) {  // 记忆化搜索：返回恰好买齐 cur 中各物品所需的最少花费
            if (f.contains(cur)) {  // 该状态已经算过（C++20 的 contains）
                return f[cur];  // 直接返回缓存值，避免重复搜索
            }  // 缓存未命中，继续往下计算
            int ans = 0;  // 初始方案：全部按单价购买
            for (int i = 0; i < n; ++i) {  // 逐件累计按单价购买的花费
                ans += price[i] * ((cur >> (i * bits)) & 0xf);  // 取出第 i 件物品的需求量（掩码 0xf）再乘单价
            }  // 单价方案算完，ans 作为当前上界
            for (const auto& offer : special) {  // 枚举每个大礼包，尝试作为下一步选择
                int nxt = cur;  // 假设使用该礼包后剩下的需求状态
                bool ok = true;  // 标记该礼包在当前需求下是否可用
                for (int j = 0; j < n; ++j) {  // 检查礼包里每件物品的数量是否够扣
                    if (((cur >> (j * bits)) & 0xf) < offer[j]) {  // 需求量小于礼包提供的数量，买不了
                        ok = false;  // 标记该礼包不可用
                        break;  // 提前结束这层检查
                    }  // 数量足够，继续扣减下一件
                    nxt -= offer[j] << (j * bits);  // 从状态里减去礼包提供的第 j 件物品数量
                }  // 礼包可用性检查结束
                if (ok) {  // 礼包可以买
                    ans = min(ans, offer[n] + dfs(nxt));  // 花礼包价 + 递归解决剩余需求，与当前上界取较小值
                }  // 不可用的礼包直接跳过
            }  // 所有礼包枚举完毕
            f[cur] = ans;  // 把当前状态的最优解记入记忆化表
            return ans;  // 返回当前状态的最少花费
        };  // lambda 定义结束
        return dfs(mask);  // 从最初的需求状态开始搜索
    }  // 方法结束
};  // 类结束