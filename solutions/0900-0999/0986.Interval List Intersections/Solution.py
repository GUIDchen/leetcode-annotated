# 题目：986. 区间列表的交集（Interval List Intersections）
# 思路：双指针扫描两个有序区间列表，每次用 max 求交集左端、min 求交集右端，右端更小的区间先被推进。
# 时间复杂度：O(m+n)，每个区间最多访问一次；空间复杂度：O(1)，不计答案列表。
class Solution:  # LeetCode 约定的题解类
    def intervalIntersection(  # 方法签名第一行：两个按左端升序的区间列表
        self, firstList: List[List[int]], secondList: List[List[int]]  # 方法签名第二行：参数与类型标注
    ) -> List[List[int]]:  # 返回交集区间的列表
        i = j = 0  # i、j 分别是两个列表的扫描指针
        ans = []  # ans 保存所有交集区间
        while i < len(firstList) and j < len(secondList):  # 两个列表都还有区间可比较
            s1, e1, s2, e2 = *firstList[i], *secondList[j]  # 把两个区间解包成左右端点 s1,e1 与 s2,e2
            l, r = max(s1, s2), min(e1, e2)  # 交集左端取较大者，右端取较小者
            if l <= r:  # 左端不超过右端才算有交集
                ans.append([l, r])  # 把交集区间加入答案
            if e1 < e2:  # 第一个区间右端更小
                i += 1  # 推进第一个列表的指针
            else:  # 否则
                j += 1  # 推进第二个列表的指针
        return ans  # 返回所有交集
