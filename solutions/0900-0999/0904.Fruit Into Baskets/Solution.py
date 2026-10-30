# 题目：904. 水果成篮（Fruit Into Baskets）
# 核心思路：滑动窗口保证窗口内水果种类不超过两种，用 Counter 维护窗口内各类型计数，种类超过 2 就收缩左边界。
# 时间复杂度：O(n)，每个元素最多进出窗口各一次；空间复杂度：O(1)，Counter 最多只有 3 个键。
class Solution:  # LeetCode 约定的题解类
    def totalFruit(self, fruits: List[int]) -> int:  # fruits：每棵树上的水果类型；返回最多能摘的水果个数
        cnt = Counter()  # 计数器：记录当前窗口内每种水果出现的次数
        ans = j = 0  # ans 存最大窗口长度；j 是滑动窗口的左端点
        for i, x in enumerate(fruits):  # i 是右端点，x 是右端点的水果类型
            cnt[x] += 1  # 把当前水果纳入窗口，计数加一
            while len(cnt) > 2:  # 窗口内种类超过两种，不合法，需要收缩左边界
                y = fruits[j]  # 左端点的水果类型
                cnt[y] -= 1  # 左端点移出窗口，计数减一
                if cnt[y] == 0:  # 该类型在窗口内已经没有了
                    cnt.pop(y)  # 删掉这个键，让 len(cnt) 等于窗口内的种类数
                j += 1  # 左端点右移一位
            ans = max(ans, i - j + 1)  # 窗口合法，用当前长度更新答案
        return ans  # 返回最多能摘的水果个数
