# 题目：587. 安装栅栏（Erect the Fence）
# 思路：先按坐标字典序排序，用单调链（Andrew）扫描求凸包；第二趟放宽条件，把落在边界上的共线点也收进栅栏。
# 时间复杂度：O(n log n)，瓶颈在排序，两次扫描都是 O(n)；空间复杂度：O(n)，标记数组、栈与答案都至多 n 个元素。
class Solution:  # LeetCode 约定的题解类
    def outerTrees(self, trees: List[List[int]]) -> List[List[int]]:  # trees 是所有树的坐标，返回位于栅栏上的点
        def cross(i, j, k):  # 用下标取点，计算 i→j→k 的叉积
            a, b, c = trees[i], trees[j], trees[k]  # 一次取出三个点，后面写起来更短
            return (b[0] - a[0]) * (c[1] - b[1]) - (b[1] - a[1]) * (c[0] - b[0])  # 结果 < 0 表示右转（凹），= 0 表示三点共线

        n = len(trees)  # 点的个数
        if n < 4:  # 少于 4 个点时所有点都在栅栏上
            return trees  # 直接原样返回
        trees.sort()  # 按 (x, y) 字典序排序，让扫描方向确定
        vis = [False] * n  # vis[i] 标记第 i 个点是否已落在边界上
        stk = [0]  # 栈里放点的下标，先放入最左下的点
        for i in range(1, n):  # 第一趟：从左到右求下凸包
            while len(stk) > 1 and cross(stk[-2], stk[-1], i) < 0:  # 栈顶造成右转，说明它不是边界点
                vis[stk.pop()] = False  # 弹栈并撤销该点的边界标记
            vis[i] = True  # 当前点暂时记为边界点
            stk.append(i)  # 当前点入栈
        m = len(stk)  # 记下下凸包的栈大小，第二趟据此保护已确定的部分
        for i in range(n - 2, -1, -1):  # 第二趟：从右到左求上凸包，并补收共线点
            if vis[i]:  # 已在下凸包上的点跳过
                continue  # 进入下一轮
            while len(stk) > m and cross(stk[-2], stk[-1], i) < 0:  # 同样判断栈顶是否造成右转
                stk.pop()  # 右转则弹出栈顶
            stk.append(i)  # 当前点入栈
        stk.pop()  # 首尾两点重合，弹出最后一个避免重复
        return [trees[i] for i in stk]  # 按栈中下标取出坐标就是答案
