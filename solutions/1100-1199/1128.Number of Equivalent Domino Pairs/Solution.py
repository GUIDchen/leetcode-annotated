# 题目：1128. 等价多米诺骨牌对的数量（Number of Equivalent Domino Pairs）
# 思路：等价骨牌的判定与顺序无关，因此把每张牌规范化为「小数字在前」的两位编号 a*10+b，用计数数组统计每种编号已出现的次数，每来一张新牌就能与之前所有同编号的牌配对。
# 时间复杂度：O(n)，一次遍历；空间复杂度 O(1)，计数数组大小固定为 100。
class Solution:  # LeetCode 约定的题解类
    def numEquivDominoPairs(self, dominoes: List[List[int]]) -> int:  # dominoes：骨牌列表；返回等价骨牌对的数量
        cnt = Counter()  # cnt：规范化编号 → 出现次数
        ans = 0  # ans：等价骨牌对数
        for a, b in dominoes:  # 逐张解构出骨牌的两个数字
            x = a * 10 + b if a < b else b * 10 + a  # 统一成「小数字在前」的编号，等价的两张牌编号相同
            ans += cnt[x]  # 当前牌与之前所有同编号的牌都构成一对
            cnt[x] += 1  # 处理完再把当前牌计入计数
        return ans  # 返回等价骨牌对总数
