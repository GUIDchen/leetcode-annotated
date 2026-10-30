# 题目：2305. 公平分发饼干（Fair Distribution of Cookies）
# 思路：把饼干按大小降序排序后回溯搜索，逐块饼干尝试分给每个孩子，用“超过当前最优”和“与上一个孩子负载相同”两条剪枝去掉重复分支，最终答案是所有分法中最大负载的最小值。
# 时间复杂度：O(k^n)，最坏情况每块饼干有 k 种去向，剪枝后远小于该上界；空间复杂度：O(n + k)，递归深度为 n，另有 k 个孩子的负载数组。
class Solution:  # LeetCode 约定的题解类
    def distributeCookies(self, cookies: List[int], k: int) -> int:  # cookies：每包饼干的个数；k：孩子数量，要求最小化“最累孩子”的饼干数
        def dfs(i):  # 定义回溯函数 dfs，i 表示正在分发第 i 包饼干
            if i >= len(cookies):  # 所有饼干都分完了，得到一个完整分配方案
                nonlocal ans  # 声明 ans 来自外层函数作用域，下面要就地修改它
                ans = max(cnt)  # 该方案的最大负载即“最累孩子”的饼干数，直接更新最优答案
                return  # 回到上一层继续搜索
            for j in range(k):  # 枚举这一包饼干可以分给哪个孩子
                if cnt[j] + cookies[i] >= ans or (j and cnt[j] == cnt[j - 1]):  # 剪枝一：分过去会超过当前最优，不可能更优；剪枝二：与上一个孩子负载相同，交换孩子得到的是等价方案，跳过避免重复
                    continue  # 放弃这个孩子，尝试下一个
                cnt[j] += cookies[i]  # 把当前饼干分给第 j 个孩子，累加负载
                dfs(i + 1)  # 递归分发下一包饼干
                cnt[j] -= cookies[i]  # 回溯：撤销分配，恢复原负载以便尝试其他孩子

        ans = inf  # ans 用无穷大初始化，表示还没有找到任何可行方案
        cnt = [0] * k  # cnt[j] 记录第 j 个孩子当前分到的饼干总数，初始都为 0
        cookies.sort(reverse=True)  # 从大到小排序：先分大饼干，能让最优上界尽快变小，触发更早的剪枝
        dfs(0)  # 从第 0 包饼干开始搜索
        return ans  # 返回所有分法中最大负载的最小值
