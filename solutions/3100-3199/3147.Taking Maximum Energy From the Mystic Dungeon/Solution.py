# 题目：3147. 从魔法师身上吸取的最大能量（Taking Maximum Energy From the Mystic Dungeon）
# 思路：一次取法的下标是 i, i+k, i+2k, ...，末项一定在最后 k 个位置中；枚举末项往前每隔 k 累加，得到该等差数列的所有后缀和并取最大。
# 时间复杂度：O(n)，每个下标只被访问一次；空间复杂度：O(1)，只用常数个额外变量。
class Solution:  # LeetCode 约定的题解类
    def maximumEnergy(self, energy: List[int], k: int) -> int:  # energy：各位魔法师的能量；k：每次跳跃的步长
        ans = -inf  # ans：初值取负无穷，保证能被第一次更新覆盖
        n = len(energy)  # n：数组长度
        for i in range(n - k, n):  # 枚举末项 i，末项只可能落在最后 k 个位置
            j, s = i, 0  # j 从末项开始往前回退，s 是当前后缀和
            while j >= 0:  # 还有下标可以累加
                s += energy[j]  # 把当前位置的能量累加进后缀和
                ans = max(ans, s)  # 每个后缀和都对应一种合法取法，用它更新答案
                j -= k  # 步长固定为 k，继续往前
        return ans  # 返回能吸取到的最大能量
