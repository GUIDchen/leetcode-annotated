# 题目：2672. 有相同颜色的相邻元素数目（Number of Adjacent Elements With the Same Color）
# 思路：维护颜色数组 nums 与当前相邻同色对数 x；每次改色只影响 i 与左右邻居，先减掉旧的同色对再补上新的。
# 时间复杂度：O(n + q)，每个查询 O(1)；空间复杂度：O(n)，需要保存颜色数组与答案数组。
class Solution:  # 逐次涂色，并实时维护「相邻同色对数」
    def colorTheArray(self, n: int, queries: List[List[int]]) -> List[int]:  # n 个位置初始未涂色，queries 的每项是 [下标, 颜色]，返回每次涂色后的答案
        nums = [0] * n  # 颜色数组，0 表示该位置还没被涂过
        ans = [0] * len(queries)  # 预先开好答案数组，长度等于查询次数
        x = 0  # x 是当前的相邻同色对数
        for k, (i, c) in enumerate(queries):  # 同时取出查询序号 k 与查询内容 (i, c)
            if i > 0 and nums[i] and nums[i - 1] == nums[i]:  # i 原来已涂色且与左邻居同色，本次改色会拆掉这一对
                x -= 1  # 减去左边这一对
            if i < n - 1 and nums[i] and nums[i + 1] == nums[i]:  # i 原来已涂色且与右邻居同色，同样会被拆掉
                x -= 1  # 减去右边这一对
            if i > 0 and nums[i - 1] == c:  # 改色后与左邻居同色，新增一对
                x += 1  # 加上左边这一对新贡献
            if i < n - 1 and nums[i + 1] == c:  # 改色后与右邻居同色，新增一对
                x += 1  # 加上右边这一对新贡献
            ans[k] = x  # 记录本次涂色后的答案
            nums[i] = c  # 最后才写入新颜色，保证上面几次判断用的都是旧值
        return ans  # 返回每次涂色后的相邻同色对数
