# 题目：638. 大礼包（Shopping Offers）
# 核心思路：把每件物品的需求量按 4 位一段压进整数当状态，用 @cache 记忆化搜索；每个状态先算全按单价买的花费，再枚举可用大礼包转移到需求更小的状态取最小值。
# 时间复杂度：O(S·n·|special|)，S 为可达状态数（单件需求 ≤ 6，故 S ≤ 16^n）；空间复杂度：O(S)，缓存表。
class Solution:  # LeetCode 约定的题解类
    def shoppingOffers(  # price：单价列表；special：大礼包（前 n 项是数量、最后一项是价格）；needs：当前需求量
        self, price: List[int], special: List[List[int]], needs: List[int]  # 形参续行，括号内可以安全地追加注释
    ) -> int:  # 返回满足需求所需的最小花费
        @cache  # 给 dfs 加上记忆化，同一个 cur 只计算一次
        def dfs(cur: int) -> int:  # cur：压缩后的需求状态，返回满足它的最小花费
            ans = sum(p * (cur >> (i * bits) & 0xF) for i, p in enumerate(price))  # 初始方案：全部按单价购买（bits 在后面才赋值，但 dfs 在其赋值之后才被调用）
            for offer in special:  # 枚举每个大礼包，尝试作为下一步选择
                nxt = cur  # 假设使用该礼包后剩下的需求状态
                for j in range(len(needs)):  # 检查礼包里每件物品的数量是否够扣
                    if (cur >> (j * bits) & 0xF) < offer[j]:  # 需求量不足，该礼包不可用
                        break  # 提前跳出检查循环
                    nxt -= offer[j] << (j * bits)  # 从状态里扣掉礼包提供的第 j 件物品数量
                else:  # for-else：循环没有被 break 说明礼包可用
                    ans = min(ans, offer[-1] + dfs(nxt))  # 礼包价 + 剩余需求的最优解，与当前上界取较小值
            return ans  # 返回当前状态的最少花费

        bits, mask = 4, 0  # bits：每件物品占 4 位；mask：初始需求状态
        for i, need in enumerate(needs):  # 逐件物品拼装状态
            mask |= need << i * bits  # 第 i 件物品的需求量放到第 i*4 位起
        return dfs(mask)  # 从最初的需求状态开始搜索
