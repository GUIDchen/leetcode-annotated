# 题目：1996. 游戏中弱角色的数量（The Number of Weak Characters in the Game）
# 思路：按攻击力降序、攻击力相同时防御力升序排序，再线性扫描维护最大防御力，统计弱角色。
# 时间复杂度：O(n log n)，排序主导；空间复杂度：O(n)，排序 key 元组的额外空间。
class Solution:  # LeetCode 约定的题解类
    def numberOfWeakCharacters(self, properties: List[List[int]]) -> int:  # properties：每个元素是 [攻击力, 防御力]
        properties.sort(key=lambda x: (-x[0], x[1]))  # 攻击力降序；同攻击力时防御力升序，保证同攻击力角色不会被误判
        ans = mx = 0  # ans 统计弱角色个数；mx 记录已扫描角色的最大防御力
        for _, x in properties:  # 按攻击力从大到小遍历，只用防御力 x
            ans += x < mx  # 防御力小于此前最大值，说明存在攻防都严格更大的角色，计为弱角色
            mx = max(mx, x)  # 更新最大防御力供后续角色比较
        return ans  # 返回弱角色总数
