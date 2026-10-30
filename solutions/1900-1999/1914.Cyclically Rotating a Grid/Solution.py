# 题目：1914. 循环轮转矩阵（Cyclically Rotating a Grid）
# 思路：逐层处理，把第 p 圈按顺时针展开成一维列表，切成 nums[k:] + nums[:k] 完成右移 k 位，再按同样顺序写回矩阵。
# 时间复杂度：O(m*n)，每个格子被读写常数次；空间复杂度：O(min(m, n))，只保存当前这一圈的元素。
class Solution:  # LeetCode 约定的题解类
    def rotateGrid(self, grid: List[List[int]], k: int) -> List[List[int]]:  # grid：待轮转的矩阵；k：顺时针轮转步数
        def rotate(p: int, k: int):  # 内部函数 rotate(p, k)：处理第 p 圈（p 从 0 开始，由外向内）
            nums = []  # nums：按顺时针顺序暂存这一圈的元素
            for j in range(p, n - p - 1):  # 上边：从左到右（不含右上角，避免重复）
                nums.append(grid[p][j])  # 收集上边元素
            for i in range(p, m - p - 1):  # 右边：从上到下
                nums.append(grid[i][n - p - 1])  # 收集右边元素
            for j in range(n - p - 1, p, -1):  # 下边：从右到左
                nums.append(grid[m - p - 1][j])  # 收集下边元素
            for i in range(m - p - 1, p, -1):  # 左边：从下到上
                nums.append(grid[i][p])  # 收集左边元素，四条边首尾相接正好覆盖整圈
            k %= len(nums)  # 轮转 k 位等价于对圈长取模，避免多余绕圈
            if k == 0:  # 余数为 0 说明这一圈无需移动
                return  # 直接返回，省掉一次无意义的写回
            nums = nums[k:] + nums[:k]  # 切成后半段加前半段，即整体右移 k 位
            k = 0  # k 复用为写回时的游标，从 0 开始
            for j in range(p, n - p - 1):  # 重新走上边
                grid[p][j] = nums[k]  # 写入轮转后的值
                k += 1  # 游标后移
            for i in range(p, m - p - 1):  # 重新走右边
                grid[i][n - p - 1] = nums[k]  # 写入轮转后的值
                k += 1  # 游标后移
            for j in range(n - p - 1, p, -1):  # 重新走下边
                grid[m - p - 1][j] = nums[k]  # 写入轮转后的值
                k += 1  # 游标后移
            for i in range(m - p - 1, p, -1):  # 重新走左边
                grid[i][p] = nums[k]  # 写入轮转后的值
                k += 1  # 写完最后一个元素，整圈右移完成

        # 先取出行列数，rotate 内部通过闭包直接使用
        m, n = len(grid), len(grid[0])  # m、n：矩阵的行数与列数（供内部函数闭包使用）
        for p in range(min(m, n) >> 1):  # 圈数最多为 min(m, n) 的一半，由外向内逐层处理
            rotate(p, k)  # 处理第 p 圈
        return grid  # 返回原地修改后的矩阵
