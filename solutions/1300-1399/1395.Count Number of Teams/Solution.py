# 题目：1395. 统计作战单位数（Count Number of Teams）
# 思路：枚举中间那个人 b，用两个生成器 sum 出左侧比 b 小的人数 l、右侧比 b 大的人数 r，再按乘法原理累加递增与递减三元组的个数。
# 时间复杂度：O(n^2)，每个中间点都要扫一遍左右两侧；空间复杂度：O(n)，切片 rating[:i] 与 rating[i+1:] 产生的临时空间。
class Solution:  # LeetCode 约定的题解类
    def numTeams(self, rating: List[int]) -> int:  # rating 是每个人的战力，题目保证互不相同
        ans, n = 0, len(rating)  # ans 累计合法三元组个数，n 是总人数
        for i, b in enumerate(rating):  # i 是中间位置，b 是中间那个人的战力
            l = sum(a < b for a in rating[:i])  # 左侧比 b 小的人数，对应递增三元组的左端
            r = sum(c > b for c in rating[i + 1 :])  # 右侧比 b 大的人数，对应递增三元组的右端
            ans += l * r  # 递增三元组：左侧更弱 × 右侧更强
            ans += (i - l) * (n - i - 1 - r)  # 递减三元组：(左侧更强) × (右侧更弱)
        return ans  # 返回合法三元组总数
