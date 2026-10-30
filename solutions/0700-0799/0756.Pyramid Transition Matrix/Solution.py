# 题目：756. 金字塔转换矩阵（Pyramid Transition Matrix）——中等
# 思路：先把「两个字母对 → 可生成的字母列表」建成字典，再用 @cache 记忆化深搜：逐层用 pairwise + product 枚举上层串，能缩到剩一个字母即成功。
# 时间复杂度：O(n * 分支数)，每个「当前层串」状态只计算一次；空间复杂度：O(状态数)，缓存字典与递归栈的开销。
class Solution:  # LeetCode 约定的题解类
    def pyramidTransition(self, bottom: str, allowed: List[str]) -> bool:  # bottom 是最底层串，allowed 是允许的三元组
        @cache  # 记忆化装饰器：同一个层串只计算一次，避免指数级重复搜索
        def dfs(s: str) -> bool:  # s 是当前需要被缩减的这一层
            if len(s) == 1:  # 只剩一个字母，已经搭到顶点，成功
                return True
            t = []  # 收集每对相邻字母各自可生成的字母列表
            for a, b in pairwise(s):  # 依次取相邻的两个字母
                cs = d[a, b]  # 这个字母对能生成的字母列表
                if not cs:  # 任意一对无法生成字母，这一层就拼不出来
                    return False
                t.append(cs)  # 记录这一对的可选项，供后面做笛卡尔积
            return any(dfs("".join(nxt)) for nxt in product(*t))  # 枚举所有组合，只要有一种能继续成功即可

        d = defaultdict(list)  # 字母对 → 可生成字母列表，默认空列表正好表示「不可生成」
        for a, b, c in allowed:  # 遍历每个允许三元组，直接解包成三个字符
            d[a, b].append(c)  # 把第三个字母登记到字母对 (a, b) 下
        return dfs(bottom)  # 从最底层开始递归判断能否搭满整座金字塔
