class Solution:  # LeetCode 约定的题解类
    def removeInterval(  # intervals：互不重叠的区间列表；toBeRemoved：要删除的区间
        self, intervals: List[List[int]], toBeRemoved: List[int]  # 参数续行：两个输入参数的类型标注
    ) -> List[List[int]]:  # 返回值是删除后剩下的区间列表
        x, y = toBeRemoved  # 解包出要删除区间的左右端点 x、y
        ans = []  # 存放删除后的结果
        for a, b in intervals:  # 逐个处理原有区间
            if a >= y or b <= x:  # 当前区间完全在删除区间左侧或右侧，没有交集
                ans.append([a, b])  # 没有重叠部分，原样加入结果
            else:  # 否则当前区间与删除区间相交
                if a < x:  # 交集左侧还剩下片段 [a, x)
                    ans.append([a, x])  # 保留左残段
                if b > y:  # 交集右侧还剩下片段 (y, b]
                    ans.append([y, b])  # 保留右残段
        return ans  # 返回删除后的区间列表
