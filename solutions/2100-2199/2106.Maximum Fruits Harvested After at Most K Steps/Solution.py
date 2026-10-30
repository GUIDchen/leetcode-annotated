# 题目：2106. 摘水果（Maximum Fruits Harvested After at Most K Steps）
# 思路：滑动窗口枚举右端 j，窗口内所有有水果的位置都要被走到；最小步数 = 区间宽度 + 起点到较近一端的距离，超出 k 就移动左端 i。
# 时间复杂度：O(n)，i、j 都只单调前进；空间复杂度：O(1)，只用了常数个变量。
class Solution:  # LeetCode 约定的题解类
    def maxTotalFruits(self, fruits: List[List[int]], startPos: int, k: int) -> int:  # fruits 按位置升序给出 {位置, 水果数}，startPos 是起点，k 是步数上限
        ans = i = s = 0  # ans 是答案，i 是窗口左端，s 是窗口内水果总数，三者同时初始化
        for j, (pj, fj) in enumerate(fruits):  # j 为窗口右端，pj 是它的位置，fj 是那里的水果数
            s += fj  # 把右端水果计入窗口总和
            while (  # while 条件跨多行书写：计算覆盖 [fruits[i][0], pj] 这段所需的最少步数
                i <= j  # 左端点不能越过右端点
                and pj  # 区间右端位置 pj
                - fruits[i][0]  # 减去区间左端位置，得到区间宽度
                + min(abs(startPos - fruits[i][0]), abs(startPos - fruits[j][0]))  # 加上起点到左端、到右端两者中较近的那段距离
                > k  # 该窗口代价大于 k，需要收缩
            ):  # 条件结束，进入循环体开始缩窗
                s -= fruits[i][1]  # 把左端水果移出窗口
                i += 1  # 左端点右移一格
            ans = max(ans, s)  # 收缩完毕，用当前窗口水果数更新答案
        return ans  # 返回最多能摘的水果数
