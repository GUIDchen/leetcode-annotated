# 题目：1452. 收藏清单（People Whose List of Favorite Companies Is Not a Subset of Another List）
# 核心思路：把公司名离散化成整数编号，每个人的清单变成集合；若某人的集合与任意别人的集合求交后仍等于自己，说明它是子集，应被淘汰。
# 时间复杂度：O(n^2 * m)，n 为人数、m 为单份清单长度；空间复杂度：O(n * m)，存放离散化后的集合。
class Solution:  # LeetCode 约定的题解类
    def peopleIndexes(self, favoriteCompanies: List[List[str]]) -> List[int]:  # 返回那些「收藏清单不是别人收藏清单子集」的人的下标
        idx = 0  # 下一个可分配的公司编号
        d = {}  # 公司名 → 编号的映射，把长字符串压缩成整数
        n = len(favoriteCompanies)  # 人数，也就是清单份数
        nums = [set() for _ in range(n)]  # 为每个人准备一个空集合，元素是公司编号
        for i, ss in enumerate(favoriteCompanies):  # 逐个处理每个人的清单
            for s in ss:  # 遍历这个人收藏的每一家公司
                if s not in d:  # 该公司名第一次出现，需要分配新编号
                    d[s] = idx  # 记录映射关系
                    idx += 1  # 编号计数器自增
                nums[i].add(d[s])  # 把公司编号加入第 i 个人的集合
        ans = []  # 存放答案下标（按 i 递增遍历，结果天然有序）
        for i in range(n):  # 逐个检查第 i 个人是否应该保留
            if not any(i != j and (nums[i] & nums[j]) == nums[i] for j in range(n)):  # 交集等于自己说明是子集；只要存在这样的 j 就淘汰 i
                ans.append(i)  # 不是任何人的子集，保留该下标
        return ans  # 返回所有满足条件的下标
