# 题目：3237. Alt 和 Tab 模拟（Alt and Tab Simulation）
# 思路：倒序扫描 queries，越晚按下的窗口越靠前；集合用于去重，最后把没出现过的窗口按原顺序补在末尾。
# 时间复杂度：O(n + q)，q 为按键次数；空间复杂度：O(n)，集合与答案列表。
class Solution:  # LeetCode 约定的题解类
    def simulationResult(self, windows: List[int], queries: List[int]) -> List[int]:  # windows 是初始窗口顺序，queries 是按下的窗口序列
        s = set()  # s 记录已经进入答案的窗口编号，用于去重
        ans = []  # 按最终 Z 序收集结果
        for q in queries[::-1]:  # 倒序扫描按键：越晚按下在最终顺序里越靠前
            if q not in s:  # 首次出现才处理，重复按下不改变位置
                ans.append(q)  # 追加到答案中
                s.add(q)  # 记入已出现的集合
        for w in windows:  # 补上从未被按下的窗口，保持原相对顺序
            if w not in s:  # 只补未出现过的
                ans.append(w)  # 追加到末尾
        return ans  # 返回最终的窗口顺序
